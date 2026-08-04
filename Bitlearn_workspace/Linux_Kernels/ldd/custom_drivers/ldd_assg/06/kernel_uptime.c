#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include<linux/types.h>
#include<linux/jiffies.h>

MODULE_LICENSE("GPL");

static struct proc_dir_entry *proc_entry;

int uptime_open(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}   
ssize_t uptime_read(struct file *pfile, char __user *buff, size_t len, loff_t *poff)
{
    int ret;
    char kbuff[64];
    unsigned long int uptime;

    if(*poff > 0)
        return 0;

    pr_info("%s : called\n",__func__);

    uptime = (jiffies/HZ);

    ret = snprintf(kbuff,sizeof(kbuff),"Kernel Uptime : %lu seconds\n",uptime);

    if(copy_to_user(buff,kbuff,ret))
    {
        return -EFAULT;
    }

    *poff += ret;
    

    return ret;
}
ssize_t uptime_write(struct file *pfile, const char __user *buff, size_t len, loff_t *poff)
{

    pr_info("%s : called\n",__func__);

    return len;
}

int uptime_release(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}



static struct proc_ops proc_fops = {
    .proc_open = uptime_open,
    .proc_read = uptime_read,
    .proc_write = uptime_write,
    .proc_release = uptime_release,

};


static int __init proc_init(void)
{
    pr_info("%s : init\n",__func__);

    proc_entry = proc_create("uptime_test", 
                0666, 
                NULL, 
                &proc_fops);

    return 0;
}

static void __exit proc_exit(void)
{
    proc_remove(proc_entry);
    pr_info("%s : exit\n",__func__);

}


module_init(proc_init);
module_exit(proc_exit);