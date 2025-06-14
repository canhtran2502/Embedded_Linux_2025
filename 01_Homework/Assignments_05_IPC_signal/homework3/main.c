#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define RESET_VALUE 		(0)
#define MAX_SENDING_TIME 	(5)

void handle_sigusr1(int sig) {
    printf("Received signal from parent\n");
}
 
int main()
{
	int signal_count = RESET_VALUE;
	pid_t pid; 

	pid = fork(); 
	if (pid == 0) //Child process.
    {
        printf("This is child process: PID = %d\n", getpid());
		
		signal(SIGUSR1, handle_sigusr1);

		while (1)
		{
			// do nothing.
			sleep(1);
		}
    }
    else if (pid > 0) //Parent process.
    {
        while (signal_count < MAX_SENDING_TIME)
		{
			sleep(2);
			signal_count++;
			printf("Parent send signal %d\n", signal_count);
			kill(pid, SIGUSR1); //Send signal to child process.
		}

		kill(pid, SIGKILL);
		printf("Parent finished sending signals.\n");
	}
    else //return -1 if error.
    {
        printf("fork() unsuccessfully.\n");
    }

	return 0;
}
