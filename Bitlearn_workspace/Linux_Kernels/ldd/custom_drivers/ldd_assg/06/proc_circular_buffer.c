#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

#define MAX_LOGS    10
#define MAX_LEN     100

static struct proc_dir_entry *proc_entry;

/* Circular buffer */
static char logs[MAX_LOGS][MAX_LEN];
static int head = 0;
static int count = 0;

static int log_open(struct inode *inode, struct file *file)
{
    pr_info("%s called\n", __func__);
    return 0;
}

static ssize_t log_write(struct file *file,
                         const char __user *buffer,
                         size_t len,
                         loff_t *off)
{
    if (len >= MAX_LEN)
        len = MAX_LEN - 1;

    if (copy_from_user(logs[head], buffer, len))
        return -EFAULT;

    logs[head][len] = '\0';

    /* Remove newline added by echo */
    if (len > 0 && logs[head][len - 1] == '\n')
        logs[head][len - 1] = '\0';

    head = (head + 1) % MAX_LOGS;

    if (count < MAX_LOGS)
        count++;

    return len;
}

static ssize_t log_read(struct file *file,
                        char __user *buffer,
                        size_t len,
                        loff_t *off)
{
    char temp[1200];
    int i, index;
    int pos = 0;
    int copied;

    if (*off != 0)
        return 0;

    for (i = 0; i < count; i++) {

        index = (head - count + i + MAX_LOGS) % MAX_LOGS;

        pos += scnprintf(temp + pos,
                         sizeof(temp) - pos,
                         "%s\n",
                         logs[index]);
    }

    copied = min((size_t)pos, len);

    if (copy_to_user(buffer, temp, copied))
        return -EFAULT;

    *off += copied;

    return copied;
}

static const struct proc_ops log_ops = {
    .proc_open  = log_open,
    .proc_read  = log_read,
    .proc_write = log_write,
};

static int __init log_init(void)
{
    proc_entry = proc_create("log", 0666, NULL, &log_ops);

    if (!proc_entry)
        return -ENOMEM;

    pr_info("Circular Log Module Loaded\n");
    return 0;
}

static void __exit log_exit(void)
{
    proc_remove(proc_entry);
    pr_info("Circular Log Module Removed\n");
}

module_init(log_init);
module_exit(log_exit);