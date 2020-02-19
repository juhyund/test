#ifndef _CMP_H
#define _CMP_H

#include "x509com.h"
#include "x509pkc.h"
#include "pkcs.h"
#include "cms.h"
#include "cmp_types.h"
#include "pkiinfo.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************/
/* API */

/* FIXME : �� rfc2510.h���� ���� �����ϴ��� �� �κ�.
 * ������ �ڵ� ��Ÿ�Ͽ� �°� ������ �ʿ��� */
enum {
  GENERALNAME_OPT_OTHERNAME,
  GENERALNAME_OPT_RFC822NAME,
  GENERALNAME_OPT_DNSNAME,
  GENERALNAME_OPT_X400ADDRESS,
  GENERALNAME_OPT_DIRECTORYNAME,
  GENERALNAME_OPT_EDIPARTYNAME,
  GENERALNAME_OPT_URI,
  GENERALNAME_OPT_IPADDRESS,
  GENERALNAME_OPT_REGISTEREDID,
};


#define CERTTEMPLATE_DEFAULT_VERSION CERT_VER3

enum {
  CERTTEMPLATE_OPT_VERSION,
  CERTTEMPLATE_OPT_SERIALNUM,
  CERTTEMPLATE_OPT_SIGNING_ALG,
  CERTTEMPLATE_OPT_ISSUER_NAME,
  CERTTEMPLATE_OPT_VALIDITY,
  CERTTEMPLATE_OPT_SUBJECT_NAME,
  CERTTEMPLATE_OPT_PUBLICKEY,
  CERTTEMPLATE_OPT_ISSUER_UID,  /* Not yet available */
  CERTTEMPLATE_OPT_SUBJECT_UID, /* Not yet available */
  CERTTEMPLATE_OPT_EXTENSIONS,  
};

LIBSPEC_CKM
int CertTemplate_SetOption(CertTemplate* temp, void *context, int option);

/*## PKIStatusInfo ���� �Լ� ##*/
/**
 * PKIFailureInfo ���� ����
 */
LIBSPEC_CKM
int PKIFailureInfo_Set(PKIFailureInfo *pInfo, int in);
/**
 * PKIFailureInfo ���� ������
 *
 * @return
 *    PKIFailureInfo ��(���нÿ��� FAIL)
 */
LIBSPEC_CKM
int PKIFailureInfo_Get(PKIFailureInfo *pInfo);

/**
 * PKIStatusInfo���� �����Ѵ�.
 *
 * @param *pStatus      (Out) ������ PKIStatusInfo ��
 * @param  nStatus      (In)  Status ��(PKIStatus_accepted, ..)
 * @param *pszFreeText  (In)  statusString ��, NULL�̸� �������� ����
 * @param  nFailInfo    (In)  failInfo ��(PKIFailureInfo_badAlg, ..), 0�̸� �������� ����
 *
 * @return
 *  - SUCCESS : ����
 * @note : ���� statusString(SEQ OF UTF8String)�� �ϳ����� ������ �� ����
 */
LIBSPEC_CKM
int PKIStatusInfo_Set(PKIStatusInfo *pStatus, int nStatus, const char *pszFreeText, int nFailInfo);

/*## EncryptedValue ���� �Լ� ##*/

