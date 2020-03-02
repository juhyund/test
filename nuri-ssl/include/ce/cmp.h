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

/* FIXME : 옛 rfc2510.h에서 급히 포팅하느라 들어간 부분.
 * 현재의 코딩 스타일에 맞게 정리가 필요함 */
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

/*## PKIStatusInfo 관련 함수 ##*/
/**
 * PKIFailureInfo 값을 설정
 */
LIBSPEC_CKM
int PKIFailureInfo_Set(PKIFailureInfo *pInfo, int in);
/**
 * PKIFailureInfo 값을 가져옴
 *
 * @return
 *    PKIFailureInfo 값(실패시에는 FAIL)
 */
LIBSPEC_CKM
int PKIFailureInfo_Get(PKIFailureInfo *pInfo);

/**
 * PKIStatusInfo값을 설정한다.
 *
 * @param *pStatus      (Out) 설정할 PKIStatusInfo 값
 * @param  nStatus      (In)  Status 값(PKIStatus_accepted, ..)
 * @param *pszFreeText  (In)  statusString 값, NULL이면 설정하지 않음
 * @param  nFailInfo    (In)  failInfo 값(PKIFailureInfo_badAlg, ..), 0이면 설정하지 않음
 *
 * @return
 *  - SUCCESS : 성공
 * @note : 현재 statusString(SEQ OF UTF8String)은 하나만을 지정할 수 있음
 */
LIBSPEC_CKM
int PKIStatusInfo_Set(PKIStatusInfo *pStatus, int nStatus, const char *pszFreeText, int nFailInfo);

/*## EncryptedValue 관련 함수 ##*/

