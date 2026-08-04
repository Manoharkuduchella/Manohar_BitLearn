#include<linux/module.h>
#include<linux/init.h>
#include<linux/sysfs.h>
#include<linux/kobject.h>


MODULE_LICENSE("GPL");

struct kobject *mykobj;
const char *led_on = "->LED_ON\n";
const char *led_off = "->LED_OFF\n";
int val;

ssize_t show_brightness(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    //return sysfs_emit(buf,"%d",val);
    if(val)
    {
        pr_info("%s",led_on);
        return strlen(led_on);
    }
    else
    {
        pr_info("%s",led_off);
        return strlen(led_off);
    }
    
}

ssize_t store_brightness(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    int ret;
    ret = kstrtoint(buf,10,&val);
    if(ret < 0)
    {
        pr_info("kstrint failed\n");
        return ret;
    }

    if(val)
        pr_info("%s",led_on);
    else
        pr_info("%s",led_off);


    return count;
}                 


const struct kobj_attribute brightness_attr = __ATTR(brightness,0644,show_brightness,store_brightness);


static int __init sys_attri_init(void)
{
    int ret;
    pr_info("%s : called\n",__func__);

    mykobj = kobject_create_and_add("kobj_driver",kernel_kobj);
    if(IS_ERR(PTR_ERR(mykobj)))
    {
        pr_info("%s : kobject creation failed\n",__func__);
        return -1;
    }

    ret = sysfs_create_file(mykobj,&brightness_attr.attr);
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