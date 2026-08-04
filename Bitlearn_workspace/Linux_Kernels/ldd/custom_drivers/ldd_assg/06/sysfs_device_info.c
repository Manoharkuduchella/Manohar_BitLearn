/*Objective:
Create driver information entries.

Create:
/sys/kernel/device/

Attributes:
- temperature
- voltage
- status

Expected Output:
Temperature : 35 C
Voltage : 3.3 V
Status : Running*/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/sysfs.h>
#include<linux/kobject.h>

MODULE_LICENSE("GPL");

struct kobject *mykobj;

const char *Temparature = "35 C\n";
const char *Voltage = "3.3 V\n";
const char *status = "Running\n";

ssize_t show_temperature(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    return sysfs_emit(buf,"%s",Temparature);
}

ssize_t store_temperature(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    pr_info("%s : called\n",__func__);

    return count;
} 


ssize_t show_voltage(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    return sysfs_emit(buf,"%s",Voltage);
}

ssize_t store_voltage(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    pr_info("%s : called\n",__func__);

    return count;
} 


ssize_t show_status(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    return sysfs_emit(buf,"%s",status);
}

ssize_t store_status(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    pr_info("%s : called\n",__func__);

    return count;
} 



const struct kobj_attribute temparature_attr = __ATTR(temperature,0444,show_temperature,store_temperature);
const struct kobj_attribute voltage_attr = __ATTR(voltage,0444,show_voltage,store_voltage);
const struct kobj_attribute status_attr = __ATTR(status,0444,show_status,store_status);


struct attribute *kobj_attr[] = {
    &temparature_attr.attr,
    &voltage_attr.attr,
    &status_attr.attr,
    NULL
};

struct attribute_group kobj_attr_grp = {
    .attrs = kobj_attr,
};

static int __init sys_device_init(void)
{
    int ret;
    pr_info("%s : called\n",__func__);

    mykobj = kobject_create_and_add("device",kernel_kobj);
    if(!mykobj)
    {
        pr_info("%s : kobject creation failed\n",__func__);
        return -1;
    }

    ret = sysfs_create_group(mykobj,&kobj_attr_grp);
    if(ret)
    {
        pr_info("%s : sysfs create failed\n",__func__);
        kobject_put(mykobj);
        return -1;
    }

    return 0;
}

static  void __exit sys_device_exit(void)
{
    sysfs_remove_group(mykobj,&kobj_attr_grp);
    kobject_put(mykobj);
    pr_info("%s : called\n",__func__);
}

module_init(sys_device_init);
module_exit(sys_device_exit);
