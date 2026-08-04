#include<linux/module.h>
#include<linux/init.h>
#include<linux/sysfs.h>
#include<linux/kobject.h>


MODULE_LICENSE("GPL");

struct kobject *mykobj;

int cnt = 50;
const char *nm = "mydriver";
const char *ver = "5.0";

ssize_t show_count(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    return sysfs_emit(buf,"%d",cnt);
}

ssize_t store_count(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    pr_info("%s : called\n",__func__);

    return count;
}   

ssize_t show_version(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    return sysfs_emit(buf,"%s",ver);
}

ssize_t store_version(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    pr_info("%s : called\n",__func__);

    return count;
}


ssize_t show_name(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    return sysfs_emit(buf,"%s",nm);
}

ssize_t store_name(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
   pr_info("%s : called\n",__func__);

    return count;
}





const struct kobj_attribute name_attr = __ATTR(name,0644,show_name,store_name);
const struct kobj_attribute version_attr = __ATTR(version,0644,show_version,store_version);
const struct kobj_attribute count_attr = __ATTR(count,0644,show_count,store_count);


struct attribute *kobj_attr[] = {
    &name_attr.attr,
    &version_attr.attr,
    &count_attr.attr,
    NULL
};

const struct attribute_group kobj_attr_grp = {
    .attrs = kobj_attr,
};


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

    ret = sysfs_create_group(mykobj,&kobj_attr_grp);
    if(IS_ERR(ret))
    {
        pr_info("%s : sysfs create failed\n",__func__);
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