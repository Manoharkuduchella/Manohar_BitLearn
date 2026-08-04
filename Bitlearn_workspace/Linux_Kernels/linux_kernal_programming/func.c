#include<linux/kernel.h>

void func(void)
{
	pr_info("%s : func called\n",__func__);
}
