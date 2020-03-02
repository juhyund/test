/**
 * \file aria.h
 *
 * \brief ARIA block cipher
 *
 *        The ARIA algorithm is a symmetric block cipher that can encrypt and
 *        decrypt information. It is defined by the Korean Agency for
 *        Technology and Standards (KATS) in <em>KS X 1213:2004</em> (in
 *        Korean, but see http://210.104.33.10/ARIA/index-e.html in English)
 *        and also described by the IETF in <em>RFC 5794</em>.
 */
/*  Copyright (C) 2006-2018, ARM Limited, All Rights Reserved
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

#ifndef PTLS_ARIA_H
#define PTLS_ARIA_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#define PTLS_ARIA_ENCRYPT     1 /**< ARIA encryption. */
#define PTLS_ARIA_DECRYPT     0 /**< ARIA decryption. */

#define PTLS_ARIA_BLOCKSIZE   16 /**< ARIA block size in bytes. */
#define PTLS_ARIA_MAX_ROUNDS  16 /**< Maxiumum number of rounds in ARIA. */
#define PTLS_ARIA_MAX_KEYSIZE 32 /**< Maximum size of an ARIA key in bytes. */

#define PTLS_ERR_ARIA_INVALID_KEY_LENGTH   -0x005C  /**< Invalid key length. */
#define PTLS_ERR_ARIA_INVALID_INPUT_LENGTH -0x005E  /**< Invalid data input length. */
#define PTLS_ERR_ARIA_FEATURE_UNAVAILABLE  -0x005A  /**< Feature not available. For example, an unsupported ARIA key size. */
#define PTLS_ERR_ARIA_HW_ACCEL_FAILED      -0x0058  /**< ARIA hardware accelerator failed. */

#if !defined(PTLS_ARIA_ALT)
// Regular implementation
//

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief The ARIA context-type definition.
 */
typedef struct ptls_aria_context
{
    unsigned char nr;           /*!< The number of rounds (12, 14 or 16) */
    /*! The ARIA round keys. */
    uint32_t rk[PTLS_ARIA_MAX_ROUNDS + 1][PTLS_ARIA_BLOCKSIZE / 4];
}
ptls_aria_context;

#else  /* PTLS_ARIA_ALT */
#include "aria_alt.h"
#endif /* PTLS_ARIA_ALT */

/**
 * \brief          This function initializes the specified ARIA context.
 *
 *                 It must be the first API called before using
 *                 the context.
 *
 * \param ctx      The ARIA context to initialize.
 */
void ptls_aria_init( ptls_aria_context *ctx );

/**
 * \brief          This function releases and clears the specified ARIA context.
 *
 * \param ctx      The ARIA context to clear.
 */
void ptls_aria_free( ptls_aria_context *ctx );

/**
 * \brief          This function sets the encryption key.
 *
 * \param ctx      The ARIA context to which the key should be bound.
 * \param key      The encryption key.
 * \param keybits  The size of data passed in bits. Valid options are:
 *                 <ul><li>128 bits</li>
 *                 <li>192 bits</li>
 *                 <li>256 bits</li></ul>
 *
 * \return         \c 0 on success or #PTLS_ERR_ARIA_INVALID_KEY_LENGTH
 *                 on failure.
 */
int ptls_aria_setkey_enc( ptls_aria_context *ctx,
                             const unsigned char *key,
                             unsigned int keybits );

/**
 * \brief          This function sets the decryption key.
 *
 * \param ctx      The ARIA context to which the key should be bound.
 * \param key      The decryption key.
 * \param keybits  The size of data passed. Valid options are:
 *                 <ul><li>128 bits</li>
 *                 <li>192 bits</li>
 *                 <li>256 bits</li></ul>
 *
 * \return         \c 0 on success, or #PTLS_ERR_ARIA_INVALID_KEY_LENGTH on failure.
 */
int ptls_aria_setkey_dec( ptls_aria_context *ctx,
                             const unsigned char *key,
                             unsigned int keybits );

