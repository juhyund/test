/**
 * \file md2.h
 *
 * \brief MD2 message digest algorithm (hash function)
 *
 * \warning MD2 is considered a weak message digest and its use constitutes a
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
#ifndef PTLS_MD2_H
#define PTLS_MD2_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include <stddef.h>

#define PTLS_ERR_MD2_HW_ACCEL_FAILED                   -0x002B  /**< MD2 hardware accelerator failed */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(PTLS_MD2_ALT)
// Regular implementation
//

/**
 * \brief          MD2 context structure
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
typedef struct ptls_md2_context
{
    unsigned char cksum[16];    /*!< checksum of the data block */
    unsigned char state[48];    /*!< intermediate digest state  */
    unsigned char buffer[16];   /*!< data block being processed */
    size_t left;                /*!< amount of data in buffer   */
}
ptls_md2_context;

#else  /* PTLS_MD2_ALT */
#include "md2_alt.h"
#endif /* PTLS_MD2_ALT */

/**
 * \brief          Initialize MD2 context
 *
 * \param ctx      MD2 context to be initialized
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void ptls_md2_init( ptls_md2_context *ctx );

/**
 * \brief          Clear MD2 context
 *
 * \param ctx      MD2 context to be cleared
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void ptls_md2_free( ptls_md2_context *ctx );

/**
 * \brief          Clone (the state of) an MD2 context
 *
 * \param dst      The destination context
 * \param src      The context to be cloned
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void ptls_md2_clone( ptls_md2_context *dst,
                        const ptls_md2_context *src );

/**
 * \brief          MD2 context setup
 *
 * \param ctx      context to be initialized
 *
 * \return         0 if successful
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md2_starts_ret( ptls_md2_context *ctx );

/**
 * \brief          MD2 process buffer
 *
 * \param ctx      MD2 context
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 *
 * \return         0 if successful
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md2_update_ret( ptls_md2_context *ctx,
                            const unsigned char *input,
                            size_t ilen );

/**
 * \brief          MD2 final digest
 *
 * \param ctx      MD2 context
 * \param output   MD2 checksum result
 *
 * \return         0 if successful
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md2_finish_ret( ptls_md2_context *ctx,
                            unsigned char output[16] );

/**
 * \brief          MD2 process data block (internal use only)
 *
 * \param ctx      MD2 context
 *
 * \return         0 if successful
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_internal_md2_process( ptls_md2_context *ctx );

#if !defined(PTLS_DEPRECATED_REMOVED)
#if defined(PTLS_DEPRECATED_WARNING)
#define PTLS_DEPRECATED      __attribute__((deprecated))
#else
#define PTLS_DEPRECATED
#endif
/**
 * \brief          MD2 context setup
 *
 * \deprecated     Superseded by ptls_md2_starts_ret() in 2.7.0
 *
 * \param ctx      context to be initialized
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md2_starts( ptls_md2_context *ctx );

/**
 * \brief          MD2 process buffer
 *
 * \deprecated     Superseded by ptls_md2_update_ret() in 2.7.0
 *
 * \param ctx      MD2 context
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md2_update( ptls_md2_context *ctx,
                                            const unsigned char *input,
                                            size_t ilen );

/**
 * \brief          MD2 final digest
 *
 * \deprecated     Superseded by ptls_md2_finish_ret() in 2.7.0
 *
 * \param ctx      MD2 context
 * \param output   MD2 checksum result
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md2_finish( ptls_md2_context *ctx,
                                            unsigned char output[16] );

/**
 * \brief          MD2 process data block (internal use only)
 *
 * \deprecated     Superseded by ptls_internal_md2_process() in 2.7.0
 *
 * \param ctx      MD2 context
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md2_process( ptls_md2_context *ctx );

#undef PTLS_DEPRECATED
#endif /* !PTLS_DEPRECATED_REMOVED */

/**
 * \brief          Output = MD2( input buffer )
 *
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 * \param output   MD2 checksum result
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md2_ret( const unsigned char *input,
                     size_t ilen,
                     unsigned char output[16] );

#if !defined(PTLS_DEPRECATED_REMOVED)
#if defined(PTLS_DEPRECATED_WARNING)
#define PTLS_DEPRECATED      __attribute__((deprecated))
#else
#define PTLS_DEPRECATED
#endif
/**
 * \brief          Output = MD2( input buffer )
 *
 * \deprecated     Superseded by ptls_md2_ret() in 2.7.0
 *
 * \param input    buffer holding the data
 * \param ilen     length of the input data
 * \param output   MD2 checksum result
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
PTLS_DEPRECATED void ptls_md2( const unsigned char *input,
                                     size_t ilen,
                                     unsigned char output[16] );

#undef PTLS_DEPRECATED
#endif /* !PTLS_DEPRECATED_REMOVED */

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 *
 * \warning        MD2 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int ptls_md2_self_test( int verbose );

#ifdef __cplusplus
}
#endif

#endif /* ptls_md2.h */
