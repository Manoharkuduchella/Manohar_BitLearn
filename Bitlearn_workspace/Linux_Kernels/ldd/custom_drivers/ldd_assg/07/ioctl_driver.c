/*Assignment 6: IOCTL Driver
Tasks:
Add custom IOCTL commands:
Reset buffer
Get driver version
Set LED status (dummy)
Write a user-space application using:
ioctl()*/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/errno.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include "ioctl_cmd.h"

#define DRIVER_VERSION "0.15"

MODULE_LICENSE("GPL");

dev_t device_number;

struct cdev ch_dev;

struct class *ch_class;
struct device *ch_device;

char kbuffer[20];
char led_status[10] = "OFF\n";

int char_open(struct inode *pionode,struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}

ssize_t char_read(struct file *pfile,char __user *buff,size_t count, loff_t *poff)
{
    pr_info("%s : called\n",__func__);

    if(*poff != 0)
        return 0;

    if(count > sizeof(kbuffer))
        count = sizeof(kbuffer)-1;

    if(copy_to_user(buff,kbuffer,count))
    {
        pr_info("failed to copy to user\n");
        return -EFAULT;
    }

    
    *poff += count;

    return count;
}

ssize_t char_write(struct file *pfile,const char __user *buff, size_t count, loff_t *poff)
{
    pr_info("%s : called\n",__func__);

    if(*poff != 0)
        return 0;

    if(count > sizeof(kbuffer))
        count = sizeof(kbuffer)-1;

    if(copy_from_user(kbuffer,buff,count))
    {
        pr_info("failed to copy from user\n");
        return -EFAULT;
    }

    kbuffer[count] = '\0';

    *poff += count;

    return count;
}

int char_release(struct inode *pinode,struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}

long char_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg)
{
    pr_info("%s : called\n",__func__);

    switch(cmd)
    {
        case RESET_BUFFER:
            memset(kbuffer,0,sizeof(kbuffer));
            pr_info("Done Buffer reset\n");break;

        case GET_DRIVER_VERSION:
            if(copy_to_user((char __user *)arg,DRIVER_VERSION,strlen(DRIVER_VERSION)+1))
            {
                pr_err("failed to get driver version\n");
                return -EFAULT;
            }
            break;

        case SET_LED_STATUS:
            if(copy_from_user(led_status,(char __user *)arg,sizeof(led_status)))
            {
                pr_err("failed to set led status\n");
                return-EFAULT;
            }
            pr_info("LED status: %s\n",led_status);
            break;


        default: pr_err("Ivalid IOCTL cmd\n");return -EINVAL;


    }

    return 0;

}

static struct file_operations ch_fops = {
    .read = char_read,
    .write = char_write,
    .open = char_open,
    .release = char_release,
    .unlocked_ioctl = char_ioctl,
    .owner = THIS_MODULE
};



static int __init chr_driver_init(void)
{
    int ret;
    pr_info("%s : called\n",__func__);

    if(alloc_chrdev_region(&device_number,0,1,"chr_device"))
    {
        pr_info("alloc chrdev failed\n");
        return -EFAULT;

    }

    pr_info("Major = %d Minor = %d\n",MAJOR(device_number),MINOR(device_number));

    ch_dev.owner = THIS_MODULE;
    cdev_init(&ch_dev,&ch_fops);

    ret = cdev_add(&ch_dev,device_number,1);
    if(ret < 0)
        pr_info("cdev add failed\n");

    ch_class = class_create(THIS_MODULE,"chr_device");
    if(IS_ERR(ch_class))
    {
        pr_info("class cretion failed\n");
        return -EFAULT;
    }


    ch_device = device_create(ch_class,NULL,device_number,NULL,"mychar");
    if(IS_ERR(ch_device))
    {
        pr_info("device creation failed\n");
        return -EFAULT;
    }


    return 0;
}

static void __exit chr_driver_exit(void)
{
    device_destroy(ch_class,device_number);

    class_destroy(ch_class);

    cdev_del(&ch_dev);

    unregister_chrdev_region(device_number,1);
    pr_info("%s : called\n",__func__);

}

module_init(chr_driver_init);
module_exit(chr_driver_exit);