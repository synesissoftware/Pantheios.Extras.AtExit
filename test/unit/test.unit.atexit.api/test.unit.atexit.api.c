/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atexit.api.c
 *
 * Purpose: Unit tests for Pantheios.Extras.AtExit.
 *
 * Created: 16th August 2026
 * Updated: 16th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <pantheios/extras/atexit.h>

#include <xtests/xtests.h>

#include <errno.h>
#include <stdlib.h>


static int  s_calls[8];
static int  s_ncalls;
static int  s_tag1 = 1;
static int  s_tag2 = 2;
static int  s_tag3 = 3;
static int  s_tag7 = 7;


static void
record(void* param)
{
    if (s_ncalls < (int)(sizeof(s_calls) / sizeof(s_calls[0])))
    {
        s_calls[s_ncalls] = *(int*)param;
    }

    ++s_ncalls;
}


static void
test_init_succeeds(void)
{
    int const r = pantheios_extras_atexit_init(NULL, 0);

    XTESTS_TEST_INTEGER_EQUAL(0, r);
}

static void
test_second_init_fails(void)
{
    int const r = pantheios_extras_atexit_init(NULL, 0);

    XTESTS_TEST_INTEGER_NOT_EQUAL(0, r);
    XTESTS_TEST_INTEGER_EQUAL(EBUSY, r);
}

static void
test_uninit_invokes_lifo(void)
{
    s_ncalls = 0;

    XTESTS_TEST_INTEGER_EQUAL(0, pantheios_extras_atexit_add(record, &s_tag1));
    XTESTS_TEST_INTEGER_EQUAL(0, pantheios_extras_atexit_add(record, &s_tag2));
    XTESTS_TEST_INTEGER_EQUAL(0, pantheios_extras_atexit_add(record, &s_tag3));

    pantheios_extras_atexit_uninit();

    XTESTS_TEST_INTEGER_EQUAL(3, s_ncalls);
    XTESTS_TEST_INTEGER_EQUAL(3, s_calls[0]);
    XTESTS_TEST_INTEGER_EQUAL(2, s_calls[1]);
    XTESTS_TEST_INTEGER_EQUAL(1, s_calls[2]);
}

static void
test_uninit_is_idempotent_for_callbacks(void)
{
    int before;

    s_ncalls = 0;

    XTESTS_TEST_INTEGER_EQUAL(0, pantheios_extras_atexit_add(record, &s_tag7));

    pantheios_extras_atexit_uninit();
    before = s_ncalls;
    XTESTS_TEST_INTEGER_EQUAL(1, before);

    pantheios_extras_atexit_uninit();

    XTESTS_TEST_INTEGER_EQUAL(before, s_ncalls);
}


static void
test_init_after_uninit_fails(void)
{
    int const r = pantheios_extras_atexit_init(NULL, 0);

    XTESTS_TEST_INTEGER_EQUAL(EBUSY, r);
}


int
main(int argc, char** argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atexit.api", verbosity))
    {
        /* Order matters: first case performs the single process init.
         * Later cases add/drain the list; process atexit is then a no-op.
         */
        XTESTS_RUN_CASE(test_init_succeeds);
        XTESTS_RUN_CASE(test_second_init_fails);
        XTESTS_RUN_CASE(test_uninit_invokes_lifo);
        XTESTS_RUN_CASE(test_uninit_is_idempotent_for_callbacks);
        XTESTS_RUN_CASE(test_init_after_uninit_fails);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
