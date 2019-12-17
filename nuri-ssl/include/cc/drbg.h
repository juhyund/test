#ifndef _DRBG_H_
#define _DRBG_H_

/** @defgroup RNG Random Number
 * @ingroup CC
 * @brief Random Number Generation
 */

#include <stdio.h>
#include "mint_common.h"
#include "hash_op.h"
#include "bcipher_op.h"

/** @file
 * @ingroup RNG
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup HASHDRBG HASHDRBG
 * @ingroup RNG
 * @brief HASHDRBG algorithm
 */

/** @defgroup HMACDRBG HMACDRBG
 * @ingroup RNG
 * @brief HMACDRBG algorithm
 */

/** @defgroup CTRDRBG CTRDRBG
 * @ingroup RNG
 * @brief CTRDRBG algorithm
 */

#define HASH_MAX_OUT_LEN 64
#define MAX_BLOCK_LEN 32
#define RESEED_INTERVAL 16

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/** @ingroup HASHDRBG
 * @brief HASH_DRBG instance state */
typedef struct {
	BYTE V[112]; /**< ���� ���� */
	BYTE C[112]; /**< ���� ���� */
	BWT reseed_counter; /**< reseed ���� Ƚ�� */
	BWT reseed_interval; /**< reseed �ִ� Ƚ�� */
	BWT seedLen; /**< V, C�� ���� ��� ũ�� */
	BWT prediction_resistance_flag; /**< ���� ���� ���� */
	BYTE prev_rand[2050]; /**< ���� ��� ���� */
	AlgDesc hashAlg; /**< �˰��� ������ */
} HashDrbgState;

/** @ingroup HMACDRBG
 * @brief HMAC_DRBG instance state */
typedef struct {
	BYTE V[64]; /**< ���� ���� */
	BYTE Key[64]; /**< HMAC Ű */
	BWT outLen; /**< V�� ���� ��� ũ�� */
	BWT reseed_counter; /**< reseed ���� Ƚ�� */
	BWT reseed_interval; /**< reseed �ִ� Ƚ�� */
	BWT prediction_resistance_flag; /**< ���� ���� ���� */
	BYTE prev_rand[2050]; /**< ���� ��� ���� */
	AlgDesc hashAlg; /**< �˰��� ������ */
} HmacDrbgState;

/** @ingroup CTRDRBG
 * @brief CTR_DRBG instance state */
typedef struct {
	BYTE V[112]; /**< ���� ���� */
	BYTE Key[112]; /**< BCIPHER Ű */
	BWT reseed_counter; /**< reseed ���� Ƚ�� */
	BWT reseed_interval; /**< reseed �ִ� Ƚ�� */
	BWT blockLen; /**< BCIPHER ��� ũ�� */
	BWT keyLen; /**< Key�� ���� ũ�� */
	BWT prediction_resistance_flag; /**< ���� ���� ���� */
	BWT df_flag; /**< ���� �Լ� ��� ���� */
	BYTE prev_rand[2050]; /**< ���� ��� ���� */
	AlgDesc bcipherAlg; /**< �˰��� ������ */
} CtrDrbgState;

/** @ingroup RNG */
enum
{
	ALG_SHA224 = 0,
	ALG_SHA256,
	ALG_SHA384,
	ALG_SHA512,
	ALG_SEED,
	ALG_HIGHT,
	ALG_ARIA,
	ALG_ARIA192,
	ALG_ARIA256,
	ALG_LEA128,
	ALG_LEA192,
	ALG_LEA256
};

/** @addtogroup HASHDRBG
 * @{ */

/** @brief ���� HASHDRBG instance�κ��� ������ �߻��Ѵ�. */
LIBSPEC
ERT HASHDRBG_GetRandNum(
		BYTE* rand, /**< [out] ������ ������ ����� ���۸� ����Ű�� ������ */
		BWT randBitLen /**< [in] ������ ������ ��Ʈ ���� ���� */
		);

/** @ingroup CC
 * @brief ���� HASHDRBG ���� ���¸� ����ȭ�Ѵ�. */
LIBSPEC
void PCIS_CC_InternalDrbgZeroize(void);

