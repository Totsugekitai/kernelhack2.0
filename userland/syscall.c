#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SYS_HELLO (548)
#define SYS_HOOK (549)

asmlinkage int orig_write(int, const char *, int);

asmlinkage int hook(int fd, const char *buf, int len)
{
    printf("hook!!!!!!!\n");
    return 1;
}

int main(void)
{
    char *s = "syscall jikken ";
    unsigned long slen = sizeof("syscall jikken ");
    long err = 0;
    char buf[40] = {0};
    err = syscall(SYS_HELLO, s, buf, slen);
    printf(buf);
    printf("error no: %ld\n", err);

    err = syscall(SYS_HELLO, NULL, buf, slen);
    printf("error no: %ld\n", err);
    err = syscall(SYS_HELLO, s, NULL, slen);
    printf("error no: %ld\n", err);
    err = syscall(SYS_HELLO, NULL, NULL, slen);
    printf("error no: %ld\n", err);
    err = syscall(SYS_HELLO, s, buf, 0x10000000);
    printf("error no: %ld\n", err);

    printf("syscall hook\n");
}
