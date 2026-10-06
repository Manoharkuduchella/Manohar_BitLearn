// /*--------for device tree:---------
// &spi1 {
//     status = "okay";
//     spi-cpha;
//     spi-cpol;

//     my_sensor@0 {
//         reg = <0>;
//         compatible = "sensor,my-sensor";
//     };
// };
// */

// #include<linux/module.h>
// #include<linux/spi/spi.h>
// #include<linux/of_device.h>

// MODULE_LICENSE("GPL");

// static struct of_device_id my_of_match[] = {
//     {.compatible = "sensor,my-sensor"},
//     { }
// };

// static int my_probe(struct spi_device *spi)
// {
//     pr_info("Probe called\n");

//     pr_info("SPI Bus = %hi\n",spi->master->bus_num);
//     pr_info("Chip Select = %hhx\n,spi->chip_select");

//     return 0;
// }

// static int my_remove(struct spi_device *spi)
// {
//     pr_info("Remove called\n");
//     return 0;
// }

// MODULE_DEVICE_TABLE(of,my_of_match);


// static struct spi_driver my_spi_driver = {
//     .probe = my_probe,
//     .remove = my_remove,
//     .driver = {
//         .name = "my_sensor",
//         .of_match_table = of_match_ptr(my_of_match),
//     },
// };


// module_spi_driver(my_spi_driver);



/*4. You have a system that crashes randomly. Provide steps to diagnose and fix the issue.*/
/*firstly check kernel logs look for messages such as:
     Kernel panic
    Oops
    BUG:
    Call Trace
    Segmentation fault
    Null pointer dereference
    Out of memory
    Watchdog

  inspect driver messages dmesg | grep driver_name
  Enable dynamic debugging
  Use gdb for userspace
  Use Valgrind for memory issues
*/

/*5. Explain the role of "BitBake" in Yocto project and provide an example recipe for building a custom application.*/

/*
Bitbake is the build engine of the yocto project

it reads recipes(.bb), resolves dependencies, executes build tasks, and generates packages and images.
role of bitbake:
    parses recipes
    parses configuration files(.conf)
    resolve dependencies
    Downloads source code
    applirs patches
    compiles source code
    Installs files into a staging directory
    Creates packages(.ipk,.rpm,.deb)
    Builds complete Linux images

    -------------------hello_0.1.bb-------------------:

    DESCRIPITON = "Simple Hello World Application"
    LICENSE = "MIT"

    SRC_URI = "file://hello.c \ 
               file://Makefile \ 
              "
    
    S = "${WORKDIR}"

    do_compile() {
        oe_runmake
    }

    do_install() {
        install -d ${D}${bindir}
        install -m 0677 hello ${D}${bindir}
    }

*/


/*7. Describe the process of validating a complex embedded system. What tools and techniques would you use, and how do you ensure robustness during testing?
*/

/*
Requirements
      │
      ▼
Test Plan
      │
      ▼
Test Case Design
      │
      ▼
Test Environment Setup
      │
      ▼
Functional Testing
      │
      ▼
Integration Testing
      │
      ▼
Stress & Performance Testing
      │
      ▼
Regression Testing
      │
      ▼
Bug Fixes
      │
      ▼
Revalidation
      │
      ▼
Release


example:
Suppose you're validating a V4L2 camera driver.

Validation steps:

Boot the board.
Verify the driver probes successfully (dmesg).
Confirm /dev/video0 is created.
Capture images using v4l2-ctl or GStreamer.
Test different resolutions and frame rates.
Run continuous streaming for several hours.
Disconnect and reconnect the camera (if supported).
Monitor CPU, memory, and kernel logs.
Verify no frame drops, memory leaks, or kernel panics.
Re-run all tests after any driver modifications.


*/

/*8. Provide an in-depth explanation of how kmalloc and vmalloc are used for memory allocation, including their advantages and disadvantages.*/

/*
kmalloc() allocates physically contiguous memory from the kernel's slab allocator.

#include <linux/slab.h>

void *kmalloc(size_t size, gfp_t flags);


| Flag         | Meaning                                                  |
| ------------ | -------------------------------------------------------- |
| `GFP_KERNEL` | Normal kernel allocation; may sleep.                     |
| `GFP_ATOMIC` | Used in interrupt context; cannot sleep.                 |
| `GFP_DMA`    | Allocate DMA-capable memory if required by the platform. |
| `GFP_NOWAIT` | Return immediately if memory isn't available.            |

Advantages of kmalloc():
Fast allocation
Physically contiguous memory
Suitable for DMA (depending on allocation flags and hardware requirements)
Lower overhead than vmalloc()
Good cache locality

Disadvantages of kmalloc():
Limited by the availability of contiguous physical memory
Large allocations may fail due to fragmentation
Not ideal for very large buffers


vmalloc() allocates virtually contiguous memory.
The underlying physical pages may be scattered throughout RAM.

#include <linux/vmalloc.h>

void *vmalloc(unsigned long size);

Advantages of vmalloc():
Easier to allocate large memory regions
Less affected by physical memory fragmentation
Convenient for large software buffers

Disadvantages of vmalloc():
Slower than kmalloc()
Not physically contiguous
Requires page table setup
Typically unsuitable for DMA because devices usually require physically contiguous memory


When Should You Use Each?

Use kmalloc() for:

Driver private structures
Network packets
DMA buffers (when appropriate)
Small to medium-sized allocations
Frequently accessed data

Use vmalloc() for:

Large software buffers
Large lookup tables
Filesystem caches
Image/frame buffers that don't need physically contiguous memory

*/


#include<stdio.h>
#include<stdbool.h>

typedef struct {
    int pin;
    bool is_enabled;
} GpioPin;

int num_pins = 0;

void add_gpio(GpioPin *pins, int pin, bool status)
{
    if(!pins)
    {
        pins = realloc(pins,sizeof(GpioPin));
        pins[num_pins].pin = pin;
        pins[num_pins].is_enabled = status;
        num_pins++;
        return;
    }

    pins = realloc(pins,(sizeof(GpioPin)*(num_pins+1)));
    pins[num_pins].pin = pin;
    pins[num_pins].is_enabled = status;
    num_pins++;
    return;

}

void remove_gpio(GpioPin **pins, int pin)
{

}

void update_gpio(GpioPin **pins, int pin, bool status)
{
    for(int i = 0; i < num_pins;i++)
    {
        if((*pins)[i].pin == pin)
            (*pins)[i].is_enabled = status;
    }

}

int main()
{

    GpioPin *gpins = NULL;


    
}