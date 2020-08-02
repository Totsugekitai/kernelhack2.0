#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    printf("getppid: %d\n", getppid());
    return 0;
}
