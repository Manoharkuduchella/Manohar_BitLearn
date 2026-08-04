#include "pcd_platform_driver_dt_sysfs.h"

#define NO_OF_DEVICES 10


#define MEM_SIZE_MAX_CHDEV1 1024
#define MEM_SIZE_MAX_CHDEV2 1024
#define MEM_SIZE_MAX_CHDEV3 1024
#define MEM_SIZE_MAX_CHDEV4 1024


char device_buffer_chdev1[MEM_SIZE_MAX_CHDEV1];
char device_buffer_chdev2[MEM_SIZE_MAX_CHDEV2];
char device_buffer_chdev3[MEM_SIZE_MAX_CHDEV3];
char device_buffer_chdev4[MEM_SIZE_MAX_CHDEV4];


struct ch_driver_private_data pcdrv_data;


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
	},
	{ }
};

struct of_device_id org_pcdev_dt_match[] = {
	{.compatible = "pcdev-A1x", .data = (void*)PCDEVA1X},
	{.compatible = "pcdev-B1x", .data = (void*)PCDEVB1X},
	{.compatible = "pcdev-C1x", .data = (void*)PCDEVC1X},
	{.compatible = "pcdev-D1x", .data = (void*)PCDEVD1X},
	{ }
};



struct file_operations ch_fops = {
	.open = ch_open,
	.read = ch_read,
	.write = ch_write,
	.release = ch_release,
	.llseek = ch_lseek,
	.owner = THIS_MODULE

};



ssize_t show_max_size(struct device *dev, struct device_attribute *attr,char *buf)
{
	struct ch_dev_private_data *dev_data = dev_get_drvdata(dev->parent);

	return sprintf(buf,"%d\n",dev_data->pdata.size);
}

ssize_t show_serial_num(struct device *dev, struct device_attribute *attr,char *buf)
{
	struct ch_dev_private_data *dev_data = dev_get_drvdata(dev->parent);

	return sprintf(buf,"%s\n",dev_data->pdata.serial_number);
	
}

ssize_t store_max_size(struct device *dev, struct device_attribute *attr,const char *buf, size_t count)
{

	long result;
	int ret;

	struct ch_dev_private_data *dev_data = dev_get_drvdata(dev->parent);

	ret = kstrtol(buf,10,&result);
	if(ret)
		return ret;

	dev_data->pdata.size = result;

	dev_data->buffer = krealloc(dev_data->buffer,dev_data->pdata.size,GFP_KERNEL);


	return count;
}




/*create 2 variables of struct device_attribute*/
static DEVICE_ATTR(max_size,S_IRUGO|S_IWUSR,show_max_size,store_max_size);

static DEVICE_ATTR(serial_num,S_IRUGO,show_serial_num,NULL);


struct attribute *pcd_attrs[] = {
	&dev_attr_max_size.attr,
	&dev_attr_serial_num.attr,
	NULL

};

const struct attribute_group pcd_attr_group = {
	.attrs = pcd_attrs
};


int pcd_sysfs_create_files(struct device *pcd_dev)
{
	// int ret;

	// ret = sysfs_create_files(&pcd_dev->kobj,(const struct attribute * const *)&dev_attr_max_size.attr);
	// if(ret)
	// 	return ret;

	// return sysfs_create_files(&pcd_dev->kobj,(const struct attribute * const *)&dev_attr_serial_num.attr);

	return sysfs_create_group(&pcd_dev->kobj,&pcd_attr_group);

}



struct pcdev_platform_data *pcdev_get_platform_from_dt(struct device *dev)
{
	struct device_node *dev_node = dev->of_node;
	struct pcdev_platform_data *pdata;

	if(!dev_node)
	{/*this probe not happen because of device tree node*/
		return NULL;
	}
	
	pdata = devm_kzalloc(dev,sizeof(*pdata),GFP_KERNEL);
	if(!pdata) {
		dev_info(dev,"Cannot allocate memory\n");
		return ERR_PTR(-ENOMEM);
	}

	
	if(of_property_read_string(dev_node,"org,device-serial-num",&pdata->serial_number))
	{
		dev_info(dev,"Missing serial number property\n");
		return ERR_PTR(-EINVAL);
	}

	if(of_property_read_u32(dev_node,"org,size",&pdata->size))
	{
		dev_info(dev,"Missing size property\n");
		return ERR_PTR(-EINVAL);
	}

		if(of_property_read_u32(dev_node,"org,perm",&pdata->perm))
	{
		dev_info(dev,"Missing perm property\n");
		return ERR_PTR(-EINVAL);
	}

	return pdata;
}


