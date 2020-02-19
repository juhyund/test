/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_ECKCDSA_H_
#define _PCIS_ECKCDSA_H_

#include "pkcrypt_op.h"
#include "ecc.h"
#include "ec_curve.h"
#include "hash_op.h"

/** @defgroup ECKCDSA
 * @ingroup PKCRYPT_ALG
 * @brief EC-KCDSA (Korean Certificate-based Digital Signature Algorithm using
 * Elliptic Curves)
 */

/** @file
 * @ingroup ECKCDSA
 * EC-KCDSA Signature algorithm interface
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ECKCDSA
 * @{ */

/** @brief ECKCDSA Private Key */
typedef MINT PCIS_ECKCDSA_PriKey;

/** @brief ECKCDSA Public Key */
typedef struct {
	size_t field_len; /**< advisory info about field bit-length. only used when
					 encoding or decoding a pubkey */
	PCIS_EC_Point *P;
} PCIS_ECKCDSA_PubKey;

/** ECKCDSA signature structure
 * ECKCDSA의 서명값은 두 가지값(r, s)이다.
 */
typedef struct {
	BYTE r[HASH_MAX_DIGEST_SIZE];
	MINT *s;
} PCIS_ECKCDSA_Sig;

LIBSPEC
extern PKCryptAlgorithm pcis_eckcdsa;

/** @brief ECKCDSA Algorithm descriptor alias */
#define ECKCDSA (&pcis_eckcdsa)
/** @brief ECKCDSA Algorithm descriptor alias */
#define PCIS_ECKCDSA (&pcis_eckcdsa)

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_ECKCDSA_H_ */
