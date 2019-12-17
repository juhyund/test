/**
 * \file check_config.h
 *
 * \brief Consistency checks for configuration options
 */
/*
 *  Copyright (C) 2006-2018, ARM Limited, All Rights Reserved
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

/*
 * It is recommended to include this file from your config.h
 * in order to catch dependency issues early.
 */

#ifndef PTLS_CHECK_CONFIG_H
#define PTLS_CHECK_CONFIG_H

/*
 * We assume CHAR_BIT is 8 in many places. In practice, this is true on our
 * target platforms, so not an issue, but let's just be extra sure.
 */
#include <limits.h>
#if CHAR_BIT != 8
#error "penta TLS requires a platform with 8-bit chars"
#endif

#if defined(_WIN32)
#if !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_C is required on Windows"
#endif

/* Fix the config here. Not convenient to put an #ifdef _WIN32 in config.h as
 * it would confuse config.pl. */
#if !defined(PTLS_PLATFORM_SNPRINTF_ALT) && \
    !defined(PTLS_PLATFORM_SNPRINTF_MACRO)
#define PTLS_PLATFORM_SNPRINTF_ALT
#endif
#endif /* _WIN32 */

#if defined(TARGET_LIKE_MBED) && \
    ( defined(PTLS_NET_C) || defined(PTLS_TIMING_C) )
#error "The NET and TIMING modules are not available for penta OS - please use the network and timing functions provided by penta OS"
#endif

#if defined(PTLS_DEPRECATED_WARNING) && \
    !defined(__GNUC__) && !defined(__clang__)
#error "PTLS_DEPRECATED_WARNING only works with GCC and Clang"
#endif

#if defined(PTLS_HAVE_TIME_DATE) && !defined(PTLS_HAVE_TIME)
#error "PTLS_HAVE_TIME_DATE without PTLS_HAVE_TIME does not make sense"
#endif

#if defined(PTLS_AESNI_C) && !defined(PTLS_HAVE_ASM)
#error "PTLS_AESNI_C defined, but not all prerequisites"
#endif

#if defined(PTLS_CTR_DRBG_C) && !defined(PTLS_AES_C)
#error "PTLS_CTR_DRBG_C defined, but not all prerequisites"
#endif

#if defined(PTLS_DHM_C) && !defined(PTLS_BIGNUM_C)
#error "PTLS_DHM_C defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_TRUNCATED_HMAC_COMPAT) && !defined(PTLS_SSL_TRUNCATED_HMAC)
#error "PTLS_SSL_TRUNCATED_HMAC_COMPAT defined, but not all prerequisites"
#endif

#if defined(PTLS_CMAC_C) && \
    !defined(PTLS_AES_C) && !defined(PTLS_DES_C)
#error "PTLS_CMAC_C defined, but not all prerequisites"
#endif

#if defined(PTLS_NIST_KW_C) && \
    ( !defined(PTLS_AES_C) || !defined(PTLS_CIPHER_C) )
#error "PTLS_NIST_KW_C defined, but not all prerequisites"
#endif

#if defined(PTLS_ECDH_C) && !defined(PTLS_ECP_C)
#error "PTLS_ECDH_C defined, but not all prerequisites"
#endif

#if defined(PTLS_ECDSA_C) &&            \
    ( !defined(PTLS_ECP_C) ||           \
      !defined(PTLS_ASN1_PARSE_C) ||    \
      !defined(PTLS_ASN1_WRITE_C) )
#error "PTLS_ECDSA_C defined, but not all prerequisites"
#endif

#if defined(PTLS_ECJPAKE_C) &&           \
    ( !defined(PTLS_ECP_C) || !defined(PTLS_MD_C) )
