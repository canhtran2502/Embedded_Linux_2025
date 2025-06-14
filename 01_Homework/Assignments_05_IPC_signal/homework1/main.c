#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define RESET_VALUE 	(0)
#define MAX_INTERRUPT 	(3)
int count = RESET_VALUE;

void sig_handler(int num)
{
	count++;
	printf("\nSIGINT received: %d\n", count);
	if (count == MAX_INTERRUPT)
	{
		printf("MAX SIGINT received. Exit program\n");
		exit(0); //Exit process
	}
}
 
int main()
{
  	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		fprintf(stderr, "Cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

 	printf("Press Ctrl+C to send SIGINT. The program will exit after receiving it 3 times.\n");

	while (1)
	{
		// do nothing.
		sleep(1);
	}
}
