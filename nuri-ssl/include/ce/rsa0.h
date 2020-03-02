#ifndef _RSA0_H_
#define _RSA0_H_

/** @defgroup RSA0
 * @ingroup PKCRYPT_ALG
 * @brief obsolete variant of RSA (for compatilibity)
 *
 * RSA0는 예전 버그가 있던 Penta의 라이브러리인 issaclib의 RSA 알고리즘을
 * 말하는 것이다. ISSAC-Web은 issaclib을 쓰고 있기 때문에 구버전과의
 * 호환성때문에 RSA0는 탄생되었다.   
 */

/** @file rsa0.h
    @ingroup RSA0
    @brief RSA0 알고리즘을 사용하기 위한 인터페이스 
    
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
    @brief RSA0 공개키 구조체
	@deprecated
    @sa RSA0PriKey

    RSA0 공개키 구조체이다. 
*/    
typedef struct {
  MINT    N;  /**< mudulus */
  MINT    e;  /**< public Exponent */
} RSA0PubKey;

/** @ingroup RSA0
    @brief RSA0 비공개키 구조체
	@deprecated
    @sa RSA0PubKey

    RSA0 비공개키 구조체이다. 
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
    @brief RSA0 알고리즘 descriptor인 rsa0 전역 변수의 주소값 rename
	@deprecated
    */
#define RSA0 &rsa0

/** @ingroup RSA0
    @brief RSA0 공개키 암호화 함수
	@deprecated
    @param cipher    [out] 암호화된 메시지가 저장될 버퍼의 포인터
    @param cipherLen [in]  암호화된 메시지의 바이트 단위 길이 
    @param M         [in]  암호화할 메시지 버퍼의 바이트 포인터
    @param MLen      [in]  암호화할 메시지 버퍼의 바이트 단위 길이 
    @param param     [in]  NULL  
    @param pubKey    [in]  RSA0PubKey의 포인터  
    @param hashAlg   [in]  사용할 hash 알고리즘의 descriptor; OAEP 방식에 한해서
    @param maskAlg   [in]  사용할 mask 알고리즘의 descriptor; 현재는 NULL을 입력해 사용
    @retval ER_RSA0_MESSAGE_TOO_LONG The length of message(MLen) is too long.
    
    RSA0 알고리즘에서는 비공개키 구조체에 시스템 파라미터가 포함되어 있기 때문에 
    시스템 파라미터를 따로 입력 받을 필요가  없다. \e param은 다른 알고리즘과의 
    인터페이스 일치를 위해 포함된 인자이고, 내부에서 사용되지 않는다. NULL값을
    입력한다.

    hashAlg는 RSA0ES-OAEP 방식으로 암호화하길 원할 경우에만 입력한다.
    NULL값을 넣으면, RSA0ES-PKCS1-v1_5 방식으로 암호화된다.

    error code 중 ER_RSA0_MESSAGE_TOO_LONG은 입력 M의 바이트 길이 MLen이 너무
    클 경우 리턴되는 코드이다. Modulus N의 바이트단위 길이를 k라 하고,
    사용하는 해쉬 알고리즘의 결과값이 hLen 이라 하면,
    MLen < k-2hLen-2 이어야 한다.
    예를 들어 SHA-1을 쓰는 RSA0 1024bit(N이 1024bit)일 경우에는 k값이 128이
    되고 hLen 값은 20이 되므로 MLen < 128-2*20-2 (= 87) 이 된다. 따라서, MLen
    은 최대 86바이트까지만 허용되는 것이다.
    
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
    @brief RSA0 공개키 복호화 함수
	@deprecated
    @param M         [out] 복호화된 메시지가 저장될 버퍼의 포인터
    @param MLen      [out] 복호화된 메시지의 바이트 단위 길이 
    @param cipher    [in]  복호화할 메시지 버퍼의 바이트 포인터
    @param cipherLen [in]  복호화할 메시지 버퍼의 바이트 단위 길이 
    @param param     [in]  NULL  
    @param priKey    [in]  RSA0PriKey의 포인터  
    @param hashAlg   [in]  사용할 hash 알고리즘의 descriptor; OAEP 방식에 한해서
    @param maskAlg   [in]  사용할 mask 알고리즘의 descriptor; 현재는 NULL을 입력해 사용
    @retval ER_RSA0_WRONG_CIPHER_LEN The length of cipher is wrong
    
    RSA0 알고리즘에서는 비공개키 구조체에 시스템 파라미터가 포함되어 있기 때문에 
    시스템 파라미터를 따로 입력 받을 필요가  없다. \e param은 다른 알고리즘과의 
    인터페이스 일치를 위해 포함된 인자이고, 내부에서 사용되지 않는다. NULL값을
    입력한다.

    hashAlg는 RSA0ES-OAEP 방식으로 복호화하길 원할 경우에만 입력한다.
    NULL값을 넣으면, RSA0ES-PKCS1-v1_5 방식으로 복호화된다.
    
    error code 중 ER_RSA0_WRONG_CIPHER_LEN 은 입력된 암호문의 길이가 틀리다는
    에러이다. RSA0 알고리즘으로 암호화된 암호문은 modulus N의 octet 단위 길이와
    일치해야만 한다. 따라서, 올바르게 생성된 암호문이라면, 올바른 길이를
    가지고 있을 것이다.

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
    @brief RSA0 의 integer를 octet string으로 전환하는 함수
	@deprecated
    @param byteArray [out] 전환된 octet string
    @param byteLen [out] 생성될 public key가 저장될 RSA0PubKey 구조체
    @param nLen      [in]  생성하고자 하는 modulus N 의 bit 단위 길이
    @sa MINT_WriteInByteArray

    PKCS#1 ver 2.0(RFC2437)에 설명된 integer를 octet string으로
    전환하는 함수이다.  이전에는 MINT_WriteInByteArray() 함수를
    사용하였으나, 이 함수에서는 상위 byte들의 값이 0일 경우 이를 의미없는
    값으로 판단하고 삭제해버리기 때문에 항상 길이가 modulus 길이와
    같아야만 하는 RSA0 서명값 생성에서 가끔 문제를
    일으켰다.  이 함수는 MINT_WriteInByteArray()와 거의 같은 역할을 하나
    PKCS#1에서 설명한 대로 입력의 길이를 절대 변환하지 않고 그대로 내보내는
    특성을 가진다.

    */
LIBSPEC_CE
ERT RSA0_I2OSP(BYTE *byteArray, BWT *byteLen, const MINT *a);

#ifdef __cplusplus
}
#endif

#endif /* _RSA0_H_ */  
