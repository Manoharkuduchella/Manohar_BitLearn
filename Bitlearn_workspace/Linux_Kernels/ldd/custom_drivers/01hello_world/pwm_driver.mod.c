#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xf28efea0, "module_layout" },
	{ 0x53934f07, "platform_driver_unregister" },
	{ 0xb3e308df, "__platform_driver_register" },
	{ 0x4ad8eb83, "devm_ioremap_resource" },
	{ 0x26cbdb59, "_dev_err" },
	{ 0x8b077ff4, "platform_get_resource" },
	{ 0xc392e164, "devm_kmalloc" },
	{ 0xbaaced3b, "_dev_info" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cjahnavi,my-pwm");
MODULE_ALIAS("of:N*T*Cjahnavi,my-pwmC*");