/** ��ĪŰ �ִ� ���� */
#define MAX_SYMMKEY_LEN 128 
#define DEFAULT_SYMMETRIC_KEY_LEN 16
enum{
  ER_INSUFFICIENT_BUFFER = -500,        /**< Buffer ũ�Ⱑ ���� */
  ER_ENCVALUE_INVALID_ENCRYPTEDVALUE,   /**< �߸��� ������ EncryptedValue */
  ER_ENCVALUE_INVALID_SYMMKEY,          /**< �߸��� ��ĪŰ ��(��ĪŰ ���� NULL�̰ų� �ùٸ��� ���� ����) */
  ER_ENCVALUE_CANNOT_FIND_SYMMKEY,      /**< EncryptedValue�κ��� ��ĪŰ ���� ��µ� ���� */
  ER_ENCVALUE_FAIL_TO_GET_SYMMKEY,      /**< ��ĪŰ ���� ��ȣȭ �ϴµ� ���� */
  ER_ENCVALUE_CANNOT_FIND_KEYALG,       /**< ����Ű ��ȣȭ�� ���� �˰����� �����Ǿ� ���� ���� */
  ER_ENCVALUE_CANNOT_FIND_SYMMALG,      /**< ��ĪŰ ��ȣȭ�� ���� �˰����� �����Ǿ� ���� ���� */
  ER_ENCVALUE_INVALID_SYMMALG,          /**< �ùٸ��� ���� ��ĪŰ ��ȣȭ �˰��� */
};
/**
 * �־��� �����͸� �־��� Ű�� ��ȣȭ�Ͽ� EncryptedValue�� �����Ѵ�.
 * (��ȣȭ �ϴµ� ����ϴ� �ؽ� �˰����� SHA1�� ���)
 *
 * @param *pEncryptedValue  (Out) EncryptedValue��
 * @param *pbValue          (In)  ��ȣȭ �� ������
 * @param cbValue           (In)  pbValue�� ����
 * @param *pbSymmKey        (In)  pbValue�� ��ĪŰ ��ȣȭ �ϴµ� ����� ��ĪŰ
 *                                (NULL�̸� ���������� cbSymmKey ���̿� �ش��ϴ� ��ĪŰ�� �����Ѵ�)
 * @param cbSymmKey         (In)  pbKey�� ����
 * @param pSymmAlg          (In)  ��ĪŰ ��ȣȭ �˰���
 *                                Ȥ�� PBE(Password Based Encryption) �˰��� PKCS#12���� ����)
 * @param pPubKey           (In)  ��ĪŰ�� ����Ű ��ȣȭ �ϴµ� ����� ����Ű.
 *                                �̹� recipient�� ��ĪŰ�� �˰� �־ ��ĪŰ�� ������ �ʿ䰡 ���� ��쿡��
 *                                NULL���� �Է�.
 *                                NULL�̸� ��ȣȭ �� ��ĪŰ�� EncryptedValue�� ���Խ�Ű�� �ʴ´�.
 * @param HashAlg           (In)  ����Ű ��ȣȭ �ÿ� ���� Hash �˰���. pPubKey�� NULL�̸� �� ���� ���õȴ�.
 * @return 
 *   - SUCCESS : ����
 *   - �׿�     : ����
 */
LIBSPEC_CKM
int EncryptedValue_Set(EncryptedValue      *pEncryptedValue,
                       unsigned char       *pbValue,
                       int                  cbValue,
                       unsigned char       *pbSymmKey,
                       int                  cbSymmKey,
                       AlgorithmIdentifier *pSymmAlg,
                       PublicKeyInfo       *pPubKey,
                       AlgorithmIdentifier *pHashAlg);

