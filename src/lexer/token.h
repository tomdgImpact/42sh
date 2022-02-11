#pragma once

/*
** Note
** ============================================================================
** How to add a token for recognition pattern ?
** Add the token into the enumeration 'e_token_type' then
** math the added token with its string in the array 'token_identifiers'.
** ============================================================================
*/

/* Token type enumeration */
enum e_token_type
{
    /* ================================ */
    /*  TOKEN_EXAMPLE,                  */
    /*  // Add tokens below ...         */
    /* ================================ */

    TOKEN_CMD, /* token command           */
    TOKEN_EOF, /* token end of file       */
    TOKEN_WORD, /* token word              */
};

/* Token structure */
struct s_token
{
    enum e_token_type type;
    char *data_str;
};

/* Pair structure for array 'token_identifiers' */
typedef struct
{
    enum e_token_type type;
    const char *word;
} token_id;
