#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>

#include "ioctl_cmd.h"

int main()
{
    int fd;
    char Driver_version[5];
    char led[5] = "ON";

    fd = open("/dev/mychar",O_RDWR);
    if(fd < 0)
    {
        printf("failed to open file\n");
        return -1;
    }

    ioctl(fd,RESET_BUFFER);

    printf("reset\n");

    ioctl(fd,GET_DRIVER_VERSION,Driver_version);

    printf("Driver version is: %s\n",Driver_version);

   

    ioctl(fd,SET_LED_STATUS,led);

    close(fd);

    return 0;
}