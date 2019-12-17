/**
 * \file ssl.h
 *
 * \brief SSL/TLS functions.
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
#ifndef PTLS_SSL_H
#define PTLS_SSL_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#include "bignum.h"
#include "ecp.h"

#include "ssl_ciphersuites.h"

#if defined(PTLS_X509_CRT_PARSE_C)
#include "x509_crt.h"
#include "x509_crl.h"
#endif

#if defined(PTLS_DHM_C)
#include "dhm.h"
#endif

#if defined(PTLS_ECDH_C)
#include "ecdh.h"
#endif

#if defined(PTLS_ZLIB_SUPPORT)

#if defined(PTLS_DEPRECATED_WARNING)
#warning "Record compression support via PTLS_ZLIB_SUPPORT is deprecated and will be removed in the next major revision of the library"
#endif

#if defined(PTLS_DEPRECATED_REMOVED)
#error "Record compression support via PTLS_ZLIB_SUPPORT is deprecated and cannot be used if PTLS_DEPRECATED_REMOVED is set"
#endif

#include "zlib.h"
#endif

#if defined(PTLS_HAVE_TIME)
#include "platform_time.h"
#endif

#if defined(PTLS_X509_CRT_PARSE_C)

typedef struct ptls_x509_ca_st {
    ptls_x509_crt *crt;
    ptls_x509_crl *crl;
    struct ptls_x509_ca_st *next;
} ptls_x509_ca;

#endif

/*
 * SSL Error codes
 */
#define PTLS_ERR_SSL_FEATURE_UNAVAILABLE               -0x7080  /**< The requested feature is not available. */
#define PTLS_ERR_SSL_BAD_INPUT_DATA                    -0x7100  /**< Bad input parameters to function. */
#define PTLS_ERR_SSL_INVALID_MAC                       -0x7180  /**< Verification of the message MAC failed. */
#define PTLS_ERR_SSL_INVALID_RECORD                    -0x7200  /**< An invalid SSL record was received. */
#define PTLS_ERR_SSL_CONN_EOF                          -0x7280  /**< The connection indicated an EOF. */
#define PTLS_ERR_SSL_UNKNOWN_CIPHER                    -0x7300  /**< An unknown cipher was received. */
#define PTLS_ERR_SSL_NO_CIPHER_CHOSEN                  -0x7380  /**< The server has no ciphersuites in common with the client. */
#define PTLS_ERR_SSL_NO_RNG                            -0x7400  /**< No RNG was provided to the SSL module. */
#define PTLS_ERR_SSL_NO_CLIENT_CERTIFICATE             -0x7480  /**< No client certification received from the client, but required by the authentication mode. */
#define PTLS_ERR_SSL_CERTIFICATE_TOO_LARGE             -0x7500  /**< Our own certificate(s) is/are too large to send in an SSL message. */
#define PTLS_ERR_SSL_CERTIFICATE_REQUIRED              -0x7580  /**< The own certificate is not set, but needed by the server. */
#define PTLS_ERR_SSL_PRIVATE_KEY_REQUIRED              -0x7600  /**< The own private key or pre-shared key is not set, but needed. */
#define PTLS_ERR_SSL_CA_CHAIN_REQUIRED                 -0x7680  /**< No CA Chain is set, but required to operate. */
#define PTLS_ERR_SSL_UNEXPECTED_MESSAGE                -0x7700  /**< An unexpected message was received from our peer. */
#define PTLS_ERR_SSL_FATAL_ALERT_MESSAGE               -0x7780  /**< A fatal alert message was received from our peer. */
#define PTLS_ERR_SSL_PEER_VERIFY_FAILED                -0x7800  /**< Verification of our peer failed. */
#define PTLS_ERR_SSL_PEER_CLOSE_NOTIFY                 -0x7880  /**< The peer notified us that the connection is going to be closed. */
#define PTLS_ERR_SSL_BAD_HS_CLIENT_HELLO               -0x7900  /**< Processing of the ClientHello handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_SERVER_HELLO               -0x7980  /**< Processing of the ServerHello handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_CERTIFICATE                -0x7A00  /**< Processing of the Certificate handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST        -0x7A80  /**< Processing of the CertificateRequest handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE        -0x7B00  /**< Processing of the ServerKeyExchange handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_SERVER_HELLO_DONE          -0x7B80  /**< Processing of the ServerHelloDone handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE        -0x7C00  /**< Processing of the ClientKeyExchange handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP     -0x7C80  /**< Processing of the ClientKeyExchange handshake message failed in DHM / ECDH Read Public. */
#define PTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS     -0x7D00  /**< Processing of the ClientKeyExchange handshake message failed in DHM / ECDH Calculate Secret. */
#define PTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY         -0x7D80  /**< Processing of the CertificateVerify handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_CHANGE_CIPHER_SPEC         -0x7E00  /**< Processing of the ChangeCipherSpec handshake message failed. */
#define PTLS_ERR_SSL_BAD_HS_FINISHED                   -0x7E80  /**< Processing of the Finished handshake message failed. */
#define PTLS_ERR_SSL_ALLOC_FAILED                      -0x7F00  /**< Memory allocation failed */
#define PTLS_ERR_SSL_HW_ACCEL_FAILED                   -0x7F80  /**< Hardware acceleration function returned with error */
#define PTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH              -0x6F80  /**< Hardware acceleration function skipped / left alone data */
#define PTLS_ERR_SSL_COMPRESSION_FAILED                -0x6F00  /**< Processing of the compression / decompression failed */
#define PTLS_ERR_SSL_BAD_HS_PROTOCOL_VERSION           -0x6E80  /**< Handshake protocol not within min/max boundaries */
#define PTLS_ERR_SSL_BAD_HS_NEW_SESSION_TICKET         -0x6E00  /**< Processing of the NewSessionTicket handshake message failed. */
#define PTLS_ERR_SSL_SESSION_TICKET_EXPIRED            -0x6D80  /**< Session ticket has expired. */
#define PTLS_ERR_SSL_PK_TYPE_MISMATCH                  -0x6D00  /**< Public key type mismatch (eg, asked for RSA key exchange and presented EC key) */
#define PTLS_ERR_SSL_UNKNOWN_IDENTITY                  -0x6C80  /**< Unknown identity received (eg, PSK identity) */
#define PTLS_ERR_SSL_INTERNAL_ERROR                    -0x6C00  /**< Internal error (eg, unexpected failure in lower-level module) */
#define PTLS_ERR_SSL_COUNTER_WRAPPING                  -0x6B80  /**< A counter would wrap (eg, too many messages exchanged). */
#define PTLS_ERR_SSL_WAITING_SERVER_HELLO_RENEGO       -0x6B00  /**< Unexpected message at ServerHello in renegotiation. */
#define PTLS_ERR_SSL_HELLO_VERIFY_REQUIRED             -0x6A80  /**< DTLS client must retry for hello verification */
#define PTLS_ERR_SSL_BUFFER_TOO_SMALL                  -0x6A00  /**< A buffer is too small to receive or write a message */
#define PTLS_ERR_SSL_NO_USABLE_CIPHERSUITE             -0x6980  /**< None of the common ciphersuites is usable (eg, no suitable certificate, see debug messages). */
#define PTLS_ERR_SSL_WANT_READ                         -0x6900  /**< No data of requested type currently available on underlying transport. */
#define PTLS_ERR_SSL_WANT_WRITE                        -0x6880  /**< Connection requires a write call. */
#define PTLS_ERR_SSL_TIMEOUT                           -0x6800  /**< The operation timed out. */
#define PTLS_ERR_SSL_CLIENT_RECONNECT                  -0x6780  /**< The client initiated a reconnect from the same port. */
#define PTLS_ERR_SSL_UNEXPECTED_RECORD                 -0x6700  /**< Record header looks valid but is not expected. */
#define PTLS_ERR_SSL_NON_FATAL                         -0x6680  /**< The alert message received indicates a non-fatal error. */
#define PTLS_ERR_SSL_INVALID_VERIFY_HASH               -0x6600  /**< Couldn't set the hash for verifying CertificateVerify */
#define PTLS_ERR_SSL_CONTINUE_PROCESSING               -0x6580  /**< Internal-only message signaling that further message-processing should be done */
#define PTLS_ERR_SSL_ASYNC_IN_PROGRESS                 -0x6500  /**< The asynchronous operation is not completed yet. */
#define PTLS_ERR_SSL_EARLY_MESSAGE                     -0x6480  /**< Internal-only message signaling that a message arrived early. */

/*
 * Various constants
 */
#define PTLS_SSL_MAJOR_VERSION_3             3
#define PTLS_SSL_MINOR_VERSION_0             0   /*!< SSL v3.0 */
#define PTLS_SSL_MINOR_VERSION_1             1   /*!< TLS v1.0 */
#define PTLS_SSL_MINOR_VERSION_2             2   /*!< TLS v1.1 */
#define PTLS_SSL_MINOR_VERSION_3             3   /*!< TLS v1.2 */

#define PTLS_SSL_TRANSPORT_STREAM            0   /*!< TLS      */
#define PTLS_SSL_TRANSPORT_DATAGRAM          1   /*!< DTLS     */

#define PTLS_SSL_MAX_HOST_NAME_LEN           255 /*!< Maximum host name defined in RFC 1035 */

/* RFC 6066 section 4, see also mfl_code_to_length in ssl_tls.c
 * NONE must be zero so that memset()ing structure to zero works */
#define PTLS_SSL_MAX_FRAG_LEN_NONE           0   /*!< don't use this extension   */
#define PTLS_SSL_MAX_FRAG_LEN_512            1   /*!< MaxFragmentLength 2^9      */
#define PTLS_SSL_MAX_FRAG_LEN_1024           2   /*!< MaxFragmentLength 2^10     */
#define PTLS_SSL_MAX_FRAG_LEN_2048           3   /*!< MaxFragmentLength 2^11     */
#define PTLS_SSL_MAX_FRAG_LEN_4096           4   /*!< MaxFragmentLength 2^12     */
#define PTLS_SSL_MAX_FRAG_LEN_INVALID        5   /*!< first invalid value        */

#define PTLS_SSL_IS_CLIENT                   0
#define PTLS_SSL_IS_SERVER                   1

#define PTLS_SSL_IS_NOT_FALLBACK             0
#define PTLS_SSL_IS_FALLBACK                 1

#define PTLS_SSL_EXTENDED_MS_DISABLED        0
#define PTLS_SSL_EXTENDED_MS_ENABLED         1

#define PTLS_SSL_ETM_DISABLED                0
#define PTLS_SSL_ETM_ENABLED                 1

#define PTLS_SSL_COMPRESS_NULL               0
#define PTLS_SSL_COMPRESS_DEFLATE            1

#define PTLS_SSL_VERIFY_NONE                 0
#define PTLS_SSL_VERIFY_OPTIONAL             1
#define PTLS_SSL_VERIFY_REQUIRED             2
#define PTLS_SSL_VERIFY_UNSET                3 /* Used only for sni_authmode */

#define PTLS_SSL_VERIFY_TYPE_CRL             0
#define PTLS_SSL_VERIFY_TYPE_OCSP            1

#define PTLS_SSL_LEGACY_RENEGOTIATION        0
#define PTLS_SSL_SECURE_RENEGOTIATION        1

#define PTLS_SSL_RENEGOTIATION_DISABLED      0
#define PTLS_SSL_RENEGOTIATION_ENABLED       1

#define PTLS_SSL_ANTI_REPLAY_DISABLED        0
#define PTLS_SSL_ANTI_REPLAY_ENABLED         1

#define PTLS_SSL_RENEGOTIATION_NOT_ENFORCED  -1
#define PTLS_SSL_RENEGO_MAX_RECORDS_DEFAULT  16

#define PTLS_SSL_LEGACY_NO_RENEGOTIATION     0
#define PTLS_SSL_LEGACY_ALLOW_RENEGOTIATION  1
#define PTLS_SSL_LEGACY_BREAK_HANDSHAKE      2

#define PTLS_SSL_TRUNC_HMAC_DISABLED         0
#define PTLS_SSL_TRUNC_HMAC_ENABLED          1
#define PTLS_SSL_TRUNCATED_HMAC_LEN          10  /* 80 bits, rfc 6066 section 7 */

#define PTLS_SSL_SESSION_TICKETS_DISABLED     0
#define PTLS_SSL_SESSION_TICKETS_ENABLED      1

#define PTLS_SSL_CBC_RECORD_SPLITTING_DISABLED    0
#define PTLS_SSL_CBC_RECORD_SPLITTING_ENABLED     1

#define PTLS_SSL_ARC4_ENABLED                0
#define PTLS_SSL_ARC4_DISABLED               1

#define PTLS_SSL_PRESET_DEFAULT              0
#define PTLS_SSL_PRESET_SUITEB               2

#define PTLS_SSL_CERT_REQ_CA_LIST_ENABLED       1
#define PTLS_SSL_CERT_REQ_CA_LIST_DISABLED      0

/*
 * Default range for DTLS retransmission timer value, in milliseconds.
 * RFC 6347 4.2.4.1 says from 1 second to 60 seconds.
 */
#define PTLS_SSL_DTLS_TIMEOUT_DFL_MIN    1000
#define PTLS_SSL_DTLS_TIMEOUT_DFL_MAX   60000

/**
 * \name SECTION: Module settings
 *
 * The configuration options you can set for this module are in this section.
 * Either change them in config.h or define them on the compiler command line.
 * \{
 */

#if !defined(PTLS_SSL_DEFAULT_TICKET_LIFETIME)
#define PTLS_SSL_DEFAULT_TICKET_LIFETIME     86400 /**< Lifetime of session tickets (if enabled) */
#endif

/*
 * Maximum fragment length in bytes,
 * determines the size of each of the two internal I/O buffers.
 *
 * Note: the RFC defines the default size of SSL / TLS messages. If you
 * change the value here, other clients / servers may not be able to
 * communicate with you anymore. Only change this value if you control
 * both sides of the connection and have it reduced at both sides, or
 * if you're using the Max Fragment Length extension and you know all your
 * peers are using it too!
 */
#if !defined(PTLS_SSL_MAX_CONTENT_LEN)
#define PTLS_SSL_MAX_CONTENT_LEN         16384   /**< Size of the input / output buffer */
#endif

#if !defined(PTLS_SSL_IN_CONTENT_LEN)
#define PTLS_SSL_IN_CONTENT_LEN PTLS_SSL_MAX_CONTENT_LEN
#endif

#if !defined(PTLS_SSL_OUT_CONTENT_LEN)
#define PTLS_SSL_OUT_CONTENT_LEN PTLS_SSL_MAX_CONTENT_LEN
#endif

/*
 * Maximum number of heap-allocated bytes for the purpose of
 * DTLS handshake message reassembly and future message buffering.
 */
#if !defined(PTLS_SSL_DTLS_MAX_BUFFERING)
#define PTLS_SSL_DTLS_MAX_BUFFERING 32768
#endif

/* \} name SECTION: Module settings */

/*
 * Length of the verify data for secure renegotiation
 */
#if defined(PTLS_SSL_PROTO_SSL3)
#define PTLS_SSL_VERIFY_DATA_MAX_LEN 36
#else
#define PTLS_SSL_VERIFY_DATA_MAX_LEN 12
#endif

/*
 * Signaling ciphersuite values (SCSV)
 */
#define PTLS_SSL_EMPTY_RENEGOTIATION_INFO    0xFF   /**< renegotiation info ext */
#define PTLS_SSL_FALLBACK_SCSV_VALUE         0x5600 /**< RFC 7507 section 2 */

/*
 * Supported Signature and Hash algorithms (For TLS 1.2)
 * RFC 5246 section 7.4.1.4.1
 */
#define PTLS_SSL_HASH_NONE                0
#define PTLS_SSL_HASH_MD5                 1
#define PTLS_SSL_HASH_SHA1                2
#define PTLS_SSL_HASH_SHA224              3
#define PTLS_SSL_HASH_SHA256              4
#define PTLS_SSL_HASH_SHA384              5
#define PTLS_SSL_HASH_SHA512              6

#define PTLS_SSL_SIG_ANON                 0
#define PTLS_SSL_SIG_RSA                  1
#define PTLS_SSL_SIG_ECDSA                3

/*
 * Client Certificate Types
 * RFC 5246 section 7.4.4 plus RFC 4492 section 5.5
 */
#define PTLS_SSL_CERT_TYPE_RSA_SIGN       1
#define PTLS_SSL_CERT_TYPE_ECDSA_SIGN    64

/*
 * Message, alert and handshake types
 */
#define PTLS_SSL_MSG_CHANGE_CIPHER_SPEC     20
#define PTLS_SSL_MSG_ALERT                  21
#define PTLS_SSL_MSG_HANDSHAKE              22
#define PTLS_SSL_MSG_APPLICATION_DATA       23

#define PTLS_SSL_ALERT_LEVEL_WARNING         1
#define PTLS_SSL_ALERT_LEVEL_FATAL           2

