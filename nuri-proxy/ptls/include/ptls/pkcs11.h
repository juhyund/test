/**
 * \file pkcs11.h
 *
 * \brief Wrapper for PKCS#11 library libpkcs11-helper
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
#ifndef PTLS_PKCS11_H
#define PTLS_PKCS11_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#if defined(PTLS_PKCS11_C)

#include "x509_crt.h"

#include <pkcs11-helper-1.0/pkcs11h-certificate.h>

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Context for PKCS #11 private keys.
 */
typedef struct ptls_pkcs11_context
{
        pkcs11h_certificate_t pkcs11h_cert;
        int len;
} ptls_pkcs11_context;

/**
 * Initialize a ptls_pkcs11_context.
 * (Just making memory references valid.)
 */
void ptls_pkcs11_init( ptls_pkcs11_context *ctx );

/**
 * Fill in a penta TLS certificate, based on the given PKCS11 helper certificate.
 *
 * \param cert          X.509 certificate to fill
 * \param pkcs11h_cert  PKCS #11 helper certificate
 *
 * \return              0 on success.
 */
int ptls_pkcs11_x509_cert_bind( ptls_x509_crt *cert, pkcs11h_certificate_t pkcs11h_cert );

/**
 * Set up a ptls_pkcs11_context storing the given certificate. Note that the
 * ptls_pkcs11_context will take over control of the certificate, freeing it when
 * done.
 *
 * \param priv_key      Private key structure to fill.
 * \param pkcs11_cert   PKCS #11 helper certificate
 *
 * \return              0 on success
 */
int ptls_pkcs11_priv_key_bind( ptls_pkcs11_context *priv_key,
        pkcs11h_certificate_t pkcs11_cert );

/**
 * Free the contents of the given private key context. Note that the structure
 * itself is not freed.
 *
 * \param priv_key      Private key structure to cleanup
 */
void ptls_pkcs11_priv_key_free( ptls_pkcs11_context *priv_key );

/**
 * \brief          Do an RSA private key decrypt, then remove the message
 *                 padding
 *
 * \param ctx      PKCS #11 context
 * \param mode     must be PTLS_RSA_PRIVATE, for compatibility with rsa.c's signature
 * \param input    buffer holding the encrypted data
 * \param output   buffer that will hold the plaintext
 * \param olen     will contain the plaintext length
 * \param output_max_len    maximum length of the output buffer
 *
 * \return         0 if successful, or an PTLS_ERR_RSA_XXX error code
 *
 * \note           The output buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used) otherwise
 *                 an error is thrown.
 */
int ptls_pkcs11_decrypt( ptls_pkcs11_context *ctx,
                       int mode, size_t *olen,
                       const unsigned char *input,
                       unsigned char *output,
                       size_t output_max_len );

/**
 * \brief          Do a private RSA to sign a message digest
 *
 * \param ctx      PKCS #11 context
 * \param mode     must be PTLS_RSA_PRIVATE, for compatibility with rsa.c's signature
 * \param md_alg   a PTLS_MD_XXX (use PTLS_MD_NONE for signing raw data)
 * \param hashlen  message digest length (for PTLS_MD_NONE only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer that will hold the ciphertext
 *
 * \return         0 if the signing operation was successful,
 *                 or an PTLS_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int ptls_pkcs11_sign( ptls_pkcs11_context *ctx,
                    int mode,
                    ptls_md_type_t md_alg,
                    unsigned int hashlen,
                    const unsigned char *hash,
                    unsigned char *sig );

/**
 * SSL/TLS wrappers for PKCS#11 functions
 */
static inline int ptls_ssl_pkcs11_decrypt( void *ctx, int mode, size_t *olen,
                        const unsigned char *input, unsigned char *output,
                        size_t output_max_len )
{
    return ptls_pkcs11_decrypt( (ptls_pkcs11_context *) ctx, mode, olen, input, output,
                           output_max_len );
}

static inline int ptls_ssl_pkcs11_sign( void *ctx,
                     int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                     int mode, ptls_md_type_t md_alg, unsigned int hashlen,
                     const unsigned char *hash, unsigned char *sig )
{
    ((void) f_rng);
    ((void) p_rng);
    return ptls_pkcs11_sign( (ptls_pkcs11_context *) ctx, mode, md_alg,
                        hashlen, hash, sig );
}

static inline size_t ptls_ssl_pkcs11_key_len( void *ctx )
{
    return ( (ptls_pkcs11_context *) ctx )->len;
}

#ifdef __cplusplus
}
#endif

#endif /* PTLS_PKCS11_C */

#endif /* PTLS_PKCS11_H */
