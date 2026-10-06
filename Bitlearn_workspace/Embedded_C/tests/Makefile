obj-m := t_06_08_ldd.o

all:
	make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- -C /home/manohar/linux_ldd/ldd/source/linux/ M=${PWD} modules

clean:
	make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- -C /home/manohar/linux_ldd/ldd/source/linux/ M=${PWD} clean