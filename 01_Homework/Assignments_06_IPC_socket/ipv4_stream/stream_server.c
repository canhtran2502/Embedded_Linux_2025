#include <stdio.h>
#include <string.h>
#include <sys/socket.h>     // Contain necessary struct for socket
#include <netinet/in.h>     // Contain const, struct when using address in internet.
#include <stdlib.h>
#include <unistd.h>

#define RESET_VALUE     (0)
#define RESET_CHAR      ('0')
#define TRUE            (1)
#define LISTEN_BACKLOG  (50)
#define BUFF_SIZE       (256)
#define NUM_ARG         (2)
#define FAILURE         (-1)
#define CREATE_THREAD_SUCCESS (0)
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* Chat func */
void* chat_func(int new_socket_fd)
{       
    int numb_read = RESET_VALUE;
    int numb_write = RESET_VALUE;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];
	
    while (TRUE) 
    {        
        memset(sendbuff, RESET_CHAR, BUFF_SIZE);
        memset(recvbuff, RESET_CHAR, BUFF_SIZE);

        /* Read data from socket */
        numb_read = read(new_socket_fd, recvbuff, BUFF_SIZE);
        if(numb_read == FAILURE)
        {
            handle_error("read()");
        }

        if (strncmp("exit", recvbuff, strlen("exit")) == 0) 
        {
            system("clear");
            break;
        }

        printf("\nMessage from Client: %s\n", recvbuff);

        /* Response from keyboard */
        printf("Please respond the message : ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        /* Write data */
        numb_write = write(new_socket_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == FAILURE)
        {
            handle_error("write()");
        }
        
        if (strncmp("exit", sendbuff, 4) == 0) 
        {
            system("clear");
            break;
        }

        sleep(1);
    }

    close(new_socket_fd);
}

int main(int argc, char *argv[])
{
    int port_no = RESET_VALUE;
    int len = RESET_VALUE;
    int opt = RESET_VALUE;
    int server_sd = RESET_VALUE;
    int new_socket_fd = RESET_VALUE;

    struct sockaddr_in  serv_addr, client_addr;

    /* Read port number */
    if (argc < NUM_ARG)
    {
        printf("No port provided\ncommand: ./stream_server <port number>\n");
        exit(EXIT_FAILURE);
    }
    
    port_no = atoi(argv[1]);

    memset(&serv_addr, RESET_VALUE, sizeof(struct sockaddr_in));
    memset(&serv_addr, RESET_VALUE, sizeof(struct sockaddr_in));

    /* Create socket */
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == FAILURE)
    {
        handle_error("socket()");
    }

    /* Initialize server address */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr =  INADDR_ANY; //inet_addr("192.168.5.128"); //INADDR_ANY

    /* Link socket with server address */
    if (bind(server_sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == FAILURE)
    {
        handle_error("bind()");
    }

    /* Listen  */
    if (listen(server_sd, LISTEN_BACKLOG) == -1)
    {
        handle_error("listen()");
    }

    len = sizeof(client_addr);

    while (TRUE) 
    {
        printf("Server is listening at port : %d \n....\n",port_no);

        new_socket_fd  = accept(server_sd, (struct sockaddr*)&client_addr, (socklen_t *)&len); 
        if (new_socket_fd == RESET_VALUE)
        {
            handle_error("accept()");
        }

        system("clear"); // Clear terminal
        
        printf("Server : got connection \n");

        chat_func(new_socket_fd);
    }

    return 0;
}