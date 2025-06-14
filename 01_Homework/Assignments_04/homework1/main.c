#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS (2)
#define CREATE_THREAD_SUCCESS (0)

void* thread_function(void* arg);
void* thread_function(void* arg) {
    int thread_id = *((int*)arg);  // Get thread ID
    printf("Thread %d: Hello from thread\n", thread_id);
}

int main() {

    pthread_t threads[NUM_THREADS];  // Thread ID array.
    int thread_ids[NUM_THREADS];

    /* Create two threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;  // increase 
        if (pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]) != CREATE_THREAD_SUCCESS) {
            printf("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait two thread completed */ 
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");
    
    return 0;
}
