#include<linux/init.h>
#include<linux/module.h>
#include<linux/spinlock.h>
#include<linux/kthread.h>
#include<linux/delay.h>
#include<linux/slab.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Spinlock implementation module");

unsigned int counter;
struct task_struct *reader,*writer;

//DEFINE_SPINLOCK(my_lock);//statically initializing the spinlock

spinlock_t *my_lock;

int reader_fun(void *data)
{
    pr_info("reader_fun is called\n");
    spin_lock(my_lock);
    pr_info("%s : read counter-> %d\n",__func__,counter);
    spin_unlock(my_lock);
    msleep(5);

    return 0;
}

int writer_fun(void *data)
{
    pr_info("writer_fun is called\n");
    spin_lock(my_lock);
    counter++;
    pr_info("%s : written counter-> %d\n",__func__,counter);
    spin_unlock(my_lock);

    return 0;
}


static int __init spin_in(void)
{
    /*for static spinlock*/
    // pr_info("%s : called\n",__func__);
    // spin_lock(&my_lock);
    // pr_info("critical section in spinlock\n");
    // spin_unlock(&my_lock);

    reader = kthread_run(reader_fun,NULL,"reader_function");
    writer = kthread_run(writer_fun,NULL,"writer_function");

    /*for dynamic spinlock*/

    my_lock = kzalloc(sizeof(spinlock_t),GFP_KERNEL);
    if(!my_lock)
        return -ENOMEM;

    spin_lock_init(my_lock);

    return 0;
}

static void __exit spin_ex(void)
{
    pr_info("%s : called\n",__func__);
    pr_info("stopping the reader and writer threads\n");
}

module_init(spin_in);
module_exit(spin_ex);