/**
 * EncryptedValue�� ��ȣȭ�Ѵ�.
 * �� ��ȣȭ ����� ������ 2������ ���еȴ�.
 * 1) �����Ű(pPriKey)�� NULL�� �ƴ� ���
 *    �� ���, �� �����Ű�� �̿��Ͽ�, EncryptedValue���� encSymmKey���� ����Ű ��ȣȭ �Ͽ� ��ĪŰ����
 *    ���� ��, �� ��ĪŰ�� �̿��Ͽ� �����͸� ��ȣȭ�Ѵ�. �̶�, ��ĪŰ���� pbSymmKey�� ����ȴ�.
 *    (pbSymmKey�� NULL�� ���, ��ĪŰ ���� ���ϵ��� �ʴ´�.)
 * 2) �����Ű(pPriKey)�� NULL�� ���
 *    �� ���, �Է¹��� ��ĪŰ(pbSymmKey)���� �̿��Ͽ� �����͸� ��ȣȭ�Ѵ�.
 *    �� ��, cbSymmKeyBufLen�� ��ĪŰ�� ���̸� ���´�.
 *
 * @param *pEncryptedValue  (In)  ��ȣȭ �� EncryptedValue 
 * @param *pPriKey          (In)  EncryptedValue�� ��ȣȭ �ϴµ� ����� �����Ű
 *                                ������ ��ȣȭ�� ���� ��ĪŰ���� �̹� �˰� �ִ� ��쿡�� NULL�� �Է�
 * @param *pbValue          (Out) ��ȣȭ �� ������
 * @param *pcbValue         (Out) ��ȣȭ �� �������� ����
 * @param cbValueBufLen     (In)  pbValue�� ������ ũ��
 * @param *pbSymmKey        (In,Out) ������ ��ȣȭ�� ���� ��ĪŰ. 
 *                                NULL�̸� ��ĪŰ ���� ���ϵ��� �ʴ´�.
 * @param *pcbSymmKey       (Out) ��ĪŰ�� ����
 * @param cbSymmKeyBufLen   (In)  pbSymmKey�� ������ ũ��, pbSymmKey�� �Է� �Ķ�����϶����� pbSymmKey�� ����
 * @param *pSymmEncAlg      (Out) ������ ��ȣȭ�� ���� ��ĪŰ �˰���(NULL�̸� �˰����� �������� ����)
 *
 * @return 
 *   - SUCCESS : ����
 *   - �׿�     : ����
 */
LIBSPEC_CKM
int EncryptedValue_Get(EncryptedValue      *pEncryptedValue,
                       PrivateKeyInfo      *pPriKey,
                       unsigned char       *pbValue,
                       int                 *pcbValue,
                       int                  cbValueBufLen,
                       unsigned char       *pbSymmKey,
                       int                 *pcbSymmKey,
                       int                  cbSymmKeyBufLen,
                       AlgorithmIdentifier *pSymmAlg);
/* ------------------------------------------------------------------------*/
LIBSPEC_CKM
int CMP_MakePasswordBasedMac(ASNBuf **out, ASNBuf *in, AlgorithmIdentifier *alg, 
                             const char *passwd, int passwdLen);


enum {
  ER_CMP_INVALID_PKIHEADER = -200,
  ER_CMP_INVALID_PKIBODY,
  ER_CMP_INVALID_CERTS,
  ER_CMP_CANNOT_FIND_PROTECTION,
  ER_CMP_CANNOT_MAKE_PROTECTION,
  ER_CMP_CANNOT_ENCODE,
};

/**
 * �־��� PKIHeader�� PKIBody�� PKIMessage�� �����Ѵ�
 * priKey�� passwd���� header�� protectionAlg���� ������ ��Ŀ� ���� ���̾�� �Ѵ�.
 *
 * @param *out        (Out) �����, ������ �޽����� �����. 
 *                          �̸� ASN_New(PKIMessage,NULL)�� �̿��Ͽ� �ʱ�ȭ �Ǿ� �־�� �Ѵ�.
 * @param *pKIHeader  (In)  PKIHeader��
 * @param *pKIBody    (In)  PKIBody��
 * @param *priKey     (In)  protection �����ÿ� ����� privatekey
 * @param *signerCert (In)  ����ÿ� Domain parameter�� �ʿ��� ���, �� ���� ��� ���� ������
 * @param *domainParam(In)  Domain parameter, priKey�� signerCert�� domain parameter�� ���� ��� ����
 * @param *passwd     (In)  protection �����ÿ� ����� password
 * @param  passwdLen  (In)  passwd�� ����
 * @param *certs      (In)  PKIMessage�� extraCerts ������ �߰��� ������, NULL�� ��� �߰����� ����
 *
 * @return 
 *  - SUCCESS : ����
 *  - �׿�     : ����
 * @see CMP_MakePKIMessageString
 */
LIBSPEC_CKM
int CMP_MakePKIMessage(PKIMessage     *out,
                       PKIHeader      *pKIHeader,
                       PKIBody        *pKIBody,
                       PrivateKeyInfo *priKey,
                       Certificate    *signerCert,
                       Parameter      *domainParam,
                       const char     *passwd,
                       int             passwdLen,
                       Certificates   *certs);

enum {
  ER_CMP_WRONG_PKIMESSAGE_VERSION = -200,
  ER_CMP_WRONG_PKIMESSAGE_TIME,
  ER_CMP_WRONG_PKIMESSAGE_PROTECTION,

};

/**
 * PKIMessage�� �˻��Ѵ�. �� �˻� ������ ������ �������� �����Ѵ�.
 *  - Header�� version �� �˻�
 *  - Header�� message time�� �ִ� ���, message time�� ���� �ð����κ��� ���� �ð� �̳������� �˻�
 *  - Protection �˻�(Protection�� �ݵ�� �����ؾ� ��)
 *
 * @param *pKIMessage   (In) �˻��Ϸ��� PKIMessage
 * @param *cert         (In) Protection�� ������ �����ϱ� ���� ������
 * @param *passwd       (In) MAC���� �����ϱ� ���� password
 * @param *passwdLen    (In) passwd�� ����
 * @param checkTime     (In) Message time�� �����ϱ� ���� ���� �ð�(0�� ��� ���� �ð� ���)
 *
 * @return 
 *  - SUCCESS : ����
 *  - �׿�     : ����
 */
LIBSPEC_CKM
int CMP_VerifyPKIMessage(PKIMessage  *pKIMessage,
                         Certificate *cert,
                         const char  *passwd,
                         int          passwdLen,
                         time_t       checkTime);


/*## POP ���� �Լ� ##*/
enum {
  /*## POP ����/������ ���� ##*/
  ER_CMP_POP_INVALID_POP_TECHNIQUE,     /**< �߸��� ����� POP ��� */
  ER_CMP_POP_NOT_EXIST,                 /**< POP ���� �������� ���� */
  ER_CMP_POP_CANNOT_FIND_PUBLICKEY,     /**< PublicKey ���� �������� ���� */      
  ER_CMP_POP_INVALID_SIGNATURE,         /**< POP�� signature ����� ��, ���� ������ ������ ��� */
  ER_CMP_POP_NOT_SUPPORTED,             /**< �������� �ʴ� ����� POP */
  ER_CMP_POP_CANNOT_FIND_SUBJECT,       /**< certTemplate�� publicKey���� ������ subject���� ���� */
  ER_CMP_POP_POPSKINPUT_MUST_NOT_EXIST, /**< certTemplate�� publicKey���� �����鼭 
                                             pop�� signature�� popskInput���� �����ϴ� ��� */
  ER_CMP_POP_FAIL_TO_ENCODE,            /**< signature�� �����ϱ� ���� input�� ���� ���� */
  ER_CMP_POP_CANNOT_FIND_POPSKINPUT,    /**< certTemplate�� publicKey���� �����鼭
                                             pop�� signature�� popskInput���� ���� ��� */
  ER_CMP_POP_INVALID_THISMESSAGE,       /**< POP�� thisMessage ����� ��, thisMessage������ �߸��� ���
                                             thisMessage�� EncryptedValue�� DER encoding�� ��,
                                             BitString���� ��ȯ�� ���̾�� �Ѵ�. */
  ER_CMP_POP_FAIL_TO_DECODE_PRIKEYINFO, /**< POP�� thisMessage ����� ��, thisMessage��
                                             PrivateKeyInfo�� ��ȣȭ �� ���� ������ �־�� �ϳ�, 
                                             PrivateKeyInfo���� ��µ� �������� �� */
  ER_CMP_POP_FAIL_TO_DECRYPT,           /**< POP�� thisMessage���� decrypt�ϴµ� ���� */
  ER_CMP_POP_FAIL_TO_VERIFY,            /**< POP ������ ������ ��� */
  /*## POP ������ ���� ##*/
  ER_CMP_POP_FAIL_TO_MAKE_PUBLICKEYMAC, /**< POP�� poposkInput�� ����� ���� publicKeyMAC�� ���� ���� */
  ER_CMP_POP_INVALID_PUBLICKEYINFO,     /**< �߸��� ������ publicKeyInfo �� */
  ER_CMP_POP_INAVLID_PRIVATEKEYINFO,    /**< �߸��� ������ privateKeyInfo �� */
  ER_CMP_POP_INVALID_CERTTEMPLATE,      /**< �߸��� ������ certTemplate �� */
  ER_CMP_POP_FAIL_TO_ENCODE_POPOSKINPUT, /**< poposkInput encoding ���� */ 
  ER_CMP_POP_FAIL_TO_MAKE_SIGNATURE,    /**< ���� ���� ���� */
  ER_CMP_POP_FAIL_TO_ENCRYPT_PRIKEYINFO,/**< �����Ű ��ȣȭ ���� */
  ER_CMP_POP_CANNOT_FIND_PUBKEY_IN_CERTTEMPLATE, /**< CertTemplate ���� ����Ű ���� ���� �� */
  ER_CMP_POP_CAPRIKEY_NOT_SUPPLIED, /**< CA�� �����Ű�� �Է����� ���� �ʾ��� �� */
};

