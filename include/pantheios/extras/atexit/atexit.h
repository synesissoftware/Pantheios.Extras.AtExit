/* /////////////////////////////////////////////////////////////////////////
 * File:        pantheios/extras/atexit/atexit.h
 *
 * Purpose:     Header file for Pantheios.Extras.AtExit.
 *
 * Created:     30th December 2011
 * Updated:     16th August 2026
 *
 * Home:        http://www.pantheios.org/
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
# define PANTHEIOS_EXTRAS_ATEXIT_VER_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT_MINOR    1
# define PANTHEIOS_EXTRAS_ATEXIT_VER_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT_REVISION 1
# define PANTHEIOS_EXTRAS_ATEXIT_VER_PANTHEIOS_EXTRAS_ATEXIT_H_ATEXIT_EDIT     5
#endif /* !PANTHEIOS_DOCUMENTATION_SKIP_SECTION */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER_MAJOR
 * The major version number of Pantheios.Extras.AtExit
 */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER_MINOR
 * The minor version number of Pantheios.Extras.AtExit
 */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER_REVISION
 * The revision version number of Pantheios.Extras.AtExit
 */

/** \def PANTHEIOS_EXTRAS_ATEXIT_VER
 * The current composite version number of Pantheios.Extras.AtExit
 */

#ifndef PANTHEIOS_DOCUMENTATION_SKIP_SECTION
# define PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_1                     0x000101ff
#endif /* !PANTHEIOS_DOCUMENTATION_SKIP_SECTION */

#define PANTHEIOS_EXTRAS_ATEXIT_VER_MAJOR                     0
#define PANTHEIOS_EXTRAS_ATEXIT_VER_MINOR                     1
#define PANTHEIOS_EXTRAS_ATEXIT_VER_REVISION                  1

#define PANTHEIOS_EXTRAS_ATEXIT_VER                           PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* /////////////////////////////////////////////////////////////////////////
 * API
 */

/** Initialises the Pantheios.Extras.AtExit library, registering the API
 * state with the C standard library function <code>atexit()</code>.
 *
 * Must not be called more than once per process. Subsequent calls fail
 * even after \c pantheios_extras_atexit_uninit(), because libc
 * <code>atexit()</code> handlers cannot be unregistered.
 *
 * \param reserved0 Currently unused. Must be NULL.
 * \param reserved1 Currently unused. Must be 0.
 *
 * \retval 0 The library was initialised successfully.
 * \retval !0 The library was not initialised successfully. The return value
 *   is a C failure code, and may be used with <code>strerror()</code> to
 *   obtain a human-readable string form of the failure.
 *
 * \warning Failure to call this function will mean that no callbacks
 *   registered by pantheios_extras_atexit_add() will be invoked at process
 *   exit (they may still be invoked by pantheios_extras_atexit_uninit()).
 */
int
pantheios_extras_atexit_init(
    void*       reserved0
,   unsigned    reserved1
);

/** Uninitialises the Pantheios.Extras.AtExit library.
 *
 * Invokes remaining registered callbacks (LIFO) and frees the list so the
 * registered <code>atexit()</code> hook is a no-op. Does not (and cannot)
 * unregister the libc <code>atexit()</code> handler.
 */
void
pantheios_extras_atexit_uninit(
    void
);

/** Adds a callback function to the Pantheios.Extras.AtExit library, which
 * will be called, along with the given callback parameter, during
 * <code>atexit()</code>-processing, or during
 * \c pantheios_extras_atexit_uninit() if that is invoked first.
 *
 * Callbacks are invoked in LIFO order.
 *
 * \param pfn Callback function.
 * \param param Parameter to be passed to the callback function when it is
 *   invoked.
 *
 * \retval 0 The callback function was successfully registered.
 * \retval !0 The callback function was not registered successfully. The
 *   return value is a C failure code, and may be used with
 *   <code>strerror()</code> to obtain a human-readable string form of the
 *   failure.
 *
 * \pre (NULL != pfn)
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
