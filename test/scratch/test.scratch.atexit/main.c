/* /////////////////////////////////////////////////////////////////////////
 * File:    main.c
 *
 * Purpose: Scratch test for Pantheios.Extras.AtExit.
 *
 * Created: 30th December 2011
 * Updated: 21st August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <pantheios/extras/atexit.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void
fn(void* param)
{
    printf("scratch callback %p\n", param);
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

    pantheios_extras_atexit_add(fn, (void*)1);
    pantheios_extras_atexit_add(fn, (void*)2);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
