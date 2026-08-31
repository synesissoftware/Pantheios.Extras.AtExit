/* /////////////////////////////////////////////////////////////////////////
 * File:    atexit.api.c
 *
 * Purpose: Implementation file for Pantheios.Extras.AtExit
 *
 * Created: 30th December 2011
 * Updated: 31st August 2026
 *
 * Home:    http://www.pantheios.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2011-2019, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Software nor the
 *   names of any contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <pantheios/extras/atexit/atexit.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * atomics
 */

#if defined(_WIN32)
# include <windows.h>
typedef LONG pantheios_extras_atexit_atomic_int_t;
# define PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_INC_(p)    InterlockedIncrement((p))
# define PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_DEC_(p)    InterlockedDecrement((p))
#elif defined(__STDC_NO_ATOMICS__)
# if defined(__GNUC__) || defined(__clang__)
typedef int pantheios_extras_atexit_atomic_int_t;
#  define PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_INC_(p)   __sync_add_and_fetch((p), 1)
#  define PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_DEC_(p)   __sync_sub_and_fetch((p), 1)
# else
#  error Pantheios.Extras.AtExit requires C11 atomics, GCC/Clang __sync, or Windows Interlocked
# endif
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
# include <stdatomic.h>
typedef atomic_int pantheios_extras_atexit_atomic_int_t;
# define PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_INC_(p)    (atomic_fetch_add((p), 1) + 1)
# define PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_DEC_(p)    ((void)atomic_fetch_sub((p), 1))
#elif defined(__GNUC__) || defined(__clang__)
typedef int pantheios_extras_atexit_atomic_int_t;
# define PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_INC_(p)    __sync_add_and_fetch((p), 1)
# define PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_DEC_(p)    __sync_sub_and_fetch((p), 1)
#else
# error Pantheios.Extras.AtExit requires C11 atomics, GCC/Clang __sync, or Windows Interlocked
#endif

/* /////////////////////////////////////////////////////////////////////////
 * types
 */

struct pantheios_extras_atexit_context_t_;
typedef struct pantheios_extras_atexit_context_t_ pantheios_extras_atexit_context_t_;
struct pantheios_extras_atexit_context_t_
{
    void                                (*pfn)(void* param);
    void*                               param;
    pantheios_extras_atexit_context_t_* next;
};

/* /////////////////////////////////////////////////////////////////////////
 * globals
 */

static pantheios_extras_atexit_context_t_*  s_head          =   NULL;
static pantheios_extras_atexit_atomic_int_t s_mx            =   0;
static int                                  s_initialised   =   0;

/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

static
void
pantheios_extras_atexit_log_string_(
    char const* message
);

static
void
pantheios_extras_atexit_lock_(void)
{
    for (; 1 != PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_INC_(&s_mx); PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_DEC_(&s_mx))
    {}
}

static
void
pantheios_extras_atexit_unlock_(void)
{
    PANTHEIOS_EXTRAS_ATEXIT_ATOMIC_DEC_(&s_mx);
}

static
void
pantheios_extras_atexit_drain_unlocked_(void)
{
    pantheios_extras_atexit_context_t_* item;

    for (item = s_head; NULL != item; )
    {
        pantheios_extras_atexit_context_t_* next = item->next;

        item->pfn(item->param);
        free(item);

        item = next;
    }

    s_head = NULL;
}

static
void
pantheios_extras_atexit_procedure_(
    void
)
{
    pantheios_extras_atexit_lock_();
    pantheios_extras_atexit_drain_unlocked_();
    pantheios_extras_atexit_unlock_();
}

/* /////////////////////////////////////////////////////////////////////////
 * API
 */

int
pantheios_extras_atexit_init(
    void*       reserved0
,   unsigned    reserved1
)
{
    int r;

    ((void)reserved0);
    ((void)reserved1);

    if (0 != s_initialised)
    {
        pantheios_extras_atexit_log_string_("Pantheios.Extras.AtExit already initialised!\n");

        return EBUSY;
    }

    r = atexit(pantheios_extras_atexit_procedure_);

    if (0 != r)
    {
        return r;
    }

    s_initialised = 1;

    return 0;
}

void
pantheios_extras_atexit_uninit(
    void
)
{
    pantheios_extras_atexit_lock_();
    pantheios_extras_atexit_drain_unlocked_();
    pantheios_extras_atexit_unlock_();
}

int
pantheios_extras_atexit_add(
    void    (*pfn)(void* param)
,   void*   param
)
{
    pantheios_extras_atexit_context_t_* item;

    assert(NULL != pfn);

    item = (pantheios_extras_atexit_context_t_*)malloc(sizeof(pantheios_extras_atexit_context_t_));

    if (NULL == item)
    {
        return ENOMEM;
    }

    item->pfn   =   pfn;
    item->param =   param;

    pantheios_extras_atexit_lock_();

    item->next  =   s_head;
    s_head      =   item;

    pantheios_extras_atexit_unlock_();

    return 0;
}

/* /////////////////////////////////////////////////////////////////////////
 * helper definitions
 */

static
void
pantheios_extras_atexit_log_string_(
    char const* message
)
{
#ifdef _WIN32
    OutputDebugStringA(message);
#endif /* _WIN32 */
    fputs(message, stderr);
}

/* ///////////////////////////// end of file //////////////////////////// */

