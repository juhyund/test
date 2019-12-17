/**
 * \file cipher.h
 *
 * \brief This file contains an abstraction interface for use with the cipher
 * primitives provided by the library. It provides a common interface to all of
 * the available cipher operations.
 *
 * \author Adriaan de Jong <dejong@fox-it.com>
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

#ifndef PTLS_CIPHER_H
#define PTLS_CIPHER_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include <stddef.h>

#if defined(PTLS_GCM_C) || defined(PTLS_CCM_C) || defined(PTLS_CHACHAPOLY_C)
#define PTLS_CIPHER_MODE_AEAD
#endif

#if defined(PTLS_CIPHER_MODE_CBC)
#define PTLS_CIPHER_MODE_WITH_PADDING
#endif

#if defined(PTLS_ARC4_C) || defined(PTLS_CIPHER_NULL_CIPHER) || \
    defined(PTLS_CHACHA20_C)
#define PTLS_CIPHER_MODE_STREAM
#endif

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

#define PTLS_ERR_CIPHER_FEATURE_UNAVAILABLE  -0x6080  /**< The selected feature is not available. */
#define PTLS_ERR_CIPHER_BAD_INPUT_DATA       -0x6100  /**< Bad input parameters. */
#define PTLS_ERR_CIPHER_ALLOC_FAILED         -0x6180  /**< Failed to allocate memory. */
#define PTLS_ERR_CIPHER_INVALID_PADDING      -0x6200  /**< Input data contains invalid padding and is rejected. */
#define PTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED  -0x6280  /**< Decryption of block requires a full block. */
#define PTLS_ERR_CIPHER_AUTH_FAILED          -0x6300  /**< Authentication failed (for AEAD modes). */
#define PTLS_ERR_CIPHER_INVALID_CONTEXT      -0x6380  /**< The context is invalid. For example, because it was freed. */
#define PTLS_ERR_CIPHER_HW_ACCEL_FAILED      -0x6400  /**< Cipher hardware accelerator failed. */

#define PTLS_CIPHER_VARIABLE_IV_LEN     0x01    /**< Cipher accepts IVs of variable length. */
#define PTLS_CIPHER_VARIABLE_KEY_LEN    0x02    /**< Cipher accepts keys of variable length. */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief     Supported cipher types.
 *
 * \warning   RC4 and DES are considered weak ciphers and their use
 *            constitutes a security risk. Arm recommends considering stronger
 *            ciphers instead.
 */
typedef enum {
    PTLS_CIPHER_ID_NONE = 0,  /**< Placeholder to mark the end of cipher ID lists. */
    PTLS_CIPHER_ID_NULL,      /**< The identity cipher, treated as a stream cipher. */
    PTLS_CIPHER_ID_AES,       /**< The AES cipher. */
    PTLS_CIPHER_ID_DES,       /**< The DES cipher. */
    PTLS_CIPHER_ID_3DES,      /**< The Triple DES cipher. */
    PTLS_CIPHER_ID_CAMELLIA,  /**< The Camellia cipher. */
    PTLS_CIPHER_ID_BLOWFISH,  /**< The Blowfish cipher. */
    PTLS_CIPHER_ID_ARC4,      /**< The RC4 cipher. */
    PTLS_CIPHER_ID_ARIA,      /**< The Aria cipher. */
    PTLS_CIPHER_ID_CHACHA20,  /**< The ChaCha20 cipher. */
} ptls_cipher_id_t;

/**
 * \brief     Supported {cipher type, cipher mode} pairs.
 *
 * \warning   RC4 and DES are considered weak ciphers and their use
 *            constitutes a security risk. Arm recommends considering stronger
 *            ciphers instead.
 */
