#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/mod_devicetable.h>
#include "platform.h"

#define NO_OF_DEVICES 10


#define MEM_SIZE_MAX_CHDEV1 1024
#define MEM_SIZE_MAX_CHDEV2 1024
#define MEM_SIZE_MAX_CHDEV3 1024
#define MEM_SIZE_MAX_CHDEV4 1024


char device_buffer_chdev1[MEM_SIZE_MAX_CHDEV1];
char device_buffer_chdev2[MEM_SIZE_MAX_CHDEV2];
char device_buffer_chdev3[MEM_SIZE_MAX_CHDEV3];
char device_buffer_chdev4[MEM_SIZE_MAX_CHDEV4];


// struct ch_dev_private_data
// {
// 	char *buffer;
// 	unsigned size;
// 	const char *serial_number;
// 	int perm;
// 	struct cdev ch_dev;
// };

struct ch_dev_private_data
{
	struct pcdev_platform_data pdata;
	char *buffer;
	dev_t dev_num;
	struct cdev ch_dev;
};

// struct ch_driver_private_data
// {
// 	int total_devices;

// 	dev_t device_number;

// 	struct class *class_ch;
// 	struct device *ch_device;

// 	struct ch_dev_private_data ch_dev_data[NO_OF_DEVICES];
// };

struct ch_driver_private_data
{
	int total_devices;
	dev_t device_num_base;
	struct class *class_ch;
	struct device *ch_device;
};

struct ch_driver_private_data pcdrv_data;


enum pcdev_names
{
	PCDEVA1X,
	PCDEVB1X,
	PCDEVC1X,
	PCDEVD1X
};

struct device_config
{
	int config_item1;
	int config_item2;
};

struct device_config pcdev_config[] = {
	[PCDEVA1X] = {.config_item1 = 60, .config_item2 = 21},
	[PCDEVB1X] = {.config_item1 = 50, .config_item2 = 22},
	[PCDEVC1X] = {.config_item1 = 40, .config_item2 = 23},
	[PCDEVD1X] = {.config_item1 = 30, .config_item2 = 24},
};


struct platform_device_id pcdevs_ids[] = {
	[0] = {
		.name = "pcdev-A1x",
		.driver_data = PCDEVA1X,
	},
	[1] = {
		.name = "pcdev-B1x",
		.driver_data = PCDEVB1X,
	},
	[2] = {
		.name = "pcdev-C1x",
		.driver_data = PCDEVC1X,
	},
	[3] = {
		.name = "pcdev-D1x",
		.driver_data = PCDEVD1X,
	}
};


loff_t ch_lseek(struct file *filp, loff_t offset, int whence)
{
	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->pdata.size;

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

	return 0;

}

ssize_t ch_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->pdata.size;

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

	return count;

}

ssize_t ch_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{

	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->pdata.size;

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

	ret = check_permission(ch_dev_pv_data->pdata.perm,filp->f_mode);

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

/*called when matched device is found*/
int pcd_platform_driver_probe(struct platform_device *pdev)
{
	int ret;

	struct ch_dev_private_data *dev_data;

	struct pcdev_platform_data *pdata;

	pr_info("A Device is detected\n");

	pdata = (struct pcdev_platform_data*)dev_get_platdata(&pdev->dev);
	if(!pdata)
	{
			pr_info("No platform data available\n");
			pr_info("Device probe failed\n");
			return -EINVAL;
	}
	
	//allocate mem for device private data
	dev_data = devm_kzalloc(&pdev->dev,sizeof(struct pcdev_platform_data),GFP_KERNEL);
	if(!dev_data)
	{
		pr_info("Cannot allocate memory\n");
		return -ENOMEM;

	}

	//save the device private data pointer in platform device structure
	dev_set_drvdata(&pdev->dev, dev_data);

	dev_data->pdata.size = pdata->size;
	dev_data->pdata.perm = pdata->perm;
	dev_data->pdata.serial_number = pdata->serial_number;

	pr_info("Device serial number = %s\n",dev_data->pdata.serial_number);
	pr_info("Device size = %d\n",dev_data->pdata.size);
	pr_info("Device permission = %d\n",dev_data->pdata.perm);

	/*configuring the platform device using id_tables in platform_device*/
	pr_info("Config item 1 = %d\n",pcdev_config[pdev->id_entry->driver_data].config_item1);
	pr_info("Config item 2 = %d\n",pcdev_config[pdev->id_entry->driver_data].config_item2);


	//allocate mem for device private data's buffer
	dev_data->buffer = devm_kzalloc(&pdev->dev,dev_data->pdata.size,GFP_KERNEL);
	if(!dev_data->buffer)
	{
		pr_info("Cannot allocate memory\n");
		return -ENOMEM;
		
	}
	

	dev_data->dev_num = (pcdrv_data.device_num_base + pdev->id);

	cdev_init(&dev_data->ch_dev,&ch_fops);

	dev_data->ch_dev.owner = THIS_MODULE;
	ret = cdev_add(&dev_data->ch_dev,dev_data->dev_num,1);
	if(ret < 0)
	{
		pr_err("Cdev add failed\n");
		return ret;
	}

	pcdrv_data.ch_device = device_create(pcdrv_data.class_ch,NULL,dev_data->dev_num,NULL,"ch_device-%d",pdev->id);
	if(IS_ERR(pcdrv_data.ch_device))
	{
		pr_err("Device creation failed\n");
		ret = PTR_ERR(pcdrv_data.ch_device);
		cdev_del(&dev_data->ch_dev);
		return ret;
	}

	pcdrv_data.total_devices++;

	pr_info("The probe was succussful\n");
    return 0;
}


/*called when the device is removed from the system*/
int pcd_platform_driver_remove(struct platform_device *pdev)
{
	struct ch_dev_private_data *dev_data = dev_get_drvdata(&pdev->dev);
	
	device_destroy(pcdrv_data.class_ch,dev_data->dev_num);

	cdev_del(&dev_data->ch_dev);


	pcdrv_data.total_devices--;

	pr_info("A device is removed\n");
    return 0;
}




struct platform_driver pcd_platform_driver = {
    .probe = pcd_platform_driver_probe,
    .remove = pcd_platform_driver_remove,
	.id_table = pcdevs_ids,
    .driver = {
        .name = "pseudo-char-device",
    }

};



static int __init pcd_platform_driver_in(void)
{

	int ret;

	ret = alloc_chrdev_region(&pcdrv_data.device_num_base,0,NO_OF_DEVICES,"chr_devices");
	if(ret < 0)
	{
		pr_err("Alloc chrdev failed\n");
		//pr_info("Module insertion failed\n");
		return ret;
	}

	pcdrv_data.class_ch = class_create(THIS_MODULE,"ch_class");
	if(IS_ERR(pcdrv_data.class_ch))
	{
		pr_err("Class creation failed\n");
		ret = PTR_ERR(pcdrv_data.class_ch);
		unregister_chrdev_region(pcdrv_data.device_num_base,NO_OF_DEVICES);
		return ret;
	}

    platform_driver_register(&pcd_platform_driver);
    pr_info("pcd platform driver loaded\n");

	return 0;

}

static void __exit pcd_platform_driver_ex(void)
{

    platform_driver_unregister(&pcd_platform_driver);
    pr_info("pcd platform driver unloaded\n");


	class_destroy(pcdrv_data.class_ch);

	unregister_chrdev_region(pcdrv_data.device_num_base,NO_OF_DEVICES);

	pr_info("module unloaded\n");

}

module_init(pcd_platform_driver_in);
module_exit(pcd_platform_driver_ex);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("manohar");
MODULE_DESCRIPTION("character device driver for multiple devices");