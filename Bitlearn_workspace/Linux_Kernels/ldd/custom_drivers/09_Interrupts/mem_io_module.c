#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/io.h>
#include<linux/ioport.h>

#define MY_BASE_ADDR 0xf8000000
#define LENGTH 0xf

MODULE_LICENSE("GPL");

static int test_memio_init(void)
{
    if(!request_mem_region(MY_BASE_ADDR,LENGTH,"myports"))
    {
        pr_info("request mem region failed for myports\n");
        return -1;
    }else{
        void __iomem *p;

        int value;

        pr_info("request mem region success for myports\n");

        p = ioremap(MY_BASE_ADDR,LENGTH);
        pr_info("ioremap returned:%px\n",p);

        // *(unsigned int *)p = 0x12345678;
        // pr_info("read:%04x\n",*(unsigned int *p));

        iowrite32(0x12345678,p);
        value = ioread32(p);

        pr_info("value read: %02x\n",value);


        iounmap(p);
    }

    return 0;
}

static void test_memio_exit(void)
{
    pr_info("%s: In exit\n",__func__);
    release_mem_region(MY_BASE_ADDR,LENGTH);
}

module_init(test_memio_init);
module_exit(test_memio_exit);