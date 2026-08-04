#include<linux/module.h>
#include<linux/init.h>
#include<linux/sysfs.h>
#include<linux/kobject.h>


MODULE_LICENSE("GPL");

struct kobject *mykobj;
static int val=0;

ssize_t show_value(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    return sysfs_emit(buf,"%d",val);
}

ssize_t store_value(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    int ret;
    ret = kstrtoint(buf,10,&val);
    if(ret < 0)
    {
        pr_info("kstrint failed\n");
        return ret;
    }

    return count;
}                 


const struct kobj_attribute value_attr = __ATTR(value,0644,show_value,store_value);


static int __init sys_attri_init(void)
{
    int ret;
    pr_info("%s : called\n",__func__);

    mykobj = kobject_create_and_add("kobj_driver",kernel_kobj);
    if(IS_ERR(mykobj))
    {
        pr_info("%s : kobject creation failed\n",__func__);
        return -1;
    }

    ret = sysfs_create_file(mykobj,&value_attr.attr);
    if(IS_ERR(ret))
    {
        pr_info("%s : sysfs create fail\n",__func__);
        kobject_put(mykobj);
        return -1;
    }

    return 0;
}

static void __exit sys_attri_exit(void)
{
    kobject_put(mykobj);
    pr_info("%s : called\n",__func__);
}


module_init(sys_attri_init);
module_exit(sys_attri_exit);