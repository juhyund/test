/**
 * @file     pkiinfo.h
 *
 * @desc     PKI request message 및 confirm message 생성에 필요한 구조체 및 함수 선언
 * @author   박지영(jypark@pentasecurity.com)
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
 *  인증서 생성을 위한 키쌍에 대한 정보를 담는 구조체
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
 *  인증서 폐지를 위한 정보를 담는 구조체
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
 * General Message 요청을 위한 정보를 담는 구조체
 */
typedef InfoTypeAndValue PKIReqGenInfo;

#define AD_PKIReqGenInfo AD_InfoTypeAndValue


/*********************************************************************/
/* PKIReqInfo */

/**
 *  Request 메시지 생성에 필요한 정보를 담는 구조체
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
 * 인증서 발급을 위한 PKIReqInfo 값을 설정한다.
 *
 * @param *pPKIReqInfo    (Out) 설정할 PKIReqInfo 값
 * @param bKeyGenInCA     (In)  키 쌍을 CA에서 생성하는지 여부 (1: true, 0: false)
 * @param nPopTechnique   (In)  비공개키의 POP 방식
 * @param bArchiveKey     (In)  비공개키를 CA에서 저장할지 여부(CA로 비공개키를 전달해야 하는지 여부)
 * @param nidKeyType      (In)  해시 알고리즘이 지정된 비공개키 종류(ex. NID_sha1WithRSAEncryption, NID_kcdsaWithHAS160 ..)
 * @param  nKeyLen        (In)  공개키 값 & 비공개키 값이 NULL인 경우에 생성해야 하는 키 길이
                                공개키 값 & 비공개키 값이 NULL이 아니면 이 값은 무시된다.
 * @param *pPubKeyInfo    (In)  공개키 값(NULL 가능)
 * @param *pPriKeyInfo    (In)  비공개키 값(NULL 가능)
 * @param *pDomainParam   (In)  도메인 파라메터 값(NULL 가능)
 * @param *pOldCert       (In)  기존 인증서(인증서 갱신 시)
 *
 * @return 
 *  - SUCCESS : 성공
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
 * pPKIReqCertInfo에 필요한 신규 contorl을 추가한다.
 *
 * @param *pPKIReqCertInfo (Out) contorl를 추가할 PKIReqCertInfo 변수
 * @param  nidInfoType     (In)  추가할 control의 NID 값
 * @param *pInfoValue      (In)  추가할 control의 value 값
 *
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int ReqCertInfo_AddControl(PKIReqCertInfo      *pPKIReqCertInfo,
                           Nid                  nidInfoType,
                           ASN                 *pInfoValue);
/**
 * 인증서 폐지를 위한 PKIReqInfo 값을 설정한다.
 * 
 * @param *pPKIReqInfo    (Out) 설정할 PKIReqInfo 값
 * @param *pCertificate   (In)  폐지할 인증서
 * @param nReasonFlag     (In)  폐지 사유(0이면 지정하지 않음)
 */
LIBSPEC_CKM
int PKIReqInfo_SetReqRevInfo(PKIReqInfo   *pPKIReqInfo,
                             Certificate  *pCertificate,
                             int           nReasonFlag);

/**
 * PKIReqRevInfo에 필요한 crlEntryDetails을 추가한다.
 *
 * @param *pPKIReqRevInfo (In,Out) crlEntryDetails를 추가할 PKIReqRevInfo
 * @param *pExtension     (In) 추가할 extension 값
 * @return
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int PKIReqRevInfo_AddCrlEntryDetails(PKIReqRevInfo *pPKIReqRevInfo,
                                     Extension     *pExtension);

/**
 * 일반적인 정보 교환을 위한 PKIGenInfo 값을 설정한다.
 * 
 * @param pPKIReqInfo    (Out) 설정할 PKIReqInfo 값
 * @param nInfoType      (In)  보낼 정보의 종류를 나타내는 Nid 값
 * @param pInfoValue     (In)  전송할 정보체
 */
LIBSPEC_CKM
int PKIReqInfo_SetReqGenInfo(PKIReqInfo   *pPKIReqInfo,
                             Nid           nInfoType,
                             ASN          *pInfoValue);

/**
 *  Reference Number와 Secret Value를 사용한 사용자 인증을 위한 구조체
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
 *  서명을 통한 사용자 인증을 위한 구조체
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
 *  폐지시 revPassPhrase를 이용하여 폐지 신청을 하는 경우를 위한 구조체
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
 * POP가 subsequentMessage 방식일 때, Conf의 MAC값을 생성하기 위한 구조체
 * (rfc2510 3.2.8 참조)
 */
typedef struct _PKIPOPEncCertKey {
   ASNSeqClass klass;
   BitString *certEncKey;
} PKIPOPEncCertKey;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIPOPEncCertKey;

/**
 * 사용자 인증을 위한 정보를 담는 구조체
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
 * PKIMessage를 reference number와 secret value를 이용해 인증하는 경우
 * 그 과정에 사용하기 위한 reference number와 secret value로 PKISenderAuthInfo값을 설정한다.
 * owfAlg,macAlg,PbeAlg은 client에서 메시지를 생성하기 위해 사용되며, 
 * CA에서는 0값을 지정(추후 메시지 해석시 설정)
 *
 * @param *pPKISenderAuthInfo (Out) 설정할 PKISenderAuthInfo 값
 * @param *pszRefNum          (In)  Reference number 값
 * @param *pszSecretVal       (In)  Secret Value 값
 * @param  nidOwfAlg          (In)  MAC 생성시 사용될 one way function 알고리즘
 * @param  nidMacAlg          (In)  MAC 알고리즘(ex)NID_hmacWithSHA1)
 * @param  nidPbeAlg          (In)  PBE(Password-Based Encryption) 알고리즘(pbe.h 참조),
 *                                  PBE를 사용하지 않는 경우(CA 인증서를 가지고 있는 경우)엔 0을 지정
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int PKISenderAuthInfo_SetSecretValue(PKISenderAuthInfo *pPKISenderAuthInfo,
                                     const char *pszRefNum,
                                     const char *pszSecretVal,
                                     Nid         nidOwfAlg,
                                     Nid         nidMacAlg,
                                     Nid         nidPbeAlg);
                                     
/**
 * PKIMessage를 서명을 이용해 인증하는 경우
 * 그 과정에 사용하기 위한 Sender의 인증서와 비공개키로 PKISenderAuthInfo값을 설정한다.
 * nidHashAlg은 client에서 메시지를 생성하기 위해 사용되며, 
 * CA에서는 0값을 지정(추후 메시지 해석시 설정)
 *
 * @param *pPKISenderAuthInfo (Out) 설정할 PKISenderAuthInfo 값
 * @param *pSenderCert        (In)  Sender의 인증서
 * @param *pSenderPriKey      (In)  Sender의 비공개키
 * @param *pDomainParam       (In)  도메인 파라메터(NULL 가능)
 * @param  nidHashAlg         (In)  서명시 사용될 hash algorithm
 *
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int PKISenderAuthInfo_SetCertAndPriKey(PKISenderAuthInfo *pPKISenderAuthInfo,
                                       Certificate       *pSenderCert,
                                       PrivateKeyInfo    *pSenderPriKey,
                                       Parameter         *pDomainParam,
                                       Nid                nidHashAlg);
/**
 * PKIMessage를 revPassPhrase를 이용해 인증하는 경우(폐지시에만 해당됨)
 * 그 과정에 사용하기 위한 Entity의 인증서와 revPassPhrase로 PKISenderAuthInfo값을 설정한다.
 * owfAlg,macAlg은 client에서 메시지를 생성하기 위해 사용되며, 
 * CA에서는 0값을 지정(추후 메시지 해석시 설정)
 *
 * @param *pPKISenderAuthInfo (Out) 설정할 PKISenderAuthInfo 값
 * @param *pEntityName        (In)  Entity의 Name
 * @param *pszRevPassPhrase   (In)  폐지를 위해 미리 등록해 둔 Entity의 revPassPhrase
 * @param  nidOwfAlg          (In)  MAC 생성시 사용될 one way function 알고리즘
 * @param  nidMacAlg          (In)  MAC 알고리즘(ex)NID_hmacWithSHA1)
 *
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int PKISenderAuthInfo_SetRevPassPhrase(PKISenderAuthInfo *pPKISenderAuthInfo,
                                      Name              *pEntityName,
                                      const char        *pszRevPassPhrase,
                                      Nid                nidOwfAlg,
                                      Nid                nidMacAlg);

/**
 * POP가 subsequentMessage 방식일 때, Conf의 MAC값을 생성하기 위한 구조체
 * (rfc2510 3.2.8 참조)
 *
 * @param *pPKISenderAuthInfo (Out) 설정할 PKISenderAuthInfo 값
 * @param *pbSymmKey          (In)  CA에서 인증서를 암호화 할 때 사용한 대칭키 값
 * @param  cbSymmKey          (In)  pbSymmKey의 길이
 *
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int PKISenderAuthInfo_SetPopEncCertKey(PKISenderAuthInfo *pPKISenderAuthInfo,
                                       unsigned char     *pbSymmKey,
                                       int                cbSymmKey);

/*## 인증서 발급을 위한 구조체 및 함수 ##*/
/**
 *  인증서 발급 대상에 대한 정보를 담는 구조체
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
 * PKIEntityInfo 값을 설정한다.
 *
 * @param *pPKIEntityInfo (Out) 설정할 PKIEntityInfo 값
 * @param *pSubject       (In)  Entity의 subject값(NULL 가능)
 * @param *pszSubAltName  (In)  Entity의 subject alternative name(NULL가능)
 * @param nSubAltOpt      (In)  Entity의 subject alternative name의 종류
 *                              (ex)GeneralName_rfc822Name, 그외 값은 GeneralName 참조)
 *
 * @return 
 *  - SUCCESS : 성공
 * @see PKIEntity_SetByStr
 */
LIBSPEC_CKM
int PKIEntityInfo_Set(PKIEntityInfo *pPKIEntityInfo,
                      Name          *pSubject,
                      const char    *pszSubAltName,
                      int            nSubAltOpt);

/**
 * PKIEntityInfo 값을 설정한다.
 * subject값이 Name이 아닌 문자열로 주어지는 점을 제외하고는 PKIEntityInfo_Set과 동일하다.
 *
 * @param *pPKIEntityInfo (Out) 설정할 PKIEntityInfo 값
 * @param *pszSubject     (In)  Entity의 subject값(NULL 가능)
 * @param *pszSubAltName  (In)  Entity의 subject alternative name(NULL가능)
 * @param nSubAltOpt      (In)  Entity의 subject alternative name의 종류
 *                              (ex)GeneralName_rfc822Name, 그외 값은 GeneralName 참조)
 *
 * @return 
 *  - SUCCESS : 성공
 * @see PKIEntity_Set
 */
LIBSPEC_CKM
int PKIEntityInfo_SetByStr(PKIEntityInfo *pPKIEntityInfo,
                           const char    *pszSubject,
                           const char    *pszSubAltName,
                           int            nSubAltOpt);

/**
 * 인증서 발급 주체에 대한 정보를 담는 구조체
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
 * PKIIssuerInfo 값을 설정한다.
 *
 * @param pPKIIssuerInfo    (Out) 설정할 PKIIssuerInfo 값
 * @param bIssueSelfSigned  (In)  Self-Signed CA 인증서를 발급하는 경우엔 TRUE(1)
 * @param pIssuerCert       (In)  발급 주체의 인증서(Self-Signed 발급하는 경우에는 NULL)
 * @param pIssuerPriKey     (In)  발급 주체의 비공개키(Self-Signed 발급하는 경우에는 NULL)
 * @return 
 *  - SUCCESS : 성공
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
 * 키복구를 위해 사용자 비공개키를 암호화하여 저장할 때 사용되는 인증서
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
 * PKIPolicyInfo 값을 설정한다.(인증서 생성을 위해)
 *
 * @param pPKIPolicyInfo  (Out) 설정할 PKIPolicyInfo 값
 * @param pExtTemplate    (In)  인증서 확장 영역 값 설정을 위한 Template 값
 * @param nValidYear      (In)  유효기간(년)
 * @param nValidMonth     (In)  유효기간(월)
 * @param nValidDay       (In)  유효기간(일)
 * @param nValidHour      (In)  유효기간(시간)
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int PKIPolicyInfo_Set(PKIPolicyInfo *pPKIPolicyInfo,
                      Extensions    *pExtTemplate,
                      int            nValidYear,
                      int            nValidMonth,
                      int            nValidDay,
                      int            nValidHour);

/**
 * PKIPolicyInfo 값을 설정한다.(인증서 생성 및 사용자 정책 반영을 위해)
 *
 * @param pPKIPolicyInfo  (Out) 설정할 PKIPolicyInfo 값
 * @param nIndex          (In)  사용자의 정책중에서 이 정책의 번호(0~3)
 * @param pszPolicyName   (In)  정책 명(단, 64자를 넘을 수 없다)
 * @param nPubKeyLen      (In)  공개키 길이(bit)
 * @param nidPubKey       (In)  공개키 알고리즘의 NID
 * @param pDomainParam    (In)  도메인 파라메터
 * @param pExtTemplate    (In)  인증서 확장 영역 값 설정을 위한 Template 값
 * @param nValidYear      (In)  유효기간(년)
 * @param nValidMonth     (In)  유효기간(월)
 * @param nValidDay       (In)  유효기간(일)
 * @param nValidHour      (In)  유효기간(시간)
 * @param bKeyBackup      (In)  사용자 비공개키를 암호화하여 저장하는 여부
 * @param pKeyRecCert     (In)  키 복구 기관의 인증서, NULL이면 CA의 인증서를 사용
 * @return 
 *  - SUCCESS : 성공
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

/*## 신청 결과 값을 처리하기 위한 구조체 및 함수들 ##*/
/**
 * 인증서 발급 요청에 대한 결과값을 저장하는 구조체
 * certificate값은 status의 status값이 PKIStatus_accepted나 PKIStatus_grantedWithMods인 경우에만 존재
 */

typedef struct _PKICertResponse {
   ASNSeqClass klass;
   Integer *certReqId;
   PKIStatusInfo *status;
   Certificate *certificate; /*optional [0] */
   PrivateKeyInfo *privateKey; /*optional [1], CA에서 키를 생성하는 경우를 위한 영역(Reserved) */
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
 * 인증서 발급 요청에 대한 결과값을 저장하는 구조체
 */
typedef struct _PKICertRepInfo {
   ASNSeqClass klass;
   SeqOfCertificate *caPubs; /*optional [0] */
   SeqOfPKICertResponse *response;
} PKICertRepInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKICertRepInfo;


/**
 * 신청 결과값을 저장하는 구조체
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
 * PKICertResponse값을 설정한다.
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

