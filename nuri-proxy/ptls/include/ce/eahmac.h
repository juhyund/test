#ifndef _EA_HMAC_H_
#define _EA_HMAC_H_

/** @ingoup EA
    @file eahmac.h
    @brief HMAC�� �̿��� ��ü������ �������̽� ����

    HMAC�� �̿���, �ܹ���/����� ��ü ������ ������ ����̴�.
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
    @brief �ܹ���/����� ������ ����Ű�� ��
    */
enum _EAHMAC_WAY {
  EAHMAC_UNI = 1,
  EAHMAC_MUT = 2,
};

/** @typedef EAHMAC_Context
    @ingroup EA
    @brief EAHMAC �������̽� ���� ���� ������ ���� Context
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
    @brief EAHMAC_Context�� �ʱ�ȭ�Ѵ�.
    @param ctx     [out] EAHMAC_Context�� ������
    @param key     [in]
    @param keyLen  [in]
    @param hashAlg [in]
    @param way     [in]  �ܹ���/����� �ɼ�
    @sa EAHMAC_DelContext

    A�� A-entity�� ���ϸ�, ���ʷ� ������ ��û�ϴ� ��ü�̴�. B�� B-entity��
    ���ϸ� challenge���� ������ ��ü�̴�. A�� B�� Ư���� �ǹ̰� ���� ����
    �ƴϸ�, ���ǻ� ������ �̸��̴�.

    �ܹ��� ��������
    A <----       nonce      ----- B
    A ----- HMAC(nonce||ext) ----> B
  
    - HMAC�� �̿��� �ܹ��� ���� ����
      -# EAHMAC_B_Challenge : B-entity�� ó�� nonce(random number)�� �����Ͽ�,
           A-entity���� �����Ѵ�.
      -# EAHMAC_A_Response : Prover�� verifier�κ��� ���� nonce�� HMAC��
           ����Ͽ� A-entity���� �����Ѵ�.
      -# EAHMAC_B_Verify : B-entity�� ������ nonce�κ��� HMAC�� ����Ͽ�
           A-entity�� ������ ���� ���Ͽ� �����Ѵ�.

    ����� ��������
    A <-----------------------   nonceOfB   -------------------------- B
    A ----- noceOfA || HMAC(nonceOfA||nonceOfB||nameOfB||extOfA) ----> B
    A <-------------  HMAC(nonceOfB||nonceOfA||extOfB)  -------------- B

    - HMAC�� �̿��� ����� ���� ����
      -# EAHMAC_B_Challenge : B-entity�� nonceOfB�� �����Ͽ� A-entity����
           �����Ѵ�.
      -# EAHMAC_A_Respnse : A-entity�� �ڽ��� nonceOfA�� �����Ͽ�, B-entity��
           ������ nonceOfB�� �� �̸� nameOfB�� ��θ� message�� �Ͽ� HMAC����
           ����Ͽ� nonceOfA�� �Բ� B���� ����
      -# EAHMAC_B_Verify : B-entity�� A-entity�� response�� �ް�, nonceOfA��
           ���� ���� A-entity�� ���������� HMAC���� ����Ͽ� �����Ѵ�.
      -# EAHMAC_B_Resonse : �׸���, B-entity�� nonceOfB nonceOfA�� �޽�����
           �ϴ� HMAC���� ����Ͽ� A���� �����Ѵ�.
      -# EAHMAC_A_Verify : ���������� A-entity�� B-entity�� response�� ����
           ����, ���� �޽����� HMAC���� ����ϰ� response�� ���� ���Ͽ� �����Ѵ�.
    */
LIBSPEC_SP
ERT EAHMAC_NewContext( EAHMAC_Context *ctx,
                       BYTE           *key,
                       BWT             keyLen,
                       AlgDesc         hashAlg,
                       int             way);

/** @ingroup EA
    @brief EAHMAC_Context�� �����Ѵ�.
    @param ctx [in] EAHMAC_Context�� ������
    @sa EAHMAC_NewContext

    EAHMAC_NewContext�� ���Ͽ� �ʱ�ȭ�� EAHMAC_Context��, �� �Լ���
    ����Ͽ� �Ҵ�� �޸𸮰� �����Ǿ�� �Ѵ�.
    */
LIBSPEC_SP
ERT EAHMAC_DelContext( EAHMAC_Context *ctx);

/** @ingroup EA
    @brief B-entity�� challenge���� �����Ѵ�.
    @param bChallenge [out] ������ challenge���� �Ҵ�� ASNBuf�������� �����Ͱ�
    @param bCtx       [in]  B-entity�� context
    @sa EAHMAC_NewContext EAHMAC_A_Response

    process-1 : challenge���� �����ϴ� �Լ��̴�.
    */
