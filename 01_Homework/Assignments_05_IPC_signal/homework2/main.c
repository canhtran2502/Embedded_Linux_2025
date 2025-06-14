#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define RESET_VALUE 	(0)
#define MAX_SECOND	 	(10)
int timer_count = RESET_VALUE;

void handle_sigalrm(int sig)
{
	timer_count++;
	printf("Timer: %d seconds\n", timer_count);
    if (timer_count < MAX_SECOND) {
        alarm(1); // Set alarm 1s again.
    } else {
        printf("Timer finished after 10 seconds.\n");
        exit(0); // Exit program.
    }
}
 
int main()
{
  	if (signal(SIGALRM, handle_sigalrm) == SIG_ERR) {
		fprintf(stderr, "Cannot handle SIGALRM\n");
		exit(EXIT_FAILURE);
	}

	alarm(1); // Set first alarm

	printf("Starting timer. Press Ctrl+C to exit early.\n");

	while (1)
	{
		// do nothing.
		sleep(1);
	}
}
