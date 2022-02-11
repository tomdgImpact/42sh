#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../builtins/builtins.h"

static int last(char *str, size_t len)
{
    for (size_t i = len - 1; i > 0; i++)
        if (str[i] == '/' && i != len - 1)
            return i;
    return 0;
}

static void case_point(char *pwd, char *arg)
{
    size_t length = strlen(arg);
    length -= last(arg, length);
    char *duplicate = strndup(pwd, length);
    chdir("..");
    setenv("OLDPWD", pwd, 1);
    setenv("PWD", duplicate, 1);
}

static void change_dir(char *pwd, char *arg)
{
    setenv("OLDPWD", pwd, 1);
    pwd = strcat(pwd, "/");
    pwd = strcat(pwd, arg);
    int change = chdir(arg);
    if (change == -1)
        errx(1, "no such file or directory");
    setenv("PWD", pwd, 1);
}

static void home(char *pwd)
{
    char *home_dir = getenv("HOME");
    chdir(home_dir);
    setenv("OLDPWD", pwd, 1);
    setenv("PWD", home_dir, 1);
}

int cd_builtin(char **arg)
{
    if (arg == NULL)
        errx(1, "error %s", __func__);
    char *pwd = getenv("PWD");
    char *old = getenv("OLDPWD");
    if (arg[1] == NULL || strcmp(arg[1], "~") == 0)
        home(pwd);
    else if (strchr(arg[1], '.') != NULL)
        return 0;
    else if (strchr(arg[1], '-') != NULL)
    {
        setenv("OLDPWD", pwd, 1);
        pwd = old;
        setenv("PWD", old, 1);
        chdir(old);
    }
    else if (strcmp(arg[1], "..") == 0)
        case_point(pwd, arg[1]);
    else
        change_dir(pwd, arg[1]);
    pwd = getenv("PWD");
    old = getenv("OLDPWD");
    printf("PWD = %s and OLD = %s\n", pwd, old);
    return 0;
}
