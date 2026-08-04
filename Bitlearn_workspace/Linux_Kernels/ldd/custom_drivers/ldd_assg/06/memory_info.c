#include<linux/module.h>
#include<linux/init.h>
#include<linux/sysinfo.h>
#include<linux/mm.h>

MODULE_LICENSE("GPL");


static int __init process_init(void)
{
    struct sysinfo sinfo;

    si_meminfo(&sinfo);

    pr_info("%s : init\n",__func__);
    pr_info("%s : Total RAM = %lu KB\n",__func__,(sinfo.totalram * sinfo.mem_unit) / 1024);
    pr_info("%s : Free RAM = %lu KB\n",__func__,(sinfo.freeram * sinfo.mem_unit) / 1024);
    pr_info("%s : Buffer Memory = %lu KB\n",__func__,(sinfo.bufferram * sinfo.mem_unit) / 1024);
    pr_info("%s : Shared Memory = %lu KB\n",__func__,(sinfo.sharedram * sinfo.mem_unit) / 1024);

    return 0;
}

static void __exit process_exit(void)
{
    pr_info("%s : exit\n",__func__);

}


module_init(process_init);
module_exit(process_exit);