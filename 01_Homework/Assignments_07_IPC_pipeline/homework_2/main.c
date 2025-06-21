#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int pipefd1[2];
    int pipefd2[2];
    pid_t pid[0];

    if ((pipe(pipefd1) == -1) || (pipe(pipefd2) == -1))
    {
        printf("Create pipe ununsuccessfully.\n");
        return 1;
    }

    pid[0] = fork();
    if (pid[0] == 0) //Child process 1
    {
        printf("This is child process 1: PID = %d\n", getpid());

        close(pipefd1[1]); //Close Write port 1.
        close(pipefd2[0]); //Close Read port 2.

        char buffer[100];

        read(pipefd1[0], buffer, sizeof(buffer));
        printf("Child 1: Received from pipeline: %s\n", buffer);

        strcat(buffer, " World !!!!");
        write(pipefd2[1], buffer, strlen(buffer));

        close(pipefd1[0]); //Close Read port 1.
        close(pipefd2[1]); //Close Write port 2.

        exit(EXIT_SUCCESS);
    }
    else if (pid[0] > 0) //Parent process
    {
        pid[1] = fork();

        if (pid[1] == 0) //Child process 2
        {
            printf("This is child process 2: PID = %d\n", getpid());

            close(pipefd2[1]); //Close Write port 2.

            char buffer[100];

            read(pipefd2[0], buffer, sizeof(buffer));
            printf("Child 2: Received from pipeline: %s\n", buffer);

            close(pipefd2[0]); //Close Read port 2.

            exit(EXIT_SUCCESS);
        }
        else if (pid[1] > 0) //Parent process
        {
            close(pipefd1[0]); //Close Write port.

            const char *msg = "Hello";
            write(pipefd1[1], msg, strlen(msg));

            close(pipefd1[1]); //Close Write port.

            wait(NULL); // Wait child 1
            wait(NULL); // Wait child 2
        }
        else //return -1 if error.
        {
            printf("fork() unsuccessfully.\n");
            return 1;
        }
    }
    else //return -1 if error.
    {
        printf("fork() unsuccessfully.\n");
        return 1;
    }

    return 0;
}