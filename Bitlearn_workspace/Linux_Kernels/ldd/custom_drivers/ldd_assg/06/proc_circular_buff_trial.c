#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include<linux/types.h>
#include<linux/slab.h>


MODULE_LICENSE("GPL");

static struct proc_dir_entry *proc_entry;

static struct kring_buffer {
    char *log_messages[11];
    size_t size;
    unsigned int head;
    unsigned int tail;
}krb;

int log_open(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}   
ssize_t log_read(struct file *pfile, char __user *buff, size_t len, loff_t *poff)
{
    int ret,index=0;
    char *kbuff[10]={0};char messages[100];


    if(len > sizeof(messages))
        len = sizeof(messages)-1;

    while((kbuff[index] = pop()) != NULL)
    {
        index++;
    }

    ret = snprintf(messages,sizeof(messages),"Reading:\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n"
            ,kbuff[0],kbuff[1],kbuff[2],kbuff[3],kbuff[4],kbuff[5],kbuff[6],kbuff[7],
            kbuff[8],kbuff[9]);

    if(ret < 0)
    {
        pr_info("snprintf failed\n");
        return -EFAULT;
    }

    if(copy_to_user(buff,messages,ret))
    {
        pr_info("copy to user failed\n");
        return -EFAULT;
    }

    *poff += ret;

    
    return ret;
}
ssize_t log_write(struct file *pfile, const char __user *buff, size_t len, loff_t *poff)
{
    char kbuff[10];
    pr_info("%s : called\n",__func__);

    if(len >= sizeof(kbuff))
        len = sizeof(kbuff);
   
    if(copy_from_user(kbuff,buff,len))
    {
        pr_info("copy form user failed\n");
        return -EFAULT;
    }

    char *msg = kzalloc(len,GFP_KERNEL);

    strcpy(msg,kbuff);

    push(msg);

    *poff += len;

    return len;
}

int log_release(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}

static void init_kringbuffer()
{
    krb.head = krb.tail = 0;
    krb.size = 11;
}

static int is_empty()
{
    if(krb.head == krb.tail)
    {
        pr_warn("Buffer is empthy\n");
        return 1;
    }
    return 0;
}

static int is_full(int next)
{
    if(krb.tail == next)
    {
        pr_warn("Buffer is full\n");
        return 1;
    }
    return 0;
}


static void push(int d)
{
    int next;
    next = krb.head +1;

    if(next >= krb.size)
        next = 0;

    if(!is_full(next))
    {
        krb.log_messages[krb.head] = d;
        krb.head = next;
    }

}

static int pop()
{
    int next;int d;

    if(is_empty())
    {
        return -1;
    }

    next = krb.tail +1;

    if(next >= krb.size)
        next =0;

    d = krb.log_messages[krb.tail];
    krb.tail = next;

    return d;
}


static struct proc_ops proc_fops = {
    .proc_open = log_open,
    .proc_read = log_read,
    .proc_write = log_write,
    .proc_release = log_release,

};


static int __init proc_init(void)
{
    pr_info("%s : init\n",__func__);

    proc_entry = proc_create("log", 
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