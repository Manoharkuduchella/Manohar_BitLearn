obj-m := pcd_device_setup.o pcd_platform_driver.o

TARGET=arm
COMPILER=arm-none-linux-gnueabihf-
KERN_DIR=/home/manohar/linux_ldd/ldd/source/linux/

all:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) modules

clean:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) clean
	
