#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
    {
        printf("Create pipe ununsuccessfully.\n");
        return 1;
    }

    pid = fork();
    if (pid == 0) //Child process
    {
        printf("This is child process: PID = %d\n", getpid());

        close(pipefd[1]); //Close Write port.

        char buffer[100];

        read(pipefd[0], buffer, sizeof(buffer));
        printf("Received from pipeline: %s\nTotal character: %ld\n", buffer, strlen(buffer));

        close(pipefd[0]); //Close Read port.

    }
    else if (pid > 0) //Parent process
    {
        printf("This is parent process. Child process: PID = %d\n", pid);

        close(pipefd[0]); //Close Write port.

        const char *msg = "Hello";
        write(pipefd[1], msg, strlen(msg));

        close(pipefd[1]); //Close Write port.
    }
    else //return -1 if error.
    {
        printf("fork() unsuccessfully.\n");
        return 1;
    }

    return 0;
}