#define PTLS_SSL_ALERT_MSG_CLOSE_NOTIFY           0  /* 0x00 */
#define PTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE    10  /* 0x0A */
#define PTLS_SSL_ALERT_MSG_BAD_RECORD_MAC        20  /* 0x14 */
#define PTLS_SSL_ALERT_MSG_DECRYPTION_FAILED     21  /* 0x15 */
#define PTLS_SSL_ALERT_MSG_RECORD_OVERFLOW       22  /* 0x16 */
#define PTLS_SSL_ALERT_MSG_DECOMPRESSION_FAILURE 30  /* 0x1E */
#define PTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE     40  /* 0x28 */
#define PTLS_SSL_ALERT_MSG_NO_CERT               41  /* 0x29 */
#define PTLS_SSL_ALERT_MSG_BAD_CERT              42  /* 0x2A */
#define PTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT      43  /* 0x2B */
#define PTLS_SSL_ALERT_MSG_CERT_REVOKED          44  /* 0x2C */
#define PTLS_SSL_ALERT_MSG_CERT_EXPIRED          45  /* 0x2D */
#define PTLS_SSL_ALERT_MSG_CERT_UNKNOWN          46  /* 0x2E */
#define PTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER     47  /* 0x2F */
#define PTLS_SSL_ALERT_MSG_UNKNOWN_CA            48  /* 0x30 */
#define PTLS_SSL_ALERT_MSG_ACCESS_DENIED         49  /* 0x31 */
#define PTLS_SSL_ALERT_MSG_DECODE_ERROR          50  /* 0x32 */
#define PTLS_SSL_ALERT_MSG_DECRYPT_ERROR         51  /* 0x33 */
#define PTLS_SSL_ALERT_MSG_EXPORT_RESTRICTION    60  /* 0x3C */
#define PTLS_SSL_ALERT_MSG_PROTOCOL_VERSION      70  /* 0x46 */
#define PTLS_SSL_ALERT_MSG_INSUFFICIENT_SECURITY 71  /* 0x47 */
#define PTLS_SSL_ALERT_MSG_INTERNAL_ERROR        80  /* 0x50 */
#define PTLS_SSL_ALERT_MSG_INAPROPRIATE_FALLBACK 86  /* 0x56 */
#define PTLS_SSL_ALERT_MSG_USER_CANCELED         90  /* 0x5A */
#define PTLS_SSL_ALERT_MSG_NO_RENEGOTIATION     100  /* 0x64 */
#define PTLS_SSL_ALERT_MSG_UNSUPPORTED_EXT      110  /* 0x6E */
#define PTLS_SSL_ALERT_MSG_UNRECOGNIZED_NAME    112  /* 0x70 */
#define PTLS_SSL_ALERT_MSG_UNKNOWN_PSK_IDENTITY 115  /* 0x73 */
#define PTLS_SSL_ALERT_MSG_NO_APPLICATION_PROTOCOL 120 /* 0x78 */

#define PTLS_SSL_HS_HELLO_REQUEST            0
#define PTLS_SSL_HS_CLIENT_HELLO             1
#define PTLS_SSL_HS_SERVER_HELLO             2
#define PTLS_SSL_HS_HELLO_VERIFY_REQUEST     3
#define PTLS_SSL_HS_NEW_SESSION_TICKET       4
#define PTLS_SSL_HS_CERTIFICATE             11
#define PTLS_SSL_HS_SERVER_KEY_EXCHANGE     12
#define PTLS_SSL_HS_CERTIFICATE_REQUEST     13
#define PTLS_SSL_HS_SERVER_HELLO_DONE       14
#define PTLS_SSL_HS_CERTIFICATE_VERIFY      15
#define PTLS_SSL_HS_CLIENT_KEY_EXCHANGE     16
#define PTLS_SSL_HS_FINISHED                20

/*
 * TLS extensions
 */
#define PTLS_TLS_EXT_SERVERNAME                   0
#define PTLS_TLS_EXT_SERVERNAME_HOSTNAME          0

#define PTLS_TLS_EXT_MAX_FRAGMENT_LENGTH          1

#define PTLS_TLS_EXT_TRUNCATED_HMAC               4

#define PTLS_TLS_EXT_SUPPORTED_ELLIPTIC_CURVES   10
#define PTLS_TLS_EXT_SUPPORTED_POINT_FORMATS     11

#define PTLS_TLS_EXT_SIG_ALG                     13

#define PTLS_TLS_EXT_ALPN                        16

#define PTLS_TLS_EXT_ENCRYPT_THEN_MAC            22 /* 0x16 */
#define PTLS_TLS_EXT_EXTENDED_MASTER_SECRET  0x0017 /* 23 */

#define PTLS_TLS_EXT_SESSION_TICKET              35

#define PTLS_TLS_EXT_ECJPAKE_KKPP               256 /* experimental */

#define PTLS_TLS_EXT_RENEGOTIATION_INFO      0xFF01

/*
 * Size defines
 */
#if !defined(PTLS_PSK_MAX_LEN)
#define PTLS_PSK_MAX_LEN            32 /* 256 bits */
#endif

/* Dummy type used only for its size */
union ptls_ssl_premaster_secret
{
#if defined(PTLS_KEY_EXCHANGE_RSA_ENABLED)
    unsigned char _pms_rsa[48];                         /* RFC 5246 8.1.1 */
#endif
#if defined(PTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)
    unsigned char _pms_dhm[PTLS_MPI_MAX_SIZE];      /* RFC 5246 8.1.2 */
#endif
#if defined(PTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)    || \
    defined(PTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)  || \
    defined(PTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)     || \
    defined(PTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
    unsigned char _pms_ecdh[PTLS_ECP_MAX_BYTES];    /* RFC 4492 5.10 */
#endif
#if defined(PTLS_KEY_EXCHANGE_PSK_ENABLED)
    unsigned char _pms_psk[4 + 2 * PTLS_PSK_MAX_LEN];       /* RFC 4279 2 */
#endif
#if defined(PTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
    unsigned char _pms_dhe_psk[4 + PTLS_MPI_MAX_SIZE
                                 + PTLS_PSK_MAX_LEN];       /* RFC 4279 3 */
#endif
#if defined(PTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
    unsigned char _pms_rsa_psk[52 + PTLS_PSK_MAX_LEN];      /* RFC 4279 4 */
#endif
#if defined(PTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
    unsigned char _pms_ecdhe_psk[4 + PTLS_ECP_MAX_BYTES
                                   + PTLS_PSK_MAX_LEN];     /* RFC 5489 2 */
#endif
#if defined(PTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    unsigned char _pms_ecjpake[32];     /* Thread spec: SHA-256 output */
#endif
};

#define PTLS_PREMASTER_SIZE     sizeof( union ptls_ssl_premaster_secret )

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SSL state machine
 */
typedef enum
{
    PTLS_SSL_HELLO_REQUEST,
    PTLS_SSL_CLIENT_HELLO,
    PTLS_SSL_SERVER_HELLO,
    PTLS_SSL_SERVER_CERTIFICATE,
    PTLS_SSL_SERVER_KEY_EXCHANGE,
    PTLS_SSL_CERTIFICATE_REQUEST,
    PTLS_SSL_SERVER_HELLO_DONE,
    PTLS_SSL_CLIENT_CERTIFICATE,
    PTLS_SSL_CLIENT_KEY_EXCHANGE,
    PTLS_SSL_CERTIFICATE_VERIFY,
    PTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC,
    PTLS_SSL_CLIENT_FINISHED,
    PTLS_SSL_SERVER_CHANGE_CIPHER_SPEC,
    PTLS_SSL_SERVER_FINISHED,
    PTLS_SSL_FLUSH_BUFFERS,
    PTLS_SSL_HANDSHAKE_WRAPUP,
    PTLS_SSL_HANDSHAKE_OVER,
    PTLS_SSL_SERVER_NEW_SESSION_TICKET,
    PTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT,
}
ptls_ssl_states;

/**
 * \brief          Callback type: send data on the network.
 *
 * \note           That callback may be either blocking or non-blocking.
 *
 * \param ctx      Context for the send callback (typically a file descriptor)
 * \param buf      Buffer holding the data to send
 * \param len      Length of the data to send
 *
 * \return         The callback must return the number of bytes sent if any,
 *                 or a non-zero error code.
 *                 If performing non-blocking I/O, \c PTLS_ERR_SSL_WANT_WRITE
 *                 must be returned when the operation would block.
 *
 * \note           The callback is allowed to send fewer bytes than requested.
 *                 It must always return the number of bytes actually sent.
 */
typedef int ptls_ssl_send_t( void *ctx,
                                const unsigned char *buf,
                                size_t len );

/**
 * \brief          Callback type: receive data from the network.
 *
 * \note           That callback may be either blocking or non-blocking.
 *
 * \param ctx      Context for the receive callback (typically a file
 *                 descriptor)
 * \param buf      Buffer to write the received data to
 * \param len      Length of the receive buffer
 *
 * \return         The callback must return the number of bytes received,
 *                 or a non-zero error code.
 *                 If performing non-blocking I/O, \c PTLS_ERR_SSL_WANT_READ
 *                 must be returned when the operation would block.
 *
 * \note           The callback may receive fewer bytes than the length of the
 *                 buffer. It must always return the number of bytes actually
 *                 received and written to the buffer.
 */
typedef int ptls_ssl_recv_t( void *ctx,
                                unsigned char *buf,
                                size_t len );

/**
 * \brief          Callback type: receive data from the network, with timeout
 *
 * \note           That callback must block until data is received, or the
 *                 timeout delay expires, or the operation is interrupted by a
 *                 signal.
 *
 * \param ctx      Context for the receive callback (typically a file descriptor)
 * \param buf      Buffer to write the received data to
 * \param len      Length of the receive buffer
 * \param timeout  Maximum nomber of millisecondes to wait for data
 *                 0 means no timeout (potentially waiting forever)
 *
 * \return         The callback must return the number of bytes received,
 *                 or a non-zero error code:
 *                 \c PTLS_ERR_SSL_TIMEOUT if the operation timed out,
 *                 \c PTLS_ERR_SSL_WANT_READ if interrupted by a signal.
 *
 * \note           The callback may receive fewer bytes than the length of the
 *                 buffer. It must always return the number of bytes actually
 *                 received and written to the buffer.
 */
typedef int ptls_ssl_recv_timeout_t( void *ctx,
                                        unsigned char *buf,
                                        size_t len,
                                        uint32_t timeout );
/**
 * \brief          Callback type: set a pair of timers/delays to watch
 *
 * \param ctx      Context pointer
 * \param int_ms   Intermediate delay in milliseconds
 * \param fin_ms   Final delay in milliseconds
 *                 0 cancels the current timer.
 *
 * \note           This callback must at least store the necessary information
 *                 for the associated \c ptls_ssl_get_timer_t callback to
 *                 return correct information.
 *
 * \note           If using a event-driven style of programming, an event must
 *                 be generated when the final delay is passed. The event must
 *                 cause a call to \c ptls_ssl_handshake() with the proper
 *                 SSL context to be scheduled. Care must be taken to ensure
 *                 that at most one such call happens at a time.
 *
 * \note           Only one timer at a time must be running. Calling this
 *                 function while a timer is running must cancel it. Cancelled
 *                 timers must not generate any event.
 */
typedef void ptls_ssl_set_timer_t( void * ctx,
                                      uint32_t int_ms,
                                      uint32_t fin_ms );

/**
 * \brief          Callback type: get status of timers/delays
 *
 * \param ctx      Context pointer
 *
 * \return         This callback must return:
 *                 -1 if cancelled (fin_ms == 0),
 *                  0 if none of the delays have passed,
 *                  1 if only the intermediate delay has passed,
 *                  2 if the final delay has passed.
 */
typedef int ptls_ssl_get_timer_t( void * ctx );

/* Defined below */
typedef struct ptls_ssl_session ptls_ssl_session;
typedef struct ptls_ssl_context ptls_ssl_context;
typedef struct ptls_ssl_config  ptls_ssl_config;

/* Defined in ssl_internal.h */
typedef struct ptls_ssl_transform ptls_ssl_transform;
typedef struct ptls_ssl_handshake_params ptls_ssl_handshake_params;
typedef struct ptls_ssl_sig_hash_set_t ptls_ssl_sig_hash_set_t;
#if defined(PTLS_X509_CRT_PARSE_C)
typedef struct ptls_ssl_key_cert ptls_ssl_key_cert;
#endif
#if defined(PTLS_SSL_PROTO_DTLS)
typedef struct ptls_ssl_flight_item ptls_ssl_flight_item;
#endif

#if defined(PTLS_SSL_ASYNC_PRIVATE)
#if defined(PTLS_X509_CRT_PARSE_C)
/**
 * \brief           Callback type: start external signature operation.
 *
 *                  This callback is called during an SSL handshake to start
 *                  a signature decryption operation using an
 *                  external processor. The parameter \p cert contains
 *                  the public key; it is up to the callback function to
 *                  determine how to access the associated private key.
 *
 *                  This function typically sends or enqueues a request, and
 *                  does not wait for the operation to complete. This allows
 *                  the handshake step to be non-blocking.
 *
 *                  The parameters \p ssl and \p cert are guaranteed to remain
 *                  valid throughout the handshake. On the other hand, this
 *                  function must save the contents of \p hash if the value
 *                  is needed for later processing, because the \p hash buffer
 *                  is no longer valid after this function returns.
 *
 *                  This function may call ptls_ssl_set_async_operation_data()
 *                  to store an operation context for later retrieval
 *                  by the resume or cancel callback.
 *
 * \note            For RSA signatures, this function must produce output
 *                  that is consistent with PKCS#1 v1.5 in the same way as
 *                  ptls_rsa_pkcs1_sign(). Before the private key operation,
 *                  apply the padding steps described in RFC 8017, section 9.2
 *                  "EMSA-PKCS1-v1_5" as follows.
 *                  - If \p md_alg is #PTLS_MD_NONE, apply the PKCS#1 v1.5
 *                    encoding, treating \p hash as the DigestInfo to be
 *                    padded. In other words, apply EMSA-PKCS1-v1_5 starting
 *                    from step 3, with `T = hash` and `tLen = hash_len`.
 *                  - If `md_alg != PTLS_MD_NONE`, apply the PKCS#1 v1.5
 *                    encoding, treating \p hash as the hash to be encoded and
 *                    padded. In other words, apply EMSA-PKCS1-v1_5 starting
 *                    from step 2, with `digestAlgorithm` obtained by calling
 *                    ptls_oid_get_oid_by_md() on \p md_alg.
 *
 * \note            For ECDSA signatures, the output format is the DER encoding
 *                  `Ecdsa-Sig-Value` defined in
 *                  [RFC 4492 section 5.4](https://tools.ietf.org/html/rfc4492#section-5.4).
 *
 * \param ssl             The SSL connection instance. It should not be
 *                        modified other than via
 *                        ptls_ssl_set_async_operation_data().
 * \param cert            Certificate containing the public key.
 *                        In simple cases, this is one of the pointers passed to
 *                        ptls_ssl_conf_own_cert() when configuring the SSL
 *                        connection. However, if other callbacks are used, this
 *                        property may not hold. For example, if an SNI callback
 *                        is registered with ptls_ssl_conf_sni(), then
 *                        this callback determines what certificate is used.
 * \param md_alg          Hash algorithm.
 * \param hash            Buffer containing the hash. This buffer is
 *                        no longer valid when the function returns.
 * \param hash_len        Size of the \c hash buffer in bytes.
 *
 * \return          0 if the operation was started successfully and the SSL
 *                  stack should call the resume callback immediately.
 * \return          #PTLS_ERR_SSL_ASYNC_IN_PROGRESS if the operation
 *                  was started successfully and the SSL stack should return
 *                  immediately without calling the resume callback yet.
 * \return          #PTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH if the external
 *                  processor does not support this key. The SSL stack will
 *                  use the private key object instead.
 * \return          Any other error indicates a fatal failure and is
 *                  propagated up the call chain. The callback should
 *                  use \c PTLS_ERR_PK_xxx error codes, and <b>must not</b>
 *                  use \c PTLS_ERR_SSL_xxx error codes except as
 *                  directed in the documentation of this callback.
 */
typedef int ptls_ssl_async_sign_t( ptls_ssl_context *ssl,
                                      ptls_x509_crt *cert,
                                      ptls_md_type_t md_alg,
                                      const unsigned char *hash,
                                      size_t hash_len );

/**
 * \brief           Callback type: start external decryption operation.
 *
 *                  This callback is called during an SSL handshake to start
 *                  an RSA decryption operation using an
 *                  external processor. The parameter \p cert contains
 *                  the public key; it is up to the callback function to
 *                  determine how to access the associated private key.
 *
 *                  This function typically sends or enqueues a request, and
 *                  does not wait for the operation to complete. This allows
 *                  the handshake step to be non-blocking.
 *
 *                  The parameters \p ssl and \p cert are guaranteed to remain
 *                  valid throughout the handshake. On the other hand, this
 *                  function must save the contents of \p input if the value
 *                  is needed for later processing, because the \p input buffer
 *                  is no longer valid after this function returns.
 *
 *                  This function may call ptls_ssl_set_async_operation_data()
 *                  to store an operation context for later retrieval
 *                  by the resume or cancel callback.
 *
 * \warning         RSA decryption as used in TLS is subject to a potential
 *                  timing side channel attack first discovered by Bleichenbacher
 *                  in 1998. This attack can be remotely exploitable
 *                  in practice. To avoid this attack, you must ensure that
 *                  if the callback performs an RSA decryption, the time it
 *                  takes to execute and return the result does not depend
 *                  on whether the RSA decryption succeeded or reported
 *                  invalid padding.
 *
 * \param ssl             The SSL connection instance. It should not be
 *                        modified other than via
 *                        ptls_ssl_set_async_operation_data().
 * \param cert            Certificate containing the public key.
 *                        In simple cases, this is one of the pointers passed to
 *                        ptls_ssl_conf_own_cert() when configuring the SSL
 *                        connection. However, if other callbacks are used, this
 *                        property may not hold. For example, if an SNI callback
 *                        is registered with ptls_ssl_conf_sni(), then
 *                        this callback determines what certificate is used.
 * \param input           Buffer containing the input ciphertext. This buffer
 *                        is no longer valid when the function returns.
 * \param input_len       Size of the \p input buffer in bytes.
 *
 * \return          0 if the operation was started successfully and the SSL
 *                  stack should call the resume callback immediately.
 * \return          #PTLS_ERR_SSL_ASYNC_IN_PROGRESS if the operation
 *                  was started successfully and the SSL stack should return
 *                  immediately without calling the resume callback yet.
 * \return          #PTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH if the external
 *                  processor does not support this key. The SSL stack will
 *                  use the private key object instead.
 * \return          Any other error indicates a fatal failure and is
 *                  propagated up the call chain. The callback should
 *                  use \c PTLS_ERR_PK_xxx error codes, and <b>must not</b>
 *                  use \c PTLS_ERR_SSL_xxx error codes except as
 *                  directed in the documentation of this callback.
 */
typedef int ptls_ssl_async_decrypt_t( ptls_ssl_context *ssl,
                                         ptls_x509_crt *cert,
                                         const unsigned char *input,
                                         size_t input_len );
#endif /* PTLS_X509_CRT_PARSE_C */

/**
 * \brief           Callback type: resume external operation.
 *
 *                  This callback is called during an SSL handshake to resume
 *                  an external operation started by the
 *                  ::ptls_ssl_async_sign_t or
 *                  ::ptls_ssl_async_decrypt_t callback.
 *
 *                  This function typically checks the status of a pending
 *                  request or causes the request queue to make progress, and
 *                  does not wait for the operation to complete. This allows
 *                  the handshake step to be non-blocking.
 *
 *                  This function may call ptls_ssl_get_async_operation_data()
 *                  to retrieve an operation context set by the start callback.
 *                  It may call ptls_ssl_set_async_operation_data() to modify
 *                  this context.
 *
 *                  Note that when this function returns a status other than
 *                  #PTLS_ERR_SSL_ASYNC_IN_PROGRESS, it must free any
 *                  resources associated with the operation.
 *
 * \param ssl             The SSL connection instance. It should not be
 *                        modified other than via
 *                        ptls_ssl_set_async_operation_data().
 * \param output          Buffer containing the output (signature or decrypted
 *                        data) on success.
 * \param output_len      On success, number of bytes written to \p output.
 * \param output_size     Size of the \p output buffer in bytes.
 *
 * \return          0 if output of the operation is available in the
 *                  \p output buffer.
 * \return          #PTLS_ERR_SSL_ASYNC_IN_PROGRESS if the operation
 *                  is still in progress. Subsequent requests for progress
 *                  on the SSL connection will call the resume callback
 *                  again.
 * \return          Any other error means that the operation is aborted.
 *                  The SSL handshake is aborted. The callback should
 *                  use \c PTLS_ERR_PK_xxx error codes, and <b>must not</b>
 *                  use \c PTLS_ERR_SSL_xxx error codes except as
 *                  directed in the documentation of this callback.
 */
typedef int ptls_ssl_async_resume_t( ptls_ssl_context *ssl,
                                        unsigned char *output,
                                        size_t *output_len,
                                        size_t output_size );

/**
 * \brief           Callback type: cancel external operation.
 *
 *                  This callback is called if an SSL connection is closed
 *                  while an asynchronous operation is in progress. Note that
 *                  this callback is not called if the
 *                  ::ptls_ssl_async_resume_t callback has run and has
 *                  returned a value other than
 *                  #PTLS_ERR_SSL_ASYNC_IN_PROGRESS, since in that case
 *                  the asynchronous operation has already completed.
 *
 *                  This function may call ptls_ssl_get_async_operation_data()
 *                  to retrieve an operation context set by the start callback.
 *
 * \param ssl             The SSL connection instance. It should not be
 *                        modified.
 */
typedef void ptls_ssl_async_cancel_t( ptls_ssl_context *ssl );
#endif /* PTLS_SSL_ASYNC_PRIVATE */

/*
 * This structure is used for storing current session data.
 */
struct ptls_ssl_session
{
#if defined(PTLS_HAVE_TIME)
    ptls_time_t start;       /*!< starting time      */
#endif
    int ciphersuite;            /*!< chosen ciphersuite */
    int compression;            /*!< chosen compression */
    size_t id_len;              /*!< session id length  */
    unsigned char id[32];       /*!< session identifier */
    unsigned char master[48];   /*!< the master secret  */
    unsigned char client_rand[32];
    unsigned char server_rand[32];
    int  (*tls_prf)(const unsigned char *, size_t, const char *,
            const unsigned char *, size_t,
            unsigned char *, size_t);

#if defined(PTLS_X509_CRT_PARSE_C)
    ptls_x509_crt *peer_cert;        /*!< peer X.509 cert chain */
#endif /* PTLS_X509_CRT_PARSE_C */
    uint32_t verify_result;          /*!<  verification result     */

#if defined(PTLS_SSL_SESSION_TICKETS) && defined(PTLS_SSL_CLI_C)
    unsigned char *ticket;      /*!< RFC 5077 session ticket */
    size_t ticket_len;          /*!< session ticket length   */
    uint32_t ticket_lifetime;   /*!< ticket lifetime hint    */
#endif /* PTLS_SSL_SESSION_TICKETS && PTLS_SSL_CLI_C */

#if defined(PTLS_SSL_MAX_FRAGMENT_LENGTH)
    unsigned char mfl_code;     /*!< MaxFragmentLength negotiated by peer */
#endif /* PTLS_SSL_MAX_FRAGMENT_LENGTH */

#if defined(PTLS_SSL_TRUNCATED_HMAC)
    int trunc_hmac;             /*!< flag for truncated hmac activation   */
#endif /* PTLS_SSL_TRUNCATED_HMAC */

#if defined(PTLS_SSL_ENCRYPT_THEN_MAC)
    int encrypt_then_mac;       /*!< flag for EtM activation                */
#endif
};

/**
 * SSL/TLS configuration to be shared between ptls_ssl_context structures.
 */
struct ptls_ssl_config
{
    /* Group items by size (largest first) to minimize padding overhead */

