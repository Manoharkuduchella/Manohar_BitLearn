/*Objective:
Accept PID from user and display process details.

Input:
echo 1234 > /proc/pidinfo

Output:
PID
Name
Parent PID
State*/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include<linux/types.h>
#include <linux/pid.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");

static struct proc_dir_entry *proc_entry;

static pid_t pid;

struct task_struct *task;

char kbuf[200];

int pid_open(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}   
ssize_t pid_read(struct file *pfile, char __user *buff, size_t len, loff_t *poff)
{
    int ret;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if(!task)
        return -ESRCH;

    ret = snprintf(kbuf,sizeof(kbuf), "PID : %d\nName : %s\nParent PID : %d\nState : %ld\n",
                    task->pid,
                    task->comm,
                    task->real_parent->pid,
                    task->state);

    if (copy_to_user(buff, kbuf, ret))
    return -EFAULT;

    *poff = ret;
    return ret;

}
ssize_t pid_write(struct file *pfile, const char __user *buff, size_t len, loff_t *poff)
{
    int ret;

    if (len >= sizeof(kbuf))
        len = sizeof(kbuf) - 1;

    if (copy_from_user(kbuf, buff, len))
        return -EFAULT;

    kbuf[len] = '\0';

    ret = kstrtoint(kbuf, 10, &pid);
    if (ret)
        return ret;

    return len;
}

int pid_release(struct inode *pinode, struct file *pfile)
{
    pr_info("%s : called\n",__func__);
    return 0;
}



static struct proc_ops proc_fops = {
    .proc_open = pid_open,
    .proc_read = pid_read,
    .proc_write = pid_write,
    .proc_release = pid_release,

};


static int __init proc_init(void)
{
    pr_info("%s : init\n",__func__);

    proc_entry = proc_create("pid_info", 
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