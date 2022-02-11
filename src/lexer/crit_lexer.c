/*
** Don't forget to link criterion library :
** gcc -lcriterion file.c
*/

#include <criterion/criterion.h>

#include "lexer.h"
#include "lexer_create.h"
#include "lexer_destroy.h"
#include "lexer_peek.h"
#include "lexer_pop.h"
#include "my_strcmp.h"
#include "token.h"
#include "token_destroy.h"

/*
** =================
** TESTS TESTS TESTS
** =================
*/

Test(suite_lexer, test_01)
{
    /* Param setting */
    const char *input_str = "";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    /* Checking if creation performs well */
    cr_assert(Alex->curr_token->type == TOKEN_EOF);
    cr_assert(my_strcmp(Alex->input_str, input_str));
    cr_assert(Alex->curr_token->data_str == NULL);

    token_destroy(Alex->curr_token);
    lexer_destroy(Alex);
}

Test(suite_lexer, test_02)
{
    /* Param setting */
    const char *input_str = "   echo echo echo    ";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    /* Checking that Alex contains the right things. */
    cr_assert(Alex->curr_token->type == TOKEN_CMD);
    cr_assert(my_strcmp(Alex->input_str, input_str));
    cr_assert(my_strcmp(Alex->curr_token->data_str, "echo"));

    /* Poping one element */
    struct s_token *tok = lexer_pop(Alex, NULL, 0);

    /* Checking the poped element */
    cr_assert(tok->type == TOKEN_CMD);
    cr_assert(my_strcmp(tok->data_str, "echo"));

    /* Checking that Alex contains the right things. */
    cr_assert(Alex->curr_token->type == TOKEN_CMD);
    cr_assert(my_strcmp(Alex->input_str, input_str));
    cr_assert(my_strcmp(Alex->curr_token->data_str, "echo"));

    token_destroy(tok);

    /* Checking lexer_peek() for second 'echo' */
    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(Alex->curr_token);
    lexer_destroy(Alex);
}

Test(suite_lexer, test_03)
{
    /* Param setting */
    const char *input_str = " error echo";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    cr_assert(Alex->curr_token->type == TOKEN_WORD);
    cr_assert(my_strcmp(Alex->input_str, input_str));
    cr_assert(my_strcmp(Alex->curr_token->data_str, "error"));

    /* Poping 'error' token from the string and checking it */
    struct s_token *tok = lexer_pop(Alex, NULL, 0);
    cr_assert(tok->type == TOKEN_WORD);
    cr_assert(my_strcmp(tok->data_str, "error"));

    /* Checking 'echo' token */
    token_destroy(tok);
    tok = lexer_peek(Alex);

    cr_assert(tok->type == TOKEN_CMD);
    cr_assert(my_strcmp(tok->data_str, "echo"));

    /* Checking EOF token */
    token_destroy(lexer_pop(Alex, NULL, 0));
    tok = lexer_peek(Alex);

    cr_assert(tok->type == TOKEN_EOF);
    cr_assert(tok->data_str == NULL);

    /* Destroying the last token and the lexer */
    token_destroy(tok);
    lexer_destroy(Alex);
}

Test(suite_lexer, test_04)
{
    /* Param setting */
    const char *input_str = "echo\t\v\n\v\f echo    ";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    token_destroy(lexer_pop(Alex, NULL, 0));

    /* Checking second 'echo' */
    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(lexer_pop(Alex, NULL, 0));

    /* Checking EOF token */
    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    /* Checking beyond EOF token */
    token_destroy(lexer_pop(Alex, NULL, 0));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_05)
{
    /* Param setting */
    const char *input_str = "\t\v\n\v\f   ";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_pop(Alex, NULL, 0));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_06)
{
    /* Param setting */
    const char *input_str = "xxxxxxxxxxxxx";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_pop(Alex, NULL, 0));

    struct s_token *tok = lexer_peek(Alex);

    cr_assert(tok->type == TOKEN_EOF);
    cr_assert(tok->data_str == NULL);

    token_destroy(tok);
    lexer_destroy(Alex);
}

