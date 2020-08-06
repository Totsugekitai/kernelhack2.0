#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_module.h"

void set_kitchen_values(struct kitchen_values *k, unsigned long e, unsigned long r, unsigned long x, int f)
{
    k->elapsed_time = e;
    k->remaining_time = r;
    k->extend_time = x;
    k->release_flag = f;
}

void print_kitchen_values(struct kitchen_values kval, char *str)
{
    printf("%s\n", str);
    printf("elapsed time   : %ld\n", kval.elapsed_time);
    printf("remaining time : %ld\n", kval.remaining_time);
    printf("extend time    : %ld\n", kval.extend_time);
    printf("release flag   : %d\n", kval.release_flag);
}

void test_ioctl(void)
{
    int fd = open("/dev/kitchen", O_RDWR);
    if (!fd) {
        fprintf(stderr, "file open error\n");
        exit(1);
    }

    write(fd, "10", 3);

    struct kitchen_values kval;
    set_kitchen_values(&kval, 0, 0, 0, 0);
    // get values
    if (ioctl(fd, KITCHEN_TIMER_GET_VALUES, &kval) < 0) {
        fprintf(stderr, "ioctl KITCHEN_TIMER_GET_VALUES error\n");
        exit(1);
    }
    print_kitchen_values(kval, "ioctl get values");
    // extend timer count
    set_kitchen_values(&kval, 0, 0, 5, 0);
    if (ioctl(fd, KITCHEN_TIMER_EXTEND_VALUES, &kval) < 0) {
        fprintf(stderr, "ioctl KITCHEN_TIMER_EXTEND_VALUES error\n");
        exit(1);
    }
    print_kitchen_values(kval, "ioctl extend values");
    sleep(13);
    char buf[100] = {'\0'};
    read(fd, buf, sizeof(buf));
    printf("%s\n", buf);
    // releaser timer
    set_kitchen_values(&kval, 0, 0, 0, 1);
    if (ioctl(fd, KITCHEN_TIMER_RELEASE_TIMER, &kval) < 0) {
        fprintf(stderr, "ioctl KITCHEN_TIMER_RELEASE_TIMER error\n");
        exit(1);
    }
    print_kitchen_values(kval, "ioctl release timer");

    close(fd);
}

void test_ioctl2(void)
{
    int fd = open("/dev/kitchen", O_RDWR);
    if (!fd) {
        fprintf(stderr, "file open error\n");
        exit(1);
    }

    write(fd, "10", 3);

    struct kitchen_values kval;
    set_kitchen_values(&kval, 0, 0, 0, 0);
    if (ioctl(fd, KITCHEN_TIMER_RELEASE_TIMER, &kval) < 0) {
        fprintf(stderr, "ioctl KITCHEN_TIMER_RELEASE_TIMER error\n");
        exit(1);
    }
    print_kitchen_values(kval, "ioctl release timer");

    close(fd);
}

int main(void)
{
    test_ioctl();
    test_ioctl2();
    return 0;
}

