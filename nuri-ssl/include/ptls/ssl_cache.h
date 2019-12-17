/**
 * \file ssl_cache.h
 *
 * \brief SSL session cache implementation
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
#ifndef PTLS_SSL_CACHE_H
#define PTLS_SSL_CACHE_H

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

#if !defined(PTLS_SSL_CACHE_DEFAULT_TIMEOUT)
#define PTLS_SSL_CACHE_DEFAULT_TIMEOUT       86400   /*!< 1 day  */
#endif

#if !defined(PTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES)
#define PTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES      50   /*!< Maximum entries in cache */
#endif

/* \} name SECTION: Module settings */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ptls_ssl_cache_context ptls_ssl_cache_context;
typedef struct ptls_ssl_cache_entry ptls_ssl_cache_entry;

/**
 * \brief   This structure is used for storing cache entries
 */
struct ptls_ssl_cache_entry
{
#if defined(PTLS_HAVE_TIME)
    ptls_time_t timestamp;           /*!< entry timestamp    */
#endif
    ptls_ssl_session session;        /*!< entry session      */
#if defined(PTLS_X509_CRT_PARSE_C)
    ptls_x509_buf peer_cert;         /*!< entry peer_cert    */
#endif
    ptls_ssl_cache_entry *next;      /*!< chain pointer      */
};

/**
 * \brief Cache context
 */
struct ptls_ssl_cache_context
{
    ptls_ssl_cache_entry *chain;     /*!< start of the chain     */
    int timeout;                /*!< cache entry timeout    */
    int max_entries;            /*!< maximum entries        */
#if defined(PTLS_THREADING_C)
    ptls_threading_mutex_t mutex;    /*!< mutex                  */
#endif
};

/**
 * \brief          Initialize an SSL cache context
 *
 * \param cache    SSL cache context
 */
void ptls_ssl_cache_init( ptls_ssl_cache_context *cache );

/**
 * \brief          Cache get callback implementation
 *                 (Thread-safe if PTLS_THREADING_C is enabled)
 *
 * \param data     SSL cache context
 * \param session  session to retrieve entry for
 */
int ptls_ssl_cache_get( void *data, ptls_ssl_session *session );

/**
 * \brief          Cache set callback implementation
 *                 (Thread-safe if PTLS_THREADING_C is enabled)
 *
 * \param data     SSL cache context
 * \param session  session to store entry for
 */
int ptls_ssl_cache_set( void *data, const ptls_ssl_session *session );

#if defined(PTLS_HAVE_TIME)
/**
 * \brief          Set the cache timeout
 *                 (Default: PTLS_SSL_CACHE_DEFAULT_TIMEOUT (1 day))
 *
 *                 A timeout of 0 indicates no timeout.
 *
 * \param cache    SSL cache context
 * \param timeout  cache entry timeout in seconds
 */
void ptls_ssl_cache_set_timeout( ptls_ssl_cache_context *cache, int timeout );
#endif /* PTLS_HAVE_TIME */

/**
 * \brief          Set the maximum number of cache entries
 *                 (Default: PTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES (50))
 *
 * \param cache    SSL cache context
 * \param max      cache entry maximum
 */
void ptls_ssl_cache_set_max_entries( ptls_ssl_cache_context *cache, int max );

/**
 * \brief          Free referenced items in a cache context and clear memory
 *
 * \param cache    SSL cache context
 */
void ptls_ssl_cache_free( ptls_ssl_cache_context *cache );

#ifdef __cplusplus
}
#endif

#endif /* ssl_cache.h */