/** 대칭키 최대 길이 */
#define MAX_SYMMKEY_LEN 128 
#define DEFAULT_SYMMETRIC_KEY_LEN 16
enum{
  ER_INSUFFICIENT_BUFFER = -500,        /**< Buffer 크기가 작음 */
  ER_ENCVALUE_INVALID_ENCRYPTEDVALUE,   /**< 잘못된 형식의 EncryptedValue */
  ER_ENCVALUE_INVALID_SYMMKEY,          /**< 잘못된 대칭키 값(대칭키 값이 NULL이거나 올바르지 않은 길이) */
  ER_ENCVALUE_CANNOT_FIND_SYMMKEY,      /**< EncryptedValue로부터 대칭키 값을 얻는데 실패 */
  ER_ENCVALUE_FAIL_TO_GET_SYMMKEY,      /**< 대칭키 값을 복호화 하는데 실패 */
  ER_ENCVALUE_CANNOT_FIND_KEYALG,       /**< 공개키 암호화에 사용된 알고리즘이 지정되어 있지 않음 */
  ER_ENCVALUE_CANNOT_FIND_SYMMALG,      /**< 대칭키 암호화에 사용된 알고리즘이 지정되어 있지 않음 */
  ER_ENCVALUE_INVALID_SYMMALG,          /**< 올바르지 않은 대칭키 암호화 알고리즘 */
};
/**
 * 주어진 데이터를 주어진 키로 암호화하여 EncryptedValue를 설정한다.
 * (암호화 하는데 사용하는 해시 알고리즘은 SHA1을 사용)
 *
 * @param *pEncryptedValue  (Out) EncryptedValue값
 * @param *pbValue          (In)  암호화 할 데이터
 * @param cbValue           (In)  pbValue의 길이
 * @param *pbSymmKey        (In)  pbValue를 대칭키 암호화 하는데 사용할 대칭키
 *                                (NULL이면 내부적으로 cbSymmKey 길이에 해당하는 대칭키를 생성한다)
 * @param cbSymmKey         (In)  pbKey의 길이
 * @param pSymmAlg          (In)  대칭키 암호화 알고리즘
 *                                혹은 PBE(Password Based Encryption) 알고리즘 PKCS#12만을 지원)
 * @param pPubKey           (In)  대칭키를 공개키 암호화 하는데 사용할 공개키.
 *                                이미 recipient가 대칭키를 알고 있어서 대칭키를 전달할 필요가 없는 경우에는
 *                                NULL값을 입력.
 *                                NULL이면 암호화 된 대칭키를 EncryptedValue에 포함시키지 않는다.
 * @param HashAlg           (In)  공개키 암호화 시에 사용될 Hash 알고리즘. pPubKey가 NULL이면 이 값은 무시된다.
 * @return 
 *   - SUCCESS : 성공
 *   - 그외     : 실패
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
 * EncryptedValue를 복호화한다.
 * 이 복호화 방법은 다음의 2가지로 구분된다.
 * 1) 비공개키(pPriKey)가 NULL이 아닌 경우
 *    이 경우, 이 비공개키를 이용하여, EncryptedValue내의 encSymmKey값을 공개키 복호화 하여 대칭키값을
 *    얻은 뒤, 이 대칭키를 이용하여 데이터를 복호화한다. 이때, 대칭키값은 pbSymmKey에 저장된다.
 *    (pbSymmKey가 NULL인 경우, 대칭키 값은 리턴되지 않는다.)
 * 2) 비공개키(pPriKey)가 NULL인 경우
 *    이 경우, 입력받은 대칭키(pbSymmKey)값을 이용하여 데이터를 복호화한다.
 *    이 때, cbSymmKeyBufLen은 대칭키의 길이를 갖는다.
 *
 * @param *pEncryptedValue  (In)  복호화 할 EncryptedValue 
 * @param *pPriKey          (In)  EncryptedValue를 복호화 하는데 사용할 비공개키
 *                                데이터 암호화에 사용된 대칭키값을 이미 알고 있는 경우에는 NULL을 입력
 * @param *pbValue          (Out) 복호화 된 데이터
 * @param *pcbValue         (Out) 복호화 된 데이터의 길이
 * @param cbValueBufLen     (In)  pbValue의 버퍼의 크기
 * @param *pbSymmKey        (In,Out) 데이터 암호화에 사용된 대칭키. 
 *                                NULL이면 대칭키 값을 리턴되지 않는다.
 * @param *pcbSymmKey       (Out) 대칭키의 길이
 * @param cbSymmKeyBufLen   (In)  pbSymmKey의 버퍼의 크기, pbSymmKey가 입력 파라메터일때에는 pbSymmKey의 길이
 * @param *pSymmEncAlg      (Out) 데이터 암호화에 사용된 대칭키 알고리즘(NULL이면 알고리즘을 리턴하지 않음)
 *
 * @return 
 *   - SUCCESS : 성공
 *   - 그외     : 실패
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
 * 주어진 PKIHeader와 PKIBody로 PKIMessage를 생성한다
 * priKey와 passwd값은 header의 protectionAlg에서 지정한 방식에 따른 값이어야 한다.
 *
 * @param *out        (Out) 결과값, 성공시 메시지가 저장됨. 
 *                          미리 ASN_New(PKIMessage,NULL)를 이용하여 초기화 되어 있어야 한다.
 * @param *pKIHeader  (In)  PKIHeader값
 * @param *pKIBody    (In)  PKIBody값
 * @param *priKey     (In)  protection 생성시에 사용할 privatekey
 * @param *signerCert (In)  서명시에 Domain parameter가 필요한 경우, 그 값을 얻기 위한 인증서
 * @param *domainParam(In)  Domain parameter, priKey와 signerCert에 domain parameter가 없는 경우 사용됨
 * @param *passwd     (In)  protection 생성시에 사용할 password
 * @param  passwdLen  (In)  passwd의 길이
 * @param *certs      (In)  PKIMessage의 extraCerts 영역에 추가할 인증서, NULL인 경우 추가하지 않음
 *
 * @return 
 *  - SUCCESS : 성공
 *  - 그외     : 실패
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
 * PKIMessage를 검사한다. 이 검사 과정은 다음의 과정들을 포함한다.
 *  - Header의 version 값 검사
 *  - Header의 message time이 있는 경우, message time이 기준 시간으로부터 일정 시간 이내인지를 검사
 *  - Protection 검사(Protection은 반드시 존재해야 함)
 *
 * @param *pKIMessage   (In) 검사하려는 PKIMessage
 * @param *cert         (In) Protection의 서명을 검증하기 위한 인증서
 * @param *passwd       (In) MAC값을 검증하기 위한 password
 * @param *passwdLen    (In) passwd의 길이
 * @param checkTime     (In) Message time을 검증하기 위한 기준 시간(0인 경우 현재 시간 사용)
 *
 * @return 
 *  - SUCCESS : 성공
 *  - 그외     : 실패
 */
