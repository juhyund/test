/**
 * \file version.h
 *
 * \brief Run-time version information
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
/*
 * This set of compile-time defines and run-time variables can be used to
 * determine the version number of the penta TLS library used.
 */
#ifndef PTLS_VERSION_H
#define PTLS_VERSION_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

/**
 * The version number x.y.z is split into three parts.
 * Major, Minor, Patchlevel
 */
#define PTLS_VERSION_MAJOR  2
#define PTLS_VERSION_MINOR  13
#define PTLS_VERSION_PATCH  0

/**
 * The single version number has the following structure:
 *    MMNNPP00
 *    Major version | Minor version | Patch version
 */
#define PTLS_VERSION_NUMBER         0x020D0000
#define PTLS_VERSION_STRING         "2.13.0"
#define PTLS_VERSION_STRING_FULL    "penta TLS 2.13.0"

#if defined(PTLS_VERSION_C)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the version number.
 *
 * \return          The constructed version number in the format
 *                  MMNNPP00 (Major, Minor, Patch).
 */
unsigned int ptls_version_get_number( void );

/**
 * Get the version string ("x.y.z").
 *
 * \param string    The string that will receive the value.
 *                  (Should be at least 9 bytes in size)
 */
void ptls_version_get_string( char *string );

/**
 * Get the full version string ("penta TLS x.y.z").
 *
 * \param string    The string that will receive the value. The penta TLS version
 *                  string will use 18 bytes AT MOST including a terminating
 *                  null byte.
 *                  (So the buffer should be at least 18 bytes to receive this
 *                  version string).
 */
void ptls_version_get_string_full( char *string );

/**
 * \brief           Check if support for a feature was compiled into this
 *                  penta TLS binary. This allows you to see at runtime if the
 *                  library was for instance compiled with or without
 *                  Multi-threading support.
 *
 * \note            only checks against defines in the sections "System
 *                  support", "penta TLS modules" and "penta TLS feature
 *                  support" in config.h
 *
 * \param feature   The string for the define to check (e.g. "PTLS_AES_C")
 *
 * \return          0 if the feature is present,
 *                  -1 if the feature is not present and
 *                  -2 if support for feature checking as a whole was not
 *                  compiled in.
 */
int ptls_version_check_feature( const char *feature );

#ifdef __cplusplus
}
#endif

#endif /* PTLS_VERSION_C */

#endif /* version.h */
