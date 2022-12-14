/**
 * \file cipher_internal.h
 *
 * \brief Cipher wrappers.
 *
 * \author Adriaan de Jong <dejong@fox-it.com>
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
#ifndef PTLS_CIPHER_WRAP_H
#define PTLS_CIPHER_WRAP_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include "cipher.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Base cipher information. The non-mode specific functions and values.
 */
struct ptls_cipher_base_t
{
    /** Base Cipher type (e.g. PTLS_CIPHER_ID_AES) */
    ptls_cipher_id_t cipher;

    /** Encrypt using ECB */
    int (*ecb_func)( void *ctx, ptls_operation_t mode,
                     const unsigned char *input, unsigned char *output );

#if defined(PTLS_CIPHER_MODE_CBC)
    /** Encrypt using CBC */
    int (*cbc_func)( void *ctx, ptls_operation_t mode, size_t length,
                     unsigned char *iv, const unsigned char *input,
                     unsigned char *output );
#endif

#if defined(PTLS_CIPHER_MODE_CFB)
    /** Encrypt using CFB (Full length) */
    int (*cfb_func)( void *ctx, ptls_operation_t mode, size_t length, size_t *iv_off,
                     unsigned char *iv, const unsigned char *input,
                     unsigned char *output );
#endif

#if defined(PTLS_CIPHER_MODE_OFB)
    /** Encrypt using OFB (Full length) */
    int (*ofb_func)( void *ctx, size_t length, size_t *iv_off,
                     unsigned char *iv,
                     const unsigned char *input,
                     unsigned char *output );
#endif

#if defined(PTLS_CIPHER_MODE_CTR)
    /** Encrypt using CTR */
    int (*ctr_func)( void *ctx, size_t length, size_t *nc_off,
                     unsigned char *nonce_counter, unsigned char *stream_block,
                     const unsigned char *input, unsigned char *output );
#endif

#if defined(PTLS_CIPHER_MODE_XTS)
    /** Encrypt or decrypt using XTS. */
    int (*xts_func)( void *ctx, ptls_operation_t mode, size_t length,
                     const unsigned char data_unit[16],
                     const unsigned char *input, unsigned char *output );
#endif

#if defined(PTLS_CIPHER_MODE_STREAM)
    /** Encrypt using STREAM */
    int (*stream_func)( void *ctx, size_t length,
                        const unsigned char *input, unsigned char *output );
#endif

    /** Set key for encryption purposes */
    int (*setkey_enc_func)( void *ctx, const unsigned char *key,
                            unsigned int key_bitlen );

    /** Set key for decryption purposes */
    int (*setkey_dec_func)( void *ctx, const unsigned char *key,
                            unsigned int key_bitlen);

    /** Allocate a new context */
    void * (*ctx_alloc_func)( void );

    /** Free the given context */
    void (*ctx_free_func)( void *ctx );

};

typedef struct
{
    ptls_cipher_type_t type;
    const ptls_cipher_info_t *info;
} ptls_cipher_definition_t;

extern const ptls_cipher_definition_t ptls_cipher_definitions[];

extern int ptls_cipher_supported[];

#ifdef __cplusplus
}
#endif

#endif /* PTLS_CIPHER_WRAP_H */