#error "PTLS_ECJPAKE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_ECDSA_DETERMINISTIC) && !defined(PTLS_HMAC_DRBG_C)
#error "PTLS_ECDSA_DETERMINISTIC defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_C) && ( !defined(PTLS_BIGNUM_C) || (   \
    !defined(PTLS_ECP_DP_SECP192R1_ENABLED) &&                  \
    !defined(PTLS_ECP_DP_SECP224R1_ENABLED) &&                  \
    !defined(PTLS_ECP_DP_SECP256R1_ENABLED) &&                  \
    !defined(PTLS_ECP_DP_SECP384R1_ENABLED) &&                  \
    !defined(PTLS_ECP_DP_SECP521R1_ENABLED) &&                  \
    !defined(PTLS_ECP_DP_BP256R1_ENABLED)   &&                  \
    !defined(PTLS_ECP_DP_BP384R1_ENABLED)   &&                  \
    !defined(PTLS_ECP_DP_BP512R1_ENABLED)   &&                  \
    !defined(PTLS_ECP_DP_SECP192K1_ENABLED) &&                  \
    !defined(PTLS_ECP_DP_SECP224K1_ENABLED) &&                  \
    !defined(PTLS_ECP_DP_SECP256K1_ENABLED) ) )
#error "PTLS_ECP_C defined, but not all prerequisites"
#endif

#if defined(PTLS_ENTROPY_C) && (!defined(PTLS_SHA512_C) &&      \
                                    !defined(PTLS_SHA256_C))
#error "PTLS_ENTROPY_C defined, but not all prerequisites"
#endif
#if defined(PTLS_ENTROPY_C) && defined(PTLS_SHA512_C) &&         \
    defined(PTLS_CTR_DRBG_ENTROPY_LEN) && (PTLS_CTR_DRBG_ENTROPY_LEN > 64)
#error "PTLS_CTR_DRBG_ENTROPY_LEN value too high"
#endif
#if defined(PTLS_ENTROPY_C) &&                                            \
    ( !defined(PTLS_SHA512_C) || defined(PTLS_ENTROPY_FORCE_SHA256) ) \
    && defined(PTLS_CTR_DRBG_ENTROPY_LEN) && (PTLS_CTR_DRBG_ENTROPY_LEN > 32)
#error "PTLS_CTR_DRBG_ENTROPY_LEN value too high"
#endif
#if defined(PTLS_ENTROPY_C) && \
    defined(PTLS_ENTROPY_FORCE_SHA256) && !defined(PTLS_SHA256_C)
#error "PTLS_ENTROPY_FORCE_SHA256 defined, but not all prerequisites"
#endif

#if defined(PTLS_TEST_NULL_ENTROPY) && \
    ( !defined(PTLS_ENTROPY_C) || !defined(PTLS_NO_DEFAULT_ENTROPY_SOURCES) )
#error "PTLS_TEST_NULL_ENTROPY defined, but not all prerequisites"
#endif
#if defined(PTLS_TEST_NULL_ENTROPY) && \
     ( defined(PTLS_ENTROPY_NV_SEED) || defined(PTLS_ENTROPY_HARDWARE_ALT) || \
    defined(PTLS_HAVEGE_C) )
#error "PTLS_TEST_NULL_ENTROPY defined, but entropy sources too"
#endif

#if defined(PTLS_GCM_C) && (                                        \
        !defined(PTLS_AES_C) && !defined(PTLS_CAMELLIA_C) )
#error "PTLS_GCM_C defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_RANDOMIZE_JAC_ALT) && !defined(PTLS_ECP_INTERNAL_ALT)
#error "PTLS_ECP_RANDOMIZE_JAC_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_ADD_MIXED_ALT) && !defined(PTLS_ECP_INTERNAL_ALT)
#error "PTLS_ECP_ADD_MIXED_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_DOUBLE_JAC_ALT) && !defined(PTLS_ECP_INTERNAL_ALT)
#error "PTLS_ECP_DOUBLE_JAC_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_NORMALIZE_JAC_MANY_ALT) && !defined(PTLS_ECP_INTERNAL_ALT)
#error "PTLS_ECP_NORMALIZE_JAC_MANY_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_NORMALIZE_JAC_ALT) && !defined(PTLS_ECP_INTERNAL_ALT)
#error "PTLS_ECP_NORMALIZE_JAC_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_DOUBLE_ADD_MXZ_ALT) && !defined(PTLS_ECP_INTERNAL_ALT)
#error "PTLS_ECP_DOUBLE_ADD_MXZ_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_RANDOMIZE_MXZ_ALT) && !defined(PTLS_ECP_INTERNAL_ALT)
#error "PTLS_ECP_RANDOMIZE_MXZ_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_ECP_NORMALIZE_MXZ_ALT) && !defined(PTLS_ECP_INTERNAL_ALT)
#error "PTLS_ECP_NORMALIZE_MXZ_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_HAVEGE_C) && !defined(PTLS_TIMING_C)
#error "PTLS_HAVEGE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_HKDF_C) && !defined(PTLS_MD_C)
#error "PTLS_HKDF_C defined, but not all prerequisites"
#endif

