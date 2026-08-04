#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>

/* Driver private data */
struct my_pwm_chip {
	void __iomem *base;
};

/* Device tree match table */
static const struct of_device_id pwm_of_match[] = {
	{
		.compatible = "jahnavi,my-pwm",
	},
	{}
};

MODULE_DEVICE_TABLE(of, pwm_of_match);

/* Probe function */
static int pwm_probe(struct platform_device *pdev)
{
	struct my_pwm_chip *pc;
	struct resource *res;

	dev_info(&pdev->dev, "Probe called\n");

	/* Allocate private data */
	pc = devm_kzalloc(&pdev->dev, sizeof(*pc), GFP_KERNEL);
	if(!pc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if(!res){
		dev_err(&pdev->dev, "Failed to get memory resource\n");
		return -ENODEV;
	}

	dev_info(&pdev->dev, "Physical start: %pa\n", &res->start);
	dev_info(&pdev->dev, "Physical end: %pa\n", &res->end);

	/* Map registers */
       	pc->base = devm_ioremap_resource(&pdev->dev, res);
	if(IS_ERR(pc->base))
	 	return PTR_ERR(pc->base);
	dev_info(&pdev->dev, "Registers mapped successfully\n");

	/* Save private data */
	platform_set_drvdata(pdev, pc);
	dev_info(&pdev->dev, "Driver initialised successfully\n");

	return 0;
}

/* Remove function */
static int pwm_remove(struct platform_device *pdev)
{
	struct my_pwm_chip *pc;

	pc = platform_get_drvdata(pdev);

	dev_info(&pdev->dev, "Removing PWM driver\n");
	pc = NULL;

	return 0;
}

/* Platform driver */
static struct platform_driver pwm_driver = {
	.probe = pwm_probe,
	.remove = pwm_remove,
	.driver = {
		.name = "my-pwm",
		.of_match_table = pwm_of_match,
	},
};

/* Register driver */
module_platform_driver(pwm_driver);

/* Module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jahnavi");
MODULE_DESCRIPTION("PWM driver");
