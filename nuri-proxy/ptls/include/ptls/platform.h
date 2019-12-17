/**
 * \file platform.h
 *
 * \brief This file contains the definitions and functions of the
 *        Mbed TLS platform abstraction layer.
 *
 *        The platform abstraction layer removes the need for the library
 *        to directly link to standard C library functions or operating
 *        system services, making the library easier to port and epenta.
 *        Application developers and users of the library can provide their own
 *        implementations of these functions, or implementations specific to
 *        their platform, which can be statically linked to the library or
 *        dynamically configured at runtime.
 */
/*
 *  Copyright (C) 2006-2018, Arm Limited (or its affiliates), All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of Mbed TLS (https://tls.penta.org)
 */
#ifndef PTLS_PLATFORM_H
#define PTLS_PLATFORM_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#if defined(PTLS_HAVE_TIME)
#include "platform_time.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name SECTION: Module settings
 *
 * The configuration options you can set for this module are in this section.
 * Either change them in config.h or define them on the compiler command line.
 * \{
 */

#if !defined(PTLS_PLATFORM_NO_STD_FUNCTIONS)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if !defined(PTLS_PLATFORM_STD_SNPRINTF)
#if defined(_WIN32)
#define PTLS_PLATFORM_STD_SNPRINTF   ptls_platform_win32_snprintf /**< The default \c snprintf function to use.  */
#else
#define PTLS_PLATFORM_STD_SNPRINTF   snprintf /**< The default \c snprintf function to use.  */
#endif
#endif
#if !defined(PTLS_PLATFORM_STD_PRINTF)
#define PTLS_PLATFORM_STD_PRINTF   printf /**< The default \c printf function to use. */
#endif
#if !defined(PTLS_PLATFORM_STD_FPRINTF)
#define PTLS_PLATFORM_STD_FPRINTF fprintf /**< The default \c fprintf function to use. */
#endif
#if !defined(PTLS_PLATFORM_STD_CALLOC)
#define PTLS_PLATFORM_STD_CALLOC   calloc /**< The default \c calloc function to use. */
#endif
#if !defined(PTLS_PLATFORM_STD_FREE)
#define PTLS_PLATFORM_STD_FREE       free /**< The default \c free function to use. */
#endif
#if !defined(PTLS_PLATFORM_STD_EXIT)
#define PTLS_PLATFORM_STD_EXIT      exit /**< The default \c exit function to use. */
#endif
#if !defined(PTLS_PLATFORM_STD_TIME)
#define PTLS_PLATFORM_STD_TIME       time    /**< The default \c time function to use. */
#endif
#if !defined(PTLS_PLATFORM_STD_EXIT_SUCCESS)
#define PTLS_PLATFORM_STD_EXIT_SUCCESS  EXIT_SUCCESS /**< The default exit value to use. */
#endif
#if !defined(PTLS_PLATFORM_STD_EXIT_FAILURE)
#define PTLS_PLATFORM_STD_EXIT_FAILURE  EXIT_FAILURE /**< The default exit value to use. */
#endif
#if defined(PTLS_FS_IO)
#if !defined(PTLS_PLATFORM_STD_NV_SEED_READ)
#define PTLS_PLATFORM_STD_NV_SEED_READ   ptls_platform_std_nv_seed_read
#endif
#if !defined(PTLS_PLATFORM_STD_NV_SEED_WRITE)
#define PTLS_PLATFORM_STD_NV_SEED_WRITE  ptls_platform_std_nv_seed_write
#endif
#if !defined(PTLS_PLATFORM_STD_NV_SEED_FILE)
#define PTLS_PLATFORM_STD_NV_SEED_FILE   "seedfile"
#endif
#endif /* PTLS_FS_IO */
#else /* PTLS_PLATFORM_NO_STD_FUNCTIONS */
#if defined(PTLS_PLATFORM_STD_MEM_HDR)
#include PTLS_PLATFORM_STD_MEM_HDR
#endif
#endif /* PTLS_PLATFORM_NO_STD_FUNCTIONS */


/* \} name SECTION: Module settings */

/*
 * The function pointers for calloc and free.
 */
#if defined(PTLS_PLATFORM_MEMORY)
#if defined(PTLS_PLATFORM_FREE_MACRO) && \
    defined(PTLS_PLATFORM_CALLOC_MACRO)
#define ptls_free       PTLS_PLATFORM_FREE_MACRO
#define ptls_calloc     PTLS_PLATFORM_CALLOC_MACRO
#else
/* For size_t */
#include <stddef.h>
extern void *ptls_calloc( size_t n, size_t size );
extern void ptls_free( void *ptr );

/**
 * \brief               This function dynamically sets the memory-management
 *                      functions used by the library, during runtime.
 *
 * \param calloc_func   The \c calloc function implementation.
 * \param free_func     The \c free function implementation.
 *
 * \return              \c 0.
 */
int ptls_platform_set_calloc_free( void * (*calloc_func)( size_t, size_t ),
                              void (*free_func)( void * ) );
#endif /* PTLS_PLATFORM_FREE_MACRO && PTLS_PLATFORM_CALLOC_MACRO */
#else /* !PTLS_PLATFORM_MEMORY */
#define ptls_free       free
#define ptls_calloc     calloc
#endif /* PTLS_PLATFORM_MEMORY && !PTLS_PLATFORM_{FREE,CALLOC}_MACRO */

/*
 * The function pointers for fprintf
 */
#if defined(PTLS_PLATFORM_FPRINTF_ALT)
/* We need FILE * */
#include <stdio.h>
extern int (*ptls_fprintf)( FILE *stream, const char *format, ... );

/**
 * \brief                This function dynamically configures the fprintf
 *                       function that is called when the
 *                       ptls_fprintf() function is invoked by the library.
 *
 * \param fprintf_func   The \c fprintf function implementation.
 *
 * \return               \c 0.
 */
int ptls_platform_set_fprintf( int (*fprintf_func)( FILE *stream, const char *,
                                               ... ) );
#else
#if defined(PTLS_PLATFORM_FPRINTF_MACRO)
#define ptls_fprintf    PTLS_PLATFORM_FPRINTF_MACRO
#else
#define ptls_fprintf    fprintf
#endif /* PTLS_PLATFORM_FPRINTF_MACRO */
#endif /* PTLS_PLATFORM_FPRINTF_ALT */

/*
 * The function pointers for printf
 */
#if defined(PTLS_PLATFORM_PRINTF_ALT)
extern int (*ptls_printf)( const char *format, ... );

/**
 * \brief               This function dynamically configures the snprintf
 *                      function that is called when the ptls_snprintf()
 *                      function is invoked by the library.
 *
 * \param printf_func   The \c printf function implementation.
 *
 * \return              \c 0 on success.
 */
int ptls_platform_set_printf( int (*printf_func)( const char *, ... ) );
#else /* !PTLS_PLATFORM_PRINTF_ALT */
#if defined(PTLS_PLATFORM_PRINTF_MACRO)
#define ptls_printf     PTLS_PLATFORM_PRINTF_MACRO
#else
#define ptls_printf     printf
#endif /* PTLS_PLATFORM_PRINTF_MACRO */
#endif /* PTLS_PLATFORM_PRINTF_ALT */

/*
 * The function pointers for snprintf
 *
 * The snprintf implementation should conform to C99:
 * - it *must* always correctly zero-terminate the buffer
 *   (except when n == 0, then it must leave the buffer untouched)
 * - however it is acceptable to return -1 instead of the required length when
 *   the destination buffer is too short.
 */
#if defined(_WIN32)
/* For Windows (inc. MSYS2), we provide our own fixed implementation */
int ptls_platform_win32_snprintf( char *s, size_t n, const char *fmt, ... );
#endif

#if defined(PTLS_PLATFORM_SNPRINTF_ALT)
extern int (*ptls_snprintf)( char * s, size_t n, const char * format, ... );

/**
 * \brief                 This function allows configuring a custom
 *                        \c snprintf function pointer.
 *
 * \param snprintf_func   The \c snprintf function implementation.
 *
 * \return                \c 0 on success.
 */
int ptls_platform_set_snprintf( int (*snprintf_func)( char * s, size_t n,
                                                 const char * format, ... ) );
#else /* PTLS_PLATFORM_SNPRINTF_ALT */
#if defined(PTLS_PLATFORM_SNPRINTF_MACRO)
#define ptls_snprintf   PTLS_PLATFORM_SNPRINTF_MACRO
#else
#define ptls_snprintf   PTLS_PLATFORM_STD_SNPRINTF
#endif /* PTLS_PLATFORM_SNPRINTF_MACRO */
#endif /* PTLS_PLATFORM_SNPRINTF_ALT */

/*
 * The function pointers for exit
 */
#if defined(PTLS_PLATFORM_EXIT_ALT)
extern void (*ptls_exit)( int status );

/**
 * \brief             This function dynamically configures the exit
 *                    function that is called when the ptls_exit()
 *                    function is invoked by the library.
 *
 * \param exit_func   The \c exit function implementation.
 *
 * \return            \c 0 on success.
 */
int ptls_platform_set_exit( void (*exit_func)( int status ) );
#else
#if defined(PTLS_PLATFORM_EXIT_MACRO)
#define ptls_exit   PTLS_PLATFORM_EXIT_MACRO
#else
#define ptls_exit   exit
#endif /* PTLS_PLATFORM_EXIT_MACRO */
#endif /* PTLS_PLATFORM_EXIT_ALT */

/*
 * The default exit values
 */
#if defined(PTLS_PLATFORM_STD_EXIT_SUCCESS)
#define PTLS_EXIT_SUCCESS PTLS_PLATFORM_STD_EXIT_SUCCESS
#else
#define PTLS_EXIT_SUCCESS 0
#endif
#if defined(PTLS_PLATFORM_STD_EXIT_FAILURE)
#define PTLS_EXIT_FAILURE PTLS_PLATFORM_STD_EXIT_FAILURE
#else
#define PTLS_EXIT_FAILURE 1
#endif

/*
 * The function pointers for reading from and writing a seed file to
 * Non-Volatile storage (NV) in a platform-independent way
 *
 * Only enabled when the NV seed entropy source is enabled
 */
#if defined(PTLS_ENTROPY_NV_SEED)
#if !defined(PTLS_PLATFORM_NO_STD_FUNCTIONS) && defined(PTLS_FS_IO)
/* Internal standard platform definitions */
int ptls_platform_std_nv_seed_read( unsigned char *buf, size_t buf_len );
int ptls_platform_std_nv_seed_write( unsigned char *buf, size_t buf_len );
#endif

#if defined(PTLS_PLATFORM_NV_SEED_ALT)
extern int (*ptls_nv_seed_read)( unsigned char *buf, size_t buf_len );
extern int (*ptls_nv_seed_write)( unsigned char *buf, size_t buf_len );

/**
 * \brief   This function allows configuring custom seed file writing and
 *          reading functions.
 *
 * \param   nv_seed_read_func   The seed reading function implementation.
 * \param   nv_seed_write_func  The seed writing function implementation.
 *
 * \return  \c 0 on success.
 */
int ptls_platform_set_nv_seed(
            int (*nv_seed_read_func)( unsigned char *buf, size_t buf_len ),
            int (*nv_seed_write_func)( unsigned char *buf, size_t buf_len )
            );
#else
#if defined(PTLS_PLATFORM_NV_SEED_READ_MACRO) && \
    defined(PTLS_PLATFORM_NV_SEED_WRITE_MACRO)
#define ptls_nv_seed_read    PTLS_PLATFORM_NV_SEED_READ_MACRO
#define ptls_nv_seed_write   PTLS_PLATFORM_NV_SEED_WRITE_MACRO
#else
#define ptls_nv_seed_read    ptls_platform_std_nv_seed_read
#define ptls_nv_seed_write   ptls_platform_std_nv_seed_write
#endif
#endif /* PTLS_PLATFORM_NV_SEED_ALT */
#endif /* PTLS_ENTROPY_NV_SEED */

#if !defined(PTLS_PLATFORM_SETUP_TEARDOWN_ALT)

/**
 * \brief   The platform context structure.
 *
 * \note    This structure may be used to assist platform-specific
 *          setup or teardown operations.
 */
typedef struct ptls_platform_context
{
    char dummy; /**< A placeholder member, as empty structs are not portable. */
}
ptls_platform_context;

#else
#include "platform_alt.h"
#endif /* !PTLS_PLATFORM_SETUP_TEARDOWN_ALT */

/**
 * \brief   This function performs any platform-specific initialization
 *          operations.
 *
 * \note    This function should be called before any other library functions.
 *
 *          Its implementation is platform-specific, and unless
 *          platform-specific code is provided, it does nothing.
 *
 * \note    The usage and necessity of this function is dependent on the platform.
 *
 * \param   ctx     The platform context.
 *
 * \return  \c 0 on success.
 */
int ptls_platform_setup( ptls_platform_context *ctx );
/**
 * \brief   This function performs any platform teardown operations.
 *
 * \note    This function should be called after every other Mbed TLS module
 *          has been correctly freed using the appropriate free function.
 *
 *          Its implementation is platform-specific, and unless
 *          platform-specific code is provided, it does nothing.
 *
 * \note    The usage and necessity of this function is dependent on the platform.
 *
 * \param   ctx     The platform context.
 *
 */
void ptls_platform_teardown( ptls_platform_context *ctx );

#ifdef __cplusplus
}
#endif

#endif /* platform.h */
