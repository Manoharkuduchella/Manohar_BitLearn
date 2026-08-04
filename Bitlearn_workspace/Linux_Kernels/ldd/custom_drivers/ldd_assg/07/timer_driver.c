/*Assignment 12: Timer Driver
Tasks:
Create a periodic timer.
Print a message every 3 seconds.
Stop the timer on module removal.
Learn:
timer_setup()
mod_timer()*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

#define TIME_OUT 3000

MODULE_LICENSE("GPL");

static struct timer_list tm;

static void timer_callback(struct timer_list *tm)
{
    pr_info("%s : Timer expired\n",__func__);
    mod_timer(tm,(jiffies + msecs_to_jiffies(TIME_OUT)));
}

static int __init timer_init(void)
{
    pr_info("%s : called\n",__func__);

    timer_setup(&tm,timer_callback,0);

    mod_timer(&tm,(jiffies + msecs_to_jiffies(TIME_OUT)));

    return 0;
}

static void __exit timer_exit(void)
{
    pr_info("%s : called\n",__func__);
    del_timer_sync(&tm);
}

module_init(timer_init);
module_exit(timer_exit);