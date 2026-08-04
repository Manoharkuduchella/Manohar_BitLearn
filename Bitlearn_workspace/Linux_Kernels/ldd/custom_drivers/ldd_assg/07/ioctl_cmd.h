#include <linux/ioctl.h>

#define MAGIC_NUMBER 0xF1

#define RESET_BUFFER _IO(MAGIC_NUMBER, 1)

#define GET_DRIVER_VERSION _IOR(MAGIC_NUMBER, 2, char )//_IOR(type,nr,size)

#define SET_LED_STATUS _IOW(MAGIC_NUMBER, 3, char)//_IOW(type,nr,size)
