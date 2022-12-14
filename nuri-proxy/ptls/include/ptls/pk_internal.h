/**
 * \file pk_internal.h
 *
 * \brief Public Key abstraction layer: wrapper functions
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

#ifndef PTLS_PK_WRAP_H
#define PTLS_PK_WRAP_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include "pk.h"

struct ptls_pk_info_t
{
    /** Public key type */
    ptls_pk_type_t type;

    /** Type name */
    const char *name;

    /** Get key size in bits */
    size_t (*get_bitlen)( const void * );

    /** Tell if the context implements this type (e.g. ECKEY can do ECDSA) */
    int (*can_do)( ptls_pk_type_t type );

    /** Verify signature */
    int (*verify_func)( void *ctx, ptls_md_type_t md_alg,
                        const unsigned char *hash, size_t hash_len,
                        const unsigned char *sig, size_t sig_len );

    /** Make signature */
    int (*sign_func)( void *ctx, ptls_md_type_t md_alg,
                      const unsigned char *hash, size_t hash_len,
                      unsigned char *sig, size_t *sig_len,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng );

    /** Decrypt message */
    int (*decrypt_func)( void *ctx, const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen, size_t osize,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng );

    /** Encrypt message */
    int (*encrypt_func)( void *ctx, const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen, size_t osize,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng );

    /** Check public-private key pair */
    int (*check_pair_func)( const void *pub, const void *prv );

    /** Allocate a new context */
    void * (*ctx_alloc_func)( void );

    /** Free the given context */
    void (*ctx_free_func)( void *ctx );

    /** Interface with the debug module */
    void (*debug_func)( const void *ctx, ptls_pk_debug_item *items );

};
#if defined(PTLS_PK_RSA_ALT_SUPPORT)
/* Container for RSA-alt */
typedef struct
{
    void *key;
    ptls_pk_rsa_alt_decrypt_func decrypt_func;
    ptls_pk_rsa_alt_sign_func sign_func;
    ptls_pk_rsa_alt_key_len_func key_len_func;
} ptls_rsa_alt_context;
#endif

#if defined(PTLS_RSA_C)
extern const ptls_pk_info_t ptls_rsa_info;
#endif

#if defined(PTLS_ECP_C)
extern const ptls_pk_info_t ptls_eckey_info;
extern const ptls_pk_info_t ptls_eckeydh_info;
#endif

#if defined(PTLS_ECDSA_C)
extern const ptls_pk_info_t ptls_ecdsa_info;
#endif

#if defined(PTLS_PK_RSA_ALT_SUPPORT)
extern const ptls_pk_info_t ptls_rsa_alt_info;
#endif

#endif /* PTLS_PK_WRAP_H */