    /*
     * Pointers
     */

    const int *ciphersuite_list[4]; /*!< allowed ciphersuites per version   */

    /** Callback for printing debug output                                  */
    void (*f_dbg)(void *, int, const char *, int, const char *);
    void *p_dbg;                    /*!< context for the debug function     */

    /** Callback for getting (pseudo-)random numbers                        */
    int  (*f_rng)(void *, unsigned char *, size_t);
    void *p_rng;                    /*!< context for the RNG function       */

    /** Callback to retrieve a session from the cache                       */
    int (*f_get_cache)(void *, ptls_ssl_session *);
    /** Callback to store a session into the cache                          */
    int (*f_set_cache)(void *, const ptls_ssl_session *);
    void *p_cache;                  /*!< context for cache callbacks        */

#if defined(PTLS_SSL_SERVER_NAME_INDICATION)
    /** Callback for setting cert according to SNI extension                */
    int (*f_sni)(void *, ptls_ssl_context *, const unsigned char *, size_t);
    void *p_sni;                    /*!< context for SNI callback           */
#endif

#if defined(PTLS_X509_CRT_PARSE_C)
    /** Callback to customize X.509 certificate chain verification          */
    int (*f_vrfy)(void *, ptls_x509_crt *, int, uint32_t *);
    void *p_vrfy;                   /*!< context for X.509 verify calllback */
#endif

#if defined(PTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
    /** Callback to retrieve PSK key from identity                          */
    int (*f_psk)(void *, ptls_ssl_context *, const unsigned char *, size_t);
    void *p_psk;                    /*!< context for PSK callback           */
#endif

#if defined(PTLS_SSL_DTLS_HELLO_VERIFY) && defined(PTLS_SSL_SRV_C)
    /** Callback to create & write a cookie for ClientHello veirifcation    */
    int (*f_cookie_write)( void *, unsigned char **, unsigned char *,
                           const unsigned char *, size_t );
    /** Callback to verify validity of a ClientHello cookie                 */
    int (*f_cookie_check)( void *, const unsigned char *, size_t,
                           const unsigned char *, size_t );
    void *p_cookie;                 /*!< context for the cookie callbacks   */
#endif

#if defined(PTLS_SSL_SESSION_TICKETS) && defined(PTLS_SSL_SRV_C)
    /** Callback to create & write a session ticket                         */
    int (*f_ticket_write)( void *, const ptls_ssl_session *,
            unsigned char *, const unsigned char *, size_t *, uint32_t * );
    /** Callback to parse a session ticket into a session structure         */
    int (*f_ticket_parse)( void *, ptls_ssl_session *, unsigned char *, size_t);
    void *p_ticket;                 /*!< context for the ticket callbacks   */
#endif /* PTLS_SSL_SESSION_TICKETS && PTLS_SSL_SRV_C */

#if defined(PTLS_SSL_EXPORT_KEYS)
    /** Callback to export key block and master secret                      */
    int (*f_export_keys)( void *, const unsigned char *,
            const unsigned char *, size_t, size_t, size_t );
    void *p_export_keys;            /*!< context for key export callback    */
#endif

#if defined(PTLS_X509_CRT_PARSE_C)
    const ptls_x509_crt_profile *cert_profile; /*!< verification profile */
    ptls_ssl_key_cert *key_cert; /*!< own certificate/key pair(s)        */
    ptls_x509_crt *ca_chain;     /*!< trusted CAs                        */
    ptls_x509_crl *ca_crl;       /*!< trusted CAs CRLs                   */
    ptls_x509_ca *ca;
#endif /* PTLS_X509_CRT_PARSE_C */

#if defined(PTLS_SSL_ASYNC_PRIVATE)
#if defined(PTLS_X509_CRT_PARSE_C)
    ptls_ssl_async_sign_t *f_async_sign_start; /*!< start asynchronous signature operation */
    ptls_ssl_async_decrypt_t *f_async_decrypt_start; /*!< start asynchronous decryption operation */
#endif /* PTLS_X509_CRT_PARSE_C */
    ptls_ssl_async_resume_t *f_async_resume; /*!< resume asynchronous operation */
    ptls_ssl_async_cancel_t *f_async_cancel; /*!< cancel asynchronous operation */
    void *p_async_config_data; /*!< Configuration data set by ptls_ssl_conf_async_private_cb(). */
#endif /* PTLS_SSL_ASYNC_PRIVATE */

#if defined(PTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
    const int *sig_hashes;          /*!< allowed signature hashes           */
#endif

#if defined(PTLS_ECP_C)
    const ptls_ecp_group_id *curve_list; /*!< allowed curves             */
#endif

#if defined(PTLS_DHM_C)
    ptls_mpi dhm_P;              /*!< prime modulus for DHM              */
    ptls_mpi dhm_G;              /*!< generator for DHM                  */
#endif

#if defined(PTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
    unsigned char *psk;             /*!< pre-shared key. This field should
                                         only be set via
                                         ptls_ssl_conf_psk() */
    size_t         psk_len;         /*!< length of the pre-shared key. This
                                         field should only be set via
                                         ptls_ssl_conf_psk() */
    unsigned char *psk_identity;    /*!< identity for PSK negotiation. This
                                         field should only be set via
                                         ptls_ssl_conf_psk() */
    size_t         psk_identity_len;/*!< length of identity. This field should
                                         only be set via
                                         ptls_ssl_conf_psk() */
#endif

#if defined(PTLS_SSL_ALPN)
    const char **alpn_list;         /*!< ordered list of protocols          */
#endif

    /*
     * Numerical settings (int then char)
     */

    uint32_t read_timeout;          /*!< timeout for ptls_ssl_read (ms)  */

#if defined(PTLS_SSL_PROTO_DTLS)
    uint32_t hs_timeout_min;        /*!< initial value of the handshake
                                         retransmission timeout (ms)        */
    uint32_t hs_timeout_max;        /*!< maximum value of the handshake
                                         retransmission timeout (ms)        */
#endif

#if defined(PTLS_SSL_RENEGOTIATION)
    int renego_max_records;         /*!< grace period for renegotiation     */
    unsigned char renego_period[8]; /*!< value of the record counters
                                         that triggers renegotiation        */
#endif

#if defined(PTLS_SSL_DTLS_BADMAC_LIMIT)
    unsigned int badmac_limit;      /*!< limit of records with a bad MAC    */
#endif

#if defined(PTLS_DHM_C) && defined(PTLS_SSL_CLI_C)
    unsigned int dhm_min_bitlen;    /*!< min. bit length of the DHM prime   */
#endif

    unsigned char max_major_ver;    /*!< max. major version used            */
    unsigned char max_minor_ver;    /*!< max. minor version used            */
    unsigned char min_major_ver;    /*!< min. major version used            */
    unsigned char min_minor_ver;    /*!< min. minor version used            */

    /*
     * Flags (bitfields)
     */

    unsigned int endpoint : 1;      /*!< 0: client, 1: server               */
    unsigned int transport : 1;     /*!< stream (TLS) or datagram (DTLS)    */
    unsigned int authmode : 2;      /*!< PTLS_SSL_VERIFY_XXX             */
    unsigned int authtype : 1;      /*!< PTLS_SSL_VERIFY_TYPE_XXX           */
    /* needed even with renego disabled for LEGACY_BREAK_HANDSHAKE          */
    unsigned int allow_legacy_renegotiation : 2 ; /*!< PTLS_LEGACY_XXX   */
#if defined(PTLS_ARC4_C)
    unsigned int arc4_disabled : 1; /*!< blacklist RC4 ciphersuites?        */
#endif
#if defined(PTLS_SSL_MAX_FRAGMENT_LENGTH)
    unsigned int mfl_code : 3;      /*!< desired fragment length            */
#endif
#if defined(PTLS_SSL_ENCRYPT_THEN_MAC)
    unsigned int encrypt_then_mac : 1 ; /*!< negotiate encrypt-then-mac?    */
#endif
#if defined(PTLS_SSL_EXTENDED_MASTER_SECRET)
    unsigned int extended_ms : 1;   /*!< negotiate extended master secret?  */
#endif
#if defined(PTLS_SSL_DTLS_ANTI_REPLAY)
    unsigned int anti_replay : 1;   /*!< detect and prevent replay?         */
#endif
#if defined(PTLS_SSL_CBC_RECORD_SPLITTING)
    unsigned int cbc_record_splitting : 1;  /*!< do cbc record splitting    */
#endif
#if defined(PTLS_SSL_RENEGOTIATION)
    unsigned int disable_renegotiation : 1; /*!< disable renegotiation?     */
#endif
#if defined(PTLS_SSL_TRUNCATED_HMAC)
    unsigned int trunc_hmac : 1;    /*!< negotiate truncated hmac?          */
#endif
#if defined(PTLS_SSL_SESSION_TICKETS)
    unsigned int session_tickets : 1;   /*!< use session tickets?           */
#endif
#if defined(PTLS_SSL_FALLBACK_SCSV) && defined(PTLS_SSL_CLI_C)
    unsigned int fallback : 1;      /*!< is this a fallback?                */
#endif
#if defined(PTLS_SSL_SRV_C)
    unsigned int cert_req_ca_list : 1;  /*!< enable sending CA list in
                                          Certificate Request messages?     */
#endif
};


struct ptls_ssl_context
{
    const ptls_ssl_config *conf; /*!< configuration information          */

    /*
     * Miscellaneous
     */
    int state;                  /*!< SSL handshake: current state     */
#if defined(PTLS_SSL_RENEGOTIATION)
    int renego_status;          /*!< Initial, in progress, pending?   */
    int renego_records_seen;    /*!< Records since renego request, or with DTLS,
                                  number of retransmissions of request if
                                  renego_max_records is < 0           */
#endif /* PTLS_SSL_RENEGOTIATION */

    int major_ver;              /*!< equal to  PTLS_SSL_MAJOR_VERSION_3    */
    int minor_ver;              /*!< either 0 (SSL3) or 1 (TLS1.0)    */

#if defined(PTLS_SSL_DTLS_BADMAC_LIMIT)
    unsigned badmac_seen;       /*!< records with a bad MAC received    */
#endif /* PTLS_SSL_DTLS_BADMAC_LIMIT */

    ptls_ssl_send_t *f_send; /*!< Callback for network send */
    ptls_ssl_recv_t *f_recv; /*!< Callback for network receive */
    ptls_ssl_recv_timeout_t *f_recv_timeout;
                                /*!< Callback for network receive with timeout */

    void *p_bio;                /*!< context for I/O operations   */

    /*
     * Session layer
     */
    ptls_ssl_session *session_in;            /*!<  current session data (in)   */
    ptls_ssl_session *session_out;           /*!<  current session data (out)  */
    ptls_ssl_session *session;               /*!<  negotiated session data     */
    ptls_ssl_session *session_negotiate;     /*!<  session data in negotiation */

    ptls_ssl_handshake_params *handshake;    /*!<  params required only during
                                              the handshake process        */

    /*
     * Record layer transformations
     */
    ptls_ssl_transform *transform_in;        /*!<  current transform params (in)   */
    ptls_ssl_transform *transform_out;       /*!<  current transform params (in)   */
    ptls_ssl_transform *transform;           /*!<  negotiated transform params     */
    ptls_ssl_transform *transform_negotiate; /*!<  transform params in negotiation */

    /*
     * Timers
     */
    void *p_timer;              /*!< context for the timer callbacks */

    ptls_ssl_set_timer_t *f_set_timer;       /*!< set timer callback */
    ptls_ssl_get_timer_t *f_get_timer;       /*!< get timer callback */

