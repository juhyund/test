/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_FFC_H_
#define _PCIS_FFC_H_

/** @ingroup PKCRYPT
 * @defgroup FFC Finite Field Cryptography
 * @brief Cryptography based on finite field arithmetic
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "mint_common.h"

/** @addtogroup FFC
 * @{ */

/** @brief ����ü �Ķ���� */
typedef struct {
	MINT *p; /**< prime modulus */
	MINT *q; /**< factor of p-1 */
	MINT *g; /**< generator */
} PCIS_FFC_Param;

/** @brief ����ü ���� Ű �� */
typedef struct {
	MINT *x; /**< private key or info. */
	MINT *y; /**< public key or info. y = g^x mod p */
	const PCIS_FFC_Param *param; /**< parameter about generated key pair*/
} PCIS_FFC_Key;

/** @brief ����ü ���Ű */
typedef MINT PCIS_FFC_PriKey;
/** @brief ����ü ����Ű */
typedef MINT PCIS_FFC_PubKey;

/** @brief alloc new FFC parameter
 * @return [out] pointer to allocated param
 */
LIBSPEC
PCIS_FFC_Param* PCIS_FFC_Param_New(void);

/** destroy FFC parameter */
LIBSPEC
void PCIS_FFC_Param_Del(
		PCIS_FFC_Param *param /**<[in] ����ü �Ķ���� */
		);

/** @brief alloc new FFC key 
 * @return [out] pointer to allocated key
 */
LIBSPEC
PCIS_FFC_Key* PCIS_FFC_Key_New(
		PCIS_FFC_Param* param /**< [in] ����ü �Ķ���� */
		);

/** @brief destroy FFC key */
LIBSPEC
void PCIS_FFC_Key_Del(
		PCIS_FFC_Key *key /**<[in] ����ü Ű �� */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_FFC_H_ */
