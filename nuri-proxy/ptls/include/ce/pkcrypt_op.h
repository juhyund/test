#ifndef _PKCRYPT_OP_H_
#define _PKCRYPT_OP_H_

/** @defgroup PKCRYPT Public-Key Cryptography
 * @ingroup CC
 * @brief Public-Key Cryptography
 */ 

/** @defgroup PKCRYPT_ALG Algorithm Descriptors
 * @ingroup PKCRYPT
 * @brief PKCRYPT Algorithm Descriptors
 */

/** @file pkcrypt_op.h
 * @ingroup PKCRYPT
 */

#include <stdio.h>
#include "cc_define.h"
#include "mint_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup PKCRYPT
    @brief PKCryptAlgorithm 구조체

		알고리즘 descriptor, 알고리즘의 정보를 가지고 있다. 이 구조체의 멤버는
    각 알고리즘 모듈 내부에서 결정되는 것으로 사용자가 임의로 내용을 변경하면
    안된다. 현재 지원되는 descriptor로는 KCDSA, KCDSA1, RSA, DSA, ECDSA, ECKCDSA 가 있다.
*/
typedef struct {
  ERT   (*signFunc)(); /**< 서명 생성 함수 포인터 */
  ERT   (*verifyFunc)(); /**< 서명 검증 함수 포인터 */
  ERT   (*signFileFunc)(); /**< 파일 서명 함수 생성 포인터 */
  ERT   (*verifyFileFunc)(); /**< 파일 서명 검증 함수 포인터 */
  ERT   (*encFunc)(); /**< 암호화 함수 포인터 */
  ERT   (*decFunc)(); /**< 복호화 함수 포인터 */
  ERT   (*genParam)(); /**< 파라미터 생성 함수 포인터 */
  ERT   (*genKey)(); /**< 키 생성 함수 포인터 */
  ERT   (*checkParam)(); /**< 파라미터 유효성 검증 함수 포인터 */
  ERT   (*checkKey)(); /**< 키 일치 확인 함수 포인터 */
  ERT   (*checkKeyPair)(); /**< 개인키 구조체 내 공개키와 공개키 일치 확인 함수 포인터 */
  BWT     priKeySize; /**< 개인키의 바이트 크기*/
  BWT     pubKeySize; /**< 공개키의 바이트 크기 */ 
  BWT     paramSize; /**< 파라미터의 바이트 크기 */ 
  BWT     sigSize; /**< 서명 값의 바이트 크기 */ 
  BWT     idx; /**< KCDSA가 아닐 경우 0, KCDSA일 경우, old version = 1, new version = 2*/

  ERT   (*signHashFunc)(); /**< 해시 값에 대한 서명 생성 함수 포인터 */
  ERT   (*verifyHashFunc)(); /**< 해시 값에 대한 서명 검증 함수 포인터 */
} PKCryptAlgorithm;

/** @brief 공개키 서명 값의 최대 바이트 길이 */
#define PKCRYPT_MAX_SIG_LEN (MINT_SIZE<<1)

/** @ingroup PKCRYPT
    @brief 서명값을 의미하는 구조체
*/
typedef struct {
  AlgDesc alg;
  BYTE val[PKCRYPT_MAX_SIG_LEN];
} PKCryptSig;

struct _pkc_data {
  AlgDesc alg; /**< 알고리즘 지시자 */
  void *val; /**< 데이터(ex. 비밀키, 공개키, 등) */
}; 


/** @ingroup PKCRYPT
    @brief 도메인 파라미터를 의미하는 구조체
*/
typedef struct _pkc_data PKCryptParam;

/** @ingroup PKCRYPT
    @brief 비공개키를 의미하는 구조체
*/
typedef struct _pkc_data PKCryptPriKey;

/** @ingroup PKCRYPT
    @brief 공개키를 의미하는 구조체
*/
typedef struct _pkc_data PKCryptPubKey;

/** @ingroup PKCRYPT
    @brief 도메인 파라미터 구조체인 PKCryptParam을 할당한다.
    @param[in]  pkAlg 알고리즘 descriptor
    @return [out] 할당된 구조체의 포인터값을 리턴
    @sa PKCRYPT_DelParam PKCRYPT_NewPriKey PKCRYPT_NewPubKey

    알고리즘 descriptor를 입력 받아, 알고리즘에 해당하는
    도메인 파라미터, PKCryptParam 구조체를 할당하여 포인터를 리턴한다.

    알고리즘 descriptor는 알고리즘의 각종 정보를 담고 있는 global 구조체
    인스턴스로서, KCDSA, KCDSA1, RSA, DSA가 존재한다.
*/
LIBSPEC
PKCryptParam*  PKCRYPT_NewParam(AlgDesc pkAlg);