    /*
     * Record layer (incoming data)
     */
    unsigned char *in_buf;      /*!< input buffer                     */
    unsigned char *in_ctr;      /*!< 64-bit incoming message counter
                                     TLS: maintained by us
                                     DTLS: read from peer             */
    unsigned char *in_hdr;      /*!< start of record header           */
    unsigned char *in_len;      /*!< two-bytes message length field   */
    unsigned char *in_iv;       /*!< ivlen-byte IV                    */
    unsigned char *in_msg;      /*!< message contents (in_iv+ivlen)   */
    unsigned char *in_offt;     /*!< read offset in application data  */

    int in_msgtype;             /*!< record header: message type      */
    size_t in_msglen;           /*!< record header: message length    */
    size_t in_left;             /*!< amount of data read so far       */
#if defined(PTLS_SSL_PROTO_DTLS)
    uint16_t in_epoch;          /*!< DTLS epoch for incoming records  */
    size_t next_record_offset;  /*!< offset of the next record in datagram
                                     (equal to in_left if none)       */
#endif /* PTLS_SSL_PROTO_DTLS */
#if defined(PTLS_SSL_DTLS_ANTI_REPLAY)
    uint64_t in_window_top;     /*!< last validated record seq_num    */
    uint64_t in_window;         /*!< bitmask for replay detection     */
#endif /* PTLS_SSL_DTLS_ANTI_REPLAY */

    size_t in_hslen;            /*!< current handshake message length,
                                     including the handshake header   */
    int nb_zero;                /*!< # of 0-length encrypted messages */

    int keep_current_message;   /*!< drop or reuse current message
                                     on next call to record layer? */

#if defined(PTLS_SSL_PROTO_DTLS)
    uint8_t disable_datagram_packing;  /*!< Disable packing multiple records
                                        *   within a single datagram.  */
#endif /* PTLS_SSL_PROTO_DTLS */

    /*
     * Record layer (outgoing data)
     */
    unsigned char *out_buf;     /*!< output buffer                    */
    unsigned char *out_ctr;     /*!< 64-bit outgoing message counter  */
    unsigned char *out_hdr;     /*!< start of record header           */
    unsigned char *out_len;     /*!< two-bytes message length field   */
    unsigned char *out_iv;      /*!< ivlen-byte IV                    */
    unsigned char *out_msg;     /*!< message contents (out_iv+ivlen)  */

    int out_msgtype;            /*!< record header: message type      */
    size_t out_msglen;          /*!< record header: message length    */
    size_t out_left;            /*!< amount of data not yet written   */

    unsigned char cur_out_ctr[8]; /*!<  Outgoing record sequence  number. */

#if defined(PTLS_SSL_PROTO_DTLS)
    uint16_t mtu;               /*!< path mtu, used to fragment outgoing messages */
#endif /* PTLS_SSL_PROTO_DTLS */

#if defined(PTLS_ZLIB_SUPPORT)
    unsigned char *compress_buf;        /*!<  zlib data buffer        */
#endif /* PTLS_ZLIB_SUPPORT */
#if defined(PTLS_SSL_CBC_RECORD_SPLITTING)
    signed char split_done;     /*!< current record already splitted? */
#endif /* PTLS_SSL_CBC_RECORD_SPLITTING */

    /*
     * PKI layer
     */
    int client_auth;                    /*!<  flag for client auth.   */

    /*
     * User settings
     */
#if defined(PTLS_X509_CRT_PARSE_C)
    char *hostname;             /*!< expected peer CN for verification
                                     (and SNI if available)                 */
#endif /* PTLS_X509_CRT_PARSE_C */

#if defined(PTLS_SSL_ALPN)
    const char *alpn_chosen;    /*!<  negotiated protocol                   */
#endif /* PTLS_SSL_ALPN */

    /*
     * Information for DTLS hello verify
     */
#if defined(PTLS_SSL_DTLS_HELLO_VERIFY) && defined(PTLS_SSL_SRV_C)
    unsigned char  *cli_id;         /*!<  transport-level ID of the client  */
    size_t          cli_id_len;     /*!<  length of cli_id                  */
#endif /* PTLS_SSL_DTLS_HELLO_VERIFY && PTLS_SSL_SRV_C */

