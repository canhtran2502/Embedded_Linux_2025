#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_ITERATIONS  (10)
#define RESET_VALUE     (0)
#define CREATE_THREAD_SUCCESS (0)

int data = RESET_VALUE;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {

    for (int i=0; i < NUM_ITERATIONS; i++)
    {
        int random = rand() % 10 + 1; //Random value from 1-10
        pthread_mutex_lock(&mutex);

        data = random;
        printf("thread1 producer send, data[%d] = %d\n", i+1, data);

        pthread_cond_signal(&cond_var);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    pthread_exit(NULL); // exit
}

void* consumer(void* arg) {

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        pthread_mutex_lock(&mutex);
        while(data == RESET_VALUE) //Make sure producer set new value for data.
        {
            pthread_cond_wait(&cond_var, &mutex);
        }
        printf("thread2 consumer receive data = %d\n", data);
        printf("\n");

        data = RESET_VALUE; // Reset data.

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL); // exit
}

int main() {

    srand(time(NULL)); // Init for random number.

    pthread_t thread_producer;
    pthread_t thread_consumer;

    /* Initialize mutex, condition variable */
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    /* Create producer thread */
    if (pthread_create(&thread_producer, NULL, producer, NULL) != CREATE_THREAD_SUCCESS) {
        printf("Failed to create thread");
        exit(EXIT_FAILURE);
    }

    /* Create consumer thread */
    if (pthread_create(&thread_consumer, NULL, consumer, NULL) != CREATE_THREAD_SUCCESS) {
        printf("Failed to create thread");
        exit(EXIT_FAILURE);
    }

    /* Wait threads completed */
    pthread_join(thread_producer, NULL);
    pthread_join(thread_consumer, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);

    return 0;
}
