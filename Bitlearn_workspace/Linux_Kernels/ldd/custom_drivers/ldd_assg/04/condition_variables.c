#include<stdio.h>
#include<pthread.h>

pthread_t th1,th2,th3,th4,th5;

pthread_mutex_t mutex;
pthread_cond_t condition;

int shared_resource = 1;

void Increment_2_thread1(void *arg)
{
    int cnt = 2;
    while(cnt)
    {
        pthread_mutex_lock(&mutex);
        shared_resource += 2;
        printf("Inc 2 - shared_resource: %d\n",shared_resource);
        cnt--;
        pthread_mutex_unlock(&mutex);
    }
}

void Increment_4_thread2(void *arg)
{
    int cnt = 2;
    while(cnt)
    {
        pthread_mutex_lock(&mutex);
        shared_resource += 4;
        printf("Inc 4 - shared_resource: %d\n",shared_resource);
        cnt--;
        pthread_mutex_unlock(&mutex);
    }

}

void Decrement_1_thread3(void *arg)
{
    pthread_mutex_lock(&mutex);
    shared_resource -= 1;
    printf("Dec 1 - shared_resource: %d\n",shared_resource);
    pthread_mutex_unlock(&mutex);
}

void validate_less_5_thread4(void *arg)
{
    pthread_mutex_lock(&mutex);

    while((shared_resource <= 5))
    {
        printf("Waiting..\n");
        pthread_cond_wait(&condition,&mutex);
        
    }   

    printf("shared_resource > 5 : %d\n",shared_resource);

    pthread_mutex_unlock(&mutex);

}

void validate_greater_5_thread5(void *arg)
{
    pthread_mutex_lock(&mutex);

    if(shared_resource > 5)
    {
        pthread_cond_signal(&condition);
        printf("Signaled: %d\n",shared_resource);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    if(pthread_mutex_init(&mutex,NULL))
    {
        printf("pthread_mutex_init failed\n");
        return -1;
    }

    if(pthread_cond_init(&condition,NULL))
    {
        printf("pthread_cond_init failed\n");
        return -1;
    }

    if(pthread_create(&th1,NULL,(void * (*)(void*))Increment_2_thread1,NULL))
    {
        printf("thread1 error\n");
        return -1;
    }
    
    if(pthread_create(&th2,NULL,(void * (*)(void*))Increment_4_thread2,NULL))
    {
        printf("thread2 error\n");
        return -1;
    }

    if(pthread_create(&th3,NULL,(void * (*)(void*))Decrement_1_thread3,NULL))
    {
        printf("thread2 error\n");
        return -1;
    }

        if(pthread_create(&th4,NULL,(void * (*)(void*))validate_less_5_thread4,NULL))
    {
        printf("thread4 error\n");
        return -1;
    }

    if(pthread_create(&th5,NULL,(void * (*)(void*))validate_greater_5_thread5,NULL))
    {
        printf("thread5 error\n");
        return -1;
    }

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);
    pthread_join(th5,NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    return 0;
}