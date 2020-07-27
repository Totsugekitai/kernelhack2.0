#ifndef MY_MODULE_H_
#define MY_MODULE_H_

#include <linux/ioctl.h>

struct kitchen_values {
    unsigned long elapsed_time;
    unsigned long remaining_time;
    unsigned long extend_time;
    int release_flag;
};

#define KITCHEN_TIMER_IOC_TYPE 'K'

#define KITCHEN_TIMER_EXTEND_VALUES _IOW(KITCHEN_TIMER_IOC_TYPE, 1, struct kitchen_values)

#define KITCHEN_TIMER_GET_VALUES _IOR(KITCHEN_TIMER_IOC_TYPE, 2, struct kitchen_values)

#define KITCHEN_TIMER_RELEASE_TIMER _IOW(KITCHEN_TIMER_IOC_TYPE, 3, struct kitchen_values)

#endif
