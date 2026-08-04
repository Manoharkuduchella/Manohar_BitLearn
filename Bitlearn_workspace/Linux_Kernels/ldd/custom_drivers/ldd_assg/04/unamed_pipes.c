#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_t th1,th2;
int pipefd[2];
int cnt=0;

void Thread1_handler_write(void *arg)
{
    printf("In thread1\n");
    *(int*)arg = 1;
    //close(pipefd[0]);// if closed reader cant access because globals(var) are shared bwteen threads
    write(pipefd[1],arg,4);
    perror("t1 pipe write");
    
    close(pipefd[1]);

}

void Thread2_handler_read(void *arg)
{
    int buff;
    printf("In thread2\n");
    //close(pipefd[1]);//if closed reader cant access because globals(var) are shared bwteen threads
    read(pipefd[0],&buff,4);
    perror("t2 pipe read");
    printf("read : %d\n",buff);

    close(pipefd[0]);
}

int main()
{

    pipe(pipefd);
    perror("pipe");

    if(pthread_create(&th1,NULL,(void * (*)(void*))Thread1_handler_write,&cnt))
    {
        printf("thread1 creation failed\n");
        return -1;
    }

    if(pthread_create(&th2,NULL,(void * (*)(void*))Thread2_handler_read,NULL))
    {
        printf("thread2 creation failed\n");
        return -1;
    }

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

}
