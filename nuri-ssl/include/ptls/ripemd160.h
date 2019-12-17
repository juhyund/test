/**
 * \file ripemd160.h
 *
 * \brief RIPE MD-160 message digest
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
#ifndef PTLS_RIPEMD160_H
#define PTLS_RIPEMD160_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#define PTLS_ERR_RIPEMD160_HW_ACCEL_FAILED             -0x0031  /**< RIPEMD160 hardware accelerator failed */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(PTLS_RIPEMD160_ALT)
// Regular implementation
//

/**
 * \brief          RIPEMD-160 context structure
 */
typedef struct ptls_ripemd160_context
{
    uint32_t total[2];          /*!< number of bytes processed  */
    uint32_t state[5];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */
}
ptls_ripemd160_context;

#else  /* PTLS_RIPEMD160_ALT */
#include "ripemd160.h"
#endif /* PTLS_RIPEMD160_ALT */

/**
 * \brief          Initialize RIPEMD-160 context
 *
 * \param ctx      RIPEMD-160 context to be initialized
 */
void ptls_ripemd160_init( ptls_ripemd160_context *ctx );

/**
 * \brief          Clear RIPEMD-160 context
 *
 * \param ctx      RIPEMD-160 context to be cleared
 */
void ptls_ripemd160_free( ptls_ripemd160_context *ctx );

/**
 * \brief          Clone (the state of) an RIPEMD-160 context
 *
 * \param dst      The destination context
 * \param src      The context to be cloned
 */
void ptls_ripemd160_clone( ptls_ripemd160_context *dst,
                        const ptls_ripemd160_context *src );

/**
 * \brief          RIPEMD-160 context setup
 *
 * \param ctx      context to be initialized
 *
 * \return         0 if successful
 */
int ptls_ripemd160_starts_ret( ptls_ripemd160_context *ctx );

/**
 * \brief          RIPEMD-160 process buffer
 *
 * \param ctx      RIPEMD-160 context
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 *
 * \return         0 if successful
 */
int ptls_ripemd160_update_ret( ptls_ripemd160_context *ctx,
                                  const unsigned char *input,
                                  size_t ilen );

/**
 * \brief          RIPEMD-160 final digest
 *
 * \param ctx      RIPEMD-160 context
 * \param output   RIPEMD-160 checksum result
 *
 * \return         0 if successful
 */
int ptls_ripemd160_finish_ret( ptls_ripemd160_context *ctx,
                                  unsigned char output[20] );

/**
 * \brief          RIPEMD-160 process data block (internal use only)
 *
 * \param ctx      RIPEMD-160 context
 * \param data     buffer holding one block of data
 *
 * \return         0 if successful
 */
int ptls_internal_ripemd160_process( ptls_ripemd160_context *ctx,
                                        const unsigned char data[64] );

#if !defined(PTLS_DEPRECATED_REMOVED)
#if defined(PTLS_DEPRECATED_WARNING)
#define PTLS_DEPRECATED      __attribute__((deprecated))
#else
#define PTLS_DEPRECATED
#endif
/**
 * \brief          RIPEMD-160 context setup
 *
 * \deprecated     Superseded by ptls_ripemd160_starts_ret() in 2.7.0
 *
 * \param ctx      context to be initialized
 */
PTLS_DEPRECATED void ptls_ripemd160_starts(
                                            ptls_ripemd160_context *ctx );

/**
 * \brief          RIPEMD-160 process buffer
 *
 * \deprecated     Superseded by ptls_ripemd160_update_ret() in 2.7.0
 *
 * \param ctx      RIPEMD-160 context
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 */
PTLS_DEPRECATED void ptls_ripemd160_update(
                                                ptls_ripemd160_context *ctx,
                                                const unsigned char *input,
                                                size_t ilen );

/**
 * \brief          RIPEMD-160 final digest
 *
 * \deprecated     Superseded by ptls_ripemd160_finish_ret() in 2.7.0
 *
 * \param ctx      RIPEMD-160 context
 * \param output   RIPEMD-160 checksum result
 */
PTLS_DEPRECATED void ptls_ripemd160_finish(
                                                ptls_ripemd160_context *ctx,
                                                unsigned char output[20] );

/**
 * \brief          RIPEMD-160 process data block (internal use only)
 *
 * \deprecated     Superseded by ptls_internal_ripemd160_process() in 2.7.0
 *
 * \param ctx      RIPEMD-160 context
 * \param data     buffer holding one block of data
 */
PTLS_DEPRECATED void ptls_ripemd160_process(
                                            ptls_ripemd160_context *ctx,
                                            const unsigned char data[64] );

#undef PTLS_DEPRECATED
#endif /* !PTLS_DEPRECATED_REMOVED */

/**
 * \brief          Output = RIPEMD-160( input buffer )
 *
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 * \param output   RIPEMD-160 checksum result
 *
 * \return         0 if successful
 */
int ptls_ripemd160_ret( const unsigned char *input,
                           size_t ilen,
                           unsigned char output[20] );

#if !defined(PTLS_DEPRECATED_REMOVED)
#if defined(PTLS_DEPRECATED_WARNING)
#define PTLS_DEPRECATED      __attribute__((deprecated))
#else
#define PTLS_DEPRECATED
#endif
/**
 * \brief          Output = RIPEMD-160( input buffer )
 *
 * \deprecated     Superseded by ptls_ripemd160_ret() in 2.7.0
 *
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 * \param output   RIPEMD-160 checksum result
 */
PTLS_DEPRECATED void ptls_ripemd160( const unsigned char *input,
                                           size_t ilen,
                                           unsigned char output[20] );

#undef PTLS_DEPRECATED
#endif /* !PTLS_DEPRECATED_REMOVED */

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int ptls_ripemd160_self_test( int verbose );

#ifdef __cplusplus
}
#endif

#endif /* ptls_ripemd160.h */
