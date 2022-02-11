#ifndef _XOPEN_SOURCE
#    define _XOPEN_SOURCE 500
#endif

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dynstring/dynstring.h"
#include "eval/eval.h"
#include "io/cstream.h"
#include "parser/parser.h"
#include "utils/vec.h"

/**
 * \brief Parse the command line arguments
 * \return A character stream
 */
struct cstream *parse_args(int argc, char *argv[])
{
    // If launched without argument, read the standard input
    if (argc == 1)
    {
        if (isatty(STDIN_FILENO))
            return cstream_readline_create();
        return cstream_file_create(stdin, /* fclose_on_free */ false);
    }

    // 42sh FILENAME
    if (argc == 2)
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            warn("failed to open input file");
            return NULL;
        }

        return cstream_file_create(fp, /* fclose_on_free */ true);
    }

    fprintf(stderr, "Usage: %s [COMMAND]\n", argv[0]);
    return NULL;
}

/**
 * \brief Read and print lines on newlines until EOF
 * \return An error code
 */
enum error read_print_loop(struct cstream *cs, struct vec *line)
{
    enum error err;

    while (true)
    {
        // Read the next character
        int c;
        if ((err = cstream_pop(cs, &c)))
            return err;

        // If the end of file was reached, stop right there
        if (c == EOF)
            break;

        // If a newline was met, print the line
        if (c == '\n')
        {
            if (vec_cstring(line)[0] == '\n')
                continue;

            struct s_ast_node *ast = parse_input(vec_cstring(line));

            eval(ast);

            ast_destroy(ast);
            vec_reset(line);
            continue;
        }

        // Otherwise, add the character to the line
        vec_push(line, c);
    }

    return NO_ERROR;
}

static char *one_line(FILE *file)
{
    struct dynstring *dyns = dynstring_create();
    char *line = NULL;
    size_t line_length = 0;

    while (getline(&line, &line_length, file) != -1)
        dyns = dynstring_append(dyns, line);

    free(line);
    char *to_ret = strndup(dyns->data, dyns->size);
    dynstring_delete(dyns);
    return to_ret;
}

int main(int argc, char *argv[])
{
    int rc;
    if (argc > 1)
    {
        if (strcmp(argv[1], "-c") == 0)
        {
            struct s_ast_node *ast = parse_input(argv[2]);
            size_t status = eval(ast);
            ast_destroy(ast);
            return status;
        }
        FILE *file = fopen(argv[1], "r");
        if (file)
        {
            char *to_parse = one_line(file);
            struct s_ast_node *ast = parse_input(to_parse);
            size_t status = eval(ast);
            free(to_parse);
            ast_destroy(ast);
            fclose(file);
            return status;
        }
    }
    // Parse command line arguments and get an input stream
    struct cstream *cs;
    if ((cs = parse_args(argc, argv)) == NULL)
    {
        rc = 1;
        goto err_parse_args;
    }

    // Create a vector to hold the current line
    struct vec line;
    vec_init(&line);

    // Run the test loop
    if (read_print_loop(cs, &line) != NO_ERROR)
    {
        rc = 1;
        goto err_loop;
    }

    // Success
    rc = 0;

err_loop:
    cstream_free(cs);
    vec_destroy(&line);
err_parse_args:
    return rc;
}