#ifndef _KEDH_H_
#define _KEDH_H_

/** @defgroup KEA
 * @ingroup SP
 * @brief Key Exchange Algorithm interface (legacy).
 * Use @ref KEX interface instead.
 */

/** @file kedh.h
    @ingroup KEA
    @brief Diffie-Hellman 방식의 KE 모듈

    Key Exchagne 방식 중 Diffie-Hellman 방식을 이용한 프로토콜이다.
    향후, RFC2631 지원을 고려하여 만들어져 있다.
    
*/

#include "sp_define.h"
#include "asn1.h"
#include "mint_common.h"
#include "dh.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEDH_MINT_MAX_LEN (MINT_MANIPULATED_DATA_BIT_LEN/8)
 
typedef struct {
  ASNSeqClass klass;
  Integer *y;
  OctetString *keyInfo;
} KEDHInfo;

LIBSPEC_SP 
extern ASNDescriptor AD_KEDHInfo;

/* 향후 지원
typedef struct {
  ASNSeqClass klass;
  AsnOid algorithm;
  OctetString counter;
} KeySpecificInfo;
 
typedef struct {
  ASNSeqClass klass;
  KeySpecificInfo keyInfo;
  OctetString partyAInfo;
  OctetString suppPubInfo;
} OtherInfo;
*/  

/**
    @ingroup KEA
    @brief KEDH을 사용하기 위한 정보를 담을 구조체

    keyLen과 hashAlg은 KEDH_GenKey에서 사용하는 값이다. 키 길이는 기본적으로 
    이 구조체에 설정된 keyLen을 따르지만, RFC2631 방식일 경우에는 이 값을 
    사용하지 않는다.
   
*/
/* see cc/dh.h
typedef PCIS_DH_Context KEDH_Context;
*/

/** @ingroup KEA
    @brief KEDH_Context를 초기화 하는 함수

    @param ctx [out]     초기화 대상인 KEDH_Context의 포인터
    @param p [in]       시스템 파라미터 p
    @param q [in]       시스템 파라미터 q
    @param g [in]       시스템 파라미터 g
    @param x [in]       자신의 private info or private key
    @param yR [in]      상대방의 public info or public key
    @param keyLen [in]  키생성시 사용할 키의 바이트 길이
    @param hashAlg [in] hash 알고리즘 descriptor

    x와 yR은 고정된 값을 사용하는 경우, 초기화 함수로 입력하여 사용해야 한다.
    그렇지 않을 경우 x, yR에 입력으로 NULL을 주면 내부에서 생성하여 사용한다.
*/    
LIBSPEC_SP
ERT KEDH_Initialize
   (KEDH_Context *ctx, MINT *p, MINT *q, MINT *g, 
   MINT *x, MINT *yR, BWT keyLen, const void *hashAlg);

/** @ingroup KEA
    @brief ShareInfo를 생성하는 함수

    @param shareInfo [out]  키공유 정보인 shareInfo의 포인터
    @param keyInfo [in]    현재는 NULL을 입력
    @param ctx [in]        KEDH_Context의 포인터
    
    KEDH_Context 타입인 ctx와 ASNBuf 타입인 keyInfo를 입력으로 받아 키공유를 하기 위해 
    상대방에게 보낼 ASNBuf 타입의 shareInfo를 생성한다.
   
    지금은 keyInfo는 사용하지 않는다. NULL을 입력하여 사용한다.

    현재는 Diffie-Hellmac Basic Protocol 방식만 구현되어 있다. 
    (RFc2631 방식은 추후 구현한다.)
*/
LIBSPEC_SP 
ERT KEDH_GenShareInfo(ASNBuf **shareInfo, ASNBuf *keyInfo, KEDH_Context *ctx);

/* 향후 지원
LIBSPEC_SP
ERT KEDH_GenKeyInfo(ASNBuf **keyInfo, ...);
*/

/** @ingroup KEA
    @brief 키 생성 함수

    @param key [out]         생성된 키가 저장될 바이트 포인터
    @param keyLen [out]      생성된 키의 바이트 단위 길이
    @param shareInfo [in]   키공유할 상대방이 보낸 정보의 ASNBuf 타입 포인터
    @param ctx [in]         KEDH_Context 구조체의 포인트
     
    ASNBuf 타입인 shareInfo와 KEDH_Context 타입인 ctx를 입력으로 받아
    key를 출력한다. 
    이때 키 길이는 기본적으로 ctx의 keyLen을 따르지만,
    RFC2631을 따르는 경우에는 shareInfo 내의 keyInfo의 키 길이를 따른다.
    때문에 그경우에는 해당 길이의 키길이가 keyLen으로 출력된다.
    keyInfo를 사용하지 않을 경우에는 ctx의 keyLen의 길이가 출력된다.
     
*/
LIBSPEC_SP
ERT KEDH_GetKey(BYTE *key, BWT *keyLen, ASNBuf *shareInfo, KEDH_Context *ctx);


#ifdef __cplusplus
}
#endif

#endif /* _KEDH_H_ */
