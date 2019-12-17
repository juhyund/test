/**
 * \file havege.h
 *
 * \brief HAVEGE: HArdware Volatile Entropy Gathering and Expansion
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
#ifndef PTLS_HAVEGE_H
#define PTLS_HAVEGE_H

#include <stddef.h>

#define PTLS_HAVEGE_COLLECT_SIZE 1024

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          HAVEGE state structure
 */
typedef struct ptls_havege_state
{
    int PT1, PT2, offset[2];
    int pool[PTLS_HAVEGE_COLLECT_SIZE];
    int WALK[8192];
}
ptls_havege_state;

/**
 * \brief          HAVEGE initialization
 *
 * \param hs       HAVEGE state to be initialized
 */
void ptls_havege_init( ptls_havege_state *hs );

/**
 * \brief          Clear HAVEGE state
 *
 * \param hs       HAVEGE state to be cleared
 */
void ptls_havege_free( ptls_havege_state *hs );

/**
 * \brief          HAVEGE rand function
 *
 * \param p_rng    A HAVEGE state
 * \param output   Buffer to fill
 * \param len      Length of buffer
 *
 * \return         0
 */
int ptls_havege_random( void *p_rng, unsigned char *output, size_t len );

#ifdef __cplusplus
}
#endif

#endif /* havege.h */
