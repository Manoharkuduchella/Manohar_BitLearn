
#obj-m := character_device_driver.o
#obj-m += kernel_linked_list.o
#obj-m += ioctl_driver.o
#obj-m += character_proc_fs_mod.o
#obj-m += char_sysfs_attr_mod.o
#obj-m += char_wait_queue_mod.o
#obj-m += char_kernel_thread.o
#obj-m += char_work_queue.o
#obj-m += timer_driver.o
#obj-m += shared_irq_module.o
#obj-m += char_platform_driver.o
#obj-m += i2c_client_driver.o
#obj-m += spi_slave_driver.o
#obj-m += gpio_platform_driver.o
#obj-m += complete_char_driver.o
obj-m += virtual_temperature_sensor.o

TARGET=arm
COMPILER=arm-none-linux-gnueabihf-
KERN_DIR=/home/manohar/linux_ldd/ldd/source/linux/

all:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) modules

clean:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) clean

ioctl_app:
	$(COMPILER)gcc ioctl_userapp.c -o ioctl_userapp