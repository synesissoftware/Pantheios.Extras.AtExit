/* /////////////////////////////////////////////////////////////////////////
 * File:    example.c.1.c
 *
 * Purpose: Example of Pantheios.Extras.AtExit: register several atexit
 *          callbacks (LIFO) and drain them via uninit().
 *
 * Created: 30th December 2011
 * Updated: 16th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <pantheios/extras/atexit.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void
fn1(void* param)
{
    printf("fn1(%p)\n", param);
}

static void
fn2(void* param)
{
    printf("fn2(%p)\n", param);
}


int
main(void)
{
    int r = pantheios_extras_atexit_init(NULL, 0);

    if (0 != r)
    {
#ifdef _MSC_VER
        char error_message[256];

        strerror_s(error_message, sizeof(error_message), r);
#else
        char const* error_message = strerror(r);
#endif

        fprintf(
            stderr
        ,   "failed to initialise Pantheios.Extras.AtExit : %s (%d)\n"
        ,   error_message
        ,   r
        );

        return EXIT_FAILURE;
    }

    /* LIFO: last add is invoked first by uninit() / atexit */
    pantheios_extras_atexit_add(fn1, (void*)1);
    pantheios_extras_atexit_add(fn2, (void*)2);
    pantheios_extras_atexit_add(fn1, (void*)3);
    pantheios_extras_atexit_add(fn2, (void*)4);

    pantheios_extras_atexit_uninit();

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

