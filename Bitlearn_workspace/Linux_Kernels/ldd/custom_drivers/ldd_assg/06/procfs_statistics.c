#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include<linux/types.h>

MODULE_LICENSE("GPL");

struct proc_dir_entry *proc_file;

static uint32_t read_cnt;
static uint32_t write_cnt;

int statistics_open(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}   
ssize_t statistics_read(struct file *pfile, char __user *buff, size_t len, loff_t *poff)
{
    char rwcnt[30];int ret;

    pr_info("%s : called\n",__func__);

    if (*poff != 0)
    return 0;

    read_cnt++;

    if(len > sizeof(rwcnt))
        len = sizeof(rwcnt);

    ret = snprintf(rwcnt,sizeof(rwcnt),"Reads : %u\nWrites : %u\n",read_cnt,write_cnt);
    
    if(copy_to_user(buff, rwcnt, ret))
    {
        pr_err("copy to user failed\n");
        return -EFAULT;
    }

    *poff += ret;

    return ret;
}
ssize_t statistics_write(struct file *pfile, const char __user *buff, size_t len, loff_t *poff)
{

    pr_info("%s : called\n",__func__);

    write_cnt++;

    return len;
}

int statistics_release(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}



static struct proc_ops proc_statistics_fops = {
    .proc_open = statistics_open,
    .proc_read = statistics_read,
    .proc_write = statistics_write,
    .proc_release = statistics_release,

};


static int __init proc_init(void)
{
    pr_info("%s : init\n",__func__);

    proc_file = proc_create("statistics", 
                0666, 
                NULL, 
                &proc_statistics_fops);

    return 0;
}

static void __exit proc_exit(void)
{
    proc_remove(proc_file);
    pr_info("%s : exit\n",__func__);

}


module_init(proc_init);
module_exit(proc_exit);