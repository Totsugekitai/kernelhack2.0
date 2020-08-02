#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/errno.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/kallsyms.h>
#include <asm/special_insns.h>

MODULE_AUTHOR("Totsugekitai");
MODULE_LICENSE("GPL");

int (*orig_write)(int, const void *, int);
static unsigned long *syscall_table;
static unsigned long orig_cr0;

#define unprotect_memory()                                             \
	({                                                                 \
		orig_cr0 = read_cr0();                                         \
		write_cr0(orig_cr0 & (~0x10000));                              \
	});

#define protect_memnry()                        \
    ({                                          \
        write_cr0(orig_cr0);                    \
    });


void get_syscall_table_address(void)
{
    syscall_table = (unsigned long *)(unsigned long)kallsyms_lookup_name("sys_call_table");
}

void hooking_syscall(void *hook_addr, unsigned short syscall_offset, unsigned long *sys_call_table)
{
    unprotect_memory();
    sys_call_table[syscall_offset] = (unsigned long)hook_addr;
    protect_memnry();
}

void unhooking_syscall(void *orig_addr, unsigned short syscall_offset)
{
    unprotect_memory();
    syscall_table[syscall_offset] = (unsigned long)orig_addr;
    protect_memnry();
}

asmlinkage int hooked_write(int fd, const char *buf, int num)
{
    printk("write hook!!!!!!!\n");
    return orig_write(fd, buf, num);
}

static int __init hook_write_init(void)
{
    printk(KERN_INFO "syscall_hook module init\n");
    get_syscall_table_address();
    orig_write = (void *)syscall_table[__NR_write];
    hooking_syscall(hooked_write, __NR_write, syscall_table);
    return 0;
}

static void __exit hook_write_exit(void)
{
    unhooking_syscall(orig_write, __NR_write);
    printk(KERN_INFO "syscall_hook module exit\n");
}

module_init(hook_write_init);
module_exit(hook_write_exit);