typedef enum {
    PTLS_CIPHER_NONE = 0,             /**< Placeholder to mark the end of cipher-pair lists. */
    PTLS_CIPHER_NULL,                 /**< The identity stream cipher. */
    PTLS_CIPHER_AES_128_ECB,          /**< AES cipher with 128-bit ECB mode. */
    PTLS_CIPHER_AES_192_ECB,          /**< AES cipher with 192-bit ECB mode. */
    PTLS_CIPHER_AES_256_ECB,          /**< AES cipher with 256-bit ECB mode. */
    PTLS_CIPHER_AES_128_CBC,          /**< AES cipher with 128-bit CBC mode. */
    PTLS_CIPHER_AES_192_CBC,          /**< AES cipher with 192-bit CBC mode. */
    PTLS_CIPHER_AES_256_CBC,          /**< AES cipher with 256-bit CBC mode. */
    PTLS_CIPHER_AES_128_CFB128,       /**< AES cipher with 128-bit CFB128 mode. */
    PTLS_CIPHER_AES_192_CFB128,       /**< AES cipher with 192-bit CFB128 mode. */
    PTLS_CIPHER_AES_256_CFB128,       /**< AES cipher with 256-bit CFB128 mode. */
    PTLS_CIPHER_AES_128_CTR,          /**< AES cipher with 128-bit CTR mode. */
    PTLS_CIPHER_AES_192_CTR,          /**< AES cipher with 192-bit CTR mode. */
    PTLS_CIPHER_AES_256_CTR,          /**< AES cipher with 256-bit CTR mode. */
    PTLS_CIPHER_AES_128_GCM,          /**< AES cipher with 128-bit GCM mode. */
    PTLS_CIPHER_AES_192_GCM,          /**< AES cipher with 192-bit GCM mode. */
    PTLS_CIPHER_AES_256_GCM,          /**< AES cipher with 256-bit GCM mode. */
    PTLS_CIPHER_CAMELLIA_128_ECB,     /**< Camellia cipher with 128-bit ECB mode. */
    PTLS_CIPHER_CAMELLIA_192_ECB,     /**< Camellia cipher with 192-bit ECB mode. */
    PTLS_CIPHER_CAMELLIA_256_ECB,     /**< Camellia cipher with 256-bit ECB mode. */
    PTLS_CIPHER_CAMELLIA_128_CBC,     /**< Camellia cipher with 128-bit CBC mode. */
    PTLS_CIPHER_CAMELLIA_192_CBC,     /**< Camellia cipher with 192-bit CBC mode. */
    PTLS_CIPHER_CAMELLIA_256_CBC,     /**< Camellia cipher with 256-bit CBC mode. */
    PTLS_CIPHER_CAMELLIA_128_CFB128,  /**< Camellia cipher with 128-bit CFB128 mode. */
    PTLS_CIPHER_CAMELLIA_192_CFB128,  /**< Camellia cipher with 192-bit CFB128 mode. */
    PTLS_CIPHER_CAMELLIA_256_CFB128,  /**< Camellia cipher with 256-bit CFB128 mode. */
    PTLS_CIPHER_CAMELLIA_128_CTR,     /**< Camellia cipher with 128-bit CTR mode. */
    PTLS_CIPHER_CAMELLIA_192_CTR,     /**< Camellia cipher with 192-bit CTR mode. */
    PTLS_CIPHER_CAMELLIA_256_CTR,     /**< Camellia cipher with 256-bit CTR mode. */
    PTLS_CIPHER_CAMELLIA_128_GCM,     /**< Camellia cipher with 128-bit GCM mode. */
    PTLS_CIPHER_CAMELLIA_192_GCM,     /**< Camellia cipher with 192-bit GCM mode. */
    PTLS_CIPHER_CAMELLIA_256_GCM,     /**< Camellia cipher with 256-bit GCM mode. */
    PTLS_CIPHER_DES_ECB,              /**< DES cipher with ECB mode. */
    PTLS_CIPHER_DES_CBC,              /**< DES cipher with CBC mode. */
    PTLS_CIPHER_DES_EDE_ECB,          /**< DES cipher with EDE ECB mode. */
    PTLS_CIPHER_DES_EDE_CBC,          /**< DES cipher with EDE CBC mode. */
    PTLS_CIPHER_DES_EDE3_ECB,         /**< DES cipher with EDE3 ECB mode. */
    PTLS_CIPHER_DES_EDE3_CBC,         /**< DES cipher with EDE3 CBC mode. */
    PTLS_CIPHER_BLOWFISH_ECB,         /**< Blowfish cipher with ECB mode. */
    PTLS_CIPHER_BLOWFISH_CBC,         /**< Blowfish cipher with CBC mode. */
    PTLS_CIPHER_BLOWFISH_CFB64,       /**< Blowfish cipher with CFB64 mode. */
    PTLS_CIPHER_BLOWFISH_CTR,         /**< Blowfish cipher with CTR mode. */
    PTLS_CIPHER_ARC4_128,             /**< RC4 cipher with 128-bit mode. */
    PTLS_CIPHER_AES_128_CCM,          /**< AES cipher with 128-bit CCM mode. */
    PTLS_CIPHER_AES_192_CCM,          /**< AES cipher with 192-bit CCM mode. */
    PTLS_CIPHER_AES_256_CCM,          /**< AES cipher with 256-bit CCM mode. */
    PTLS_CIPHER_CAMELLIA_128_CCM,     /**< Camellia cipher with 128-bit CCM mode. */
    PTLS_CIPHER_CAMELLIA_192_CCM,     /**< Camellia cipher with 192-bit CCM mode. */
    PTLS_CIPHER_CAMELLIA_256_CCM,     /**< Camellia cipher with 256-bit CCM mode. */
    PTLS_CIPHER_ARIA_128_ECB,         /**< Aria cipher with 128-bit key and ECB mode. */
    PTLS_CIPHER_ARIA_192_ECB,         /**< Aria cipher with 192-bit key and ECB mode. */
    PTLS_CIPHER_ARIA_256_ECB,         /**< Aria cipher with 256-bit key and ECB mode. */
    PTLS_CIPHER_ARIA_128_CBC,         /**< Aria cipher with 128-bit key and CBC mode. */
    PTLS_CIPHER_ARIA_192_CBC,         /**< Aria cipher with 192-bit key and CBC mode. */
    PTLS_CIPHER_ARIA_256_CBC,         /**< Aria cipher with 256-bit key and CBC mode. */
    PTLS_CIPHER_ARIA_128_CFB128,      /**< Aria cipher with 128-bit key and CFB-128 mode. */
    PTLS_CIPHER_ARIA_192_CFB128,      /**< Aria cipher with 192-bit key and CFB-128 mode. */
    PTLS_CIPHER_ARIA_256_CFB128,      /**< Aria cipher with 256-bit key and CFB-128 mode. */
    PTLS_CIPHER_ARIA_128_CTR,         /**< Aria cipher with 128-bit key and CTR mode. */
    PTLS_CIPHER_ARIA_192_CTR,         /**< Aria cipher with 192-bit key and CTR mode. */
    PTLS_CIPHER_ARIA_256_CTR,         /**< Aria cipher with 256-bit key and CTR mode. */
    PTLS_CIPHER_ARIA_128_GCM,         /**< Aria cipher with 128-bit key and GCM mode. */
    PTLS_CIPHER_ARIA_192_GCM,         /**< Aria cipher with 192-bit key and GCM mode. */
    PTLS_CIPHER_ARIA_256_GCM,         /**< Aria cipher with 256-bit key and GCM mode. */
    PTLS_CIPHER_ARIA_128_CCM,         /**< Aria cipher with 128-bit key and CCM mode. */
    PTLS_CIPHER_ARIA_192_CCM,         /**< Aria cipher with 192-bit key and CCM mode. */
    PTLS_CIPHER_ARIA_256_CCM,         /**< Aria cipher with 256-bit key and CCM mode. */
    PTLS_CIPHER_AES_128_OFB,          /**< AES 128-bit cipher in OFB mode. */
    PTLS_CIPHER_AES_192_OFB,          /**< AES 192-bit cipher in OFB mode. */
    PTLS_CIPHER_AES_256_OFB,          /**< AES 256-bit cipher in OFB mode. */
    PTLS_CIPHER_AES_128_XTS,          /**< AES 128-bit cipher in XTS block mode. */
    PTLS_CIPHER_AES_256_XTS,          /**< AES 256-bit cipher in XTS block mode. */
    PTLS_CIPHER_CHACHA20,             /**< ChaCha20 stream cipher. */
    PTLS_CIPHER_CHACHA20_POLY1305,    /**< ChaCha20-Poly1305 AEAD cipher. */
} ptls_cipher_type_t;