/** @ingroup PKCRYPT
    @brief 메모리에 할당된 PKCryptParam 구조체를 해제한다.
    @param[in]  param PKCryptParam 구조체의 포인터값
    @sa PKCRYPT_NewParam PKCRYPT_DelPriKey PKCRYPT_DelPubKey

*/
LIBSPEC
void PKCRYPT_DelParam(PKCryptParam *param);

/** @ingroup PKCRYPT
    @brief 비공개키 구조체인 PKCryptPriKey을 할당한다.
    @param[in]  pkAlg 알고리즘 descriptor
    @return [out] 할당된 구조체의 포인터값을 리턴
    @sa PKCRYPT_DelPriKey PKCRYPT_NewParam PKCRYPT_NewPubKey

    알고리즘 descriptor를 입력으로 받아, 알고리즘에 해당하는
    비공개키인 PKCryptPriKey 구조체를 할당하여 포인터를 리턴한다.
*/
LIBSPEC
PKCryptPriKey* PKCRYPT_NewPriKey(AlgDesc pkAlg);

/** @ingroup PKCRYPT
    @brief 메모리에 할당된 PKCryptPriKey 구조체를 제로화하고, 해제한다.
    @sa PKCRYPT_NewPriKey PKCRYPT_DelParam PKCRYPT_DelPubKey
*/
LIBSPEC
void PKCRYPT_DelPriKey(
		PKCryptPriKey *priKey /**< [in] PKCryptPriKey 구조체의 포인터값 */
		);

/** @ingroup PKCRYPT
    @brief 공개키 구조체인 PKCryptPubKey을 할당한다.
    @param pkAlg [in] 알고리즘 descriptor
    @return [out] 할당된 구조체의 포인터값을 리턴
    @sa PKCRYPT_DelPriKey PKCRYPT_NewParam PKCRYPT_NewPriKey

    알고리즘 descriptor를 입력으로 받아, 알고리즘에 해당하는
    공개키인 PKCryptPubKey 구조체를 할당하여 포인터를 리턴한다.
*/
LIBSPEC
PKCryptPubKey* PKCRYPT_NewPubKey(AlgDesc pkAlg);

/** @ingroup PKCRYPT
    @brief 메모리에 할당된 PKCryptPubKey 구조체를 제로화하고, 해제한다.
    @sa PKCRYPT_NewPubKey PKCRYPT_DelParam PKCRYPT_DelPriKey
*/
LIBSPEC
void PKCRYPT_DelPubKey(
		PKCryptPubKey *pubKey /**< [in] public key to be deleted */
		);

/** @ingroup PKCRYPT
    @brief 파라미터 생성 함수
    @sa PKCRYPT_CheckParam PKCRYPT_GenKey PKCRYPT_CheckKey
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시

    도메인의 쓰일 파라미터를 생성한다. param은 Param 구조체이며,
    각 알고리즘별로, DSAParam, KCDSAParam 의 구조체 변수가
    입력되어야 한다.
*/
LIBSPEC
ERT PKCRYPT_GenParam(
		PKCryptParam *param, /**< [in,out] 생성된 파라미터 */
		BWT pBitLen, /**< [in] p의 비트 길이 */
		BWT qBitLen /**< [in] q의 비트 길이 */
		);

/** @ingroup PKCRYPT
 * @return [out] check result
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @brief 파라미터 검증 함수
    @sa PKCRYPT_GenParam PKCRYPT_GenKey PKCRYPT_CheckKey

    param 에 저장된 도메인 변수가 유효한 값들인지를 검증한다.
*/
LIBSPEC
ERT PKCRYPT_CheckParam(
		const PKCryptParam *param /**< [in] parameter to be checked */
		);

/** @ingroup KEYGEN
    @brief 키 생성 함수
    @sa PKCRYPT_GenParam PKCRYPT_CheckParam PKCRYPT_CheckKey
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @retval ER_CONDITIONAL_SELFTEST 키쌍 일치 시험 실패하였을 경우

    Private/Public key pair를 생성하는 함수이다. 도메인 변수를 가지는
    알고리별 Param(DsaParam, KcdsaParam, RsaParam) 구조체와 알고리즘
    descriptor를 입력하면, priKey와 pubKey에 생성된 key pair가 저장된다.
    priKey와 pubKey는 각 알고리즘의 key 구조체의 포인터값이다.

    RSA를 사용할 경우, dlParam = NULL, rsaNLen = |n|를 입력하고,
    이외의 경우, rsaNLen = 0을 입력해야한다.
*/
LIBSPEC
ERT PKCRYPT_GenKey(
		PKCryptPriKey *priKey, /**< [in,out] generated private key */
		PKCryptPubKey *pubKey, /**< [in,out] generated public key */
		const PKCryptParam *dlParam, /**< [in] parameter for discret
									   logarithm-based algorithms */
		BWT rsaNLen /**< [in] desired modulus length for RSA algorithm */
		);