/** @brief �־��� HASHDRBG instance�� �ʱ�ȭ�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ���� ���� ����
 * @retval ER_NULL_STATE HashDrbgState �ν��Ͻ�ȭ�� context �޸𸮰� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * nonce�� pers�� ��� ������ ���� ������ �����ִ� ������ �ϸ� NULL�� �Է��ص�
 * ������ �����ȴ�.
 */
LIBSPEC
ERT HASHDRBG_Instantiate(
		HashDrbgState *drbg, /**< [out] �ʱ�ȭ�ϰ��� �ϴ� HASHDRBG instance */
		BWT hashAlg, /**< [in] ����� �ؽ� �Լ� �˰��� ������
					   (SHA224, SHA256, SHA384, SHA512 �� �ϳ�) */
		BWT pResist, /**< [in] ���� ���� ���� (TRUE, FALSE �� �� �� �ϳ�) */
		BYTE *nonce, /**< [in] �ʱ�ȭ�� ����� �� */
		BWT nonceLen, /**< [in] ���� ����Ʈ ���� ���� */
		BYTE *pers, /**< [in] �ʱ�ȭ�� ����� ����ȭ ���ڿ� */
		BWT persLen /**< [in] ����ȭ ���ڿ��� ����Ʈ ���� ���� */
		);

/** @brief �־��� HASHDRBG instance�� Reseeding�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ���� ���� ����
 * @retval ER_NULL_STATE HashDrbgState context�� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_REQUEST_TOO_LONG_RANDOM 16384��Ʈ���� �� ���� �߻��� �䱸�Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * addString�� Reseeding �������� ���� ���� ���� ������ ���⵵�� �ϸ�, NULL��
 * �Է��ص� Reseeding�� �����ϴ�.
 *
 * instance �ʱ�ȭ �� ���� ���� �÷��׸� TRUE�� �Է��ϸ� HASHDRBG_GenerateRand
 * ���ο��� �� ���� �����ø��� Reseeding�� �̷��������, FALSE�� ���
 * reseed_interval��ŭ ȣ��� ��츦 �����ϰ�� Reseeding�� �̷������ �ʱ�
 * ������ �ʿ��� ��쿣 ���� �Լ��� ȣ���Ͽ� Reseeding�� ���ֵ��� �Ѵ�.
 */
LIBSPEC
ERT HASHDRBG_Reseed(
		HashDrbgState *drbg, /**< [in,out] Reseeding�� DRBG instance */
		BYTE *addString, /**< [in] Reseeding�� �ʿ��� �߰� ���ڿ� */
		BWT addLen /**< [in] �߰� ���ڿ��� ����Ʈ ���� ���� */
		);

/** @brief �־��� HASHDRBG instance�κ��� ������ �߻��Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ���� ���� ����
 * @retval ER_NULL_STATE HashDrbgState context�� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_REQUEST_TOO_LONG_RANDOM 16384��Ʈ���� �� ���� �߻��� �䱸�Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * addString�� reseeding�� �̷������ ��쿡 �ʿ��ϴ�. HASHDRBG_GenerateRand
 * ���ο��� Reseeding�� �̷������ ���� ���� ���� ���ΰ� TRUE�̰ų�,
 * reseed_counter ���� reseed_interval ���� ������ ��찡 �ִ�.
 */
LIBSPEC
ERT HASHDRBG_GenerateRand(
		BYTE *rand, /**< [out] ������ ������ ����� ���۸� ����Ű�� ������ */
		HashDrbgState *drbg, /**< [in,out] ����� DRBG instance */
		BWT bitNo, /**< [in] ������ ������ ��Ʈ ���� ����, �ִ� 16384(��Ʈ) */
		BYTE *addString, /**< [in] reseeding�� �ʿ��� �߰� ���ڿ� */
		BWT addLen /**< [in] �߰� ���ڿ��� ����Ʈ ���� ���� */
		);

/** @ingroup ZERO
 * @brief HASHDRBG�� ���� ���¸� ����ȭ�Ѵ�. */
LIBSPEC
void HASHDRBG_Zeroize(
		HashDrbgState *drbg /**< [in] ����� DRBG instance*/
		);

/** @} */

/** @addtogroup HMACDRBG
 * @{ */

#define HMACDRBG_GetRandNum HASHDRBG_GetRandNum

