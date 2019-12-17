#ifndef _FPE_OP_H_
#define _FPE_OP_H_

#include "pe_define.h"
#include "bcipher_op.h"
#include "fpe_common.h"
#include <stdio.h>

/**
 * @defgroup FPE Format-Preserving Encryption
 * @ingroup PE
 * @brief Block Cipher Mode of Operation: Format-Preserving Encryption
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup FPE
 * @brief FPE parameter set
 */
typedef struct {
	BWT radix; /**< prerequisites: aka base */
	BWT minLen; /**< prerequisites: input range min */
	BWT maxLen; /**< prerequisites: input range max */
	AlgDesc fpeAlg;
	AlgDesc bcipherAlg; /**< prerequisites: underlying block cipher */
	AlgDesc hashAlg;
	BYTE *P;
	BWT PLen;
	BCipherKey *bcKey; /**< prerequisites: key to underlying block cipher */
} FPEParameterSet;

/** @ingroup FPE */
LIBSPEC_PE
BWT POPFPE_GetMinLength(AlgDesc fpeAlg, BWT radix);

/** @ingroup FPE */
LIBSPEC_PE
BWT POPFPE_GetMaxLength(AlgDesc fpeAlg, BWT radix);

/** @ingroup FPE
    @brief FPEParameterSet�� �ʱ�ȭ�Ѵ�.
    @param param [out] �ʱ�ȭ�� FPEParameterSet�� ����Ű�� ������
    @param radix[in] �Է�, ��� ��Ʈ���� �����ϴ� Character Set�� Radix
	@param fpeAlg [in] ����� FPE �˰��� ������
    @param bcipherAlg [in] �Ϻ�ȣȭ �������� ����� ��Ͼ�ȣ �˰��� ������
    @param hashAlg [in] �Ϻ�ȣȭ �������� ����� �ؽ��Լ� �˰��� ������
    @retval ER_FPE_NULL_PARAM null parameterset pointer
    @retval ER_FPE_INVALID_RADIX invald radix value

    FPE�� ��� ���� ������ �Է¹޾� FPEParameterSet�� �ʱ�ȭ�Ѵ�.
	radix�� 2<= radix <= 0x10000 �� �����ϴ� ���������� ��ȿ�ϸ�, FPEMJ
	�˰����� ����� �� Long ������ radix�� 10���� ���� �� 8 �̸��� ���̸�
	���� ��Ʈ���� ��ȣȭ���� ���ϹǷ� �� ��쿣 Short ������ ����ؾ� �Ѵ�.
	����ϴ� ��Ͼ�ȣ �˰����� ��� ����� 128bit �̻��� �˰�������
	����ϴ� ���� �����Ѵ�. �� �� �ʱ�ȭ�� FPEParameterSet ����ü�� ��ȣȭ,
	��ȣȭ�� ��� ������� ���� �� �ִ�.
*/
LIBSPEC_PE
BWT POPFPE_Initialize(FPEParameterSet *param, BWT radix, AlgDesc fpeAlg, AlgDesc bcipherAlg, AlgDesc hashAlg);

/** @ingroup FPE
    @brief x�� �Է¹��� ��Ʈ���� ��ȣȭ�Ͽ� y���� ����Ѵ�.
    @param y [out] ��ȣȭ�� ����� ����� ���۸� ����Ű�� ������
    @param yLen [out] ��ȣȭ�� ����� ���̰� ����� ������ ������
    @param x [in] ��ȣȭ�� ��Ʈ���� ����Ǿ� �ִ� ���۸� ����Ű�� ������
    @param xLen [in] ��ȣȭ�� ��Ʈ���� ����
    @param param [in] FPEParameterSet ������
    @param key [in] Octet string Ÿ���� key binary ������
    @param keyLen [in] key material�� ����Ʈ ���� ����
    @param tweak [in] tweak ��Ʈ���� ����Ǿ� �ִ� ���۸� ����Ű�� ������
    @param tweakLen [in] tweak ��Ʈ���� ����
    @param iv [in] �̴ϼ� ����
    @retval ER_FPE_INVALID_RADIX invald radix value
    @retval ER_FPE_INVALID_X_LENGTH invald x length
    @retval ER_FPE_INVALID_Y_LENGTH invald y length
    @retval ER_FPE_INVALID_ADDITION invald blockwise addition input lenth

    \e in ���ۿ� ����Ǿ� �ִ� ��Ʈ���� FPEParameterSet�� key, tweak�� ������
    ���� ��ȣȭ�Ͽ� ����� \e out ���ۿ� ����Ѵ�. ������ ����, Octet string ������ key�� �޸�
    x, tweak�� 0x00..(0x00+radix-1) ������ Charater set���� ������ ��Ʈ���� ���¿��� ���̴�.
    ���� x, tweak�� �����ϴ� Character �߿��� 0x00+radix-1���� ū ���� ���� Charater�� ������ ��
    �������� �Ϻ�ȣȭ�� �̷���� �� ����.
    ��°��� y ���� ���� Charater set���� ������ ��Ʈ���� �����̴�.
*/
LIBSPEC_PE
BWT POPFPE_Encrypt(void *y, BWT *yLen, void *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, void *tweak, BWT tweakLen, BYTE *iv);

