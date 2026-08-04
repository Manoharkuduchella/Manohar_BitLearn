#include<linux/module.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");

dev_t device_number;

struct cdev ch_dev;

struct class *ch_class;

struct device *ch_device;

int ch_open(struct inode *pinode,struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}

int ch_release(struct inode *pinode,struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}

ssize_t ch_read(struct file *pfile, char __user *buff, size_t len, loff_t *poff) 
{
    pr_info("%s : called\n",__func__);
    return len;
}

ssize_t ch_write(struct file *pfile, const char __user *buff, size_t len,loff_t *poff)
{
    pr_info("%s : called\n",__func__);
    return len;
}

struct file_operations ch_fops = {
    .open = ch_open,
    .read = ch_read,
    .write = ch_write,
    .release = ch_release,
    .owner = THIS_MODULE
};


static int __init ch_drv_init(void)
{
    int ret;
    pr_info("%s : called\n",__func__);

    ret = alloc_chrdev_region(&device_number,0,1,"ch_device");
    if(ret < 0)
    {
        pr_info("alloc chrdev failed\n");
        return -EFAULT;
    }

    cdev_init(&ch_dev,&ch_fops);

    ch_dev.owner = THIS_MODULE;
    ret = cdev_add(&ch_dev,device_number,1);
    if(ret < 0)
    {
        pr_info("cdev_add failed\n");
        return -EFAULT;
    }

    ch_class = class_create(THIS_MODULE,"ch_class");
    if(IS_ERR(ch_class))
    {
        pr_info("class creation failed\n");
        return -EFAULT;
    }

    ch_device = device_create(ch_class,NULL,device_number,NULL,"mychrdev");
    if(IS_ERR(ch_device))
    {
        pr_info("device creation failed\n");
        return -EFAULT;
    }




    return 0;
}

static void __exit ch_drv_exit(void)
{
    device_destroy(ch_class,device_number);
    class_destroy(ch_class);
    cdev_del(&ch_dev);
    unregister_chrdev_region(device_number,1);
    pr_info("%s : called\n",__func__);

}

module_init(ch_drv_init);
module_exit(ch_drv_exit);