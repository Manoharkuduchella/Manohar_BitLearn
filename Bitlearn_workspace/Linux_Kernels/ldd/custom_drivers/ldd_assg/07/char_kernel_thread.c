#include<linux/module.h>
#include<linux/init.h>
#include<linux/kthread.h>
#include<linux/timekeeping.h>
#include<linux/delay.h>


MODULE_LICENSE("GPL");

struct task_struct *kthread;

int thread_handler(void *data)
{
    struct timespec64 ts;

    while(!kthread_should_stop())
    {
        ktime_get_real_ts64(&ts);

        pr_info("Current Time: %lld.%09ld\n",(long long)ts.tv_sec,ts.tv_nsec);

        ssleep(5);
    }

    pr_info("Thread stopped\n");

    return 0;
}

static int __init thread_init(void)
{
    pr_info("%s : called\n",__func__);
    kthread = kthread_run(thread_handler,NULL,"kernel thread");
    if(IS_ERR(kthread))
    {
        pr_err("Failed to create kernel thread\n");
        return PTR_ERR(kthread);
    }
    return 0;
}

static void __exit thread_exit(void)
{
    if(kthread)
        kthread_stop(kthread);
    pr_info("%s : kthread stopped\n");
}

module_init(thread_init);
module_exit(thread_exit);