Test(suite_lexer, test_07)
{
    /* Param setting */
    const char *input_str = "foo";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    struct s_token *tok = lexer_pop(Alex, NULL, 0);

    cr_assert(tok->type == TOKEN_WORD);
    cr_assert(my_strcmp(tok->data_str, "foo"));

    token_destroy(tok);
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_08)
{
    /* Param setting */
    const char *input_str = "fooechofoo";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    struct s_token *tok = lexer_pop(Alex, NULL, 0);

    cr_assert(tok->type == TOKEN_WORD);
    cr_assert(my_strcmp(tok->data_str, "fooechofoo"));

    token_destroy(tok);
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_9)
{
    /* Param setting */
    const char *input_str = "";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    struct s_token *tok = lexer_pop(Alex, NULL, 0);

    cr_assert(tok->type == TOKEN_EOF);
    cr_assert(tok->data_str == NULL);

    token_destroy(tok);
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_10)
{
    /* Param setting */
    const char *input_str = "\nx\n";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    struct s_token *tok = lexer_pop(Alex, NULL, 0);

    cr_assert(tok->type == TOKEN_WORD);
    cr_assert(my_strcmp(tok->data_str, "x"));

    token_destroy(tok);
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_11)
{
    /* Param setting */
    const char *input_str = "e";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    struct s_token *tok = lexer_pop(Alex, NULL, 0);

    cr_assert(tok->type == TOKEN_WORD);
    cr_assert(my_strcmp(tok->data_str, "e"));

    token_destroy(tok);
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_12)
{
    /* Param setting */
    const char *input_str = "\vecho";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    struct s_token *tok = lexer_pop(Alex, NULL, 0);

    cr_assert(tok->type == TOKEN_CMD);
    cr_assert(my_strcmp(tok->data_str, "echo"));

    token_destroy(tok);
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_13)
{
    /* Param setting */
    const char *input_str = "echo";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(lexer_pop(Alex, NULL, 0));
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_14)
{
    /* Param setting */
    const char *input_str = "echo";
    struct s_lexer *Alex = lexer_create(input_str, NULL, 0);

    token_destroy(lexer_peek(Alex));
    lexer_pop(Alex, NULL, 0);
    token_destroy(lexer_peek(Alex));
    lexer_pop(Alex, NULL, 0);
    token_destroy(lexer_peek(Alex));
    lexer_pop(Alex, NULL, 0);
    token_destroy(lexer_peek(Alex));
    lexer_pop(Alex, NULL, 0);
    token_destroy(lexer_peek(Alex));
    lexer_pop(Alex, NULL, 0);
    token_destroy(lexer_peek(Alex));
    lexer_pop(Alex, NULL, 0);
    token_destroy(lexer_peek(Alex));
    lexer_pop(Alex, NULL, 0);

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

/* ======================================================================== */
/* ==================== CHECKING SPECIFIED SEPARATORS ===================== */
/* ======================================================================== */

Test(suite_lexer, test_15)
{
    /* Param setting */
    const char *input_str = "XXXXXXXXX-XXXXXXXXXX";
    char delimiters[] = { '-' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 1);

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "XXXXXXXXX"));

    token_destroy(lexer_pop(Alex, delimiters, 1));
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_16)
{
    /* Param setting */
    const char *input_str = "XXXXXXXXX-XXXXXXXXXX";
    char delimiters[] = { '-' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 1);

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "XXXXXXXXX"));

    token_destroy(lexer_pop(Alex, delimiters, 1));

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "XXXXXXXXXX"));

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_17)
{
    /* Param setting */
    const char *input_str = "";
    char delimiters[] = { 'N', 'O', 'T', 'H', 'I', 'N', 'G' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 7);

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_18)
{
    /* Param setting */
    const char *input_str = "NOTHING";
    char delimiters[] = { 'N', 'O', 'T', 'H', 'I', 'N', 'G' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 7);

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_19)
{
    /* Param setting */
    const char *input_str = "NOTHINGechoNOTHINGecho";
    char delimiters[] = { 'N', 'O', 'T', 'H', 'I', 'N', 'G' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 7);

    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_20)
{
    /* Param setting */
    const char *input_str = "NOTHINGechoNOTHINGechoNOTHI";
    char delimiters[] = { 'N', 'O', 'T', 'H', 'I', 'N', 'G' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 7);

    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_21)
{
    /* Param setting */
    const char *input_str = "NOT HINGechoNOT     HINGechoNOTHI";
    char delimiters[] = { 'N', 'O', 'T', 'H', 'I', 'N', 'G' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 7);

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, " "));

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "     "));

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_CMD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "echo"));

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_22)
{
    /* Param setting */
    const char *input_str = "";
    char delimiters[] = { 'N', 'O', 'T', 'H', 'I', 'N', 'G' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 7);

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_pop(Alex, delimiters, 7));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_23)
{
    /* Param setting */
    const char *input_str = "";
    char delimiters[] = { '\0' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 1);

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_pop(Alex, delimiters, 1));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_24)
{
    /* Param setting */
    const char *input_str = "xyzxyzxyz";
    char delimiters[] = { 'x', 'y', 'z' };

    /*
    ** Although delimiters contains 'x', 'y', 'z' the 0 as argument
    ** implies that the delimiters are not considered and the default are used.
    */
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 0);

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "xyzxyzxyz"));

    token_destroy(lexer_pop(Alex, delimiters, 0));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_25)
{
    /* Param setting */
    const char *input_str = "xyzxyzxyz";
    char delimiters[] = { 'x', 'y', 'z' };
    struct s_lexer *Alex = lexer_create(input_str, delimiters, 3);

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_pop(Alex, delimiters, 3));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_26)
{
    /* Param setting */
    const char *input_str = "This is-a-random-string";
    char delimiters[] = { '-', ' ' };
    struct s_lexer *Alex = lexer_create(input_str, NULL, 4843);

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "This"));

    token_destroy(lexer_pop(Alex, delimiters, 2));

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "is"));

    token_destroy(lexer_pop(Alex, NULL, 0));

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "-a-random-string"));

    token_destroy(lexer_pop(Alex, NULL, 0));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_27)
{
    /* Param setting */
    const char *input_str = "xyzxyzxyz";
    struct s_lexer *Alex = lexer_create(input_str, "xyz", 3);

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_pop(Alex, "zyx", 3));

    cr_assert(lexer_peek(Alex)->type == TOKEN_EOF);
    cr_assert(lexer_peek(Alex)->data_str == NULL);

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}

Test(suite_lexer, test_28)
{
    /* Param setting */
    const char *input_str = "xyzxyzxyz";
    struct s_lexer *Alex = lexer_create(input_str, "", 0);

    cr_assert(lexer_peek(Alex)->type == TOKEN_WORD);
    cr_assert(my_strcmp(lexer_peek(Alex)->data_str, "xyzxyzxyz"));

    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);
}
