#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/mutex.h>

/******************************************************************************/
static int at24cxx_detect(struct i2c_adapter *adapter, int address, int kind);
static int at24cxx_attach(struct i2c_adapter *adapter);
static int at24cxx_detach(struct i2c_client *client);

/*******************************************************************************/


static unsigned short ignore[]  =   { I2C_CLIENT_END };
static unsigned short normal_addr[] =   {0x50, I2C_CLIENT_END};

/*******************************************************************************/
static struct i2c_client_address_data addr_data = {
    .normal_i2c = normal_addr,
    .probe      = ignore,
    .ignore     = ignore,
};


static struct i2c_driver at24cxx_driver = {
    .driver = {
        .name   = "at24cxx",
    },
    .attach_adapter = at24cxx_attach,
    .detach_client  = at24cxx_detach,
};
/******************************************************************************/

static int at24cxx_detect(struct i2c_adapter *adapter, int address, int kind)
{
    printk("at24cxx_detect\r\n");
    return 0;
}

static int at24cxx_attach(struct i2c_adapter *adapter)
{
    return i2c_probe(adapter, &addr_data, at24cxx_detect);
}

static int at24cxx_detach(struct i2c_client *client)
{

    printk("at24cxx_detach!\r\n");
    return 0;
}





/**************************MODULE_INIT*****************************************/
static int  at24cxx_init(void)
{
    i2c_add_driver(&at24cxx_driver);
    return 0;
}

static void at24cxx_exit(void)
{
    i2c_del_driver(&at24cxx_driver);
}




module_init(at24cxx_init);
module_exit(at24cxx_exit);

MODULE_LICENSE("GPL");