/**
 * \brief          This function performs an ARIA single-block encryption or
 *                 decryption operation.
 *
 *                 It performs encryption or decryption (depending on whether
 *                 the key was set for encryption on decryption) on the input
 *                 data buffer defined in the \p input parameter.
 *
 *                 ptls_aria_init(), and either ptls_aria_setkey_enc() or
 *                 ptls_aria_setkey_dec() must be called before the first
 *                 call to this API with the same context.
 *
 * \param ctx      The ARIA context to use for encryption or decryption.
 * \param input    The 16-Byte buffer holding the input data.
 * \param output   The 16-Byte buffer holding the output data.

 * \return         \c 0 on success.
 */
int ptls_aria_crypt_ecb( ptls_aria_context *ctx,
                            const unsigned char input[PTLS_ARIA_BLOCKSIZE],
                            unsigned char output[PTLS_ARIA_BLOCKSIZE] );

#if defined(PTLS_CIPHER_MODE_CBC)
/**
 * \brief  This function performs an ARIA-CBC encryption or decryption operation
 *         on full blocks.
 *
 *         It performs the operation defined in the \p mode
 *         parameter (encrypt/decrypt), on the input data buffer defined in
 *         the \p input parameter.
 *
 *         It can be called as many times as needed, until all the input
 *         data is processed. ptls_aria_init(), and either
 *         ptls_aria_setkey_enc() or ptls_aria_setkey_dec() must be called
 *         before the first call to this API with the same context.
 *
 * \note   This function operates on aligned blocks, that is, the input size
 *         must be a multiple of the ARIA block size of 16 Bytes.
 *
 * \note   Upon exit, the content of the IV is updated so that you can
 *         call the same function again on the next
 *         block(s) of data and get the same result as if it was
 *         encrypted in one call. This allows a "streaming" usage.
 *         If you need to retain the contents of the IV, you should
 *         either save it manually or use the cipher module instead.
 *
 *
 * \param ctx      The ARIA context to use for encryption or decryption.
 * \param mode     The ARIA operation: #PTLS_ARIA_ENCRYPT or
 *                 #PTLS_ARIA_DECRYPT.
 * \param length   The length of the input data in Bytes. This must be a
 *                 multiple of the block size (16 Bytes).
 * \param iv       Initialization vector (updated after use).
 * \param input    The buffer holding the input data.
 * \param output   The buffer holding the output data.
 *
 * \return         \c 0 on success, or #PTLS_ERR_ARIA_INVALID_INPUT_LENGTH
 *                 on failure.
 */
int ptls_aria_crypt_cbc( ptls_aria_context *ctx,
                            int mode,
                            size_t length,
                            unsigned char iv[PTLS_ARIA_BLOCKSIZE],
                            const unsigned char *input,
                            unsigned char *output );
#endif /* PTLS_CIPHER_MODE_CBC */

#if defined(PTLS_CIPHER_MODE_CFB)
/**
 * \brief This function performs an ARIA-CFB128 encryption or decryption
 *        operation.
 *
 *        It performs the operation defined in the \p mode
 *        parameter (encrypt or decrypt), on the input data buffer
 *        defined in the \p input parameter.
 *
 *        For CFB, you must set up the context with ptls_aria_setkey_enc(),
 *        regardless of whether you are performing an encryption or decryption
 *        operation, that is, regardless of the \p mode parameter. This is
 *        because CFB mode uses the same key schedule for encryption and
 *        decryption.
 *
 * \note  Upon exit, the content of the IV is updated so that you can
 *        call the same function again on the next
 *        block(s) of data and get the same result as if it was
 *        encrypted in one call. This allows a "streaming" usage.
 *        If you need to retain the contents of the
 *        IV, you must either save it manually or use the cipher
 *        module instead.
 *
 *
 * \param ctx      The ARIA context to use for encryption or decryption.
 * \param mode     The ARIA operation: #PTLS_ARIA_ENCRYPT or
 *                 #PTLS_ARIA_DECRYPT.
 * \param length   The length of the input data.
 * \param iv_off   The offset in IV (updated after use).
 * \param iv       The initialization vector (updated after use).
 * \param input    The buffer holding the input data.
 * \param output   The buffer holding the output data.
 *
 * \return         \c 0 on success.
 */
