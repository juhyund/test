/**
 * \file ecdsa.h
 *
 * \brief This file contains ECDSA definitions and functions.
 *
 * The Elliptic Curve Digital Signature Algorithm (ECDSA) is defined in
 * <em>Standards for Efficient Cryptography Group (SECG):
 * SEC1 Elliptic Curve Cryptography</em>.
 * The use of ECDSA for TLS is defined in <em>RFC-4492: Elliptic Curve
 * Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS)</em>.
 *
 */
/*
 *  Copyright (C) 2006-2018, Arm Limited (or its affiliates), All Rights Reserved
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
 *  This file is part of Mbed TLS (https://tls.penta.org)
 */

#ifndef PTLS_ECDSA_H
#define PTLS_ECDSA_H

#include "ecp.h"
#include "md.h"

/*
 * RFC-4492 page 20:
 *
 *     Ecdsa-Sig-Value ::= SEQUENCE {
 *         r       INTEGER,
 *         s       INTEGER
 *     }
 *
 * Size is at most
 *    1 (tag) + 1 (len) + 1 (initial 0) + ECP_MAX_BYTES for each of r and s,
 *    twice that + 1 (tag) + 2 (len) for the sequence
 * (assuming ECP_MAX_BYTES is less than 126 for r and s,
 * and less than 124 (total len <= 255) for the sequence)
 */
#if PTLS_ECP_MAX_BYTES > 124
#error "PTLS_ECP_MAX_BYTES bigger than expected, please fix PTLS_ECDSA_MAX_LEN"
#endif
/** The maximal size of an ECDSA signature in Bytes. */
#define PTLS_ECDSA_MAX_LEN  ( 3 + 2 * ( 3 + PTLS_ECP_MAX_BYTES ) )

/**
 * \brief           The ECDSA context structure.
 */
typedef ptls_ecp_keypair ptls_ecdsa_context;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief           This function computes the ECDSA signature of a
 *                  previously-hashed message.
 *
 * \note            The deterministic version is usually preferred.
 *
 * \note            If the bitlength of the message hash is larger than the
 *                  bitlength of the group order, then the hash is truncated
 *                  as defined in <em>Standards for Efficient Cryptography Group
 *                  (SECG): SEC1 Elliptic Curve Cryptography</em>, section
 *                  4.1.3, step 5.
 *
 * \see             ecp.h
 *
 * \param grp       The ECP group.
 * \param r         The first output integer.
 * \param s         The second output integer.
 * \param d         The private signing key.
 * \param buf       The message hash.
 * \param blen      The length of \p buf.
 * \param f_rng     The RNG function.
 * \param p_rng     The RNG context.
 *
 * \return          \c 0 on success.
 * \return          An \c PTLS_ERR_ECP_XXX
 *                  or \c PTLS_MPI_XXX error code on failure.
 */
