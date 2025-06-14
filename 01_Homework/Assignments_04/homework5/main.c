#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS_READ (5)
#define NUM_THREADS_WRITE (2)
#define RESET_VALUE (0)
#define CREATE_THREAD_SUCCESS (0)

int data = RESET_VALUE;  
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* reader(void* arg) {

    pthread_rwlock_rdlock(&rwlock);

    printf("Reader %d: data = %d\n", arg+1, data);

    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

void* writer(void* arg) {

    pthread_rwlock_wrlock(&rwlock);

    data++;
    printf("Writer %d: data incremented to %d\n", arg+1, data);

    pthread_rwlock_unlock(&rwlock);

    return NULL;
}
int main() {

    pthread_t threads_read[NUM_THREADS_READ];  // Read thread ID array.
    pthread_t threads_write[NUM_THREADS_WRITE];  // Write thread ID array.

    /* Initialize rwlock */
    pthread_rwlock_init(&rwlock, NULL);

    /* Create five read threads */
    for (int i = 0; i < NUM_THREADS_READ; i++) {
        if (pthread_create(&threads_read[i], NULL, reader, (void*)i) != CREATE_THREAD_SUCCESS) {
            printf("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    /* Create two write threads */
    for (int i = 0; i < NUM_THREADS_WRITE; i++) {
        if (pthread_create(&threads_write[i], NULL, writer, (void*)i) != CREATE_THREAD_SUCCESS) {
            printf("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait read threads completed */
    for (int i = 0; i < NUM_THREADS_READ; i++) {
        pthread_join(threads_read[i], NULL);
    }

    /* Wait write threads completed */
    for (int i = 0; i < NUM_THREADS_WRITE; i++) {
        pthread_join(threads_write[i], NULL);
    }


    printf("Final value of data: %d\n", data);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
