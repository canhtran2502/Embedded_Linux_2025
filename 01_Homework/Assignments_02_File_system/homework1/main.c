#include "stdio.h"
#include "string.h"
#include <fcntl.h>
#include "unistd.h"

#define PATH_FILE           ("./text.txt")
#define ORIGINAL_CONTENT    ("Hello World!") //Write content before using lseek() API.
#define INSERT_CONTENT      ("Seek_content") //Write content after using lseek() API.
#define ENABLE_APPEND       (1) //Option checking O_APPEND flag with open() API. Disable: 0, Enable: 1.
#define ERROR          (-1)

int main()
{
    int fd = 0;
    int write_bytes = 0;
    char* w_buffer = ORIGINAL_CONTENT;
    const char* pathfile = PATH_FILE;

#if (ENABLE_APPEND == 1)
    fd = open(pathfile, O_RDWR | O_CREAT | O_APPEND, 0664);
#else
    fd = open(pathfile, O_RDWR | O_CREAT, 0664);
#endif
    if (ERROR == fd)
    {
        printf("Open file %s failed \n",PATH_FILE);
        return 1;
    }
    else
    {
        printf("Open file %s successfully with file id %d \n",pathfile, fd);

        write_bytes = write(fd, w_buffer, strlen(w_buffer));
        if ( ERROR == write_bytes)
        {
            printf("Write to file failed\n");
            close(fd);
            return 1;
        }
        else
        {
            printf("Write %d bytes to file %s\n", write_bytes, pathfile);
        }
    }

    printf("Checking with lseek() API\n");
    if ( ERROR == lseek(fd, 2, SEEK_SET))
    {
        printf("lseek API failed\n");
    }

    w_buffer = INSERT_CONTENT;
    write_bytes = write(fd, w_buffer, strlen(w_buffer));
    if (ERROR == write_bytes)
    {
        printf("Write to file failed\n");
        close(fd);
        return 1;
    }
    else
    {
        printf("Write %d bytes to file %s\n", write_bytes, pathfile);
    }

    close(fd);

    return 0;
}