/** @ingroup FPE
    @brief y�� �Է¹��� ��Ʈ���� ��ȣȭ�Ͽ� x���� ����Ѵ�.
    @param x [out] ��ȣȭ�� ����� ����� ���۸� ����Ű�� ������
    @param xLen [out] ��ȣȭ�� ����� ���̰� ����� ������ ������
    @param y [in] ��ȣȭ�� ��Ʈ���� ����Ǿ� �ִ� ���۸� ����Ű�� ������
    @param yLen [in] ��ȣȭ�� ��Ʈ���� ����
    @param param [in] FPEParameterSet ������
    @param key [in] Octet string Ÿ���� key binary ������
    @param keyLen [in] key material�� ����Ʈ ���� ����
    @param tweak [in] tweak ��Ʈ���� ����Ǿ� �ִ� ���۸� ����Ű�� ������
    @param tweakLen [in] tweak ��Ʈ���� ����
    @param iv [in] �̴ϼ� ����
    @retval ER_FPE_INVALID_RADIX invald radix value
    @retval ER_FPE_INVALID_X_LENGTH invald x length
    @retval ER_FPE_INVALID_Y_LENGTH invald y length
    @retval ER_FPE_INVALID_ADDITION invald blockwise addition input lenth

    \e in ���ۿ� ����Ǿ� �ִ� ��Ʈ���� FPEParameterSet�� key, tweak�� ������
    ���� ��ȣȭ�Ͽ� ����� \e out ���ۿ� ����Ѵ�. ������ ����, Octet string ������ key�� �޸�
    y, tweak�� 0x00..(0x00+radix-1) ������ Charater set���� ������ ��Ʈ���� ���¿��� ���̴�.
    ���� y, tweak�� �����ϴ� Character �߿��� 0x00+radix-1���� ū ���� ���� Charater�� ������ ��
    �������� �Ϻ�ȣȭ�� �̷���� �� ����.
    ��°��� x ���� ���� Charater set���� ������ ��Ʈ���� �����̴�.
*/
LIBSPEC_PE
BWT POPFPE_Decrypt(void *x, BWT *xLen, void *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, void *tweak, BWT tweakLen, BYTE *iv);

BWT FSE2BT16(BT16 *y, BWT *yLen, BT16 *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, BT16 *tweak, BWT tweakLen, BYTE *iv);

BWT FSD2BT16(BT16 *x, BWT *xLen, BT16 *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, BT16 *tweak, BWT tweakLen, BYTE *iv);

BWT FSE2BYTE(BYTE *y, BWT *yLen, BYTE *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT FSD2BYTE(BYTE *x, BWT *xLen, BYTE *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT CHAR_ADD(char *a, char *b);

BWT BLOCK_ADDBT16(BT16 *a, BWT aLen, BT16 *b, BWT bLen, BWT radix);

BWT BLOCK_SUBBT16(BT16 *a, BWT aLen, BT16 *b, BWT bLen, BWT radix);

BWT BLOCK_ADDBYTE(BYTE *a, BWT aLen, BYTE *b, BWT bLen, BWT radix);

BWT BLOCK_SUBBYTE(BYTE *a, BWT aLen, BYTE *b, BWT bLen, BWT radix);

/** @ingroup FPE
 * @brief FPEParameterSet�� �ʱ�ȭ�Ѵ�(extended version).
 * @param[out] param �ʱ�ȭ�� FPEParameterSet�� ����Ű�� ������
 *
 * FPE�� ��� ���� ������ �Է¹޾� FPEParameterSet�� �ʱ�ȭ�Ѵ�.
 *
 * param�� �̸� �޸� �Ҵ��� �̷���� ���¿��� �Ѵ�.
 */
LIBSPEC_PE
BWT POPFPE_InitializeEx(FPEParameterSet *param, void *bcKey, BWT radix, BYTE *key, BWT keyLen, BYTE *tweak, BWT tweakLen, BWT inLen, AlgDesc fpeAlg, AlgDesc bcipherAlg, AlgDesc hashAlg);

/** @ingroup FPE
 * @brief x�� �Է¹��� ��Ʈ���� ��ȣȭ�Ͽ� y���� ����Ѵ�.
 * @param[out] y output ciphertext
 * @param[out] yLen output ciphertext length
 * @param[in] x input plaintext
 * @param[in] xLen input plaintext length
 * @param[in] param POPFPE_InitializeEx()�� initialize�� FPEParameterSet
 */
LIBSPEC_PE
BWT POPFPE_EncryptEx(void *y, BWT *yLen, void *x, BWT xLen, FPEParameterSet *param, void *bcKey, void *tweak, BWT tweakLen, BYTE *iv);

/** @ingroup FPE
 * @brief y�� �Է¹��� ��Ʈ���� ��ȣȭ�Ͽ� x���� ����Ѵ�.
 * @param[out] x
 * @param[out] xLen
 * @param[in] y
 * @param[in] yLen
 * @param[in] param POPFPE_InitializeEx()�� initialize�� FPEParameterSet
 */
LIBSPEC_PE
BWT POPFPE_DecryptEx(void *x, BWT *xLen, void *y, BWT yLen, FPEParameterSet *param, void *bcKey, void *tweak, BWT tweakLen, BYTE *iv);

/** @ingroup FPE */
LIBSPEC_PE
void FPEParameterSet_Free(FPEParameterSet *param);

BWT FSE2BYTEEX(BYTE *y, BWT *yLen, BYTE *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT FSD2BYTEEX(BYTE *x, BWT *xLen, BYTE *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT FSE2BT16EX(BT16 *y, BWT *yLen, BT16 *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT FSD2BT16EX(BT16 *x, BWT *xLen, BT16 *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

#ifdef __cplusplus
}
#endif

#endif /* _FPE_OP_H_ */
