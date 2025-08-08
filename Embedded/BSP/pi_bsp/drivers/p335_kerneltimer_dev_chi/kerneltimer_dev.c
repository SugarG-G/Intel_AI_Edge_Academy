#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/types.h>

#define DEBUG 1

#define LEDKEY_DEV_NAME "kerneltimer"
#define LEDKEY_DEV_MAJOR 230

#define LED_OFF 0
#define LED_ON 1
#define GPIOCNT 8

static void kerneltimer_func(struct timer_list *t);
static void kerneltimer_registertimer(unsigned long timeover);

static unsigned int gpioLed[GPIOCNT] = {518, 519, 520, 521, 522, 523, 524, 525};
static unsigned int gpioKey[GPIOCNT] = {528, 529, 530, 531, 532, 533, 534, 535};
static int irqKey[GPIOCNT];

static int gpioLedInit(void);
static void gpioLedSet(long val);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static long gpioKeyGet(void);
static void gpioKeyFree(void);

static int openFlag = 0;

static int keyNum = 0;
static DEFINE_MUTEX(keyMutex);
static int timerVal = 100;
// module_param(timerVal, int, 0);
static unsigned char ledVal = 0;
// module_param(ledVal, byte, 0);

struct timer_list timerLed;

static irqreturn_t keyIsr(int irq, void *data)
{
    int i;
    for (i = 0; i < GPIOCNT; i++)
    {
        if (irq == irqKey[i])
        {
            if (mutex_trylock(&keyMutex) != 0)
            {
                keyNum = i + 1;
                mutex_unlock(&keyMutex);
                break;
            }
        }
    }
#if DEBUG
    printk("keyIsr() irq : %d, keyNum : %d\n", irq, keyNum);
#endif
    return IRQ_HANDLED;
}

static int irqKeyInit(void)
{
    int i;
    int ret = 0;
    for (i = 0; i < GPIOCNT; i++)
    {
        irqKey[i] = gpio_to_irq(gpioKey[i]);
        if (irqKey[i] < 0)
        {
            printk("Failed gpio_to_irq() gpio%d error\n", gpioKey[i]);
            return irqKey[i];
        }
#if DEBUG
        else
            printk("gpio_to_irq() gpio%d (irq%d) \n", gpioKey[i], irqKey[i]);
#endif
    }
    return ret;
}

static void irqKeyFree(void)
{
    int i;
    for (i = 0; i < GPIOCNT; i++)
    {
        free_irq(irqKey[i], NULL);
    }
}

static int ledkey_open(struct inode *inode, struct file *filp)
{

#if DEBUG
    int num0 = MAJOR(inode->i_rdev);
    int num1 = MINOR(inode->i_rdev);
    printk("call open -> major : %d\n", num0);
    printk("call open -> minor : %d\n", num1);
#endif

    if (openFlag)
        return -EBUSY;
    else
        openFlag = 1;

    if (!try_module_get(THIS_MODULE))
        return -ENODEV;

    return 0;
}

static loff_t ledkey_llseek(struct file *filp, loff_t off, int whence)
{
#if DEBUG
    printk("call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence);
#endif
    return 0x23;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    char kubf = 0;
    //	kbuf=gpioKeyGet();
    if (mutex_trylock(&keyMutex) != 0)
    {
        if (keyNum != 0)
        {
            kubf = (char)keyNum;
            keyNum = 0;
        }
        mutex_unlock(&keyMutex);
    }
#if 1
    put_user(kubf, buf);
#else
    int ret = copy_to_user(buf, &kbuf, sizeof(kbuf));
    if (ret < 0)
        return ret;
#endif

#if DEBUG
    printk("call read -> key : %#04x\n", kubf);
#endif

    return sizeof(kubf);
}

static ssize_t ledkey_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    // char kbuf;

#if 1
    get_user(ledVal, buf);
#else
    int ret;
    ret = copy_from_user(&kbuf, buf, sizeof(kbuf));
#endif

#if DEBUG
    printk("call write -> led : %#04x\n", ledVal);
#endif

    // gpioLedSet(kbuf);
    return sizeof(ledVal);
}

static long ledkey_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int err = 0;
    return err;
}

static int ledkey_release(struct inode *inode, struct file *filp)
{
    printk("call release \n");

    module_put(THIS_MODULE);
    openFlag = 0;
    return 0;
}

static void kerneltimer_registertimer(unsigned long timeover)
{
    timerLed.expires = get_jiffies_64() + timeover;
    timer_setup(&timerLed, kerneltimer_func, 0);
    add_timer(&timerLed);
}