LIBSPEC_CKM
int CMP_VerifyPKIMessage(PKIMessage  *pKIMessage,
                         Certificate *cert,
                         const char  *passwd,
                         int          passwdLen,
                         time_t       checkTime);


/*## POP 관련 함수 ##*/
enum {
  /*## POP 생성/검증시 에러 ##*/
  ER_CMP_POP_INVALID_POP_TECHNIQUE,     /**< 잘못된 방식의 POP 방식 */
  ER_CMP_POP_NOT_EXIST,                 /**< POP 값이 존재하지 않음 */
  ER_CMP_POP_CANNOT_FIND_PUBLICKEY,     /**< PublicKey 값이 존재하지 않음 */      
  ER_CMP_POP_INVALID_SIGNATURE,         /**< POP가 signature 방식일 때, 서명값 검증에 실패한 경우 */
  ER_CMP_POP_NOT_SUPPORTED,             /**< 지원되지 않는 방식의 POP */
  ER_CMP_POP_CANNOT_FIND_SUBJECT,       /**< certTemplate에 publicKey값은 있으나 subject값이 없음 */
  ER_CMP_POP_POPSKINPUT_MUST_NOT_EXIST, /**< certTemplate에 publicKey값이 있으면서 
                                             pop의 signature에 popskInput값이 존재하는 경우 */
  ER_CMP_POP_FAIL_TO_ENCODE,            /**< signature를 검증하기 위한 input값 생성 실패 */
  ER_CMP_POP_CANNOT_FIND_POPSKINPUT,    /**< certTemplate에 publicKey값이 없으면서
                                             pop의 signature에 popskInput값이 없는 경우 */
  ER_CMP_POP_INVALID_THISMESSAGE,       /**< POP가 thisMessage 방식일 때, thisMessage형식이 잘못된 경우
                                             thisMessage는 EncryptedValue를 DER encoding한 뒤,
                                             BitString으로 전환한 값이어야 한다. */
  ER_CMP_POP_FAIL_TO_DECODE_PRIKEYINFO, /**< POP가 thisMessage 방식일 때, thisMessage는
                                             PrivateKeyInfo가 암호화 된 값을 가지고 있어야 하나, 
                                             PrivateKeyInfo값을 얻는데 실패했을 때 */
  ER_CMP_POP_FAIL_TO_DECRYPT,           /**< POP의 thisMessage값을 decrypt하는데 실패 */
  ER_CMP_POP_FAIL_TO_VERIFY,            /**< POP 검증에 실패한 경우 */
  /*## POP 생성시 에러 ##*/
  ER_CMP_POP_FAIL_TO_MAKE_PUBLICKEYMAC, /**< POP의 poposkInput을 만들기 위한 publicKeyMAC값 생성 실패 */
  ER_CMP_POP_INVALID_PUBLICKEYINFO,     /**< 잘못된 형식의 publicKeyInfo 값 */
  ER_CMP_POP_INAVLID_PRIVATEKEYINFO,    /**< 잘못된 형식의 privateKeyInfo 값 */
  ER_CMP_POP_INVALID_CERTTEMPLATE,      /**< 잘못된 형식의 certTemplate 값 */
  ER_CMP_POP_FAIL_TO_ENCODE_POPOSKINPUT, /**< poposkInput encoding 실패 */ 
  ER_CMP_POP_FAIL_TO_MAKE_SIGNATURE,    /**< 서명값 생성 실패 */
  ER_CMP_POP_FAIL_TO_ENCRYPT_PRIKEYINFO,/**< 비공개키 암호화 실패 */
  ER_CMP_POP_CANNOT_FIND_PUBKEY_IN_CERTTEMPLATE, /**< CertTemplate 내에 공개키 값이 없을 때 */
  ER_CMP_POP_CAPRIKEY_NOT_SUPPLIED, /**< CA의 비공개키를 입력으로 주지 않았을 때 */
};

typedef enum{
  POP_Technique_None  = 0,          /**< POP을 사용하지 않음(별도의 방식 사용) */
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
 * CertReqMsg의 POP값을 검증한다.
 *
 * @param *pPopTechnique  (Out) POP방식
 * @param **ppPubKey      (Out) POP가 검증된 공개키 값(NULL이면 리턴하지 않음)
 * @param **ppPriKey      (Out) CertReqMsg내에 암호화 된 비공개키가 포함되어 전송된 경우, 복호화 된 비공개키 값,
 *                              포함되어 전송되지 않은 경우에는 NULL값이 저장됨(NULL이면 리턴하지 않음)
 * @param *pCertReq       (In)  POP를 검증할 CertReqMsg
 * @param *pCAPrivateKey  (In)  POP 방식이 thisMessage인 경우에 POP를 검증하기 위한 CA의 비공개키
 * @param *pDomainParam   (In)  POP 방식이 signature인 경우에 POP의 서명값을 검증하는데 사용되는 domainParameter
 * @param *pszSecretValue (In)  ir의 경우 secret value 값(PKIMessage의 protection 생성시 사용된 값)
 *
 * @return 
 *  - SUCCESS : 성공
 *  - 그외     : 실패
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
 * POP 값을 생성한다.
 * 서명을 이용한 POP를 사용하는 경우, 이 함수에서 지원하는 방식은 다음과 같다.
 * 1. sender name을 알고 있는 경우
 *    이 경우 pCertTemplate값은 NULL이 아니어야 하고, 반드시 sender name과 publicKey 값을 가지고 있어야 한다.
 *    함수 내에서는 certTemplate의 DER-Encoding 된 값에 대해 서명값을 생성한다.
 * 2. sender name을 모르고 있는 경우
 *    reference number와 secret value를 이용하여 ir을 생성하는 경우가 이에 해당되며,
 *    함수 내에서는 publicKeyInfo와 secret value값을 이용하여 poposkInput을 생성한 뒤, 이의 DER-Encoding된
 *    값에 대해 서명값을 생성한다.
 *
 * @param *pPop            (Out) 생성된 ProofOfPossession 값
 * @param *pCertTemplate   (In)  CertTemplate 값(signature에 의한 POP일때 서명값을 생성하기 위해 사용)
 * @param *pSenderAuthInfo (In)  신청자 인증을 위한 정보
 *                               이 값이 필요한 경우는 다음과 같으며 다음에 해당하지 않는 경우에는 NULL값 가능.
 *                               1. POP가 thisMessage 방식이나, CA인증서를 얻을 수 없기에,
 *                                  secretvalue를 이용하여 비공개키를 암호화 하여 전송하려는 경우
 * @param *pReqCertInfo    (In)  인증서 발급 신청에 대한 키 정보
 * @param *pCACert         (In)  CA의 인증서(POP가 thisMessage 방식일때, 비공개키를 암호화 하기 위해 사용
 *                                        단, ir의 경우에는 이 값이 NULL이면 secret value를 이용하여 암호화)
 * @param nidSymmAlg       (In)  대칭키 알고리즘(POP가 thisMessage 방식일때, 비공개키를 암호화 하는데 사용)
 * @return
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int CMP_MakePOP(ProofOfPossession   *pPop,
                CertRequest         *pCertReq,
                PKISenderAuthInfo   *pSenderAuthInfo,
                PKIReqCertInfo      *pReqCertInfo,
                Certificate         *pCACert,
                AlgorithmIdentifier *pSymmAlg);

/*# PBM(Password Based MAC) 관련 함수 #*/
#define PBM_SALT_DEFAULT        "\x83\x24\x49\x32\x17\x07\x53\x15"
#define PBM_SALT_LEN            8
#define PBM_ITERATION_DEFAULT   1976


/**
 * PBMParameter 값을 설정한다.
 *
 * @param *pParam         (Out) 설정할 PBMParameter 값
 * @param *pbSalt         (In)  Salt 값
 * @param cbSalt          (In)  Salt 길이
 * @param nidOwf          (In)  AlgId for a One-way function
 * @param nIterationCount (In)  number of times the OWF is applied
 * @param nidMac          (In)  the MAC AlgId
 *
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int PBMParameter_Set(PBMParameter *pParam, 
                     const unsigned char *pbSalt, int cbSalt,
                     Nid  nidOwf,
                     int  nIterationCount,
                     Nid  nidMac);


/**
 * 신규 KeyPolicyRequest를 생성하는 함수 
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
