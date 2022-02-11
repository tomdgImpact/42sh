#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "redir.h"

#define BUF_SIZE 2048

size_t change_file(char *file_left, char *file_right)
{
    size_t status = 0;
    int fd_lr = open(file_left, S_IRUSR);
    int fd_rw = open(file_right, S_IWUSR);
    int read_stat = 0;
    char *buf = calloc(BUF_SIZE, sizeof(char));
    while ((read_stat = read(fd_lr, buf, BUF_SIZE)) != 0)
    {
        if (read_stat == -1)
            errx(1, "error while reading fd = %d in %s", fd_lr, __func__);
        int write_stat = 0;
        int count = BUF_SIZE;
        while ((write_stat = write(fd_rw, buf, count)) != 0)
        {
            if (write_stat == -1)
                errx(1, "error on writing on fd = %d in %s", fd_rw, __func__);
            buf += write_stat;
            count -= write_stat;
        }
    }
    return status;
}
