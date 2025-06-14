#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MODE    (1) // 0: orphan checking, 1: zombie checking

int main()
{
    pid_t pid;
    int status;
#if (MODE == 0)
    printf("Check orphan\n");
#else
    printf("Check zombie\n");
#endif
    pid = fork();
    if (pid == 0) //Child process.
    {
        printf("This is child process: PID = %d\n", getpid());
        printf("Child process: My parent is: %d\n", getppid());
    #if (MODE == 0)
        sleep(10);
        printf("Child process: Now, my parent is: %d\n", getppid());
    #endif
        exit(0);
    }
    else if (pid > 0) //Parent process.
    {
        printf("This is parent process. PID: %d, is waiting for child process PID: %d\n", getpid(), pid);
    #if (MODE == 0)
        sleep(3); //End earlier than child process to create orphan.
    #else
        while(1) //Do not call wait() to create zombie.
        {

        }
    #endif
    }
    else //return -1 if error.
    {
        printf("fork() unsuccessfully.\n");
    }

    return 0;
}