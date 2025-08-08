#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/gpio.h>

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
static int led_init(void)
{
	printk(KERN_INFO "hello, led\n");
	gpioLedInit();
	gpioKeyInit();
	gpioLedSet(gpioKeyGet());
//	gpioLedFree();
	return 0;
}

static void led_exit(void)
{
	printk(KERN_INFO "Goodbye, led\n");
	gpioLedSet(gpioKeyGet());
	gpioLedFree();
	gpioKeyFree();
}

module_init(led_init);
module_exit(led_exit);

MODULE_AUTHOR("KCCI-AIOT"); 
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");
