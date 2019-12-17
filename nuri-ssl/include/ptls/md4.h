/**
 * \file md4.h
 *
 * \brief MD4 message digest algorithm (hash function)
 *
 * \warning MD4 is considered a weak message digest and its use constitutes a
 *          security risk. We recommend considering stronger message digests
 *          instead.
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
 *
 */
#ifndef PTLS_MD4_H
#define PTLS_MD4_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#define PTLS_ERR_MD4_HW_ACCEL_FAILED                   -0x002D  /**< MD4 hardware accelerator failed */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(PTLS_MD4_ALT)
// Regular implementation
//

/**
 * \brief          MD4 context structure
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
typedef struct ptls_md4_context
{
    uint32_t total[2];          /*!< number of bytes processed  */
    uint32_t state[4];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */
}
ptls_md4_context;

#else  /* PTLS_MD4_ALT */
#include "md4_alt.h"
#endif /* PTLS_MD4_ALT */

/**
 * \brief          Initialize MD4 context
 *
 * \param ctx      MD4 context to be initialized
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void ptls_md4_init( ptls_md4_context *ctx );

/**
 * \brief          Clear MD4 context
 *
 * \param ctx      MD4 context to be cleared
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void ptls_md4_free( ptls_md4_context *ctx );

/**
 * \brief          Clone (the state of) an MD4 context
 *
 * \param dst      The destination context
 * \param src      The context to be cloned
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void ptls_md4_clone( ptls_md4_context *dst,
                        const ptls_md4_context *src );

/**
 * \brief          MD4 context setup
 *
 * \param ctx      context to be initialized
 *
 * \return         0 if successful
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 */
int ptls_md4_starts_ret( ptls_md4_context *ctx );

/**
 * \brief          MD4 process buffer
 *
 * \param ctx      MD4 context
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 *
 * \return         0 if successful
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md4_update_ret( ptls_md4_context *ctx,
                            const unsigned char *input,
                            size_t ilen );

/**
 * \brief          MD4 final digest
 *
 * \param ctx      MD4 context
 * \param output   MD4 checksum result
 *
 * \return         0 if successful
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md4_finish_ret( ptls_md4_context *ctx,
                            unsigned char output[16] );

/**
 * \brief          MD4 process data block (internal use only)
 *
 * \param ctx      MD4 context
 * \param data     buffer holding one block of data
 *
 * \return         0 if successful
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_internal_md4_process( ptls_md4_context *ctx,
                                  const unsigned char data[64] );

#if !defined(PTLS_DEPRECATED_REMOVED)
#if defined(PTLS_DEPRECATED_WARNING)
#define PTLS_DEPRECATED      __attribute__((deprecated))
#else
#define PTLS_DEPRECATED
#endif
/**
 * \brief          MD4 context setup
 *
 * \deprecated     Superseded by ptls_md4_starts_ret() in 2.7.0
 *
 * \param ctx      context to be initialized
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md4_starts( ptls_md4_context *ctx );

/**
 * \brief          MD4 process buffer
 *
 * \deprecated     Superseded by ptls_md4_update_ret() in 2.7.0
 *
 * \param ctx      MD4 context
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md4_update( ptls_md4_context *ctx,
                                            const unsigned char *input,
                                            size_t ilen );

/**
 * \brief          MD4 final digest
 *
 * \deprecated     Superseded by ptls_md4_finish_ret() in 2.7.0
 *
 * \param ctx      MD4 context
 * \param output   MD4 checksum result
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md4_finish( ptls_md4_context *ctx,
                                            unsigned char output[16] );

/**
 * \brief          MD4 process data block (internal use only)
 *
 * \deprecated     Superseded by ptls_internal_md4_process() in 2.7.0
 *
 * \param ctx      MD4 context
 * \param data     buffer holding one block of data
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md4_process( ptls_md4_context *ctx,
                                             const unsigned char data[64] );

#undef PTLS_DEPRECATED
#endif /* !PTLS_DEPRECATED_REMOVED */

/**
 * \brief          Output = MD4( input buffer )
 *
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 * \param output   MD4 checksum result
 *
 * \return         0 if successful
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md4_ret( const unsigned char *input,
                     size_t ilen,
                     unsigned char output[16] );

#if !defined(PTLS_DEPRECATED_REMOVED)
#if defined(PTLS_DEPRECATED_WARNING)
#define PTLS_DEPRECATED      __attribute__((deprecated))
#else
#define PTLS_DEPRECATED
#endif
/**
 * \brief          Output = MD4( input buffer )
 *
 * \deprecated     Superseded by ptls_md4_ret() in 2.7.0
 *
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 * \param output   MD4 checksum result
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md4( const unsigned char *input,
                                     size_t ilen,
                                     unsigned char output[16] );

#undef PTLS_DEPRECATED
#endif /* !PTLS_DEPRECATED_REMOVED */

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md4_self_test( int verbose );

#ifdef __cplusplus
}
#endif

#endif /* ptls_md4.h */
