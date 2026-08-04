#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<asm/current.h>
#include<linux/sched.h>
#include<generated/utsrelease.h>
#include<linux/version.h>

MODULE_LICENSE("GPL");

static int __init ker_ver_in(void)
{
	#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,10)
		pr_info("KERNEL_VERSION: Hello OLD Kernel %s\n", UTS_RELEASE);
	#elif LINUX_VERSION_CODE >= KERNEL_VERSION(5,0,0)
		pr_info("KERNEL_VERSION: Hello NEW Kernel %s\n", UTS_RELEASE);
	#else
		pr_info("KERNEL_VERSION: Hello Moderate Kernel %s\n", UTS_RELEASE);
	#endif
	
	return 0;
		
}

static void __exit ker_ver_ex(void)
{
	pr_info("Exited multiple version driver\n");

}

module_init(ker_ver_in);
module_exit(ker_ver_ex);
