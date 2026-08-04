#include <linux/module.h> 

#include <linux/fs.h> 

#include <linux/cdev.h> 

#include <linux/device.h> 

#include <linux/uaccess.h> 

#include <linux/mutex.h> 

#include <linux/wait.h> 

#include <linux/timer.h> 

#include <linux/jiffies.h> 

#include <linux/random.h> 

#include <linux/proc_fs.h> 

#include <linux/seq_file.h> 

#include <linux/kobject.h> 

#include <linux/sysfs.h> 

#include <linux/version.h> 

#include "tempsensor_ioctl.h" 

#define DEVICE_NAME "tempsensor" 

#define CLASS_NAME "tempsensor_class" 

#define PROC_NAME "tempsensor" 

 

static dev_t dev_num; 

static struct cdev my_cdev; 

static struct class *my_class; 

static struct proc_dir_entry *proc_entry; 

static struct kobject *sensor_kobj; 

static struct timer_list sample_timer; 

static DEFINE_MUTEX(sensor_lock); 

static DECLARE_WAIT_QUEUE_HEAD(threshold_wq); 

 

static int current_temp = 25; /* degrees C */ 

static int low_limit = 10; 

static int high_limit = 40; 

static int interval_ms = 1000; /* sampling period */ 

static int threshold_event;  /* set when temp goes out of range */ 

static unsigned long sample_count; 

static unsigned long threshold_event_count; 

 

static void sample_timer_cb(struct timer_list *t) 

{ 

    int new_temp; 

    u32 rnd; 

    get_random_bytes(&rnd, sizeof(rnd)); 

  /* random walk within [-2, +2] around a base range, clamped to [-20, 80] */ 

    new_temp = current_temp + ((int)(rnd % 5) - 2); 

     if (new_temp < -20) 

         new_temp = -20; 

    if (new_temp > 80) 

        new_temp = 80; 

 

     mutex_lock(&sensor_lock); 

    current_temp = new_temp; 

    sample_count++; 

 

    if (current_temp < low_limit || current_temp > high_limit) 

    { 

        threshold_event = 1; 

         threshold_event_count++; 

         mutex_unlock(&sensor_lock); 

         wake_up_interruptible(&threshold_wq); 

     } 

     else 

     { 

     mutex_unlock(&sensor_lock); 

     } 

 

     mod_timer(&sample_timer, jiffies + msecs_to_jiffies(interval_ms)); 

} 

 

static int dev_open(struct inode *inode, struct file *file) { return 0; } 

static int dev_release(struct inode *inode, struct file *file) { return 0; } 

 

/* Blocks until a threshold event occurs, then reports the temperature 

* that triggered it as ASCII text, e.g. "47\n". */ 

static ssize_t dev_read(struct file *file, char __user *buf, size_t len, loff_t *offset) 

{ 

     char tmp[16]; 

     int n, ret, temp_snapshot; 

 

    if (*offset > 0) 
        return 0; 

 

    ret = wait_event_interruptible(threshold_wq, threshold_event != 0); 

    if (ret) 
        return -ERESTARTSYS; 

    mutex_lock(&sensor_lock); 

    temp_snapshot = current_temp; 

    threshold_event = 0; 

     mutex_unlock(&sensor_lock); 

 

     n = scnprintf(tmp, sizeof(tmp), "%d\n", temp_snapshot); 

     if (n > len) 
         n = len; 

     if (copy_to_user(buf, tmp, n)) 
        return -EFAULT; 

 

     *offset += n; 

     return n; 

} 

 

/* write() is not used for control; ioctl configures limits. Reject writes. */ 

static ssize_t dev_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) 

{ 

     return -EPERM; 

} 

 

static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg) 

{ 

     struct temp_limits limits; 

     switch (cmd) 

     { 

    case TEMPSENSOR_SET_LIMITS: 

         if (copy_from_user(&limits, (void __user *)arg, sizeof(limits))) 

             return -EFAULT; ;

         if (limits.low_limit >= limits.high_limit) 

             return -EINVAL; 

         mutex_lock(&sensor_lock); 

         low_limit = limits.low_limit; 

         high_limit = limits.high_limit; 

         mutex_unlock(&sensor_lock); 

         pr_info("tempsensor: limits set to [%d, %d]\n", low_limit, high_limit); 

         break; 

 

    case TEMPSENSOR_GET_LIMITS: 


        mutex_lock(&sensor_lock); 

        limits.low_limit = low_limit; 

        limits.high_limit = high_limit; 

        mutex_unlock(&sensor_lock); 

        if (copy_to_user((void __user *)arg, &limits, sizeof(limits))) 

        return -EFAULT; 

        break; 

 

    default: 

        return -ENOTTY; 

  } 

  return 0; 

} 

 

static const struct file_operations fops = { 

  .owner = THIS_MODULE, 

  .open = dev_open, 

  .release = dev_release, 

  .read = dev_read, 

  .write = dev_write, 

  .unlocked_ioctl = dev_ioctl, 

}; 

 

