#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>

int main()
{
    mqd_t mq;

    mq = mq_open("/myqueue", O_RDONLY);

    if(mq == -1)
    {
        perror("mq_open");
        exit(1);
    }

    char buffer[100];
    unsigned int priority;

    if(mq_receive(mq,
                  buffer,
                  sizeof(buffer),
                  &priority) == -1)
    {
        perror("mq_receive");
        exit(1);
    }

    printf("Received: %s\n", buffer);
    printf("Priority: %u\n", priority);

    mq_close(mq);
    mq_unlink("/myqueue");

    return 0;
}