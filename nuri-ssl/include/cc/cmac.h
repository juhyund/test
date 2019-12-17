#ifndef _CMAC_H_
#define _CMAC_H_

/** @file
 * @ingroup MAC
 * CMAC�� ��ϱ� ���� �������̽�
 */

#include "cc_define.h"
#include "bcipher_op.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CMAC_Initialize PCIS_CMAC_Initialize
#define CMAC_Update PCIS_CMAC_Update
#define CMAC_Finalize PCIS_CMAC_Finalize

/** @addtogroup MAC
 * @{ */

typedef struct {
	BWT index; /**< ������Ʈ�� �� ��� ���� */
	BYTE input[BCIPHER_MAX_BLOCK_SIZE]; /**< �� �� ��� */
	BYTE cipher[BCIPHER_MAX_BLOCK_SIZE]; /**< ��ȣ�� �� ��� */
	BCipherKey *key; /**< ��Ͼ�ȣ Ű */
	BCipherContext bCtx; /**< ��Ͼ�ȣ context */
	BYTE key1[BCIPHER_MAX_KEY_SIZE]; /**< CMAC K1 */
	BYTE key2[BCIPHER_MAX_KEY_SIZE]; /**< CMAC K2 */
} CmacContext;

/** CmacContext�� �ʱ�ȭ�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS cmac context �ʱ�ȭ ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_BCIPHER_INVALID_KEY_LENGTH ���� ���� Ű ���̸� �Է��Ͽ��� ��
 * ����� ���Ű�� ZEROIZE()�� �̿��Ͽ� �������α׷����� ����ȭ�Ѵ�.
*/
LIBSPEC
ERT PCIS_CMAC_Initialize(
		CmacContext* cmCtx, /**< [out] CMAC context */
		const BYTE *key, /**< [in] ���Ű */
		BWT keyLen, /**< [in] ���Ű�� ����Ʈ ���� */
		AlgDesc bcipherAlg /**< [in] ��Ͼ�ȣ ������ */
		);

/** CmacContext�� ������Ʈ�Ѵ�.
 * �ִ� 1GB��ŭ �޽����� Update�� �� �ִ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS cmac context �������� ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
*/
LIBSPEC
ERT PCIS_CMAC_Update(
		CmacContext *cmCtx, /**< [in,out] CMAC context */
		const BYTE *msg, /**< [in] �߰� �޽��� */
		BWT msgLen /**< [in] �޽����� ����Ʈ ���� */
		);

/** ���������� CMAC ���� ���Ѵ�.
 * cmacLen�� ��Ͼ�ȣ�� ��� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS cmac context �������� ����
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_BCIPHER_INVALID_TAG_LENGTH cmacLen�� ���ũ�⺸�� ũ�� �Է��Ͽ��� ��
 */
LIBSPEC
ERT PCIS_CMAC_Finalize(
		BYTE *cmac, /**< [out] ���� MAC �� */
		BWT cmacLen, /**< [in] MAC�� ���� */
		CmacContext *cmCtx /**< [in,out] CMAC context */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif



