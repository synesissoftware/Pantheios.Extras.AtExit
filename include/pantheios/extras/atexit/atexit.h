/* /////////////////////////////////////////////////////////////////////////
 * File:    pantheios/extras/atexit/atexit.h
 *
 * Purpose: Header file for Pantheios.Extras.AtExit.
 *
 * Created: 30th December 2011
 * Updated: 4th November 2026
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


/** \file pantheios/extras/atexit/atexit.h
 * [C only] API for the
 *   \ref group__library__pantheios_extras_atexit "Pantheios.Extras.AtExit" library.
 */

#ifndef PANTHEIOS_EXTRAS_ATEXIT_INCL_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT
#define PANTHEIOS_EXTRAS_ATEXIT_INCL_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef PANTHEIOS_DOCUMENTATION_SKIP_SECTION
# define PANTHEIOS_EXTRAS_ATEXIT_VER_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT_MAJOR    1
# define PANTHEIOS_EXTRAS_ATEXIT_VER_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT_MINOR    2
# define PANTHEIOS_EXTRAS_ATEXIT_VER_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT_REVISION 5
# define PANTHEIOS_EXTRAS_ATEXIT_VER_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT_EDIT     14
#endif /* !PANTHEIOS_DOCUMENTATION_SKIP_SECTION */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER_MAJOR
 * The major version number of Pantheios.Extras.AtExit
 */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER_MINOR
 * The minor version number of Pantheios.Extras.AtExit
 */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER_PATCH
 * The patch version number of Pantheios.Extras.AtExit
 */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER_RELSTATUS
 * The release status of Pantheios.Extras.AtExit, in the range 1-0xFE for
 * prerelease versions, and 0xFF for a released version
 */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER
 * The current composite version number of Pantheios.Extras.AtExit
 */

#ifndef PANTHEIOS_DOCUMENTATION_SKIP_SECTION
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_1                     0x000101ff
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_2_ALPHA_1             0x00010241
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_3                     0x000103ff
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_4_BETA_1              0x00010481
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_4_BETA_2              0x00010482
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_4_BETA_3              0x00010483
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_4_BETA_4              0x00010484
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_4_BETA_5              0x00010485
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_4                     0x000104ff
#endif /* !PANTHEIOS_DOCUMENTATION_SKIP_SECTION */

#define PANTHEIOS_EXTRAS_ATEXIT_VER_MAJOR                     0
#define PANTHEIOS_EXTRAS_ATEXIT_VER_MINOR                     1
#define PANTHEIOS_EXTRAS_ATEXIT_VER_PATCH                     4
#define PANTHEIOS_EXTRAS_ATEXIT_VER_RELSTATUS                 0xff

#define PANTHEIOS_EXTRAS_ATEXIT_VER \
    (0\
        |   (   PANTHEIOS_EXTRAS_ATEXIT_VER_MAJOR       << 24   ) \
        |   (   PANTHEIOS_EXTRAS_ATEXIT_VER_MINOR       << 16   ) \
        |   (   PANTHEIOS_EXTRAS_ATEXIT_VER_PATCH       <<  8   ) \
        |   (   PANTHEIOS_EXTRAS_ATEXIT_VER_RELSTATUS   <<  0   ) \
    )

#ifndef PANTHEIOS_DOCUMENTATION_SKIP_SECTION
# define PANTHEIOS_EXTRAS_ATEXIT_VER_ALPHABETA              PANTHEIOS_EXTRAS_ATEXIT_VER_RELSTATUS
# define PANTHEIOS_EXTRAS_ATEXIT_VER_REVISION               PANTHEIOS_EXTRAS_ATEXIT_VER_PATCH
#endif /* !PANTHEIOS_DOCUMENTATION_SKIP_SECTION */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* /////////////////////////////////////////////////////////////////////////
 * API
 */

/** \brief Initialises the library and registers one libc atexit hook.
 *
 * Concurrent calls are serialised on the library lock. The first call that
 * finds the library uninitialised registers the hook; every other call
 * returns EBUSY, including calls after uninit(), because libc atexit()
 * handlers cannot be unregistered.
 *
 * \param reserved0 Currently unused. Must be NULL;
 * \param reserved1 Currently unused. Must be 0;
 *
 * \retval 0 The library was initialised;
 * \retval EBUSY The library was already initialised;
 * \retval ENOMEM libc atexit() could not register the hook. The raw
 *   atexit() status is not returned; ENOMEM is an errno value and may be
 *   passed to strerror();
 *
 * \pre NULL == reserved0
 * \pre 0 == reserved1
 *
 * \note add() before a successful init() still queues callbacks. Process
 *   exit drains that queue only after init() has registered the hook.
 *   uninit() can drain the queue without init().
 */
int
pantheios_extras_atexit_init(
    void*       reserved0
,   unsigned    reserved1
);

/** \brief Drains registered callbacks and leaves the libc hook in place.
 *
 * Invokes the current list in LIFO order, then frees those nodes. The libc
 * atexit() handler stays registered, so a later add() still runs at process
 * exit or at a later uninit(). Callbacks run after the library lock is
 * released, and may call add() or uninit().
 */
void
pantheios_extras_atexit_uninit(
    void
);

/** \brief Registers a callback and the parameter passed to it.
 *
 * The callback runs during atexit processing, or during uninit() when that
 * drains the list first. Order is LIFO. add() after uninit() is valid; the
 * hook is still live. add() before init() queues the callback, and process
 * exit drains it only after a successful init().
 *
 * \param pfn Callback function;
 * \param param Value passed to pfn when it is invoked;
 *
 * \retval 0 The callback was registered;
 * \retval ENOMEM The callback was not registered. ENOMEM may be passed
 *   to strerror();
 *
 * \pre NULL != pfn
 */
int
pantheios_extras_atexit_add(
    void    (*pfn)(void* param)
,   void*   param
);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !PANTHEIOS_EXTRAS_ATEXIT_INCL_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT */

/* ///////////////////////////// end of file //////////////////////////// */