int ptls_ecdsa_sign( ptls_ecp_group *grp, ptls_mpi *r, ptls_mpi *s,
                const ptls_mpi *d, const unsigned char *buf, size_t blen,
                int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

#if defined(PTLS_ECDSA_DETERMINISTIC)
/**
 * \brief           This function computes the ECDSA signature of a
 *                  previously-hashed message, deterministic version.
 *
 *                  For more information, see <em>RFC-6979: Deterministic
 *                  Usage of the Digital Signature Algorithm (DSA) and Elliptic
 *                  Curve Digital Signature Algorithm (ECDSA)</em>.
 *
 * \note            If the bitlength of the message hash is larger than the
 *                  bitlength of the group order, then the hash is truncated as
 *                  defined in <em>Standards for Efficient Cryptography Group
 *                  (SECG): SEC1 Elliptic Curve Cryptography</em>, section
 *                  4.1.3, step 5.
 *
 * \see             ecp.h
 *
 * \param grp       The ECP group.
 * \param r         The first output integer.
 * \param s         The second output integer.
 * \param d         The private signing key.
 * \param buf       The message hash.
 * \param blen      The length of \p buf.
 * \param md_alg    The MD algorithm used to hash the message.
 *
 * \return          \c 0 on success.
 * \return          An \c PTLS_ERR_ECP_XXX or \c PTLS_MPI_XXX
 *                  error code on failure.
 */
int ptls_ecdsa_sign_det( ptls_ecp_group *grp, ptls_mpi *r, ptls_mpi *s,
                    const ptls_mpi *d, const unsigned char *buf, size_t blen,
                    ptls_md_type_t md_alg );
#endif /* PTLS_ECDSA_DETERMINISTIC */

/**
 * \brief           This function verifies the ECDSA signature of a
 *                  previously-hashed message.
 *
 * \note            If the bitlength of the message hash is larger than the
 *                  bitlength of the group order, then the hash is truncated as
 *                  defined in <em>Standards for Efficient Cryptography Group
 *                  (SECG): SEC1 Elliptic Curve Cryptography</em>, section
 *                  4.1.4, step 3.
 *
 * \see             ecp.h
 *
 * \param grp       The ECP group.
 * \param buf       The message hash.
 * \param blen      The length of \p buf.
 * \param Q         The public key to use for verification.
 * \param r         The first integer of the signature.
 * \param s         The second integer of the signature.
 *
 * \return          \c 0 on success.
 * \return          #PTLS_ERR_ECP_BAD_INPUT_DATA if the signature
 *                  is invalid.
 * \return          An \c PTLS_ERR_ECP_XXX or \c PTLS_MPI_XXX
 *                  error code on failure for any other reason.
 */
int ptls_ecdsa_verify( ptls_ecp_group *grp,
                  const unsigned char *buf, size_t blen,
                  const ptls_ecp_point *Q, const ptls_mpi *r, const ptls_mpi *s);

/**
 * \brief           This function computes the ECDSA signature and writes it
 *                  to a buffer, serialized as defined in <em>RFC-4492:
 *                  Elliptic Curve Cryptography (ECC) Cipher Suites for
 *                  Transport Layer Security (TLS)</em>.
 *
 * \warning         It is not thread-safe to use the same context in
 *                  multiple threads.
 *
 * \note            The deterministic version is used if
 *                  #PTLS_ECDSA_DETERMINISTIC is defined. For more
 *                  information, see <em>RFC-6979: Deterministic Usage
 *                  of the Digital Signature Algorithm (DSA) and Elliptic
 *                  Curve Digital Signature Algorithm (ECDSA)</em>.
 *
 * \note            The \p sig buffer must be at least twice as large as the
 *                  size of the curve used, plus 9. For example, 73 Bytes if
 *                  a 256-bit curve is used. A buffer length of
 *                  #PTLS_ECDSA_MAX_LEN is always safe.
 *
 * \note            If the bitlength of the message hash is larger than the
 *                  bitlength of the group order, then the hash is truncated as
 *                  defined in <em>Standards for Efficient Cryptography Group
 *                  (SECG): SEC1 Elliptic Curve Cryptography</em>, section
 *                  4.1.3, step 5.
 *
 * \see             ecp.h
 *
 * \param ctx       The ECDSA context.
 * \param md_alg    The message digest that was used to hash the message.
 * \param hash      The message hash.
 * \param hlen      The length of the hash.
 * \param sig       The buffer that holds the signature.
 * \param slen      The length of the signature written.
 * \param f_rng     The RNG function.
 * \param p_rng     The RNG context.
 *
 * \return          \c 0 on success.
 * \return          An \c PTLS_ERR_ECP_XXX, \c PTLS_ERR_MPI_XXX or
 *                  \c PTLS_ERR_ASN1_XXX error code on failure.
 */
int ptls_ecdsa_write_signature( ptls_ecdsa_context *ctx, ptls_md_type_t md_alg,
                           const unsigned char *hash, size_t hlen,
                           unsigned char *sig, size_t *slen,
                           int (*f_rng)(void *, unsigned char *, size_t),
                           void *p_rng );

#if defined(PTLS_ECDSA_DETERMINISTIC)
#if ! defined(PTLS_DEPRECATED_REMOVED)
#if defined(PTLS_DEPRECATED_WARNING)
#define PTLS_DEPRECATED    __attribute__((deprecated))
#else
#define PTLS_DEPRECATED
#endif
/**
 * \brief           This function computes an ECDSA signature and writes
 *                  it to a buffer, serialized as defined in <em>RFC-4492:
 *                  Elliptic Curve Cryptography (ECC) Cipher Suites for
 *                  Transport Layer Security (TLS)</em>.
 *
 *                  The deterministic version is defined in <em>RFC-6979:
 *                  Deterministic Usage of the Digital Signature Algorithm (DSA)
 *                  and Elliptic Curve Digital Signature Algorithm (ECDSA)</em>.
 *
 * \warning         It is not thread-safe to use the same context in
 *                  multiple threads.
 *
 * \note            The \p sig buffer must be at least twice as large as the
 *                  size of the curve used, plus 9. For example, 73 Bytes if a
 *                  256-bit curve is used. A buffer length of
 *                  #PTLS_ECDSA_MAX_LEN is always safe.
 *
 * \note            If the bitlength of the message hash is larger than the
 *                  bitlength of the group order, then the hash is truncated as
 *                  defined in <em>Standards for Efficient Cryptography Group
 *                  (SECG): SEC1 Elliptic Curve Cryptography</em>, section
 *                  4.1.3, step 5.
 *
 * \see             ecp.h
 *
 * \deprecated      Superseded by ptls_ecdsa_write_signature() in
 *                  Mbed TLS version 2.0 and later.
 *
 * \param ctx       The ECDSA context.
 * \param hash      The message hash.
 * \param hlen      The length of the hash.
 * \param sig       The buffer that holds the signature.
 * \param slen      The length of the signature written.
 * \param md_alg    The MD algorithm used to hash the message.
 *
 * \return          \c 0 on success.
 * \return          An \c PTLS_ERR_ECP_XXX, \c PTLS_ERR_MPI_XXX or
 *                  \c PTLS_ERR_ASN1_XXX error code on failure.
 */
int ptls_ecdsa_write_signature_det( ptls_ecdsa_context *ctx,
                               const unsigned char *hash, size_t hlen,
                               unsigned char *sig, size_t *slen,
                               ptls_md_type_t md_alg ) PTLS_DEPRECATED;
#undef PTLS_DEPRECATED
#endif /* PTLS_DEPRECATED_REMOVED */
#endif /* PTLS_ECDSA_DETERMINISTIC */

/**
 * \brief           This function reads and verifies an ECDSA signature.
 *
 * \note            If the bitlength of the message hash is larger than the
 *                  bitlength of the group order, then the hash is truncated as
 *                  defined in <em>Standards for Efficient Cryptography Group
 *                  (SECG): SEC1 Elliptic Curve Cryptography</em>, section
 *                  4.1.4, step 3.
 *
 * \see             ecp.h
 *
 * \param ctx       The ECDSA context.
 * \param hash      The message hash.
 * \param hlen      The size of the hash.
 * \param sig       The signature to read and verify.
 * \param slen      The size of \p sig.
 *
 * \return          \c 0 on success.
 * \return          #PTLS_ERR_ECP_BAD_INPUT_DATA if signature is invalid.
 * \return          #PTLS_ERR_ECP_SIG_LEN_MISMATCH if there is a valid
 *                  signature in \p sig, but its length is less than \p siglen.
 * \return          An \c PTLS_ERR_ECP_XXX or \c PTLS_ERR_MPI_XXX
 *                  error code on failure for any other reason.
 */
int ptls_ecdsa_read_signature( ptls_ecdsa_context *ctx,
                          const unsigned char *hash, size_t hlen,
                          const unsigned char *sig, size_t slen );

/**
 * \brief          This function generates an ECDSA keypair on the given curve.
 *
 * \see            ecp.h
 *
 * \param ctx      The ECDSA context to store the keypair in.
 * \param gid      The elliptic curve to use. One of the various
 *                 \c PTLS_ECP_DP_XXX macros depending on configuration.
 * \param f_rng    The RNG function.
 * \param p_rng    The RNG context.
 *
 * \return         \c 0 on success.
 * \return         An \c PTLS_ERR_ECP_XXX code on failure.
 */
int ptls_ecdsa_genkey( ptls_ecdsa_context *ctx, ptls_ecp_group_id gid,
                  int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

/**
 * \brief           This function sets an ECDSA context from an EC key pair.
 *
 * \see             ecp.h
 *
 * \param ctx       The ECDSA context to set.
 * \param key       The EC key to use.
 *
 * \return          \c 0 on success.
 * \return          An \c PTLS_ERR_ECP_XXX code on failure.
 */
int ptls_ecdsa_from_keypair( ptls_ecdsa_context *ctx, const ptls_ecp_keypair *key );

/**
 * \brief           This function initializes an ECDSA context.
 *
 * \param ctx       The ECDSA context to initialize.
 */
void ptls_ecdsa_init( ptls_ecdsa_context *ctx );

/**
 * \brief           This function frees an ECDSA context.
 *
 * \param ctx       The ECDSA context to free.
 */
void ptls_ecdsa_free( ptls_ecdsa_context *ctx );

#ifdef __cplusplus
}
#endif

#endif /* ecdsa.h */
