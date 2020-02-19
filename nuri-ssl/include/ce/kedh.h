#ifndef _KEDH_H_
#define _KEDH_H_

/** @defgroup KEA
 * @ingroup SP
 * @brief Key Exchange Algorithm interface (legacy).
 * Use @ref KEX interface instead.
 */

/** @file kedh.h
    @ingroup KEA
    @brief Diffie-Hellman ����� KE ���

    Key Exchagne ��� �� Diffie-Hellman ����� �̿��� ���������̴�.
    ����, RFC2631 ������ ����Ͽ� ������� �ִ�.
    
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

/* ���� ����
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
    @brief KEDH�� ����ϱ� ���� ������ ���� ����ü

    keyLen�� hashAlg�� KEDH_GenKey���� ����ϴ� ���̴�. Ű ���̴� �⺻������ 
    �� ����ü�� ������ keyLen�� ��������, RFC2631 ����� ��쿡�� �� ���� 
    ������� �ʴ´�.
   
*/
/* see cc/dh.h
typedef PCIS_DH_Context KEDH_Context;
*/

/** @ingroup KEA
    @brief KEDH_Context�� �ʱ�ȭ �ϴ� �Լ�

    @param ctx [out]     �ʱ�ȭ ����� KEDH_Context�� ������
    @param p [in]       �ý��� �Ķ���� p
    @param q [in]       �ý��� �Ķ���� q
    @param g [in]       �ý��� �Ķ���� g
    @param x [in]       �ڽ��� private info or private key
    @param yR [in]      ������ public info or public key
    @param keyLen [in]  Ű������ ����� Ű�� ����Ʈ ����
    @param hashAlg [in] hash �˰��� descriptor

    x�� yR�� ������ ���� ����ϴ� ���, �ʱ�ȭ �Լ��� �Է��Ͽ� ����ؾ� �Ѵ�.
    �׷��� ���� ��� x, yR�� �Է����� NULL�� �ָ� ���ο��� �����Ͽ� ����Ѵ�.
*/    
LIBSPEC_SP
ERT KEDH_Initialize
   (KEDH_Context *ctx, MINT *p, MINT *q, MINT *g, 
   MINT *x, MINT *yR, BWT keyLen, const void *hashAlg);

/** @ingroup KEA
    @brief ShareInfo�� �����ϴ� �Լ�

    @param shareInfo [out]  Ű���� ������ shareInfo�� ������
    @param keyInfo [in]    ����� NULL�� �Է�
    @param ctx [in]        KEDH_Context�� ������
    
    KEDH_Context Ÿ���� ctx�� ASNBuf Ÿ���� keyInfo�� �Է����� �޾� Ű������ �ϱ� ���� 
    ���濡�� ���� ASNBuf Ÿ���� shareInfo�� �����Ѵ�.
   
    ������ keyInfo�� ������� �ʴ´�. NULL�� �Է��Ͽ� ����Ѵ�.

    ����� Diffie-Hellmac Basic Protocol ��ĸ� �����Ǿ� �ִ�. 
    (RFc2631 ����� ���� �����Ѵ�.)
*/
LIBSPEC_SP 
ERT KEDH_GenShareInfo(ASNBuf **shareInfo, ASNBuf *keyInfo, KEDH_Context *ctx);

/* ���� ����
LIBSPEC_SP
ERT KEDH_GenKeyInfo(ASNBuf **keyInfo, ...);
*/

/** @ingroup KEA
    @brief Ű ���� �Լ�

    @param key [out]         ������ Ű�� ����� ����Ʈ ������
    @param keyLen [out]      ������ Ű�� ����Ʈ ���� ����
    @param shareInfo [in]   Ű������ ������ ���� ������ ASNBuf Ÿ�� ������
    @param ctx [in]         KEDH_Context ����ü�� ����Ʈ
     
    ASNBuf Ÿ���� shareInfo�� KEDH_Context Ÿ���� ctx�� �Է����� �޾�
    key�� ����Ѵ�. 
    �̶� Ű ���̴� �⺻������ ctx�� keyLen�� ��������,
    RFC2631�� ������ ��쿡�� shareInfo ���� keyInfo�� Ű ���̸� ������.
    ������ �װ�쿡�� �ش� ������ Ű���̰� keyLen���� ��µȴ�.
    keyInfo�� ������� ���� ��쿡�� ctx�� keyLen�� ���̰� ��µȴ�.
     
*/
LIBSPEC_SP
ERT KEDH_GetKey(BYTE *key, BWT *keyLen, ASNBuf *shareInfo, KEDH_Context *ctx);


#ifdef __cplusplus
}
#endif

#endif /* _KEDH_H_ */