#if defined(PTLS_HMAC_DRBG_C) && !defined(PTLS_MD_C)
#error "PTLS_HMAC_DRBG_C defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED) &&                 \
    ( !defined(PTLS_ECDH_C) || !defined(PTLS_X509_CRT_PARSE_C) )
#error "PTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED) &&                 \
    ( !defined(PTLS_ECDH_C) || !defined(PTLS_X509_CRT_PARSE_C) )
#error "PTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_DHE_PSK_ENABLED) && !defined(PTLS_DHM_C)
#error "PTLS_KEY_EXCHANGE_DHE_PSK_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED) &&                     \
    !defined(PTLS_ECDH_C)
#error "PTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) &&                   \
    ( !defined(PTLS_DHM_C) || !defined(PTLS_RSA_C) ||           \
      !defined(PTLS_X509_CRT_PARSE_C) || !defined(PTLS_PKCS1_V15) )
#error "PTLS_KEY_EXCHANGE_DHE_RSA_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) &&                 \
    ( !defined(PTLS_ECDH_C) || !defined(PTLS_RSA_C) ||          \
      !defined(PTLS_X509_CRT_PARSE_C) || !defined(PTLS_PKCS1_V15) )
#error "PTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED) &&                 \
    ( !defined(PTLS_ECDH_C) || !defined(PTLS_ECDSA_C) ||          \
      !defined(PTLS_X509_CRT_PARSE_C) )
#error "PTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_RSA_PSK_ENABLED) &&                   \
    ( !defined(PTLS_RSA_C) || !defined(PTLS_X509_CRT_PARSE_C) || \
      !defined(PTLS_PKCS1_V15) )
#error "PTLS_KEY_EXCHANGE_RSA_PSK_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_RSA_ENABLED) &&                       \
    ( !defined(PTLS_RSA_C) || !defined(PTLS_X509_CRT_PARSE_C) || \
      !defined(PTLS_PKCS1_V15) )
#error "PTLS_KEY_EXCHANGE_RSA_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_KEY_EXCHANGE_ECJPAKE_ENABLED) &&                    \
    ( !defined(PTLS_ECJPAKE_C) || !defined(PTLS_SHA256_C) ||      \
      !defined(PTLS_ECP_DP_SECP256R1_ENABLED) )
#error "PTLS_KEY_EXCHANGE_ECJPAKE_ENABLED defined, but not all prerequisites"
#endif

#if defined(PTLS_MEMORY_BUFFER_ALLOC_C) &&                          \
    ( !defined(PTLS_PLATFORM_C) || !defined(PTLS_PLATFORM_MEMORY) )
#error "PTLS_MEMORY_BUFFER_ALLOC_C defined, but not all prerequisites"
#endif

#if defined(PTLS_PADLOCK_C) && !defined(PTLS_HAVE_ASM)
#error "PTLS_PADLOCK_C defined, but not all prerequisites"
#endif

#if defined(PTLS_PEM_PARSE_C) && !defined(PTLS_BASE64_C)
#error "PTLS_PEM_PARSE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_PEM_WRITE_C) && !defined(PTLS_BASE64_C)
#error "PTLS_PEM_WRITE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_PK_C) && \
    ( !defined(PTLS_RSA_C) && !defined(PTLS_ECP_C) )
#error "PTLS_PK_C defined, but not all prerequisites"
#endif

#if defined(PTLS_PK_PARSE_C) && !defined(PTLS_PK_C)
#error "PTLS_PK_PARSE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_PK_WRITE_C) && !defined(PTLS_PK_C)
#error "PTLS_PK_WRITE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_PKCS11_C) && !defined(PTLS_PK_C)
#error "PTLS_PKCS11_C defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_EXIT_ALT) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_EXIT_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_EXIT_MACRO) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_EXIT_MACRO defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_EXIT_MACRO) &&\
    ( defined(PTLS_PLATFORM_STD_EXIT) ||\
        defined(PTLS_PLATFORM_EXIT_ALT) )
