#include <linux/module.h> 

#include <linux/kernel.h> 

#include <linux/init.h> 

#include <linux/fs.h> 

#include <linux/cdev.h> 

#include <linux/device.h> 

#include <linux/slab.h> 

#include <linux/mutex.h> 

#include <linux/wait.h> 

#include <linux/poll.h> 

#include <linux/ioctl.h> 

#include <linux/proc_fs.h> 

#include <linux/seq_file.h> 

#include <linux/kthread.h> 

#include <linux/delay.h> 

 

#define BUFFER_SIZE 1024 

#define DEVICE_NAME "mydriver" 


#define MY_MAGIC 'J' 


#define CLEAR_BUFFER _IO(MY_MAGIC,1) 

#define GET_BUFFER_SIZE _IOR(MY_MAGIC, 2, int) 

#define SET_BUFFER_SIZE _IOW(MY_MAGIC, 3, int) 

 

static struct task_struct *my_thread; 

 

static struct proc_dir_entry *proc_entry; 

static size_t buffer_size = BUFFER_SIZE; 

 

static DEFINE_MUTEX(my_lock); 

 

static char *kernel_buffer; 

static size_t data_size; 

 

static wait_queue_head_t read_queue; 

 

static dev_t dev_num; 

static struct cdev my_cdev; 

static struct class *my_class; 

static struct device *my_device; 

 

static int thread_function(void *data) 

{ 

        while(!kthread_should_stop()) 

        { 

                mutex_lock(&my_lock); 

 

                pr_info("Kernel thread: buffer size = %zu, data size = %zu\n", buffer_size, data_size); 

 

                mutex_unlock(&my_lock); 

 

                msleep(5000); 

        } 

 

        pr_info("Kernel thread exiting\n"); 

 

        return 0; 

} 

static ssize_t buffer_size_show(struct device *dev, struct device_attribute *attr, char *buf) 

{ 

        return sprintf(buf, "%zu\n", buffer_size); 

} 

 

static ssize_t data_size_show(struct device *dev, struct device_attribute *attr, char *buf) 

{ 

        return sprintf(buf, "%zu\n", data_size); 

} 

 

static DEVICE_ATTR_RO(buffer_size); 

static DEVICE_ATTR_RO(data_size); 

 

 

static int proc_show(struct seq_file *m, void *v) 

{ 

        seq_printf(m, "Driver name     : %s\n", DEVICE_NAME); 

        seq_printf(m, "Buffer size     : %zu bytes\n", buffer_size); 

        seq_printf(m, "Data size       : %zu bytes\n", data_size); 

        seq_printf(m, "Buffer address  : %px\n", kernel_buffer); 

 

        return 0; 

} 

 

static int proc_open(struct inode *inode, struct file *file) 

{ 

        return single_open(file, proc_show, NULL); 

} 

 

static const struct proc_ops proc_fops = { 

        .proc_open = proc_open, 

        .proc_read = seq_read, 

        .proc_release = single_release, 

}; 

 

 

 

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) 

{ 

        int size; 

        char *new_buffer; 

 

        switch (cmd) 

        { 

                case CLEAR_BUFFER: 

 

                        mutex_lock(&my_lock); 

 

                        memset(kernel_buffer, 0, buffer_size); 

                        data_size = 0; 

 

                        mutex_unlock(&my_lock); 

 

                        pr_info("IOCTL : Buffer Cleared\n"); 

 

                        break; 

 

                case GET_BUFFER_SIZE: 

 

                        size = data_size; 

 

                        if (copy_to_user((int __user *)arg, &size, sizeof(size))) 

                                return -EFAULT; 

 

                        pr_info("IOCTL : Current Data Size = %d\n", size); 

 

                        break; 

 

                case SET_BUFFER_SIZE: 

 

                        if (copy_from_user(&size, (int __user *)arg, sizeof(size))) 

                                return -EFAULT; 

 

                        if (size <= 0) 

                                return -EINVAL; 

 

                        new_buffer = kzalloc(size, GFP_KERNEL); 

 

                        if (!new_buffer) 

                                return -ENOMEM; 

 

                        mutex_lock(&my_lock); 

 

                        memcpy(new_buffer, 

                               kernel_buffer, 

                               min((size_t)size, data_size)); 

 

                        kfree(kernel_buffer); 

 

                        kernel_buffer = new_buffer; 

                        buffer_size = size; 

                        data_size = min((size_t)size, data_size); 

 

                        mutex_unlock(&my_lock); 

 

                        pr_info("IOCTL : Buffer resized to %d bytes\n", size); 

 

                        break; 

 

                default: 

                        return -EINVAL; 

        } 

 

        return 0; 

} 

 

static __poll_t device_poll(struct file *file, poll_table *wait) 

{ 

        __poll_t mask = 0; 

 

        pr_info("poll() called\n"); 

 

        poll_wait(file, &read_queue, wait); 

 

        mutex_lock(&my_lock); 

 

        pr_info("data_size = %zu\n", data_size); 

 

        if(data_size > 0) 

        { 

                pr_info("Returning POLLIN\n"); 

                mask |= POLLIN | POLLRDNORM; 

        } 

 

        mutex_unlock(&my_lock); 

 

        return mask; 

} 

 

static ssize_t device_write(struct file *file, const char __user* buff, size_t count, loff_t *ppos) 

