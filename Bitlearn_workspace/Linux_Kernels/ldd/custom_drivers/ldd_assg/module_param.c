#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");

static char *str="name";
static int id=0;
static bool enable=false;

module_param(str,charp,0);
module_param(id,int,0);
module_param(enable,bool,0);


static int __init mod_in(void)
{
	pr_info("mod_in called\n");
	pr_info("%s : str = %s\n",__func__,str);
	pr_info("%s : id = %d\n",__func__,id);
	pr_info("%s : str = %d\n",__func__,enable);

	return 0;
}

static void __exit mod_ex(void)
{
	pr_info("mod_ex called\n");

}

module_init(mod_in);
module_exit(mod_ex);
