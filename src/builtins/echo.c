#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "../alloc/alloc.h"
#include "../builtins/builtins.h"
enum echo_options
{
    OPTION_NULL,
    OPTION_N,
    OPTION_E,
};

static void get_options(char **argv, enum echo_options *options,
                        size_t *cursor);

static bool already_option(enum echo_options cur_opt,
                           enum echo_options *options, size_t size);

static void handle_char(char chr, bool check_e_opt);

int echo_builtin(char **argv)
{
    enum echo_options options[2] = { 0 }; // initialisation of option's array
    size_t cursor = 1; // cursor to the first args of argv to print

    get_options(argv, options, &cursor); // scan options in argv

    bool check_e_option = already_option(OPTION_E, options, 2);

    for (int index_args = cursor; argv[index_args] != NULL; index_args++)
    {
        char *arg = argv[index_args];
        for (int index = 0; arg[index] != '\0'; index++)
        {
            handle_char(arg[index], check_e_option);
        }
        if (argv[index_args + 1] != NULL)
            putchar(' ');
    }

    if (!already_option(OPTION_N, options, 2))
    {
        putchar('\n');
    }

    // free(options);
    return 0;
}

static void get_options(char **argv, enum echo_options *options, size_t *cursor)
{
    bool set_n = false;
    bool set_e = false;
    int index_options = 0;
    for (int index_args = 1; argv[index_args] != NULL; index_args++)
    {
        if (strchr(argv[index_args], '-') != NULL)
        {
            if (strchr(argv[index_args], 'n') != NULL && set_n == false)
            {
                options[index_options++] = OPTION_N;
                set_n = true;
            }
            if (strchr(argv[index_args], 'e') != NULL && set_e == false)
            {
                options[index_options++] = OPTION_E;
                set_e = true;
            }
        }
        *cursor += 1;
    }
    *cursor -= 1;
}

static bool already_option(enum echo_options cur_opt,
                           enum echo_options *options, size_t size)
{
    if (!options)
        return false;

    for (size_t index = 0; index < size; index++)
    {
        if (cur_opt == options[index])
        {
            return true;
        }
    }
    return false;
}

static void handle_char(char chr, bool check_e_option)
{
    if (chr == '\n' && !check_e_option)
    {
        printf("\\n");
    }
    else if (chr == '\t' && !check_e_option)
    {
        printf("\\t");
    }
    else if (chr == '\\' && !check_e_option)
    {
        printf("\\");
    }
    else
    {
        putchar(chr);
    }
}