static void kerneltimer_func(struct timer_list *t)
{
#if DEBUG
    printk("ledVal : %#04x\n", (unsigned int)ledVal);
#endif

    gpioLedSet(ledVal);
    ledVal = ~ledVal & 0xff;
    mod_timer(t, get_jiffies_64() + timerVal);
}

static int gpioLedInit(void)
{
    int i;
    int ret = 0;
    char gpioName[10];
    for (i = 0; i < GPIOCNT; i++)
    {
        sprintf(gpioName, "led%d", i);
        ret = gpio_request(gpioLed[i], gpioName);
        if (ret < 0)
        {
            printk("Failed request gpio%d error\n", gpioLed[i]);
            return ret;
        }
    }
    for (i = 0; i < GPIOCNT; i++)
    {
        ret = gpio_direction_output(gpioLed[i], LED_OFF);
        if (ret < 0)
        {
            printk("Failed direction_output gpio%d error\n", gpioLed[i]);
            return ret;
        }
    }
    return ret;
}
static void gpioLedSet(long val)
{
    int i;
    for (i = 0; i < GPIOCNT; i++)
    {
        gpio_set_value(gpioLed[i], ((val >> i) & 0x01));
    }
}
static void gpioLedFree(void)
{
    int i;
    for (i = 0; i < GPIOCNT; i++)
    {
        gpio_free(gpioLed[i]);
    }
}

static int gpioKeyInit(void)
{
    int i;
    int ret = 0;
    char gpioName[10];
    for (i = 0; i < GPIOCNT; i++)
    {
        sprintf(gpioName, "key%d", i);
        ret = gpio_request(gpioKey[i], gpioName);
        if (ret < 0)
        {
            printk("Failed request gpio%d error\n", gpioKey[i]);
            return ret;
        }
    }
    for (i = 0; i < GPIOCNT; i++)
    {
        ret = gpio_direction_input(gpioKey[i]);
        if (ret < 0)
        {
            printk("Failed direction_output gpio%d error\n", gpioKey[i]);
            return ret;
        }
    }
    return ret;
}
static long gpioKeyGet(void)
{
    int i;
    long key = 0;
    long ret;
    for (i = 0; i < GPIOCNT; i++)
    {
        //		key |= gpio_get_value(gpioKey[i]) << i;

        ret = gpio_get_value(gpioKey[i]);
        if (ret < 0)
            return ret;
        key |= ret << i;
    }
    return key;
}
static void gpioKeyFree(void)
{
    int i;
    for (i = 0; i < GPIOCNT; i++)
    {
        gpio_free(gpioKey[i]);
    }
}

struct file_operations ledkey_fops = {
    //    .owner    = THIS_MODULE,
    .open = ledkey_open,     .read = ledkey_read,
    .write = ledkey_write,   .unlocked_ioctl = ledkey_ioctl,
    .llseek = ledkey_llseek, .release = ledkey_release,
};

static int kerneltimer_init(void)
{
    int ret;
    char *irqName[GPIOCNT] = {
        "irqKey0", "irqKey1", "irqKey2", "irqKey3", "irqKey4", "irqKey5", "irqKey6", "irqKey7",
    };

#if DEBUG
    printk("timerVal : %d, sec : %d \n", timerVal, timerVal / HZ);
#endif

    mutex_init(&keyMutex);

    ret = gpioLedInit();
    if (ret < 0)
    {
        return ret;
    }
    ret = gpioKeyInit();
    if (ret < 0)
    {
        return ret;
    }

    ret = irqKeyInit();
    if (ret < 0)
        return ret;

    for (int i = 0; i < GPIOCNT; i++)
    {
        ret = request_irq(irqKey[i], keyIsr, IRQF_TRIGGER_RISING, irqName[i], NULL);
        if (ret < 0)
            return ret;
    }

    ret = register_chrdev(LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
    if (ret < 0)
        return ret;
    kerneltimer_registertimer(timerVal);

    return 0;
}

static void kerneltimer_exit(void)
{
    unregister_chrdev(LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME);

    irqKeyFree();
    gpioLedFree();
    gpioKeyFree();
    mutex_destroy(&keyMutex);
    if (timer_pending(&timerLed))
    {
        del_timer(&timerLed);
    }
}

module_init(kerneltimer_init);
module_exit(kerneltimer_exit);
MODULE_AUTHOR("KCCI-AIOT KSH");
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");