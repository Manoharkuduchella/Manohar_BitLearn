#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");

#define DRIVER_VERSION "1.0"

static struct proc_dir_entry *proc_entry;
static struct kobject *device_kobj;

/* Driver State */
static int device_enabled;
static int enable_count;
static int disable_count;
static int reset_count;


static ssize_t status_show(struct kobject *kobj,struct kobj_attribute *attr,char *buf)
{
    return sprintf(buf, "%s\n",
            device_enabled ? "Enabled" : "Disabled");
}

static struct kobj_attribute status_attr =__ATTR(status, 0444, status_show, NULL);

static ssize_t version_show(struct kobject *kobj,struct kobj_attribute *attr,char *buf)
{
    return sprintf(buf, "%s\n", DRIVER_VERSION);
}

static struct kobj_attribute version_attr =__ATTR(version, 0444, version_show, NULL);

static ssize_t statistics_show(struct kobject *kobj,struct kobj_attribute *attr,char *buf)
{
    return sprintf(buf,
            "Enable Count : %d\n"
            "Disable Count : %d\n"
            "Reset Count : %d\n",
            enable_count,
            disable_count,
            reset_count);
}

static struct kobj_attribute statistics_attr =__ATTR(statistics, 0444, statistics_show, NULL);


static int device_open(struct inode *inode, struct file *file)
{
    pr_info("%s called\n", __func__);
    return 0;
}

static ssize_t device_read(struct file *file,char __user *buff,size_t len,loff_t *off)
{
    char msg[128];
    int ret;

    if (*off)
        return 0;

    ret = snprintf(msg, sizeof(msg),
            "Status : %s\n"
            "Version : %s\n",
            device_enabled ? "Enabled" : "Disabled",
            DRIVER_VERSION);

    if (copy_to_user(buff, msg, ret))
        return -EFAULT;

    *off = ret;

    return ret;
}

static ssize_t device_write(struct file *file,const char __user *buff,size_t len,loff_t *off)
{
    char cmd[20];

    if (len >= sizeof(cmd))
        len = sizeof(cmd) - 1;

    if (copy_from_user(cmd, buff, len))
        return -EFAULT;

    cmd[len] = '\0';

    if (cmd[len - 1] == '\n')
        cmd[len - 1] = '\0';

    if (!strcmp(cmd, "enable")) {

        if (!device_enabled) {
            device_enabled = 1;
            enable_count++;
        }

        pr_info("Device Enabled\n");
    }
    else if (!strcmp(cmd, "disable")) {

        if (device_enabled) {
            device_enabled = 0;
            disable_count++;
        }

        pr_info("Device Disabled\n");
    }
    else if (!strcmp(cmd, "reset")) {

        device_enabled = 0;

        enable_count = 0;
        disable_count = 0;
        reset_count++;

        pr_info("Device Reset\n");
    }
    else {

        pr_info("Unknown Command\n");
    }

    return len;
}

static int device_release(struct inode *inode, struct file *file)
{
    pr_info("%s called\n", __func__);
    return 0;
}

static const struct proc_ops proc_fops = {

    .proc_open = device_open,
    .proc_read = device_read,
    .proc_write = device_write,
    .proc_release = device_release,
};


static int __init mini_driver_init(void)
{
    int ret;

    proc_entry = proc_create("device",
                             0666,
                             NULL,
                             &proc_fops);

    if (!proc_entry)
        return -ENOMEM;

    device_kobj = kobject_create_and_add("device", kernel_kobj);

    if (!device_kobj) {
        proc_remove(proc_entry);
        return -ENOMEM;
    }

    ret = sysfs_create_file(device_kobj, &status_attr.attr);
    if (ret)
        goto err;

    ret = sysfs_create_file(device_kobj, &version_attr.attr);
    if (ret)
        goto err;

    ret = sysfs_create_file(device_kobj, &statistics_attr.attr);
    if (ret)
        goto err;

    pr_info("Mini Driver Loaded\n");

    return 0;

err:
    kobject_put(device_kobj);
    proc_remove(proc_entry);
    return ret;
}


static void __exit mini_driver_exit(void)
{
    sysfs_remove_file(device_kobj, &status_attr.attr);
    sysfs_remove_file(device_kobj, &version_attr.attr);
    sysfs_remove_file(device_kobj, &statistics_attr.attr);

    kobject_put(device_kobj);

    proc_remove(proc_entry);

    pr_info("Mini Driver Removed\n");
}

module_init(mini_driver_init);
module_exit(mini_driver_exit);
