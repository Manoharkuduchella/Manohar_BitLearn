#obj-m := char_driver.o
#obj-m := procfs_read_module.o
#obj-m += proc_rw_module.o
#obj-m += proc_counter_module.o
#obj-m += process_info.o
#obj-m += memory_info.o
#obj-m += sysfs_attribute_mod.o
#obj-m += sysfs_attribute_multi_mod.o
#obj-m += led_sim_sysfs.o
#obj-m += proc_calculator.o
#obj-m += kernel_uptime.o
#obj-m += sysfs_device_info.o
#obj-m += procfs_statistics.o
#obj-m += proc_sysinfo.o
#obj-m += sys_attribute_mode.o
#obj-m += proc_pid_lookup.o
#obj-m += proc_moduleparam.o
#obj-m += sysfs_trigger.o
obj-m += proc_circular_buffer.o
#obj-m += sysfs_ro_rw_module.o
#obj-m += mini_device_driver.o




TARGET=arm
COMPILER=arm-none-linux-gnueabihf-
KERN_DIR=/home/manohar/linux_ldd/ldd/source/linux/

all:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) modules

clean:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) clean
