#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <fcntl.h>
#include "unistd.h"

#define NUM_CMD     (4)
#define SUCCESS     (0)
#define ERROR       (-1)

typedef struct 
{
    int num_bytes;
    const char* pathfile;
    char* action;
    char* w_buffer;
    char* r_buffer;
} s_file_param_t;

int init_param(s_file_param_t* param, char *argv[]);
int read_write_op(s_file_param_t* param, int fd);
int open_file(s_file_param_t* param, int* fd);
void deinit_param(s_file_param_t* param);

int main(int argc, char *argv[])
{
    if (argc != (NUM_CMD + 1))
    {
        printf("Usage: %s filename num-bytes [r/w] \"data\"\n", argv[0]);
        return 1;
    }

    int err = ERROR;
    int fd = 0;

    s_file_param_t param;
    err = init_param(&param,argv);
    if (err != SUCCESS)
    {
        printf("Please input again\n");
        return 1;
    }

    err = open_file(&param, &fd);
    if (err != SUCCESS)
    {
        printf("Cannot open file. Please try again\n");
        return 1;
    }

    err = read_write_op(&param,fd);
    if (err != SUCCESS)
    {
        printf("Read/Write issue. Please try again\n");
        return 1;
    }

    err = close(fd);
    if (err != SUCCESS)
    {
        printf("Close file failed\n");
        return 1;
    }

    (void)deinit_param(&param);

    return 0;
}


int init_param(s_file_param_t* param, char *argv[])
{
    param->pathfile = argv[1];
    param->num_bytes = atoi(argv[2]);
    param->action = argv[3];
    param->w_buffer = argv[4];
    param->r_buffer = malloc(param->num_bytes + 1);
    if (!param->r_buffer) {
        printf("malloc failed");
        return ERROR;
    }

    if (param->num_bytes < 0)
    {
        printf("Invalid num-bytes\n");
        return ERROR;
    }

    if (strcmp(param->action, "w") != 0 && strcmp(param->action, "r") != 0)
    {
        printf("Invalid action - r or w only\n");
        return ERROR;
    }

    return SUCCESS;
}

int open_file(s_file_param_t* param, int* fd)
{
    *fd = open(param->pathfile, O_RDWR | O_CREAT, 0664);
    if (ERROR == *fd)
    {
        printf("Open file %s failed \n",param->pathfile);
        return ERROR;
    }
    else
    {
        printf("Open file %s successfully with file id %d \n",param->pathfile, *fd);
    }
    
    return SUCCESS;
}

int read_write_op(s_file_param_t* param, int fd)
{
    if (!strcmp(param->action,"r"))
    {
        param->num_bytes = read(fd, param->r_buffer, param->num_bytes);
        if (ERROR == param->num_bytes)
        {
            printf("Read failed\n");
            close(fd);
            return ERROR;
        }
        else
        {
            param->r_buffer[param->num_bytes]='\0';
            printf("Read %d bytes from the file. Value: %s\n",param->num_bytes, param->r_buffer);
        }
    }
    else if (!strcmp(param->action,"w"))
    {
        char* temp_buffer = malloc(param->num_bytes);
        if (!temp_buffer)
        {
            printf("malloc failed");
            return ERROR;
        }
        memset(temp_buffer,0,param->num_bytes);
        size_t copy_len = (strlen(param->w_buffer) < param->num_bytes) ? strlen(param->w_buffer) : param->num_bytes;
        memcpy(temp_buffer,param->w_buffer,copy_len);

        param->num_bytes = write(fd, temp_buffer, param->num_bytes);
        if ( ERROR == param->num_bytes)
        {
            printf("Write to file failed\n");
            free(temp_buffer);
            close(fd);
            return ERROR;
        }
        else
        {
            free(temp_buffer);
            printf("Write %d bytes to file\n", param->num_bytes);
        }
    }
    else
    {
        printf("Invalid action - r or w only");
        close(fd);
        return ERROR;
    }
    
    return SUCCESS;
}

void deinit_param(s_file_param_t* param)
{
    free(param -> r_buffer);
}