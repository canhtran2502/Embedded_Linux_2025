#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE (10)
#define SOCK_PATH ("./sock_dgram")

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int fd, j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];

    memset(buf, 0, sizeof(buf));
    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    memset(&claddr, 0, sizeof(struct sockaddr_un));

    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        return 1;
    }

    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);
    if (bind(fd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1)
    {
        return 1;
    } 

    printf("start listening on server\n");
	
    len = sizeof(struct sockaddr_un);
    numBytes = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
    if (numBytes == -1)
    {
        return 1;
    }

    printf("Server received %ld bytes\n", (long) numBytes);

    for (j = 0; j < numBytes; j++)
    {
        buf[j] = toupper((unsigned char) buf[j]);
    }

    if (sendto(fd, buf, numBytes, 0, (struct sockaddr *) &claddr, len) != numBytes)
    {
        printf("sendto error\n");
    }

    close(fd);

	remove(SOCK_PATH);

    return 0;
}
