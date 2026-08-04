#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

static int number;
static char *string;

module_param(number,int,0);
MODULE_PARM_DESC(number,"an int as parameter");

module_param(string,charp,0);
MODULE_PARM_DESC(string,"an string as parameter");


static int __init hell_in(void)
{
	pr_info("%s called\n",__func__);
	pr_info("parameter number:%d\n",number);
	pr_info("parameter string:%s\n",string);

	return 0;
		
}

static void __exit hell_ex(void)
{
	pr_info("%s called\n",__func__);

}

module_init(hell_in);
module_exit(hell_ex);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("module_param module");