/** Supported cipher modes. */
typedef enum {
    PTLS_MODE_NONE = 0,               /**< None. */
    PTLS_MODE_ECB,                    /**< The ECB cipher mode. */
    PTLS_MODE_CBC,                    /**< The CBC cipher mode. */
    PTLS_MODE_CFB,                    /**< The CFB cipher mode. */
    PTLS_MODE_OFB,                    /**< The OFB cipher mode. */
    PTLS_MODE_CTR,                    /**< The CTR cipher mode. */
    PTLS_MODE_GCM,                    /**< The GCM cipher mode. */
    PTLS_MODE_STREAM,                 /**< The stream cipher mode. */
    PTLS_MODE_CCM,                    /**< The CCM cipher mode. */
    PTLS_MODE_XTS,                    /**< The XTS cipher mode. */
    PTLS_MODE_CHACHAPOLY,             /**< The ChaCha-Poly cipher mode. */
} ptls_cipher_mode_t;

/** Supported cipher padding types. */
typedef enum {
    PTLS_PADDING_PKCS7 = 0,     /**< PKCS7 padding (default).        */
    PTLS_PADDING_ONE_AND_ZEROS, /**< ISO/IEC 7816-4 padding.         */
    PTLS_PADDING_ZEROS_AND_LEN, /**< ANSI X.923 padding.             */
    PTLS_PADDING_ZEROS,         /**< Zero padding (not reversible). */
    PTLS_PADDING_NONE,          /**< Never pad (full blocks only).   */
} ptls_cipher_padding_t;

