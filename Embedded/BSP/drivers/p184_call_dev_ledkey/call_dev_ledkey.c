#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>

#define CALL_DEV_NAME    "calldev"
#define CALL_DEV_MAJOR   230

//#define key
#define GPIO_CNT 8
#define LED_ON 1
#define LED_OFF 0

//int gpioLed[GPIO_CNT] = {6,7,8,9,10,11,12,13};
int gpioLed[GPIO_CNT] = {518,519,520,521,522,523,524,525};
int gpioKey[GPIO_CNT] = {528,529,530,531,532,533,534,535};

int gpioLedInit(void);
void gpioLedSet(long );
void gpioLedFree(void);
int gpioKeyInit(void);
long  gpioKeyGet(void);
void gpioKeyFree(void);

int gpioLedInit(void)
{
	int ledrequest_ret = 0;
	int leddirection_ret = 0;
	char gpioLedName[10] = {0,};
	for(int i = 0; i < GPIO_CNT; i++)
	{
		sprintf(gpioLedName, "led%d", i);

		ledrequest_ret = gpio_request(gpioLed[i], gpioLedName);
		if(ledrequest_ret < 0)
		{
			printk("Failed request gpio %d error\n", gpioLed[i]);
			return ledrequest_ret;
		}

		leddirection_ret = gpio_direction_output(gpioLed[i], LED_OFF);
		if(leddirection_ret < 0)
		{
			printk("Failed request gpio %d error\n", gpioLed[i]);
			return leddirection_ret;
		}
	}
	return 0;
}

void gpioLedSet(long val)
{
	for(int i = 0; i < GPIO_CNT; i++)
	{
		gpio_set_value(gpioLed[i], ((val >> i) & 0x01));
	}
}

void gpioLedFree(void)
{
	for(int i = 0; i < GPIO_CNT; i++)
	{
		gpio_free(gpioLed[i]);
	}
}
int gpioKeyInit(void)
{
	int keyrequest_ret = 0;
	int keydirection_ret = 0;
	char gpioKeyName[10] = {0,};
	for(int i = 0; i < GPIO_CNT; i++)
	{
		sprintf(gpioKeyName, "key%d", i);
		keyrequest_ret = gpio_request(gpioKey[i], gpioKeyName);
		if(keyrequest_ret < 0)
		{
			printk("Failed request gpio %d error\n", gpioKey[i]);
			return keyrequest_ret;
		}

		keydirection_ret = gpio_direction_input(gpioKey[i]);
		if(keydirection_ret < 0)
		{
			printk("Failed request gpio %d error\n", gpioKey[i]);
			return keydirection_ret;
		}
	}
	return 0;
}

long gpioKeyGet(void)
{
    long temp = 0;
    for(int i = 0; i < GPIO_CNT; i++)
    {
        temp |= (gpio_get_value(gpioKey[i]) & 0x01) << i;
    }
	// if(temp != 0)
	// {
		return temp;
	// }
}

void gpioKeyFree(void)
{
	for(int i = 0; i < GPIO_CNT; i++)
	{
		gpio_free(gpioKey[i]);
	}
}

static int call_open(struct inode *inode, struct file *filp)
{
    int num = MINOR(inode->i_rdev);
    printk("call open -> minor : %d\n", num);
    num = MAJOR(inode->i_rdev);
    printk("call open -> major : %d\n", num);
    return 0;
}

static loff_t call_llseek(struct file *filp, loff_t off, int whence)
{
    printk("call llseek -> off : %08X, whence : %08X\n", (unsigned int)off, whence);
    return 0x23;
}

static ssize_t call_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    printk("call read -> buf : %08X, count : %08X\n", (unsigned int)buf, count);
	return gpioKeyGet();
}

static ssize_t call_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    printk("call write -> buf : %08X, count : %08X\n", *buf, count);
    gpioLedSet(*buf);
    return 0x43;
}

static long call_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("call ioctl -> cmd : %08X, arg : %08lX\n", cmd, (unsigned long)arg);
    return 0x53;
}

static int call_release(struct inode *inode, struct file *filp)
{
    printk("call release \n");
    return 0;
}

struct file_operations call_fops =
{
    .owner    = THIS_MODULE,
    .llseek   = call_llseek,
    .read     = call_read,
    .write    = call_write,
    .unlocked_ioctl = call_ioctl,
    .open     = call_open,
    .release  = call_release,
};

static int call_init(void)
{
    int result;
    printk("call call_init \n");
    result = register_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME, &call_fops);
    if(result < 0) return result;

    gpioLedInit();
	gpioKeyInit();

    return 0;
}

static void call_exit(void)
{
    printk("call call_exit \n");
    unregister_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME);

	gpioLedFree();
	gpioKeyFree();
}

module_init(call_init);
module_exit(call_exit);

MODULE_LICENSE("Dual BSD/GPL");
