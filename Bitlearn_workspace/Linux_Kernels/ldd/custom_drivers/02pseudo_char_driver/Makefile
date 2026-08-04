obj-m := chr_dev_lock.o
obj-m += chr_dev.o

TARGET=arm
COMPILER=arm-none-linux-gnueabihf-
KERN_DIR=/home/manohar/linux_ldd/ldd/source/linux/

all:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) modules

clean:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) clean

app:
	$(COMPILER)gcc user_ioctl_app.c -o user_ioctl_app


ioctl_macro:

	$(COMPILER)gcc ioctl_macros.c -o ioctl_macros