/** Type of operation. */
typedef enum {
    PTLS_OPERATION_NONE = -1,
    PTLS_DECRYPT = 0,
    PTLS_ENCRYPT,
} ptls_operation_t;

enum {
    /** Undefined key length. */
    PTLS_KEY_LENGTH_NONE = 0,
    /** Key length, in bits (including parity), for DES keys. */
    PTLS_KEY_LENGTH_DES  = 64,
    /** Key length in bits, including parity, for DES in two-key EDE. */
    PTLS_KEY_LENGTH_DES_EDE = 128,
    /** Key length in bits, including parity, for DES in three-key EDE. */
    PTLS_KEY_LENGTH_DES_EDE3 = 192,
};

/** Maximum length of any IV, in Bytes. */
#define PTLS_MAX_IV_LENGTH      16
/** Maximum block size of any cipher, in Bytes. */
#define PTLS_MAX_BLOCK_LENGTH   16

/**
 * Base cipher information (opaque struct).
 */
typedef struct ptls_cipher_base_t ptls_cipher_base_t;

/**
 * CMAC context (opaque struct).
 */
typedef struct ptls_cmac_context_t ptls_cmac_context_t;

/**
 * Cipher information. Allows calling cipher functions
 * in a generic way.
 */
typedef struct ptls_cipher_info_t
{
    /** Full cipher identifier. For example,
     * PTLS_CIPHER_AES_256_CBC.
     */
    ptls_cipher_type_t type;

    /** The cipher mode. For example, PTLS_MODE_CBC. */
    ptls_cipher_mode_t mode;

    /** The cipher key length, in bits. This is the
     * default length for variable sized ciphers.
     * Includes parity bits for ciphers like DES.
     */
    unsigned int key_bitlen;

    /** Name of the cipher. */
    const char * name;

    /** IV or nonce size, in Bytes.
     * For ciphers that accept variable IV sizes,
     * this is the recommended size.
     */
    unsigned int iv_size;

    /** Bitflag comprised of PTLS_CIPHER_VARIABLE_IV_LEN and
     *  PTLS_CIPHER_VARIABLE_KEY_LEN indicating whether the
     *  cipher supports variable IV or variable key sizes, respectively.
     */
    int flags;

    /** The block size, in Bytes. */
    unsigned int block_size;

    /** Struct for base cipher information and functions. */
    const ptls_cipher_base_t *base;

} ptls_cipher_info_t;

/**
 * Generic cipher context.
 */
typedef struct ptls_cipher_context_t
{
    /** Information about the associated cipher. */
    const ptls_cipher_info_t *cipher_info;

    /** Key length to use. */
    int key_bitlen;

    /** Operation that the key of the context has been
     * initialized for.
     */
    ptls_operation_t operation;

#if defined(PTLS_CIPHER_MODE_WITH_PADDING)
    /** Padding functions to use, if relevant for
     * the specific cipher mode.
     */
    void (*add_padding)( unsigned char *output, size_t olen, size_t data_len );
    int (*get_padding)( unsigned char *input, size_t ilen, size_t *data_len );
#endif

    /** Buffer for input that has not been processed yet. */
    unsigned char unprocessed_data[PTLS_MAX_BLOCK_LENGTH];

    /** Number of Bytes that have not been processed yet. */
    size_t unprocessed_len;

    /** Current IV or NONCE_COUNTER for CTR-mode, data unit (or sector) number
     * for XTS-mode. */
    unsigned char iv[PTLS_MAX_IV_LENGTH];

    /** IV size in Bytes, for ciphers with variable-length IVs. */
    size_t iv_size;

    /** The cipher-specific context. */
    void *cipher_ctx;

#if defined(PTLS_CMAC_C)
    /** CMAC-specific context. */
    ptls_cmac_context_t *cmac_ctx;
#endif
#if defined(USE_PENTA_CIS)
    void *cis_bcipher_info;
#endif
} ptls_cipher_context_t;

