#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/errno.h>
#include <linux/string.h>
#include <linux/uaccess.h>

#define HELLO_MAX_LEN (0x100)

long do_sys_hello(const char __user *readbuf, char __user *writebuf, unsigned long len)
{
    int slen;
    char buf[HELLO_MAX_LEN];
    long retval;

    slen = sizeof("syscall hello!!\n");
    if (!access_ok(readbuf, len)) {
        return -EINVAL;
    }
    if (!access_ok(writebuf, len + slen)) {
        return -EINVAL;
    }
    if (len > HELLO_MAX_LEN) {
        return -EINVAL;
    }

    if (copy_from_user(buf, readbuf, len)) {
        return -EFAULT;
    }
    strcat(buf, "syscall hello!!\n");
    retval = len + slen;
    if (copy_to_user(writebuf, buf, retval)) {
        return -EFAULT;
    }
    return retval;
}

SYSCALL_DEFINE3(hello, const char __user *, readbuf, char __user *, writebuf, unsigned long, len)
{
    return do_sys_hello(readbuf, writebuf, len);
}

