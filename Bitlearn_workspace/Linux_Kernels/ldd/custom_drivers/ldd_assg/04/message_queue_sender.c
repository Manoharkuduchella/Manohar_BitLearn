#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    mqd_t mq;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_curmsgs = 0;

    mq = mq_open("/myqueue",
                 O_CREAT | O_RDWR,
                 0666,
                 &attr);

    if(mq == -1)
    {
        perror("mq_open");
        exit(1);
    }

    char msg[] = "Hello from Process A";

    if(mq_send(mq, msg, strlen(msg)+1, 1) == -1)
        perror("mq_send");

    printf("Sent: %s\n", msg);

    mq_close(mq);

    return 0;
}