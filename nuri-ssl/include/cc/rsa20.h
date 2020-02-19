#ifndef _RSA20_H_
#define _RSA20_H_

/** @defgroup RSA20 RSA20
 * @ingroup PKCRYPT_ALG
 * @brief RSA Algorithm from PKCS1 v2.0
 * @deprecated Use RSA or RSA21 algorithm instead
 */

/** @file
    @ingroup RSA20
    @brief RSA20 �˰����� ����ϱ� ���� �������̽� 
*/

#include <stdio.h>
#include "cc_define.h"
#include "mint_common.h"
#include "pkcrypt_op.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef MINT RSA20Sig;

typedef struct {
  BYTE *z;
  BWT   zLen;
} RSA20Param;

/** @ingroup RSA20
    @brief RSA ����Ű ����ü
	@deprecated Use RSA or RSA21 algorithm instead
    @sa RSAPriKey

    RSA ����Ű ����ü�̴�. 
*/    
typedef struct {
  MINT    N;  /**< mudulus */
  MINT    e;  /**< public Exponent */
} RSA20PubKey;

/** @ingroup RSA20
    @brief RSA �����Ű ����ü
	@deprecated Use RSA or RSA21 algorithm instead
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
} RSA20PriKey;

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
} RSA20Descriptor;

LIBSPEC
extern RSA20Descriptor poprsa20;

/** @ingroup RSA20
 * @brief RSA from PKCS1 v2.0
 * @deprecated Use RSA or RSA21 algorithm instead
 */
#define RSA20 &poprsa20

/** @ingroup PKCRYPT
    @brief RSA ����Ű ��ȣȭ �Լ�
	@deprecated Use RSA or RSA21 algorithm instead
    @retval FAIL on fail
    @retval SUCCESS on success
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL �Լ� ����� ����� �Ķ������ �޸� ���� ũ�Ⱑ ���� ��
    @retval ER_RSA_MESSAGE_TOO_LONG The length of message(MLen) is too long.
    
    RSA �˰��򿡼��� �����Ű ����ü�� �ý��� �Ķ���Ͱ� ���ԵǾ� �ֱ� ������ 
    �ý��� �Ķ���͸� ���� �Է� ���� �ʿ䰡 ����. \e param�� �ٸ� �˰������ 
    �������̽� ��ġ�� ���� ���Ե� �����̰�, ���ο��� ������ �ʴ´�. NULL����
    �Է��Ѵ�.

    hashAlg�� RSAES-OAEP ������� ��ȣȭ�ϱ� ���� ��쿡�� �Է��Ѵ�.
    NULL���� ������, RSAES-PKCS1-v1_5 ������� ��ȣȭ�ȴ�.

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
ERT RSA20_ES_E(
		BYTE *cipher, /**< [out] ��ȣȭ�� �޽����� ����� ������ ������ */
		BWT *cipherLen, /**< [in, out] ��ȣȭ�� �޽����� ����Ʈ ���� ���� */
		const BYTE *M, /**< [in] ��ȣȭ�� �޽��� ������ ����Ʈ ������ */
		BWT MLen, /**< [in] ��ȣȭ�� �޽��� ������ ����Ʈ ���� ���� */
		const PKCryptPubKey *pubKey, /**< [in] RSAPubKey�� ������ */
		const PKCryptParam *param, /**< [in] NULL */
		const void *hashAlg, /**< [in] OAEP�� ������ �� ����� hash �˰��� */
		const void *maskAlg /**< [in] masking algorithm */
		);

/** @ingroup PKCRYPT
    @brief RSA ����Ű ��ȣȭ �Լ�
	@deprecated Use RSA or RSA21 algorithm instead
    @param M         [out] ��ȣȭ�� �޽����� ����� ������ ������
    @param MLen      [in,out] ��ȣȭ�� �޽����� ����Ʈ ���� ���� 
    @param cipher    [in]  ��ȣȭ�� �޽��� ������ ����Ʈ ������
    @param cipherLen [in]  ��ȣȭ�� �޽��� ������ ����Ʈ ���� ���� 
    @param param     [in]  NULL  
    @param priKey    [in]  RSAPriKey�� ������  
    @param hashAlg   [in]  ����� hash �˰����� descriptor; OAEP ��Ŀ� ���ؼ�
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

    hashAlg�� RSAES-OAEP ������� ��ȣȭ�ϱ� ���� ��쿡�� �Է��Ѵ�.
    NULL���� ������, RSAES-PKCS1-v1_5 ������� ��ȣȭ�ȴ�.
    
    error code �� ER_RSA_WRONG_CIPHER_LEN �� �Էµ� ��ȣ���� ���̰� Ʋ���ٴ�
    �����̴�. RSA �˰������� ��ȣȭ�� ��ȣ���� modulus N�� octet ���� ���̿�
    ��ġ�ؾ߸� �Ѵ�. ����, �ùٸ��� ������ ��ȣ���̶��, �ùٸ� ���̸�
    ������ ���� ���̴�.

    @sa RSA_ES_E
*/
LIBSPEC
ERT RSA20_ES_D(       BYTE *M,
                    BWT  *MLen,
              const BYTE *cipher,
                    BWT   cipherLen,
              const PKCryptPriKey *priKey,
              const PKCryptPubKey *param,
              const void *hashAlg,
              const void *maskAlg);


#ifdef __cplusplus
}
#endif

#endif /* _RSA_H_ */  
