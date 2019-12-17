#ifndef _BCIPHER_OP_H_
#define _BCIPHER_OP_H_

/** @defgroup BCIPHER Block Cipher
 * @ingroup CC
 * @brief Block Cipher
 */ 

/** @defgroup BCIPHER_ALG Algorithm Descriptors
 * @ingroup BCIPHER
 * @brief BCIPHER Algorithm Descriptors
 */

/** @file bcipher_op.h
 * @ingroup BCIPHER
 * @brief ��Ͼ�ȣ ���񽺸� �̿��ϱ� ���� API
 */

#include "cc_define.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BCIPHER
 * @{ */

/** No padding */
#define NPAD		0 
/** PKCS5 and PKCS7 padding */
#define PAD_PKCS7	1
/** X9.23 padding.
 * not popular compared to PKCS7 padding method */
#define PAD_X9_23	2
/** for compatibility */
#define PAD PAD_PKCS7

/** ��� ��ȣ�� ���Ű�� ����� �� �ִ� �ִ� ����Ʈ ũ�� */
#define BCIPHER_MAX_KEY_SIZE          32
/** ��� ��ȣ�� �̿��� �޽��� ������ �±� ������ �ִ� ����Ʈ ũ�� */
#define BCIPHER_MAX_TAG_SIZE          16
/** ��� ��ȣ ���忡���� �ʱ� ������ �ִ� ����Ʈ ũ�� */
#define BCIPHER_MAX_IV_SIZE           16
/** ��� ��ȣ�� ����� �ִ� ����Ʈ ũ�� */
#define BCIPHER_MAX_BLOCK_SIZE        16
/** ��� ��ȣ�� ����� 32��Ʈ �� �ִ� ũ�� */
#define BCIPHER_MAX_BLOCK_BT32_SIZE    4

/** @name Modes of operation
 * @{ */

/** @brief ECB mode
 *
 * Chaining vector ���� �� block�� ���������� ��ȣȭ�Ѵ�. ����, \e
 * MODE_ECB�� \e BCIPHER_Initialize �� ������ \e iv���� NULL�� �Ѱ��ָ� �ȴ�.
 * (\e iv �� initiali vecotr�� ���ڷ� chaining vector�� �ʱⰪ�� �ǹ��Ѵ�.)
 * MODE_ECB�� ������ ������ ��忡���� ��� chaining vector�� ����ϹǷ� \e iv
 * ���� �����ϴ� ���� �ʿ��ϴ�. ����, NULL���� �ָ� iv �� ����Ʈ�� 0����
 * ���õ�����, ���� ���鿡�� iv �� key ��ŭ �߿��� ���̹Ƿ� key�� ����������
 * ������ ���� �־����� �ϰ� ����, ����� �����Ǿ�� �Ѵ�.
 * @sa BCIPHER_Initialize
 */
#define MODE_ECB        1
/** @brief CBC mode.
 *
 * CBC ����� ���Ǵ� ������ ����.
 * - Chaining vector�� plain text�� exclusive OR �� ���� ��ȣȭ�Ͽ� cipher
 *   text�� �����Ѵ�.
 * - Chaining vector�� ���� plain text�� cipher text�̴�.
 * - Chaining vector�� �ʱⰪ�� \e BCIPHER_Intialize �Լ��� \e iv ������
 *   �־�����.
 *
 * Chaining vector���� \e BCipherContext�� �����ǹǷ�, ��ȣȭ��
 * BCipherContext�� ��ȣȭ�� BCipherContext�� ������ �ʱ�ȭ�Ͽ� ����Ͽ���
 * �Ѵ�. MODE_ECB�� ������ �ٸ� ��� ��忡���� chaining vector�� ����ϹǷ�
 * ���� �Ϻ�ȣȭ�� Context�� ���� ���� ��Ͽ��� �Ѵ�.
 * @sa BCIPHER_Initialize
 */
#define MODE_CBC        2
/** @brief CFB mode with full block feedback.
 *
 * �Ϲ����� CFB ����� ���ǿ� ���� �������� ���Ǵ� ������ ����.
 * - Chaining vector�� ��ȣȭ�� �� �� ���� j-bits�� plain text j-bits��
 *   EXOR�Ͽ� cipher text j-bits�� �����Ѵ�.
 * - Chaining vector�� ���� chaing vector�� j-bits��ŭ shift�� ����, ����
 *   j-bits�� ���� cipher text�� ��ü�Ѵ�.
 *
 * MODE_CFB�� �ǹ��ϴ� �ٴ� ���� ���� �� j-bits�� ����ϴ� �˰����� ��
 * ũ��� ������ ���� ��带 �ǹ��Ѵ�. feedback ũ�Ⱑ �ٸ� �ٸ� ����
 * MODE_CFB_BYTE�� MODE_CFB1�� �����Ѵ�.
 * @sa BCIPHER_Initialize, MODE_CFB_BYTE
 */
#define MODE_CFB        3
/** @brief CFB mode with byte feedback.
 *
 * MODE_CFB���� ������ CFB ����� ���� ��, j-bits�� 8-bits ��, 1 ����Ʈ�� ����
 * ����̴�.
 * @sa BCIPHER_Initialize, MODE_CFB
 */
#define MODE_CFB_BYTE   4
/** @brief OFB mode with full block feedback.
 *
 * �Ϲ����� OFB ����� ���ǿ� ���� �������� ���Ǵ� ������ ����.
 * - Chaining vector�� ��ȣȭ�� �� �� ���� j-bits�� plain text j-bits��
 *   EXOR�Ͽ� cipher text j-bits�� �����Ѵ�.
 * - Chaining vector�� ���� chaing vector�� j-bits��ŭ shift�� ����, ����
 *   j-bits�� ���� pain text�� EXOR�� j-bits���� ��ü�Ѵ�.
 *
 * MODE_OFB�� �ǹ��ϴ� �ٴ� ���� ���� �� j-bits�� ����ϴ� �˰����� ��
 * ũ��� ������ ���� ��带 �ǹ��Ѵ�.
 * @sa BCIPHER_Initialize, MODE_OFB_BYTE
 */
#define MODE_OFB        5
/** @brief OFB mode with byte feedback.
 *
 * MODE_OFB���� ������ OFB ����� ���� ��, j-bits�� 8-bits ��, 1 ����Ʈ�� ����
 * ����̴�.
 * @sa BCIPHER_Initialize, MODE_OFB
 */
#define MODE_OFB_BYTE   6
/** @brief CTS mode.
 *
 * CTS ���� ��ȣȭ�� ���� cipher text�� ���̰� plain text�� ���̿� ������
 * �ʿ䰡 ���� �� ����� �� �ִ� ����̴�.
 *
 * PAD �ɼ��� ��ȿ�� ECB, CBC, CTS ��� �� CTS�� �����ϰ�� �������� �е��� ��
 * ��, ����ϴ� �˰����� �� ũ���� ����� �ǵ��� �ʿ��� ���̸�ŭ�� Ư��
 * ���� �߰��Ѵ�. ����, ECB, CBC ��忡���� paint text ���̺��� cipher text��
 * ���̰� ������� �ȴ�. CTS���� �е� ����� plain text�� cipher text��
 * ���̰� �����ϴ�. ������ �е� ����� �����ϰ�� CBC ���� �����ϴ�.
 * @sa BCIPHER_Initialize, BCIPHER_Encrypt, BCIPHER_Decyrypt
 */
#define MODE_CTS        7
/** @brief CFB mode with bit feedback.
 *
 * @sa BCIPHER_Initialize
 */
#define MODE_CFB1       8
/** @brief CTR mode
 *
 * @sa BCIPHER_Initialize
 */
#define MODE_CTR        9
/** @brief CFB mode with variable-sized message input.
 *
 * @sa BCIPHER_Initialize, BCIPHER_Encrypt, BCIPHER_Decyrypt
 */
#define MODE_MCFB       10
/** @brief GCM mode.
 *
 * @sa BCIPHER_Initialize
 */
#define MODE_GCM        11
/** @brief CCM mode.
 *
 * @sa BCIPHER_Initialize
 */
#define MODE_CCM        12

/** @} */ /* end of modes of operation */

/**
 * @brief �˰��� �����ڸ� �ǹ��ϴ� ����ü
 *
 * ��� ��ȣ �˰����� �����ϴ� ���� ������ ��Ÿ���� ����ü�̸�, BCIPHER
 * ��⿡�� �����Ǵ� API���� ���� �˰���� �����ϱ� ���� ������(descriptor)��
 * ���ȴ�.
 *
 * @sa BCIPHER_Initialize
 */
typedef struct {
	BWT     blockLen; /**< �˰����� ����ϴ� �⺻ ���� ����Ʈ ���� ���� */
	BWT     rKeySize; /**< �˰����� ����ϴ� round key�� ����Ʈ ���� ���� */
	void  (*keyFunc)(); /**< ����Ű�� �����ϴ� �Լ� ������ */
	void  (*encFunc)(); /**< ��ȣȭ �Լ� ������ */
	void  (*decFunc)(); /**< ��ȣȭ �Լ� ������ */
	BWT   (*apadFunc)(); /**< �е� �Լ� ������ */
	BWT   (*rpadFunc)(); /**< �е� ���� �Լ� ������ */
} BCipherAlgorithm;

/**
 * @brief Block cipher�� ��� ���� ������ ������ ����ü
 *
 * \e mode�� ECB, CBC, CFB, OFB, CTS���� block cipher�� operation mode��
 * ����Ű��, \e iv�� �̵� �� ��忡�� ���� initial vector�� ������ �����̴�.
 * \e alg�� ����ϰ��� �ϴ� �˰����� �������̴�.
 *
 * @sa BCIPHER_Initialize
 */
typedef struct {
	BYTE    mode; /**< � ��� */
	BYTE    iv[BCIPHER_MAX_IV_SIZE]; /**< chaining vector�� ������ ���� */
	AlgDesc alg; /**< �˰��� �������� ������ */ 
	BYTE    index; /**< MCFB ��带 ����� �� iv �Է� ������ ���� */
} BCipherContext;

/**
 * @brief Block cipher key ����ü
 * @sa BCIPHER_NewKey BCIPHER_MakeKey BCIPHER_DelKey
 */
typedef struct {
	AlgDesc alg; /**< �˰��� �������� ������ */
	BYTE  keyMat[BCIPHER_MAX_KEY_SIZE]; /**< ���Ű */
	BWT   keyMatLen; /**< ���Ű�� ����Ʈ ���� */
	/** keyMat�κ��� ������ round key ����.
	 * �� �˰��򸶴� �ٸ��� Ȱ��ȴ�. ��ü���� Ȱ����� �� �˰����� ����
	 * �ڵ忡�� �����ǰ� �ܺο� ������� �ʴ´�. */
	BYTE *roundKey;
} BCipherKey;

/**
 * @brief BCipherKey�� �����Ѵ�.
 * @return [out] ������ BCipherKey ����ü�� pointer
 *
 * �˰��� descriptor�� �Է����� �޾�, �ش� �˰����� Ű�� �޸𸮿� �Ҵ��Ͽ�
 * �� �����͸� �����Ѵ�. ���ϵ� �����Ͱ� ����Ű�� BCipherKey�� ����ϱ� ��,
 * �ݵ�� BCIPHER_MakeKey�� ����Ͽ� key material�κ��� ���� ������ �Ŀ�
 * ����ؾ� �Ѵ�.
 *
 * @sa BCIPHER_DupKey BCIPHER_DelKey BCIPHER_MakeKey
 */
LIBSPEC
BCipherKey* BCIPHER_NewKey(
		AlgDesc bcipherAlg /**< [in] �˰��� descriptor */
		);

/**
 * @brief BCipherKey�� �����Ѵ�.
 * @return [out] ������ Ű
 *
 * �Է����� ���� BCipherKey�� ������ Ű�� �����Ͽ� �޸𸮸� �Ҵ��� ��
 * return�Ѵ�.
 *
 * @sa BCIPHER_NewKey BCIPHER_DelKey BCIPHER_MakeKey
 */
LIBSPEC
BCipherKey* BCIPHER_DupKey(
		const BCipherKey *bcKey /**< [in] ������ BCiopherKey�� ������ */
		);

/**
 * @brief BCipherKey�� �޸𸮿��� �����Ѵ�.
 *
 * BCIPHER_NewKey�� ���� ������ Ű�� ����� ���� �ڿ��� �� �Լ��� �Ҵ��
 * �޸𸮸� ����ȭ�ϰ�, �����Ѵ�.
 *
 * @sa BCIPHER_NewKey BCIPHER_MakeKey
 */
LIBSPEC
void BCIPHER_DelKey(
		BCipherKey *bcKey /**< [in] BCipherKey�� ������ */
		);

/** @ingroup KEYGEN
 * @brief BCIPHER�� ���Ǳ� ������ ���Ű�� �������� �����Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS Ű ����Ʈ �� ���� ����
 *
 * ������ ���Ű�� ����Ʈ ���� ����(KeyLen)�� �Է����� �޾� �������
 * �����߻���(HASHDRBG)�� ���������� ����Ͽ� ���Ű�� �����ϰ� �����Ѵ�.
 * BCIPHER�� ����� Ű�� �ݵ�� �� ������� ���� �ʿ䰡 �ִ� ���� �ƴϸ�
 * �ܺηκ��� �Է¹��� Ű�� �״�� ����� ���� �ִ�. �� API�� ���� �Ұ�����
 * ���ο� Ű�� ���Ƿ� �����ϰ��� �� �� ����Ѵ�.
 *
 * @sa BCIPHER_NewKey BCIPHER_MakeKey
 */
LIBSPEC
ERT BCIPHER_GenKey(
		BYTE *Key, /**< [out] ������ ���Ű�� ����� ���۸� ����Ű�� ������ */
		BWT KeyLen /**< [in] ������ ���Ű�� ����Ʈ ���� ���� */
		);

/**
 * @brief Block Cipher�� Ű�� �ʱ�ȭ�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ��ȣȭ ���� ����
 * @retval ER_NOT_APPROVED_ALGOTITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_KEY_LENGTH ���� ���� Ű ���̸� �Է��Ͽ��� ��

    Block cipher�� ���� \e keyMat��, ����Ʈ ���� ���̿� �Բ� �Է�
    ���� ��, \e key ����ü�� �ʱ�ȭ�Ѵ�. key ����ü�� �� �˰����� ��� ���Ͽ�
    ���� �Ǿ� �ִ�. ���� ��� DES �˰����� Ű ����ü�� des.h�� \e DesKey��
    ���ǵǾ� �ִ�. Key�� ����Ʈ ���� ���̴� �� �˰��� ����� ���ǵǾ� �ִ�.
    
    \e alg �� ����ϰ��� �ϴ� �˰����� �����ڷ�, �� �˰�����
    ��� ���Ͽ� ����ü�� ���� �Ǿ� �ְ�, global instance�� ����Ǿ� �ִ�.
    ����ڰ� �� �����ڸ� ���� �ٷ��� �� �Ǹ�, ���� �����ڸ�
    �Ѱ��ִ� ������ ����ϴ�. ������ �̸��� �˰��� ��Ī�� �����ϴ�.

    ������ �� ���� �������� �˰��� ���� �����̴�.

    \code
    BYTE keyMat1[8]  = {0x01,0x23, ...};
    BYTE keyMat2[16] = {0xf1,0xf2, ...};
    BYTE keyMat3[16] = {0x11,0x22, ...};

    BCipherKey *desKey;
    BCipherKey *bfKey;
    BCipherKey *ideaKey;

    desKey = BCIPHER_NewKey(DES);
    BCIPHER_MakeKey(desKey, keyMat1, DES_KEY_SIZE,  DES);
    BCIPHER_DelKey(desKey);

    bfKey = BCIPHER_NewKey(BLOWFISH);
    BCIPHER_MakeKey(bfKey,  keyMat2, 16, BLOWFISH);
    BCIPHER_DelKey(bfKey);

    ideaKeyKey = BCIPHER_NewKey(IDEA);
    BCIPHER_MakeKey(ideaKey,keyMat3, IDEA_KEY_SIZE, IDEA);
    BCIPHER_DelKey(ideaKeyKey);
    \endcode

    Blowfish �˰����� ���, \e BLOWFISH_KEY_SIZE�� ���� �ʾҴµ�,
    Ű�� ���̰� �������̱� �����̴�. �ִ� ���̴� blowfish.h ��
    BLOWFISH_MAX_KEY_SIZE�� ���ǵǾ� �ִ�.

    ����� Ű�� BCIPHER_DelKey�� ����Ͽ� �Ҵ�� �޸𸮸� �����Ͽ��� �Ѵ�.
    ����� ���Ű�� ZEROIZE()�� �̿��Ͽ� �������α׷����� ����ȭ�Ѵ�.

 * @sa BCIPHER_NewKey BCIPHER_DelKey
 */
LIBSPEC
ERT BCIPHER_MakeKey(
		BCipherKey *key, /**< [in,out] �ʱ�ȭ�ϰ��� �ϴ� key ����ü�� �����Ͱ� */
		const BYTE *keyMat, /**< [in] Octet string Ÿ���� key binary ������ */
		BWT keyLen, /**< [in] keyMat�� ����Ʈ ������ ���� */
		AlgDesc bcipherAlg /**< [in] ����� block cipher �˰��� */
		);

/**
 * @brief BCipherContext�� �ʱ�ȭ�Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS BCipherContext�� �ʱ�ȭ ����
 * @retval ER_NOT_APPROVED_ALGOTITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��

    Block cipher�� ��� ���� ������ �Է¹޾� BCipherContext�� �ʱ�ȭ�Ѵ�.

    ECB ��� �̿��� ��带 ����� ���, ��Ͼ�ȣ�� ��� ũ�⸸ŭ iv�� �ݵ�� �Է��ؾ� �Ѵ�.

    �Ѱ��� ������ ���� chaining vector�� 
    ��ȣȭ�� ����, ��ȣȭ�� �� ��� ������Ʈ �Ǵ� ���̹Ƿ� 
    ��ȣȭ�� \e BCipherContext�� ��ȣȭ�� \e BcipherContext�� ����
    ���� �����ؼ� ����ؾ� �Ѵٴ� ���̴�. ��, �ϳ��� Context�� ������
    ��ȣȭ�� ��ȣȭ�� ������ ����ؼ��� �� �Ǹ�, �ϳ��� �뵵���� ����ؾ�
    �Ѵٴ� ���̴�. ��, chaining vecotr�� ������� ECB����� ��쿡�� �ϳ���
    context�� �Ϻ�ȣȭ�� ��� ���� �� �ִ�.

    ������ �� ���̴�.

    \code
    BWT pLen1, cLen, dLen;    

    BYTE plain[256];
    BYTE cipher[256];
    BYTE decrypted[256];
    BYTE iv[8];
    BYTE key[8];

    BCipherKey *key;
    BCipherContext enc, dec, ctx;

    .
    .
    initialize
    .
    .

    BCIPHER_Initialize(&ctx, MODE_ECB, iv, DES);
    BCIPHER_Initialize(&enc, MODE_CBC, iv, DES);
    BCIPHER_Initialize(&dec, MODE_CBC, iv, DES);

    cLen = sizeof(cipher);
    BCIPHER_Encrypt(cipher,   &cLen, plain,  pLen, &ctx, key, PAD);
    dLen = sizeof(decrypted);
    BCIPHER_Decrypt(decrypted, &dLen, cipher, cLen, &ctx, key, PAD);

    cLen = sizeof(cipher);
    BCIPHER_Encrypt(cipher,   &cLen, plain,  pLen, &enc, key, PAD);
    dLen = sizeof(decrypted);
    BCIPHER_Decrypt(decrypted, &dLen, cipher, cLen, &dec, key, PAD);

    .
    .
    .
    finalize
    .
    .
    .

    \endcode

    ���� �ڵ忡�� MODE_ECB�� ��� ���� BCipherContext�� �Ϻ�ȣȭ�� 
    ��� ����Ͽ�����, MODE_CBC ��쿡�� ������ BCipherContext��
    ����Ѵ�.

 * @sa BCipherContext
 */
LIBSPEC
ERT BCIPHER_Initialize(
		BCipherContext *bcipher, /**< [out] �ʱ�ȭ�� BcipherContext */
		BYTE mode, /**< [in] Operation mode */
		const BYTE *iv, /**< [in] Initial vector */
		AlgDesc bcipherAlg /**< [in] ����ϰ��� �ϴ� �˰����� ������ */
		); 

/**
 * @brief Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ��ȣȭ ���� ����
 * @retval ER_NOT_APPROVED_ALGOTITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD include invalid padding bytes
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL ��� ������ �޸� ũ�Ⱑ ����� �������� �޸𸮺��� ���� ��

    \e in ���ۿ� ����Ǿ� �ִ� �����͸� BCipherContext�� BCipherKey�� ������
    ���� ��ȣȭ�Ͽ� ����� \e out ���ۿ� ����Ѵ�. �� ��, ����� ���̴� ����Ʈ
    �����̸� ��±��̴� \e outLen�� ����Ű�� �ִ� BWT Ÿ���� ������ ����ȴ�.
    �Ѱ��� ������ ���� �����Ͱ� ����Ǵ� ���۴� �ݵ�� octet string���ν� 
    �ٷ���������� �ùٸ� ����� ���� �� �ִ�.

    \e padFlag�� �־��� ���۰� block cipher�� block������ �ǵ��� padding��
    �� ���ΰ��� �����Ѵ�. \b NPAD�̸� padding�� ���� �ʰ�, \b PAD�̸� padding��
    �ϰ� �ȴ�. ����, NPAD�� ��쿡�� ���� ���̴� block cipher�� �ٷ�� 
    �� ������ ����� �־����� �ϸ� �̰��� ������� �������� �����̴�. 
    �� ��⿡���� ������ ���Ͻ�Ű�� ��� �ڵ�(ex. error return)�� �����Ƿ�
    �̰��� üũ���� �ʴ´�.

    PAD �ɼ��� ���, ECB, CBC, CTS ��忡���� ��ȿ�ϴ�. ������ ��忡���� ��� 
    NPAD �̸�, PAD �ɼ��� ����� �� ����.

	\e bcipher�� \e key�� ���� BCIPHER_Initialize�� BCIPHER_MakeKey�� ���ؼ�
	�ʱ�ȭ�� �̷���� �Ŀ� ����ؾ� �Ѵ�.

 * @sa BCIPHER_Decrypt, BCipherContext
 */
LIBSPEC
ERT BCIPHER_Encrypt(
		BYTE *out, /**< [out] ��� ��ȣ�� */
		BWT *outLen, /**< [in, out] in: out�� �޸� ���� ũ��, out: ��� ��ȣ���� ����Ʈ ���� */
		const BYTE *in, /**< [in] �Է� �� */
		BWT inLen, /**< [in] �Է� ���� ����Ʈ ���� */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding ���� */
		);

/**
 * @brief GCM ���� CCM ����� ���� Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ������ȣȭ �˰��� ��ȣȭ ���� ����
 * @retval ER_NOT_APPROVED_ALGOTITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL ��� ������ �޸� ũ�Ⱑ ����� �������� �޸𸮺��� ���� ��
 * @retval ER_BCIPHER_INVALID_TAG_LENGTH ��� ������ �±ױ��̰� �ƴ� ��
 * @retval ER_BCIPHER_INVALID_NONCE_LENGTH �Է� ������ �������̰� �ƴ� ��
 *
 * BCIPHER_Encrypt()�� �����ϳ� � ��尡 GCM�̳� CCM�� �� ����Ѵ�.
 * CCM ����� ���, 4 <= tLen <= 16, 7 <= ivLen(nonceLen) <= 13 �̾�� �Ѵ�.
 * GCM ����� ���, tLen <= 16(���ũ��) �̾�� �ϰ�, 12 <= ivLen �� �����Ѵ�.
 */
LIBSPEC
ERT BCIPHER_EncryptAuth(
		BYTE *out, /**< [out] ��� ��ȣ�� */
		BWT *outLen, /**< [in, out] in: out�� �޸� ���� ũ��, out: ��� ��ȣ���� ����Ʈ ���� */
		const BYTE *in, /**< [in] �Է� �� */
		BWT inLen, /**< [in] �Է� ���� ����Ʈ ���� */
		BYTE *authData, /**< [in] CCM/GCM�� �߰� �Է� ���� */
		BWT authDataLen, /**< [in] authData�� ����Ʈ ���� */
		BYTE *iv, /**< [in] GCM�� iv, CCM�� nonce*/
		BWT ivLen, /**< [in] iv�� ����Ʈ ���� */
		BCipherContext *bcipher, /**< [in] context */
		const BCipherKey *key, /**< [in] key */
		BWT tLen /**< [in] �޽��� ���� �±��� ����Ʈ ���� */
		);

/**
 * @brief Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ��ȣȭ ���� ����
 * @retval ER_NOT_APPROVED_ALGOTITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD include invalid padding bytes
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL ��� ������ �޸� ũ�Ⱑ ����� �������� �޸𸮺��� ���� ��

    \e in ���ۿ� ����Ǿ� �ִ� �����͸� BCipherContext�� BCipherKey�� ������
    ���� ��ȣȭ�Ͽ� ����� \e out ���ۿ� ����Ѵ�. �� ��, ����� ���̴� ����Ʈ
    �����̸� ��±��̴� \e outLen�� ����Ű�� �ִ� BWT Ÿ���� ������ ����ȴ�.
    �Ѱ��� ������ ���� �����Ͱ� ����Ǵ� ���۴� �ݵ�� octet string���ν� 
    �ٷ���������� �ùٸ� ����� ���� �� �ִ�.

    \e padFlag�� �־��� ���۰� ��ȣȭ�� ��, padding�� �� �����ΰ��� �����Ѵ�.
    \b PAD�̸� ������ ����Ʈ�� ������ ���� padding�� �κ��� �����Ͽ� �����
    ����ϸ�, \b NPAD�� ��� ��ȭȭ�� ��ü�� �״�� ����Ѵ�. ��ȣȭ�� ����
    ���������� NPAD�� ��쿡�� �Է� ������ ���̱� block cipher�� �ٷ��
    �� ������ ����� �Ǿ�� �Ѵ�.
    
    PAD �ɼ��� ���, ECB, CBC ��忡���� ��ȿ�ϴ�. ������ ��忡���� ��� 
    NPAD �̸�, PAD �ɼ��� ����� �� ����.

	\e bcipher�� \e key�� ���� BCIPHER_Initialize�� BCIPHER_MakeKey�� ���ؼ�
	�ʱ�ȭ�� �̷���� �Ŀ� ����ؾ� �Ѵ�.

 * @sa BCIPHER_Encrypt, BCipherContext
 */
LIBSPEC
ERT BCIPHER_Decrypt(
		BYTE *out, /**< [out] ��� �� */
		BWT *outLen, /**< [in, out] in: out�� �޸� ���� ũ��, out: ��� ��ȣ���� ����Ʈ ���� */
		const BYTE *in, /**< [in] �Է� ��ȣ�� */
		BWT inLen, /**< [in] �Է� ��ȣ���� ����Ʈ ���� */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding ���� */
		);

/**
 * @brief GCM ���� CCM ����� ���� Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval FAIL NULL �� �Է� ���� ����
 * @retval SUCCESS ������ȣȭ �˰��� ��ȣȭ ���� ����
 * @retval ER_NOT_APPROVED_ALGOTITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL ��� ������ �޸� ũ�Ⱑ ����� �������� �޸𸮺��� ���� ��
 * @retval ER_BCIPHER_INVALID_TAG_LENGTH ��� ������ �±ױ��̰� �ƴ� ��
 * @retval ER_BCIPHER_INVALID_NONCE_LENGTH �Է� ������ �������̰� �ƴ� ��
 *
 * BCIPHER_Decrypt()�� �����ϳ� � ��尡 GCM�̳� CCM�� �� ����Ѵ�.
 * CCM ����� ���, 4 <= tLen <= 16, 7 <= ivLen(nonceLen) <= 13 �̾�� �Ѵ�.
 * GCM ����� ���, tLen <= 16(���ũ��) �̾�� �ϰ�, 12 <= ivLen �� �����Ѵ�.
 */
LIBSPEC
ERT BCIPHER_DecryptAuth(
		BYTE *out, /**< [out] ��� �� */
		BWT *outLen, /**< [in, out] in: out�� �޸� ���� ũ��, out: ��� ��ȣ���� ����Ʈ ���� */
		const BYTE *in, /**< [in] �Է� ��ȣ�� */
		BWT inLen, /**< [in] �Է� ��ȣ���� ����Ʈ ���� */
		BYTE *authData, /**< [in] CCM/GCM�� �߰� �Է� ���� */
		BWT authDataLen, /**< [in] authData�� ����Ʈ ���� */
		BYTE *iv, /**< [in] GCM�� iv, CCM�� nonce*/
		BWT ivLen, /**< [in] iv�� ����Ʈ ���� */
		BCipherContext *bcipher, /**< [in] context */
		const BCipherKey *key, /**< [in] key */
		BWT tLen /**< [in] �޽��� ���� �±��� ����Ʈ ���� */
		);

/** @ingroup ZERO
 * @brief BcipherContext�� iv�� ����ȭ�Ѵ�. */
LIBSPEC
void BCIPHER_WipeIV(
		BCipherContext  *bcipher /**< [in] ����ȭ�� iv�� �ִ� BcipherContext */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _BCIPHER_OP_H_ */
