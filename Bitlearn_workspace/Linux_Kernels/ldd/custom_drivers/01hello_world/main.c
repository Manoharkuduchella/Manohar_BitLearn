#include<linux/module.h>
#include<linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manohar");
MODULE_DESCRIPTION("A hello world kernel module");
MODULE_INFO(board,"Beaglebone black REV A5");

static int __init hello_in(void)
{
	pr_info("%s called\n",__func__);
	return 0;
}

static void __exit hello_ex(void)
{
	pr_info("%s called\n",__func__);
}

module_init(hello_in);
module_exit(hello_ex);

