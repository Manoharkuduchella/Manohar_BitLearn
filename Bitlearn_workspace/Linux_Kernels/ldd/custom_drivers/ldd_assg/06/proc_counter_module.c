#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include<linux/types.h>

MODULE_LICENSE("GPL");

struct proc_dir_entry *pproc_dir;
static uint32_t counter;

int dummy_open(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}   
ssize_t dummy_read(struct file *pfile, char __user *buff, size_t len, loff_t *poff)
{
    char cntbf[5];

    pr_info("%s : called\n",__func__);

    if (*poff != 0)
    return 0;

    counter++;

    if(len > sizeof(int))
        len = sizeof(int);

    snprintf(cntbf,sizeof(cntbf),"%d",counter);
    
    if(copy_to_user(buff, cntbf, strlen(cntbf)))
    {
        pr_err("copy to user failed\n");
        return -EFAULT;
    }

    *poff += len;

    return len;
}
ssize_t dummy_write(struct file *pfile, const char __user *buff, size_t len, loff_t *poff)
{

    pr_info("%s : called\n",__func__);

    return len;
}

int dummy_release(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}



static struct proc_ops proc_fops = {
    .proc_open = dummy_open,
    .proc_read = dummy_read,
    .proc_write = dummy_write,
    .proc_release = dummy_release,

};


static int __init proc_init(void)
{
    pr_info("%s : init\n",__func__);
    pproc_dir = proc_mkdir("dummy", NULL);
    if(!pproc_dir)
    {
        pr_info("failed to create proc_mkdir\n");
        return -1;
    }

    proc_create("counter", 
                0666, 
                pproc_dir, 
                &proc_fops);

    return 0;
}

static void __exit proc_exit(void)
{
    proc_remove(pproc_dir);
    pr_info("%s : exit\n",__func__);

}


module_init(proc_init);
module_exit(proc_exit);