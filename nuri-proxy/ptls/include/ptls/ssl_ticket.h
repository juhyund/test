/**
 * \file ssl_ticket.h
 *
 * \brief TLS server ticket callbacks implementation
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
#ifndef PTLS_SSL_TICKET_H
#define PTLS_SSL_TICKET_H

/*
 * This implementation of the session ticket callbacks includes key
 * management, rotating the keys periodically in order to preserve forward
 * secrecy, when PTLS_HAVE_TIME is defined.
 */

#include "ssl.h"
#include "cipher.h"

#if defined(PTLS_THREADING_C)
#include "threading.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief   Information for session ticket protection
 */
typedef struct ptls_ssl_ticket_key
{
    unsigned char name[4];          /*!< random key identifier              */
    uint32_t generation_time;       /*!< key generation timestamp (seconds) */
    ptls_cipher_context_t ctx;   /*!< context for auth enc/decryption    */
}
ptls_ssl_ticket_key;

/**
 * \brief   Context for session ticket handling functions
 */
typedef struct ptls_ssl_ticket_context
{
    ptls_ssl_ticket_key keys[2]; /*!< ticket protection keys             */
    unsigned char active;           /*!< index of the currently active key  */

    uint32_t ticket_lifetime;       /*!< lifetime of tickets in seconds     */

    /** Callback for getting (pseudo-)random numbers                        */
    int  (*f_rng)(void *, unsigned char *, size_t);
    void *p_rng;                    /*!< context for the RNG function       */

#if defined(PTLS_THREADING_C)
    ptls_threading_mutex_t mutex;
#endif
}
ptls_ssl_ticket_context;

/**
 * \brief           Initialize a ticket context.
 *                  (Just make it ready for ptls_ssl_ticket_setup()
 *                  or ptls_ssl_ticket_free().)
 *
 * \param ctx       Context to be initialized
 */
void ptls_ssl_ticket_init( ptls_ssl_ticket_context *ctx );

/**
 * \brief           Prepare context to be actually used
 *
 * \param ctx       Context to be set up
 * \param f_rng     RNG callback function
 * \param p_rng     RNG callback context
 * \param cipher    AEAD cipher to use for ticket protection.
 *                  Recommended value: PTLS_CIPHER_AES_256_GCM.
 * \param lifetime  Tickets lifetime in seconds
 *                  Recommended value: 86400 (one day).
 *
 * \note            It is highly recommended to select a cipher that is at
 *                  least as strong as the the strongest ciphersuite
 *                  supported. Usually that means a 256-bit key.
 *
 * \note            The lifetime of the keys is twice the lifetime of tickets.
 *                  It is recommended to pick a reasonnable lifetime so as not
 *                  to negate the benefits of forward secrecy.
 *
 * \return          0 if successful,
 *                  or a specific PTLS_ERR_XXX error code
 */
int ptls_ssl_ticket_setup( ptls_ssl_ticket_context *ctx,
    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
    ptls_cipher_type_t cipher,
    uint32_t lifetime );

/**
 * \brief           Implementation of the ticket write callback
 *
 * \note            See \c pentalts_ssl_ticket_write_t for description
 */
ptls_ssl_ticket_write_t ptls_ssl_ticket_write;

/**
 * \brief           Implementation of the ticket parse callback
 *
 * \note            See \c pentalts_ssl_ticket_parse_t for description
 */
ptls_ssl_ticket_parse_t ptls_ssl_ticket_parse;

/**
 * \brief           Free a context's content and zeroize it.
 *
 * \param ctx       Context to be cleaned up
 */
void ptls_ssl_ticket_free( ptls_ssl_ticket_context *ctx );

#ifdef __cplusplus
}
#endif

#endif /* ssl_ticket.h */