/** @brief �־��� HMACDRBG instance�� �ʱ�ȭ�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ���� ���� ����
 * @retval ER_NULL_STATE HmacDrbgState �ν��Ͻ�ȭ�� context �޸𸮰� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * nonce�� pers�� ��� ������ ���� ������ �����ִ� ������ �ϸ� NULL�� �Է��ص�
 * ������ �����ȴ�.
 */
LIBSPEC
ERT HMACDRBG_Instantiate(
		HmacDrbgState *drbg, /**< [out] �ʱ�ȭ�ϰ��� �ϴ� HMACDRBG instance */
		BWT hashAlg, /**< [in] ����� �ؽ� �Լ� �˰��� ������
					   (SHA224, SHA256, SHA384, SHA512 �� �ϳ�) */
		BWT pResist, /**< [in] ���� ���� ����, (TRUE, FALSE �� �� �� �ϳ�) */
		BYTE *nonce, /**< [in] �ʱ�ȭ�� ����� �� */
		BWT nonceLen, /**< [in] ���� ����Ʈ ���� ���� */
		BYTE *pers, /**< [in] �ʱ�ȭ�� ����� ����ȭ ���ڿ� */
		BWT persLen /**< [in] ����ȭ ���ڿ��� ����Ʈ ���� ���� */
		);

/** @brief �־��� HMACDRBG instance�� Reseeding�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ���� ���� ����
 * @retval ER_NULL_STATE HmacDrbgState context�� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * addString�� Reseeding �������� ���� ���� ���� ������ ���⵵�� �ϸ�, NULL��
 * �Է��ص� Reseeding�� �����ϴ�.
 *
 * instance �ʱ�ȭ �� ���� ���� �÷��׸� TRUE�� �Է��ϸ� HMACDRBG_GenerateRand
 * ���ο��� �� ���� �����ø��� Reseeding�� �̷��������, FALSE�� ���
 * reseed_interval��ŭ ȣ��� ��츦 �����ϰ�� Reseeding�� �̷������ �ʱ�
 * ������ �ʿ��� ��쿣 ���� �Լ��� ȣ���Ͽ� Reseeding�� ���ֵ��� �Ѵ�.
 */
LIBSPEC
ERT HMACDRBG_Reseed(
		HmacDrbgState *drbg, /**< [in,out] Reseeding�� DRBG instance */
		BYTE *addString, /**< [in] Reseeding�� �ʿ��� �߰� ���ڿ� */
		BWT addLen /**< [in] �߰� ���ڿ��� ����Ʈ ���� ���� */
		);

/** @brief �־��� HMACDRBG instance�κ��� ������ �߻��Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ���� ���� ����
 * @retval ER_NULL_STATE HmacDrbgState context�� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_REQUEST_TOO_LONG_RANDOM 16384��Ʈ���� �� ���� �߻��� �䱸�Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * addString�� reseeding�� �̷������ ��쿡 �ʿ��ϴ�. HMACDRBG_GenerateRand
 * ���ο��� Reseeding�� �̷������ ���� ���� ���� ���ΰ� TRUE�̰ų�,
 * reseed_counter ���� reseed_interval ���� ������ ��찡 �ִ�.
 */
LIBSPEC
ERT HMACDRBG_GenerateRand(
		BYTE *rand, /**< [out] ������ ������ ����� ���۸� ����Ű�� ������ */
		HmacDrbgState *drbg, /**< [in,out] ����� DRBG instance */
		BWT bitNo, /**< [in] ������ ������ ��Ʈ ���� ����, �ִ� 16384(��Ʈ) */
		BYTE *addString, /**< [in] reseeding�� �ʿ��� �߰� ���ڿ� */
		BWT addLen /**< [in] �߰� ���ڿ��� ����Ʈ ���� ���� */
		);

/** @ingroup ZERO
 * @brief HMACDRBG�� ���� ���¸� ����ȭ�Ѵ�. */
LIBSPEC
void HMACDRBG_Zeroize(
		HmacDrbgState *drbg /**< [in] ����� DRBG instance*/
		);

/** @} */

/** @addtogroup CTRDRBG
 * @{ */

