#ifndef _EA_HMAC_H_
#define _EA_HMAC_H_

/** @ingoup EA
    @file eahmac.h
    @brief HMAC을 이용한 객체인증의 인터페이스 정의

    HMAC을 이용한, 단방향/양방향 객체 인증을 구현한 모듈이다.
    */

#include "sp_define.h"
#include "asn1.h"
#include "pkcs.h"
#include "hmac.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EAHMAC_NONCE_LEN 16

typedef struct {
  ASNSeqClass klass;
  OctetString *bNonce;
} EAHMAC_B_ChalToken;

LIBSPEC_SP
extern ASNDescriptor AD_EAHMAC_B_ChalToken;

typedef struct {
  ASNSeqClass klass;
  OctetString *aNonce; /* optional */
  Digest *digest; 
} EAHMAC_A_RespToken;

LIBSPEC_SP
extern ASNDescriptor AD_EAHMAC_A_RespToken;

typedef struct {
  ASNSeqClass klass;
  Digest *digest;
} EAHMAC_B_RespToken;

LIBSPEC_SP
extern ASNDescriptor AD_EAHMAC_B_RespToken;

/** @enum _EAHMAC_WAY
    @ingroup EA
    @brief 단방향/양방향 인증을 가리키는 값
    */
enum _EAHMAC_WAY {
  EAHMAC_UNI = 1,
  EAHMAC_MUT = 2,
};

/** @typedef EAHMAC_Context
    @ingroup EA
    @brief EAHMAC 인터페이스 간의 세션 정보를 담을 Context
    */
typedef struct _EAHMAC_Context {
  int way;
  EAHMAC_B_ChalToken *bChal;
  EAHMAC_A_RespToken *aResp;
  EAHMAC_B_RespToken *bResp;
  BYTE key[HMAC_MAX_KEY_LEN];
  BWT keyLen;
  AlgDesc hashAlg;
} EAHMAC_Context;

/** @ingroup EA
    @brief EAHMAC_Context를 초기화한다.
    @param ctx     [out] EAHMAC_Context의 포인터
    @param key     [in]
    @param keyLen  [in]
    @param hashAlg [in]
    @param way     [in]  단방향/양방향 옵션
    @sa EAHMAC_DelContext

    A는 A-entity를 말하며, 최초로 인증을 요청하는 객체이다. B는 B-entity를
    말하며 challenge값을 보내는 객체이다. A와 B는 특별한 의미가 있은 것은
    아니며, 편의상 지어진 이름이다.

    단방향 프로토콜
    A <----       nonce      ----- B
    A ----- HMAC(nonce||ext) ----> B
  
    - HMAC을 이용한 단방향 인증 과정
      -# EAHMAC_B_Challenge : B-entity는 처음 nonce(random number)를 생성하여,
           A-entity에게 전달한다.
      -# EAHMAC_A_Response : Prover는 verifier로부터 받은 nonce로 HMAC을
           계산하여 A-entity에게 전달한다.
      -# EAHMAC_B_Verify : B-entity도 생성한 nonce로부터 HMAC을 계산하여
           A-entity가 응답한 값과 비교하여 검증한다.

    양방향 프로토콜
    A <-----------------------   nonceOfB   -------------------------- B
    A ----- noceOfA || HMAC(nonceOfA||nonceOfB||nameOfB||extOfA) ----> B
    A <-------------  HMAC(nonceOfB||nonceOfA||extOfB)  -------------- B

    - HMAC을 이용한 양방향 인증 과정
      -# EAHMAC_B_Challenge : B-entity는 nonceOfB를 생성하여 A-entity에게
           전달한다.
      -# EAHMAC_A_Respnse : A-entity는 자신의 nonceOfA를 생성하여, B-entity가
           생성한 nonceOfB와 그 이름 nameOfB를 모두를 message로 하여 HMAC값을
           계산하여 nonceOfA와 함께 B에게 전달
      -# EAHMAC_B_Verify : B-entity는 A-entity의 response를 받고, nonceOfA를
           얻은 다음 A-entity와 마찬가지로 HMAC값을 계산하여 인증한다.
      -# EAHMAC_B_Resonse : 그리고, B-entity는 nonceOfB nonceOfA를 메시지로
           하는 HMAC값을 계산하여 A에게 전달한다.
      -# EAHMAC_A_Verify : 마지막으로 A-entity는 B-entity의 response를 받은
           다음, 같은 메시지로 HMAC값을 계산하고 response의 값과 비교하여 인증한다.
    */
LIBSPEC_SP
ERT EAHMAC_NewContext( EAHMAC_Context *ctx,
                       BYTE           *key,
                       BWT             keyLen,
                       AlgDesc         hashAlg,
                       int             way);

/** @ingroup EA
    @brief EAHMAC_Context를 제거한다.
    @param ctx [in] EAHMAC_Context의 포인터
    @sa EAHMAC_NewContext

    EAHMAC_NewContext를 통하여 초기화된 EAHMAC_Context는, 이 함수를
    사용하여 할당된 메모리가 해제되어야 한다.
    */
