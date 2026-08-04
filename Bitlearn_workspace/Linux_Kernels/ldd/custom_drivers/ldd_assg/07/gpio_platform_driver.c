#include<linux/module.h>
#include<linux/init.h>
#include<linux/of_device.h>
#include<linux/platform_device.h>
#include<linux/gpio/consumer.h>
#include<linux/delay.h>

MODULE_LICENSE("GPL");

const struct of_device_id gpio_of_device_id[] = {
    {.compatible = "bitsilica,bone-usrled"},
    { }
};

int gpio_led_probe(struct platform_device *gdev)
{
    struct device_node *np = gdev->dev.of_node;
    struct device_node *child;
    const char *label;
    struct gpio_desc *desc[2];
    int i=0;

    pr_info("GPIO probe called\n");
    pr_info("Device : %s\n",dev_name(&gdev->dev));


    for_each_child_of_node(np,child)
    {
        pr_info("child node: %s\n",child->name);

        if(!of_property_read_string(child,"label",&label))
        {
            pr_info("%s : %s\n",child->name,label);
            
            desc[i] = devm_gpiod_get_from_of_node(&gdev->dev,
                                                        child,
                                                        "bone-gpios",
                                                        0,
                                                        GPIOD_OUT_HIGH,
                                                        child->name);
            if(IS_ERR(desc[i]))
            {
                pr_err("Failed to get GPIO for %s\n",child->name);
                continue;
            }
            gpiod_set_value(desc[i],0);
            msleep(2000);
            gpiod_set_value(desc[i++],1);
        }
    }


    return 0;
}

int gpio_led_remove(struct  platform_device *gdev)
{
    pr_info("GPIO remove called\n");
    return 0;
}
static struct platform_driver gpio_plat_driver = {
    .probe = gpio_led_probe,
    .remove = gpio_led_remove,
    .driver = {
        .name = "gpio-led",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(gpio_of_device_id),
    },
};


static int __init gpio_init(void)
{
    platform_driver_register(&gpio_plat_driver);
    return 0;
}

static void __exit gpio_exit(void)
{
    platform_driver_unregister(&gpio_plat_driver);
}

module_init(gpio_init);
module_exit(gpio_exit);
