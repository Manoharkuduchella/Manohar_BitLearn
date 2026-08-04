#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>


#define DEV_MEM_SIZE 512

char device_buffer[DEV_MEM_SIZE];

dev_t device_number;

struct cdev ch_dev;

struct class *class_ch;

struct device *ch_device;

static DEFINE_SPINLOCK(pcd_spin_lock);

static DEFINE_MUTEX(pcd_mutex_lock);

loff_t ch_lseek(struct file *filp, loff_t offset, int whence)
{
	loff_t temp;

	pr_info("lseek requested\n");
	pr_info("Current value of file position = %lld\n", filp->f_pos);

	switch (whence)
	{
		case SEEK_SET:
			if( (offset > DEV_MEM_SIZE)||(offset < 0) )
				return -EINVAL;
			filp->f_pos = offset; break;
		case SEEK_CUR:
			temp = filp->f_pos + offset;
			if( (temp > DEV_MEM_SIZE) || (temp < 0) )
				return -EINVAL;
			filp->f_pos += offset; break;
		case SEEK_END:
			temp = DEV_MEM_SIZE + offset;
			if( (temp > DEV_MEM_SIZE) || ( temp < 0) )
				return -EINVAL;
			filp->f_pos = DEV_MEM_SIZE + offset; break;
		default:
			return -EINVAL;
	}

	pr_info("New value of the file position = %lld\n", filp->f_pos);

	return filp->f_pos;
}

ssize_t ch_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	//mutex_lock(&pcd_mutex_lock);
	if(mutex_lock_interruptible(&pcd_mutex_lock))
		return -EINTR;

	pr_info("read requested for %zu bytes\n",count);
	pr_info("Current file position = %lld\n",*f_pos);

	if(*f_pos + count > DEV_MEM_SIZE)
		count = (DEV_MEM_SIZE - *f_pos);

	if(copy_to_user(buff,&device_buffer[*f_pos],count))
	{
		return -EFAULT;
	}

	*f_pos += count;

	pr_info("Number of bytes successfully read = %zu\n",count);
	pr_info("Updated file position = %lld\n",*f_pos);

	mutex_unlock(&pcd_mutex_lock);

	return count;
}

ssize_t ch_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	//spin_lock(&pcd_spin_lock);//not suitable since critical section sleeps
	//mutex_lock(&pcd_mutex_lock);
	if(mutex_lock_interruptible(&pcd_mutex_lock))
		return -EINTR;

	pr_info("write requested for %zu bytes\n",count);
	pr_info("Current file position = %lld\n",*f_pos);

	if(*f_pos + count > DEV_MEM_SIZE)
		count = (DEV_MEM_SIZE - *f_pos);

	if(!count)
	{
		pr_err("%s : No space left on the device\n",__func__);
		return -ENOMEM;
	}

	if(copy_from_user(&device_buffer[*f_pos],buff,count))
	{
		return -EFAULT;
	}

	*f_pos += count;

	pr_info("Number of bytes successfully written = %zu\n",count);
	pr_info("Updated file position = %lld\n",*f_pos);

	//spin_unlock(&pcd_spin_lock);
	mutex_unlock(&pcd_mutex_lock);

	return count;

}

int ch_open(struct inode *pinode, struct file *filp)
{
	pr_info("open was successfull\n");
	return 0;
}

        
int ch_release(struct inode *pinode, struct file *filp)
{
	pr_info("release was successfull\n");
	return 0;
}


struct file_operations ch_fops = {
	.open = ch_open,
	.read = ch_read,
	.write = ch_write,
	.release = ch_release,
	.llseek = ch_lseek,
	.owner = THIS_MODULE

};




static int __init chr_in(void)
{
	int ret;

	ret = alloc_chrdev_region(&device_number,0,1,"chr_device");
	if(ret < 0)
		goto out;

	pr_info("%s : Device number <major>:<minor> = %d:%d\n",__func__, MAJOR(device_number),MINOR(device_number));


	cdev_init(&ch_dev,&ch_fops);


	ch_dev.owner = THIS_MODULE;
	ret = cdev_add(&ch_dev,device_number,1);
	if(ret < 0)
		goto unreg_chrdev;


	class_ch = class_create(THIS_MODULE,"ch_class");
	if(IS_ERR(class_ch))
	{
		pr_err("Class creation failed\n");
		ret = PTR_ERR(class_ch);
		goto cdev_del;
	}

	ch_device = device_create(class_ch,NULL,device_number,NULL,"ch_device");
	if(IS_ERR(ch_device))
	{
		pr_err("Device creation failed\n");
		ret = PTR_ERR(ch_device);
		goto class_del;
	}

	pr_info("module init was successfull\n");

	return 0;

	class_del:
		class_destroy(class_ch);

	cdev_del:
		cdev_del(&ch_dev);

	unreg_chrdev:
		unregister_chrdev_region(device_number,1);

	out:
		pr_info("Module insertion failed\n");
		return ret;
}

static void __exit chr_ex(void)
{
	device_destroy(class_ch,device_number);

	class_destroy(class_ch);

	cdev_del(&ch_dev);

	unregister_chrdev_region(device_number,1);

	pr_info("module unloaded\n");

}

module_init(chr_in);
module_exit(chr_ex);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("manohar");
MODULE_DESCRIPTION("character device driver");