    /*
     * Secure renegotiation
     */
    /* needed to know when to send extension on server */
    int secure_renegotiation;           /*!<  does peer support legacy or
                                              secure renegotiation           */
#if defined(PTLS_SSL_RENEGOTIATION)
    size_t verify_data_len;             /*!<  length of verify data stored   */
    char own_verify_data[PTLS_SSL_VERIFY_DATA_MAX_LEN]; /*!<  previous handshake verify data */
    char peer_verify_data[PTLS_SSL_VERIFY_DATA_MAX_LEN]; /*!<  previous handshake verify data */
#endif /* PTLS_SSL_RENEGOTIATION */
};

#if defined(PTLS_SSL_HW_RECORD_ACCEL)

#define PTLS_SSL_CHANNEL_OUTBOUND    0
#define PTLS_SSL_CHANNEL_INBOUND     1

extern int (*ptls_ssl_hw_record_init)(ptls_ssl_context *ssl,
                const unsigned char *key_enc, const unsigned char *key_dec,
                size_t keylen,
                const unsigned char *iv_enc,  const unsigned char *iv_dec,
                size_t ivlen,
                const unsigned char *mac_enc, const unsigned char *mac_dec,
                size_t maclen);
extern int (*ptls_ssl_hw_record_activate)(ptls_ssl_context *ssl, int direction);
extern int (*ptls_ssl_hw_record_reset)(ptls_ssl_context *ssl);
extern int (*ptls_ssl_hw_record_write)(ptls_ssl_context *ssl);
extern int (*ptls_ssl_hw_record_read)(ptls_ssl_context *ssl);
extern int (*ptls_ssl_hw_record_finish)(ptls_ssl_context *ssl);
#endif /* PTLS_SSL_HW_RECORD_ACCEL */

/**
 * \brief               Return the name of the ciphersuite associated with the
 *                      given ID
 *
 * \param ciphersuite_id SSL ciphersuite ID
 *
 * \return              a string containing the ciphersuite name
 */
const char *ptls_ssl_get_ciphersuite_name( const int ciphersuite_id );

/**
 * \brief               Return the ID of the ciphersuite associated with the
 *                      given name
 *
 * \param ciphersuite_name SSL ciphersuite name
 *
 * \return              the ID with the ciphersuite or 0 if not found
 */
int ptls_ssl_get_ciphersuite_id( const char *ciphersuite_name );

/**
 * \brief          Initialize an SSL context
 *                 Just makes the context ready for ptls_ssl_setup() or
 *                 ptls_ssl_free()
 *
 * \param ssl      SSL context
 */
void ptls_ssl_init( ptls_ssl_context *ssl );

/**
 * \brief          Set up an SSL context for use
 *
 * \note           No copy of the configuration context is made, it can be
 *                 shared by many ptls_ssl_context structures.
 *
 * \warning        The conf structure will be accessed during the session.
 *                 It must not be modified or freed as long as the session
 *                 is active.
 *
 * \warning        This function must be called exactly once per context.
 *                 Calling ptls_ssl_setup again is not supported, even
 *                 if no session is active.
 *
 * \param ssl      SSL context
 * \param conf     SSL configuration to use
 *
 * \return         0 if successful, or PTLS_ERR_SSL_ALLOC_FAILED if
 *                 memory allocation failed
 */
int ptls_ssl_setup( ptls_ssl_context *ssl,
                       const ptls_ssl_config *conf );

/**
 * \brief          Reset an already initialized SSL context for re-use
 *                 while retaining application-set variables, function
 *                 pointers and data.
 *
 * \param ssl      SSL context
 * \return         0 if successful, or PTLS_ERR_SSL_ALLOC_FAILED,
                   PTLS_ERR_SSL_HW_ACCEL_FAILED or
 *                 PTLS_ERR_SSL_COMPRESSION_FAILED
 */
int ptls_ssl_session_reset( ptls_ssl_context *ssl );

/**
 * \brief          Set the current endpoint type
 *
 * \param conf     SSL configuration
 * \param endpoint must be PTLS_SSL_IS_CLIENT or PTLS_SSL_IS_SERVER
 */
void ptls_ssl_conf_endpoint( ptls_ssl_config *conf, int endpoint );

/**
 * \brief           Set the transport type (TLS or DTLS).
 *                  Default: TLS
 *
 * \note            For DTLS, you must either provide a recv callback that
 *                  doesn't block, or one that handles timeouts, see
 *                  \c ptls_ssl_set_bio(). You also need to provide timer
 *                  callbacks with \c ptls_ssl_set_timer_cb().
 *
 * \param conf      SSL configuration
 * \param transport transport type:
 *                  PTLS_SSL_TRANSPORT_STREAM for TLS,
 *                  PTLS_SSL_TRANSPORT_DATAGRAM for DTLS.
 */
void ptls_ssl_conf_transport( ptls_ssl_config *conf, int transport );

/**
 * \brief          Set the certificate verification mode
 *                 Default: NONE on server, REQUIRED on client
 *
 * \param conf     SSL configuration
 * \param authmode can be:
 *
 *  PTLS_SSL_VERIFY_NONE:      peer certificate is not checked
 *                        (default on server)
 *                        (insecure on client)
 *
 *  PTLS_SSL_VERIFY_OPTIONAL:  peer certificate is checked, however the
 *                        handshake continues even if verification failed;
 *                        ptls_ssl_get_verify_result() can be called after the
 *                        handshake is complete.
 *
 *  PTLS_SSL_VERIFY_REQUIRED:  peer *must* present a valid certificate,
 *                        handshake is aborted if verification failed.
 *                        (default on client)
 *
 * \note On client, PTLS_SSL_VERIFY_REQUIRED is the recommended mode.
 * With PTLS_SSL_VERIFY_OPTIONAL, the user needs to call ptls_ssl_get_verify_result() at
 * the right time(s), which may not be obvious, while REQUIRED always perform
 * the verification as soon as possible. For example, REQUIRED was protecting
 * against the "triple handshake" attack even before it was found.
 */
void ptls_ssl_conf_authmode( ptls_ssl_config *conf, int authmode );

void ptls_ssl_conf_authtype( ptls_ssl_config *conf, int authtype );

#if defined(PTLS_X509_CRT_PARSE_C)
/**
 * \brief          Set the verification callback (Optional).
 *
 *                 If set, the verify callback is called for each
 *                 certificate in the chain. For implementation
 *                 information, please see \c ptls_x509_crt_verify()
 *
 * \param conf     SSL configuration
 * \param f_vrfy   verification function
 * \param p_vrfy   verification parameter
 */
void ptls_ssl_conf_verify( ptls_ssl_config *conf,
                     int (*f_vrfy)(void *, ptls_x509_crt *, int, uint32_t *),
                     void *p_vrfy );
#endif /* PTLS_X509_CRT_PARSE_C */

/**
 * \brief          Set the random number generator callback
 *
 * \param conf     SSL configuration
 * \param f_rng    RNG function
 * \param p_rng    RNG parameter
 */
void ptls_ssl_conf_rng( ptls_ssl_config *conf,
                  int (*f_rng)(void *, unsigned char *, size_t),
                  void *p_rng );

/**
 * \brief          Set the debug callback
 *
 *                 The callback has the following argument:
 *                 void *           opaque context for the callback
 *                 int              debug level
 *                 const char *     file name
 *                 int              line number
 *                 const char *     message
 *
 * \param conf     SSL configuration
 * \param f_dbg    debug function
 * \param p_dbg    debug parameter
 */
void ptls_ssl_conf_dbg( ptls_ssl_config *conf,
                  void (*f_dbg)(void *, int, const char *, int, const char *),
                  void  *p_dbg );

/**
 * \brief          Set the underlying BIO callbacks for write, read and
 *                 read-with-timeout.
 *
 * \param ssl      SSL context
 * \param p_bio    parameter (context) shared by BIO callbacks
 * \param f_send   write callback
 * \param f_recv   read callback
 * \param f_recv_timeout blocking read callback with timeout.
 *
 * \note           One of f_recv or f_recv_timeout can be NULL, in which case
 *                 the other is used. If both are non-NULL, f_recv_timeout is
 *                 used and f_recv is ignored (as if it were NULL).
 *
 * \note           The two most common use cases are:
 *                 - non-blocking I/O, f_recv != NULL, f_recv_timeout == NULL
 *                 - blocking I/O, f_recv == NULL, f_recv_timout != NULL
 *
 * \note           For DTLS, you need to provide either a non-NULL
 *                 f_recv_timeout callback, or a f_recv that doesn't block.
 *
 * \note           See the documentations of \c ptls_ssl_sent_t,
 *                 \c ptls_ssl_recv_t and \c ptls_ssl_recv_timeout_t for
 *                 the conventions those callbacks must follow.
 *
 * \note           On some platforms, net_sockets.c provides
 *                 \c ptls_net_send(), \c ptls_net_recv() and
 *                 \c ptls_net_recv_timeout() that are suitable to be used
 *                 here.
 */
void ptls_ssl_set_bio( ptls_ssl_context *ssl,
                          void *p_bio,
                          ptls_ssl_send_t *f_send,
                          ptls_ssl_recv_t *f_recv,
                          ptls_ssl_recv_timeout_t *f_recv_timeout );

#if defined(PTLS_SSL_PROTO_DTLS)
/**
 * \brief          Set the Maximum Tranport Unit (MTU).
 *                 Special value: 0 means unset (no limit).
 *                 This represents the maximum size of a datagram payload
 *                 handled by the transport layer (usually UDP) as determined
 *                 by the network link and stack. In practice, this controls
 *                 the maximum size datagram the DTLS layer will pass to the
 *                 \c f_send() callback set using \c ptls_ssl_set_bio().
 *
 * \note           The limit on datagram size is converted to a limit on
 *                 record payload by subtracting the current overhead of
 *                 encapsulation and encryption/authentication if any.
 *
 * \note           This can be called at any point during the connection, for
 *                 example when a Path Maximum Transfer Unit (PMTU)
 *                 estimate becomes available from other sources,
 *                 such as lower (or higher) protocol layers.
 *
 * \note           This setting only controls the size of the packets we send,
 *                 and does not restrict the size of the datagrams we're
 *                 willing to receive. Client-side, you can request the
 *                 server to use smaller records with \c
 *                 ptls_ssl_conf_max_frag_len().
 *
 * \note           If both a MTU and a maximum fragment length have been
 *                 configured (or negotiated with the peer), the resulting
 *                 lower limit on record payload (see first note) is used.
 *
 * \note           This can only be used to decrease the maximum size
 *                 of datagrams (hence records, see first note) sent. It
 *                 cannot be used to increase the maximum size of records over
 *                 the limit set by #PTLS_SSL_OUT_CONTENT_LEN.
 *
 * \note           Values lower than the current record layer expansion will
 *                 result in an error when trying to send data.
 *
 * \note           Using record compression together with a non-zero MTU value
 *                 will result in an error when trying to send data.
 *
 * \param ssl      SSL context
 * \param mtu      Value of the path MTU in bytes
 */
void ptls_ssl_set_mtu( ptls_ssl_context *ssl, uint16_t mtu );
#endif /* PTLS_SSL_PROTO_DTLS */

/**
 * \brief          Set the timeout period for ptls_ssl_read()
 *                 (Default: no timeout.)
 *
 * \param conf     SSL configuration context
 * \param timeout  Timeout value in milliseconds.
 *                 Use 0 for no timeout (default).
 *
 * \note           With blocking I/O, this will only work if a non-NULL
 *                 \c f_recv_timeout was set with \c ptls_ssl_set_bio().
 *                 With non-blocking I/O, this will only work if timer
 *                 callbacks were set with \c ptls_ssl_set_timer_cb().
 *
 * \note           With non-blocking I/O, you may also skip this function
 *                 altogether and handle timeouts at the application layer.
 */
void ptls_ssl_conf_read_timeout( ptls_ssl_config *conf, uint32_t timeout );

/**
 * \brief          Set the timer callbacks (Mandatory for DTLS.)
 *
 * \param ssl      SSL context
 * \param p_timer  parameter (context) shared by timer callbacks
 * \param f_set_timer   set timer callback
 * \param f_get_timer   get timer callback. Must return:
 *
 * \note           See the documentation of \c ptls_ssl_set_timer_t and
 *                 \c ptls_ssl_get_timer_t for the conventions this pair of
 *                 callbacks must follow.
 *
 * \note           On some platforms, timing.c provides
 *                 \c ptls_timing_set_delay() and
 *                 \c ptls_timing_get_delay() that are suitable for using
 *                 here, except if using an event-driven style.
 *
 * \note           See also the "DTLS tutorial" article in our knowledge base.
 *                 https://tls.penta.org/kb/how-to/dtls-tutorial
 */
void ptls_ssl_set_timer_cb( ptls_ssl_context *ssl,
                               void *p_timer,
                               ptls_ssl_set_timer_t *f_set_timer,
                               ptls_ssl_get_timer_t *f_get_timer );

/**
 * \brief           Callback type: generate and write session ticket
 *
 * \note            This describes what a callback implementation should do.
 *                  This callback should generate an encrypted and
 *                  authenticated ticket for the session and write it to the
 *                  output buffer. Here, ticket means the opaque ticket part
 *                  of the NewSessionTicket structure of RFC 5077.
 *
 * \param p_ticket  Context for the callback
 * \param session   SSL session to be written in the ticket
 * \param start     Start of the output buffer
 * \param end       End of the output buffer
 * \param tlen      On exit, holds the length written
 * \param lifetime  On exit, holds the lifetime of the ticket in seconds
 *
 * \return          0 if successful, or
 *                  a specific PTLS_ERR_XXX code.
 */
typedef int ptls_ssl_ticket_write_t( void *p_ticket,
                                        const ptls_ssl_session *session,
                                        unsigned char *start,
                                        const unsigned char *end,
                                        size_t *tlen,
                                        uint32_t *lifetime );

#if defined(PTLS_SSL_EXPORT_KEYS)
/**
 * \brief           Callback type: Export key block and master secret
 *
 * \note            This is required for certain uses of TLS, e.g. EAP-TLS
 *                  (RFC 5216) and Thread. The key pointers are ephemeral and
 *                  therefore must not be stored. The master secret and keys
 *                  should not be used directly except as an input to a key
 *                  derivation function.
 *
 * \param p_expkey  Context for the callback
 * \param ms        Pointer to master secret (fixed length: 48 bytes)
 * \param kb        Pointer to key block, see RFC 5246 section 6.3
 *                  (variable length: 2 * maclen + 2 * keylen + 2 * ivlen).
 * \param maclen    MAC length
 * \param keylen    Key length
 * \param ivlen     IV length
 *
 * \return          0 if successful, or
 *                  a specific PTLS_ERR_XXX code.
 */
typedef int ptls_ssl_export_keys_t( void *p_expkey,
                                const unsigned char *ms,
                                const unsigned char *kb,
                                size_t maclen,
                                size_t keylen,
                                size_t ivlen );
#endif /* PTLS_SSL_EXPORT_KEYS */

/**
 * \brief           Callback type: parse and load session ticket
 *
 * \note            This describes what a callback implementation should do.
 *                  This callback should parse a session ticket as generated
 *                  by the corresponding ptls_ssl_ticket_write_t function,
 *                  and, if the ticket is authentic and valid, load the
 *                  session.
 *
 * \note            The implementation is allowed to modify the first len
 *                  bytes of the input buffer, eg to use it as a temporary
 *                  area for the decrypted ticket contents.
 *
 * \param p_ticket  Context for the callback
 * \param session   SSL session to be loaded
 * \param buf       Start of the buffer containing the ticket
 * \param len       Length of the ticket.
 *
 * \return          0 if successful, or
 *                  PTLS_ERR_SSL_INVALID_MAC if not authentic, or
 *                  PTLS_ERR_SSL_SESSION_TICKET_EXPIRED if expired, or
 *                  any other non-zero code for other failures.
 */
typedef int ptls_ssl_ticket_parse_t( void *p_ticket,
                                        ptls_ssl_session *session,
                                        unsigned char *buf,
                                        size_t len );

#if defined(PTLS_SSL_SESSION_TICKETS) && defined(PTLS_SSL_SRV_C)
/**
 * \brief           Configure SSL session ticket callbacks (server only).
 *                  (Default: none.)
 *
 * \note            On server, session tickets are enabled by providing
 *                  non-NULL callbacks.
 *
 * \note            On client, use \c ptls_ssl_conf_session_tickets().
 *
 * \param conf      SSL configuration context
 * \param f_ticket_write    Callback for writing a ticket
 * \param f_ticket_parse    Callback for parsing a ticket
 * \param p_ticket          Context shared by the two callbacks
 */
void ptls_ssl_conf_session_tickets_cb( ptls_ssl_config *conf,
        ptls_ssl_ticket_write_t *f_ticket_write,
        ptls_ssl_ticket_parse_t *f_ticket_parse,
        void *p_ticket );
#endif /* PTLS_SSL_SESSION_TICKETS && PTLS_SSL_SRV_C */

#if defined(PTLS_SSL_EXPORT_KEYS)
/**
 * \brief           Configure key export callback.
 *                  (Default: none.)
 *
 * \note            See \c ptls_ssl_export_keys_t.
 *
 * \param conf      SSL configuration context
 * \param f_export_keys     Callback for exporting keys
 * \param p_export_keys     Context for the callback
 */
void ptls_ssl_conf_export_keys_cb( ptls_ssl_config *conf,
        ptls_ssl_export_keys_t *f_export_keys,
        void *p_export_keys );
#endif /* PTLS_SSL_EXPORT_KEYS */

#if defined(PTLS_SSL_ASYNC_PRIVATE)
/**
 * \brief           Configure asynchronous private key operation callbacks.
 *
 * \param conf              SSL configuration context
 * \param f_async_sign      Callback to start a signature operation. See
 *                          the description of ::ptls_ssl_async_sign_t
 *                          for more information. This may be \c NULL if the
 *                          external processor does not support any signature
 *                          operation; in this case the private key object
 *                          associated with the certificate will be used.
 * \param f_async_decrypt   Callback to start a decryption operation. See
 *                          the description of ::ptls_ssl_async_decrypt_t
 *                          for more information. This may be \c NULL if the
 *                          external processor does not support any decryption
 *                          operation; in this case the private key object
 *                          associated with the certificate will be used.
 * \param f_async_resume    Callback to resume an asynchronous operation. See
 *                          the description of ::ptls_ssl_async_resume_t
 *                          for more information. This may not be \c NULL unless
 *                          \p f_async_sign and \p f_async_decrypt are both
 *                          \c NULL.
 * \param f_async_cancel    Callback to cancel an asynchronous operation. See
 *                          the description of ::ptls_ssl_async_cancel_t
 *                          for more information. This may be \c NULL if
 *                          no cleanup is needed.
 * \param config_data       A pointer to configuration data which can be
 *                          retrieved with
 *                          ptls_ssl_conf_get_async_config_data(). The
 *                          library stores this value without dereferencing it.
 */
void ptls_ssl_conf_async_private_cb( ptls_ssl_config *conf,
                                        ptls_ssl_async_sign_t *f_async_sign,
                                        ptls_ssl_async_decrypt_t *f_async_decrypt,
                                        ptls_ssl_async_resume_t *f_async_resume,
                                        ptls_ssl_async_cancel_t *f_async_cancel,
                                        void *config_data );

/**
 * \brief           Retrieve the configuration data set by
 *                  ptls_ssl_conf_async_private_cb().
 *
 * \param conf      SSL configuration context
 * \return          The configuration data set by
 *                  ptls_ssl_conf_async_private_cb().
 */
void *ptls_ssl_conf_get_async_config_data( const ptls_ssl_config *conf );

/**
 * \brief           Retrieve the asynchronous operation user context.
 *
 * \note            This function may only be called while a handshake
 *                  is in progress.
 *
 * \param ssl       The SSL context to access.
 *
 * \return          The asynchronous operation user context that was last
 *                  set during the current handshake. If
 *                  ptls_ssl_set_async_operation_data() has not yet been
 *                  called during the current handshake, this function returns
 *                  \c NULL.
 */
void *ptls_ssl_get_async_operation_data( const ptls_ssl_context *ssl );

/**
 * \brief           Retrieve the asynchronous operation user context.
 *
 * \note            This function may only be called while a handshake
 *                  is in progress.
 *
 * \param ssl       The SSL context to access.
 * \param ctx       The new value of the asynchronous operation user context.
 *                  Call ptls_ssl_get_async_operation_data() later during the
 *                  same handshake to retrieve this value.
 */
void ptls_ssl_set_async_operation_data( ptls_ssl_context *ssl,
                                 void *ctx );
#endif /* PTLS_SSL_ASYNC_PRIVATE */

/**
 * \brief          Callback type: generate a cookie
 *
 * \param ctx      Context for the callback
 * \param p        Buffer to write to,
 *                 must be updated to point right after the cookie
 * \param end      Pointer to one past the end of the output buffer
 * \param info     Client ID info that was passed to
 *                 \c ptls_ssl_set_client_transport_id()
 * \param ilen     Length of info in bytes
 *
 * \return         The callback must return 0 on success,
 *                 or a negative error code.
 */
typedef int ptls_ssl_cookie_write_t( void *ctx,
                                unsigned char **p, unsigned char *end,
                                const unsigned char *info, size_t ilen );

/**
 * \brief          Callback type: verify a cookie
 *
 * \param ctx      Context for the callback
 * \param cookie   Cookie to verify
 * \param clen     Length of cookie
 * \param info     Client ID info that was passed to
 *                 \c ptls_ssl_set_client_transport_id()
 * \param ilen     Length of info in bytes
 *
 * \return         The callback must return 0 if cookie is valid,
 *                 or a negative error code.
 */
typedef int ptls_ssl_cookie_check_t( void *ctx,
                                const unsigned char *cookie, size_t clen,
                                const unsigned char *info, size_t ilen );

#if defined(PTLS_SSL_DTLS_HELLO_VERIFY) && defined(PTLS_SSL_SRV_C)
/**
 * \brief           Register callbacks for DTLS cookies
 *                  (Server only. DTLS only.)
 *
 *                  Default: dummy callbacks that fail, in order to force you to
 *                  register working callbacks (and initialize their context).
 *
 *                  To disable HelloVerifyRequest, register NULL callbacks.
 *
 * \warning         Disabling hello verification allows your server to be used
 *                  for amplification in DoS attacks against other hosts.
 *                  Only disable if you known this can't happen in your
 *                  particular environment.
 *
 * \note            See comments on \c ptls_ssl_handshake() about handling
 *                  the PTLS_ERR_SSL_HELLO_VERIFY_REQUIRED that is expected
 *                  on the first handshake attempt when this is enabled.
 *
 * \note            This is also necessary to handle client reconnection from
 *                  the same port as described in RFC 6347 section 4.2.8 (only
 *                  the variant with cookies is supported currently). See
 *                  comments on \c ptls_ssl_read() for details.
 *
 * \param conf              SSL configuration
 * \param f_cookie_write    Cookie write callback
 * \param f_cookie_check    Cookie check callback
 * \param p_cookie          Context for both callbacks
 */
void ptls_ssl_conf_dtls_cookies( ptls_ssl_config *conf,
                           ptls_ssl_cookie_write_t *f_cookie_write,
                           ptls_ssl_cookie_check_t *f_cookie_check,
                           void *p_cookie );

/**
 * \brief          Set client's transport-level identification info.
 *                 (Server only. DTLS only.)
 *
 *                 This is usually the IP address (and port), but could be
 *                 anything identify the client depending on the underlying
 *                 network stack. Used for HelloVerifyRequest with DTLS.
 *                 This is *not* used to route the actual packets.
 *
 * \param ssl      SSL context
 * \param info     Transport-level info identifying the client (eg IP + port)
 * \param ilen     Length of info in bytes
 *
 * \note           An internal copy is made, so the info buffer can be reused.
 *
 * \return         0 on success,
 *                 PTLS_ERR_SSL_BAD_INPUT_DATA if used on client,
 *                 PTLS_ERR_SSL_ALLOC_FAILED if out of memory.
 */
int ptls_ssl_set_client_transport_id( ptls_ssl_context *ssl,
                                 const unsigned char *info,
                                 size_t ilen );

#endif /* PTLS_SSL_DTLS_HELLO_VERIFY && PTLS_SSL_SRV_C */

#if defined(PTLS_SSL_DTLS_ANTI_REPLAY)
/**
 * \brief          Enable or disable anti-replay protection for DTLS.
 *                 (DTLS only, no effect on TLS.)
 *                 Default: enabled.
 *
 * \param conf     SSL configuration
 * \param mode     PTLS_SSL_ANTI_REPLAY_ENABLED or PTLS_SSL_ANTI_REPLAY_DISABLED.
 *
 * \warning        Disabling this is a security risk unless the application
 *                 protocol handles duplicated packets in a safe way. You
 *                 should not disable this without careful consideration.
 *                 However, if your application already detects duplicated
 *                 packets and needs information about them to adjust its
 *                 transmission strategy, then you'll want to disable this.
 */
void ptls_ssl_conf_dtls_anti_replay( ptls_ssl_config *conf, char mode );
#endif /* PTLS_SSL_DTLS_ANTI_REPLAY */

#if defined(PTLS_SSL_DTLS_BADMAC_LIMIT)
/**
 * \brief          Set a limit on the number of records with a bad MAC
 *                 before terminating the connection.
 *                 (DTLS only, no effect on TLS.)
 *                 Default: 0 (disabled).
 *
 * \param conf     SSL configuration
 * \param limit    Limit, or 0 to disable.
 *
 * \note           If the limit is N, then the connection is terminated when
 *                 the Nth non-authentic record is seen.
 *
 * \note           Records with an invalid header are not counted, only the
 *                 ones going through the authentication-decryption phase.
 *
 * \note           This is a security trade-off related to the fact that it's
 *                 often relatively easy for an active attacker ot inject UDP
 *                 datagrams. On one hand, setting a low limit here makes it
 *                 easier for such an attacker to forcibly terminated a
 *                 connection. On the other hand, a high limit or no limit
 *                 might make us waste resources checking authentication on
 *                 many bogus packets.
 */
void ptls_ssl_conf_dtls_badmac_limit( ptls_ssl_config *conf, unsigned limit );
#endif /* PTLS_SSL_DTLS_BADMAC_LIMIT */

#if defined(PTLS_SSL_PROTO_DTLS)

/**
 * \brief          Allow or disallow packing of multiple handshake records
 *                 within a single datagram.
 *
 * \param ssl           The SSL context to configure.
 * \param allow_packing This determines whether datagram packing may
 *                      be used or not. A value of \c 0 means that every
 *                      record will be sent in a separate datagram; a
 *                      value of \c 1 means that, if space permits,
 *                      multiple handshake messages (including CCS) belonging to
 *                      a single flight may be packed within a single datagram.
 *
 * \note           This is enabled by default and should only be disabled
 *                 for test purposes, or if datagram packing causes
 *                 interoperability issues with peers that don't support it.
 *
 * \note           Allowing datagram packing reduces the network load since
 *                 there's less overhead if multiple messages share the same
 *                 datagram. Also, it increases the handshake efficiency
 *                 since messages belonging to a single datagram will not
 *                 be reordered in transit, and so future message buffering
 *                 or flight retransmission (if no buffering is used) as
 *                 means to deal with reordering are needed less frequently.
 *
 * \note           Application records are not affected by this option and
 *                 are currently always sent in separate datagrams.
 *
 */
void ptls_ssl_set_datagram_packing( ptls_ssl_context *ssl,
                                       unsigned allow_packing );

/**
 * \brief          Set retransmit timeout values for the DTLS handshake.
 *                 (DTLS only, no effect on TLS.)
 *
 * \param conf     SSL configuration
 * \param min      Initial timeout value in milliseconds.
 *                 Default: 1000 (1 second).
 * \param max      Maximum timeout value in milliseconds.
 *                 Default: 60000 (60 seconds).
 *
 * \note           Default values are from RFC 6347 section 4.2.4.1.
 *
 * \note           The 'min' value should typically be slightly above the
 *                 expected round-trip time to your peer, plus whatever time
 *                 it takes for the peer to process the message. For example,
 *                 if your RTT is about 600ms and you peer needs up to 1s to
 *                 do the cryptographic operations in the handshake, then you
 *                 should set 'min' slightly above 1600. Lower values of 'min'
 *                 might cause spurious resends which waste network resources,
 *                 while larger value of 'min' will increase overall latency
 *                 on unreliable network links.
 *
 * \note           The more unreliable your network connection is, the larger
 *                 your max / min ratio needs to be in order to achieve
 *                 reliable handshakes.
 *
 * \note           Messages are retransmitted up to log2(ceil(max/min)) times.
 *                 For example, if min = 1s and max = 5s, the retransmit plan
 *                 goes: send ... 1s -> resend ... 2s -> resend ... 4s ->
 *                 resend ... 5s -> give up and return a timeout error.
 */
void ptls_ssl_conf_handshake_timeout( ptls_ssl_config *conf, uint32_t min, uint32_t max );
#endif /* PTLS_SSL_PROTO_DTLS */

#if defined(PTLS_SSL_SRV_C)
/**
 * \brief          Set the session cache callbacks (server-side only)
 *                 If not set, no session resuming is done (except if session
 *                 tickets are enabled too).
 *
 *                 The session cache has the responsibility to check for stale
 *                 entries based on timeout. See RFC 5246 for recommendations.
 *
 *                 Warning: session.peer_cert is cleared by the SSL/TLS layer on
 *                 connection shutdown, so do not cache the pointer! Either set
 *                 it to NULL or make a full copy of the certificate.
 *
 *                 The get callback is called once during the initial handshake
 *                 to enable session resuming. The get function has the
 *                 following parameters: (void *parameter, ptls_ssl_session *session)
 *                 If a valid entry is found, it should fill the master of
 *                 the session object with the cached values and return 0,
 *                 return 1 otherwise. Optionally peer_cert can be set as well
 *                 if it is properly present in cache entry.
 *
 *                 The set callback is called once during the initial handshake
 *                 to enable session resuming after the entire handshake has
 *                 been finished. The set function has the following parameters:
 *                 (void *parameter, const ptls_ssl_session *session). The function
 *                 should create a cache entry for future retrieval based on
 *                 the data in the session structure and should keep in mind
 *                 that the ptls_ssl_session object presented (and all its referenced
 *                 data) is cleared by the SSL/TLS layer when the connection is
 *                 terminated. It is recommended to add metadata to determine if
 *                 an entry is still valid in the future. Return 0 if
 *                 successfully cached, return 1 otherwise.
 *
 * \param conf           SSL configuration
 * \param p_cache        parmater (context) for both callbacks
 * \param f_get_cache    session get callback
 * \param f_set_cache    session set callback
 */
void ptls_ssl_conf_session_cache( ptls_ssl_config *conf,
        void *p_cache,
        int (*f_get_cache)(void *, ptls_ssl_session *),
        int (*f_set_cache)(void *, const ptls_ssl_session *) );
#endif /* PTLS_SSL_SRV_C */

#if defined(PTLS_SSL_CLI_C)
/**
 * \brief          Request resumption of session (client-side only)
 *                 Session data is copied from presented session structure.
 *
 * \param ssl      SSL context
 * \param session  session context
 *
 * \return         0 if successful,
 *                 PTLS_ERR_SSL_ALLOC_FAILED if memory allocation failed,
 *                 PTLS_ERR_SSL_BAD_INPUT_DATA if used server-side or
 *                 arguments are otherwise invalid
 *
 * \sa             ptls_ssl_get_session()
 */
int ptls_ssl_set_session( ptls_ssl_context *ssl, const ptls_ssl_session *session );
#endif /* PTLS_SSL_CLI_C */

/**
 * \brief               Set the list of allowed ciphersuites and the preference
 *                      order. First in the list has the highest preference.
 *                      (Overrides all version-specific lists)
 *
 *                      The ciphersuites array is not copied, and must remain
 *                      valid for the lifetime of the ssl_config.
 *
 *                      Note: The server uses its own preferences
 *                      over the preference of the client unless
 *                      PTLS_SSL_SRV_RESPECT_CLIENT_PREFERENCE is defined!
 *
 * \param conf          SSL configuration
 * \param ciphersuites  0-terminated list of allowed ciphersuites
 */
void ptls_ssl_conf_ciphersuites( ptls_ssl_config *conf,
                                   const int *ciphersuites );

/**
 * \brief               Set the list of allowed ciphersuites and the
 *                      preference order for a specific version of the protocol.
 *                      (Only useful on the server side)
 *
 *                      The ciphersuites array is not copied, and must remain
 *                      valid for the lifetime of the ssl_config.
 *
 * \param conf          SSL configuration
 * \param ciphersuites  0-terminated list of allowed ciphersuites
 * \param major         Major version number (only PTLS_SSL_MAJOR_VERSION_3
 *                      supported)
 * \param minor         Minor version number (PTLS_SSL_MINOR_VERSION_0,
 *                      PTLS_SSL_MINOR_VERSION_1 and PTLS_SSL_MINOR_VERSION_2,
 *                      PTLS_SSL_MINOR_VERSION_3 supported)
 *
 * \note                With DTLS, use PTLS_SSL_MINOR_VERSION_2 for DTLS 1.0
 *                      and PTLS_SSL_MINOR_VERSION_3 for DTLS 1.2
 */
void ptls_ssl_conf_ciphersuites_for_version( ptls_ssl_config *conf,
                                       const int *ciphersuites,
                                       int major, int minor );

#if defined(PTLS_X509_CRT_PARSE_C)
/**
 * \brief          Set the X.509 security profile used for verification
 *
 * \note           The restrictions are enforced for all certificates in the
 *                 chain. However, signatures in the handshake are not covered
 *                 by this setting but by \b ptls_ssl_conf_sig_hashes().
 *
 * \param conf     SSL configuration
 * \param profile  Profile to use
 */
void ptls_ssl_conf_cert_profile( ptls_ssl_config *conf,
                                    const ptls_x509_crt_profile *profile );

/**
 * \brief          Set the data required to verify peer certificate
 *
 * \note           See \c ptls_x509_crt_verify() for notes regarding the
 *                 parameters ca_chain (maps to trust_ca for that function)
 *                 and ca_crl.
 *
 * \param conf     SSL configuration
 * \param ca_chain trusted CA chain (meaning all fully trusted top-level CAs)
 * \param ca_crl   trusted CA CRLs
 */
void ptls_ssl_conf_ca_chain( ptls_ssl_config *conf,
                               ptls_x509_crt *ca_chain,
                               ptls_x509_crl *ca_crl );

void ptls_ssl_conf_ca(ptls_ssl_config *conf, ptls_x509_ca *ca);

/**
 * \brief          Set own certificate chain and private key
 *
 * \note           own_cert should contain in order from the bottom up your
 *                 certificate chain. The top certificate (self-signed)
 *                 can be omitted.
 *
 * \note           On server, this function can be called multiple times to
 *                 provision more than one cert/key pair (eg one ECDSA, one
 *                 RSA with SHA-256, one RSA with SHA-1). An adequate
 *                 certificate will be selected according to the client's
 *                 advertised capabilities. In case mutliple certificates are
 *                 adequate, preference is given to the one set by the first
 *                 call to this function, then second, etc.
 *
 * \note           On client, only the first call has any effect. That is,
 *                 only one client certificate can be provisioned. The
 *                 server's preferences in its CertficateRequest message will
 *                 be ignored and our only cert will be sent regardless of
 *                 whether it matches those preferences - the server can then
 *                 decide what it wants to do with it.
 *
 * \param conf     SSL configuration
 * \param own_cert own public certificate chain
 * \param pk_key   own private key
 *
 * \return         0 on success or PTLS_ERR_SSL_ALLOC_FAILED
 */
int ptls_ssl_conf_own_cert( ptls_ssl_config *conf,
                              ptls_x509_crt *own_cert,
                              ptls_pk_context *pk_key );
#endif /* PTLS_X509_CRT_PARSE_C */

#if defined(PTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
/**
 * \brief          Set the Pre Shared Key (PSK) and the expected identity name
 *
 * \note           This is mainly useful for clients. Servers will usually
 *                 want to use \c ptls_ssl_conf_psk_cb() instead.
 *
 * \note           Currently clients can only register one pre-shared key.
 *                 In other words, the servers' identity hint is ignored.
 *                 Support for setting multiple PSKs on clients and selecting
 *                 one based on the identity hint is not a planned feature but
 *                 feedback is welcomed.
 *
 * \param conf     SSL configuration
 * \param psk      pointer to the pre-shared key
 * \param psk_len  pre-shared key length
 * \param psk_identity      pointer to the pre-shared key identity
 * \param psk_identity_len  identity key length
 *
 * \return         0 if successful or PTLS_ERR_SSL_ALLOC_FAILED
 */
int ptls_ssl_conf_psk( ptls_ssl_config *conf,
                const unsigned char *psk, size_t psk_len,
                const unsigned char *psk_identity, size_t psk_identity_len );


/**
 * \brief          Set the Pre Shared Key (PSK) for the current handshake
 *
 * \note           This should only be called inside the PSK callback,
 *                 ie the function passed to \c ptls_ssl_conf_psk_cb().
 *
 * \param ssl      SSL context
 * \param psk      pointer to the pre-shared key
 * \param psk_len  pre-shared key length
 *
 * \return         0 if successful or PTLS_ERR_SSL_ALLOC_FAILED
 */
int ptls_ssl_set_hs_psk( ptls_ssl_context *ssl,
                            const unsigned char *psk, size_t psk_len );

/**
 * \brief          Set the PSK callback (server-side only).
 *
 *                 If set, the PSK callback is called for each
 *                 handshake where a PSK ciphersuite was negotiated.
 *                 The caller provides the identity received and wants to
 *                 receive the actual PSK data and length.
 *
 *                 The callback has the following parameters: (void *parameter,
 *                 ptls_ssl_context *ssl, const unsigned char *psk_identity,
 *                 size_t identity_len)
 *                 If a valid PSK identity is found, the callback should use
 *                 \c ptls_ssl_set_hs_psk() on the ssl context to set the
 *                 correct PSK and return 0.
 *                 Any other return value will result in a denied PSK identity.
 *
 * \note           If you set a PSK callback using this function, then you
 *                 don't need to set a PSK key and identity using
 *                 \c ptls_ssl_conf_psk().
 *
 * \param conf     SSL configuration
 * \param f_psk    PSK identity function
 * \param p_psk    PSK identity parameter
 */
void ptls_ssl_conf_psk_cb( ptls_ssl_config *conf,
                     int (*f_psk)(void *, ptls_ssl_context *, const unsigned char *,
                                  size_t),
                     void *p_psk );
#endif /* PTLS_KEY_EXCHANGE__SOME__PSK_ENABLED */

#if defined(PTLS_DHM_C) && defined(PTLS_SSL_SRV_C)

#if !defined(PTLS_DEPRECATED_REMOVED)

#if defined(PTLS_DEPRECATED_WARNING)
#define PTLS_DEPRECATED    __attribute__((deprecated))
#else
#define PTLS_DEPRECATED
#endif

/**
 * \brief          Set the Diffie-Hellman public P and G values,
 *                 read as hexadecimal strings (server-side only)
 *                 (Default values: PTLS_DHM_RFC3526_MODP_2048_[PG])
 *
 * \param conf     SSL configuration
 * \param dhm_P    Diffie-Hellman-Merkle modulus
 * \param dhm_G    Diffie-Hellman-Merkle generator
 *
 * \deprecated     Superseded by \c ptls_ssl_conf_dh_param_bin.
 *
 * \return         0 if successful
 */
PTLS_DEPRECATED int ptls_ssl_conf_dh_param( ptls_ssl_config *conf,
                                                  const char *dhm_P,
                                                  const char *dhm_G );

#endif /* PTLS_DEPRECATED_REMOVED */

/**
 * \brief          Set the Diffie-Hellman public P and G values
 *                 from big-endian binary presentations.
 *                 (Default values: PTLS_DHM_RFC3526_MODP_2048_[PG]_BIN)
 *
 * \param conf     SSL configuration
 * \param dhm_P    Diffie-Hellman-Merkle modulus in big-endian binary form
 * \param P_len    Length of DHM modulus
 * \param dhm_G    Diffie-Hellman-Merkle generator in big-endian binary form
 * \param G_len    Length of DHM generator
 *
 * \return         0 if successful
 */
int ptls_ssl_conf_dh_param_bin( ptls_ssl_config *conf,
                                   const unsigned char *dhm_P, size_t P_len,
                                   const unsigned char *dhm_G,  size_t G_len );

/**
 * \brief          Set the Diffie-Hellman public P and G values,
 *                 read from existing context (server-side only)
 *
 * \param conf     SSL configuration
 * \param dhm_ctx  Diffie-Hellman-Merkle context
 *
 * \return         0 if successful
 */
int ptls_ssl_conf_dh_param_ctx( ptls_ssl_config *conf, ptls_dhm_context *dhm_ctx );
#endif /* PTLS_DHM_C && defined(PTLS_SSL_SRV_C) */

#if defined(PTLS_DHM_C) && defined(PTLS_SSL_CLI_C)
/**
 * \brief          Set the minimum length for Diffie-Hellman parameters.
 *                 (Client-side only.)
 *                 (Default: 1024 bits.)
 *
 * \param conf     SSL configuration
 * \param bitlen   Minimum bit length of the DHM prime
 */
void ptls_ssl_conf_dhm_min_bitlen( ptls_ssl_config *conf,
                                      unsigned int bitlen );
#endif /* PTLS_DHM_C && PTLS_SSL_CLI_C */

#if defined(PTLS_ECP_C)
/**
 * \brief          Set the allowed curves in order of preference.
 *                 (Default: all defined curves.)
 *
 *                 On server: this only affects selection of the ECDHE curve;
 *                 the curves used for ECDH and ECDSA are determined by the
 *                 list of available certificates instead.
 *
 *                 On client: this affects the list of curves offered for any
 *                 use. The server can override our preference order.
 *
 *                 Both sides: limits the set of curves accepted for use in
 *                 ECDHE and in the peer's end-entity certificate.
 *
 * \note           This has no influence on which curves are allowed inside the
 *                 certificate chains, see \c ptls_ssl_conf_cert_profile()
 *                 for that. For the end-entity certificate however, the key
 *                 will be accepted only if it is allowed both by this list
 *                 and by the cert profile.
 *
 * \note           This list should be ordered by decreasing preference
 *                 (preferred curve first).
 *
 * \param conf     SSL configuration
 * \param curves   Ordered list of allowed curves,
 *                 terminated by PTLS_ECP_DP_NONE.
 */
void ptls_ssl_conf_curves( ptls_ssl_config *conf,
                              const ptls_ecp_group_id *curves );
#endif /* PTLS_ECP_C */

#if defined(PTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
/**
 * \brief          Set the allowed hashes for signatures during the handshake.
 *                 (Default: all available hashes except MD5.)
 *
 * \note           This only affects which hashes are offered and can be used
 *                 for signatures during the handshake. Hashes for message
 *                 authentication and the TLS PRF are controlled by the
 *                 ciphersuite, see \c ptls_ssl_conf_ciphersuites(). Hashes
 *                 used for certificate signature are controlled by the
 *                 verification profile, see \c ptls_ssl_conf_cert_profile().
 *
 * \note           This list should be ordered by decreasing preference
 *                 (preferred hash first).
 *
 * \param conf     SSL configuration
 * \param hashes   Ordered list of allowed signature hashes,
 *                 terminated by \c PTLS_MD_NONE.
 */
void ptls_ssl_conf_sig_hashes( ptls_ssl_config *conf,
                                  const int *hashes );
#endif /* PTLS_KEY_EXCHANGE__WITH_CERT__ENABLED */

#if defined(PTLS_X509_CRT_PARSE_C)
/**
 * \brief          Set or reset the hostname to check against the received
 *                 server certificate. It sets the ServerName TLS extension,
 *                 too, if that extension is enabled. (client-side only)
 *
 * \param ssl      SSL context
 * \param hostname the server hostname, may be NULL to clear hostname

 * \note           Maximum hostname length PTLS_SSL_MAX_HOST_NAME_LEN.
 *
 * \return         0 if successful, PTLS_ERR_SSL_ALLOC_FAILED on
 *                 allocation failure, PTLS_ERR_SSL_BAD_INPUT_DATA on
 *                 too long input hostname.
 *
 *                 Hostname set to the one provided on success (cleared
 *                 when NULL). On allocation failure hostname is cleared.
 *                 On too long input failure, old hostname is unchanged.
 */
int ptls_ssl_set_hostname( ptls_ssl_context *ssl, const char *hostname );
#endif /* PTLS_X509_CRT_PARSE_C */

#if defined(PTLS_SSL_SERVER_NAME_INDICATION)
/**
 * \brief          Set own certificate and key for the current handshake
 *
 * \note           Same as \c ptls_ssl_conf_own_cert() but for use within
 *                 the SNI callback.
 *
 * \param ssl      SSL context
 * \param own_cert own public certificate chain
 * \param pk_key   own private key
 *
 * \return         0 on success or PTLS_ERR_SSL_ALLOC_FAILED
 */
int ptls_ssl_set_hs_own_cert( ptls_ssl_context *ssl,
                                 ptls_x509_crt *own_cert,
                                 ptls_pk_context *pk_key );

/**
 * \brief          Set the data required to verify peer certificate for the
 *                 current handshake
 *
 * \note           Same as \c ptls_ssl_conf_ca_chain() but for use within
 *                 the SNI callback.
 *
 * \param ssl      SSL context
 * \param ca_chain trusted CA chain (meaning all fully trusted top-level CAs)
 * \param ca_crl   trusted CA CRLs
 */
void ptls_ssl_set_hs_ca_chain( ptls_ssl_context *ssl,
                                  ptls_x509_crt *ca_chain,
                                  ptls_x509_crl *ca_crl );

/**
 * \brief          Set authmode for the current handshake.
 *
 * \note           Same as \c ptls_ssl_conf_authmode() but for use within
 *                 the SNI callback.
 *
 * \param ssl      SSL context
 * \param authmode PTLS_SSL_VERIFY_NONE, PTLS_SSL_VERIFY_OPTIONAL or
 *                 PTLS_SSL_VERIFY_REQUIRED
 */
void ptls_ssl_set_hs_authmode( ptls_ssl_context *ssl,
                                  int authmode );

/**
 * \brief          Set server side ServerName TLS extension callback
 *                 (optional, server-side only).
 *
 *                 If set, the ServerName callback is called whenever the
 *                 server receives a ServerName TLS extension from the client
 *                 during a handshake. The ServerName callback has the
 *                 following parameters: (void *parameter, ptls_ssl_context *ssl,
 *                 const unsigned char *hostname, size_t len). If a suitable
 *                 certificate is found, the callback must set the
 *                 certificate(s) and key(s) to use with \c
 *                 ptls_ssl_set_hs_own_cert() (can be called repeatedly),
 *                 and may optionally adjust the CA and associated CRL with \c
 *                 ptls_ssl_set_hs_ca_chain() as well as the client
 *                 authentication mode with \c ptls_ssl_set_hs_authmode(),
 *                 then must return 0. If no matching name is found, the
 *                 callback must either set a default cert, or
 *                 return non-zero to abort the handshake at this point.
 *
 * \param conf     SSL configuration
 * \param f_sni    verification function
 * \param p_sni    verification parameter
 */
void ptls_ssl_conf_sni( ptls_ssl_config *conf,
                  int (*f_sni)(void *, ptls_ssl_context *, const unsigned char *,
                               size_t),
                  void *p_sni );
#endif /* PTLS_SSL_SERVER_NAME_INDICATION */

#if defined(PTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
/**
 * \brief          Set the EC J-PAKE password for current handshake.
 *
 * \note           An internal copy is made, and destroyed as soon as the
 *                 handshake is completed, or when the SSL context is reset or
 *                 freed.
 *
 * \note           The SSL context needs to be already set up. The right place
 *                 to call this function is between \c ptls_ssl_setup() or
 *                 \c ptls_ssl_reset() and \c ptls_ssl_handshake().
 *
 * \param ssl      SSL context
 * \param pw       EC J-PAKE password (pre-shared secret)
 * \param pw_len   length of pw in bytes
 *
 * \return         0 on success, or a negative error code.
 */
int ptls_ssl_set_hs_ecjpake_password( ptls_ssl_context *ssl,
                                         const unsigned char *pw,
                                         size_t pw_len );
#endif /*PTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(PTLS_SSL_ALPN)
/**
 * \brief          Set the supported Application Layer Protocols.
 *
 * \param conf     SSL configuration
 * \param protos   Pointer to a NULL-terminated list of supported protocols,
 *                 in decreasing preference order. The pointer to the list is
 *                 recorded by the library for later reference as required, so
 *                 the lifetime of the table must be atleast as long as the
 *                 lifetime of the SSL configuration structure.
 *
 * \return         0 on success, or PTLS_ERR_SSL_BAD_INPUT_DATA.
 */
int ptls_ssl_conf_alpn_protocols( ptls_ssl_config *conf, const char **protos );

/**
 * \brief          Get the name of the negotiated Application Layer Protocol.
 *                 This function should be called after the handshake is
 *                 completed.
 *
 * \param ssl      SSL context
 *
 * \return         Protcol name, or NULL if no protocol was negotiated.
 */
const char *ptls_ssl_get_alpn_protocol( const ptls_ssl_context *ssl );
#endif /* PTLS_SSL_ALPN */

/**
 * \brief          Set the maximum supported version sent from the client side
 *                 and/or accepted at the server side
 *                 (Default: PTLS_SSL_MAX_MAJOR_VERSION, PTLS_SSL_MAX_MINOR_VERSION)
 *
 * \note           This ignores ciphersuites from higher versions.
 *
 * \note           With DTLS, use PTLS_SSL_MINOR_VERSION_2 for DTLS 1.0 and
 *                 PTLS_SSL_MINOR_VERSION_3 for DTLS 1.2
 *
 * \param conf     SSL configuration
 * \param major    Major version number (only PTLS_SSL_MAJOR_VERSION_3 supported)
 * \param minor    Minor version number (PTLS_SSL_MINOR_VERSION_0,
 *                 PTLS_SSL_MINOR_VERSION_1 and PTLS_SSL_MINOR_VERSION_2,
 *                 PTLS_SSL_MINOR_VERSION_3 supported)
 */
void ptls_ssl_conf_max_version( ptls_ssl_config *conf, int major, int minor );

/**
 * \brief          Set the minimum accepted SSL/TLS protocol version
 *                 (Default: TLS 1.0)
 *
 * \note           Input outside of the SSL_MAX_XXXXX_VERSION and
 *                 SSL_MIN_XXXXX_VERSION range is ignored.
 *
 * \note           PTLS_SSL_MINOR_VERSION_0 (SSL v3) should be avoided.
 *
 * \note           With DTLS, use PTLS_SSL_MINOR_VERSION_2 for DTLS 1.0 and
 *                 PTLS_SSL_MINOR_VERSION_3 for DTLS 1.2
 *
 * \param conf     SSL configuration
 * \param major    Major version number (only PTLS_SSL_MAJOR_VERSION_3 supported)
 * \param minor    Minor version number (PTLS_SSL_MINOR_VERSION_0,
 *                 PTLS_SSL_MINOR_VERSION_1 and PTLS_SSL_MINOR_VERSION_2,
 *                 PTLS_SSL_MINOR_VERSION_3 supported)
 */
void ptls_ssl_conf_min_version( ptls_ssl_config *conf, int major, int minor );

#if defined(PTLS_SSL_FALLBACK_SCSV) && defined(PTLS_SSL_CLI_C)
/**
 * \brief          Set the fallback flag (client-side only).
 *                 (Default: PTLS_SSL_IS_NOT_FALLBACK).
 *
 * \note           Set to PTLS_SSL_IS_FALLBACK when preparing a fallback
 *                 connection, that is a connection with max_version set to a
 *                 lower value than the value you're willing to use. Such
 *                 fallback connections are not recommended but are sometimes
 *                 necessary to interoperate with buggy (version-intolerant)
 *                 servers.
 *
 * \warning        You should NOT set this to PTLS_SSL_IS_FALLBACK for
 *                 non-fallback connections! This would appear to work for a
 *                 while, then cause failures when the server is upgraded to
 *                 support a newer TLS version.
 *
 * \param conf     SSL configuration
 * \param fallback PTLS_SSL_IS_NOT_FALLBACK or PTLS_SSL_IS_FALLBACK
 */
void ptls_ssl_conf_fallback( ptls_ssl_config *conf, char fallback );
#endif /* PTLS_SSL_FALLBACK_SCSV && PTLS_SSL_CLI_C */

#if defined(PTLS_SSL_ENCRYPT_THEN_MAC)
/**
 * \brief           Enable or disable Encrypt-then-MAC
 *                  (Default: PTLS_SSL_ETM_ENABLED)
 *
 * \note            This should always be enabled, it is a security
 *                  improvement, and should not cause any interoperability
 *                  issue (used only if the peer supports it too).
 *
 * \param conf      SSL configuration
 * \param etm       PTLS_SSL_ETM_ENABLED or PTLS_SSL_ETM_DISABLED
 */
void ptls_ssl_conf_encrypt_then_mac( ptls_ssl_config *conf, char etm );
#endif /* PTLS_SSL_ENCRYPT_THEN_MAC */

#if defined(PTLS_SSL_EXTENDED_MASTER_SECRET)
/**
 * \brief           Enable or disable Extended Master Secret negotiation.
 *                  (Default: PTLS_SSL_EXTENDED_MS_ENABLED)
 *
 * \note            This should always be enabled, it is a security fix to the
 *                  protocol, and should not cause any interoperability issue
 *                  (used only if the peer supports it too).
 *
 * \param conf      SSL configuration
 * \param ems       PTLS_SSL_EXTENDED_MS_ENABLED or PTLS_SSL_EXTENDED_MS_DISABLED
 */
void ptls_ssl_conf_extended_master_secret( ptls_ssl_config *conf, char ems );
#endif /* PTLS_SSL_EXTENDED_MASTER_SECRET */

#if defined(PTLS_ARC4_C)
/**
 * \brief          Disable or enable support for RC4
 *                 (Default: PTLS_SSL_ARC4_DISABLED)
 *
 * \warning        Use of RC4 in DTLS/TLS has been prohibited by RFC 7465
 *                 for security reasons. Use at your own risk.
 *
 * \note           This function is deprecated and will likely be removed in
 *                 a future version of the library.
 *                 RC4 is disabled by default at compile time and needs to be
 *                 actively enabled for use with legacy systems.
 *
 * \param conf     SSL configuration
 * \param arc4     PTLS_SSL_ARC4_ENABLED or PTLS_SSL_ARC4_DISABLED
 */
void ptls_ssl_conf_arc4_support( ptls_ssl_config *conf, char arc4 );
#endif /* PTLS_ARC4_C */

#if defined(PTLS_SSL_SRV_C)
/**
 * \brief          Whether to send a list of acceptable CAs in
 *                 CertificateRequest messages.
 *                 (Default: do send)
 *
 * \param conf     SSL configuration
 * \param cert_req_ca_list   PTLS_SSL_CERT_REQ_CA_LIST_ENABLED or
 *                          PTLS_SSL_CERT_REQ_CA_LIST_DISABLED
 */
void ptls_ssl_conf_cert_req_ca_list( ptls_ssl_config *conf,
                                          char cert_req_ca_list );
#endif /* PTLS_SSL_SRV_C */

#if defined(PTLS_SSL_MAX_FRAGMENT_LENGTH)
/**
 * \brief          Set the maximum fragment length to emit and/or negotiate
 *                 (Default: the smaller of PTLS_SSL_IN_CONTENT_LEN and
 *                 PTLS_SSL_OUT_CONTENT_LEN, usually 2^14 bytes)
 *                 (Server: set maximum fragment length to emit,
 *                 usually negotiated by the client during handshake
 *                 (Client: set maximum fragment length to emit *and*
 *                 negotiate with the server during handshake)
 *
 * \note           With TLS, this currently only affects ApplicationData (sent
 *                 with \c ptls_ssl_read()), not handshake messages.
 *                 With DTLS, this affects both ApplicationData and handshake.
 *
 * \note           This sets the maximum length for a record's payload,
 *                 excluding record overhead that will be added to it, see
 *                 \c ptls_ssl_get_record_expansion().
 *
 * \note           For DTLS, it is also possible to set a limit for the total
 *                 size of daragrams passed to the transport layer, including
 *                 record overhead, see \c ptls_ssl_set_mtu().
 *
 * \param conf     SSL configuration
 * \param mfl_code Code for maximum fragment length (allowed values:
 *                 PTLS_SSL_MAX_FRAG_LEN_512,  PTLS_SSL_MAX_FRAG_LEN_1024,
 *                 PTLS_SSL_MAX_FRAG_LEN_2048, PTLS_SSL_MAX_FRAG_LEN_4096)
 *
 * \return         0 if successful or PTLS_ERR_SSL_BAD_INPUT_DATA
 */
int ptls_ssl_conf_max_frag_len( ptls_ssl_config *conf, unsigned char mfl_code );
#endif /* PTLS_SSL_MAX_FRAGMENT_LENGTH */

#if defined(PTLS_SSL_TRUNCATED_HMAC)
/**
 * \brief          Activate negotiation of truncated HMAC
 *                 (Default: PTLS_SSL_TRUNC_HMAC_DISABLED)
 *
 * \param conf     SSL configuration
 * \param truncate Enable or disable (PTLS_SSL_TRUNC_HMAC_ENABLED or
 *                                    PTLS_SSL_TRUNC_HMAC_DISABLED)
 */
void ptls_ssl_conf_truncated_hmac( ptls_ssl_config *conf, int truncate );
#endif /* PTLS_SSL_TRUNCATED_HMAC */

#if defined(PTLS_SSL_CBC_RECORD_SPLITTING)
/**
 * \brief          Enable / Disable 1/n-1 record splitting
 *                 (Default: PTLS_SSL_CBC_RECORD_SPLITTING_ENABLED)
 *
 * \note           Only affects SSLv3 and TLS 1.0, not higher versions.
 *                 Does not affect non-CBC ciphersuites in any version.
 *
 * \param conf     SSL configuration
 * \param split    PTLS_SSL_CBC_RECORD_SPLITTING_ENABLED or
 *                 PTLS_SSL_CBC_RECORD_SPLITTING_DISABLED
 */
void ptls_ssl_conf_cbc_record_splitting( ptls_ssl_config *conf, char split );
#endif /* PTLS_SSL_CBC_RECORD_SPLITTING */

#if defined(PTLS_SSL_SESSION_TICKETS) && defined(PTLS_SSL_CLI_C)
/**
 * \brief          Enable / Disable session tickets (client only).
 *                 (Default: PTLS_SSL_SESSION_TICKETS_ENABLED.)
 *
 * \note           On server, use \c ptls_ssl_conf_session_tickets_cb().
 *
 * \param conf     SSL configuration
 * \param use_tickets   Enable or disable (PTLS_SSL_SESSION_TICKETS_ENABLED or
 *                                         PTLS_SSL_SESSION_TICKETS_DISABLED)
 */
void ptls_ssl_conf_session_tickets( ptls_ssl_config *conf, int use_tickets );
#endif /* PTLS_SSL_SESSION_TICKETS && PTLS_SSL_CLI_C */

#if defined(PTLS_SSL_RENEGOTIATION)
/**
 * \brief          Enable / Disable renegotiation support for connection when
 *                 initiated by peer
 *                 (Default: PTLS_SSL_RENEGOTIATION_DISABLED)
 *
 * \warning        It is recommended to always disable renegotation unless you
 *                 know you need it and you know what you're doing. In the
 *                 past, there have been several issues associated with
 *                 renegotiation or a poor understanding of its properties.
 *
 * \note           Server-side, enabling renegotiation also makes the server
 *                 susceptible to a resource DoS by a malicious client.
 *
 * \param conf    SSL configuration
 * \param renegotiation     Enable or disable (PTLS_SSL_RENEGOTIATION_ENABLED or
 *                                             PTLS_SSL_RENEGOTIATION_DISABLED)
 */
void ptls_ssl_conf_renegotiation( ptls_ssl_config *conf, int renegotiation );
#endif /* PTLS_SSL_RENEGOTIATION */

/**
 * \brief          Prevent or allow legacy renegotiation.
 *                 (Default: PTLS_SSL_LEGACY_NO_RENEGOTIATION)
 *
 *                 PTLS_SSL_LEGACY_NO_RENEGOTIATION allows connections to
 *                 be established even if the peer does not support
 *                 secure renegotiation, but does not allow renegotiation
 *                 to take place if not secure.
 *                 (Interoperable and secure option)
 *
 *                 PTLS_SSL_LEGACY_ALLOW_RENEGOTIATION allows renegotiations
 *                 with non-upgraded peers. Allowing legacy renegotiation
 *                 makes the connection vulnerable to specific man in the
 *                 middle attacks. (See RFC 5746)
 *                 (Most interoperable and least secure option)
 *
 *                 PTLS_SSL_LEGACY_BREAK_HANDSHAKE breaks off connections
 *                 if peer does not support secure renegotiation. Results
 *                 in interoperability issues with non-upgraded peers
 *                 that do not support renegotiation altogether.
 *                 (Most secure option, interoperability issues)
 *
 * \param conf     SSL configuration
 * \param allow_legacy  Prevent or allow (SSL_NO_LEGACY_RENEGOTIATION,
 *                                        SSL_ALLOW_LEGACY_RENEGOTIATION or
 *                                        PTLS_SSL_LEGACY_BREAK_HANDSHAKE)
 */
void ptls_ssl_conf_legacy_renegotiation( ptls_ssl_config *conf, int allow_legacy );

#if defined(PTLS_SSL_RENEGOTIATION)
/**
 * \brief          Enforce renegotiation requests.
 *                 (Default: enforced, max_records = 16)
 *
 *                 When we request a renegotiation, the peer can comply or
 *                 ignore the request. This function allows us to decide
 *                 whether to enforce our renegotiation requests by closing
 *                 the connection if the peer doesn't comply.
 *
 *                 However, records could already be in transit from the peer
 *                 when the request is emitted. In order to increase
 *                 reliability, we can accept a number of records before the
 *                 expected handshake records.
 *
 *                 The optimal value is highly dependent on the specific usage
 *                 scenario.
 *
 * \note           With DTLS and server-initiated renegotiation, the
 *                 HelloRequest is retransmited every time ptls_ssl_read() times
 *                 out or receives Application Data, until:
 *                 - max_records records have beens seen, if it is >= 0, or
 *                 - the number of retransmits that would happen during an
 *                 actual handshake has been reached.
 *                 Please remember the request might be lost a few times
 *                 if you consider setting max_records to a really low value.
 *
 * \warning        On client, the grace period can only happen during
 *                 ptls_ssl_read(), as opposed to ptls_ssl_write() and ptls_ssl_renegotiate()
 *                 which always behave as if max_record was 0. The reason is,
 *                 if we receive application data from the server, we need a
 *                 place to write it, which only happens during ptls_ssl_read().
 *
 * \param conf     SSL configuration
 * \param max_records Use PTLS_SSL_RENEGOTIATION_NOT_ENFORCED if you don't want to
 *                 enforce renegotiation, or a non-negative value to enforce
 *                 it but allow for a grace period of max_records records.
 */
void ptls_ssl_conf_renegotiation_enforced( ptls_ssl_config *conf, int max_records );

/**
 * \brief          Set record counter threshold for periodic renegotiation.
 *                 (Default: 2^48 - 1)
 *
 *                 Renegotiation is automatically triggered when a record
 *                 counter (outgoing or ingoing) crosses the defined
 *                 threshold. The default value is meant to prevent the
 *                 connection from being closed when the counter is about to
 *                 reached its maximal value (it is not allowed to wrap).
 *
 *                 Lower values can be used to enforce policies such as "keys
 *                 must be refreshed every N packets with cipher X".
 *
 *                 The renegotiation period can be disabled by setting
 *                 conf->disable_renegotiation to
 *                 PTLS_SSL_RENEGOTIATION_DISABLED.
 *
 * \note           When the configured transport is
 *                 PTLS_SSL_TRANSPORT_DATAGRAM the maximum renegotiation
 *                 period is 2^48 - 1, and for PTLS_SSL_TRANSPORT_STREAM,
 *                 the maximum renegotiation period is 2^64 - 1.
 *
 * \param conf     SSL configuration
 * \param period   The threshold value: a big-endian 64-bit number.
 */
void ptls_ssl_conf_renegotiation_period( ptls_ssl_config *conf,
                                   const unsigned char period[8] );
#endif /* PTLS_SSL_RENEGOTIATION */

/**
 * \brief          Check if there is data already read from the
 *                 underlying transport but not yet processed.
 *
 * \param ssl      SSL context
 *
 * \return         0 if nothing's pending, 1 otherwise.
 *
 * \note           This is different in purpose and behaviour from
 *                 \c ptls_ssl_get_bytes_avail in that it considers
 *                 any kind of unprocessed data, not only unread
 *                 application data. If \c ptls_ssl_get_bytes
 *                 returns a non-zero value, this function will
 *                 also signal pending data, but the converse does
 *                 not hold. For example, in DTLS there might be
 *                 further records waiting to be processed from
 *                 the current underlying transport's datagram.
 *
 * \note           If this function returns 1 (data pending), this
 *                 does not imply that a subsequent call to
 *                 \c ptls_ssl_read will provide any data;
 *                 e.g., the unprocessed data might turn out
 *                 to be an alert or a handshake message.
 *
 * \note           This function is useful in the following situation:
 *                 If the SSL/TLS module successfully returns from an
 *                 operation - e.g. a handshake or an application record
 *                 read - and you're awaiting incoming data next, you
 *                 must not immediately idle on the underlying transport
 *                 to have data ready, but you need to check the value
 *                 of this function first. The reason is that the desired
 *                 data might already be read but not yet processed.
 *                 If, in contrast, a previous call to the SSL/TLS module
 *                 returned PTLS_ERR_SSL_WANT_READ, it is not necessary
 *                 to call this function, as the latter error code entails
 *                 that all internal data has been processed.
 *
 */
int ptls_ssl_check_pending( const ptls_ssl_context *ssl );

/**
 * \brief          Return the number of application data bytes
 *                 remaining to be read from the current record.
 *
 * \param ssl      SSL context
 *
 * \return         How many bytes are available in the application
 *                 data record read buffer.
 *
 * \note           When working over a datagram transport, this is
 *                 useful to detect the current datagram's boundary
 *                 in case \c ptls_ssl_read has written the maximal
 *                 amount of data fitting into the input buffer.
 *
 */
size_t ptls_ssl_get_bytes_avail( const ptls_ssl_context *ssl );

/**
 * \brief          Return the result of the certificate verification
 *
 * \param ssl      SSL context
 *
 * \return         0 if successful,
 *                 -1 if result is not available (eg because the handshake was
 *                 aborted too early), or
 *                 a combination of BADCERT_xxx and BADCRL_xxx flags, see
 *                 x509.h
 */
uint32_t ptls_ssl_get_verify_result( const ptls_ssl_context *ssl );

/**
 * \brief          Return the name of the current ciphersuite
 *
 * \param ssl      SSL context
 *
 * \return         a string containing the ciphersuite name
 */
const char *ptls_ssl_get_ciphersuite( const ptls_ssl_context *ssl );

/**
 * \brief          Return the current SSL version (SSLv3/TLSv1/etc)
 *
 * \param ssl      SSL context
 *
 * \return         a string containing the SSL version
 */
const char *ptls_ssl_get_version( const ptls_ssl_context *ssl );

/**
 * \brief          Return the (maximum) number of bytes added by the record
 *                 layer: header + encryption/MAC overhead (inc. padding)
 *
 * \note           This function is not available (always returns an error)
 *                 when record compression is enabled.
 *
 * \param ssl      SSL context
 *
 * \return         Current maximum record expansion in bytes, or
 *                 PTLS_ERR_SSL_FEATURE_UNAVAILABLE if compression is
 *                 enabled, which makes expansion much less predictable
 */
int ptls_ssl_get_record_expansion( const ptls_ssl_context *ssl );

#if defined(PTLS_SSL_MAX_FRAGMENT_LENGTH)
/**
 * \brief          Return the maximum fragment length (payload, in bytes).
 *                 This is the value negotiated with peer if any,
 *                 or the locally configured value.
 *
 * \sa             ptls_ssl_conf_max_frag_len()
 * \sa             ptls_ssl_get_max_record_payload()
 *
 * \param ssl      SSL context
 *
 * \return         Current maximum fragment length.
 */
size_t ptls_ssl_get_max_frag_len( const ptls_ssl_context *ssl );
#endif /* PTLS_SSL_MAX_FRAGMENT_LENGTH */

/**
 * \brief          Return the current maximum outgoing record payload in bytes.
 *                 This takes into account the config.h setting \c
 *                 PTLS_SSL_OUT_CONTENT_LEN, the configured and negotiated
 *                 max fragment length extension if used, and for DTLS the
 *                 path MTU as configured and current record expansion.
 *
 * \note           With DTLS, \c ptls_ssl_write() will return an error if
 *                 called with a larger length value.
 *                 With TLS, \c ptls_ssl_write() will fragment the input if
 *                 necessary and return the number of bytes written; it is up
 *                 to the caller to call \c ptls_ssl_write() again in
 *                 order to send the remaining bytes if any.
 *
 * \note           This function is not available (always returns an error)
 *                 when record compression is enabled.
 *
 * \sa             ptls_ssl_set_mtu()
 * \sa             ptls_ssl_get_max_frag_len()
 * \sa             ptls_ssl_get_record_expansion()
 *
 * \param ssl      SSL context
 *
 * \return         Current maximum payload for an outgoing record,
 *                 or a negative error code.
 */
int ptls_ssl_get_max_out_record_payload( const ptls_ssl_context *ssl );

#if defined(PTLS_X509_CRT_PARSE_C)
/**
 * \brief          Return the peer certificate from the current connection
 *
 *                 Note: Can be NULL in case no certificate was sent during
 *                 the handshake. Different calls for the same connection can
 *                 return the same or different pointers for the same
 *                 certificate and even a different certificate altogether.
 *                 The peer cert CAN change in a single connection if
 *                 renegotiation is performed.
 *
 * \param ssl      SSL context
 *
 * \return         the current peer certificate
 */
const ptls_x509_crt *ptls_ssl_get_peer_cert( const ptls_ssl_context *ssl );
#endif /* PTLS_X509_CRT_PARSE_C */

#if defined(PTLS_SSL_CLI_C)
/**
 * \brief          Save session in order to resume it later (client-side only)
 *                 Session data is copied to presented session structure.
 *
 *
 * \param ssl      SSL context
 * \param session  session context
 *
 * \return         0 if successful,
 *                 PTLS_ERR_SSL_ALLOC_FAILED if memory allocation failed,
 *                 PTLS_ERR_SSL_BAD_INPUT_DATA if used server-side or
 *                 arguments are otherwise invalid.
 *
 * \note           Only the server certificate is copied, and not the full chain,
 *                 so you should not attempt to validate the certificate again
 *                 by calling \c ptls_x509_crt_verify() on it.
 *                 Instead, you should use the results from the verification
 *                 in the original handshake by calling \c ptls_ssl_get_verify_result()
 *                 after loading the session again into a new SSL context
 *                 using \c ptls_ssl_set_session().
 *
 * \note           Once the session object is not needed anymore, you should
 *                 free it by calling \c ptls_ssl_session_free().
 *
 * \sa             ptls_ssl_set_session()
 */
int ptls_ssl_get_session( const ptls_ssl_context *ssl, ptls_ssl_session *session );
#endif /* PTLS_SSL_CLI_C */

/**
 * \brief          Perform the SSL handshake
 *
 * \param ssl      SSL context
 *
 * \return         0 if successful, or
 *                 PTLS_ERR_SSL_WANT_READ or PTLS_ERR_SSL_WANT_WRITE, or
 *                 PTLS_ERR_SSL_HELLO_VERIFY_REQUIRED (see below), or
 *                 a specific SSL error code.
 *
 *                 If this function returns PTLS_ERR_SSL_WANT_READ, the
 *                 handshake is unfinished and no further data is available
 *                 from the underlying transport. In this case, you must call
 *                 the function again at some later stage.
 *
 * \note           Remarks regarding event-driven DTLS:
 *                 If the function returns PTLS_ERR_SSL_WANT_READ, no datagram
 *                 from the underlying transport layer is currently being processed,
 *                 and it is safe to idle until the timer or the underlying transport
 *                 signal a new event. This is not true for a successful handshake,
 *                 in which case the datagram of the underlying transport that is
 *                 currently being processed might or might not contain further
 *                 DTLS records.
 *
 * \note           If this function returns something other than 0 or
 *                 PTLS_ERR_SSL_WANT_READ/WRITE, you must stop using
 *                 the SSL context for reading or writing, and either free it or
 *                 call \c ptls_ssl_session_reset() on it before re-using it
 *                 for a new connection; the current connection must be closed.
 *
 * \note           If DTLS is in use, then you may choose to handle
 *                 PTLS_ERR_SSL_HELLO_VERIFY_REQUIRED specially for logging
 *                 purposes, as it is an expected return value rather than an
 *                 actual error, but you still need to reset/free the context.
 */
int ptls_ssl_handshake( ptls_ssl_context *ssl );

/**
 * \brief          Perform a single step of the SSL handshake
 *
 * \note           The state of the context (ssl->state) will be at
 *                 the next state after execution of this function. Do not
 *                 call this function if state is PTLS_SSL_HANDSHAKE_OVER.
 *
 * \note           If this function returns something other than 0 or
 *                 PTLS_ERR_SSL_WANT_READ/WRITE, you must stop using
 *                 the SSL context for reading or writing, and either free it or
 *                 call \c ptls_ssl_session_reset() on it before re-using it
 *                 for a new connection; the current connection must be closed.
 *
 * \param ssl      SSL context
 *
 * \return         0 if successful, or
 *                 PTLS_ERR_SSL_WANT_READ or PTLS_ERR_SSL_WANT_WRITE, or
 *                 a specific SSL error code.
 */
int ptls_ssl_handshake_step( ptls_ssl_context *ssl );

#if defined(PTLS_SSL_RENEGOTIATION)
/**
 * \brief          Initiate an SSL renegotiation on the running connection.
 *                 Client: perform the renegotiation right now.
 *                 Server: request renegotiation, which will be performed
 *                 during the next call to ptls_ssl_read() if honored by
 *                 client.
 *
 * \param ssl      SSL context
 *
 * \return         0 if successful, or any ptls_ssl_handshake() return
 *                 value.
 *
 * \note           If this function returns something other than 0 or
 *                 PTLS_ERR_SSL_WANT_READ/WRITE, you must stop using
 *                 the SSL context for reading or writing, and either free it or
 *                 call \c ptls_ssl_session_reset() on it before re-using it
 *                 for a new connection; the current connection must be closed.
 */
int ptls_ssl_renegotiate( ptls_ssl_context *ssl );
#endif /* PTLS_SSL_RENEGOTIATION */

/**
 * \brief          Read at most 'len' application data bytes
 *
 * \param ssl      SSL context
 * \param buf      buffer that will hold the data
 * \param len      maximum number of bytes to read
 *
 * \return         One of the following:
 *                 - 0 if the read end of the underlying transport was closed,
 *                 - the (positive) number of bytes read, or
 *                 - a negative error code on failure.
 *
 *                 If PTLS_ERR_SSL_WANT_READ is returned, no application data
 *                 is available from the underlying transport. In this case,
 *                 the function needs to be called again at some later stage.
 *
 *                 If PTLS_ERR_SSL_WANT_WRITE is returned, a write is pending
 *                 but the underlying transport isn't available for writing. In this
 *                 case, the function needs to be called again at some later stage.
 *
 *                 When this function return PTLS_ERR_SSL_CLIENT_RECONNECT
 *                 (which can only happen server-side), it means that a client
 *                 is initiating a new connection using the same source port.
 *                 You can either treat that as a connection close and wait
 *                 for the client to resend a ClientHello, or directly
 *                 continue with \c ptls_ssl_handshake() with the same
 *                 context (as it has beeen reset internally). Either way, you
 *                 should make sure this is seen by the application as a new
 *                 connection: application state, if any, should be reset, and
 *                 most importantly the identity of the client must be checked
 *                 again. WARNING: not validating the identity of the client
 *                 again, or not transmitting the new identity to the
 *                 application layer, would allow authentication bypass!
 *
 * \note           If this function returns something other than a positive value
 *                 or PTLS_ERR_SSL_WANT_READ/WRITE or PTLS_ERR_SSL_CLIENT_RECONNECT,
 *                 you must stop using the SSL context for reading or writing,
 *                 and either free it or call \c ptls_ssl_session_reset() on it
 *                 before re-using it for a new connection; the current connection
 *                 must be closed.
 *
 * \note           Remarks regarding event-driven DTLS:
 *                 - If the function returns PTLS_ERR_SSL_WANT_READ, no datagram
 *                   from the underlying transport layer is currently being processed,
 *                   and it is safe to idle until the timer or the underlying transport
 *                   signal a new event.
 *                 - This function may return PTLS_ERR_SSL_WANT_READ even if data was
 *                   initially available on the underlying transport, as this data may have
 *                   been only e.g. duplicated messages or a renegotiation request.
 *                   Therefore, you must be prepared to receive PTLS_ERR_SSL_WANT_READ even
 *                   when reacting to an incoming-data event from the underlying transport.
 *                 - On success, the datagram of the underlying transport that is currently
 *                   being processed may contain further DTLS records. You should call
 *                   \c ptls_ssl_check_pending to check for remaining records.
 *
 */
int ptls_ssl_read( ptls_ssl_context *ssl, unsigned char *buf, size_t len );

/**
 * \brief          Try to write exactly 'len' application data bytes
 *
 * \warning        This function will do partial writes in some cases. If the
 *                 return value is non-negative but less than length, the
 *                 function must be called again with updated arguments:
 *                 buf + ret, len - ret (if ret is the return value) until
 *                 it returns a value equal to the last 'len' argument.
 *
 * \param ssl      SSL context
 * \param buf      buffer holding the data
 * \param len      how many bytes must be written
 *
 * \return         the number of bytes actually written (may be less than len),
 *                 or PTLS_ERR_SSL_WANT_WRITE or PTLS_ERR_SSL_WANT_READ,
 *                 or another negative error code.
 *
 * \note           If this function returns something other than 0, a positive
 *                 value or PTLS_ERR_SSL_WANT_READ/WRITE, you must stop
 *                 using the SSL context for reading or writing, and either
 *                 free it or call \c ptls_ssl_session_reset() on it before
 *                 re-using it for a new connection; the current connection
 *                 must be closed.
 *
 * \note           When this function returns PTLS_ERR_SSL_WANT_WRITE/READ,
 *                 it must be called later with the *same* arguments,
 *                 until it returns a value greater that or equal to 0. When
 *                 the function returns PTLS_ERR_SSL_WANT_WRITE there may be
 *                 some partial data in the output buffer, however this is not
 *                 yet sent.
 *
 * \note           If the requested length is greater than the maximum
 *                 fragment length (either the built-in limit or the one set
 *                 or negotiated with the peer), then:
 *                 - with TLS, less bytes than requested are written.
 *                 - with DTLS, PTLS_ERR_SSL_BAD_INPUT_DATA is returned.
 *                 \c ptls_ssl_get_max_frag_len() may be used to query the
 *                 active maximum fragment length.
 *
 * \note           Attempting to write 0 bytes will result in an empty TLS
 *                 application record being sent.
 */
int ptls_ssl_write( ptls_ssl_context *ssl, const unsigned char *buf, size_t len );

/**
 * \brief           Send an alert message
 *
 * \param ssl       SSL context
 * \param level     The alert level of the message
 *                  (PTLS_SSL_ALERT_LEVEL_WARNING or PTLS_SSL_ALERT_LEVEL_FATAL)
 * \param message   The alert message (SSL_ALERT_MSG_*)
 *
 * \return          0 if successful, or a specific SSL error code.
 *
 * \note           If this function returns something other than 0 or
 *                 PTLS_ERR_SSL_WANT_READ/WRITE, you must stop using
 *                 the SSL context for reading or writing, and either free it or
 *                 call \c ptls_ssl_session_reset() on it before re-using it
 *                 for a new connection; the current connection must be closed.
 */
int ptls_ssl_send_alert_message( ptls_ssl_context *ssl,
                            unsigned char level,
                            unsigned char message );
/**
 * \brief          Notify the peer that the connection is being closed
 *
 * \param ssl      SSL context
 *
 * \return          0 if successful, or a specific SSL error code.
 *
 * \note           If this function returns something other than 0 or
 *                 PTLS_ERR_SSL_WANT_READ/WRITE, you must stop using
 *                 the SSL context for reading or writing, and either free it or
 *                 call \c ptls_ssl_session_reset() on it before re-using it
 *                 for a new connection; the current connection must be closed.
 */
int ptls_ssl_close_notify( ptls_ssl_context *ssl );

/**
 * \brief          Free referenced items in an SSL context and clear memory
 *
 * \param ssl      SSL context
 */
void ptls_ssl_free( ptls_ssl_context *ssl );

/**
 * \brief          Initialize an SSL configuration context
 *                 Just makes the context ready for
 *                 ptls_ssl_config_defaults() or ptls_ssl_config_free().
 *
 * \note           You need to call ptls_ssl_config_defaults() unless you
 *                 manually set all of the relevent fields yourself.
 *
 * \param conf     SSL configuration context
 */
void ptls_ssl_config_init( ptls_ssl_config *conf );

/**
 * \brief          Load reasonnable default SSL configuration values.
 *                 (You need to call ptls_ssl_config_init() first.)
 *
 * \param conf     SSL configuration context
 * \param endpoint PTLS_SSL_IS_CLIENT or PTLS_SSL_IS_SERVER
 * \param transport PTLS_SSL_TRANSPORT_STREAM for TLS, or
 *                  PTLS_SSL_TRANSPORT_DATAGRAM for DTLS
 * \param preset   a PTLS_SSL_PRESET_XXX value
 *
 * \note           See \c ptls_ssl_conf_transport() for notes on DTLS.
 *
 * \return         0 if successful, or
 *                 PTLS_ERR_XXX_ALLOC_FAILED on memory allocation error.
 */
int ptls_ssl_config_defaults( ptls_ssl_config *conf,
                                 int endpoint, int transport, int preset );

/**
 * \brief          Free an SSL configuration context
 *
 * \param conf     SSL configuration context
 */
void ptls_ssl_config_free( ptls_ssl_config *conf );

/**
 * \brief          Initialize SSL session structure
 *
 * \param session  SSL session
 */
void ptls_ssl_session_init( ptls_ssl_session *session );

/**
 * \brief          Free referenced items in an SSL session including the
 *                 peer certificate and clear memory
 *
 * \note           A session object can be freed even if the SSL context
 *                 that was used to retrieve the session is still in use.
 *
 * \param session  SSL session
 */
void ptls_ssl_session_free( ptls_ssl_session *session );

void ptls_init(void);

#ifdef __cplusplus
}
#endif

#endif /* ssl.h */
