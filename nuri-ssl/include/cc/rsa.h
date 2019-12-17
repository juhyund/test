#ifndef _RSA_H_
#define _RSA_H_

/** @defgroup RSA RSA
 * @ingroup PKCRYPT_ALG
 * @brief RSA Algorithm from PKCS1 v1.5 and v2.1
 */

/** @file
    @ingroup RSA
    @brief RSA �˰����� ����ϱ� ���� �������̽� 
*/

#include <stdio.h>
#include "cc_define.h"
#include "mint_common.h"
#include "pkcrypt_op.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup RSA
 * @{ */

/** @} */

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/** @addtogroup RSA
 * @{ */

typedef MINT RSASig;

typedef struct {
  BYTE *z;
  BWT   zLen;
} RSAParam;

/**
    @brief RSA ����Ű ����ü
    @sa RSAPriKey

    RSA ����Ű ����ü�̴�. 
*/    
typedef struct {
  MINT    N;  /**< mudulus */
  MINT    e;  /**< public Exponent */
} RSAPubKey;

/**
    @brief RSA �����Ű ����ü
    @sa RSAPubKey

    RSA �����Ű ����ü�̴�. 
*/    
typedef struct {
  MINT    N;    /**< modulus */
  MINT    e;    /**< public exponent */
  MINT    d;    /**< private exponent */
  MINT    p;    /**< the first prime factor of N  */
  MINT    q;    /**< the second prime factor of N */
  MINT    dP;   /**< the first factor's exponent */
  MINT    dQ;   /**< the second factor's exponent */
  MINT    qInv; /**< the CRT coefficient */
} RSAPriKey;

typedef struct {
  ERT   (*signFunc)();
  ERT   (*verifyFunc)();
  ERT   (*signFileFunc)();
  ERT   (*verifyFileFunc)();
  ERT   (*encFunc)();
  ERT   (*decFunc)();
  ERT   (*genParam)();
  ERT   (*genKey)();
  ERT   (*checkParam)();
  ERT   (*checkKey)();
  ERT   (*checkKeyPair)();
  BWT     priKeySize;
  BWT     pubKeySize;
  BWT     paramSize;
  BWT     sigSize;
  BWT     idx;
  
  ERT   (*signHashFunc)();
  ERT   (*verifyHashFunc)();
} RSADescriptor;

LIBSPEC
extern RSADescriptor poprsa15;

LIBSPEC
extern RSADescriptor pcis_rsa;

/** @brief RSA from PKCS1 v1.5 */
#define RSA15 &poprsa15

/** alias to RSA21 */
#define RSA &pcis_rsa
/** @brief RSA from PKCS1 v2.1 */
#define RSA21 &pcis_rsa

/** @ingroup PKCRYPT
 * @brief RSA�� ��ȣ Ű ���� ����Ű e�� �Է��� eNum�� �ǵ��� �����Ѵ�.
 * @retval FAIL on fail
 * @retval SUCCESS on success
 * @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
 * @retval ER_CONDITIONAL_SELFTEST Ű�� ��ġ ���� �����Ͽ��� ���
 */
LIBSPEC
ERT RSA_GenKeyE(
		PKCryptPriKey *PriKey, /**< [in,out] RSA ���Ű */
		PKCryptPubKey *PubKey, /**< [in,out] RSA ����Ű */
		BWT nLen, /**< [in] N�� ��Ʈ ���� */
		BWT eNum /**< [in] ������ ����Ű e�� ��*/
		);

/** @ingroup PKCRYPT
    @brief RSA ����Ű ��ȣȭ �Լ�
    @retval FAIL on fail
    @retval SUCCESS on success
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL �Լ� ����� ����� �Ķ������ �޸� ���� ũ�Ⱑ ���� ��
    @retval ER_RSA_MESSAGE_TOO_LONG The length of message(MLen) is too long.
    
    RSA �˰��򿡼��� �����Ű ����ü�� �ý��� �Ķ���Ͱ� ���ԵǾ� �ֱ� ������ 
    �ý��� �Ķ���͸� ���� �Է� ���� �ʿ䰡  ����. \e param�� �ٸ� �˰������ 
    �������̽� ��ġ�� ���� ���Ե� �����̰�, ���ο��� ������ �ʴ´�. NULL����
    �Է��Ѵ�.

    error code �� ER_RSA_MESSAGE_TOO_LONG�� �Է� M�� ����Ʈ ���� MLen�� �ʹ�
    Ŭ ��� ���ϵǴ� �ڵ��̴�. Modulus N�� ����Ʈ���� ���̸� k�� �ϰ�,
    ����ϴ� �ؽ� �˰����� ������� hLen �̶� �ϸ�,
    MLen < k-2hLen-2 �̾�� �Ѵ�.
    ���� ��� SHA-1�� ���� RSA 1024bit(N�� 1024bit)�� ��쿡�� k���� 128��
    �ǰ� hLen ���� 20�� �ǹǷ� MLen < 128-2*20-2 (= 87) �� �ȴ�. ����, MLen
    �� �ִ� 86����Ʈ������ ���Ǵ� ���̴�.
    
    @sa RSA_ES_D
*/
LIBSPEC
ERT RSAES_OAEP_ENCRYPT21(
		BYTE *cipher, /**< [out] ��ȣȭ�� �޽����� ����� ���� */
		BWT *cipherLen, /**< [in,out] ��ȣȭ�� �޽����� ���� */
		const BYTE *M, /**< [in] ��ȣȭ�� �޽��� ���� */
		BWT MLen, /**< [in] ��ȣȭ�� �޽��� ������ ����Ʈ ���� ���� */
		const PKCryptPubKey *pubKey, /**< [in] RSAPubKey�� ������ */
		const PKCryptParam *param, /**< [in] NULL */
		const void *hashAlg, /**< [in] ����� hash �˰����� descriptor */
		const void *maskAlg /**< [in] masking algorithm */
		);

/** @ingroup PKCRYPT
    @brief RSA ����Ű ��ȣȭ �Լ�
    @param M         [out] ��ȣȭ�� �޽����� ����� ������ ������
    @param MLen      [in,out] ��ȣȭ�� �޽����� ����Ʈ ���� ���� 
    @param cipher    [in]  ��ȣȭ�� �޽��� ������ ����Ʈ ������
    @param cipherLen [in]  ��ȣȭ�� �޽��� ������ ����Ʈ ���� ���� 
    @param param     [in]  NULL  
    @param priKey    [in]  RSAPriKey�� ������  
    @param hashAlg   [in]  ����� hash �˰����� descriptor
    @param maskAlg   [in]  ����� mask �˰����� descriptor; ����� NULL�� �Է��� ���
    @retval FAIL on fail
    @retval SUCCESS on success
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL �Լ� ����� ����� �Ķ������ �޸� ���� ũ�Ⱑ ���� ��
    @retval ER_RSA_WRONG_CIPHER_LEN The length of cipher is wrong
    @retval ER_RSA_DECRYPT_ERROR RSA �� ��ȣȭ ������ �߸��Ǿ��� ��
    
    RSA �˰��򿡼��� �����Ű ����ü�� �ý��� �Ķ���Ͱ� ���ԵǾ� �ֱ� ������ 
    �ý��� �Ķ���͸� ���� �Է� ���� �ʿ䰡  ����. \e param�� �ٸ� �˰������ 
    �������̽� ��ġ�� ���� ���Ե� �����̰�, ���ο��� ������ �ʴ´�. NULL����
    �Է��Ѵ�.

    error code �� ER_RSA_WRONG_CIPHER_LEN �� �Էµ� ��ȣ���� ���̰� Ʋ���ٴ�
    �����̴�. RSA �˰������� ��ȣȭ�� ��ȣ���� modulus N�� octet ���� ���̿�
    ��ġ�ؾ߸� �Ѵ�. ����, �ùٸ��� ������ ��ȣ���̶��, �ùٸ� ���̸�
    ������ ���� ���̴�.

    @sa RSA_ES_E
*/
LIBSPEC
ERT RSAES_OAEP_DECRYPT21(       BYTE *M,
                    BWT  *MLen,
              const BYTE *cipher,
                    BWT   cipherLen,
              const PKCryptPriKey *priKey,
              const PKCryptParam *param,
              const void *hashAlg,
              const void *maskAlg);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _RSA_H_ */  