/**
 * \brief This function retrieves the list of ciphers supported by the generic
 * cipher module.
 *
 * \return      A statically-allocated array of ciphers. The last entry
 *              is zero.
 */
const int *ptls_cipher_list( void );

/**
 * \brief               This function retrieves the cipher-information
 *                      structure associated with the given cipher name.
 *
 * \param cipher_name   Name of the cipher to search for.
 *
 * \return              The cipher information structure associated with the
 *                      given \p cipher_name.
 * \return              NULL if the associated cipher information is not found.
 */
const ptls_cipher_info_t *ptls_cipher_info_from_string( const char *cipher_name );

/**
 * \brief               This function retrieves the cipher-information
 *                      structure associated with the given cipher type.
 *
 * \param cipher_type   Type of the cipher to search for.
 *
 * \return              The cipher information structure associated with the
 *                      given \p cipher_type.
 * \return              NULL if the associated cipher information is not found.
 */
const ptls_cipher_info_t *ptls_cipher_info_from_type( const ptls_cipher_type_t cipher_type );

/**
 * \brief               This function retrieves the cipher-information
 *                      structure associated with the given cipher ID,
 *                      key size and mode.
 *
 * \param cipher_id     The ID of the cipher to search for. For example,
 *                      #PTLS_CIPHER_ID_AES.
 * \param key_bitlen    The length of the key in bits.
 * \param mode          The cipher mode. For example, #PTLS_MODE_CBC.
 *
 * \return              The cipher information structure associated with the
 *                      given \p cipher_id.
 * \return              NULL if the associated cipher information is not found.
 */
const ptls_cipher_info_t *ptls_cipher_info_from_values( const ptls_cipher_id_t cipher_id,
                                              int key_bitlen,
                                              const ptls_cipher_mode_t mode );

/**
 * \brief               This function initializes a \p cipher_context as NONE.
 */
void ptls_cipher_init( ptls_cipher_context_t *ctx );

/**
 * \brief               This function frees and clears the cipher-specific
 *                      context of \p ctx. Freeing \p ctx itself remains the
 *                      responsibility of the caller.
 */
void ptls_cipher_free( ptls_cipher_context_t *ctx );


/**
 * \brief               This function initializes and fills the cipher-context
 *                      structure with the appropriate values. It also clears
 *                      the structure.
 *
 * \param ctx           The context to initialize. May not be NULL.
 * \param cipher_info   The cipher to use.
 *
 * \return              \c 0 on success.
 * \return              #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #PTLS_ERR_CIPHER_ALLOC_FAILED if allocation of the
 *                      cipher-specific context fails.
 *
 * \internal Currently, the function also clears the structure.
 * In future versions, the caller will be required to call
 * ptls_cipher_init() on the structure first.
 */
int ptls_cipher_setup( ptls_cipher_context_t *ctx, const ptls_cipher_info_t *cipher_info );

/**
 * \brief        This function returns the block size of the given cipher.
 *
 * \param ctx    The context of the cipher. Must be initialized.
 *
 * \return       The size of the blocks of the cipher.
 * \return       0 if \p ctx has not been initialized.
 */
static inline unsigned int ptls_cipher_get_block_size( const ptls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return 0;

    return ctx->cipher_info->block_size;
}

/**
 * \brief        This function returns the mode of operation for
 *               the cipher. For example, PTLS_MODE_CBC.
 *
 * \param ctx    The context of the cipher. Must be initialized.
 *
 * \return       The mode of operation.
 * \return       #PTLS_MODE_NONE if \p ctx has not been initialized.
 */
static inline ptls_cipher_mode_t ptls_cipher_get_cipher_mode( const ptls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return PTLS_MODE_NONE;

    return ctx->cipher_info->mode;
}

