/*Assignment 1: Character Device Driver
Objective: Create your first character driver.
Tasks:
Register a character device.
Create /dev/mychar.
Implement:
open()
release()
read()
write()
Test:
echo "Hello" > /dev/mychar
cat /dev/mychar*/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/errno.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/list.h>
#include<linux/slab.h>

MODULE_LICENSE("GPL");

#define MAX_SIZE 100


dev_t device_number;

struct cdev ch_dev;

struct class *ch_class;
struct device *ch_device;



struct char_data
{
    char data[MAX_SIZE];
    struct list_head list;
};

LIST_HEAD(chr_list);

int char_open(struct inode *pionode,struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}

ssize_t char_read(struct file *pfile,char __user *buff,size_t count, loff_t *poff)
{
    struct char_data *node;
    char kbuf[1024];
    int pos =0;

    pr_info("%s : called\n",__func__);

    if(*poff != 0)
        return 0;

    list_for_each_entry(node, &chr_list, list)
    {
        pos += snprintf(kbuf+pos, sizeof(kbuf) - pos, "%s\n",node->data);
    }

    if(copy_to_user(buff,kbuf,pos))
    {
        pr_info("failed to copy to user\n");
        return -EFAULT;
    }

    
    *poff = pos;

    return pos;
}

ssize_t char_write(struct file *pfile,const char __user *buff, size_t count, loff_t *poff)
{
    struct char_data *new;
    pr_info("%s : called\n",__func__);

    if(count >= MAX_SIZE)
        count = MAX_SIZE-1;

    new = kzalloc(sizeof(struct char_data),GFP_KERNEL);
    if(!new)
        return -ENOMEM;

    if(copy_from_user(new->data,buff,count))
    {
        kfree(new);
        return -EFAULT;
    }

    new->data[count] = '\0';

    if (new->data[count - 1] == '\n')
        new->data[count - 1] = '\0';

    *poff += count;

    INIT_LIST_HEAD(&new->list);

    list_add_tail(&new->list,&chr_list);

    return count;
}

int char_release(struct inode *pinode,struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}


static struct file_operations ch_fops = {
    .read = char_read,
    .write = char_write,
    .open = char_open,
    .release = char_release,
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
    struct  char_data *node;
    struct char_data *tmp;

    list_for_each_entry_safe(node, tmp, &chr_list, list)
    {
        list_del(&node->list);
        kfree(node);
    }
    

    device_destroy(ch_class,device_number);

    class_destroy(ch_class);

    cdev_del(&ch_dev);

    unregister_chrdev_region(device_number,1);
    pr_info("%s : called\n",__func__);

}

module_init(chr_driver_init);
module_exit(chr_driver_exit);