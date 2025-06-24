#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>

#define ledkey_DEV_NAME    "ledkey_dev"
#define ledkey_DEV_MAJOR   230
static int ledkey_open(struct inode *inode, struct file *filp)
{
    int num = MINOR(inode->i_rdev);
    printk("call open -> minor : %d\n", num);
    num = MAJOR(inode->i_rdev);
    printk("call open -> major : %d\n", num);
    return 0;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    printk("call read -> buf : %08X, count : %08X\n", (unsigned int)buf, count);
    return 0x33;
}

static ssize_t ledkey_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    printk("call write -> buf : %08X, count : %08X\n", (unsigned int)buf, count);
    return 0x43;
}

static long ledkey_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("call ioctl -> cmd : %08X, arg : %08lX\n", cmd, (unsigned long)arg);
    return 0x53;
}

static int ledkey_release(struct inode *inode, struct file *filp)
{
    printk("call release \n");
    return 0;
}

struct file_operations ledkey_fops =
{
    .owner    = THIS_MODULE,
    .read     = ledkey_read,
    .write    = ledkey_write,
    .unlocked_ioctl = ledkey_ioctl,
    .open     = ledkey_open,
    .release  = ledkey_release,
};

static int ledkey_init(void)
{
    int result;
    printk("call ledkey_init \n");
    result = register_chrdev(ledkey_DEV_MAJOR, ledkey_DEV_NAME, &ledkey_fops);
    if(result < 0) return result;
    return 0;
}

static void ledkey_exit(void)
{
    printk("call ledkey_exit \n");
    unregister_chrdev(ledkey_DEV_MAJOR, ledkey_DEV_NAME);
}

module_init(ledkey_init);
module_exit(ledkey_exit);

MODULE_LICENSE("Dual BSD/GPL");
