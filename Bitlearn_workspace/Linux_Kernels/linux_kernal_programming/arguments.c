#include<linux/kernel.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
char *name = "Embedded";
int loop_count = 1;

module_param(name, charp, S_IRUGO);
module_param(loop_count, int, S_IRUGO);

static int __init test_args_in(void)
{
	int i;
	pr_info("%s : In init\n",__func__);
	pr_info("%s : Loop count:%d\n",__func__,loop_count);

	for(i=0;i<loop_count;i++)
	{
		pr_info("%s : Hi %s\n",__func__,name);
	}

	return 0;
}

static void __exit test_arguments_ex(void)
{
	pr_info("%s : In exit\n",__func__);
}

module_init(test_args_in);
module_exit(test_arguments_ex);


