#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ioctl_cmd.h"


int main()
{
    int fd;
    fd = open("/dev/ch_device",O_APPEND);
    if(fd < 0)
    {
        perror("open");
        exit(2);
    }


    ioctl(fd,GET_BUFFER_LENGTH,0);
    perror("ioctl:GET_BUFFER_LENGTH");

    ioctl(fd,CLR_BUFFER);
    perror("ioctl:CLR_BUFFER");

    ioctl(fd,FILL_BUFFER,0);
    perror("ioctl:FILL_BUFFER");

    ioctl(fd,5);
    perror("ioctl:5");

    close(fd);
    return 0;
}