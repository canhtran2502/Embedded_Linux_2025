#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS (3)
#define INCREMENTS  (1000000)
#define RESET_VALUE (0)
#define CREATE_THREAD_SUCCESS (0)

int counter = RESET_VALUE;  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* increment_counter(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        /* Lock mutex */
        pthread_mutex_lock(&mutex);
        counter++;  // 
        /* Unlock mutex */
        pthread_mutex_unlock(&mutex);
    }
}

int main() {

    pthread_t threads[NUM_THREADS];  // Thread ID array.

    /* Initialize mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Create three threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != CREATE_THREAD_SUCCESS) {
            printf("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait three threads completed */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}
