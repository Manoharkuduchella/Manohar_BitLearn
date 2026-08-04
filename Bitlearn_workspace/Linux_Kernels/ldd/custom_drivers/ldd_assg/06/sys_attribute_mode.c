/*Objective:
Create configurable mode attribute.

Attribute:
mode

Allowed Values:
AUTO
MANUAL
OFF

Invalid input should return:
Invalid Mode
*/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/sysfs.h>
#include<linux/kobject.h>
#include<linux/string.h>


MODULE_LICENSE("GPL");

struct kobject *mykobj;

static char mode[10] = "AUTO";

ssize_t show_mode(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    return sysfs_emit(buf, "%s\n",mode);
}

ssize_t store_mode(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    if(sysfs_streq(buf,"AUTO"))
    {
        strcpy(mode,"AUTO");
    }
    else if(sysfs_streq(buf, "MANUAL"))
    {
        strcpy(mode,"MANUAL");
    }
    else if(sysfs_streq(buf, "OFF"))
    {
        strcpy(mode,"OFF");
    }
    else{
        pr_err("Invalid Mode\n");
        return -EINVAL;
    }

    return count;
}                 


const struct kobj_attribute mode_attr = __ATTR(mode,0644,show_mode,store_mode);


static int __init sys_attri_init(void)
{
    int ret;
    pr_info("%s : called\n",__func__);

    mykobj = kobject_create_and_add("ker_mode",kernel_kobj);
    if(!mykobj)
    {
        pr_info("%s : kobject creation failed\n",__func__);
        return -1;
    }

    ret = sysfs_create_file(mykobj,&mode_attr.attr);
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
    sysfs_remove_file(mykobj, &mode_attr.attr);
    kobject_put(mykobj);
    pr_info("%s : called\n",__func__);
}


module_init(sys_attri_init);
module_exit(sys_attri_exit);