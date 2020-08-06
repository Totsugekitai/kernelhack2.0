#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/umh.h>
#include "my_module.h"

#define DRIVER_NAME "kitchen_timer"
#define MAX_MSG_LEN 240

static const unsigned int MINOR_BASE = 0;
static const unsigned int MINOR_NUM = 10;

static unsigned int kitchen_timer_major;
static struct cdev kitchen_timer_cdev;
static dev_t g_dev;

static struct kitchen_struct {
    unsigned long start_time;
    struct timer_list timer;
};

static struct kitchen_struct kitchen = {
                                        .start_time = 0,
                                        .timer.entry.next = NULL,
                                        .timer.entry.pprev = NULL,
                                        .timer.expires = 0,
                                        .timer.function = NULL,
                                        .timer.flags = 0,
};

/* 時間が経過したときに動作する関数 */
void kitchen_timer_alarm(struct timer_list *timer)
{
    printk("TIMER ALARM!!!\n");

    kitchen.start_time = 0;
    kitchen.timer.entry.next = NULL;
    kitchen.timer.entry.pprev = NULL;
    kitchen.timer.expires = 0;
    kitchen.timer.function = NULL;
    kitchen.timer.flags = 0;
}

static int kitchen_timer_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "kitchen_timer open start.\n");

    if (kitchen.timer.function == NULL) {
        kitchen.start_time = get_jiffies_64();
        kitchen.timer.entry.next = NULL;
        kitchen.timer.entry.pprev = NULL;
        kitchen.timer.expires = 0;
        kitchen.timer.function = kitchen_timer_alarm;
        kitchen.timer.flags = 0;
    }
    file->private_data = &kitchen;

    printk(KERN_INFO "kitchen_timer open end.\n");
    return 0;
}

static int kitchen_timer_close(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "kitchen_timer close.\n");
    return 0;
}

static ssize_t kitchen_timer_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
    ssize_t bytes = count < (MAX_MSG_LEN-(*offset)) ? count : (MAX_MSG_LEN-(*offset));

    printk(KERN_INFO "kitchen_timer read start.\n");

    struct kitchen_struct *k = (struct kitchen_struct *)filp->private_data;
    unsigned long current_jiff = get_jiffies_64();
    unsigned long start_jiff = k->start_time;
    unsigned long elapsed_jiff = current_jiff - start_jiff;
    unsigned long elapsed_time = elapsed_jiff / HZ;

    if (kitchen.timer.expires == 0) {
        char c[20] = {0};
        snprintf(c, sizeof("timer not set\n"), "timer not set\n");
        if (copy_to_user(buf, c, strlen(c))) {
            return -EFAULT;
        }
        printk(KERN_INFO "kitchen_timer read end.\n");
        printk(KERN_INFO "%ld\n", count);
        bytes = sizeof(c) - (MAX_MSG_LEN - (MAX_MSG_LEN - (*offset)));
        (*offset) += sizeof(c);
        return bytes;
    }
    char b[40] = {0};
    snprintf(b, sizeof(b), "%ld second passed\n", elapsed_time);
    if (copy_to_user(buf, b, strlen(b))) {
        return -EFAULT;
    }

    printk(KERN_INFO "kitchen_timer read end.\n");
    bytes = sizeof(b) - (MAX_MSG_LEN - (MAX_MSG_LEN - (*offset)));
    (*offset) += sizeof(b);
    return bytes;
}

static ssize_t kitchen_timer_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
    ssize_t bytes = count < (MAX_MSG_LEN-(*offset)) ? count : (MAX_MSG_LEN-(*offset));
    printk(KERN_INFO "kitchen_timer write start.\n");

    char mybuf[20];
    int i;
    for (i = 0; i < 20; i++) {
        mybuf[i] = '\0';
    }
    long setting_second = 0;
    struct kitchen_struct *k = (struct kitchen_struct *)filp->private_data;
    if (count > 20) {
        printk(KERN_ERR "too long seconds\n");
        return -EFAULT;
    }
    if (copy_from_user(mybuf, buf, count) != 0) {
        printk(KERN_ERR "error: copy_from_user() while kitchen_timer_write\n");
        return -EFAULT;
    }

    printk(KERN_INFO "mybuf: %s\n", mybuf);

    if (mybuf[strlen(mybuf) - 1] == '\n') {
        mybuf[strlen(mybuf) - 1] = '\0';
    }

    if (kstrtol(mybuf, 0, &setting_second) != 0) {
        printk(KERN_ERR "error: kstrtol() while kitchen_timer_write\n");
        return -EFAULT;
    }
    if (setting_second < 0) {
        printk(KERN_ERR "error: bad second setting\n");
        return -EFAULT;
    }

    k->start_time = get_jiffies_64();
    k->timer.entry.next = NULL;
    k->timer.entry.pprev = NULL;
    k->timer.expires = k->start_time + (setting_second * HZ);
    printk(KERN_INFO "expires: %ld\n", k->timer.expires);
    k->timer.function = kitchen_timer_alarm;
    k->timer.flags = 0;

    add_timer(&k->timer);
    printk(KERN_INFO "kitchen_timer write end.\n");
    bytes = sizeof(count) - (MAX_MSG_LEN - (MAX_MSG_LEN - (*offset)));
    (*offset) += sizeof(count);
    return count;
}

