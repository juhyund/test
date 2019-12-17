/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_ECC_H_
#define _PCIS_ECC_H_

/** @ingroup PKCRYPT
 * @defgroup ECC Elliptic Curve Cryptography
 * @brief Cryptography based on elliptic curve arithmetic
 *
 * All functions except PCIS_ECC_GenKey() and PCIS_ECC_CheckKey() can be
 * commonly used for ECDSA, ECKCDSA and ECDH. PCIS_ECC_GenKey() and
 * PCIS_ECC_CheckKey() can be commonly used for ECDSA and ECDH, but for ECKCDSA
 * there are dedicated functions PCIS_ECKCDSA_GenKey() and
 * PCIS_ECKCDSA_CheckKey().
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ec_common.h"
#include "ec_curve.h"

/** @addtogroup ECC
 * @{ */

/** @brief ECC domain parameter used in ECDSA, ECKCDSA and ECDH */
typedef struct {
	PCIS_EC_Group* ec_group; /**< elliptic curve group */
} PCIS_ECC_Param;

/** @brief ECC 개인키 */
typedef MINT PCIS_ECC_PriKey;

/** @brief ECC 공캐키 */
typedef struct {
	size_t field_len; /**< advisory info about field bit-length. only used when
					 encoding or decoding a pubkey */
	PCIS_EC_Point *P; /**< generator */
} PCIS_ECC_PubKey;

/** @brief ECC key pair */
typedef struct {
	PCIS_ECC_PriKey *x; /**< 개인키 */
	PCIS_ECC_PubKey *y; /**< 공개키 */
	const PCIS_ECC_Param *param; /**< ECC 파라미터 */
} PCIS_ECC_Key;

/**
 * @brief alloc new ECC parameter
 * @return [out] pointer to allocated param
 * @sa PCIS_ECC_Param
 */
LIBSPEC
PCIS_ECC_Param* PCIS_ECC_Param_New(void);

/**
 * @brief destroy ECC parameter
 * @sa PCIS_ECC_Param
 *
 * Safe to pass NULL pointer
 */
LIBSPEC
void PCIS_ECC_Param_Del(
		PCIS_ECC_Param *param /**<[in] ECC 파라미터 */
		);

/** @brief alloc new ECC key
 * @return [out] pointer to allocated key
 */
LIBSPEC
PCIS_ECC_Key* PCIS_ECC_Key_New(
		PCIS_ECC_Param *param /**< [in] ECC 파라미터 */
		);

/** destroy ECC key */
LIBSPEC
void PCIS_ECC_Key_Del(
		PCIS_ECC_Key *key /**<[in] ECC 키 */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_ECC_H_ */