/** @ingroup PKCRYPT
    @brief 키 유효성 검증 함수
	@return [out] check result
    @param[in]  priKey private key
    @param[in]  pubKey public key
    @param[in]  param Param 구조체
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @sa PKCRYPT_GenParam PKCRYPT_CheckParam PKCRYPT_GenKey PKCRYPT_CheckKeyPair

    Private/Public key가 유효한 key인지를 검증한다. PKCRYPT_CheckKeyPair가 수행
    하는 키쌍이 맞는 지(개인키 내 공개키와 공개키가 일치하는지)의 여부에 대한 확인도 포함된다.
*/
LIBSPEC
ERT PKCRYPT_CheckKey(const PKCryptPriKey *priKey,
                     const PKCryptPubKey *pubKey,
                     const PKCryptParam  *param);

/** @ingroup PKCRYPT
    @brief 공개키 서명 생성함수 
	@param[out]  sig 서명 정보의 포인터
	@param[in]  msg 서명할 메시지 버퍼의 바이트 포인터
	@param[in]  msgLen 서명할 메시지 버퍼의 바이트 단위 길이
	@param[in]  priKey 서명자의 비공개키 구조체의 포인터
    @param[in]  param 도메인 파라미터 구조체의 포인터
	@param[in]  hashAlg Hash 알고리즘의 descriptor
    @param[in]  kcdsaPubInfo KCDSA를 사용할 경우 공개 정보
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @retval ER_RSA_ENCODING_ERROR RSA의 인코딩 과정이 잘못되었을 때
	@sa PKCRYPT_Verify, PKCRYPT_Verify, PKCRYPT_Decrypt, PKCRYPT_Create, PKCRYPT_Delete

		서명할 메시지 정보, 서명자의 비공개키 정보,
    해쉬 알고리즘 descriptor 입력으로 받아 서명 정보의 포인터를 리턴한다.

    kcdsaPubInfo는 KCDSA를 사용할 경우에 필요한 공개 정보이다. 새 버전의
    KCDSA는 (descriptor KCDSA1) 서명자의 공개키(PKCryptPubKey)의 포인터를
    넘겨 주고, 이전 버전의 KCDSA 경우는(descriptor KCDSA) 서명자의 공개키
    인증서를 hash한 값이 저장된 바이트 버퍼의 포인터를 넘겨 주게 된다.
    
		알고리즘별 서명 정보 타입, 비공개키 타입의 정의는 각 알고리즘 헤더 파일을
    참조한다.
		
*/
LIBSPEC
ERT PKCRYPT_Sign(       PKCryptSig     *sig,
                  const BYTE           *msg, 
                        BWT             msgLen,
                  const PKCryptPriKey  *priKey,
                  const PKCryptParam   *param,
                        AlgDesc         hashAlg,
                  const void           *kcdsaPubInfo);
  
/** @ingroup PKCRYPT
    @brief 공개키 서명 검증함수 
	@param[in]  sig 서명 정보의 포인터
	@param[in]  msg 서명 검증할 메시지 버퍼의 바이트 포인터
	@param[in]  msgLen 서명 검증할 메시지 버퍼의 바이트 단위 길이
	@param[in]  pubKey 서명자의 공개키 구조체의 포인터
    @param[in]  param 도메인 파라미터 구조체의 포인터
	@param[in]  hashAlg Hash 알고리즘의 descriptor
    @param[in]  kcdsaPubInfo KCDSA를 사용할 경우 공개 정보
	@return [out] verification result
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @retval ER_RSA_VP1_SIG_OUT_OF_RANGE RSA 의 서명 값이 올바르지 않을 때
    @retval ER_RSA_INCONSISTENT RSA 의 서명 검증 결과가 서명 생성 결과와 불일치할 때
    @retval ER_KCDSA_VP_SIG_OUT_OF_RANGE KCDSA 의 서명 값이 올바르지 않을 때
	@sa PKCRYPT_Sign, PKCRYPT_Verify, PKCRYPT_Decrypt, PKCRYPT_Create, PKCRYPT_Delete

		서명 정보의 포인터, 서명 검증할할 메시지 정보, 서명자의 공개키 정보,
    해쉬 알고리즘 descriptor를 입력으로 받아 서명 검증 결과를 리턴한다.
   
    kcdsaPubInfo는 KCDSA를 사용할 경우에 필요한 공개 정보이다. 새 버전의
    KCDSA(descriptor KCDSA1)는 서명자의 공개키가 되므로, 별도의 입력이
    필요없이 NULL값을 넘긴다. 이전 버전의 KCDSA(descriptor KCDSA)의 경우에는
    PKCRYPT_Sign과 마찬가지로 서명자의 공개키 인증서를 hash한 값이 저장된
    바이트 버퍼의 포인터를 넘겨 주어야 한다.
*/
LIBSPEC
ERT PKCRYPT_Verify( const PKCryptSig     *sig,
                    const BYTE           *msg,
                          BWT             msgLen,
                    const PKCryptPubKey  *pubKey,
                    const PKCryptParam   *param,
                          AlgDesc         hashAlg,
                    const void           *kcdsaPubInfo);

