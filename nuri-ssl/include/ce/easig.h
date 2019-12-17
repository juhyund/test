#ifndef _EA_SIG_H_
#define _EA_SIG_H_

/** @defgroup EA Entity Authentication
 * @ingroup SP
    @brief EA(Entity Authentication) ���
    */

/** @file easig.h
 * @ingroup SP
    @brief ������ �̿��� ��ü������ �������̽� ����
    
    ������ �̿���, �ܹ���/����� ��ü ������ ������ ����̴�.
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
    @brief �ܹ���/����� ������ ����Ű�� ��
    */
enum _EASIG_WAY {
  EASIG_UNI = 1,
  EASIG_MUT = 2,
};

/** @typedef EASIG_Context
    @ingroup EA
    @brief EASIG �������̽� ���� ���� ������ ���� Context
    */
typedef struct _EASIG_Context {
  int way;
  EASIG_B_ChalToken *bChal;
  EASIG_A_RespToken *aResp;
  EASIG_B_RespToken *bResp;
} EASIG_Context;


/** @ingroup EA
    @brief EASIG_Context�� �ʱ�ȭ�Ѵ�.
    @param ctx [out] EASIG_Context�� ������
    @param way [in]  �ܹ���/����� �ɼ�
    @sa EASIG_DelContext

    EASIG �������̽����� ���� ������ ���� EASIG_Context�� �ʱ�ȭ�Ѵ�.
    �� �ʱ�ȭ �������� �޸𸮰� �Ҵ�ǹǷ�, ����� ���� EASIG_Context��
    �ݵ�� EASIG_DelContext�� ���Ͽ�, �޸𸮸� �����Ͽ��� �Ѵ�.

    ����, way �Ķ���ͷ� �ܹ���/����� �߿��� ��1�� �Ͽ��� �Ѵ�.
    �ܹ��� ������ ���� EASIG_UNI��, ����� ������ ���� EASIG_MUT��
    �Է°����� �ָ� �ȴ�.

    A�� A-entity�� ���ϸ�, ���ʷ� ������ ��û�ϴ� ��ü�̴�. B�� B-entity��
    ���ϸ� challenge���� ������ ��ü�̴�. A�� B�� Ư���� �ǹ̰� ���� ����
    �ƴϸ�, ���ǻ� ������ �̸��̴�.


    �ܹ��� ��������
    A <---------------------------   nonceOfB   ----------------------------- B
    A - nonceOfA||nameOfB||Sign(nonceOfA|nonceOfB|nameOfB|extOfA)||CertOfA -> B

    - ���ڼ����� �̿��� �ܹ��� ���� ����
      -# EASIG_B_Challenge : B-entity�� nonceOfB�� �����Ͽ� A-entity����
           �����Ѵ�.
      -# EASIG_A_Response :  A-entity�� �ڽ��� nonceOfA�� �����Ͽ�,B-entity��
           ������ nonceOfB�� �� �̸� nameOfB�� ��θ� message�� �Ͽ�
           ���ڼ����Ͽ� nonceOfA�� nameOfB�� �Բ� B���� ����
      -# EASIG_B_Verify : B-entity�� A-entity�� response�� �ް�, nonceOfA��
            ���� ���� ���⼺�� nameOfB���� Ȯ���ϰ� ���ڼ����� �����Ͽ�
            �����Ѵ�.

    ����� ��������
    A <---------------------------   nonceOfB   ----------------------------- B
    A - nonceOfA||nameOfB||Sign(nonceOfA|nonceOfB|nameOfB|extOfA)||CertOfA -> B
    A <---- nameOfA||Sign(nonceOfB||nonceOfA||nameOfA||extOfB)||CertOfB ----> B

    - ���ڼ����� �̿��� ����� ���� ����
      -# EASIG_B_Challenge : B-entity�� nonceOfB�� �����Ͽ� A-entity����
           �����Ѵ�.
      -# EASIG_A_Response :  A-entity�� �ڽ��� nonceOfA�� �����Ͽ�,B-entity��
           ������ nonceOfB�� �� �̸� nameOfB�� ��θ� message�� �Ͽ�
           ���ڼ����Ͽ� nonceOfA�� nameOfB�� �Բ� B���� ����
      -# EASIG_B_Verify : B-entity�� A-entity�� response�� �ް�, nonceOfA��
            ���� ���� ���⼺�� nameOfB���� Ȯ���ϰ� ���ڼ����� �����Ͽ�
            �����Ѵ�.
      -# EASIG_B_Response : �׸���, B-entity�� nonceOfB nonceOfA�� nameOfB��
            �޽����� �Ͽ� ���ڼ����Ͽ� A���� �����Ѵ�.
      -# EASIG_A_Verify : ���������� A-entity�� B-entity�� response�� ���� ����,
            �޽����� ���⼺�� nameOfA���� Ȯ���ϰ� ���ڼ����� �����Ͽ� �����Ѵ�.
    */
LIBSPEC_SP
ERT EASIG_NewContext(EASIG_Context *ctx, int way);

/** @ingroup EA
    @brief EASIG_Context�� �����Ѵ�.
    @param ctx [in] EASIG_Context�� ������
    @sa EASIG_NewContext

    EASIG_NewContext�� ���Ͽ� �ʱ�ȭ�� EASIG_Context��, �� �Լ���
    ����Ͽ� �Ҵ�� �޸𸮰� �����Ǿ�� �Ѵ�.
    */
LIBSPEC_SP
ERT EASIG_DelContext(EASIG_Context *ctx);