int ptls_aria_crypt_cfb128( ptls_aria_context *ctx,
                               int mode,
                               size_t length,
                               size_t *iv_off,
                               unsigned char iv[PTLS_ARIA_BLOCKSIZE],
                               const unsigned char *input,
                               unsigned char *output );
#endif /* PTLS_CIPHER_MODE_CFB */

#if defined(PTLS_CIPHER_MODE_CTR)
/**
 * \brief      This function performs an ARIA-CTR encryption or decryption
 *             operation.
 *
 *             This function performs the operation defined in the \p mode
 *             parameter (encrypt/decrypt), on the input data buffer
 *             defined in the \p input parameter.
 *
 *             Due to the nature of CTR, you must use the same key schedule
 *             for both encryption and decryption operations. Therefore, you
 *             must use the context initialized with ptls_aria_setkey_enc()
 *             for both #PTLS_ARIA_ENCRYPT and #PTLS_ARIA_DECRYPT.
 *
 * \warning    You must never reuse a nonce value with the same key. Doing so
 *             would void the encryption for the two messages encrypted with
 *             the same nonce and key.
 *
 *             There are two common strategies for managing nonces with CTR:
 *
 *             1. You can handle everything as a single message processed over
 *             successive calls to this function. In that case, you want to
 *             set \p nonce_counter and \p nc_off to 0 for the first call, and
 *             then preserve the values of \p nonce_counter, \p nc_off and \p
 *             stream_block across calls to this function as they will be
 *             updated by this function.
 *
 *             With this strategy, you must not encrypt more than 2**128
 *             blocks of data with the same key.
 *
 *             2. You can encrypt separate messages by dividing the \p
 *             nonce_counter buffer in two areas: the first one used for a
 *             per-message nonce, handled by yourself, and the second one
 *             updated by this function internally.
 *
 *             For example, you might reserve the first 12 bytes for the
 *             per-message nonce, and the last 4 bytes for internal use. In that
 *             case, before calling this function on a new message you need to
 *             set the first 12 bytes of \p nonce_counter to your chosen nonce
 *             value, the last 4 to 0, and \p nc_off to 0 (which will cause \p
 *             stream_block to be ignored). That way, you can encrypt at most
 *             2**96 messages of up to 2**32 blocks each with the same key.
 *
 *             The per-message nonce (or information sufficient to reconstruct
 *             it) needs to be communicated with the ciphertext and must be unique.
 *             The recommended way to ensure uniqueness is to use a message
 *             counter. An alternative is to generate random nonces, but this
 *             limits the number of messages that can be securely encrypted:
 *             for example, with 96-bit random nonces, you should not encrypt
 *             more than 2**32 messages with the same key.
 *
 *             Note that for both stategies, sizes are measured in blocks and
 *             that an ARIA block is 16 bytes.
 *
 * \warning    Upon return, \p stream_block contains sensitive data. Its
 *             content must not be written to insecure storage and should be
 *             securely discarded as soon as it's no longer needed.
 *
 * \param ctx              The ARIA context to use for encryption or decryption.
 * \param length           The length of the input data.
 * \param nc_off           The offset in the current \p stream_block, for
 *                         resuming within the current cipher stream. The
 *                         offset pointer should be 0 at the start of a stream.
 * \param nonce_counter    The 128-bit nonce and counter.
 * \param stream_block     The saved stream block for resuming. This is
 *                         overwritten by the function.
 * \param input            The buffer holding the input data.
 * \param output           The buffer holding the output data.
 *
 * \return     \c 0 on success.
 */
int ptls_aria_crypt_ctr( ptls_aria_context *ctx,
                            size_t length,
                            size_t *nc_off,
                            unsigned char nonce_counter[PTLS_ARIA_BLOCKSIZE],
                            unsigned char stream_block[PTLS_ARIA_BLOCKSIZE],
                            const unsigned char *input,
                            unsigned char *output );
#endif /* PTLS_CIPHER_MODE_CTR */

#if defined(PTLS_SELF_TEST)
/**
 * \brief          Checkup routine.
 *
 * \return         \c 0 on success, or \c 1 on failure.
 */
int ptls_aria_self_test( int verbose );
#endif /* PTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* aria.h */