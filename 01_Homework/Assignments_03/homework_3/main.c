#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void handler_sigusr1(int signal) {
    printf("Child process: Receive SIGUSR1 signal (numer %d)\n", signal);
}

int main()
{
    pid_t pid;

    pid = fork();
    if (pid == 0) //Child process
    {
        printf("This is child process: PID = %d\n", getpid());

        signal(SIGUSR1, handler_sigusr1);

        while(1)
        {
            pause(); //Waiting for signal from parent process
        }
    }
    else if (pid > 0) //Parent process
    {
        printf("This is parent process. Child process: PID = %d\n", pid);

        sleep(2);
        kill(pid, SIGUSR1);

        printf("Parent process: Sent SIGUSR1\n");
    }
    else //return -1 if error.
    {
        printf("fork() unsuccessfully.\n");
    }

    return 0;
}