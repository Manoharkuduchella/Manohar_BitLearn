
/*2. Top Half and Bottom Half 
Objective
Simulate an interrupt.
 
Top Half
 
Timer expires
 
↓
 
Interrupt Handler
 
↓
 
Schedule Tasklet
 
↓
 
Tasklet Executes
 
Requirements
Timer acts as interrupt.
Interrupt handler prints*/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/timer.h>
#include<linux/jiffies.h>
#include<linux/interrupt.h>

MODULE_LICENSE("GPL");

#define TIMEOUT 1000
unsigned int counter;

void mytim_handler(struct timer_list *tim);
void mytasklet_handler(struct tasklet_struct *tsklt);

DEFINE_TIMER(mytim, mytim_handler);
DECLARE_TASKLET(mytasklet, mytasklet_handler);

void mytasklet_handler(struct tasklet_struct *tsklt)
{
    pr_info("In tasklet..\n");
}

void mytim_handler(struct timer_list *tim)
{
    counter++;
    pr_info("Interrupt No : %d\n",counter);
    tasklet_schedule(&mytasklet);
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