static long kitchen_timer_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    struct kitchen_values val;
    struct kitchen_struct *k = (struct kitchen_struct *)filp->private_data;
    unsigned long current_jiff = get_jiffies_64();
    unsigned long start_jiff = k->start_time;
    unsigned long remaining_jiff = k->timer.expires - current_jiff;
    unsigned long remaining_time = remaining_jiff / HZ;
    unsigned long elapsed_jiff = current_jiff - start_jiff;
    unsigned long elapsed_time = elapsed_jiff / HZ;
    unsigned long extend_time;
    printk(KERN_INFO "ioctl start\n");

    switch (cmd) {
    case KITCHEN_TIMER_EXTEND_VALUES:
        if (copy_from_user(&val, (void __user *)arg, sizeof(val))) {
            return -EFAULT;
        }
        if (k->timer.function) {
            extend_time = val.extend_time;
            mod_timer(&k->timer, k->timer.expires + (extend_time*HZ));
            printk(KERN_INFO "kitchen timer module extend time: %ld\n", extend_time);
        } else {
            printk(KERN_WARNING "no kitchen timer found\n");
        }
        break;
    case KITCHEN_TIMER_GET_VALUES:
        if (k->timer.function) {
            val.elapsed_time = elapsed_time;
            val.remaining_time = remaining_time;
            val.extend_time = 0;
            val.release_flag = 0;
        } else {
            val.elapsed_time = 0;
            val.remaining_time = 0;
            val.extend_time = 0;
            val.release_flag = 0;
        }
        printk(KERN_INFO "kitchen timer module get values\n");
        if (copy_to_user((void __user *)arg, &val, sizeof(struct kitchen_values))) {
            return -EFAULT;
        }
        break;
    case KITCHEN_TIMER_RELEASE_TIMER:
        if (copy_from_user(&val, (void __user *)arg, sizeof(val))) {
            return -EFAULT;
        }
        if (val.release_flag == 1) {
            if (k->timer.function) {
                del_timer(&k->timer);
                kitchen.start_time = 0;
                kitchen.timer.entry.next = NULL;
                kitchen.timer.entry.pprev = NULL;
                kitchen.timer.expires = 0;
                kitchen.timer.function = NULL;
                kitchen.timer.flags = 0;
                printk(KERN_INFO "kitchen timer module release timer\n");
            } else {
                printk(KERN_WARNING "kitchen timer module no such timer to release\n");
            }
        } else {
            printk(KERN_WARNING "kitchen timer module release flag is zero\n");
        }
        break;
    default:
        printk(KERN_WARNING "unsupported command %d\n", cmd);
        return -EFAULT;
    }
    printk(KERN_INFO "ioctl end\n");
    return 0;
}

const struct file_operations kitchen_fops = {
                                             .open = kitchen_timer_open,
                                             .release = kitchen_timer_close,
                                             .read = kitchen_timer_read,
                                             .write = kitchen_timer_write,
                                             .unlocked_ioctl = kitchen_timer_ioctl,
                                             .compat_ioctl = kitchen_timer_ioctl,
};

static int kitchen_timer_init(void)
{
    int alloc_err;
    int cdev_err;

    printk(KERN_INFO "kitchen_timer device init start.\n");

    alloc_err = alloc_chrdev_region(&g_dev, MINOR_BASE, MINOR_NUM, DRIVER_NAME);
    if (alloc_err != 0) {
        printk(KERN_ERR "error alloc_chrdev_region() = %d\n", alloc_err);
        return -EFAULT;
    }

    kitchen_timer_major = MAJOR(g_dev);

    cdev_init(&kitchen_timer_cdev, &kitchen_fops);

    cdev_err = cdev_add(&kitchen_timer_cdev, g_dev, MINOR_NUM);
    if (cdev_err != 0) {
        printk(KERN_ERR "error cdev_add() = %d\n", cdev_err);
        unregister_chrdev_region(g_dev, MINOR_NUM);
        return -EFAULT;
    }

    printk(KERN_INFO "kitchen_timer device init end.\n");
    return 0;
}

static void kitchen_timer_exit(void)
{
    cdev_del(&kitchen_timer_cdev);
    unregister_chrdev_region(g_dev, MINOR_NUM);
    printk(KERN_INFO "kitchen_timer device exit.\n");
}

module_init(kitchen_timer_init);
module_exit(kitchen_timer_exit);
