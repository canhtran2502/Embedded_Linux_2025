#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) //Child process
    {
        printf("This is child process: PID = %d\n", getpid());
        // while(1) // Enable to check the case end abnormally with kill command "$kill -9 <pid>"
        // {
        // }
        exit(42);
    }
    else if (pid > 0) //Parent process
    {
        printf("This is parent process. PID: %d, is waiting for child process PID: %d\n", getpid(), pid);

        wait(&status);
        if (WIFEXITED(status)) 
        {
            int exit_code = WEXITSTATUS(status);
            printf("Parent process: Child process is ended normally with exit code = %d\n", exit_code);
        } 
        else
        {
            printf("Parent process: Child process is ended abnormally.\n");
        }
    }
    else //return -1 if error.
    {
        printf("fork() unsuccessfully.\n");
    }

    return 0;
}