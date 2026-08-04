#include<linux/module.h>
#include<linux/init.h>
#include<linux/spi/spi.h>
#include<linux/of_device.h>

MODULE_LICENSE("GPL");

struct dummy_sensor {
    struct spi_device *spi;
    u8 regs[256];
}sen;

const struct of_device_id dummy_spi_dev[] = {
    {.compatible = "bitsilica,dummy-spi-sensor"},
    { },
};

const struct spi_device_id dummy_spi_id[] = {
    {"dummy-spi-sensor",0},
    { }
};

static int dummy_read_reg(struct dummy_sensor *sensor,u8 reg)
{
    return sensor->regs[reg];
}

static int dummy_write_reg(struct dummy_sensor *sensor, u8 reg, u8 value)
{
    sensor->regs[reg] = value;
    return 0;
}


int dummy_probe(struct spi_device *spi)
{
    pr_info("%s : called\n",__func__);

    pr_info("%s : max_speed_hz = %u\n",__func__,spi->max_speed_hz);

    dummy_write_reg(&sen,0x10,0x55);

    pr_info("Read = %x\n",dummy_read_reg(&sen,0x10));

    return 0;
}

int dummy_remove(struct spi_device *spi)
{
    pr_info("%s : called\n",__func__);
    return 0;
}

static struct spi_driver dummy_spi_driver = {
    .probe = dummy_probe,
    .remove = dummy_remove,
    .driver = {
        .name = "dummy-spi",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(dummy_spi_dev),
    },
    .id_table = dummy_spi_id,
};


module_spi_driver(dummy_spi_driver);