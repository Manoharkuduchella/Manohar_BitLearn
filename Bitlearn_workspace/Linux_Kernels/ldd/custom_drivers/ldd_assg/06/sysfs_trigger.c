/*Objective:
Trigger actions from userspace.

Attribute:
trigger

Commands:

echo start > trigger

Kernel Log:
Operation Started

echo stop > trigger

Kernel Log:
Operation Stopped*/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/sysfs.h>
#include<linux/kobject.h>


MODULE_LICENSE("GPL");

struct kobject *mykobj;

const char *start_cmd = "Operation Started\n";
const char *stop_cmd = "Operation Stopped\n";

ssize_t show_trigger(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    pr_info("%s : called\n",__func__);
    return 0;
}

ssize_t store_trigger(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    if(sysfs_streq(buf,"start"))
    {
        pr_info("Operation Started\n");
    }
    else if(sysfs_streq(buf,"stop"))
    {
        pr_info("Operation Stopped\n");
    }
    else{
        pr_err("%s : Invalid command\n",__func__);
        return -EINVAL;
    }
        
    return count;
}                 


const struct kobj_attribute trigger_attr = __ATTR(trigger,0644,show_trigger,store_trigger);


static int __init sys_attri_init(void)
{
    int ret;
    pr_info("%s : called\n",__func__);

    mykobj = kobject_create_and_add("ktrigger",kernel_kobj);
    if(!mykobj)
    {
        pr_info("%s : kobject creation failed\n",__func__);
        return -1;
    }

    ret = sysfs_create_file(mykobj,&trigger_attr.attr);
    if(ret)
    {
        pr_info("%s : sysfs create fail\n",__func__);
        kobject_put(mykobj);
        return -1;
    }

    return 0;
}

static void __exit sys_attri_exit(void)
{
    sysfs_remove_file(mykobj,&trigger_attr.attr);
    kobject_put(mykobj);
    pr_info("%s : called\n",__func__);
}


module_init(sys_attri_init);
module_exit(sys_attri_exit);