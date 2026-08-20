/* /////////////////////////////////////////////////////////////////////////
 * File:    example.c.1.c
 *
 * Purpose: Example of Pantheios.Extras.AtExit: register several atexit
 *          callbacks (LIFO) and drain them via uninit().
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
fn1(void* param)
{
    printf("fn1(%p)\n", param);
}

static void
fn2(void* param)
{
    printf("fn2(%p)\n", param);
}


static int
add(
    void    (*pfn)(void* param)
,   void*   param
)
{
    int const r = pantheios_extras_atexit_add(pfn, param);

    if (0 != r)
    {
        fprintf(
            stderr
        ,   "failed to add Pantheios.Extras.AtExit callback : %s (%d)\n"
        ,   strerror(r)
        ,   r
        );
    }

    return r;
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

    /* LIFO: last add is invoked first by uninit() / atexit */
    if (0 != add(fn1, (void*)1) ||
        0 != add(fn2, (void*)2) ||
        0 != add(fn1, (void*)3) ||
        0 != add(fn2, (void*)4))
    {
        return EXIT_FAILURE;
    }

    pantheios_extras_atexit_uninit();

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

