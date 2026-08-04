/*Objective:
Create attributes with different permissions.

Files:
serial_number (Read Only)
enable (Read Write)

Attempt:

echo 100 > serial_number

Expected:
Permission denied*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

MODULE_LICENSE("GPL");

static struct kobject *my_kobj;

static int enable = 0;
static const int serial_number = 123456789;

static ssize_t serial_show(struct kobject *kobj,
                           struct kobj_attribute *attr,
                           char *buf)
{
    return sprintf(buf, "%d\n", serial_number);
}

static struct kobj_attribute serial_attr =
        __ATTR(serial_number, 0444, serial_show, NULL);


static ssize_t enable_show(struct kobject *kobj,
                           struct kobj_attribute *attr,
                           char *buf)
{
    return sprintf(buf, "%d\n", enable);
}

static ssize_t enable_store(struct kobject *kobj,
                            struct kobj_attribute *attr,
                            const char *buf,
                            size_t count)
{
    kstrtoint(buf, 10, &enable);

    pr_info("Enable = %d\n", enable);

    return count;
}

static struct kobj_attribute enable_attr =
        __ATTR(enable, 0664, enable_show, enable_store);


static int __init permission_init(void)
{
    int ret;

    my_kobj = kobject_create_and_add("mydevice", kernel_kobj);

    if (!my_kobj)
        return -ENOMEM;

    ret = sysfs_create_file(my_kobj, &serial_attr.attr);
    if (ret)
        return ret;

    ret = sysfs_create_file(my_kobj, &enable_attr.attr);
    if (ret)
        return ret;

    pr_info("Module Loaded\n");

    return 0;
}


static void __exit permission_exit(void)
{
    sysfs_remove_file(my_kobj, &serial_attr.attr);
    sysfs_remove_file(my_kobj, &enable_attr.attr);

    kobject_put(my_kobj);

    pr_info("Module Removed\n");
}

module_init(permission_init);
module_exit(permission_exit);