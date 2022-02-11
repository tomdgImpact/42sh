#include <err.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../builtins/builtins.h"
#include "eval.h"

size_t eval_simple_cmd(struct s_simple_command *cmd)
{
    if (cmd == NULL)
        errx(1, "syntax error %s", __func__);
    int pid = 0;
    int status = 0;
    if (strcmp(cmd->cmd[0], "echo") == 0)
        status = echo_builtin(cmd->cmd);
    else if (strcmp(cmd->cmd[0], "cd") == 0)
        status = cd_builtin(cmd->cmd);
    else if (strcmp(cmd->cmd[0], "true") == 0)
        status = 0;
    else if (strcmp(cmd->cmd[0], "false") == 0)
        status = 1;
    else
    {
        pid = fork();
        if (pid < 0)
            errx(1, "cannot create child process %s", __func__);
        else if (pid == 0)
        {
            // child process
            status = execvp(cmd->cmd[0], cmd->cmd);
            exit(status);
        }
        int rstat = 0;
        pid_t child_pid = waitpid(pid, &rstat, 0);
        if (child_pid == -1)
            errx(1, "error on executing child process in %s", __func__);
        return rstat;
    }
    return status;
}

size_t eval_shell_cmd(struct s_shell_command *cmd)
{
    if (cmd == NULL)
        errx(1, "shell command cannot be evaluated %s", __func__);
    size_t status = 0;
    switch (cmd->type)
    {
    case IF:
        status = eval_if_clause(cmd->if_cmd);
        break;
    default:
        break;
    }
    return status;
}
