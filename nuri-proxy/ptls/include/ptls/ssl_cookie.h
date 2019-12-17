/**
 * \file ssl_cookie.h
 *
 * \brief DTLS cookie callbacks implementation
 */
/*
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
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
 *  This file is part of penta TLS (https://tls.penta.org)
 */
#ifndef PTLS_SSL_COOKIE_H
#define PTLS_SSL_COOKIE_H

#include "ssl.h"

#if defined(PTLS_THREADING_C)
#include "threading.h"
#endif

/**
 * \name SECTION: Module settings
 *
 * The configuration options you can set for this module are in this section.
 * Either change them in config.h or define them on the compiler command line.
 * \{
 */
#ifndef PTLS_SSL_COOKIE_TIMEOUT
#define PTLS_SSL_COOKIE_TIMEOUT     60 /**< Default expiration delay of DTLS cookies, in seconds if HAVE_TIME, or in number of cookies issued */
#endif

/* \} name SECTION: Module settings */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Context for the default cookie functions.
 */
typedef struct ptls_ssl_cookie_ctx
{
    ptls_md_context_t    hmac_ctx;   /*!< context for the HMAC portion   */
#if !defined(PTLS_HAVE_TIME)
    unsigned long   serial;     /*!< serial number for expiration   */
#endif
    unsigned long   timeout;    /*!< timeout delay, in seconds if HAVE_TIME,
                                     or in number of tickets issued */

#if defined(PTLS_THREADING_C)
    ptls_threading_mutex_t mutex;
#endif
} ptls_ssl_cookie_ctx;

/**
 * \brief          Initialize cookie context
 */
void ptls_ssl_cookie_init( ptls_ssl_cookie_ctx *ctx );

/**
 * \brief          Setup cookie context (generate keys)
 */
int ptls_ssl_cookie_setup( ptls_ssl_cookie_ctx *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng );

/**
 * \brief          Set expiration delay for cookies
 *                 (Default PTLS_SSL_COOKIE_TIMEOUT)
 *
 * \param ctx      Cookie contex
 * \param delay    Delay, in seconds if HAVE_TIME, or in number of cookies
 *                 issued in the meantime.
 *                 0 to disable expiration (NOT recommended)
 */
void ptls_ssl_cookie_set_timeout( ptls_ssl_cookie_ctx *ctx, unsigned long delay );

/**
 * \brief          Free cookie context
 */
void ptls_ssl_cookie_free( ptls_ssl_cookie_ctx *ctx );

/**
 * \brief          Generate cookie, see \c ptls_ssl_cookie_write_t
 */
ptls_ssl_cookie_write_t ptls_ssl_cookie_write;

/**
 * \brief          Verify cookie, see \c ptls_ssl_cookie_write_t
 */
ptls_ssl_cookie_check_t ptls_ssl_cookie_check;

#ifdef __cplusplus
}
#endif

#endif /* ssl_cookie.h */