/** @brief �־��� CTRDRBG instance�� �ʱ�ȭ�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS CtrDrbgState �ν��Ͻ�ȭ ����
 * @retval ER_NULL_STATE CtrDrbgState �ν��Ͻ�ȭ�� context �޸𸮰� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * nonce�� pers�� ��� ������ ���� ������ �����ִ� ������ �ϸ� NULL�� �Է��ص�
 * ������ �����ȴ�.
*/
LIBSPEC
ERT CTRDRBG_Instantiate(
		CtrDrbgState *drbg, /**< [out] �ʱ�ȭ�ϰ��� �ϴ� CTRDRBG instance*/
		BWT bcipherAlg, /**< [in] ����� ��� ��ȣ �˰��� ������
					   (SEED, HIGHT, ARIA, ARIA192, ARIA256, LEA128, LEA192, LEA256 �� �ϳ�)*/
		BWT pResist, /**< [in] ���� ���� ����, (TRUE, FALSE �� �� �� �ϳ�)*/
		BWT pDf, /**< [in] ���� �Լ� ��� ����, (TRUE, FALSE �� �� �� �ϳ�)*/
		BYTE *nonce, /**< [in] �ʱ�ȭ�� ����� ��*/
		BWT nonceLen, /**< [in] ���� ����Ʈ ���� ����*/
		BYTE *pers, /**< [in] �ʱ�ȭ�� ����� ����ȭ ���ڿ�*/
		BWT persLen /**< [in] ����ȭ ���ڿ��� ����Ʈ ���� ����*/
		);

/** @brief �־��� CTRDRBG instance�� Reseeding�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ���� ���� ����
 * @retval ER_NULL_STATE CtrDrbgState context�� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * addString�� Reseeding �������� ���� ���� ���� ������ ���⵵�� �ϸ�, NULL��
 * �Է��ص� Reseeding�� �����ϴ�.
 *
 * instance �ʱ�ȭ �� ���� ���� �÷��׸� TRUE�� �Է��ϸ� CTRDRBG_GenerateRand
 * ���ο��� �� ���� �����ø��� Reseeding�� �̷��������, FALSE�� ���
 * reseed_interval��ŭ ȣ��� ��츦 �����ϰ�� Reseeding�� �̷������ �ʱ�
 * ������ �ʿ��� ��쿣 ���� �Լ��� ȣ���Ͽ� Reseeding�� ���ֵ��� �Ѵ�.
*/
LIBSPEC
ERT CTRDRBG_Reseed(
		CtrDrbgState *drbg, /**< [in,out] Reseeding�� DRBG instance */
		BYTE *addString, /**< [in] Reseeding�� �ʿ��� �߰� ���ڿ� */
		BWT addLen /**< [in] �߰� ���ڿ��� ����Ʈ ���� ���� */
		);

/** @brief �־��� CTRDRBG instance�κ��� ������ �߻��Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ���� ���� ����
 * @retval ER_NULL_STATE CtrDrbgState context�� null�� ��
 * @retval ER_INVALID_BLOCKCIPHER_ALG Ÿ������ ���� ��� ��ȣ �˰����� �Է��Ͽ��� ��
 * @retval ER_REQUEST_TOO_LONG_RANDOM 16384��Ʈ���� �� ���� �߻��� �䱸�Ͽ��� ��
 * @retval ER_FAULT_DETECTION_RBG �����߻��� ���� Ž�� ���迡 �����Ͽ��� ��
 * 
 * addString�� reseeding�� �̷������ ��쿡 �ʿ��ϴ�. CTRDRBG_GenerateRand
 * ���ο��� Reseeding�� �̷������ ���� ���� ���� ���ΰ� TRUE�̰ų�,
 * reseed_counter ���� reseed_interval ���� ������ ��찡 �ִ�.
*/
LIBSPEC
ERT CTRDRBG_GenerateRand(
		BYTE *rand, /**< [out] ������ ������ ����� ���۸� ����Ű�� ������ */
		CtrDrbgState *drbg, /**< [in,out] ����� DRBG instance */
		BWT bitNo, /**< [in] ������ ������ ��Ʈ ���� ����, �ִ� 16384(��Ʈ) */
		BYTE *addString, /**< [in] reseeding�� �ʿ��� �߰� ���ڿ� */
		BWT addLen /**< [in] �߰� ���ڿ��� ����Ʈ ���� ���� */
		);

/** @ingroup ZERO
 * @brief HASHDRBG�� ���� ���¸� ����ȭ�Ѵ�. */
LIBSPEC
void CTRDRBG_Zeroize(
		CtrDrbgState *drbg /**< [in] ����� DRBG instance*/
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
