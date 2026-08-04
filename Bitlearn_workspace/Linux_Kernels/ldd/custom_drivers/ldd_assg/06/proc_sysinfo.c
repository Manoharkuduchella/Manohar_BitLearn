#include<linux/module.h>
#include<linux/init.h>
#include <linux/errno.h>
#include<linux/utsname.h>

MODULE_LICENSE("GPL");


static int __init process_init(void)
{
    pr_info("%s : init\n",__func__);
    pr_info("%s : Hostname = %s\n",__func__,init_uts_ns.name.nodename);
    pr_info("%s : Kernel Version = %s\n",__func__,init_uts_ns.name.release);
    pr_info("%s : init_uts_ns.name.version = %s\n",__func__,init_uts_ns.name.version);
    pr_info("%s : CPU Architecture = %s\n",__func__,init_uts_ns.name.machine);
    pr_info("%s : PAGE_SIZE = %lu\n",__func__,(unsigned long)PAGE_SIZE);

    return 0;
}

static void __exit process_exit(void)
{
    pr_info("%s : exit\n",__func__);

}


module_init(process_init);
module_exit(process_exit);