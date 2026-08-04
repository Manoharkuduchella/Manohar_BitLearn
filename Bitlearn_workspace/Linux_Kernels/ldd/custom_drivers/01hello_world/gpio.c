#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/sysfs.h>

MODULE_LICENSE("GPL");

struct gpio_drv_private
{
	struct gpio_desc *led;

	struct gpio_desc *button;
};

static struct gpio_drv_private pdata;

static struct kobject *my_kobj;

static ssize_t status_show(struct kobject *kobj,
			   struct kobj_attribute *attr,
			   char *buf)
{
	int led;
	int button;

	led = gpiod_get_value(pdata.led);

	button = gpiod_get_value(pdata.button);

	return sprintf(buf,
		       "LED=%d Button=%d\n",
		       led,
		       button);
}

static ssize_t status_store(struct kobject *kobj,
			    struct kobj_attribute *attr,
			    const char *buf,
			    size_t count)
{
	int value;

	if(kstrtoint(buf,10,&value))
		return -EINVAL;

	gpiod_set_value(pdata.led,value);

	return count;
}

static struct kobj_attribute status_attr =
	__ATTR(status,0664,status_show,status_store);

static int gpio_probe(struct platform_device *pdev)
{
	int ret;

	pr_info("GPIO Probe\n");

	pdata.led =
	devm_gpiod_get(&pdev->dev,
		       "led",
		       GPIOD_OUT_LOW);

	if(IS_ERR(pdata.led))
		return PTR_ERR(pdata.led);

	pdata.button =
	devm_gpiod_get(&pdev->dev,
		       "button",
		       GPIOD_IN);

	if(IS_ERR(pdata.button))
		return PTR_ERR(pdata.button);

	my_kobj =
	kobject_create_and_add("mygpio",
			       kernel_kobj);

	if(!my_kobj)
		return -ENOMEM;

	ret =
	sysfs_create_file(my_kobj,
			  &status_attr.attr);

	if(ret)
		return ret;

	pr_info("GPIO Driver Loaded\n");

	return 0;
}

static int gpio_remove(struct platform_device *pdev)
{
	sysfs_remove_file(my_kobj,
			  &status_attr.attr);

	kobject_put(my_kobj);

	pr_info("GPIO Driver Removed\n");

	return 0;
}

static const struct of_device_id gpio_dt_ids[] =
{
	{ .compatible="org,gpio_driver"},
	{ }
};

MODULE_DEVICE_TABLE(of,gpio_dt_ids);

static struct platform_driver gpio_driver =
{
	.probe = gpio_probe,
	.remove = gpio_remove,

	.driver =
	{
		.name="gpio_driver",
		.of_match_table=gpio_dt_ids,
	},
};

module_platform_driver(gpio_driver);
