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
	{ 0x18ff5646, "class_destroy" },
	{ 0x53934f07, "platform_driver_unregister" },
	{ 0xb3e308df, "__platform_driver_register" },
	{ 0xc5850110, "printk" },
	{ 0x54471b96, "__class_create" },
	{ 0xb794ef5d, "device_unregister" },
	{ 0x8c48ec5b, "device_create_with_groups" },
	{ 0xe914e41e, "strcpy" },
	{ 0x91dc4da3, "devm_fwnode_gpiod_get_index" },
	{ 0xc358aaf8, "snprintf" },
	{ 0x803788c5, "_dev_warn" },
	{ 0x97fb274c, "of_property_read_string" },
	{ 0x221567cf, "of_get_next_available_child" },
	{ 0xc392e164, "devm_kmalloc" },
	{ 0xbaaced3b, "_dev_info" },
	{ 0x26cbdb59, "_dev_err" },
	{ 0x6dd40485, "of_get_next_child" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xb1c611e4, "gpiod_set_value" },
	{ 0xaa19e4aa, "_kstrtol" },
	{ 0xadd471e9, "gpiod_get_value" },
	{ 0xa7b27c8a, "gpiod_direction_output" },
	{ 0xfa623465, "gpiod_direction_input" },
	{ 0x222e7ce2, "sysfs_streq" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x104a1d1, "gpiod_get_direction" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");