/** @ingroup PKCRYPT
    @brief 공개키 암호화 함수 
	@param cipher [out] 암호화된 결과가 저장될 버퍼를 가리키는 포인터
	@param cipherLen [in,out] IN: cipher의 메모리 버퍼 크기, OUT: 암호화된 결과의 바이트 단위 길이가 저장
	@param plain [in]  암호화할 데이터가 저장되어 있는 버퍼를 가리키는 포인터
	@param plainLen [in]  암호화할 데이터의 바이트 단위 길이
	@param pubKey [in]  공개키 구조체의 포인터
    @param param [in] 도메인 파라미터 구조체의 포인터
	@param hashAlg [in]  Hash 알고리즘의 descriptor
	@param maskAlg [in]  Mask 알고리즘의 descriptor; 향후 지원 예정, 현재는 NULL을 입력하여 사용
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL 함수 출력이 저장될 파라미터의 메모리 버퍼 크기가 작을 때
    @retval ER_RSA_MESSAGE_TOO_LONG RSA 의 메시지가 길 때

    @sa PKCRYPT_Decrypt, PKCRYPT_Sign, PKCRYPT_Verify, PKCRYPT_Create, PKCRYPT_Delete

		평문(plain), 공개키 정보, 해쉬 알고리즘 descriptor, Mask 알고리즘
    descriptor를 입력으로 받아 암호화하고 암호문(cipher)을 출력한다.
    
    maskAlg는 암호화에 필요한 mask algorithm을 선택하기 위한 값으로 향후
    확장을 위하여 존재하는 parameter이다. 현재는 NULL값을 주기 바란다.
*/
LIBSPEC
ERT PKCRYPT_Encrypt(       BYTE           *cipher,
                           BWT            *cipherLen,
                     const BYTE           *plain,
                           BWT             plainLen,
                     const PKCryptPubKey  *pubKey,
                     const PKCryptParam   *param,
                           AlgDesc         hashAlg,
                     const void           *maskAlg);

/** @ingroup PKCRYPT
    @brief 공개키 복호화 함수 
	@param plain [out] 복호화된 결과가 저장될 버퍼를 가리키는 포인터
	@param plainLen [in,out] IN: plain의 메모리 버퍼 크기, OUT: 복호화된 결과의 바이트 단위 길이가 저장
	@param cipher [in] 복호화할 데이터가 저장되어 있는 버퍼를 가리키는 포인터
	@param cipherLen [in] 복호화할 데이터의 바이트 단위 길이
	@param priKey [in] 비공개키 구조체의 포인터
    @param param [in] 도메인 파라미터 구조체의 포인터
	@param hashAlg [in] Hash 알고리즘의 descriptor
	@param maskAlg [in] Mask 알고리즘의 descriptor; 향후 지원 예정, 현재는 NULL을 입력하여 사용
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL 함수 출력이 저장될 파라미터의 메모리 버퍼 크기가 작을 때
    @retval ER_RSA_WRONG_CIPHER_LEN The length of cipher is wrong
    @retval ER_RSA_DECRYPT_ERROR RSA 의 복호화 과정이 잘못되었을 때
	@sa PKCRYPT_Encrypt, PKCRYPT_Sign, PKCRYPT_Verify, PKCRYPT_Create, PKCRYPT_Delete

		암호문(cipher), 공개키 정보, 해쉬 알고리즘 descriptor, Mask 알고리즘
    descriptor를 입력으로 받아 복호화하고 평문(plain)을 출력한다.
    
    maskAlg는 암호화에 필요한 mask algorithm을 선택하기 위한 값으로 향후
    확장을 위하여 존재하는 parameter이다. 현재는 NULL값을 주기 바란다.
*/
LIBSPEC
ERT PKCRYPT_Decrypt(       BYTE           *plain,
                           BWT            *plainLen,
                     const BYTE           *cipher,
                           BWT             cipherLen,
                     const PKCryptPriKey  *priKey,
                     const PKCryptParam   *param,
                           AlgDesc         hashAlg,
                     const void           *maskAlg);

#ifdef __cplusplus
}
#endif

#endif /* _PKCRYPT_OP_H_ */  

