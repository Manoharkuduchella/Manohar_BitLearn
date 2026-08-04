#include<linux/kernel.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

static int __init h_init(void)
{
	pr_info("%s:In Init\n",__func__);
	return 0;
	//return -1; insertion gets failed
}

static void __exit h_exit(void)
{
	pr_info("%s:In Exit\n",__func__);
}

module_init(h_init);
module_exit(h_exit);

