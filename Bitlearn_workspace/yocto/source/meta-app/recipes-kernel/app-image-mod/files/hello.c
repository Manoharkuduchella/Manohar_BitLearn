/******************************************************************************
 *
 *   Copyright (C) 2011  Intel Corporation. All rights reserved.
 *
 *   SPDX-License-Identifier: GPL-2.0-only
 *
 *****************************************************************************/

#include <linux/module.h>

static int __init hello_init(void)
{
	pr_info("Hello app-image!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("Goodbye app-image!\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
