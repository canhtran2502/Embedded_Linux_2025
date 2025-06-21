#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>    
#include <netinet/in.h>     
#include <arpa/inet.h>
#include <unistd.h>

#define RESET_VALUE     (0)
#define RESET_CHAR      ('0')
#define TRUE            (1)
#define FAILURE         (-1)
#define NUM_ARG         (3)
#define BUFF_SIZE   (256)
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)
		
/* Chat function */
void chat_func(int server_fd)
{
    int numb_write, numb_read;
    char recvbuff[BUFF_SIZE];
    char sendbuff[BUFF_SIZE];
    while (1) 
    {
        memset(sendbuff, RESET_CHAR, BUFF_SIZE);
        memset(recvbuff, RESET_CHAR, BUFF_SIZE);
        printf("Please enter the message : ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        /* Send data to server */
        numb_write = write(server_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == FAILURE)
        {
            handle_error("write()");
        }

        if (strncmp("exit", sendbuff, 4) == 0) 
        {
            printf("Client exit ...\n");
            break;
        }
		
        /* Receive message */
        numb_read = read(server_fd, recvbuff, sizeof(recvbuff));
        if (numb_read < 0)
        {
            handle_error("read()");
        }

        if (strncmp("exit", recvbuff, 4) == 0) 
        {
            printf("Server exit ...\n");
            break;
        }

        printf("\nMessage from Server: %s\n",recvbuff);   
    }
    close(server_fd); /*close*/ 
}

int main(int argc, char *argv[])
{
    int portno = RESET_VALUE;
    int server_fd  = RESET_VALUE;
    struct sockaddr_in serv_addr;
	memset(&serv_addr, RESET_CHAR,sizeof(serv_addr));
	
    if (argc < NUM_ARG) {
        printf("command : ./stream_client <server address> <port number>\n");
        exit(1);
    }
    portno = atoi(argv[2]);
	
    /* Initialize server address */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(portno);
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == FAILURE)
    {
        handle_error("inet_pton()");
    }

    /* Create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == FAILURE)
    {
        handle_error("socket()");
    }

    /* Connect to server*/
    if (connect(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == FAILURE)
    {
        handle_error("connect()");
    }

    chat_func(server_fd);

    return 0;
}

