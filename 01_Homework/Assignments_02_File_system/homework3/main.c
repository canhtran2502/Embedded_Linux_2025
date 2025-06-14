#include "stdio.h"
#include <time.h>
#include <stdint.h>
#include <sys/stat.h>

#define NUM_CMD     (1) //Input file name need to be checked.
#define SUCCESS     (0)
#define ERROR       (-1)

int main(int argc, char *argv[])
{
    if (argc != (NUM_CMD + 1))
    {
        printf("Usage: %s <filename> \n", argv[0]);
        return 1;
    }

    struct stat sb;
    int err = SUCCESS;
    const char* file_name = argv[1];
    err = lstat(file_name, &sb);
    if (ERROR == err)
    {
        printf("get status from file %s failed \n",file_name);
        return ERROR;
    }
    else
    {
        printf("get status from file %s successfully \n",file_name);
    }

    printf("File Tye: ");
    switch (sb.st_mode & S_IFMT)
    {
        case S_IFBLK:
            printf("block device\n");
            break;
        case S_IFCHR:
            printf("character device\n");
            break;
        case S_IFDIR:
            printf("directory\n");
            break;
        case S_IFIFO:
            printf("pipeline/FIFO\n");
            break;
        case S_IFREG:
            printf("regular file\n");
            break;
        case S_IFLNK:
            printf("link file\n");
            break;
        case S_IFSOCK:
            printf("socket file\n");
            break;
        default:
            printf("unknown\n");
    }

    printf("File name: %s\n", file_name);
    printf("File size: %jd (unit: byte)\n", (intmax_t)sb.st_size);
    printf("Last data modification timestamp: %s \n", ctime(&sb.st_mtim.tv_sec));
    
    return 0;
}


