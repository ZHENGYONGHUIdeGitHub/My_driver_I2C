#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/fs.h>

/******************************************************************************/
static int major;
static struct class *cls;

/******************************************************************************/
static int at24cxx_detect(struct i2c_adapter *adapter, int address, int kind);
static int at24cxx_attach(struct i2c_adapter *adapter);
static int at24cxx_detach(struct i2c_client *client);
static ssize_t at24cxx_read(struct file *file, char __user *buf, size_t size, loff_t *offset);
static ssize_t at24cxx_write(struct file *file, const char __user *buf, size_t size, loff_t *offset);


/*******************************************************************************/


static unsigned short ignore[]  =   { I2C_CLIENT_END };
static unsigned short normal_addr[] =   {0x50, I2C_CLIENT_END};
//static unsigned short forces_addr[] =   { ANY_I2C_BUS, 0x60, I2C_CLIENT_END };
//static unsigned short *forces[]     =   {  forces_addr, NULL};

/*******************************************************************************/
static struct i2c_client_address_data addr_data = {
    .normal_i2c = normal_addr,
    .probe      = ignore,
    .ignore     = ignore,
 // .forces     = forces,
};


static struct i2c_driver at24cxx_driver = {
    .driver = {
        .name   = "at24cxx",
    },
    .attach_adapter = at24cxx_attach,
    .detach_client  = at24cxx_detach,
};


static struct file_operations at24cxx_fops = {
    .owner  =   THIS_MODULE,
    .read   =   at24cxx_read,
    .write  =   at24cxx_write,
};
/******************************************************************************/

static int at24cxx_detect(struct i2c_adapter *adapter, int address, int kind)
{

    struct i2c_client *new_client;
    printk("at24cxx_detect\r\n");
    new_client  = kzalloc(sizeof(struct i2c_client),  GFP_KERNEL);
    new_client->addr    =   address;
    new_client->adapter =   adapter;
    new_client->driver  =   &at24cxx_driver;
    strcpy(new_client->name, "at24cxx");
    i2c_attach_client(new_client);

    
    major   =   register_chrdev(0, "at24cxx", &at24cxx_fops);
    cls     =   class_create(THIS_MODULE, "at24cxx");
    class_device_create(cls, NULL, MKDEV(major, 0), NULL, "at24cxx");
    
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

static ssize_t at24cxx_read(struct file *file, char __user *buf, size_t size, __kernel_loff_t *offset)
{
    return 0;
}

static ssize_t at24cxx_write(struct file *file, const char __user *buf, size_t size, __kernel_loff_t *offset)
{
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




