#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/interrupt.h>
#include<linux/delay.h>


MODULE_LICENSE("GPL");

int cpu=2;
module_param(cpu, int ,0);

struct work_struct work;

static void work_fn(struct work_struct *work)
{
    pr_info("processor id: %d\t deferred work execution\n",smp_processor_id());

}


static int test_workq_init(void)
{
    pr_info("processor id:%d in init\n",smp_processor_id());
    INIT_WORK(&work, work_fn);
    //queue_work(system_wq,&work);
    queue_work_on(cpu,system_wq,&work);
    return 0;
}

static void test_workq_exit(void)
{
    pr_info("%s: In exit\n",__func__);
}

module_init(test_workq_init);
module_exit(test_workq_exit);