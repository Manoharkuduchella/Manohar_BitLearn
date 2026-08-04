#include<linux/module.h>
#include<linux/init.h>
#include<linux/i2c.h>
#include<linux/of_device.h>
#include <linux/slab.h>


#define NUM_REGS 256

struct dummy_sensor {
    struct i2c_client *client;
    u8 regs[NUM_REGS];
};

static int dummy_read_reg(struct i2c_client *client, u8 reg)
{
    struct dummy_sensor *sensor = i2c_get_clientdata(client);

    return sensor->regs[reg];
}

static int dummy_write_reg(struct i2c_client *client,u8 reg,u8 value)
{
    struct dummy_sensor *sensor = i2c_get_clientdata(client);

    sensor->regs[reg] = value;

    return 0;
}

int dummy_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    pr_info("%s : called\n",__func__);
    pr_info("%s : Addr = %x\n",__func__,client->addr);


    struct dummy_sensor *sensor;

    sensor = devm_kzalloc(&client->dev,sizeof(*sensor),GFP_KERNEL);

    if (!sensor)
        return -ENOMEM;

    sensor->client = client;

    sensor->regs[0x00] = 0xA5;   /* Device ID */
    sensor->regs[0x01] = 0x01;   /* Version */

    i2c_set_clientdata(client, sensor);


    dummy_write_reg(client, 0x20, 0x55);

    pr_info("Reg 0x20 = 0x%x\n",dummy_read_reg(client, 0x20));


    return 0;
}
int dummy_remove(struct i2c_client *client)
{
    pr_info("%s : called\n",__func__);
    return 0;
}


static const struct of_device_id i2c_client_dev[] = {
    {.compatible = "bitsilica,dummy-i2c-sensor"},
    { },
};

static const struct i2c_device_id i2c_client_id[] = {
    {"dummy-i2c-sensor",0},
    { }
};

MODULE_DEVICE_TABLE(i2c,i2c_client_id);

static struct i2c_driver dummy_i2c_driver = {
    .probe = dummy_probe,
    .remove = dummy_remove,
    .driver = {
        .name = "dummy-sensor",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(i2c_client_dev)
    },
    .id_table = i2c_client_id,
};  

module_i2c_driver(dummy_i2c_driver);

MODULE_LICENSE("GPL");