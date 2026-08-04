#include<linux/kernel.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

extern int myadd(int a, int b);


static int __init module_stack2_in(void)
{
	pr_info("%s:In Init\n",__func__);
	pr_info("%s: Add:%d\n",__func__,myadd(3,5));
	return 0;
}

static void __exit module_stack2_ex(void)
{
	pr_info("%s:In Exit\n",__func__);
}

module_init(module_stack2_in);
module_exit(module_stack2_ex);
