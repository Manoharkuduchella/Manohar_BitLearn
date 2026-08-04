#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>
#include<linux/moduleparam.h>

#define SHARED_IRQ 27

MODULE_LICENSE("GPL");

static unsigned int irq = SHARED_IRQ, device_id, irq_counter;

module_param(irq,int,0644);

static irqreturn_t irq_handler_func(int irq, void *dev_id)
{
    irq_counter++;
    pr_info("IRQ : %d and irq_counter : %d\n",irq,irq_counter);
    return IRQ_NONE;
}

static int __init share_irq_init(void)
{
    pr_info("%s : called\n",__func__);

    if(request_irq(irq,irq_handler_func,IRQF_SHARED,"dummy_irq",&device_id))
    {
        pr_info("failed to reserve irq %d\n",irq);
        return -1;
    }

    return 0;
}

static void __exit share_irq_exit(void)
{
    pr_info("%s : called\n",__func__);
    synchronize_irq(irq);
    free_irq(irq,&device_id);
    pr_info("Successfully unloading, irq_counter = %d\n",irq_counter);
}

module_init(share_irq_init);
module_exit(share_irq_exit);