#error "PTLS_PLATFORM_EXIT_MACRO and PTLS_PLATFORM_STD_EXIT/PTLS_PLATFORM_EXIT_ALT cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_TIME_ALT) &&\
    ( !defined(PTLS_PLATFORM_C) ||\
        !defined(PTLS_HAVE_TIME) )
#error "PTLS_PLATFORM_TIME_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_TIME_MACRO) &&\
    ( !defined(PTLS_PLATFORM_C) ||\
        !defined(PTLS_HAVE_TIME) )
#error "PTLS_PLATFORM_TIME_MACRO defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_TIME_TYPE_MACRO) &&\
    ( !defined(PTLS_PLATFORM_C) ||\
        !defined(PTLS_HAVE_TIME) )
#error "PTLS_PLATFORM_TIME_TYPE_MACRO defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_TIME_MACRO) &&\
    ( defined(PTLS_PLATFORM_STD_TIME) ||\
        defined(PTLS_PLATFORM_TIME_ALT) )
#error "PTLS_PLATFORM_TIME_MACRO and PTLS_PLATFORM_STD_TIME/PTLS_PLATFORM_TIME_ALT cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_TIME_TYPE_MACRO) &&\
    ( defined(PTLS_PLATFORM_STD_TIME) ||\
        defined(PTLS_PLATFORM_TIME_ALT) )
#error "PTLS_PLATFORM_TIME_TYPE_MACRO and PTLS_PLATFORM_STD_TIME/PTLS_PLATFORM_TIME_ALT cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_FPRINTF_ALT) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_FPRINTF_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_FPRINTF_MACRO) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_FPRINTF_MACRO defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_FPRINTF_MACRO) &&\
    ( defined(PTLS_PLATFORM_STD_FPRINTF) ||\
        defined(PTLS_PLATFORM_FPRINTF_ALT) )
#error "PTLS_PLATFORM_FPRINTF_MACRO and PTLS_PLATFORM_STD_FPRINTF/PTLS_PLATFORM_FPRINTF_ALT cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_FREE_MACRO) &&\
    ( !defined(PTLS_PLATFORM_C) || !defined(PTLS_PLATFORM_MEMORY) )
#error "PTLS_PLATFORM_FREE_MACRO defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_FREE_MACRO) &&\
    defined(PTLS_PLATFORM_STD_FREE)
#error "PTLS_PLATFORM_FREE_MACRO and PTLS_PLATFORM_STD_FREE cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_FREE_MACRO) && !defined(PTLS_PLATFORM_CALLOC_MACRO)
#error "PTLS_PLATFORM_CALLOC_MACRO must be defined if PTLS_PLATFORM_FREE_MACRO is"
#endif

#if defined(PTLS_PLATFORM_CALLOC_MACRO) &&\
    ( !defined(PTLS_PLATFORM_C) || !defined(PTLS_PLATFORM_MEMORY) )
#error "PTLS_PLATFORM_CALLOC_MACRO defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_CALLOC_MACRO) &&\
    defined(PTLS_PLATFORM_STD_CALLOC)
#error "PTLS_PLATFORM_CALLOC_MACRO and PTLS_PLATFORM_STD_CALLOC cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_CALLOC_MACRO) && !defined(PTLS_PLATFORM_FREE_MACRO)
#error "PTLS_PLATFORM_FREE_MACRO must be defined if PTLS_PLATFORM_CALLOC_MACRO is"
#endif

#if defined(PTLS_PLATFORM_MEMORY) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_MEMORY defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_PRINTF_ALT) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_PRINTF_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_PRINTF_MACRO) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_PRINTF_MACRO defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_PRINTF_MACRO) &&\
    ( defined(PTLS_PLATFORM_STD_PRINTF) ||\
        defined(PTLS_PLATFORM_PRINTF_ALT) )
#error "PTLS_PLATFORM_PRINTF_MACRO and PTLS_PLATFORM_STD_PRINTF/PTLS_PLATFORM_PRINTF_ALT cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_SNPRINTF_ALT) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_SNPRINTF_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_SNPRINTF_MACRO) && !defined(PTLS_PLATFORM_C)
#error "PTLS_PLATFORM_SNPRINTF_MACRO defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_SNPRINTF_MACRO) &&\
    ( defined(PTLS_PLATFORM_STD_SNPRINTF) ||\
        defined(PTLS_PLATFORM_SNPRINTF_ALT) )