/*called when matched device is found*/
int pcd_platform_driver_probe(struct platform_device *pdev)
{
	int ret;

	struct ch_dev_private_data *dev_data;

	struct pcdev_platform_data *pdata;

	struct device *dev = &pdev->dev;

	int driver_data;

	const struct of_device_id *match;

	dev_info(dev,"A Device is detected\n");

	/*match will always be NULL if LINUX doesn't support device tree i.e CONFIG_OF is off*/
	match = of_match_device(of_match_ptr(org_pcdev_dt_match),dev);

	if(match)
	{
		pdata = pcdev_get_platform_from_dt(dev);

		if(IS_ERR(pdata))
		{
			return PTR_ERR(pdata);
		}
		driver_data = (int)match->data;
	}
	else{
		pdata = (struct pcdev_platform_data*)dev_get_platdata(dev);
		driver_data = pdev->id_entry->driver_data;
	}

	if(!pdata)
	{
		dev_info(dev,"No platform data available\n");
		return -EINVAL;
	}

	//allocate mem for device private data
	dev_data = devm_kzalloc(&pdev->dev,sizeof(*dev_data),GFP_KERNEL);
	if(!dev_data)
	{
		dev_info(dev,"Cannot allocate memory\n");
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
	pr_info("Config item 1 = %d\n",pcdev_config[driver_data].config_item1);
	pr_info("Config item 2 = %d\n",pcdev_config[driver_data].config_item2);


	//allocate mem for device private data's buffer
	dev_data->buffer = devm_kzalloc(&pdev->dev,dev_data->pdata.size,GFP_KERNEL);
	if(!dev_data->buffer)
	{
		dev_info(dev,"Cannot allocate memory\n");
		return -ENOMEM;
		
	}
	

	dev_data->dev_num = (pcdrv_data.device_num_base + pcdrv_data.total_devices);

	cdev_init(&dev_data->ch_dev,&ch_fops);

	dev_data->ch_dev.owner = THIS_MODULE;
	ret = cdev_add(&dev_data->ch_dev,dev_data->dev_num,1);
	if(ret < 0)
	{
		dev_err(dev,"Cdev add failed\n");
		return ret;
	}

	pcdrv_data.ch_device = device_create(pcdrv_data.class_ch,dev,dev_data->dev_num,NULL,"ch_device-%d",pcdrv_data.total_devices);
	if(IS_ERR(pcdrv_data.ch_device))
	{
		dev_err(dev,"Device creation failed\n");
		ret = PTR_ERR(pcdrv_data.ch_device);
		cdev_del(&dev_data->ch_dev);
		return ret;
	}

	pcdrv_data.total_devices++;

	ret = pcd_sysfs_create_files(pcdrv_data.ch_device);
	if(ret)
	{
		device_destroy(pcdrv_data.class_ch,dev_data->dev_num);
		return ret;
	}

	dev_info(dev,"The probe was succussful\n");
    return 0;
}


/*called when the device is removed from the system*/
int pcd_platform_driver_remove(struct platform_device *pdev)
{
	struct ch_dev_private_data *dev_data = dev_get_drvdata(&pdev->dev);
	
	device_destroy(pcdrv_data.class_ch,dev_data->dev_num);

	cdev_del(&dev_data->ch_dev);


	pcdrv_data.total_devices--;

	dev_info(&pdev->dev,"A device is removed\n");
    return 0;
}




struct platform_driver pcd_platform_driver = {
    .probe = pcd_platform_driver_probe,
    .remove = pcd_platform_driver_remove,
	.id_table = pcdevs_ids,
    .driver = {
        .name = "pseudo-char-device",
		.of_match_table = of_match_ptr(org_pcdev_dt_match),
    }

};



static int __init pcd_platform_driver_in(void)
{

	int ret;

	ret = alloc_chrdev_region(&pcdrv_data.device_num_base,0,NO_OF_DEVICES,"chr_devices");
	if(ret < 0)
	{
		pr_err("Alloc chrdev failed\n");
		pr_info("%s : Module insertion failed\n",__func__);
		return ret;
	}

	pcdrv_data.class_ch = class_create(THIS_MODULE,"ch_class");
	if(IS_ERR(pcdrv_data.class_ch))
	{
		pr_err("Class creation failed\n");
		ret = PTR_ERR(pcdrv_data.class_ch);
		unregister_chrdev_region(pcdrv_data.device_num_base,NO_OF_DEVICES);
		pr_info("%s : Module insertion failed\n",__func__);
		return ret;
	}

    platform_driver_register(&pcd_platform_driver);
    pr_info("pcd platform driver loaded\n");

	return 0;

}

static void __exit pcd_platform_driver_ex(void)
{

    platform_driver_unregister(&pcd_platform_driver);
    //pr_info("pcd platform driver unloaded\n");


	class_destroy(pcdrv_data.class_ch);

	unregister_chrdev_region(pcdrv_data.device_num_base,NO_OF_DEVICES);

	pr_info("module unloaded\n");

}

module_init(pcd_platform_driver_in);
module_exit(pcd_platform_driver_ex);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("manohar");
MODULE_DESCRIPTION("character device driver for multiple devices");