/** @ingroup EA
    @brief B-entity�� challenge���� �����Ѵ�.
    @param bChallenge [out] ������ challenge���� �Ҵ�� ASNBuf�������� �����Ͱ�
    @param bCtx       [in]  B-entity�� context
    @sa EASIG_NewContext EASIG_A_Response

    process-1 : challenge���� �����ϴ� �Լ��̴�.
    */
LIBSPEC_SP
ERT EASIG_B_Challenge( ASNBuf        **bChallenge,
                       EASIG_Context  *bCtx);

/** @ingroup EA
    @brief A-entity�� response���� �����Ѵ�.
    @param aResponse   [out] ������ response���� �Ҵ�� ASNBuf�������� �����Ͱ�
    @param bChallenge  [in]  B-entity�� ������ challenge�� 
    @param aCtx        [in]  A-entity�� context
    @param priInfo     [in]  A-entity�� ��������� ����� �����Ű
    @param domainParam [in]  A-entity�� ��������� ����� domainParam
    @param hashAlg     [in]  A-entity�� ��������� ����� �ؽ� �˰���
    @param cert        [in]  A-entity�� ������
    @param aExt        [in]  extension field�� ���� ����� ������ ������
    @param aExtLen     [in]  extension field�� ���� ����Ʈ ���� ����
    @sa EASIG_NewContext EASIG_B_Challenge EASIG_B_Verify

    process-2 : A-entity�� response�� �����ϴ� �Լ��̴�.
    
    aExt�� application�� ���� A-entity�� response �� ���ڼ����� �޽�����
    �߰����� �޽����� ������ �ʿ䰡 ���� ��, ����� �� �ִ� field�̴�.
    �ʿ䰡 ���� ���� aExt�� NULL�� aExtLen�� 0���� �����ϸ� �ȴ�. 
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
    @brief A-entity�� response ���� �����Ѵ�.
    @param cert      [out] A-entity�� response�� ���Ե� A-entity�� ������
    @param aRespnose [in]  A-entity�� ������ response��
    @param bCtx      [in]  B-entity�� context
    @param aExt      [in]  extension field�� ���� ����� ������ ������
    @param aExtLen   [in]  extension field�� ���� ����Ʈ ���� ����
    @retval
    @sa EASIG_NewContext EASIG_A_Response EASIG_B_Response

    process-3 : B-entity�� A-entity�� reponse�� �����ϴ� �Լ��̴�.

    cert�� ��µ� �������� �����Ǿ�� ��� ���� ���μ�����
    ��ġ�� ���̴�. �������� �����ϴ� ������ �� ��� ���� ���̴�.

    aExt�� A-entity�� response�� ������ ���� aExt�� �����Ͽ��� �Ѵ�.
    extension field�� Ȱ���� �ÿ��� �� ��ü ���̿� ������ ������ �����ϰų�
    ���� ���� ���� �� �ִ� ����� �־�� �� ���̴�.
    */
LIBSPEC_SP
ERT EASIG_B_Verify( CERT          **cert,
                    ASNBuf         *aResponse,
                    EASIG_Context  *bCtx,
                    BYTE           *aExt,
                    BWT             aExtLen);

/** @ingroup EA
    @brief B-entity�� response���� �����Ѵ�.
    @param bResponse   [out] ������ response���� �Ҵ�� ASNBuf�������� �����Ͱ�
    @param aChallenge  [in]  A-entity�� ������ challenge�� 
    @param bCtx        [in]  B-entity�� context
    @param priInfo     [in]  B-entity�� ��������� ����� �����Ű
    @param domainParam [in]  B-entity�� ��������� ����� domainParam
    @param hashAlg     [in]  B-entity�� ��������� ����� �ؽ� �˰���
    @param cert        [in]  B-entity�� ������
    @param bExt        [in]  extension field�� ���� ����� ������ ������
    @param bExtLen     [in]  extension field�� ���� ����Ʈ ���� ����
    @sa EASIG_NewContext EASIG_B_Verify EASIG_A_Verify

    process-4 : B-entity�� response�� �����ϴ� �Լ��̴�.
    
    bExt�� application�� ���� B-entity�� response �� ���ڼ����� �޽�����
    �߰����� �޽����� ������ �ʿ䰡 ���� ��, ����� �� �ִ� field�̴�.
    �ʿ䰡 ���� ���� bExt�� NULL�� bExtLen�� 0���� �����ϸ� �ȴ�. 
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
    @brief B-entity�� response ���� �����Ѵ�.
    @param cert      [out] B-entity�� response�� ���Ե� B-entity�� ������
    @param bRespnose [in]  B-entity�� ������ response��
    @param aCtx      [in]  A-entity�� context
    @param bExt      [in]  extension field�� ���� ����� ������ ������
    @param bExtLen   [in]  extension field�� ���� ����Ʈ ���� ����
    @retval
    @sa EASIG_NewContext EASIG_B_Response

    process-5 : A-entity�� B-entity�� reponse�� �����ϴ� �Լ��̴�.

    cert�� ��µ� �������� �����Ǿ�� ��� ���� ���μ�����
    ��ġ�� ���̴�. �������� �����ϴ� ������ �� ��� ���� ���̴�.

    bExt�� A-entity�� response�� ������ ���� bExt�� �����Ͽ��� �Ѵ�.
    extension field�� Ȱ���� �ÿ��� �� ��ü ���̿� ������ ������ �����ϰų�
    ���� ���� ���� �� �ִ� ����� �־�� �� ���̴�.
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