#error "PTLS_PLATFORM_SNPRINTF_MACRO and PTLS_PLATFORM_STD_SNPRINTF/PTLS_PLATFORM_SNPRINTF_ALT cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_STD_MEM_HDR) &&\
    !defined(PTLS_PLATFORM_NO_STD_FUNCTIONS)
#error "PTLS_PLATFORM_STD_MEM_HDR defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_CALLOC) && !defined(PTLS_PLATFORM_MEMORY)
#error "PTLS_PLATFORM_STD_CALLOC defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_CALLOC) && !defined(PTLS_PLATFORM_MEMORY)
#error "PTLS_PLATFORM_STD_CALLOC defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_FREE) && !defined(PTLS_PLATFORM_MEMORY)
#error "PTLS_PLATFORM_STD_FREE defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_EXIT) &&\
    !defined(PTLS_PLATFORM_EXIT_ALT)
#error "PTLS_PLATFORM_STD_EXIT defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_TIME) &&\
    ( !defined(PTLS_PLATFORM_TIME_ALT) ||\
        !defined(PTLS_HAVE_TIME) )
#error "PTLS_PLATFORM_STD_TIME defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_FPRINTF) &&\
    !defined(PTLS_PLATFORM_FPRINTF_ALT)
#error "PTLS_PLATFORM_STD_FPRINTF defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_PRINTF) &&\
    !defined(PTLS_PLATFORM_PRINTF_ALT)
#error "PTLS_PLATFORM_STD_PRINTF defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_SNPRINTF) &&\
    !defined(PTLS_PLATFORM_SNPRINTF_ALT)
#error "PTLS_PLATFORM_STD_SNPRINTF defined, but not all prerequisites"
#endif

#if defined(PTLS_ENTROPY_NV_SEED) &&\
    ( !defined(PTLS_PLATFORM_C) || !defined(PTLS_ENTROPY_C) )
#error "PTLS_ENTROPY_NV_SEED defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_NV_SEED_ALT) &&\
    !defined(PTLS_ENTROPY_NV_SEED)
#error "PTLS_PLATFORM_NV_SEED_ALT defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_NV_SEED_READ) &&\
    !defined(PTLS_PLATFORM_NV_SEED_ALT)
#error "PTLS_PLATFORM_STD_NV_SEED_READ defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_STD_NV_SEED_WRITE) &&\
    !defined(PTLS_PLATFORM_NV_SEED_ALT)
#error "PTLS_PLATFORM_STD_NV_SEED_WRITE defined, but not all prerequisites"
#endif

#if defined(PTLS_PLATFORM_NV_SEED_READ_MACRO) &&\
    ( defined(PTLS_PLATFORM_STD_NV_SEED_READ) ||\
      defined(PTLS_PLATFORM_NV_SEED_ALT) )
#error "PTLS_PLATFORM_NV_SEED_READ_MACRO and PTLS_PLATFORM_STD_NV_SEED_READ cannot be defined simultaneously"
#endif

#if defined(PTLS_PLATFORM_NV_SEED_WRITE_MACRO) &&\
    ( defined(PTLS_PLATFORM_STD_NV_SEED_WRITE) ||\
      defined(PTLS_PLATFORM_NV_SEED_ALT) )
#error "PTLS_PLATFORM_NV_SEED_WRITE_MACRO and PTLS_PLATFORM_STD_NV_SEED_WRITE cannot be defined simultaneously"
#endif

#if defined(PTLS_RSA_C) && ( !defined(PTLS_BIGNUM_C) ||         \
    !defined(PTLS_OID_C) )
#error "PTLS_RSA_C defined, but not all prerequisites"
#endif

#if defined(PTLS_RSA_C) && ( !defined(PTLS_PKCS1_V21) &&         \
    !defined(PTLS_PKCS1_V15) )
#error "PTLS_RSA_C defined, but none of the PKCS1 versions enabled"
#endif

#if defined(PTLS_X509_RSASSA_PSS_SUPPORT) &&                        \
    ( !defined(PTLS_RSA_C) || !defined(PTLS_PKCS1_V21) )
#error "PTLS_X509_RSASSA_PSS_SUPPORT defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_PROTO_SSL3) && ( !defined(PTLS_MD5_C) ||     \
    !defined(PTLS_SHA1_C) )
