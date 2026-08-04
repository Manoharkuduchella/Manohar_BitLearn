#include<linux/module.h>
#include<linux/init.h>
#include<linux/kthread.h>
#include<linux/delay.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

static struct task_struct *kthread1, *kthread2;

static int thread_handler1(void *data)
{
	int i=0;
	while(!kthread_should_stop())
	{
		pr_info("1 %d\n",i);
		usleep_range(1000000, 1000001);
		i++;
		if(i == 10)
			i=0;
	}
	return 0;
}

static int thread_handler2(void *data)
{
	int i=0;
	        while(!kthread_should_stop())
        {
                pr_info("2 %d\n",i);
                usleep_range(1000000, 1000001);
                i++;
                if(i == 10)
                        i=0;
        }
        return 0;
}


static int __init thread_in(void)
{
	kthread1 = kthread_create(thread_handler1, NULL,"kernel_thread1");
	kthread2 = kthread_create(thread_handler2, NULL,"kernel_thread2");
	wake_up_process(kthread1);
	wake_up_process(kthread2);

	return 0;
}

static void __exit thread_ex(void)
{
	kthread_stop(kthread1);
	kthread_stop(kthread2);
}


module_init(thread_in);
module_exit(thread_ex);
