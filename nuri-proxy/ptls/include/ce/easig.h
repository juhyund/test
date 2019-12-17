#ifndef _EA_SIG_H_
#define _EA_SIG_H_

/** @defgroup EA Entity Authentication
 * @ingroup SP
    @brief EA(Entity Authentication) 모듈
    */

/** @file easig.h
 * @ingroup SP
    @brief 서명을 이용한 객체인증의 인터페이스 정의
    
    서명을 이용한, 단방향/양방향 객체 인증을 구현한 모듈이다.
    */

#include "ckm_pkcrypt.h"
#include "sp_define.h"
#include "asn1.h"
#include "oid.h"
#include "x509pkc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EASIG_NONCE_LEN   16
#define EASIG_MSG_MAX_LEN 256

typedef struct {
  ASNSeqClass klass;
  OctetString *bNonce;
} EASIG_B_ChalToken;

LIBSPEC_SP
extern ASNDescriptor AD_EASIG_B_ChalToken;

typedef struct {
  ASNSeqClass klass;
  OctetString *aNonce;
  OctetString *bName;
  AlgorithmIdentifier *signatureAlgorithm;
  BitString *signatureValue;
  Certificate *cert;
} EASIG_A_RespToken;

LIBSPEC_SP
extern ASNDescriptor AD_EASIG_A_RespToken;

typedef struct {
  ASNSeqClass klass;
  OctetString *aName;
  AlgorithmIdentifier *signatureAlgorithm;
  BitString *signatureValue;
  Certificate *cert;
} EASIG_B_RespToken;

LIBSPEC_SP
extern ASNDescriptor AD_EASIG_B_RespToken;

/** @enum _EASIG_WAY
    @ingroup EA
    @brief 단방향/양방향 인증을 가리키는 값
    */
enum _EASIG_WAY {
  EASIG_UNI = 1,
  EASIG_MUT = 2,
};

/** @typedef EASIG_Context
    @ingroup EA
    @brief EASIG 인터페이스 간의 세션 정보를 담을 Context
    */
typedef struct _EASIG_Context {
  int way;
  EASIG_B_ChalToken *bChal;
  EASIG_A_RespToken *aResp;
  EASIG_B_RespToken *bResp;
} EASIG_Context;


/** @ingroup EA
    @brief EASIG_Context를 초기화한다.
    @param ctx [out] EASIG_Context의 포인터
    @param way [in]  단방향/양방향 옵션
    @sa EASIG_DelContext

    EASIG 인터페이스간의 세션 정보를 담은 EASIG_Context를 초기화한다.
    이 초기화 과정에서 메모리가 할당되므로, 사용이 끝난 EASIG_Context는
    반드시 EASIG_DelContext를 통하여, 메모리를 해제하여야 한다.

    또한, way 파라미터로 단방향/양방향 중에서 택1을 하여야 한다.
    단방향 인증일 경우는 EASIG_UNI를, 양방향 인증일 경우는 EASIG_MUT을
    입력값으로 주면 된다.

    A는 A-entity를 말하며, 최초로 인증을 요청하는 객체이다. B는 B-entity를
    말하며 challenge값을 보내는 객체이다. A와 B는 특별한 의미가 있은 것은
    아니며, 편의상 지어진 이름이다.


    단방향 프로토콜
    A <---------------------------   nonceOfB   ----------------------------- B
    A - nonceOfA||nameOfB||Sign(nonceOfA|nonceOfB|nameOfB|extOfA)||CertOfA -> B

    - 전자서명을 이용한 단방향 인증 과정
      -# EASIG_B_Challenge : B-entity는 nonceOfB를 생성하여 A-entity에게
           전달한다.
      -# EASIG_A_Response :  A-entity는 자신의 nonceOfA를 생성하여,B-entity가
           생성한 nonceOfB와 그 이름 nameOfB를 모두를 message로 하여
           전자서명하여 nonceOfA와 nameOfB와 함께 B에게 전달
      -# EASIG_B_Verify : B-entity는 A-entity의 response를 받고, nonceOfA를
            얻은 다음 방향성이 nameOfB임을 확인하고 전자서명을 검증하여
            인증한다.

    양방향 프로토콜
    A <---------------------------   nonceOfB   ----------------------------- B
    A - nonceOfA||nameOfB||Sign(nonceOfA|nonceOfB|nameOfB|extOfA)||CertOfA -> B
    A <---- nameOfA||Sign(nonceOfB||nonceOfA||nameOfA||extOfB)||CertOfB ----> B

    - 전자서명을 이용한 양방향 인증 과정
      -# EASIG_B_Challenge : B-entity는 nonceOfB를 생성하여 A-entity에게
           전달한다.
      -# EASIG_A_Response :  A-entity는 자신의 nonceOfA를 생성하여,B-entity가
           생성한 nonceOfB와 그 이름 nameOfB를 모두를 message로 하여
           전자서명하여 nonceOfA와 nameOfB와 함께 B에게 전달
      -# EASIG_B_Verify : B-entity는 A-entity의 response를 받고, nonceOfA를
            얻은 다음 방향성이 nameOfB임을 확인하고 전자서명을 검증하여
            인증한다.
      -# EASIG_B_Response : 그리고, B-entity는 nonceOfB nonceOfA와 nameOfB를
            메시지로 하여 전자서명하여 A에게 전달한다.
      -# EASIG_A_Verify : 마지막으로 A-entity는 B-entity의 response를 받은 다음,
            메시지의 방향성이 nameOfA임을 확인하고 전자서명을 검증하여 인증한다.
    */