#error "PTLS_SSL_PROTO_SSL3 defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_PROTO_TLS1) && ( !defined(PTLS_MD5_C) ||     \
    !defined(PTLS_SHA1_C) )
#error "PTLS_SSL_PROTO_TLS1 defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_PROTO_TLS1_1) && ( !defined(PTLS_MD5_C) ||     \
    !defined(PTLS_SHA1_C) )
#error "PTLS_SSL_PROTO_TLS1_1 defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_PROTO_TLS1_2) && ( !defined(PTLS_SHA1_C) &&     \
    !defined(PTLS_SHA256_C) && !defined(PTLS_SHA512_C) )
#error "PTLS_SSL_PROTO_TLS1_2 defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_PROTO_DTLS)     && \
    !defined(PTLS_SSL_PROTO_TLS1_1)  && \
    !defined(PTLS_SSL_PROTO_TLS1_2)
#error "PTLS_SSL_PROTO_DTLS defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_CLI_C) && !defined(PTLS_SSL_TLS_C)
#error "PTLS_SSL_CLI_C defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_TLS_C) && ( !defined(PTLS_CIPHER_C) ||     \
    !defined(PTLS_MD_C) )
#error "PTLS_SSL_TLS_C defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_SRV_C) && !defined(PTLS_SSL_TLS_C)
#error "PTLS_SSL_SRV_C defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_TLS_C) && (!defined(PTLS_SSL_PROTO_SSL3) && \
    !defined(PTLS_SSL_PROTO_TLS1) && !defined(PTLS_SSL_PROTO_TLS1_1) && \
    !defined(PTLS_SSL_PROTO_TLS1_2))
#error "PTLS_SSL_TLS_C defined, but no protocols are active"
#endif

#if defined(PTLS_SSL_TLS_C) && (defined(PTLS_SSL_PROTO_SSL3) && \
    defined(PTLS_SSL_PROTO_TLS1_1) && !defined(PTLS_SSL_PROTO_TLS1))
#error "Illegal protocol selection"
#endif

#if defined(PTLS_SSL_TLS_C) && (defined(PTLS_SSL_PROTO_TLS1) && \
    defined(PTLS_SSL_PROTO_TLS1_2) && !defined(PTLS_SSL_PROTO_TLS1_1))
#error "Illegal protocol selection"
#endif

#if defined(PTLS_SSL_TLS_C) && (defined(PTLS_SSL_PROTO_SSL3) && \
    defined(PTLS_SSL_PROTO_TLS1_2) && (!defined(PTLS_SSL_PROTO_TLS1) || \
    !defined(PTLS_SSL_PROTO_TLS1_1)))
#error "Illegal protocol selection"
#endif

#if defined(PTLS_SSL_DTLS_HELLO_VERIFY) && !defined(PTLS_SSL_PROTO_DTLS)
#error "PTLS_SSL_DTLS_HELLO_VERIFY  defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_DTLS_CLIENT_PORT_REUSE) && \
    !defined(PTLS_SSL_DTLS_HELLO_VERIFY)
#error "PTLS_SSL_DTLS_CLIENT_PORT_REUSE  defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_DTLS_ANTI_REPLAY) &&                              \
    ( !defined(PTLS_SSL_TLS_C) || !defined(PTLS_SSL_PROTO_DTLS) )
#error "PTLS_SSL_DTLS_ANTI_REPLAY  defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_DTLS_BADMAC_LIMIT) &&                              \
    ( !defined(PTLS_SSL_TLS_C) || !defined(PTLS_SSL_PROTO_DTLS) )
#error "PTLS_SSL_DTLS_BADMAC_LIMIT  defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_ENCRYPT_THEN_MAC) &&   \
    !defined(PTLS_SSL_PROTO_TLS1)   &&      \
    !defined(PTLS_SSL_PROTO_TLS1_1) &&      \
    !defined(PTLS_SSL_PROTO_TLS1_2)
#error "PTLS_SSL_ENCRYPT_THEN_MAC defined, but not all prerequsites"
#endif

#if defined(PTLS_SSL_EXTENDED_MASTER_SECRET) && \
    !defined(PTLS_SSL_PROTO_TLS1)   &&          \
    !defined(PTLS_SSL_PROTO_TLS1_1) &&          \
    !defined(PTLS_SSL_PROTO_TLS1_2)
