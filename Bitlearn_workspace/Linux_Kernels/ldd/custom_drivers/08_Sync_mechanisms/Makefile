obj-m := thread_spinlock.o
obj-m += chr_dev.c
obj-m += chr_dev_spin_lock.o
obj-m += chr_dev_semaphore.o
obj-m += chr_dev_mutexlock.o

TARGET=arm
COMPILER=arm-none-linux-gnueabihf-
KERN_DIR=/home/manohar/linux_ldd/ldd/source/linux/

all:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) modules

clean:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) clean