/**
 * \brief       This function returns the size of the IV or nonce
 *              of the cipher, in Bytes.
 *
 * \param ctx   The context of the cipher. Must be initialized.
 *
 * \return      The recommended IV size if no IV has been set.
 * \return      \c 0 for ciphers not using an IV or a nonce.
 * \return      The actual size if an IV has been set.
 */
static inline int ptls_cipher_get_iv_size( const ptls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return 0;

    if( ctx->iv_size != 0 )
        return (int) ctx->iv_size;

    return (int) ctx->cipher_info->iv_size;
}

/**
 * \brief               This function returns the type of the given cipher.
 *
 * \param ctx           The context of the cipher. Must be initialized.
 *
 * \return              The type of the cipher.
 * \return              #PTLS_CIPHER_NONE if \p ctx has not been initialized.
 */
static inline ptls_cipher_type_t ptls_cipher_get_type( const ptls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return PTLS_CIPHER_NONE;

    return ctx->cipher_info->type;
}

/**
 * \brief               This function returns the name of the given cipher
 *                      as a string.
 *
 * \param ctx           The context of the cipher. Must be initialized.
 *
 * \return              The name of the cipher.
 * \return              NULL if \p ctx has not been not initialized.
 */
static inline const char *ptls_cipher_get_name( const ptls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return 0;

    return ctx->cipher_info->name;
}

/**
 * \brief               This function returns the key length of the cipher.
 *
 * \param ctx           The context of the cipher. Must be initialized.
 *
 * \return              The key length of the cipher in bits.
 * \return              #PTLS_KEY_LENGTH_NONE if ctx \p has not been
 *                      initialized.
 */
static inline int ptls_cipher_get_key_bitlen( const ptls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return PTLS_KEY_LENGTH_NONE;

    return (int) ctx->cipher_info->key_bitlen;
}

/**
 * \brief          This function returns the operation of the given cipher.
 *
 * \param ctx      The context of the cipher. Must be initialized.
 *
 * \return         The type of operation: #PTLS_ENCRYPT or #PTLS_DECRYPT.
 * \return         #PTLS_OPERATION_NONE if \p ctx has not been initialized.
 */
static inline ptls_operation_t ptls_cipher_get_operation( const ptls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return PTLS_OPERATION_NONE;

    return ctx->operation;
}

/**
 * \brief               This function sets the key to use with the given context.
 *
 * \param ctx           The generic cipher context. May not be NULL. Must have
 *                      been initialized using ptls_cipher_info_from_type()
 *                      or ptls_cipher_info_from_string().
 * \param key           The key to use.
 * \param key_bitlen    The key length to use, in bits.
 * \param operation     The operation that the key will be used for:
 *                      #PTLS_ENCRYPT or #PTLS_DECRYPT.
 *
 * \return              \c 0 on success.
 * \return              #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              A cipher-specific error code on failure.
 */
int ptls_cipher_setkey( ptls_cipher_context_t *ctx, const unsigned char *key,
                   int key_bitlen, const ptls_operation_t operation );

#if defined(PTLS_CIPHER_MODE_WITH_PADDING)
/**
 * \brief               This function sets the padding mode, for cipher modes
 *                      that use padding.
 *
 *                      The default passing mode is PKCS7 padding.
 *
 * \param ctx           The generic cipher context.
 * \param mode          The padding mode.
 *
 * \return              \c 0 on success.
 * \return              #PTLS_ERR_CIPHER_FEATURE_UNAVAILABLE
 *                      if the selected padding mode is not supported.
 * \return              #PTLS_ERR_CIPHER_BAD_INPUT_DATA if the cipher mode
 *                      does not support padding.
 */
int ptls_cipher_set_padding_mode( ptls_cipher_context_t *ctx, ptls_cipher_padding_t mode );
#endif /* PTLS_CIPHER_MODE_WITH_PADDING */

/**
 * \brief           This function sets the initialization vector (IV)
 *                  or nonce.
 *
 * \note            Some ciphers do not use IVs nor nonce. For these
 *                  ciphers, this function has no effect.
 *
 * \param ctx       The generic cipher context.
 * \param iv        The IV to use, or NONCE_COUNTER for CTR-mode ciphers.
 * \param iv_len    The IV length for ciphers with variable-size IV.
 *                  This parameter is discarded by ciphers with fixed-size IV.
 *
 * \return          \c 0 on success.
 * \return          #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                  parameter-verification failure.
 */
