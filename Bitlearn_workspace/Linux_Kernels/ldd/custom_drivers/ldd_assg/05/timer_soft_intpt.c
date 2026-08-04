
/*1. Software Interrupt Counter 
Objective
Create a Linux kernel module that counts software interrupts using a timer.
Requirements
Create a kernel timer.
Trigger every 1 second.
Increment an interrupt counter and print
Interrupt No : 1
Interrupt No : 2
Interrupt No : 3 ...*/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/timer.h>
#include<linux/jiffies.h>

MODULE_LICENSE("GPL");

#define TIMEOUT 1000
unsigned int counter;

void mytim_handler(struct timer_list *tim);

DEFINE_TIMER(mytim, mytim_handler);

void mytim_handler(struct timer_list *tim)
{
    counter++;
    pr_info("Interrupt No : [%d]\n",counter);
    mod_timer(tim,jiffies + msecs_to_jiffies(TIMEOUT));

}


static int __init timer_int_init(void)
{
    pr_info("timer init\n");
    mod_timer(&mytim,jiffies + msecs_to_jiffies(TIMEOUT));

    return 0;
    
}

static void __exit timer_int_exit(void)
{
    del_timer_sync(&mytim);
    pr_info("timer exit\n");
}

module_init(timer_int_init);
module_exit(timer_int_exit);