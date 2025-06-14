#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("./exam <1 or 2> - (1: ls command); (2:date command)\n");
        return 1;
    }

    pid_t pid;

    pid = fork();
    if (pid == 0) 
    {
        printf("Child process: PID = %d\n", getpid());

        if (*argv[1] == '1') {
            execlp("ls", "ls", "-l", NULL);  // Run ls -l command
        } else if (*argv[1] == '2') {
            execlp("date", "date", NULL);   // Run date command
        } else {
            printf("Invalid input: %s\n", argv[1]);
            exit(1);
        }
        printf("exec unsuccessfully\n");
        exit(1);
    } 
    else if (pid > 0) 
    {
        printf("This is parent process. Child process: PID = %d\n", pid);
    }
    else
    {
        printf("Fork unsuccessfully\n");
        return 1;
    }

    return 0;
}
