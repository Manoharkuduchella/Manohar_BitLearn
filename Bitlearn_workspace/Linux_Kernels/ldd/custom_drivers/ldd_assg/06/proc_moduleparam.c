#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include<linux/types.h>
#include<linux/jiffies.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");

int count;
static struct proc_dir_entry *proc_entry;

module_param(count,int,0644);
MODULE_PARM_DESC(count, "A count param for proc");

int cnt_open(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}   
ssize_t cnt_read(struct file *pfile, char __user *buff, size_t len, loff_t *poff)
{
    int ret;
    char kbuff[15];

    ret = snprintf(kbuff,sizeof(kbuff),"Count = %d\n",count);

    if(copy_to_user(buff,kbuff,ret))
    {
        return -EFAULT;
    }

    *poff += ret;
    

    return ret;
}
ssize_t cnt_write(struct file *pfile, const char __user *buff, size_t len, loff_t *poff)
{

    pr_info("%s : called\n",__func__);

    return len;
}

int cnt_release(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}



static struct proc_ops proc_fops = {
    .proc_open = cnt_open,
    .proc_read = cnt_read,
    .proc_write = cnt_write,
    .proc_release = cnt_release,

};


static int __init proc_init(void)
{
    pr_info("%s : init\n",__func__);

    proc_entry = proc_create("hello", 
                0666, 
                NULL, 
                &proc_fops);

    return 0;
}

static void __exit proc_exit(void)
{
    proc_remove(NULL);
    pr_info("%s : exit\n",__func__);

}


module_init(proc_init);
module_exit(proc_exit);