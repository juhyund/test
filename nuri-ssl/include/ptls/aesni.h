/**
 * \file aesni.h
 *
 * \brief AES-NI for hardware AES acceleration on some Intel processors
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
#ifndef PTLS_AESNI_H
#define PTLS_AESNI_H

#include "aes.h"

#define PTLS_AESNI_AES      0x02000000u
#define PTLS_AESNI_CLMUL    0x00000002u

#if defined(PTLS_HAVE_ASM) && defined(__GNUC__) &&  \
    ( defined(__amd64__) || defined(__x86_64__) )   &&  \
    ! defined(PTLS_HAVE_X86_64)
#define PTLS_HAVE_X86_64
#endif

#if defined(PTLS_HAVE_X86_64)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          AES-NI features detection routine
 *
 * \param what     The feature to detect
 *                 (PTLS_AESNI_AES or PTLS_AESNI_CLMUL)
 *
 * \return         1 if CPU has support for the feature, 0 otherwise
 */
int ptls_aesni_has_support( unsigned int what );

/**
 * \brief          AES-NI AES-ECB block en(de)cryption
 *
 * \param ctx      AES context
 * \param mode     PTLS_AES_ENCRYPT or PTLS_AES_DECRYPT
 * \param input    16-byte input block
 * \param output   16-byte output block
 *
 * \return         0 on success (cannot fail)
 */
int ptls_aesni_crypt_ecb( ptls_aes_context *ctx,
                     int mode,
                     const unsigned char input[16],
                     unsigned char output[16] );

/**
 * \brief          GCM multiplication: c = a * b in GF(2^128)
 *
 * \param c        Result
 * \param a        First operand
 * \param b        Second operand
 *
 * \note           Both operands and result are bit strings interpreted as
 *                 elements of GF(2^128) as per the GCM spec.
 */
void ptls_aesni_gcm_mult( unsigned char c[16],
                     const unsigned char a[16],
                     const unsigned char b[16] );

/**
 * \brief           Compute decryption round keys from encryption round keys
 *
 * \param invkey    Round keys for the equivalent inverse cipher
 * \param fwdkey    Original round keys (for encryption)
 * \param nr        Number of rounds (that is, number of round keys minus one)
 */
void ptls_aesni_inverse_key( unsigned char *invkey,
                        const unsigned char *fwdkey, int nr );

/**
 * \brief           Perform key expansion (for encryption)
 *
 * \param rk        Destination buffer where the round keys are written
 * \param key       Encryption key
 * \param bits      Key size in bits (must be 128, 192 or 256)
 *
 * \return          0 if successful, or PTLS_ERR_AES_INVALID_KEY_LENGTH
 */
int ptls_aesni_setkey_enc( unsigned char *rk,
                      const unsigned char *key,
                      size_t bits );

#ifdef __cplusplus
}
#endif

#endif /* PTLS_HAVE_X86_64 */

#endif /* PTLS_AESNI_H */
