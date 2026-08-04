#include<linux/module.h>
#include<linux/init.h>
#include<linux/platform_device.h>
#include<linux/of_device.h>

MODULE_LICENSE("GPL");  

static const struct of_device_id char_of_device_id[] = {
    {.compatible = "bitsilica,char_plat_dev"},
    {.compatible = "bitsilica,char_plat_dev2"},
    {}
};

MODULE_DEVICE_TABLE(of,char_of_device_id);

static int char_probe(struct platform_device *ch_plat_dev)
{
    pr_info("Platform Driver: probe called\n");

    pr_info("Device Name : %s\n", dev_name(&ch_plat_dev->dev));
    return 0;
}

static int char_remove(struct platform_device *ch_plat_dev)
{
    pr_info("Platform Driver: remove called\n");
    return 0;
}


static struct platform_driver char_plat = {
    .probe = char_probe,
    .remove = char_remove,
    .driver = {
        .name = "char_plat",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(char_of_device_id)
    }
};

static int __init plat_init(void)
{
    pr_info("%s : called\n",__func__);
    return platform_driver_register(&char_plat);
}

static void __exit plat_exit(void)
{
    pr_info("%s : called\n",__func__);
    platform_driver_unregister(&char_plat);
}

module_init(plat_init);
module_exit(plat_exit);