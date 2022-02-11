#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../builtins/builtins.h"
#include "redir.h"

size_t redir_pipe(char **argv_left, char **argv_right,
                  enum redir_builtin builtin)
{
    int fd[2];
    if (pipe(fd) == -1)
        errx(1, "Pipe failed");
    if (builtin == BUILTIN)
    {
        // builtins function execution
        // if echo launch echo
    }
    if (fork() == 0)
    {
        close(STDOUT_FILENO);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        if (execvp(argv_left[0], argv_left) == -1)
            return 127;
        exit(1);
    }
    if (fork() == 0)
    {
        close(STDIN_FILENO);
        dup(fd[0]);
        close(fd[1]);
        close(fd[0]);
        if (execvp(argv_right[0], argv_right) == -1)
            return 127;
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    wait(0);
    wait(0);
    return 0;
}
