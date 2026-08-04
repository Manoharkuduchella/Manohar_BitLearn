obj-m := ethernet_interrupt.o
obj-m += ethernet_int_threaded_irq.o
obj-m += tasklet_module.o
obj-m += tasklet_schedule_module.o
obj-m += system_work_queue.o
obj-m += mem_io_module.o

TARGET=arm
COMPILER=arm-none-linux-gnueabihf-
KERN_DIR=/home/manohar/linux_ldd/ldd/source/linux/

all:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) modules

clean:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) clean

mem_app:
	$(COMPILER)-gcc memio_app.c -o memio_app
