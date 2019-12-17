/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_DH_H_
#define _PCIS_DH_H_

/** @defgroup DH
 * @ingroup PKCRYPT
 * @brief DH (Diffie-Hellman) Key Agreement
 */

/** @file
 * @ingroup DH
 */

#include "ffc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup DH
 * @{ */

typedef struct {
	MINT p; /**< �ý��� �Ķ���� p */
	MINT q; /**< �ý��� �Ķ���� q */
	MINT g; /**< �ý��� �Ķ���� g */
	MINT x;    /**< �ڽ��� private info or private key */
	MINT yR;   /**< ������ public info or public key */
	BWT  keyLen;         /**< Ű������ ����� Ű���� */
	const void *hashAlg; /**< Ű������ ����� �ؽ� �˰��� ��ũ���� */
} KEDH_Context;

/** @brief DH context�� �ʱ�ȭ�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS dh context �ʱ�ȭ ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
*/
LIBSPEC
ERT PCIS_DH_Initialize(
		KEDH_Context *ctx, /**< [out] context */
		MINT *p, /**< [in] parameter p */
		MINT *q, /**< [in] parameter q */
		MINT *g, /**< [in] parameter g */
		MINT *x, /**< [in] optional private key */
		MINT *yR /**< [in] optional peer public key */
		);

/** @brief context�� ���Ű�� �����Ͽ� �����ϰ�, �ش� ����Ű(y)�� ����
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS �ڽ��� ����Ű ���� ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 */
LIBSPEC
ERT PCIS_DH_GenShareInfo(
		KEDH_Context *ctx, /**< [in,out] context ���� �����߻��⸦ �̿��Ͽ� ����Ű(��������)�� �����Ͽ� ����� */
		MINT *y /**< [out] ������ ����Ű(��������) */
		);

/** @brief context�� ����� �ڽ��� ���Ű�� �Է��� ������ ����Ű�� �̿��Ͽ� ���� ����Ű(zz)�� ����
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ����Ű ���� ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 */
LIBSPEC
ERT PCIS_DH_GetKey(
		KEDH_Context *ctx, /**< [in] context */
		MINT *yR, /**< [in] ������ ����Ű(��������) */
		MINT *zz /**< [out] ���� ����Ű */
		);

/** @brief generate DH parameter 
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS DH �Ķ���� ���� ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
*/
LIBSPEC
ERT PCIS_DH_GenParam(
		PCIS_FFC_Param *param, /**< [out] parameter to be generated */
		BWT pLen, /**< [in] desired length of P */
		BWT qLen /**< [in] desired length of Q */
		);

/** @brief set DH parameter 
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS DH �Ķ���� ���� ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
*/
LIBSPEC
ERT PCIS_DH_SetParam(
		PCIS_FFC_Param *param, /**< [out] target parameter */
		const MINT *p, /**< [in] prime modulus */
		const MINT *q, /**< [in] factor of p-1 */
		const MINT *g /**< [in] generator */
		);

/** @brief generate DH key pair 
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS DH Ű�� ���� ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_CONDITIONAL_SELFTEST Ű�� ��ġ ���� �����Ͽ��� ���
 */
LIBSPEC
ERT PCIS_DH_GenKey(
		PCIS_FFC_Key *key /**< [in,out] ����ü ���� Ű �� */
		);

/** @brief compute DH shared key from two peer keys
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ����Ű ���� ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
*/
LIBSPEC
ERT PCIS_DH_ComputeSharedKey(
		MINT *shared, /**< [out] ���� ����Ű */
		PCIS_FFC_Key *myKey, /**< [in] �ڽ��� ���Ű(�������) */
		MINT *peerKey /**< [in] ������ ����Ű(��������) */
		);

/** @brief wipe DH private key */
LIBSPEC
void PCIS_DH_WipeKey(
		KEDH_Context *ctx /**< [in] DH context */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_DH_H_ */
