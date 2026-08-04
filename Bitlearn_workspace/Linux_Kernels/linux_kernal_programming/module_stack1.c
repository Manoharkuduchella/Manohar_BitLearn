#include<linux/kernel.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

int myadd(int a, int b)
{
	pr_info("%s: Adding %d with %d\t Result:%d\n",__func__,a,b,(a+b));
	return (a+b);
}

EXPORT_SYMBOL(myadd);

static int __init module_stack1_in(void)
{
	pr_info("%s:In Init\n",__func__);
	return 0;
}

static void __exit module_stack1_ex(void)
{
	pr_info("%s:In Exit\n",__func__);
}

module_init(module_stack1_in);
module_exit(module_stack1_ex);
