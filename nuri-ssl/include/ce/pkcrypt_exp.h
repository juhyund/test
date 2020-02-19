#ifndef _PKCRYPT_EXP_H_
#define _PKCRYPT_EXP_H_

/** @defgroup PKCRYPT Public-Key Cryptography Expand
 * @ingroup CE
 * @brief Public-Key Cryptography Expand function
 */ 

#include <stdio.h>
#include "pkcrypt_op.h"

#ifdef EXPORT_CE
#include "ce_dll.h"
#else
#define LIBSPEC_CE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup PKCRYPT
    @brief 키쌍 확인 함수
	@return [out] check result
    @param[in]  priKey private key
    @param[in]  pubKey public key
    @param[in]  param Param 구조체
    @sa PKCRYPT_CheckKey

    Private/Public key가 서로 쌍이 맞는 지(개인키 내 공개키와 공개키가 일치하는지)만 확인한다.
*/
LIBSPEC_CE
ERT PKCRYPT_CheckKeyPair(const PKCryptPriKey *priKey,
                         const PKCryptPubKey *pubKey,
                         const PKCryptParam  *param);

/** @ingroup PKCRYPT */
LIBSPEC_CE
ERT PKCRYPT_SignHash(       PKCryptSig     *sig, /**< [out] */
                      const BYTE           *hash,  /**< [in] */
                            BWT             hashLen, /**< [in] */
                      const PKCryptPriKey  *priKey, /**< [in] */
                      const PKCryptParam   *param, /**< [in] */
                            AlgDesc         hashAlg, /**< [in] */
                      const void           *kcdsaPub /**< [in] */
					  );

/** @ingroup PKCRYPT */
LIBSPEC_CE  
ERT PKCRYPT_VerifyHash( const PKCryptSig     *sig, /**< [in] */
                        const BYTE           *hash, /**< [in] */
                              BWT             hashLen, /**< [in] */
                        const PKCryptPubKey  *pubKey, /**< [in] */
                        const PKCryptParam   *param, /**< [in] */
                              AlgDesc         hashAlg, /**< [in] */
                        const void           *kcdsaPub /**< [in] */
						);

/** @ingroup PKCRYPT
    @brief 공개키 서명 생성함수 
		@param sig [out] 서명 정보의 포인터
		@param msg [in] 서명할 메시지 버퍼의 바이트 포인터
		@param msgLen [in] 서명할 메시지 버퍼의 바이트 단위 길이
		@param priKey [in] 서명자의 비공개키 구조체의 포인터
    @param param [in] 도메인 파라미터 구조체의 포인터
		@param hashAlg [in] Hash 알고리즘의 descriptor
    @param kcdsaPubInfo [in] KCDSA를 사용할 경우 공개 정보
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
LIBSPEC_CE
ERT PKCRYPT_SignFile(       PKCryptSig     *sig,
                            FILE           *msg, 
                            BWT             msgLen,
                      const PKCryptPriKey  *priKey,
                      const PKCryptParam   *param,
                            AlgDesc         hashAlg,
                      const void           *kcdsaPubInfo);
  
/** @ingroup PKCRYPT
    @brief 공개키 서명 검증함수 
		@param sig [in] 서명 정보의 포인터
		@param msg [in] 서명 검증할 메시지 버퍼의 바이트 포인터
		@param msgLen [in] 서명 검증할 메시지 버퍼의 바이트 단위 길이
		@param pubKey [in] 서명자의 공개키 구조체의 포인터
    @param param [in] 도메인 파라미터 구조체의 포인터
		@param hashAlg [in] Hash 알고리즘의 descriptor
    @param kcdsaPubInfo [in] KCDSA를 사용할 경우 공개 정보
	@return [out] verification result
    @retval ER_PKCRYPT_VERIFY_SIG_OUT_OF_RANGE signature value is out of range
		@sa PKCRYPT_Sign, PKCRYPT_Verify, PKCRYPT_Decrypt, PKCRYPT_Create, PKCRYPT_Delete

		서명 정보의 포인터, 서명 검증할할 메시지 정보, 서명자의 공개키 정보,
    해쉬 알고리즘 descriptor를 입력으로 받아 서명 검증 결과를 리턴한다.
   
    kcdsaPubInfo는 KCDSA를 사용할 경우에 필요한 공개 정보이다. 새 버전의
    KCDSA(descriptor KCDSA1)는 서명자의 공개키가 되므로, 별도의 입력이
    필요없이 NULL값을 넘긴다. 이전 버전의 KCDSA(descriptor KCDSA)의 경우에는
    PKCRYPT_Sign과 마찬가지로 서명자의 공개키 인증서를 hash한 값이 저장된
    바이트 버퍼의 포인터를 넘겨 주어야 한다.
*/
LIBSPEC_CE
ERT PKCRYPT_VerifyFile( const PKCryptSig     *sig,
                              FILE           *msg,
                              BWT             msgLen,
                        const PKCryptPubKey  *pubKey,
                        const PKCryptParam   *param,
                              AlgDesc         hashAlg,
                        const void           *kcdsaPubInfo);

#ifdef __cplusplus
}
#endif

#endif /* _PKCRYPT_EXP_H_ */  