LIBSPEC_SP
ERT EASIG_NewContext(EASIG_Context *ctx, int way);

/** @ingroup EA
    @brief EASIG_Context를 제거한다.
    @param ctx [in] EASIG_Context의 포인터
    @sa EASIG_NewContext

    EASIG_NewContext를 통하여 초기화된 EASIG_Context는, 이 함수를
    사용하여 할당된 메모리가 해제되어야 한다.
    */
LIBSPEC_SP
ERT EASIG_DelContext(EASIG_Context *ctx);

/** @ingroup EA
    @brief B-entity의 challenge값을 생성한다.
    @param bChallenge [out] 생성된 challenge값이 할당될 ASNBuf포인터의 포인터값
    @param bCtx       [in]  B-entity의 context
    @sa EASIG_NewContext EASIG_A_Response

    process-1 : challenge값의 생성하는 함수이다.
    */
LIBSPEC_SP
ERT EASIG_B_Challenge( ASNBuf        **bChallenge,
                       EASIG_Context  *bCtx);

/** @ingroup EA
    @brief A-entity의 response값을 생성한다.
    @param aResponse   [out] 생성된 response값이 할당될 ASNBuf포인터의 포인터값
    @param bChallenge  [in]  B-entity가 생성한 challenge값 
    @param aCtx        [in]  A-entity의 context
    @param priInfo     [in]  A-entity가 서명생성시 사용할 비공개키
    @param domainParam [in]  A-entity가 서명생성시 사용할 domainParam
    @param hashAlg     [in]  A-entity가 서명생성시 사용할 해쉬 알고리즘
    @param cert        [in]  A-entity의 인증서
    @param aExt        [in]  extension field의 값이 저장된 버퍼의 포인터
    @param aExtLen     [in]  extension field의 값의 바이트 단위 길이
    @sa EASIG_NewContext EASIG_B_Challenge EASIG_B_Verify

    process-2 : A-entity의 response를 생성하는 함수이다.
    
    aExt는 application에 따라서 A-entity의 response 중 전자서명할 메시지에
    추가적인 메시지를 덧붙일 필요가 있을 때, 사용할 수 있는 field이다.
    필요가 없을 때는 aExt를 NULL로 aExtLen은 0으로 셋팅하면 된다. 
    */
LIBSPEC_SP
ERT EASIG_A_Response( ASNBuf         **aResponse,
                      ASNBuf          *bChallenge,
                      char            *bName,
                      PrivateKeyInfo  *priInfo,
                      Parameter       *domainParam,
                      AlgDesc          hashAlg,
                      CERT            *cert,
                      EASIG_Context   *aCtx,
                      BYTE            *aExt,
                      BWT              aExtLen);