int ptls_cipher_set_iv( ptls_cipher_context_t *ctx,
                   const unsigned char *iv, size_t iv_len );

/**
 * \brief         This function resets the cipher state.
 *
 * \param ctx     The generic cipher context.
 *
 * \return        \c 0 on success.
 * \return        #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                parameter-verification failure.
 */
int ptls_cipher_reset( ptls_cipher_context_t *ctx );

#if defined(PTLS_GCM_C) || defined(PTLS_CHACHAPOLY_C)
/**
 * \brief               This function adds additional data for AEAD ciphers.
 *                      Currently supported with GCM and ChaCha20+Poly1305.
 *                      Must be called exactly once, after ptls_cipher_reset().
 *
 * \param ctx           The generic cipher context.
 * \param ad            The additional data to use.
 * \param ad_len        the Length of \p ad.
 *
 * \return              \c 0 on success.
 * \return              A specific error code on failure.
 */
// ���Ǵ� �� ����
#if 0
int ptls_cipher_update_ad( ptls_cipher_context_t *ctx,
                      const unsigned char *ad, size_t ad_len );
#endif
#endif /* PTLS_GCM_C || PTLS_CHACHAPOLY_C */

/**
 * \brief               The generic cipher update function. It encrypts or
 *                      decrypts using the given cipher context. Writes as
 *                      many block-sized blocks of data as possible to output.
 *                      Any data that cannot be written immediately is either
 *                      added to the next block, or flushed when
 *                      ptls_cipher_finish() is called.
 *                      Exception: For PTLS_MODE_ECB, expects a single block
 *                      in size. For example, 16 Bytes for AES.
 *
 * \note                If the underlying cipher is used in GCM mode, all calls
 *                      to this function, except for the last one before
 *                      ptls_cipher_finish(), must have \p ilen as a
 *                      multiple of the block size of the cipher.
 *
 * \param ctx           The generic cipher context.
 * \param input         The buffer holding the input data.
 * \param ilen          The length of the input data.
 * \param output        The buffer for the output data. Must be able to hold at
 *                      least \p ilen + block_size. Must not be the same buffer
 *                      as input.
 * \param olen          The length of the output data, to be updated with the
 *                      actual number of Bytes written.
 *
 * \return              \c 0 on success.
 * \return              #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #PTLS_ERR_CIPHER_FEATURE_UNAVAILABLE on an
 *                      unsupported mode for a cipher.
 * \return              A cipher-specific error code on failure.
 */
int ptls_cipher_update( ptls_cipher_context_t *ctx, const unsigned char *input,
                   size_t ilen, unsigned char *output, size_t *olen );

/**
 * \brief               The generic cipher finalization function. If data still
 *                      needs to be flushed from an incomplete block, the data
 *                      contained in it is padded to the size of
 *                      the last block, and written to the \p output buffer.
 *
 * \param ctx           The generic cipher context.
 * \param output        The buffer to write data to. Needs block_size available.
 * \param olen          The length of the data written to the \p output buffer.
 *
 * \return              \c 0 on success.
 * \return              #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #PTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED on decryption
 *                      expecting a full block but not receiving one.
 * \return              #PTLS_ERR_CIPHER_INVALID_PADDING on invalid padding
 *                      while decrypting.
 * \return              A cipher-specific error code on failure.
 */
int ptls_cipher_finish( ptls_cipher_context_t *ctx,
                   unsigned char *output, size_t *olen );

#if defined(PTLS_GCM_C) || defined(PTLS_CHACHAPOLY_C)
/**
 * \brief               This function writes a tag for AEAD ciphers.
 *                      Currently supported with GCM and ChaCha20+Poly1305.
 *                      Must be called after ptls_cipher_finish().
 *
 * \param ctx           The generic cipher context.
 * \param tag           The buffer to write the tag to.
 * \param tag_len       The length of the tag to write.
 *
 * \return              \c 0 on success.
 * \return              A specific error code on failure.
 */
int ptls_cipher_write_tag( ptls_cipher_context_t *ctx,
                      unsigned char *tag, size_t tag_len );

/**
 * \brief               This function checks the tag for AEAD ciphers.
 *                      Currently supported with GCM and ChaCha20+Poly1305.
 *                      Must be called after ptls_cipher_finish().
 *
 * \param ctx           The generic cipher context.
 * \param tag           The buffer holding the tag.
 * \param tag_len       The length of the tag to check.
 *
 * \return              \c 0 on success.
 * \return              A specific error code on failure.
 */
