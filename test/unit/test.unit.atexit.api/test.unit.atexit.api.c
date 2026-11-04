/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/test.unit.atexit.api/test.unit.atexit.api.c
 *
 * Purpose: Unit tests for Pantheios.Extras.AtExit.
 *
 * Created: 16th August 2026
 * Updated: 4th November 2026
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
static int  s_tag_pre = 11;
static int  s_tag_post = 13;
static int  s_tag_inner = 17;
static int  s_reenter_add_rc;


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
test_add_without_init_then_uninit(void)
{
    s_ncalls = 0;

    XTESTS_TEST_INTEGER_EQUAL(0, pantheios_extras_atexit_add(record, &s_tag_pre));

    pantheios_extras_atexit_uninit();

    XTESTS_TEST_INTEGER_EQUAL(1, s_ncalls);
    XTESTS_TEST_INTEGER_EQUAL(11, s_calls[0]);
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

static void
record_then_reenter(void* param)
{
    record(param);

    s_reenter_add_rc = pantheios_extras_atexit_add(record, &s_tag_inner);
    pantheios_extras_atexit_uninit();
}

static void
test_add_after_uninit_then_uninit_again(void)
{
    s_ncalls = 0;

    XTESTS_TEST_INTEGER_EQUAL(0, pantheios_extras_atexit_add(record, &s_tag_post));

    pantheios_extras_atexit_uninit();

    XTESTS_TEST_INTEGER_EQUAL(1, s_ncalls);
    XTESTS_TEST_INTEGER_EQUAL(13, s_calls[0]);
}

static void
test_callback_may_add_and_uninit(void)
{
    s_ncalls = 0;
    s_reenter_add_rc = -1;

    XTESTS_TEST_INTEGER_EQUAL(0, pantheios_extras_atexit_add(record_then_reenter, &s_tag1));

    pantheios_extras_atexit_uninit();

    XTESTS_TEST_INTEGER_EQUAL(0, s_reenter_add_rc);
    XTESTS_TEST_INTEGER_EQUAL(2, s_ncalls);
    XTESTS_TEST_INTEGER_EQUAL(1, s_calls[0]);
    XTESTS_TEST_INTEGER_EQUAL(17, s_calls[1]);
}


int
main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atexit.api", verbosity))
    {
        /* Order matters: add-without-init must run before the single
         * process init. Later cases drain before return. The libc hook
         * stays registered, so process exit sees an empty list.
         */
        XTESTS_RUN_CASE(test_add_without_init_then_uninit);
        XTESTS_RUN_CASE(test_init_succeeds);
        XTESTS_RUN_CASE(test_second_init_fails);
        XTESTS_RUN_CASE(test_uninit_invokes_lifo);
        XTESTS_RUN_CASE(test_uninit_is_idempotent_for_callbacks);
        XTESTS_RUN_CASE(test_init_after_uninit_fails);
        XTESTS_RUN_CASE(test_add_after_uninit_then_uninit_again);
        XTESTS_RUN_CASE(test_callback_may_add_and_uninit);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */

