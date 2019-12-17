/**
 * @file     pkiinfo.h
 *
 * @desc     PKI request message �� confirm message ������ �ʿ��� ����ü �� �Լ� ����
 * @author   ������(jypark@pentasecurity.com)
 * @since    2001.11.06
 *
 */


#ifndef _PKIINFO_H_
#define _PKIINFO_H_

#include "pkcs.h"
#include "x509com.h"
#include "x509pkc.h"
#include "cms.h"
#include "cmp_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/
/* PKIXXXReqInfo-s */

#define MAX_REFNUM_LEN      256
#define MAX_SECRETVAL_LEN   256
#define MAX_REVPASS_LEN     256
/**
 *  ������ ������ ���� Ű�ֿ� ���� ������ ��� ����ü
 */
typedef struct _PKIReqCertInfo {
   ASNSeqClass klass;
   Boolean             *keyGenInCA;          /* default: false */
   Integer             *popTechnique;        /*optional [0] */
   Boolean             *archiveKey;
   AlgorithmIdentifier *sigOrEncKeyAlg;
   Integer             *keyLen;
   PublicKeyInfo       *publicKey;           /*optional [1] */
   PrivateKeyInfo      *privateKey;          /*optional [2] */
   Parameter           *param;               /*optional [3] */
   Controls            *controls;            /*optional [4] */
   KeyIdentifier       *subjectKeyId;        /*optional [5] */
} PKIReqCertInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIReqCertInfo;

/**
 *  ������ ������ ���� ������ ��� ����ü
 */
typedef struct _PKIReqRevInfo {
   ASNSeqClass klass;
   Certificate *certificate;
   ReasonFlags *revocationReason; /*optional [0] */
   Extensions  *crlEntryDetails;  /*optional [1] */
} PKIReqRevInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIReqRevInfo;

/**
 * General Message ��û�� ���� ������ ��� ����ü
 */
typedef InfoTypeAndValue PKIReqGenInfo;

#define AD_PKIReqGenInfo AD_InfoTypeAndValue


/*********************************************************************/
/* PKIReqInfo */

/**
 *  Request �޽��� ������ �ʿ��� ������ ��� ����ü
 */
enum{
  PKIReqInfo_certReqInfo = 1,
  PKIReqInfo_revReqInfo,
  PKIReqInfo_genReqInfo,
};
typedef struct _PKIReqInfo {
   ASNChoiceClass klass;
   int		select;
   union{
      PKIReqCertInfo *certReqInfo;	/* [0] */
      PKIReqRevInfo  *revReqInfo;	/* [1] */
      PKIReqGenInfo  *genReqInfo;	/* [1] */
   }choice;
} PKIReqInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIReqInfo;


typedef struct _SeqOfPKIReqInfo {
  ASNSeqOfClass klass;
  int size;
  PKIReqInfo **member;
} SeqOfPKIReqInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfPKIReqInfo;

/**
 * ������ �߱��� ���� PKIReqInfo ���� �����Ѵ�.
 *
 * @param *pPKIReqInfo    (Out) ������ PKIReqInfo ��
 * @param bKeyGenInCA     (In)  Ű ���� CA���� �����ϴ��� ���� (1: true, 0: false)
 * @param nPopTechnique   (In)  �����Ű�� POP ���
 * @param bArchiveKey     (In)  �����Ű�� CA���� �������� ����(CA�� �����Ű�� �����ؾ� �ϴ��� ����)
 * @param nidKeyType      (In)  �ؽ� �˰����� ������ �����Ű ����(ex. NID_sha1WithRSAEncryption, NID_kcdsaWithHAS160 ..)
 * @param  nKeyLen        (In)  ����Ű �� & �����Ű ���� NULL�� ��쿡 �����ؾ� �ϴ� Ű ����
                                ����Ű �� & �����Ű ���� NULL�� �ƴϸ� �� ���� ���õȴ�.
 * @param *pPubKeyInfo    (In)  ����Ű ��(NULL ����)
 * @param *pPriKeyInfo    (In)  �����Ű ��(NULL ����)
 * @param *pDomainParam   (In)  ������ �Ķ���� ��(NULL ����)
 * @param *pOldCert       (In)  ���� ������(������ ���� ��)
 *
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKIReqInfo_SetReqCertInfo(PKIReqInfo      *pPKIReqInfo,
                              int              bKeyGenInCA,
                              int              nPopTechnique,
                              int              bArchiveKey,
                              Nid              nidKeyType,
                              int              nKeyLen,
                              PublicKeyInfo   *pPubKeyInfo,
                              PrivateKeyInfo  *pPriKeyInfo,
                              Parameter       *pDomainParam,
                              Certificate     *pOldCert);

/**
 * pPKIReqCertInfo�� �ʿ��� �ű� contorl�� �߰��Ѵ�.
 *
 * @param *pPKIReqCertInfo (Out) contorl�� �߰��� PKIReqCertInfo ����
 * @param  nidInfoType     (In)  �߰��� control�� NID ��
 * @param *pInfoValue      (In)  �߰��� control�� value ��
 *
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int ReqCertInfo_AddControl(PKIReqCertInfo      *pPKIReqCertInfo,
                           Nid                  nidInfoType,
                           ASN                 *pInfoValue);
/**
 * ������ ������ ���� PKIReqInfo ���� �����Ѵ�.
 * 
 * @param *pPKIReqInfo    (Out) ������ PKIReqInfo ��
 * @param *pCertificate   (In)  ������ ������
 * @param nReasonFlag     (In)  ���� ����(0�̸� �������� ����)
 */
LIBSPEC_CKM
int PKIReqInfo_SetReqRevInfo(PKIReqInfo   *pPKIReqInfo,
                             Certificate  *pCertificate,
                             int           nReasonFlag);

/**
 * PKIReqRevInfo�� �ʿ��� crlEntryDetails�� �߰��Ѵ�.
 *
 * @param *pPKIReqRevInfo (In,Out) crlEntryDetails�� �߰��� PKIReqRevInfo
 * @param *pExtension     (In) �߰��� extension ��
 * @return
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKIReqRevInfo_AddCrlEntryDetails(PKIReqRevInfo *pPKIReqRevInfo,
                                     Extension     *pExtension);

/**
 * �Ϲ����� ���� ��ȯ�� ���� PKIGenInfo ���� �����Ѵ�.
 * 
 * @param pPKIReqInfo    (Out) ������ PKIReqInfo ��
 * @param nInfoType      (In)  ���� ������ ������ ��Ÿ���� Nid ��
 * @param pInfoValue     (In)  ������ ����ü
 */
LIBSPEC_CKM
int PKIReqInfo_SetReqGenInfo(PKIReqInfo   *pPKIReqInfo,
                             Nid           nInfoType,
                             ASN          *pInfoValue);

/**
 *  Reference Number�� Secret Value�� ����� ����� ������ ���� ����ü
 */
typedef struct _PKISecretValue {
   ASNSeqClass klass;
   AlgorithmIdentifier *macAlg;
   OctetString *referenceNumber;
   OctetString *secretValue;
   AlgorithmIdentifier *pbeAlg; /*optional [0] */
} PKISecretValue;

LIBSPEC_CKM
extern ASNDescriptor AD_PKISecretValue;

/**
 *  ������ ���� ����� ������ ���� ����ü
 */
typedef struct _PKICertAndPriKey {
   ASNSeqClass klass;
   PrivateKeyInfo *privateKey; /*optional [0] */
   Certificate *certificate;
   Parameter *param; /*optional [1] */
   AlgorithmIdentifier *hashAlg;
} PKICertAndPriKey;

LIBSPEC_CKM
extern ASNDescriptor AD_PKICertAndPriKey;

/**
 *  ������ revPassPhrase�� �̿��Ͽ� ���� ��û�� �ϴ� ��츦 ���� ����ü
 */
typedef struct _PKIRevPassPhrase {
   ASNSeqClass klass;
   Name        *senderName;
   OctetString *revPassPhrase;
   AlgorithmIdentifier *macAlg;
} PKIRevPassPhrase;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIRevPassPhrase;

/**
 * POP�� subsequentMessage ����� ��, Conf�� MAC���� �����ϱ� ���� ����ü
 * (rfc2510 3.2.8 ����)
 */
typedef struct _PKIPOPEncCertKey {
   ASNSeqClass klass;
   BitString *certEncKey;
} PKIPOPEncCertKey;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIPOPEncCertKey;

/**
 * ����� ������ ���� ������ ��� ����ü
 */
enum {
  PKISenderAuthInfo_secretValue    = 1,
  PKISenderAuthInfo_certAndPriKey,
  PKISenderAuthInfo_revPassPhrase,
  PKISenderAuthInfo_popEncCertKey,
};
typedef struct _PKISenderAuthInfo {
   ASNChoiceClass klass;
   int		select;
   union{
      PKISecretValue *secretValue;	/* [0] */
      PKICertAndPriKey *certAndPriKey;	/* [1] */
      PKIRevPassPhrase *revPassPhrase;	/* [2] */
      PKIPOPEncCertKey *popEncCertKey;  /* [3] */
   }choice;
} PKISenderAuthInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKISenderAuthInfo;


/**
 * PKIMessage�� reference number�� secret value�� �̿��� �����ϴ� ���
 * �� ������ ����ϱ� ���� reference number�� secret value�� PKISenderAuthInfo���� �����Ѵ�.
 * owfAlg,macAlg,PbeAlg�� client���� �޽����� �����ϱ� ���� ���Ǹ�, 
 * CA������ 0���� ����(���� �޽��� �ؼ��� ����)
 *
 * @param *pPKISenderAuthInfo (Out) ������ PKISenderAuthInfo ��
 * @param *pszRefNum          (In)  Reference number ��
 * @param *pszSecretVal       (In)  Secret Value ��
 * @param  nidOwfAlg          (In)  MAC ������ ���� one way function �˰���
 * @param  nidMacAlg          (In)  MAC �˰���(ex)NID_hmacWithSHA1)
 * @param  nidPbeAlg          (In)  PBE(Password-Based Encryption) �˰���(pbe.h ����),
 *                                  PBE�� ������� �ʴ� ���(CA �������� ������ �ִ� ���)�� 0�� ����
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKISenderAuthInfo_SetSecretValue(PKISenderAuthInfo *pPKISenderAuthInfo,
                                     const char *pszRefNum,
                                     const char *pszSecretVal,
                                     Nid         nidOwfAlg,
                                     Nid         nidMacAlg,
                                     Nid         nidPbeAlg);
                                     
/**
 * PKIMessage�� ������ �̿��� �����ϴ� ���
 * �� ������ ����ϱ� ���� Sender�� �������� �����Ű�� PKISenderAuthInfo���� �����Ѵ�.
 * nidHashAlg�� client���� �޽����� �����ϱ� ���� ���Ǹ�, 
 * CA������ 0���� ����(���� �޽��� �ؼ��� ����)
 *
 * @param *pPKISenderAuthInfo (Out) ������ PKISenderAuthInfo ��
 * @param *pSenderCert        (In)  Sender�� ������
 * @param *pSenderPriKey      (In)  Sender�� �����Ű
 * @param *pDomainParam       (In)  ������ �Ķ����(NULL ����)
 * @param  nidHashAlg         (In)  ����� ���� hash algorithm
 *
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKISenderAuthInfo_SetCertAndPriKey(PKISenderAuthInfo *pPKISenderAuthInfo,
                                       Certificate       *pSenderCert,
                                       PrivateKeyInfo    *pSenderPriKey,
                                       Parameter         *pDomainParam,
                                       Nid                nidHashAlg);
/**
 * PKIMessage�� revPassPhrase�� �̿��� �����ϴ� ���(�����ÿ��� �ش��)
 * �� ������ ����ϱ� ���� Entity�� �������� revPassPhrase�� PKISenderAuthInfo���� �����Ѵ�.
 * owfAlg,macAlg�� client���� �޽����� �����ϱ� ���� ���Ǹ�, 
 * CA������ 0���� ����(���� �޽��� �ؼ��� ����)
 *
 * @param *pPKISenderAuthInfo (Out) ������ PKISenderAuthInfo ��
 * @param *pEntityName        (In)  Entity�� Name
 * @param *pszRevPassPhrase   (In)  ������ ���� �̸� ����� �� Entity�� revPassPhrase
 * @param  nidOwfAlg          (In)  MAC ������ ���� one way function �˰���
 * @param  nidMacAlg          (In)  MAC �˰���(ex)NID_hmacWithSHA1)
 *
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKISenderAuthInfo_SetRevPassPhrase(PKISenderAuthInfo *pPKISenderAuthInfo,
                                      Name              *pEntityName,
                                      const char        *pszRevPassPhrase,
                                      Nid                nidOwfAlg,
                                      Nid                nidMacAlg);

/**
 * POP�� subsequentMessage ����� ��, Conf�� MAC���� �����ϱ� ���� ����ü
 * (rfc2510 3.2.8 ����)
 *
 * @param *pPKISenderAuthInfo (Out) ������ PKISenderAuthInfo ��
 * @param *pbSymmKey          (In)  CA���� �������� ��ȣȭ �� �� ����� ��ĪŰ ��
 * @param  cbSymmKey          (In)  pbSymmKey�� ����
 *
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKISenderAuthInfo_SetPopEncCertKey(PKISenderAuthInfo *pPKISenderAuthInfo,
                                       unsigned char     *pbSymmKey,
                                       int                cbSymmKey);

/*## ������ �߱��� ���� ����ü �� �Լ� ##*/
/**
 *  ������ �߱� ��� ���� ������ ��� ����ü
 */
typedef struct _PKIEntityInfo {
   ASNSeqClass klass;
   Name *subject;             /*optional [0] */
   GeneralNames *subAltName;  /*optional [1] */
   Time *notAfter;            /*optional [2] */
} PKIEntityInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIEntityInfo;

/**
 * PKIEntityInfo ���� �����Ѵ�.
 *
 * @param *pPKIEntityInfo (Out) ������ PKIEntityInfo ��
 * @param *pSubject       (In)  Entity�� subject��(NULL ����)
 * @param *pszSubAltName  (In)  Entity�� subject alternative name(NULL����)
 * @param nSubAltOpt      (In)  Entity�� subject alternative name�� ����
 *                              (ex)GeneralName_rfc822Name, �׿� ���� GeneralName ����)
 *
 * @return 
 *  - SUCCESS : ����
 * @see PKIEntity_SetByStr
 */
LIBSPEC_CKM
int PKIEntityInfo_Set(PKIEntityInfo *pPKIEntityInfo,
                      Name          *pSubject,
                      const char    *pszSubAltName,
                      int            nSubAltOpt);

/**
 * PKIEntityInfo ���� �����Ѵ�.
 * subject���� Name�� �ƴ� ���ڿ��� �־����� ���� �����ϰ�� PKIEntityInfo_Set�� �����ϴ�.
 *
 * @param *pPKIEntityInfo (Out) ������ PKIEntityInfo ��
 * @param *pszSubject     (In)  Entity�� subject��(NULL ����)
 * @param *pszSubAltName  (In)  Entity�� subject alternative name(NULL����)
 * @param nSubAltOpt      (In)  Entity�� subject alternative name�� ����
 *                              (ex)GeneralName_rfc822Name, �׿� ���� GeneralName ����)
 *
 * @return 
 *  - SUCCESS : ����
 * @see PKIEntity_Set
 */
LIBSPEC_CKM
int PKIEntityInfo_SetByStr(PKIEntityInfo *pPKIEntityInfo,
                           const char    *pszSubject,
                           const char    *pszSubAltName,
                           int            nSubAltOpt);

/**
 * ������ �߱� ��ü�� ���� ������ ��� ����ü
 */
enum{
  PKIIssuerInfo_certAndPriKey = 1,
  PKIIssuerInfo_selfSigned    = 2,
};
typedef struct _PKIIssuerInfo {
   ASNChoiceClass klass;
   int		select;
   union{
      PKICertAndPriKey *certAndPriKey;	/* [0] */
      ASNNull *selfSigned;	/* [1] */
   }choice;
} PKIIssuerInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIIssuerInfo;

/**
 * PKIIssuerInfo ���� �����Ѵ�.
 *
 * @param pPKIIssuerInfo    (Out) ������ PKIIssuerInfo ��
 * @param bIssueSelfSigned  (In)  Self-Signed CA �������� �߱��ϴ� ��쿣 TRUE(1)
 * @param pIssuerCert       (In)  �߱� ��ü�� ������(Self-Signed �߱��ϴ� ��쿡�� NULL)
 * @param pIssuerPriKey     (In)  �߱� ��ü�� �����Ű(Self-Signed �߱��ϴ� ��쿡�� NULL)
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKIIssuerInfo_Set(PKIIssuerInfo  *pPKIIssuerInfo,
                      int             bIssueSelfSigned,
                      Certificate    *pIssuerCert,
                      PrivateKeyInfo *pIssuerPriKey);
LIBSPEC_CKM
int PKIIssuerInfo_SetEx(PKIIssuerInfo  *pPKIIssuerInfo,
                      int             bIssueSelfSigned,
                      Certificate    *pIssuerCert,
                      PrivateKeyInfo *pIssuerPriKey,
                      Nid             nidHashAlg);

typedef struct _PKIValidityTerm {
   ASNSeqClass klass;
   Integer *year;
   Integer *month;
   Integer *day;
   Integer *hour;
} PKIValidityTerm;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIValidityTerm;

/**
 * Ű������ ���� ����� �����Ű�� ��ȣȭ�Ͽ� ������ �� ���Ǵ� ������
 */
enum{
  PKIKeyRecCert_useCACert   = 1,
  PKIKeyRecCert_certificate = 2
};
typedef struct _PKIKeyRecCert {
  ASNChoiceClass klass;
  int     select;
  union{
    ASNNull *useCACert; /*[0]*/
    Certificate *certificate; /*[1]*/
  }choice;
} PKIKeyRecCert;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIKeyRecCert;


typedef struct _PKIPolicyInfo {
   ASNSeqClass klass;
   Integer  *index;                   /*optional [0] */
   UTF8String *policyName;            /*optional [1] */
   Integer  *publicKeyLen;            /*optional [2] */
   AlgorithmIdentifier *publicKeyAlg; /*optional [3] */
   PKIValidityTerm *validityTerm;
   Extensions *extsTemplate;
   PKIKeyRecCert *keyRecCert;         /*optional [4] */
} PKIPolicyInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIPolicyInfo;

typedef struct _SeqOfPKIPolicyInfo {
  ASNSeqOfClass klass;
  int size;
  PKIPolicyInfo **member;
} SeqOfPKIPolicyInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfPKIPolicyInfo;

/**
 * PKIPolicyInfo ���� �����Ѵ�.(������ ������ ����)
 *
 * @param pPKIPolicyInfo  (Out) ������ PKIPolicyInfo ��
 * @param pExtTemplate    (In)  ������ Ȯ�� ���� �� ������ ���� Template ��
 * @param nValidYear      (In)  ��ȿ�Ⱓ(��)
 * @param nValidMonth     (In)  ��ȿ�Ⱓ(��)
 * @param nValidDay       (In)  ��ȿ�Ⱓ(��)
 * @param nValidHour      (In)  ��ȿ�Ⱓ(�ð�)
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKIPolicyInfo_Set(PKIPolicyInfo *pPKIPolicyInfo,
                      Extensions    *pExtTemplate,
                      int            nValidYear,
                      int            nValidMonth,
                      int            nValidDay,
                      int            nValidHour);

/**
 * PKIPolicyInfo ���� �����Ѵ�.(������ ���� �� ����� ��å �ݿ��� ����)
 *
 * @param pPKIPolicyInfo  (Out) ������ PKIPolicyInfo ��
 * @param nIndex          (In)  ������� ��å�߿��� �� ��å�� ��ȣ(0~3)
 * @param pszPolicyName   (In)  ��å ��(��, 64�ڸ� ���� �� ����)
 * @param nPubKeyLen      (In)  ����Ű ����(bit)
 * @param nidPubKey       (In)  ����Ű �˰����� NID
 * @param pDomainParam    (In)  ������ �Ķ����
 * @param pExtTemplate    (In)  ������ Ȯ�� ���� �� ������ ���� Template ��
 * @param nValidYear      (In)  ��ȿ�Ⱓ(��)
 * @param nValidMonth     (In)  ��ȿ�Ⱓ(��)
 * @param nValidDay       (In)  ��ȿ�Ⱓ(��)
 * @param nValidHour      (In)  ��ȿ�Ⱓ(�ð�)
 * @param bKeyBackup      (In)  ����� �����Ű�� ��ȣȭ�Ͽ� �����ϴ� ����
 * @param pKeyRecCert     (In)  Ű ���� ����� ������, NULL�̸� CA�� �������� ���
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKIPolicyInfo_SetEx(PKIPolicyInfo *pPKIPolicyInfo,
                        int            nIndex,
                        const char    *pszPolicyName,
                        int            nPubKeyLen,
                        Nid            nidPubKey,
                        Parameter     *pDomainParam,
                        Extensions    *pExtTemplate,
                        int            nValidYear,
                        int            nValidMonth,
                        int            nValidDay,
                        int            nValidHour,
                        int            bKeyBackup,
                        Certificate   *pKeyRecCert);

/*## ��û ��� ���� ó���ϱ� ���� ����ü �� �Լ��� ##*/
/**
 * ������ �߱� ��û�� ���� ������� �����ϴ� ����ü
 * certificate���� status�� status���� PKIStatus_accepted�� PKIStatus_grantedWithMods�� ��쿡�� ����
 */

typedef struct _PKICertResponse {
   ASNSeqClass klass;
   Integer *certReqId;
   PKIStatusInfo *status;
   Certificate *certificate; /*optional [0] */
   PrivateKeyInfo *privateKey; /*optional [1], CA���� Ű�� �����ϴ� ��츦 ���� ����(Reserved) */
} PKICertResponse;

LIBSPEC_CKM
extern ASNDescriptor AD_PKICertResponse;

typedef struct _SeqOfPKICertResponse {
  ASNSeqOfClass klass;
  int size;
  PKICertResponse **member;
} SeqOfPKICertResponse;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfPKICertResponse;

/**
 * ������ �߱� ��û�� ���� ������� �����ϴ� ����ü
 */
typedef struct _PKICertRepInfo {
   ASNSeqClass klass;
   SeqOfCertificate *caPubs; /*optional [0] */
   SeqOfPKICertResponse *response;
} PKICertRepInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKICertRepInfo;


/**
 * ��û ������� �����ϴ� ����ü
 */
enum{
  PKIRepInfo_certResponse = 1,
  PKIRepInfo_revResponse,
  PKIRepInfo_genResponse,
  PKIRepInfo_errorResponse
};
typedef struct _PKIRepInfo {
   ASNChoiceClass klass;
   int		select;
   union {
      PKICertRepInfo  *certResponse;  /* [0] */
      RevRepContent   *revResponse;	  /* [1] */
      GenRepContent   *genResponse;	  /* [2] */
      ErrorMsgContent *errorResponse; /* [3] */
   } choice;
} PKIRepInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIRepInfo;

/**
 * PKICertResponse���� �����Ѵ�.
 *
 * @param *pPKICertResponse
 * @param *pCertReqId
 * @param *pStatus
 * @param *pCert
 * @param *
 *
 */
LIBSPEC_CKM
int PKICertResponse_Set(PKICertResponse *pPKICertResponse,
                        Integer         *pCertReqId,
                        PKIStatusInfo   *pStatus,
                        Certificate     *pCert,
                        PrivateKeyInfo  *pPriKey);

#ifdef __cplusplus
}
#endif

#endif /* _PKIINFO_H_ */

