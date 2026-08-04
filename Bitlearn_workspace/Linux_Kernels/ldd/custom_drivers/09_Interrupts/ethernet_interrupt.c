#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>

#define SHARED_IRQ 19  /*irq for ethernet*/

MODULE_LICENSE("GPL");

static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;

module_param(irq, int, S_IRUGO);


static irqreturn_t eth_interrupt(int irq, void *dev_id)
{
	irq_counter++;
	pr_info("In the ISR: counter = %d\n",irq_counter);
	return IRQ_NONE;
}

static int __init ethnt_Irq_init(void)
{
	if(request_irq(irq,eth_interrupt,IRQF_SHARED,"eth_interrupt",&my_dev_id))
	{
		pr_info("failed to reserve irq %d\n",irq);
		return -1;
	}
	pr_info("Successfully loading ISR handler\n");

	return 0;
}

static void __exit ethnt_Irq_exit(void)
{
	synchronize_irq(irq);//to provide atomicity for the irq
	free_irq(irq,&my_dev_id);//unregister the irq handler 

	pr_info("Successfully unloading, irq counter = %d\n",irq_counter);
}

module_init(ethnt_Irq_init);
module_exit(ethnt_Irq_exit);