{ 

        if(count > buffer_size) 

                count = buffer_size; 

        mutex_lock(&my_lock); 

 

        if(copy_from_user(kernel_buffer, buff, count)) 

        { 

                mutex_unlock(&my_lock); 

                return -EFAULT; 

        } 

 

        data_size = count; 

 

        mutex_unlock(&my_lock); 

 

        wake_up_interruptible(&read_queue); 

 

        pr_info("Written %zu bytes\n", count); 

 

        return count; 

} 

 

static ssize_t device_read(struct file *file, char __user *buff, size_t count, loff_t *ppos) 

{ 

        if(*ppos > 0) 

                return 0; 

        if(wait_event_interruptible(read_queue, data_size > 0)) 

                return -ERESTARTSYS; 

 

        mutex_lock(&my_lock); 

 

        if(count > data_size) 

                count = data_size; 

 

        if(copy_to_user(buff, kernel_buffer, count)) 

        { 

                mutex_unlock(&my_lock); 

                return -EFAULT; 

        } 

 

        *ppos += count; 

 

        mutex_unlock(&my_lock); 

        pr_info("Read %zu bytes\n", count); 

 

        return count; 

} 

 

 

static int device_open(struct inode *inode, struct file *file) 

{ 

        pr_info("Device opened\n"); 

 

        return 0; 

} 

 

static int device_release(struct inode *inode, struct file *file) 

{ 

        pr_info("Device closed\n"); 

 

        return 0; 

} 

 

static struct file_operations fops = { 

        .owner = THIS_MODULE, 

        .open  = device_open, 

        .release = device_release, 

        .read = device_read, 

        .write = device_write, 

        .poll = device_poll, 

        .unlocked_ioctl = device_ioctl, 

}; 

 

static int __init device_init(void) 

{ 

        int ret; 

 

        ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME); 

        if(ret) 

        { 

                pr_err("Failed to allocate device number\n"); 

 

                return ret; 

        } 

 

        cdev_init(&my_cdev, &fops); 

        my_cdev.owner = THIS_MODULE; 

 

        ret = cdev_add(&my_cdev, dev_num, 1); 

        if(ret) 

        { 

                unregister_chrdev_region(dev_num, 1); 

                return ret; 

        } 

 

        my_class = class_create(THIS_MODULE, DEVICE_NAME); 

 

        if(IS_ERR(my_class)){ 

                cdev_del(&my_cdev); 

                unregister_chrdev_region(dev_num, 1); 

                return PTR_ERR(my_class); 

        } 

 

        my_device = device_create(my_class, NULL, dev_num, NULL, DEVICE_NAME); 

 

        if(IS_ERR(my_device)){ 

                class_destroy(my_class); 

                cdev_del(&my_cdev); 

                unregister_chrdev_region(dev_num, 1); 

                return PTR_ERR(my_device); 

        } 

 

        pr_info("Driver loaded\n"); 

        pr_info("Major = %d Minor = %d\n", MAJOR(dev_num), MINOR(dev_num)); 

 

        device_create_file(my_device, &dev_attr_buffer_size); 

        device_create_file(my_device, &dev_attr_data_size); 

 

        kernel_buffer = kzalloc(buffer_size, GFP_KERNEL); 

        if(!kernel_buffer){ 

                device_destroy(my_class, dev_num); 

                class_destroy(my_class); 

                cdev_del(&my_cdev); 

                unregister_chrdev_region(dev_num, 1); 

                return -ENOMEM; 

        } 

 

        data_size = 0; 

 

        pr_info("Kernel buffer allocated\n"); 

        pr_info("Buffer Address : %px\n", kernel_buffer); 

        pr_info("Buffer Size    : %d bytes\n", BUFFER_SIZE); 

 

        init_waitqueue_head(&read_queue); 

        proc_entry = proc_create(DEVICE_NAME, 0444, NULL, &proc_fops); 

 

        if(!proc_entry) 

        { 

                pr_err("Failed to create proc entry\n"); 

 

                kfree(kernel_buffer); 

 

                device_destroy(my_class, dev_num); 

                class_destroy(my_class); 

                cdev_del(&my_cdev); 

                unregister_chrdev_region(dev_num, 1); 

 

                return -ENOMEM; 

        } 

 

        pr_info("/proc/%s created\n", DEVICE_NAME); 

 

        my_thread = kthread_run(thread_function, NULL, "mydriver_thread"); 

 

        if (IS_ERR(my_thread)) 

        { 

                pr_err("Failed to create kernel thread\n"); 

 

                kfree(kernel_buffer); 

 

                device_destroy(my_class, dev_num); 

                class_destroy(my_class); 

                cdev_del(&my_cdev); 

                unregister_chrdev_region(dev_num, 1); 

 

                return PTR_ERR(my_thread); 

        } 

 

        pr_info("Kernel thread started\n"); 

        return 0; 

} 

 

static void __exit device_exit(void) 

{ 

        device_destroy(my_class, dev_num); 

        class_destroy(my_class); 

        cdev_del(&my_cdev); 

        unregister_chrdev_region(dev_num, 1); 

        pr_info("Driver unloaded\n"); 

 

        kfree(kernel_buffer); 

        kernel_buffer = NULL; 

 

        pr_info("Kernel buffer freed\n"); 

        proc_remove(proc_entry); 

        pr_info("/proc/%s removed\n", DEVICE_NAME); 

        device_remove_file(my_device, &dev_attr_buffer_size); 

        device_remove_file(my_device, &dev_attr_data_size); 

 

        if(my_thread) 

                kthread_stop(my_thread); 

} 

module_init(device_init); 

module_exit(device_exit); 

MODULE_LICENSE("GPL"); 