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
        fprintf(
            stderr
        ,   "failed to initialise Pantheios.Extras.AtExit : %s (%d)\n"
        ,   strerror(r)
        ,   r
        );

        return EXIT_FAILURE;
    }

    pantheios_extras_atexit_add(fn, (void*)1);
    pantheios_extras_atexit_add(fn, (void*)2);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
