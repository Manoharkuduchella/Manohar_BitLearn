#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>

#define NO_OF_DEVICES 4

#define RDONLY 		0x01
#define WRONLY 		0x10
#define RDWR 		0x11

#define MEM_SIZE_MAX_CHDEV1 1024
#define MEM_SIZE_MAX_CHDEV2 1024
#define MEM_SIZE_MAX_CHDEV3 1024
#define MEM_SIZE_MAX_CHDEV4 1024


char device_buffer_chdev1[MEM_SIZE_MAX_CHDEV1];
char device_buffer_chdev2[MEM_SIZE_MAX_CHDEV2];
char device_buffer_chdev3[MEM_SIZE_MAX_CHDEV3];
char device_buffer_chdev4[MEM_SIZE_MAX_CHDEV4];


struct ch_dev_private_data
{
	char *buffer;
	unsigned size;
	const char *serial_number;
	int perm;
	struct cdev ch_dev;

	//struct spinlock_t ch_dev_spin_lock;
	struct mutex ch_dev_mutex_lock;
};

struct ch_driver_private_data
{
	int total_devices;

	dev_t device_number;

	struct class *class_ch;
	struct device *ch_device;

	struct ch_dev_private_data ch_dev_data[NO_OF_DEVICES];
};

struct ch_driver_private_data ch_driver_pv_data =
{
	.total_devices = NO_OF_DEVICES,
	.ch_dev_data = {
		[0] = {
			.buffer = device_buffer_chdev1,
			.size = MEM_SIZE_MAX_CHDEV1,
			.serial_number = "ch_dev0",
			.perm = RDONLY,/*RDONLY*/
		},

		[1] = {
			.buffer = device_buffer_chdev2,
			.size = MEM_SIZE_MAX_CHDEV2,
			.serial_number = "ch_dev1",
			.perm = WRONLY,/*WRONLY*/
		},

		[2] = {
			.buffer = device_buffer_chdev3,
			.size = MEM_SIZE_MAX_CHDEV3,
			.serial_number = "ch_dev2",
			.perm = RDWR,/*RDWR*/
		},

		[3] = {
			.buffer = device_buffer_chdev4,
			.size = MEM_SIZE_MAX_CHDEV4,
			.serial_number = "ch_dev3",
			.perm = RDWR,/*RDWR*/
		}
	}

};


loff_t ch_lseek(struct file *filp, loff_t offset, int whence)
{
	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->size;

	loff_t temp;

	pr_info("lseek requested\n");
	pr_info("%s : Current value of file position = %lld\n",__func__,filp->f_pos);

	switch (whence)
	{
		case SEEK_SET:
			if( (offset > max_size)||(offset < 0) )
				return -EINVAL;
			filp->f_pos = offset; break;
		case SEEK_CUR:
			temp = filp->f_pos + offset;
			if( (temp > max_size) || (temp < 0) )
				return -EINVAL;
			filp->f_pos += offset; break;
		case SEEK_END:
			temp = max_size + offset;
			if( (temp > max_size) || ( temp < 0) )
				return -EINVAL;
			filp->f_pos = max_size + offset; break;
		default:
			return -EINVAL;
	}

	pr_info("%s : New value of the file position = %lld\n",__func__,filp->f_pos);

	return filp->f_pos;

}

ssize_t ch_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->size;

	mutex_lock(&ch_dev_pv_data->ch_dev_mutex_lock);

	pr_info("read requested for %zu bytes\n",count);
	pr_info("%s : Current file position = %lld\n",__func__,*f_pos);

	if(*f_pos + count > max_size)
		count = (max_size - *f_pos);

	if(copy_to_user(buff,ch_dev_pv_data->buffer+(*f_pos),count))
	{
		return -EFAULT;
	}

	*f_pos += count;

	pr_info("Number of bytes successfully read = %zu\n",count);
	pr_info("%s : Updated file position = %lld\n",__func__,*f_pos);

	mutex_unlock(&ch_dev_pv_data->ch_dev_mutex_lock);

	return count;
}

ssize_t ch_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{

	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->size;

	mutex_lock(&ch_dev_pv_data->ch_dev_mutex_lock);

	pr_info("write requested for %zu bytes\n",count);
	pr_info("%s : Current file position = %lld\n",__func__,*f_pos);

	if(*f_pos + count > max_size)
		count = (max_size - *f_pos);

	if(!count)
	{
		pr_err("%s : No space left on the device\n",__func__);
		return -ENOMEM;
	}

	if(copy_from_user(ch_dev_pv_data->buffer+(*f_pos),buff,count))
	{
		return -EFAULT;
	}

	*f_pos += count;

	pr_info("Number of bytes successfully written = %zu\n",count);
	pr_info("%s : Updated file position = %lld\n",__func__,*f_pos);

	mutex_unlock(&ch_dev_pv_data->ch_dev_mutex_lock);

	return count;
}



