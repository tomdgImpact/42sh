#include "redir.h"

size_t redirection_caller(struct input *input)
{
    size_t status = 0;
    switch (input->type)
    {
    case PIPE:
        status = redir_pipe(input->argv, input->argv, input->built);
        break;
    case APPEND:
        status = append(input->fd, input->fd);
        break;
    case OVERWRITE:
        status = overwrite(input->fd, input->fd);
        break;
    case CHANGE_FILE:
        status = change_fd(input->fd, input->fd);
        break;
    case INPUT_RDIR:
        status = redir_input(input->argv);
        break;
    default:
        break;
    }
    return status;
}