LIBSPEC_SP
ERT EAHMAC_B_Challenge( ASNBuf         **bChallenge,
                        EAHMAC_Context  *bCtx);

/** @ingroup EA
    @brief A-entity�� response���� �����Ѵ�.
    @param aResponse  [out] ������ response���� �Ҵ�� ASNBuf�������� �����Ͱ�
    @param bChallenge [in]  B-entity�� ������ challenge�� 
    @param aCtx       [in]  A-entity�� context
    @param aExt       [in]  extension field�� ���� ����� ������ ������
    @param aExtLen    [in]  extension field�� ���� ����Ʈ ���� ����
    @sa EAHMAC_NewContext EAHMAC_B_Challenge EAHMAC_B_Verify

    process-2 : A-entity�� response�� �����ϴ� �Լ��̴�.
    
    aExt�� application�� ���� A-entity�� response �� HMAC�� ������ �޽�����
    �߰����� �޽����� ������ �ʿ䰡 ���� ��, ����� �� �ִ� field�̴�.
    �ʿ䰡 ���� ���� aExt�� NULL�� aExtLen�� 0���� �����ϸ� �ȴ�. 
    */
LIBSPEC_SP
ERT EAHMAC_A_Response( ASNBuf         **aResponse,
                       ASNBuf          *bChallenge,
                       char            *bName,
                       EAHMAC_Context  *aCtx,
                       BYTE            *aExt,
                       BWT              aExtLen);

/** @ingroup EA
    @brief A-entity�� response ���� �����Ѵ�.
    @param aRespnose [in] A-entity�� ������ response��
    @param bName     [in] B-entity�� �̸�
    @param bCtx      [in] B-entity�� context
    @param aExt       [in] extension field�� ���� ����� ������ ������
    @param aExtLen    [in] extension field�� ���� ����Ʈ ���� ����
    @sa EAHMAC_NewContext EAHMAC_A_Response EAHMAC_B_Response

    process-3 : B-entity�� A-entity�� response�� �����ϴ� �Լ��̴�.

    aExt�� A-entity�� response�� ������ ���� aExt�� �����Ͽ��� �Ѵ�.
    extension field�� Ȱ���� �ÿ��� �� ��ü ���̿� ������ ������ �����ϰų�
    ���� ���� ���� �� �ִ� ����� �־�� �� ���̴�.
    */
LIBSPEC_SP
ERT EAHMAC_B_Verify( ASNBuf         *aResponse,
                     char           *bName,
                     EAHMAC_Context *bCtx,
                     BYTE           *aExt,
                     BWT             aExtLen);

/** @ingroup EA
    @brief B-entity�� response���� �����Ѵ�.
    @param bResponse  [out] ������ response���� �Ҵ�� ASNBuf�������� �����Ͱ�
    @param aChallenge [in]  B-entity�� ������ challenge�� 
    @param bCtx       [in]  B-entity�� context
    @param bExt       [in]  extension field�� ���� ����� ������ ������
    @param bExtLen    [in]  extension field�� ���� ����Ʈ ���� ����
    @sa EAHMAC_B_Challenge EAHMAC_B_Verify

    process-4 : B-entity�� response�� �����ϴ� �Լ��̴�.
    
    bExt�� application�� ���� B-entity�� response �� ���ڼ����� �޽�����
    �߰����� �޽����� ������ �ʿ䰡 ���� ��, ����� �� �ִ� field�̴�.
    �ʿ䰡 ���� ���� bExt�� NULL�� bExtLen�� 0���� �����ϸ� �ȴ�. 
    */
LIBSPEC_SP
ERT EAHMAC_B_Response( ASNBuf         **bResponse,
                       ASNBuf          *aResponse,
                       EAHMAC_Context  *bCtx,
                       BYTE            *bExt,
                       BWT              bExtLen);

/** @ingroup EA
    @brief B-entity�� response ���� �����Ѵ�.
    @param bRespnose [in] B-entity�� ������ response��
    @param aCtx      [in] A-entity�� context
    @param bExt      [in] extension field�� ���� ����� ������ ������
    @param bExtLen   [in] extension field�� ���� ����Ʈ ���� ����
    @sa EAHMAC_NewContext EAHMAC_B_Response

    process-5 : A-entity�� B-entity�� response�� �����ϴ� �Լ��̴�.

    bExt�� B-entity�� response�� ������ ���� bExt�� �����Ͽ��� �Ѵ�.
    extension field�� Ȱ���� �ÿ��� �� ��ü ���̿� ������ ������ �����ϰų�
    ���� ���� ���� �� �ִ� ����� �־�� �� ���̴�.
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
