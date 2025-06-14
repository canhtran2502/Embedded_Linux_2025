#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define RESET_VALUE 		(0)
#define MAX_SENDING_TIME 	(5)

void handle_sigtstp(int sig) {
    printf("SIGTSTP ignored\n");
}
 
int main()
{
	signal(SIGTSTP, handle_sigtstp);

	printf("Press Ctrl+Z to test SIGTSTP.\n");

    while (1) {
        sleep(1);
        printf("Program are still running\n");
    }

	return 0;
}
