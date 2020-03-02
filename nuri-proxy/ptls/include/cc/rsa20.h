#ifndef _RSA20_H_
#define _RSA20_H_

/** @defgroup RSA20 RSA20
 * @ingroup PKCRYPT_ALG
 * @brief RSA Algorithm from PKCS1 v2.0
 * @deprecated Use RSA or RSA21 algorithm instead
 */

/** @file
    @ingroup RSA20
    @brief RSA20 알고리즘을 사용하기 위한 인터페이스 
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
    @brief RSA 공개키 구조체
	@deprecated Use RSA or RSA21 algorithm instead
    @sa RSAPriKey

    RSA 공개키 구조체이다. 
*/    
typedef struct {
  MINT    N;  /**< mudulus */
  MINT    e;  /**< public Exponent */
} RSA20PubKey;

/** @ingroup RSA20
    @brief RSA 비공개키 구조체
	@deprecated Use RSA or RSA21 algorithm instead
    @sa RSAPubKey

    RSA 비공개키 구조체이다. 
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
    @brief RSA 공개키 암호화 함수
	@deprecated Use RSA or RSA21 algorithm instead
    @retval FAIL on fail
    @retval SUCCESS on success
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL 함수 출력이 저장될 파라미터의 메모리 버퍼 크기가 작을 때
    @retval ER_RSA_MESSAGE_TOO_LONG The length of message(MLen) is too long.
    
    RSA 알고리즘에서는 비공개키 구조체에 시스템 파라미터가 포함되어 있기 때문에 
    시스템 파라미터를 따로 입력 받을 필요가 없다. \e param은 다른 알고리즘과의 
    인터페이스 일치를 위해 포함된 인자이고, 내부에서 사용되지 않는다. NULL값을
    입력한다.

    hashAlg는 RSAES-OAEP 방식으로 암호화하길 원할 경우에만 입력한다.
    NULL값을 넣으면, RSAES-PKCS1-v1_5 방식으로 암호화된다.

    error code 중 ER_RSA_MESSAGE_TOO_LONG은 입력 M의 바이트 길이 MLen이 너무
    클 경우 리턴되는 코드이다. Modulus N의 바이트단위 길이를 k라 하고,
    사용하는 해쉬 알고리즘의 결과값이 hLen 이라 하면,
    MLen < k-2hLen-2 이어야 한다.
    예를 들어 SHA-1을 쓰는 RSA 1024bit(N이 1024bit)일 경우에는 k값이 128이
    되고 hLen 값은 20이 되므로 MLen < 128-2*20-2 (= 87) 이 된다. 따라서, MLen
    은 최대 86바이트까지만 허용되는 것이다.
    
    @sa RSA_ES_D
*/
LIBSPEC
ERT RSA20_ES_E(
		BYTE *cipher, /**< [out] 암호화된 메시지가 저장될 버퍼의 포인터 */
		BWT *cipherLen, /**< [in, out] 암호화된 메시지의 바이트 단위 길이 */
		const BYTE *M, /**< [in] 암호화할 메시지 버퍼의 바이트 포인터 */
		BWT MLen, /**< [in] 암호화할 메시지 버퍼의 바이트 단위 길이 */
		const PKCryptPubKey *pubKey, /**< [in] RSAPubKey의 포인터 */
		const PKCryptParam *param, /**< [in] NULL */
		const void *hashAlg, /**< [in] OAEP를 적용할 대 사용할 hash 알고리즘 */
		const void *maskAlg /**< [in] masking algorithm */
		);

/** @ingroup PKCRYPT
    @brief RSA 공개키 복호화 함수
	@deprecated Use RSA or RSA21 algorithm instead
    @param M         [out] 복호화된 메시지가 저장될 버퍼의 포인터
    @param MLen      [in,out] 복호화된 메시지의 바이트 단위 길이 
    @param cipher    [in]  복호화할 메시지 버퍼의 바이트 포인터
    @param cipherLen [in]  복호화할 메시지 버퍼의 바이트 단위 길이 
    @param param     [in]  NULL  
    @param priKey    [in]  RSAPriKey의 포인터  
    @param hashAlg   [in]  사용할 hash 알고리즘의 descriptor; OAEP 방식에 한해서
    @param maskAlg   [in]  사용할 mask 알고리즘의 descriptor; 현재는 NULL을 입력해 사용
    @retval FAIL on fail
    @retval SUCCESS on success
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL 함수 출력이 저장될 파라미터의 메모리 버퍼 크기가 작을 때
    @retval ER_RSA_WRONG_CIPHER_LEN The length of cipher is wrong
    @retval ER_RSA_DECRYPT_ERROR RSA 의 복호화 과정이 잘못되었을 때
    
    RSA 알고리즘에서는 비공개키 구조체에 시스템 파라미터가 포함되어 있기 때문에 
    시스템 파라미터를 따로 입력 받을 필요가  없다. \e param은 다른 알고리즘과의 
    인터페이스 일치를 위해 포함된 인자이고, 내부에서 사용되지 않는다. NULL값을
    입력한다.

    hashAlg는 RSAES-OAEP 방식으로 복호화하길 원할 경우에만 입력한다.
    NULL값을 넣으면, RSAES-PKCS1-v1_5 방식으로 복호화된다.
    
    error code 중 ER_RSA_WRONG_CIPHER_LEN 은 입력된 암호문의 길이가 틀리다는
    에러이다. RSA 알고리즘으로 암호화된 암호문은 modulus N의 octet 단위 길이와
    일치해야만 한다. 따라서, 올바르게 생성된 암호문이라면, 올바른 길이를
    가지고 있을 것이다.

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
