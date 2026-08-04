#ifndef __TEMPSENSOR_IOCTL_H__
#define __TEMPSENSOR_IOCTL_H__

#include <linux/ioctl.h>

#define TEMPSENSOR_MAGIC    'T'


struct temp_limits {
    int low_limit;
    int high_limit;
};


#define TEMPSENSOR_SET_LIMITS \
        _IOW(TEMPSENSOR_MAGIC, 1, struct temp_limits)

#define TEMPSENSOR_GET_LIMITS \
        _IOR(TEMPSENSOR_MAGIC, 2, struct temp_limits)

#endif