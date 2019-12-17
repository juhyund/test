/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_LSH_H_
#define _PCIS_LSH_H_

/** @defgroup LSH LSH
 * @ingroup HASH_ALG
 * @brief LSH (Lightweight Secure Hash)
 *
 * Contains LSH-224, LSH-256, LSH-512-224, LSH-512-256, LSH-384, LSH-512.
 * Strict names are LSH-256-224, LSH-256-256, LSH-512-224, LSH-512-256,
 * LSH-512-384, LSH-512-512.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "hash_op.h"

/** @addtogroup LSH
 * @{ */
LIBSPEC
extern HashAlgorithm pcis_lsh224;

LIBSPEC
extern HashAlgorithm pcis_lsh256;

LIBSPEC
extern HashAlgorithm pcis_lsh512_224;

LIBSPEC
extern HashAlgorithm pcis_lsh512_256;

LIBSPEC
extern HashAlgorithm pcis_lsh384;

LIBSPEC
extern HashAlgorithm pcis_lsh512;

#define LSH224 &pcis_lsh224
#define LSH256 &pcis_lsh256
#define LSH512_224 &pcis_lsh512_224
#define LSH512_256 &pcis_lsh512_256
#define LSH384 &pcis_lsh384
#define LSH512 &pcis_lsh512

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_LSH_H_ */
