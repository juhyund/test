#ifndef _RSA0_H_
#define _RSA0_H_

/** @defgroup RSA0
 * @ingroup PKCRYPT_ALG
 * @brief obsolete variant of RSA (for compatilibity)
 *
 * RSA0�� ���� ���װ� �ִ� Penta�� ���̺귯���� issaclib�� RSA �˰�����
 * ���ϴ� ���̴�. ISSAC-Web�� issaclib�� ���� �ֱ� ������ ����������
 * ȣȯ�������� RSA0�� ź���Ǿ���.   
 */

/** @file rsa0.h
    @ingroup RSA0
    @brief RSA0 �˰����� ����ϱ� ���� �������̽� 
    
*/

#include <stdio.h>
#include "cc_define.h"
#include "ce_dll.h"
#include "mint_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ER_RSA0_VP1_SIG_OUT_OF_RANGE -1031
#define ER_RSA0_MESSAGE_TOO_LONG     -1032
#define ER_RSA0_WRONG_CIPHER_LEN     -1033

typedef MINT RSA0Sig;

typedef struct {
  BYTE *z;
  BWT   zLen;
} RSA0Param;

/** @ingroup RSA0
    @brief RSA0 ����Ű ����ü
	@deprecated
    @sa RSA0PriKey

    RSA0 ����Ű ����ü�̴�. 
*/    
typedef struct {
  MINT    N;  /**< mudulus */
  MINT    e;  /**< public Exponent */
} RSA0PubKey;

/** @ingroup RSA0
    @brief RSA0 �����Ű ����ü
	@deprecated
    @sa RSA0PubKey

    RSA0 �����Ű ����ü�̴�. 
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
} RSA0PriKey;

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
} RSA0Descriptor;

LIBSPEC_CE
extern RSA0Descriptor rsa0;

/** @ingroup RSA0
    @brief RSA0 �˰��� descriptor�� rsa0 ���� ������ �ּҰ� rename
	@deprecated
    */
#define RSA0 &rsa0

/** @ingroup RSA0
    @brief RSA0 ����Ű ��ȣȭ �Լ�
	@deprecated
    @param cipher    [out] ��ȣȭ�� �޽����� ����� ������ ������
    @param cipherLen [in]  ��ȣȭ�� �޽����� ����Ʈ ���� ���� 
    @param M         [in]  ��ȣȭ�� �޽��� ������ ����Ʈ ������
    @param MLen      [in]  ��ȣȭ�� �޽��� ������ ����Ʈ ���� ���� 
    @param param     [in]  NULL  
    @param pubKey    [in]  RSA0PubKey�� ������  
    @param hashAlg   [in]  ����� hash �˰����� descriptor; OAEP ��Ŀ� ���ؼ�
    @param maskAlg   [in]  ����� mask �˰����� descriptor; ����� NULL�� �Է��� ���
    @retval ER_RSA0_MESSAGE_TOO_LONG The length of message(MLen) is too long.
    
    RSA0 �˰��򿡼��� �����Ű ����ü�� �ý��� �Ķ���Ͱ� ���ԵǾ� �ֱ� ������ 
    �ý��� �Ķ���͸� ���� �Է� ���� �ʿ䰡  ����. \e param�� �ٸ� �˰������ 
    �������̽� ��ġ�� ���� ���Ե� �����̰�, ���ο��� ������ �ʴ´�. NULL����
    �Է��Ѵ�.

    hashAlg�� RSA0ES-OAEP ������� ��ȣȭ�ϱ� ���� ��쿡�� �Է��Ѵ�.
    NULL���� ������, RSA0ES-PKCS1-v1_5 ������� ��ȣȭ�ȴ�.

    error code �� ER_RSA0_MESSAGE_TOO_LONG�� �Է� M�� ����Ʈ ���� MLen�� �ʹ�
    Ŭ ��� ���ϵǴ� �ڵ��̴�. Modulus N�� ����Ʈ���� ���̸� k�� �ϰ�,
    ����ϴ� �ؽ� �˰����� ������� hLen �̶� �ϸ�,
    MLen < k-2hLen-2 �̾�� �Ѵ�.
    ���� ��� SHA-1�� ���� RSA0 1024bit(N�� 1024bit)�� ��쿡�� k���� 128��
    �ǰ� hLen ���� 20�� �ǹǷ� MLen < 128-2*20-2 (= 87) �� �ȴ�. ����, MLen
    �� �ִ� 86����Ʈ������ ���Ǵ� ���̴�.
    
    @sa RSA0_ES_D
*/
LIBSPEC_CE
ERT RSA0_ES_E(       BYTE *cipher,
                    BWT  *cipherLen,
              const BYTE *M,
                    BWT   MLen,
              const void *pubKey,
              const void *param,
              const void *hashAlg,
              const void *maskAlg);

