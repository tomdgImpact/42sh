/*
** Don't forget to link criterion library :
** gcc -lcriterion file.c
*/

#include <criterion/criterion.h>
#include <stdbool.h>
#include <string.h>

#include "my_strcmp.h"
#include "my_strtok.h"

/*
** =================
** TESTS TESTS TESTS
** =================
*/

Test(suite_my_better_strtok, test_01)
{
    /* Param setting */
    const char *input_str = "";

    char *got = my_better_strtok(input_str, NULL, 0);

    /* TEST!!! */
    cr_assert(got == NULL);

    free(got);
}

Test(suite_my_better_strtok, test_02)
{
    /* Param setting */
    const char *input_str = "This is a short string.";
    const char *expected = "This";

    char *got = my_better_strtok(input_str, NULL, 0);

    /* TEST!!! */
    cr_assert(my_strcmp(got, expected));

    free(got);
}

Test(suite_my_better_strtok, test_03)
{
    /* Param setting */
    const char *input_str = "   Starting with spaces.";
    const char *expected = "Starting";

    char *got = my_better_strtok(input_str, NULL, 0);

    /* TEST!!! */
    cr_assert(my_strcmp(got, expected));

    free(got);
}

Test(suite_my_better_strtok, test_04)
{
    /* Param setting */
    const char *input_str = "~~\nfzefé-|`é&#$dz adz\t\fret\n\n\n\t\v";
    char *tmp;

    /* TEST!!! */
    cr_assert(my_strcmp((tmp = my_better_strtok(input_str, NULL, 0)), "~~"));
    free(tmp);
    cr_assert(my_strcmp((tmp = my_better_strtok(input_str, NULL, 0)),
                        "fzefé-|`é&#$dz"));
    free(tmp);
    cr_assert(my_strcmp((tmp = my_better_strtok(input_str, NULL, 0)), "adz"));
    free(tmp);
    cr_assert(my_strcmp((tmp = my_better_strtok(input_str, NULL, 0)), "ret"));
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);

    /*
    ** Warning !!! my_better_strtok() returns a string that should be
    ** freed.
    */
}

Test(suite_my_better_strtok, test_05)
{
    /* Param setting */
    const char *input_str = "   \v\t\f\v\n\n\v\t\f\v\n\n       \n";
    char *tmp;

    /* TEST!!! */
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
}

Test(suite_my_better_strtok, test_06)
{
    /* Param setting */
    const char *input_str = " ";
    char *tmp;

    /* TEST!!! */
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
}

Test(suite_my_better_strtok, test_07)
{
    /* Param setting */
    const char *input_str = "\v";
    char *tmp;

    /* TEST!!! */
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
}

Test(suite_my_better_strtok, test_08)
{
    /* Param setting */
    const char *input_str = "_______\v_______";
    char *tmp;

    /* TEST!!! */
    cr_assert(
        my_strcmp((tmp = my_better_strtok(input_str, NULL, 0)), "_______"));
    free(tmp);
    cr_assert(
        my_strcmp((tmp = my_better_strtok(input_str, NULL, 0)), "_______"));
    free(tmp);
    cr_assert((tmp = my_better_strtok(input_str, NULL, 0)) == NULL);
    free(tmp);
}