/** @ingroup EA
    @brief A-entity의 response 값을 검증한다.
    @param cert      [out] A-entity의 response에 포함된 A-entity의 인증서
    @param aRespnose [in]  A-entity가 생성한 response값
    @param bCtx      [in]  B-entity의 context
    @param aExt      [in]  extension field의 값이 저장된 버퍼의 포인터
    @param aExtLen   [in]  extension field의 값의 바이트 단위 길이
    @retval
    @sa EASIG_NewContext EASIG_A_Response EASIG_B_Response

    process-3 : B-entity가 A-entity의 reponse를 검증하는 함수이다.

    cert로 출력된 인증서는 검증되어야 모든 인증 프로세스를
    마치는 것이다. 인증서를 검증하는 과정은 이 모듈 밖의 일이다.

    aExt는 A-entity가 response를 생성할 시의 aExt와 동일하여야 한다.
    extension field를 활용할 시에는 두 객체 사이에 사전에 정보를 공유하거나
    같을 값을 가질 수 있는 방안이 있어야 할 것이다.
    */
LIBSPEC_SP
ERT EASIG_B_Verify( CERT          **cert,
                    ASNBuf         *aResponse,
                    EASIG_Context  *bCtx,
                    BYTE           *aExt,
                    BWT             aExtLen);

/** @ingroup EA
    @brief B-entity의 response값을 생성한다.
    @param bResponse   [out] 생성된 response값이 할당될 ASNBuf포인터의 포인터값
    @param aChallenge  [in]  A-entity가 생성한 challenge값 
    @param bCtx        [in]  B-entity의 context
    @param priInfo     [in]  B-entity가 서명생성시 사용할 비공개키
    @param domainParam [in]  B-entity가 서명생성시 사용할 domainParam
    @param hashAlg     [in]  B-entity가 서명생성시 사용할 해쉬 알고리즘
    @param cert        [in]  B-entity의 인증서
    @param bExt        [in]  extension field의 값이 저장된 버퍼의 포인터
    @param bExtLen     [in]  extension field의 값의 바이트 단위 길이
    @sa EASIG_NewContext EASIG_B_Verify EASIG_A_Verify

    process-4 : B-entity의 response를 생성하는 함수이다.
    
    bExt는 application에 따라서 B-entity의 response 중 전자서명할 메시지에
    추가적인 메시지를 덧붙일 필요가 있을 때, 사용할 수 있는 field이다.
    필요가 없을 때는 bExt를 NULL로 bExtLen은 0으로 셋팅하면 된다. 
    */
LIBSPEC_SP
ERT EASIG_B_Response( ASNBuf         **bResponse,
                      ASNBuf          *aResponse,
                      char            *aName,
                      PrivateKeyInfo  *priInfo,
                      Parameter       *domainParam,
                      AlgDesc          hashAlg,
                      CERT            *cert,
                      EASIG_Context   *bCtx,
                      BYTE            *bExt,
                      BWT              bExtLen);

/** @ingroup EA
    @brief B-entity의 response 값을 검증한다.
    @param cert      [out] B-entity의 response에 포함된 B-entity의 인증서
    @param bRespnose [in]  B-entity가 생성한 response값
    @param aCtx      [in]  A-entity의 context
    @param bExt      [in]  extension field의 값이 저장된 버퍼의 포인터
    @param bExtLen   [in]  extension field의 값의 바이트 단위 길이
    @retval
    @sa EASIG_NewContext EASIG_B_Response

    process-5 : A-entity가 B-entity의 reponse를 검증하는 함수이다.

    cert로 출력된 인증서는 검증되어야 모든 인증 프로세스를
    마치는 것이다. 인증서를 검증하는 과정은 이 모듈 밖의 일이다.

    bExt는 A-entity가 response를 생성할 시의 bExt와 동일하여야 한다.
    extension field를 활용할 시에는 두 객체 사이에 사전에 정보를 공유하거나
    같을 값을 가질 수 있는 방안이 있어야 할 것이다.
    */
LIBSPEC_SP
ERT EASIG_A_Verify( CERT         **cert,
                    ASNBuf        *bResponse,
                    EASIG_Context *aCtx,
                    BYTE          *bExt,
                    BWT            bExtLen);

#ifdef __cplusplus
}
#endif

#endif /* _EA_SIG_H_ */
