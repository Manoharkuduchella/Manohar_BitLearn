#include<stdio.h>
#include<sys/stat.h>
#include<pthread.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

pthread_t th1,th2;
int fd;

void writer_thread(void *arg)
{
    int buff = 4;
    printf("in writer thread\n");
    write(fd,&buff,4);
    perror("write");
}

void reader_thread(void *arg)
{
    int buff;
    printf("in reader thread\n");
    read(fd,&buff,4);
    perror("read");

    printf("read buff : %d\n",buff);
}

int main()
{
    mkfifo("thread_fifo",0776);
    perror("mkfifo");

    fd = open("thread_fifo",O_RDWR|O_APPEND);
    if(fd < 0)
    {
        printf("open failed\n");
        return -1;
    }

    if(pthread_create(&th1,NULL,(void * (*)(void*))writer_thread,NULL))
    {
        printf("thread1 error\n");
        return -1;
    }
    
    if(pthread_create(&th2,NULL,(void * (*)(void*))reader_thread,NULL))
    {
        printf("thread2 error\n");
        return -1;
    }

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    close(fd);

}