int check_permission(int dev_perm,int acc_mode)
{
	if(dev_perm == RDWR)
		return 0;

	if( (dev_perm == RDONLY) && (acc_mode & FMODE_READ) && !(acc_mode & FMODE_WRITE) )
		return 0;

	if( (dev_perm == WRONLY) && (acc_mode & FMODE_WRITE) && !(acc_mode & FMODE_READ) )
		return 0;

	return -EPERM;

}

int ch_open(struct inode *pinode, struct file *filp)
{

	int ret;
	int minor_n;

	struct ch_dev_private_data *ch_dev_pv_data; 

	minor_n = MINOR(pinode->i_rdev);
	pr_info("%s : minor access = %d\n",__func__,minor_n);

	//to get address of parent struct by using its member
	ch_dev_pv_data = container_of(pinode->i_cdev,struct ch_dev_private_data,ch_dev);

	//supply this parent struct to other file operations as well by using void *private_data of struct file
	filp->private_data = ch_dev_pv_data;

	ret = check_permission(ch_dev_pv_data->perm,filp->f_mode);

	(!ret)? pr_info("open was successfull\n") : pr_info("open was unsuccessfull\n");

	
	return ret;
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
	int ret,i;

	ret = alloc_chrdev_region(&ch_driver_pv_data.device_number,0,NO_OF_DEVICES,"chr_devices");
	if(ret < 0)
	{
		pr_err("Alloc chrdev failed\n");
		goto out;
	}

	ch_driver_pv_data.class_ch = class_create(THIS_MODULE,"ch_class");
	if(IS_ERR(ch_driver_pv_data.class_ch))
	{
		pr_err("Class creation failed\n");
		ret = PTR_ERR(ch_driver_pv_data.class_ch);
		goto unreg_chrdev;
	}

	for(i=0;i<NO_OF_DEVICES;i++)
	{
		pr_info("%s : Device number <major>:<minor> = %d:%d\n",__func__, MAJOR(ch_driver_pv_data.device_number+i),MINOR(ch_driver_pv_data.device_number+i));

		mutex_init(&ch_driver_pv_data.ch_dev_data[i].ch_dev_mutex_lock);

		cdev_init(&ch_driver_pv_data.ch_dev_data[i].ch_dev,&ch_fops);


		ch_driver_pv_data.ch_dev_data[i].ch_dev.owner = THIS_MODULE;
		ret = cdev_add(&ch_driver_pv_data.ch_dev_data[i].ch_dev,ch_driver_pv_data.device_number+i,1);
		if(ret < 0)
			goto cdev_del;


		ch_driver_pv_data.ch_device = device_create(ch_driver_pv_data.class_ch,NULL,ch_driver_pv_data.device_number+i,NULL,"ch_device-%d",i+1);
		if(IS_ERR(ch_driver_pv_data.ch_device))
		{
			pr_err("Device creation failed\n");
			ret = PTR_ERR(ch_driver_pv_data.ch_device);
			goto class_del;
		}

	}
	


	pr_info("module init was successfull\n");

	return 0;


	cdev_del:
	class_del:
		for(;i>=0;i++)
		{
			device_destroy(ch_driver_pv_data.class_ch,ch_driver_pv_data.device_number+i);
			cdev_del(&ch_driver_pv_data.ch_dev_data[i].ch_dev);
		}
		class_destroy(ch_driver_pv_data.class_ch);


	unreg_chrdev:
		unregister_chrdev_region(ch_driver_pv_data.device_number,NO_OF_DEVICES);

	out:
		pr_info("Module insertion failed\n");
		return ret;

}

static void __exit chr_ex(void)
{
	int i;
	for(i=0;i<NO_OF_DEVICES;i++)
	{
		device_destroy(ch_driver_pv_data.class_ch,ch_driver_pv_data.device_number+i);
		cdev_del(&ch_driver_pv_data.ch_dev_data[i].ch_dev);
	}

	class_destroy(ch_driver_pv_data.class_ch);

	unregister_chrdev_region(ch_driver_pv_data.device_number,NO_OF_DEVICES);

	pr_info("module unloaded\n");

}

module_init(chr_in);
module_exit(chr_ex);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("manohar");
MODULE_DESCRIPTION("character device driver for multiple devices");
