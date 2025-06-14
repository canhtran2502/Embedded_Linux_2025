#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/select.h>

#define RESET_VALUE 		(0)
#define TRUE                (1)
#define MAX_SENDING_TIME 	(5)

void handle_sigint(int sig) {
    printf("SIGINT received.\n");
}

void handle_sigterm(int sig) {
    printf("Received SIGTERM, exiting\n");
    exit(0);
}

int main()
{
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);

    fd_set readfds; // File descriptor to select
    char buffer[100]; // Buffer store data from keyboard input.

    printf("Press Ctrl+C to send SIGINT or use kill <pid> to send SIGTERM.\n");

    while (TRUE) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds); // Add stdin to readfds

        int activity = select(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL);

        /* Check data from keyboard */
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("You entered: %s", buffer);
            }
        }
    }

	return 0;
}
