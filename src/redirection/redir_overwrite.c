#include <err.h>
#include <unistd.h>

#include "redir.h"

#define BUF_SIZE 2048

size_t overwrite(int fd_in, int fd_out)
{
    size_t status = 0;
    int read_status = 0;
    char *buf = calloc(BUF_SIZE, sizeof(char));
    if (buf == NULL)
        errx(1, "error while allocating memory %s", __func__);
    while ((read_status = read(fd_in, buf, BUF_SIZE)) != 0)
    {
        if (read_status == -1)
            errx(1, "error while reading for fd %d in %s", fd_in, __func__);
        int write_status = 0;
        int nb_char = BUF_SIZE;
        while ((write_status = write(fd_out, buf, nb_char)) != 0)
        {
            if (write_status == -1)
                errx(1, "error writing data in fd %d in %s", fd_out, __func__);
            buf += write_status;
            nb_char -= write_status;
        }
    }
    return status;
}
