/**
 * \file threading.h
 *
 * \brief Threading abstraction layer
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
#ifndef PTLS_THREADING_H
#define PTLS_THREADING_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PTLS_ERR_THREADING_FEATURE_UNAVAILABLE         -0x001A  /**< The selected feature is not available. */
#define PTLS_ERR_THREADING_BAD_INPUT_DATA              -0x001C  /**< Bad input parameters to function. */
#define PTLS_ERR_THREADING_MUTEX_ERROR                 -0x001E  /**< Locking / unlocking / free failed with error code. */

#if defined(PTLS_THREADING_PTHREAD)
#include <pthread.h>
typedef struct ptls_threading_mutex_t
{
    pthread_mutex_t mutex;
    char is_valid;
} ptls_threading_mutex_t;
#endif

#if defined(PTLS_THREADING_ALT)
/* You should define the ptls_threading_mutex_t type in your header */
#include "threading_alt.h"

/**
 * \brief           Set your alternate threading implementation function
 *                  pointers and initialize global mutexes. If used, this
 *                  function must be called once in the main thread before any
 *                  other penta TLS function is called, and
 *                  ptls_threading_free_alt() must be called once in the main
 *                  thread after all other penta TLS functions.
 *
 * \note            mutex_init() and mutex_free() don't return a status code.
 *                  If mutex_init() fails, it should leave its argument (the
 *                  mutex) in a state such that mutex_lock() will fail when
 *                  called with this argument.
 *
 * \param mutex_init    the init function implementation
 * \param mutex_free    the free function implementation
 * \param mutex_lock    the lock function implementation
 * \param mutex_unlock  the unlock function implementation
 */
void ptls_threading_set_alt( void (*mutex_init)( ptls_threading_mutex_t * ),
                       void (*mutex_free)( ptls_threading_mutex_t * ),
                       int (*mutex_lock)( ptls_threading_mutex_t * ),
                       int (*mutex_unlock)( ptls_threading_mutex_t * ) );

/**
 * \brief               Free global mutexes.
 */
void ptls_threading_free_alt( void );
#endif /* PTLS_THREADING_ALT */

#if defined(PTLS_THREADING_C)
/*
 * The function pointers for mutex_init, mutex_free, mutex_ and mutex_unlock
 *
 * All these functions are expected to work or the result will be undefined.
 */
extern void (*ptls_mutex_init)( ptls_threading_mutex_t *mutex );
extern void (*ptls_mutex_free)( ptls_threading_mutex_t *mutex );
extern int (*ptls_mutex_lock)( ptls_threading_mutex_t *mutex );
extern int (*ptls_mutex_unlock)( ptls_threading_mutex_t *mutex );

/*
 * Global mutexes
 */
#if defined(PTLS_FS_IO)
extern ptls_threading_mutex_t ptls_threading_readdir_mutex;
#endif
#endif /* PTLS_THREADING_C */

#ifdef __cplusplus
}
#endif

#endif /* threading.h */