typedef enum{
  POP_Technique_None  = 0,          /**< POP�� ������� ����(������ ��� ���) */
  POP_Technique_RAVerified = 1,
  POP_Technique_SKPOP,
  POP_Technique_EKPOPThisMessage,
  POP_Technique_KAKPOPThisMessage,
  POP_Technique_KAKPOPThnisMessageDHMAC,
  POP_Technique_EKPOPEncryptedCert,
  POP_Technique_KAKPOPEncryptedCert,
  POP_Technique_EKPOPChallengeResp,
  POP_Technique_KAKPOPChallengeResp
}POP_Technique;

/**
 * CertReqMsg�� POP���� �����Ѵ�.
 *
 * @param *pPopTechnique  (Out) POP���
 * @param **ppPubKey      (Out) POP�� ������ ����Ű ��(NULL�̸� �������� ����)
 * @param **ppPriKey      (Out) CertReqMsg���� ��ȣȭ �� �����Ű�� ���ԵǾ� ���۵� ���, ��ȣȭ �� �����Ű ��,
 *                              ���ԵǾ� ���۵��� ���� ��쿡�� NULL���� �����(NULL�̸� �������� ����)
 * @param *pCertReq       (In)  POP�� ������ CertReqMsg
 * @param *pCAPrivateKey  (In)  POP ����� thisMessage�� ��쿡 POP�� �����ϱ� ���� CA�� �����Ű
 * @param *pDomainParam   (In)  POP ����� signature�� ��쿡 POP�� ������ �����ϴµ� ���Ǵ� domainParameter
 * @param *pszSecretValue (In)  ir�� ��� secret value ��(PKIMessage�� protection ������ ���� ��)
 *
 * @return 
 *  - SUCCESS : ����
 *  - �׿�     : ����
 */
LIBSPEC_CKM
int CMP_VerifyPOP(int              *pPopTechnique,
                  PublicKeyInfo   **ppPubKey,
                  PrivateKeyInfo  **ppPriKey,
                  CertReqMsg       *pCertReq,
                  PrivateKeyInfo   *pCAPrivateKey,
                  Parameter        *pDomainParam,
                  const char       *pszSecretValue);
