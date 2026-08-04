#include<linux/module.h>
#include<linux/init.h>
#include <linux/errno.h>
#include<linux/sched.h>

MODULE_LICENSE("GPL");


static int __init process_init(void)
{
    pr_info("%s : init\n",__func__);
    pr_info("%s : current->pid = %d\n",__func__,current->pid);
    pr_info("%s : current->comm = %s\n",__func__,current->comm);
    pr_info("%s : current->real_parent = %lu\n",__func__,current->real_parent);
    pr_info("%s : current->state = %d\n",__func__,current->state);
    pr_info("%s : current->on_cpu = %d\n",__func__,current->on_cpu);

    return 0;
}

static void __exit process_exit(void)
{
    pr_info("%s : exit\n",__func__);

}


module_init(process_init);
module_exit(process_exit);