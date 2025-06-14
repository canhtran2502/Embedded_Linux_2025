#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TOTAL_NUM         (100)
#define RESET_VALUE         (0)
#define CREATE_THREAD_SUCCESS (0)

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

void* odd_counter(void* arg) {

    int *data = (int*) arg;
    int total_odd = RESET_VALUE;
    for (int i=0; i < TOTAL_NUM; i++)
    {
        if ((data[i] % 2) != 0)  //Check odd number
        {
            total_odd++;
        }
    }

    printf("Total odd number: %d \n", total_odd);

    return NULL;
}

void* even_counter(void* arg) {

    int *data = (int*) arg;
    int total_even = RESET_VALUE;
    for (int i=0; i < TOTAL_NUM; i++)
    {
        if ((data[i] % 2) == 0) //Check even number
        {
            total_even++;
        }
    }

    printf("Total even number: %d \n", total_even);

    return NULL;
}

int main() {

    srand(time(NULL)); // Init for random number.

    int data[TOTAL_NUM];
    pthread_t thread_odd_counter;
    pthread_t thread_even_counter;

    for (int i=0; i< TOTAL_NUM; i++) //Create random number.
    {
        data[i] = rand()%100 + 1;
    }

    /* Create odd counter thread */
    if (pthread_create(&thread_odd_counter, NULL, odd_counter, data) != CREATE_THREAD_SUCCESS) {
        printf("Failed to create thread");
        exit(EXIT_FAILURE);
    }

    /* Create even counter thread */
    if (pthread_create(&thread_even_counter, NULL, even_counter, data) != CREATE_THREAD_SUCCESS) {
        printf("Failed to create thread");
        exit(EXIT_FAILURE);
    }

    /* Wait threads completed */
    pthread_join(thread_odd_counter, NULL);
    pthread_join(thread_even_counter, NULL);

    return 0;
}