/**
 * POP ���� �����Ѵ�.
 * ������ �̿��� POP�� ����ϴ� ���, �� �Լ����� �����ϴ� ����� ������ ����.
 * 1. sender name�� �˰� �ִ� ���
 *    �� ��� pCertTemplate���� NULL�� �ƴϾ�� �ϰ�, �ݵ�� sender name�� publicKey ���� ������ �־�� �Ѵ�.
 *    �Լ� �������� certTemplate�� DER-Encoding �� ���� ���� ������ �����Ѵ�.
 * 2. sender name�� �𸣰� �ִ� ���
 *    reference number�� secret value�� �̿��Ͽ� ir�� �����ϴ� ��찡 �̿� �ش�Ǹ�,
 *    �Լ� �������� publicKeyInfo�� secret value���� �̿��Ͽ� poposkInput�� ������ ��, ���� DER-Encoding��
 *    ���� ���� ������ �����Ѵ�.
 *
 * @param *pPop            (Out) ������ ProofOfPossession ��
 * @param *pCertTemplate   (In)  CertTemplate ��(signature�� ���� POP�϶� ������ �����ϱ� ���� ���)
 * @param *pSenderAuthInfo (In)  ��û�� ������ ���� ����
 *                               �� ���� �ʿ��� ���� ������ ������ ������ �ش����� �ʴ� ��쿡�� NULL�� ����.
 *                               1. POP�� thisMessage ����̳�, CA�������� ���� �� ���⿡,
 *                                  secretvalue�� �̿��Ͽ� �����Ű�� ��ȣȭ �Ͽ� �����Ϸ��� ���
 * @param *pReqCertInfo    (In)  ������ �߱� ��û�� ���� Ű ����
 * @param *pCACert         (In)  CA�� ������(POP�� thisMessage ����϶�, �����Ű�� ��ȣȭ �ϱ� ���� ���
 *                                        ��, ir�� ��쿡�� �� ���� NULL�̸� secret value�� �̿��Ͽ� ��ȣȭ)
 * @param nidSymmAlg       (In)  ��ĪŰ �˰���(POP�� thisMessage ����϶�, �����Ű�� ��ȣȭ �ϴµ� ���)
 * @return
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int CMP_MakePOP(ProofOfPossession   *pPop,
                CertRequest         *pCertReq,
                PKISenderAuthInfo   *pSenderAuthInfo,
                PKIReqCertInfo      *pReqCertInfo,
                Certificate         *pCACert,
                AlgorithmIdentifier *pSymmAlg);

/*# PBM(Password Based MAC) ���� �Լ� #*/
#define PBM_SALT_DEFAULT        "\x83\x24\x49\x32\x17\x07\x53\x15"
#define PBM_SALT_LEN            8
#define PBM_ITERATION_DEFAULT   1976


/**
 * PBMParameter ���� �����Ѵ�.
 *
 * @param *pParam         (Out) ������ PBMParameter ��
 * @param *pbSalt         (In)  Salt ��
 * @param cbSalt          (In)  Salt ����
 * @param nidOwf          (In)  AlgId for a One-way function
 * @param nIterationCount (In)  number of times the OWF is applied
 * @param nidMac          (In)  the MAC AlgId
 *
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PBMParameter_Set(PBMParameter *pParam, 
                     const unsigned char *pbSalt, int cbSalt,
                     Nid  nidOwf,
                     int  nIterationCount,
                     Nid  nidMac);


/**
 * �ű� KeyPolicyRequest�� �����ϴ� �Լ� 
 *
KeyPolicyRequest  ::=  SEQUENCE {
        transacId          OCTET STRING,
        requesterRefNum    OCTET STRING OPTIONAL,
        requesterName      Name OPTIONAL,
        rAPolicy           NULL OPTIONAL }
 */
LIBSPEC_CKM
KeyPolicyRequest* KeyPolicyRequest_New(const char *id, Name *name, int rAFlag);

#ifdef __cplusplus
}
#endif

#endif /* _CMP_H */
