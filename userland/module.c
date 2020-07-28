#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd = open("/dev/kitchen", O_RDWR);
    write(fd, "10", 3);
    char buf[100];
    sleep(3);
    read(fd, buf, 100);
    //sleep(10);
    close(fd);
    return 0;
}

