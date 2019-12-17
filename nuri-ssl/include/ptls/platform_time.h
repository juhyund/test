/**
 * \file platform_time.h
 *
 * \brief penta TLS Platform time abstraction
 */
/*
 *  Copyright (C) 2006-2016, ARM Limited, All Rights Reserved
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
#ifndef PTLS_PLATFORM_TIME_H
#define PTLS_PLATFORM_TIME_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name SECTION: Module settings
 *
 * The configuration options you can set for this module are in this section.
 * Either change them in config.h or define them on the compiler command line.
 * \{
 */

/*
 * The time_t datatype
 */
#if defined(PTLS_PLATFORM_TIME_TYPE_MACRO)
typedef PTLS_PLATFORM_TIME_TYPE_MACRO ptls_time_t;
#else
/* For time_t */
#include <time.h>
typedef time_t ptls_time_t;
#endif /* PTLS_PLATFORM_TIME_TYPE_MACRO */

/*
 * The function pointers for time
 */
#if defined(PTLS_PLATFORM_TIME_ALT)
extern ptls_time_t (*ptls_time)( ptls_time_t* time );

/**
 * \brief   Set your own time function pointer
 *
 * \param   time_func   the time function implementation
 *
 * \return              0
 */
int ptls_platform_set_time( ptls_time_t (*time_func)( ptls_time_t* time ) );
#else
#if defined(PTLS_PLATFORM_TIME_MACRO)
#define ptls_time    PTLS_PLATFORM_TIME_MACRO
#else
#define ptls_time   time
#endif /* PTLS_PLATFORM_TIME_MACRO */
#endif /* PTLS_PLATFORM_TIME_ALT */

#ifdef __cplusplus
}
#endif

#endif /* platform_time.h */