LIBSPEC_SP
ERT EAHMAC_DelContext( EAHMAC_Context *ctx);

/** @ingroup EA
    @brief B-entity의 challenge값을 생성한다.
    @param bChallenge [out] 생성된 challenge값이 할당될 ASNBuf포인터의 포인터값
    @param bCtx       [in]  B-entity의 context
    @sa EAHMAC_NewContext EAHMAC_A_Response

    process-1 : challenge값의 생성하는 함수이다.
    */
LIBSPEC_SP
ERT EAHMAC_B_Challenge( ASNBuf         **bChallenge,
                        EAHMAC_Context  *bCtx);

/** @ingroup EA
    @brief A-entity의 response값을 생성한다.
    @param aResponse  [out] 생성된 response값이 할당될 ASNBuf포인터의 포인터값
    @param bChallenge [in]  B-entity가 생성한 challenge값 
    @param aCtx       [in]  A-entity의 context
    @param aExt       [in]  extension field의 값이 저장된 버퍼의 포인터
    @param aExtLen    [in]  extension field의 값의 바이트 단위 길이
    @sa EAHMAC_NewContext EAHMAC_B_Challenge EAHMAC_B_Verify

    process-2 : A-entity의 response를 생성하는 함수이다.
    
    aExt는 application에 따라서 A-entity의 response 중 HMAC을 생성할 메시지에
    추가적인 메시지를 덧붙일 필요가 있을 때, 사용할 수 있는 field이다.
    필요가 없을 때는 aExt를 NULL로 aExtLen은 0으로 셋팅하면 된다. 
    */
LIBSPEC_SP
ERT EAHMAC_A_Response( ASNBuf         **aResponse,
                       ASNBuf          *bChallenge,
                       char            *bName,
                       EAHMAC_Context  *aCtx,
                       BYTE            *aExt,
                       BWT              aExtLen);

/** @ingroup EA
    @brief A-entity의 response 값을 검증한다.
    @param aRespnose [in] A-entity가 생성한 response값
    @param bName     [in] B-entity의 이름
    @param bCtx      [in] B-entity의 context
    @param aExt       [in] extension field의 값이 저장된 버퍼의 포인터
    @param aExtLen    [in] extension field의 값의 바이트 단위 길이
    @sa EAHMAC_NewContext EAHMAC_A_Response EAHMAC_B_Response

    process-3 : B-entity가 A-entity의 response를 검증하는 함수이다.

    aExt는 A-entity가 response를 생성할 시의 aExt와 동일하여야 한다.
    extension field를 활용할 시에는 두 객체 사이에 사전에 정보를 공유하거나
    같을 값을 가질 수 있는 방안이 있어야 할 것이다.
    */
LIBSPEC_SP
ERT EAHMAC_B_Verify( ASNBuf         *aResponse,
                     char           *bName,
                     EAHMAC_Context *bCtx,
                     BYTE           *aExt,
                     BWT             aExtLen);

/** @ingroup EA
    @brief B-entity의 response값을 생성한다.
    @param bResponse  [out] 생성된 response값이 할당될 ASNBuf포인터의 포인터값
    @param aChallenge [in]  B-entity가 생성한 challenge값 
    @param bCtx       [in]  B-entity의 context
    @param bExt       [in]  extension field의 값이 저장된 버퍼의 포인터
    @param bExtLen    [in]  extension field의 값의 바이트 단위 길이
    @sa EAHMAC_B_Challenge EAHMAC_B_Verify

    process-4 : B-entity의 response를 생성하는 함수이다.
    
    bExt는 application에 따라서 B-entity의 response 중 전자서명할 메시지에
    추가적인 메시지를 덧붙일 필요가 있을 때, 사용할 수 있는 field이다.
    필요가 없을 때는 bExt를 NULL로 bExtLen은 0으로 셋팅하면 된다. 
    */
LIBSPEC_SP
ERT EAHMAC_B_Response( ASNBuf         **bResponse,
                       ASNBuf          *aResponse,
                       EAHMAC_Context  *bCtx,
                       BYTE            *bExt,
                       BWT              bExtLen);

/** @ingroup EA
    @brief B-entity의 response 값을 검증한다.
    @param bRespnose [in] B-entity가 생성한 response값
    @param aCtx      [in] A-entity의 context
    @param bExt      [in] extension field의 값이 저장된 버퍼의 포인터
    @param bExtLen   [in] extension field의 값의 바이트 단위 길이
    @sa EAHMAC_NewContext EAHMAC_B_Response

    process-5 : A-entity가 B-entity의 response를 검증하는 함수이다.

    bExt는 B-entity가 response를 생성할 시의 bExt와 동일하여야 한다.
    extension field를 활용할 시에는 두 객체 사이에 사전에 정보를 공유하거나
    같을 값을 가질 수 있는 방안이 있어야 할 것이다.
    */
LIBSPEC_SP
ERT EAHMAC_A_Verify( ASNBuf         *bResponse,
                     EAHMAC_Context *aCtx,
                     BYTE           *bExt,
                     BWT             bExtLen);

#ifdef __cplusplus
}
#endif

#endif /* _EA_HMAC_H_ */
