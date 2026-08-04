#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_t th1, th2;
pthread_mutex_t mutex;

int shared_data = 0;    // Shared among all threads

void *writer_thread(void *arg)
{
    for(int i = 1; i <= 5; i++)
    {
        pthread_mutex_lock(&mutex);

        shared_data = i * 10;
        printf("Writer: shared_data = %d\n", shared_data);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

void *reader_thread(void *arg)
{
    for(int i = 1; i <= 5; i++)
    {
        pthread_mutex_lock(&mutex);

        printf("Reader: shared_data = %d\n", shared_data);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&th1, NULL, writer_thread, NULL);
    pthread_create(&th2, NULL, reader_thread, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}