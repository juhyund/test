/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_ECDH_H_
#define _PCIS_ECDH_H_

#include "ecc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ECDH
 * @ingroup PKCRYPT
 * @brief ECDH (Elliptic-Curve Diffie-Hellmen) Key Agreement
 */

/** @file
 * @brief ECDH interface definitions
 * @ingroup ECDH
 */

/** @addtogroup ECDH
 * @{ */

/** @brief set ECDH parameter
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
*/
LIBSPEC
ERT PCIS_ECDH_SetParam(
		PCIS_ECC_Param *param, /**< [out] ECHD �Ķ���� */
		unsigned int curve_id /**< [in] Ÿ�� � Ŀ�� ���� */
		);

/**
 * @brief generate ECDH key pair
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_CONDITIONAL_SELFTEST Ű�� ��ġ ���� �����Ͽ��� ���
 */
LIBSPEC
ERT PCIS_ECDH_GenKey(
		PCIS_ECC_Key *key /**< [in,out] ����ü ���� Ű �� */
		);

/**
 * @brief compute ECDH shared key from two peer keys
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 */
LIBSPEC
ERT PCIS_ECDH_ComputeSharedKey(
		PCIS_EC_Point *shared, /**< [out] computed shared key */
		PCIS_ECC_Key *myKey, /**< [in] receiver's key */
		PCIS_EC_Point *peerKey /**< [in] sender's key */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_ECDH_H_ */
