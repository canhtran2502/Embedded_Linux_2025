#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS (4)
#define RESET_VALUE (0)
#define CREATE_THREAD_SUCCESS (0)
#define TOTAL_INT   (1000000)
int sum = RESET_VALUE;  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* calculate_1(void* arg);
void* calculate_2(void* arg);
void* calculate_3(void* arg);
void* calculate_4(void* arg);

/* Function for thread */
void * (*function[NUM_THREADS])(void* arg) = {
    (void*)calculate_1,
    (void*)calculate_2,
    (void*)calculate_3,
    (void*)calculate_4,
};

void* calculate_1(void* arg) {
    int temp_sum = RESET_VALUE;
    int* array = (int*)arg;
    for (int i = 0; i < TOTAL_INT/4; i++) // Calculate sum for first 1/4 array.
    {
        temp_sum += array[i];
    }
    printf("thread 1: Sum = %d\n", temp_sum);
    pthread_mutex_lock(&mutex);
    sum += temp_sum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL); // exit
}

void* calculate_2(void* arg) {
    int temp_sum = RESET_VALUE;
    int* array = (int*)arg;
    for (int i = TOTAL_INT/4; i < TOTAL_INT/2; i++) // Calculate sum for second 1/4 array.
    {
        temp_sum += array[i];
    }
    printf("thread 2: Sum = %d\n", temp_sum);
    pthread_mutex_lock(&mutex);
    sum += temp_sum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL); // exit
}

void* calculate_3(void* arg) {
    int temp_sum = RESET_VALUE;
    int* array = (int*)arg;
    for (int i = TOTAL_INT/2; i < TOTAL_INT*3/4; i++) // Calculate sum for third 1/4 array.
    {
        temp_sum += array[i];
    }
    printf("thread 3: Sum = %d\n", temp_sum);
    pthread_mutex_lock(&mutex);
    sum += temp_sum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL); // exit
}
void* calculate_4(void* arg) {
    int temp_sum = RESET_VALUE;
    int* array = (int*)arg;
    for (int i = TOTAL_INT*3/4; i < TOTAL_INT; i++) // Calculate sum for fourth 1/4 array.
    {
        temp_sum += array[i];
    }
    printf("thread 4: Sum = %d\n", temp_sum);
    pthread_mutex_lock(&mutex);
    sum += temp_sum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL); // exit
}

int main() {

    srand(time(NULL));
    pthread_t threads[NUM_THREADS];  // Read thread ID array.
    int array[TOTAL_INT];


    int temp_sum = RESET_VALUE;
    /* Initialize data for array */
    for(int i=0; i<TOTAL_INT; i++)
    {
        array[i] = rand()%100;
        temp_sum += array[i];
    }
    printf("Sum of all array = %d\n",temp_sum);

    /* Initialize mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Create 4 threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, function[i], (void*)array) != CREATE_THREAD_SUCCESS) {
            printf("Failed to create thread\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait write threads completed */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Sum of total array from four threads: %d\n", sum);

    pthread_mutex_destroy(&mutex);

    return 0;
}