#error "PTLS_SSL_EXTENDED_MASTER_SECRET defined, but not all prerequsites"
#endif

#if defined(PTLS_SSL_TICKET_C) && !defined(PTLS_CIPHER_C)
#error "PTLS_SSL_TICKET_C defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_CBC_RECORD_SPLITTING) && \
    !defined(PTLS_SSL_PROTO_SSL3) && !defined(PTLS_SSL_PROTO_TLS1)
#error "PTLS_SSL_CBC_RECORD_SPLITTING defined, but not all prerequisites"
#endif

#if defined(PTLS_SSL_SERVER_NAME_INDICATION) && \
        !defined(PTLS_X509_CRT_PARSE_C)
#error "PTLS_SSL_SERVER_NAME_INDICATION defined, but not all prerequisites"
#endif

#if defined(PTLS_THREADING_PTHREAD)
#if !defined(PTLS_THREADING_C) || defined(PTLS_THREADING_IMPL)
#error "PTLS_THREADING_PTHREAD defined, but not all prerequisites"
#endif
#define PTLS_THREADING_IMPL
#endif

#if defined(PTLS_THREADING_ALT)
#if !defined(PTLS_THREADING_C) || defined(PTLS_THREADING_IMPL)
#error "PTLS_THREADING_ALT defined, but not all prerequisites"
#endif
#define PTLS_THREADING_IMPL
#endif

#if defined(PTLS_THREADING_C) && !defined(PTLS_THREADING_IMPL)
#error "PTLS_THREADING_C defined, single threading implementation required"
#endif
#undef PTLS_THREADING_IMPL

#if defined(PTLS_VERSION_FEATURES) && !defined(PTLS_VERSION_C)
#error "PTLS_VERSION_FEATURES defined, but not all prerequisites"
#endif

#if defined(PTLS_X509_USE_C) && ( !defined(PTLS_BIGNUM_C) ||  \
    !defined(PTLS_OID_C) || !defined(PTLS_ASN1_PARSE_C) ||      \
    !defined(PTLS_PK_PARSE_C) )
#error "PTLS_X509_USE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_X509_CREATE_C) && ( !defined(PTLS_BIGNUM_C) ||  \
    !defined(PTLS_OID_C) || !defined(PTLS_ASN1_WRITE_C) ||       \
    !defined(PTLS_PK_WRITE_C) )
#error "PTLS_X509_CREATE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_X509_CRT_PARSE_C) && ( !defined(PTLS_X509_USE_C) )
#error "PTLS_X509_CRT_PARSE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_X509_CRL_PARSE_C) && ( !defined(PTLS_X509_USE_C) )
#error "PTLS_X509_CRL_PARSE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_X509_CSR_PARSE_C) && ( !defined(PTLS_X509_USE_C) )
#error "PTLS_X509_CSR_PARSE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_X509_CRT_WRITE_C) && ( !defined(PTLS_X509_CREATE_C) )
#error "PTLS_X509_CRT_WRITE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_X509_CSR_WRITE_C) && ( !defined(PTLS_X509_CREATE_C) )
#error "PTLS_X509_CSR_WRITE_C defined, but not all prerequisites"
#endif

#if defined(PTLS_HAVE_INT32) && defined(PTLS_HAVE_INT64)
#error "PTLS_HAVE_INT32 and PTLS_HAVE_INT64 cannot be defined simultaneously"
#endif /* PTLS_HAVE_INT32 && PTLS_HAVE_INT64 */

#if ( defined(PTLS_HAVE_INT32) || defined(PTLS_HAVE_INT64) ) && \
    defined(PTLS_HAVE_ASM)
#error "PTLS_HAVE_INT32/PTLS_HAVE_INT64 and PTLS_HAVE_ASM cannot be defined simultaneously"
#endif /* (PTLS_HAVE_INT32 || PTLS_HAVE_INT64) && PTLS_HAVE_ASM */

/*
 * Avoid warning from -pedantic. This is a convenient place for this
 * workaround since this is included by every single file before the
 * #if defined(PTLS_xxx_C) that results in emtpy translation units.
 */
typedef int ptls_iso_c_forbids_empty_translation_units;

#endif /* PTLS_CHECK_CONFIG_H */
