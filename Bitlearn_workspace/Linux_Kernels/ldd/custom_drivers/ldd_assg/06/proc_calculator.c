
#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include<linux/types.h>
#include<linux/string.h>

MODULE_LICENSE("GPL");

struct proc_dir_entry *pproc_dir;
unsigned int sum;

int calculator_open(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}   
ssize_t calculator_read(struct file *pfile, char __user *buff, size_t len, loff_t *poff)
{
    char kbuf[32];int ret;
    pr_info("%s : called\n",__func__);

    if(*poff)
        return 0;

    ret = snprintf(kbuf,sizeof(kbuf),"Sum = %d\n",sum);
 
    if(copy_to_user(buff,kbuf,ret))
    {
        return -EFAULT;
    }

    *poff += ret;

    return ret;
}
ssize_t calculator_write(struct file *pfile, const char __user *buff, size_t len, loff_t *poff)
{
    char *tok,*ptr;
    int num1,num2;
    char cal_buff[32];

    pr_info("%s : called\n",__func__);

    if (len >= sizeof(cal_buff))
    len = sizeof(cal_buff) - 1;


    if(copy_from_user(cal_buff,buff,len))
    {
        return -EFAULT;
    }
    cal_buff[len] = 0;

    ptr = cal_buff;

    /*num1*/
    tok = strsep(&ptr," ");
    if(!tok)
    {
        return -EINVAL;
    }
    kstrtoint(tok,10,&num1);

    /*num2*/
    tok = strsep(&ptr," ");
    if(!tok)
    {
        return -EINVAL;
    }
    kstrtoint(tok,10,&num1);

    sum = num1 + num2;

    pr_info("Sum : %d\n",sum);

    return len;
}

int calculator_release(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}



static struct proc_ops proc_fops = {
    .proc_open = calculator_open,
    .proc_read = calculator_read,
    .proc_write = calculator_write,
    .proc_release = calculator_release,

};


static int __init proc_init(void)
{
    pr_info("%s : init\n",__func__);
    pproc_dir = proc_mkdir("k_app", NULL);
    if(!pproc_dir)
    {
        pr_info("failed to create proc_mkdir\n");
        return -1;
    }

    proc_create("calculator", 
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