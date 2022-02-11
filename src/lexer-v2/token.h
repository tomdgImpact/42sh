#pragma once

enum e_token_type
{
    TOKEN_WORD,
    TOKEN_IF,
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_SEMICOLON,
    TOKEN_NEWLINE,
    TOKEN_PIPE,
    TOKEN_FI,
    TOKEN_EOF,
};

struct s_token
{
    enum e_token_type token_type;
    char *token_data;
};

typedef struct
{
    enum e_token_type type;
    const char *pattern;
} token_id;

struct s_token *token_create(const char *input_string);

void token_destroy(struct s_token *token);