/** @ingroup RSA0
    @brief RSA0 ����Ű ��ȣȭ �Լ�
	@deprecated
    @param M         [out] ��ȣȭ�� �޽����� ����� ������ ������
    @param MLen      [out] ��ȣȭ�� �޽����� ����Ʈ ���� ���� 
    @param cipher    [in]  ��ȣȭ�� �޽��� ������ ����Ʈ ������
    @param cipherLen [in]  ��ȣȭ�� �޽��� ������ ����Ʈ ���� ���� 
    @param param     [in]  NULL  
    @param priKey    [in]  RSA0PriKey�� ������  
    @param hashAlg   [in]  ����� hash �˰����� descriptor; OAEP ��Ŀ� ���ؼ�
    @param maskAlg   [in]  ����� mask �˰����� descriptor; ����� NULL�� �Է��� ���
    @retval ER_RSA0_WRONG_CIPHER_LEN The length of cipher is wrong
    
    RSA0 �˰��򿡼��� �����Ű ����ü�� �ý��� �Ķ���Ͱ� ���ԵǾ� �ֱ� ������ 
    �ý��� �Ķ���͸� ���� �Է� ���� �ʿ䰡  ����. \e param�� �ٸ� �˰������ 
    �������̽� ��ġ�� ���� ���Ե� �����̰�, ���ο��� ������ �ʴ´�. NULL����
    �Է��Ѵ�.

    hashAlg�� RSA0ES-OAEP ������� ��ȣȭ�ϱ� ���� ��쿡�� �Է��Ѵ�.
    NULL���� ������, RSA0ES-PKCS1-v1_5 ������� ��ȣȭ�ȴ�.
    
    error code �� ER_RSA0_WRONG_CIPHER_LEN �� �Էµ� ��ȣ���� ���̰� Ʋ���ٴ�
    �����̴�. RSA0 �˰������� ��ȣȭ�� ��ȣ���� modulus N�� octet ���� ���̿�
    ��ġ�ؾ߸� �Ѵ�. ����, �ùٸ��� ������ ��ȣ���̶��, �ùٸ� ���̸�
    ������ ���� ���̴�.

    @sa RSA0_ES_E
*/
LIBSPEC_CE
ERT RSA0_ES_D(       BYTE *M,
                    BWT  *MLen,
              const BYTE *cipher,
                    BWT   cipherLen,
              const void *priKey,
              const void *param,
              const void *hashAlg,
              const void *maskAlg);

/** @ingroup RSA0
    @brief RSA0 �� integer�� octet string���� ��ȯ�ϴ� �Լ�
	@deprecated
    @param byteArray [out] ��ȯ�� octet string
    @param byteLen [out] ������ public key�� ����� RSA0PubKey ����ü
    @param nLen      [in]  �����ϰ��� �ϴ� modulus N �� bit ���� ����
    @sa MINT_WriteInByteArray

    PKCS#1 ver 2.0(RFC2437)�� ����� integer�� octet string����
    ��ȯ�ϴ� �Լ��̴�.  �������� MINT_WriteInByteArray() �Լ���
    ����Ͽ�����, �� �Լ������� ���� byte���� ���� 0�� ��� �̸� �ǹ̾���
    ������ �Ǵ��ϰ� �����ع����� ������ �׻� ���̰� modulus ���̿�
    ���ƾ߸� �ϴ� RSA0 ���� �������� ���� ������
    �����״�.  �� �Լ��� MINT_WriteInByteArray()�� ���� ���� ������ �ϳ�
    PKCS#1���� ������ ��� �Է��� ���̸� ���� ��ȯ���� �ʰ� �״�� ��������
    Ư���� ������.

    */
LIBSPEC_CE
ERT RSA0_I2OSP(BYTE *byteArray, BWT *byteLen, const MINT *a);

#ifdef __cplusplus
}
#endif

#endif /* _RSA0_H_ */  