static int proc_show(struct seq_file *m, void *v) 

{ 

  mutex_lock(&sensor_lock); 

  seq_printf(m, "Current Temp  : %d C\n", current_temp); 

  seq_printf(m, "Low Limit    : %d C\n", low_limit); 

  seq_printf(m, "High Limit   : %d C\n", high_limit); 

  seq_printf(m, "Sample Interval : %d ms\n", interval_ms); 

  seq_printf(m, "Sample Count  : %lu\n", sample_count); 

  seq_printf(m, "Threshold Events: %lu\n", threshold_event_count); 

  mutex_unlock(&sensor_lock); 

  return 0; 

} 

 

static int proc_open(struct inode *inode, struct file *file) 

{ 

  return single_open(file, proc_show, NULL); 

} 

 

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 6, 0) 

static const struct file_operations proc_fops = { 

  .owner = THIS_MODULE, 

  .open = proc_open, 

  .read = seq_read, 

  .llseek = seq_lseek, 

  .release = single_release, 

}; 

#else 

static const struct proc_ops proc_fops = { 

  .proc_open = proc_open, 

  .proc_read = seq_read, 

  .proc_lseek = seq_lseek, 

  .proc_release = single_release, 

}; 

#endif 

 

static ssize_t current_temp_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) 

{ 

  int t; 

 

  mutex_lock(&sensor_lock); 

  t = current_temp; 

  mutex_unlock(&sensor_lock); 

  return sprintf(buf, "%d\n", t); 

} 

 

static ssize_t interval_ms_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) 

{ 

  return sprintf(buf, "%d\n", interval_ms); 

} 

 

static ssize_t interval_ms_store(struct kobject *kobj, struct kobj_attribute *attr,  const char *buf, size_t count) 

{ 

  int val; 

 

  if (kstrtoint(buf, 10, &val) < 0 || val < 100) 

    return -EINVAL; 

  interval_ms = val; 

  return count; 

} 

 

static struct kobj_attribute current_temp_attr = __ATTR_RO(current_temp); 

static struct kobj_attribute interval_ms_attr = __ATTR(interval_ms, 0664, interval_ms_show, interval_ms_store); 

 

static struct attribute *sensor_attrs[] = { 

  &current_temp_attr.attr, 

  &interval_ms_attr.attr, 

  NULL, 

}; 

static struct attribute_group sensor_attr_group = {.attrs = sensor_attrs}; 

 

static int __init tempsensor_init(void) 

{ 

  int ret; 

 

  ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME); 

  if (ret < 0) 

    return ret; 

 

  cdev_init(&my_cdev, &fops); 

  ret = cdev_add(&my_cdev, dev_num, 1); 

  if (ret < 0) 

    goto unregister_region; 

 

#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 4, 0) 

  my_class = class_create(THIS_MODULE, CLASS_NAME); 

#else 

  my_class = class_create(CLASS_NAME); 

#endif 

  if (IS_ERR(my_class)) 

  { 

    ret = PTR_ERR(my_class); 

    goto del_cdev; 

  } 

 

  if (IS_ERR(device_create(my_class, NULL, dev_num, NULL, DEVICE_NAME))) 

  { 

    ret = -ENODEV; 

    goto destroy_class; 

  } 

 

  proc_entry = proc_create(PROC_NAME, 0444, NULL, &proc_fops); 

  if (!proc_entry) 

  { 

    ret = -ENOMEM; 

    goto destroy_device; 

  } 

 

  sensor_kobj = kobject_create_and_add("tempsensor", kernel_kobj); 

  if (!sensor_kobj) 

  { 

    ret = -ENOMEM; 

    goto remove_proc; 

  } 

 

  ret = sysfs_create_group(sensor_kobj, &sensor_attr_group); 

  if (ret) 

    goto put_kobj; 

 

  timer_setup(&sample_timer, sample_timer_cb, 0); 

  mod_timer(&sample_timer, jiffies + msecs_to_jiffies(interval_ms)); 

 

  pr_info("tempsensor: virtual temperature sensor loaded\n"); 

  return 0; 

 

put_kobj: 

  kobject_put(sensor_kobj); 

remove_proc: 

  proc_remove(proc_entry); 

destroy_device: 

  device_destroy(my_class, dev_num); 

destroy_class: 

  class_destroy(my_class); 

del_cdev: 

  cdev_del(&my_cdev); 

unregister_region: 

  unregister_chrdev_region(dev_num, 1); 

  return ret; 

} 

 

static void __exit tempsensor_exit(void) 

{ 

del_timer_sync(&sample_timer); 

  kobject_put(sensor_kobj); 

  proc_remove(proc_entry); 

  device_destroy(my_class, dev_num); 

  class_destroy(my_class); 

  cdev_del(&my_cdev); 

  unregister_chrdev_region(dev_num, 1); 

  pr_info("tempsensor: module unloaded\n"); 

} 

module_init(tempsensor_init); 

module_exit(tempsensor_exit); 

 

MODULE_LICENSE("GPL"); 