#ifndef PCD_PLATFORM_DRIVER_DT_SYSFS_H
#define PCD_PLATFORM_DRIVER_DT_SYSFS_H

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/mod_devicetable.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/dev_printk.h>
#include <linux/sysfs.h>
#include "platform.h"


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


loff_t ch_lseek(struct file *filp, loff_t offset, int whence);
ssize_t ch_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos);

ssize_t ch_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos);
int check_permission(int dev_perm,int acc_mode);

int ch_open(struct inode *pinode, struct file *filp);
int ch_release(struct inode *pinode, struct file *filp);



#endif