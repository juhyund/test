/**
 * \file pkcs12.h
 *
 * \brief PKCS#12 Personal Information Exchange Syntax
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
#ifndef PTLS_PKCS12_H
#define PTLS_PKCS12_H

#include "md.h"
#include "cipher.h"
#include "asn1.h"

#include <stddef.h>

#define PTLS_ERR_PKCS12_BAD_INPUT_DATA                 -0x1F80  /**< Bad input parameters to function. */
#define PTLS_ERR_PKCS12_FEATURE_UNAVAILABLE            -0x1F00  /**< Feature not available, e.g. unsupported encryption scheme. */
#define PTLS_ERR_PKCS12_PBE_INVALID_FORMAT             -0x1E80  /**< PBE ASN.1 data not as expected. */
#define PTLS_ERR_PKCS12_PASSWORD_MISMATCH              -0x1E00  /**< Given private key password does not allow for correct decryption. */

#define PTLS_PKCS12_DERIVE_KEY       1   /**< encryption/decryption key */
#define PTLS_PKCS12_DERIVE_IV        2   /**< initialization vector     */
#define PTLS_PKCS12_DERIVE_MAC_KEY   3   /**< integrity / MAC key       */

#define PTLS_PKCS12_PBE_DECRYPT      0
#define PTLS_PKCS12_PBE_ENCRYPT      1

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief            PKCS12 Password Based function (encryption / decryption)
 *                   for pbeWithSHAAnd128BitRC4
 *
 * \param pbe_params an ASN1 buffer containing the pkcs-12PbeParams structure
 * \param mode       either PTLS_PKCS12_PBE_ENCRYPT or PTLS_PKCS12_PBE_DECRYPT
 * \param pwd        the password used (may be NULL if no password is used)
 * \param pwdlen     length of the password (may be 0)
 * \param input      the input data
 * \param len        data length
 * \param output     the output buffer
 *
 * \return           0 if successful, or a PTLS_ERR_XXX code
 */
int ptls_pkcs12_pbe_sha1_rc4_128( ptls_asn1_buf *pbe_params, int mode,
                             const unsigned char *pwd,  size_t pwdlen,
                             const unsigned char *input, size_t len,
                             unsigned char *output );

/**
 * \brief            PKCS12 Password Based function (encryption / decryption)
 *                   for cipher-based and ptls_md-based PBE's
 *
 * \param pbe_params an ASN1 buffer containing the pkcs-12PbeParams structure
 * \param mode       either PTLS_PKCS12_PBE_ENCRYPT or PTLS_PKCS12_PBE_DECRYPT
 * \param cipher_type the cipher used
 * \param md_type     the ptls_md used
 * \param pwd        the password used (may be NULL if no password is used)
 * \param pwdlen     length of the password (may be 0)
 * \param input      the input data
 * \param len        data length
 * \param output     the output buffer
 *
 * \return           0 if successful, or a PTLS_ERR_XXX code
 */
int ptls_pkcs12_pbe( ptls_asn1_buf *pbe_params, int mode,
                ptls_cipher_type_t cipher_type, ptls_md_type_t md_type,
                const unsigned char *pwd,  size_t pwdlen,
                const unsigned char *input, size_t len,
                unsigned char *output );

/**
 * \brief            The PKCS#12 derivation function uses a password and a salt
 *                   to produce pseudo-random bits for a particular "purpose".
 *
 *                   Depending on the given id, this function can produce an
 *                   encryption/decryption key, an nitialization vector or an
 *                   integrity key.
 *
 * \param data       buffer to store the derived data in
 * \param datalen    length to fill
 * \param pwd        password to use (may be NULL if no password is used)
 * \param pwdlen     length of the password (may be 0)
 * \param salt       salt buffer to use
 * \param saltlen    length of the salt
 * \param ptls_md         ptls_md type to use during the derivation
 * \param id         id that describes the purpose (can be PTLS_PKCS12_DERIVE_KEY,
 *                   PTLS_PKCS12_DERIVE_IV or PTLS_PKCS12_DERIVE_MAC_KEY)
 * \param iterations number of iterations
 *
 * \return          0 if successful, or a MD, BIGNUM type error.
 */
int ptls_pkcs12_derivation( unsigned char *data, size_t datalen,
                       const unsigned char *pwd, size_t pwdlen,
                       const unsigned char *salt, size_t saltlen,
                       ptls_md_type_t ptls_md, int id, int iterations );

#ifdef __cplusplus
}
#endif

#endif /* pkcs12.h */