int ptls_cipher_check_tag( ptls_cipher_context_t *ctx,
                      const unsigned char *tag, size_t tag_len );
#endif /* PTLS_GCM_C || PTLS_CHACHAPOLY_C */

/**
 * \brief               The generic all-in-one encryption/decryption function,
 *                      for all ciphers except AEAD constructs.
 *
 * \param ctx           The generic cipher context.
 * \param iv            The IV to use, or NONCE_COUNTER for CTR-mode ciphers.
 * \param iv_len        The IV length for ciphers with variable-size IV.
 *                      This parameter is discarded by ciphers with fixed-size
 *                      IV.
 * \param input         The buffer holding the input data.
 * \param ilen          The length of the input data.
 * \param output        The buffer for the output data. Must be able to hold at
 *                      least \p ilen + block_size. Must not be the same buffer
 *                      as input.
 * \param olen          The length of the output data, to be updated with the
 *                      actual number of Bytes written.
 *
 * \note                Some ciphers do not use IVs nor nonce. For these
 *                      ciphers, use \p iv = NULL and \p iv_len = 0.
 *
 * \return              \c 0 on success.
 * \return              #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #PTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED on decryption
 *                      expecting a full block but not receiving one.
 * \return              #PTLS_ERR_CIPHER_INVALID_PADDING on invalid padding
 *                      while decrypting.
 * \return              A cipher-specific error code on failure.
 */
int ptls_cipher_crypt( ptls_cipher_context_t *ctx,
                  const unsigned char *iv, size_t iv_len,
                  const unsigned char *input, size_t ilen,
                  unsigned char *output, size_t *olen );

#if defined(PTLS_CIPHER_MODE_AEAD)
/**
 * \brief               The generic autenticated encryption (AEAD) function.
 *
 * \param ctx           The generic cipher context.
 * \param iv            The IV to use, or NONCE_COUNTER for CTR-mode ciphers.
 * \param iv_len        The IV length for ciphers with variable-size IV.
 *                      This parameter is discarded by ciphers with fixed-size IV.
 * \param ad            The additional data to authenticate.
 * \param ad_len        The length of \p ad.
 * \param input         The buffer holding the input data.
 * \param ilen          The length of the input data.
 * \param output        The buffer for the output data.
 *                      Must be able to hold at least \p ilen.
 * \param olen          The length of the output data, to be updated with the
 *                      actual number of Bytes written.
 * \param tag           The buffer for the authentication tag.
 * \param tag_len       The desired length of the authentication tag.
 *
 * \return              \c 0 on success.
 * \return              #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              A cipher-specific error code on failure.
 */
int ptls_cipher_auth_encrypt( ptls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         unsigned char *tag, size_t tag_len );

/**
 * \brief               The generic autenticated decryption (AEAD) function.
 *
 * \note                If the data is not authentic, then the output buffer
 *                      is zeroed out to prevent the unauthentic plaintext being
 *                      used, making this interface safer.
 *
 * \param ctx           The generic cipher context.
 * \param iv            The IV to use, or NONCE_COUNTER for CTR-mode ciphers.
 * \param iv_len        The IV length for ciphers with variable-size IV.
 *                      This parameter is discarded by ciphers with fixed-size IV.
 * \param ad            The additional data to be authenticated.
 * \param ad_len        The length of \p ad.
 * \param input         The buffer holding the input data.
 * \param ilen          The length of the input data.
 * \param output        The buffer for the output data.
 *                      Must be able to hold at least \p ilen.
 * \param olen          The length of the output data, to be updated with the
 *                      actual number of Bytes written.
 * \param tag           The buffer holding the authentication tag.
 * \param tag_len       The length of the authentication tag.
 *
 * \return              \c 0 on success.
 * \return              #PTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #PTLS_ERR_CIPHER_AUTH_FAILED if data is not authentic.
 * \return              A cipher-specific error code on failure.
 */
int ptls_cipher_auth_decrypt( ptls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         const unsigned char *tag, size_t tag_len );
#endif /* PTLS_CIPHER_MODE_AEAD */

#ifdef __cplusplus
}
#endif

#endif /* PTLS_CIPHER_H */
