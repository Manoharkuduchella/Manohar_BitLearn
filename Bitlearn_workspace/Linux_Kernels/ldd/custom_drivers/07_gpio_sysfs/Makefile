obj-m := gpio_sysfs.o

TARGET=arm
COMPILER=arm-none-linux-gnueabihf-
KERN_DIR=/home/manohar/linux_ldd/ldd/source/linux/

all:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) modules

clean:
	make ARCH=$(TARGET) CROSS_COMPILE=$(COMPILER) -C $(KERN_DIR) M=$(PWD) clean
	
#app: lcd_app.o lcd.o gpio.o lcd_app.elf

#lcd_app.o: lcd_app.c
#	$(COMPILER)gcc -c -o lcd_app.o lcd_app.c 
#	(or)
#	$(COMPILER)gcc -c -o $@ $^ 
