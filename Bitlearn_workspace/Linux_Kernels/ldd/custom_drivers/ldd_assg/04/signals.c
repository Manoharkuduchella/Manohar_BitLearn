#include<stdio.h>
#include<signal.h>
#include<pthread.h>

typedef void (*sighandler_t)(int);

pthread_t th1,th2;

void sig_int_handler(int signum)
{
    if(signum == SIGINT)
    {
        printf("thread1 : SIGINT received\n");
    }else if(signum == SIGTERM)
    {
        printf("thread2 : SIGTERM recevied\n");
    }
}

void *Sig_Int_Thread_handler(void *arg)
{
    sighandler_t ret = signal(SIGINT,sig_int_handler);
    if(ret == SIG_ERR)
        printf("thread1 sig error");

}


void *Sig_Term_Thread_handler(void *arg)
{
    
    sighandler_t ret = signal(SIGTERM,sig_int_handler);
    if(ret == SIG_ERR)
        printf("thread2 sig error");
}

int main()
{

    if(pthread_create(&th1,NULL,(void * (*)(void*))Sig_Int_Thread_handler,NULL))
    {
        printf("Thread1 creation failed\n");
        return -1;
    }

    if(pthread_create(&th2,NULL,(void * (*)(void*))Sig_Term_Thread_handler,NULL))
    {
        printf("Thread2 creation failed\n");
        return -1;
    }

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    while(1)
    {
        printf("\rrunning...");
    }
    return 0;
}