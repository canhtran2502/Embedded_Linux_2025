#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid == 0) //Child process
    {
        printf("This is child process: PID = %d\n", getpid());
    }
    else if (pid > 0) //Parent process
    {
        printf("This is parent process. Child process: PID = %d\n", pid);
    }
    else //return -1 if error.
    {
        printf("fork() unsuccessfully.\n");
    }

    return 0;
}