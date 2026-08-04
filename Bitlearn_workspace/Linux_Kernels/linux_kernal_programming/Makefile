obj-m := kernel_mod.o
obj-m += kernel_mod2.o
obj-m += arguments.o
obj-m += parameter_array.o
obj-m += symbol_export.o 
obj-m += module_stack1.o 
obj-m += module_stack2.o 
obj-m += hello_pr_debug.o
obj-m += kthread_two.o
obj-m += multiple_version_mod.o

kernel_mod-objs := hello_world_mod.o
kernel_mod2-objs := hello_world_mod2.o

ccflags-y := -DDEBUG

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
