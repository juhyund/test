#ifndef _CMS_H_
#define _CMS_H_

/** @defgroup CMS CMS handling
 * @ingroup SP
    @brief Cryptographic Message Syntax(PKCS#7 TYPE) Manipulation Module
*/

/** @file cms.h
    @ingroup CMS
    @brief CMS 모듈의 타입 선언과 인터페이스 선언
*/

#ifdef WIN32
#include <time.h>
#elif _WIN32_WCE
#include "wincemodule.h"
#endif

#include "ckm_pkcrypt.h"
#include "sp_define.h"
#include "asn1.h"
#include "pkcs.h"
#include "x509pkc.h"
#include "x509ac.h"
#include "bcipher_op.h"
#include "cert.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * 6. Useful types                 
 */

typedef Version CMSVersion;
#define AD_CMSVersion AD_Version

enum {
  CMS_VER0 = 0,
  CMS_VER1,
  CMS_VER2,
  CMS_VER3,
  CMS_VER4
};

typedef CertificateList CertificateRevocationList;
#define AD_CertificateRevocationList AD_CertificateList 

typedef struct {
  ASNSetOfClass klass;
  int size;
  CertificateRevocationList **member;
} CertificateRevocationLists;

LIBSPEC_SP
extern ASNDescriptor AD_CertificateRevocationLists;

typedef struct {
  ASNSeq klass;
  Version *version;
  Certificate *certificate; /* X.509 Certificate */
  Attributes *attributes;
} ExtendedCertificateInfo;

LIBSPEC_SP
extern ASNDescriptor AD_ExtendedCertificateInfo;

typedef struct {
  ASNChoiceClass           klass;
  int                      select;
  union {
    Certificate             *certificate;
    ExtendedCertificateInfo *extendedCertificate; /* [0] IMPLICIT -- Obsolete */
    AttributeCertificate    *attrCert; /* [1] IMPLICIT -- See X.509 */
  } choice;
} CertificateChoices;

LIBSPEC_SP
extern ASNDescriptor AD_CertificateChoices;

typedef struct {
  ASNSetOfClass        klass;
  int                  size;
  CertificateChoices **member;
} CertificateSet;

LIBSPEC_SP
extern ASNDescriptor AD_CertificateSet;

typedef AlgorithmIdentifier SignatureAlgorithmIdentifier;
#define AD_SignatureAlgorithmIdentifier AD_AlgorithmIdentifier

typedef OctetString SignatureValue;
#define AD_SignatureValue AD_OctetString

typedef BitString CMSSignature;  /* due to conflict of OCSP Signature */
#define AD_CMSSignature AD_BitString

typedef struct {
  ASNSeq klass;
  ExtendedCertificateInfo *extendedCertificateInfo;
  SignatureAlgorithmIdentifier *signatureAlgorithm;
  CMSSignature *signature;  /* due to conflict of OCSP Signature */
} ExtendedCertificate; 

LIBSPEC_SP
extern ASNDescriptor AD_ExtendedCertificate;

typedef struct {
  ASNChoiceClass klass;
  int select;  
  union {
    Certificate *certificate;
    ExtendedCertificate *extendedCertificate; /* [0] IMPLICIT */
  } choice;
} ExtendedCertificateOrCertificate;

LIBSPEC_SP
extern ASNDescriptor AD_ExtendedCertificateOrCertificate;

typedef struct {
  ASNSetOfClass klass;
  int size;
  ExtendedCertificateOrCertificate **member;
} ExtendedCertificatesAndCertificates;

LIBSPEC_SP
extern ASNDescriptor AD_ExtendedCertificatesAndCertificates;

typedef struct {
  ASNSeqClass klass;
  Name *issuer;
  CertificateSerialNumber *serialNumber;
} IssuerAndSerialNumber;

LIBSPEC_SP
extern ASNDescriptor AD_IssuerAndSerialNumber;

/* made by herstory, not PKCS#7 ASN.1 Type */
typedef struct {
  ASNSetOfClass klass;
  int size;
  IssuerAndSerialNumber **member;
} IssuerAndSerialNumbers;

LIBSPEC_SP
extern ASNDescriptor AD_IssuerAndSerialNumbers;

/*****************************************************************************
 * 7. General syntax: pkcs.h
 */


/*****************************************************************************
 * 8. Data content type: pkcs.h
 */


/*****************************************************************************
 * 9. Signed-data content type
 */

/* RFC2630 - CMS_VER3 */
typedef struct {
  ASNSeqClass   klass;
  ContentType  *eContentType;
  OctetString  *eContent;   /* [0] EXPLICIT OPTIONAL */
} EncapsulatedContentInfo;

LIBSPEC_SP
extern ASNDescriptor AD_EncapsulatedContentInfo;

typedef struct {
  ASNChoiceClass  klass;
  int select;
  union {
    IssuerAndSerialNumber  *issuerAndSerialNumber;
    SubjectKeyIdentifier   *subjectKeyIdentifier; /* [0] */
  } choice;
} SignerIdentifier;

LIBSPEC_SP
extern ASNDescriptor AD_SignerIdentifier;

enum {
  SignerIdentifier_issuerAndSerialNumber = 1,
  SignerIdentifier_subjectKeyIdentifier
};

typedef OctetString EncryptedDigest;
#define AD_EncryptedDigest AD_OctetString

typedef SetOfAttribute SignedAttributes;
#define AD_SignedAttributes AD_SetOfAttribute

typedef SetOfAttribute UnsignedAttributes;
#define AD_UnsignedAttributes AD_SetOfAttribute

typedef struct {
  ASNSeqClass                   klass;
  CMSVersion                   *version;
  SignerIdentifier             *sid;
  DigestAlgorithmIdentifier    *digestAlgorithm;
  SignedAttributes             *signedAttrs;        /* [0] IMPLICIT OPTIONAL */
  SignatureAlgorithmIdentifier *signatureAlgorithm;
  SignatureValue               *signature;
  UnsignedAttributes           *unsignedAttributes; /* [1] IMPLICIT OPTIONAL */
} SignerInfo;

LIBSPEC_SP
extern ASNDescriptor AD_SignerInfo;

typedef struct {
  ASNSetOfClass klass;
  int          size;
  SignerInfo **member;
} SignerInfos;

LIBSPEC_SP
extern ASNDescriptor AD_SignerInfos;

typedef struct {
  ASNSetOfClass klass;
  int                         size;
  DigestAlgorithmIdentifier **member;
} DigestAlgorithmIdentifiers;

LIBSPEC_SP
extern ASNDescriptor AD_DigestAlgorithmIdentifiers;

typedef struct {
  ASNSeqClass klass;
  CMSVersion *version;
  DigestAlgorithmIdentifiers *digestAlgorithms;
  /* EncapsulatedContentInfo *encapContentInfo; */
  ContentInfo *contentInfo; /* for backward compatibility */
  CertificateSet *certificates; /* [0] IMPLICIT OPTIONAL */
  CertificateRevocationLists *crls; /* [1] IMPLICIT OPTIONAL */
  SignerInfos *signerInfos;
} SignedData;
 
LIBSPEC_SP
extern ASNDescriptor AD_SignedData;


/*****************************************************************************
 * 10. Enveloped-data content type
 */

typedef SetOfAttribute UnprotectedAttributes;
#define AD_UnprotectedAttributes AD_SetOfAttribute

typedef struct {
  ASNSeqClass                klass;
  CertificateSet            *certs; /* [0] IMPLICIT OPTIONAL */
  CertificateRevocationLists crls;  /* [1] IMPLICIT OPTIONAL */
} OriginatorInfo;

LIBSPEC_SP
extern ASNDescriptor AD_OriginatorInfo;

typedef SignerIdentifier RecipientIdentifier;
#define AD_RecipientIdentifier AD_SignerIdentifier

enum {
  RecipientIdentifier_issuerAndSerialNumber = 1,
  RecipientIdentifier_subjectKeyIdentifier
};

typedef struct {
  ASNSeqClass klass;
  CMSVersion *version;  /* always set to 0 or 2 */
  RecipientIdentifier *rid;
  KeyEncryptionAlgorithmIdentifier *keyEncryptionAlgorithm;
  EncryptedKey *encryptedKey;
} KeyTransRecipientInfo;

LIBSPEC_SP
extern ASNDescriptor AD_KeyTransRecipientInfo;

typedef PublicKeyInfo OriginatorPublicKey;
#define AD_OriginatorPublicKey AD_PublicKeyInfo

typedef struct {
  ASNChoiceClass klass;
  int select;
  union {
    IssuerAndSerialNumbers *issuerAndSerialNumber;
    SubjectKeyIdentifier   *subjectKeyIdentifier; /* [0] */
    OriginatorPublicKey    *originatorKey;        /* [1] */
  } choice;
} OriginatorIdentifierOrKey;

LIBSPEC_SP
extern ASNDescriptor AD_OriginatorIdentifierOrKey;

typedef OctetString UserKeyingMaterial;
#define AD_UserKeyingMaterial AD_OctetString

typedef struct {
  ASNSeqClass klass;
  ASNOid *keyAttrId;
  Any    *kyeAttr; /* OPTIONAL */
} OtherKeyAttribute;

LIBSPEC_SP
extern ASNDescriptor AD_OtherKeyAttribute;

typedef struct {
  ASNSeqClass klass;
  SubjectKeyIdentifier *subjectKeyIdentifier;
  GeneralizedTime *data; /* OPTIONAL */
  OtherKeyAttribute *other; /* OPTIONAL */
} RecipientKeyIdentifier;

LIBSPEC_SP
extern ASNDescriptor AD_RecipientKeyIdentifier;

typedef struct {
  ASNChoiceClass klass;
  int select;
  union {
    IssuerAndSerialNumbers *issuerAndSerialNumber;
    RecipientKeyIdentifier *rKeyId; /* [0] IMPLICIT */
  } choice;
} KeyAgreeRecipientIdentifier;

LIBSPEC_SP
extern ASNDescriptor AD_KeyAgreeRecipientIdentifier;

typedef struct {
  ASNSeqClass klass;
  KeyAgreeRecipientIdentifier *rid;
  EncryptedKey *encryptedKey;
} RecipientEncryptedKey;

LIBSPEC_SP
extern ASNDescriptor AD_RecipientEncryptedKey;

typedef struct {
  ASNSeqOfClass klass;
  int size;
  RecipientEncryptedKey **member;
} RecipientEncryptedKeys;

LIBSPEC_SP
extern ASNDescriptor AD_RecipientEncryptedKeys;

typedef struct {
  ASNSeqClass klass;
  CMSVersion *version; /* always set to 3 */
  OriginatorIdentifierOrKey *originator; /* [0] EXPLICIT */
  UserKeyingMaterial *ukm; /* [1] EXPLICIT */
  KeyEncryptionAlgorithmIdentifier *keyEncryptionAlgorithm;
  RecipientEncryptedKeys *recipientEncryptedKey;
} KeyAgreeRecipientInfo;

LIBSPEC_SP
extern ASNDescriptor AD_KeyAgreeRecipientInfo;

typedef struct {
  ASNSeqClass klass;
  OctetString *keyIdentifier;
  GeneralizedTime *data;
  OtherKeyAttribute *other;
} KEKIdentifier;

LIBSPEC_SP
extern ASNDescriptor AD_KEKIdentifier;

typedef struct {
  ASNSeqClass klass;
  CMSVersion *version; /* always set to 4 */
  KeyIdentifier *kekid;
  KeyEncryptionAlgorithmIdentifier *keyEncryptionAlgorithm;
} KEKRecipientInfo;

LIBSPEC_SP
extern ASNDescriptor AD_KEKRecipientInfo;

typedef struct {
  ASNChoiceClass         klass;
  int select;
  union {
    KeyTransRecipientInfo *ktri;
    KeyAgreeRecipientInfo *kari;  /* [1] */
    KEKRecipientInfo      *kekri; /* [2] */
  } choice;
} RecipientInfo;

LIBSPEC_SP
extern ASNDescriptor AD_RecipientInfo;

enum {
  RecipientInfo_ktri = 1,
  RecipientInfo_kari,
  RecipientInfo_kekri
};

typedef struct {
  ASNSetOfClass klass;
  int             size;
  RecipientInfo **member;
} RecipientInfos; 

LIBSPEC_SP
extern ASNDescriptor AD_RecipientInfos;

typedef struct {
  ASNSeqClass            klass;
  CMSVersion            *version;
  OriginatorInfo        *originatorInfo; /* [0] IMPLICIT OPTIONAL */
  RecipientInfos        *recipientInfos;
  EncryptedContentInfo  *encryptedContentInfo;
  UnprotectedAttributes *unprotectedAttrs; /* [1] IMPLICIT OPTIONAL */
} EnvelopedData;

LIBSPEC_SP
extern ASNDescriptor AD_EnvelopedData;
  

/*****************************************************************************
 * 11. Signed-and-enveloped-data content type
 */

typedef struct {
  ASNSeqClass klass;
  Version *version;
  RecipientInfos *recipientInfos;
  DigestAlgorithmIdentifiers *digestAlgorithms;
  EncryptedContentInfo *encryptedContentInfo;
  ExtendedCertificatesAndCertificates *certificates; /* [0] IMPLICIT OPTIONAL */
  CertificateRevocationLists *crls; /* [1] IMPLICIT OPTIONAL */
  SignerInfos *signerInfos; 
} SignedAndEnvelopedData;

LIBSPEC_SP
extern ASNDescriptor AD_SignedAndEnvelopedData;
  

/*****************************************************************************
 * 12. Digested-data content type
 */

typedef struct {
  ASNSeqClass klass;
  Version *version;
  DigestAlgorithmIdentifier *digestAlgorithm;
  ContentInfo *contentInfo;
  Digest *digest;
} DigestedData;

LIBSPEC_SP
extern ASNDescriptor AD_DigestedData;


/*****************************************************************************
 * 13. Encrypted-data content type - pkcs_type.h
 */

/*****************************************************************************
 * 14. Object Identifiers
 */
/*
pkcs-7                  OBJECT IDENTIFIER ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) 7 }
data                    OBJECT IDENTIFIER ::= { pkcs-7 1 }
signedData              OBJECT IDENTIFIER ::= { pkcs-7 2 }
envelopedData           OBJECT IDENTIFIER ::= { pkcs-7 3 }
signedAndEnvelopedData  OBJECT IDENTIFIER ::= { pkcs-7 4 }
digestedData            OBJECT IDENTIFIER ::= { pkcs-7 5 }
encryptedData           OBJECT IDENTIFIER ::= { pkcs-7 6 }
*/





#define CMS_SIGNED_DATA_CANNOT_FIND_SIGNER_INFO -1301

/*****************************************************************************
 * EncryptedData manipulaint functions
 */

#define EncryptedData_CheckAlg(encAlg) \
               (encAlg == NID_seedECB || \
                encAlg == NID_seedCBC || \
                encAlg == NID_seedOFB || \
                encAlg == NID_seedCFB || \
                encAlg == NID_rc2CBC || \
                encAlg == NID_rc5_CBC_PAD || \
                encAlg == NID_des_EDE3_CBC || \
                encAlg == NID_desCBC || \
                encAlg == NID_pACA_CBC || \
                encAlg == NID_nEAT_CBC_p || \
                encAlg == NID_nEAT_CBC)

/** @ingroup CMS
    @brief ContentInfo를 암호화하여 EncryptedData를 생성한다.
    @param encData [out] EncryptedData의 포인터 변수의 포인터
    @param cInfo [in] 암호화 대상인 ContentInfo 인스턴스의 포인터
    @param encAlg [in]  암호화 알고리즘 Nid
    @param key [in] 대칭키 값이 저장된 바이트 버퍼의 포인터
    @param keyLen [in] 대칭키의 바이트 단위 길이
    @sa EncryptedData_GetContentInfo

    ContentInfo를 encAlg에 지시된 암호화 알고리즘으로 암호화하여
    EncryptedData를 생성, 설정하여 출력한다.

    EncryptedData는 함수 내부에서 메모리에 할당되므로, 사용이 끝난 시점에서
    반드시 ASN_Del을 사용하여 메모리를 해제하여야 한다.

    encAlg에는 EncryptedData_CheckAlg에 표시된 알고리즘 Nid를 사용할 수 있다.

*/
LIBSPEC_SP
ERT EncryptedData_Gen( EncryptedData **encData,
                       ContentInfo    *cInfo,
                       Nid             encAlg,
                       BYTE           *key,
                       BWT             keyLen);

LIBSPEC_SP
ERT EncryptedData_Gen2( EncryptedData **encData,
                        ContentInfo    *cInfo,
                        BCipherKey     *bcKey,
                        BCipherContext *bcCtx);

/** @ingroup CMS
    @brief EncryptedData를 복호화하여 ContentInfo를 출력한다.
    @param cInfo [out] ContentInfo의 포인터 변수의 포인터
    @param encData [in] 복호화 대상인 EnvryptedData 인스턴스의 포인터
    @param key [in] 대칭키가 저장된 바이트 버퍼의 포인터
    @param keyLen [in] 대칭키의 바이트 단위 길이
    @sa EncryptedData_Gen

    EncryptedData를 입력받은 대칭키로 복호화하여 복호화 결과물인
    ContentInfo를 출력한다.

    ContentInfo는 함수 내부에서 메모리에 할당되므로, 사용이 끝난 시점에서
    반드시 ASN_Del을 사용하여 메모리를 해제하여야 한다.
*/
LIBSPEC_SP
ERT EncryptedData_GetContentInfo( ContentInfo   **cInfo,
                                  EncryptedData  *encData,
                                  BYTE           *key,
                                  BWT             keyLen);

LIBSPEC_SP
ERT EncryptedData_GetContentInfo2( ContentInfo   **cInfo,
                                   EncryptedData  *encData,
                                   BCipherKey     *bcKey);


/*****************************************************************************
 * EnvelopedData manipulating functions
 */

/** @ingroup CMS
    @brief ContentInfo를 hybrid 방식으로 암호화하여 EnvelopedData를 생성
    @param envData [out] EnvelopedData의 포인터 변수의 포인터
    @param cInfo [in] 암호화 대상인 ContentInfo 인스턴스의 포인터
    @param encAlg [in] 암호화 알고리즘 Nid
    @param numRecp [in] 수신자의 수
    @param recpCert [in] 수신자들의 Certificate
    @param domainParam [in] 수신자들의 도메인 파라미터
    @param hashAlg [in] 공개키 암호화에 사용될 해쉬 알고리즘들
    @sa EnvelopedData_GetContentInfo

    ContentInfo를 hybrid 방식으로 암호화하여 암호화 결과물인 EnvelopedData를
    생성, 설정하여 출력한다. hybrid 방식이란 평문을 대칭키로 암호화한 다음,
    그 대칭키를 다시 공개키 알고리즘으로 암호화하는 방식을 말한다. encAlg는
    바로 대칭키 알고리즘의 Nid이다. (EncryptedData_CheckAlg 참고)

    EnvelopedData는 암호문을 전달할 대상(수신자)을 복수개로 설정할 수 있는데,
    수신자의 수(numRecp)와 recpCert, domainParam, hashAlg를 배열로 받는
    이유가 그것이다. 수신자1은 recpCert[0], domainParam[0], hashAlg[0]를
    사용하여 암호화하며, 수신자2는 recpCert[1], domainParam[1], hashAlg[1]과
    같은 방식으로 파라미터가 사용된다.
    
    Certificate, Paramter에 대한 옵션 사항들은 CKM_Encrypt를 참고하기 바란다.
    
    EnvelopedData는 함수 내부에서 메모리에 할당되므로, 사용이 끝난 시점에서
    반드시 ASN_Del을 사용하여 메모리를 해제하여야 한다.
*/
LIBSPEC_SP
ERT EnvelopedData_Gen( EnvelopedData **envData,
                       ContentInfo    *cInfo,
                       Nid             encAlg,
                       BWT             numResp,
                       Certificate    *recpCert[],
                       Parameter      *domainParam[],
                       AlgDesc         hashAlg[]);

/** @ingroup CMS
    @brief ContentInfo를 hybrid 방식으로 암호화하여 EnvelopedData를 생성
    @param envData [out] EnvelopedData의 포인터 변수의 포인터
    @param skey [out] EnvelopedData를 만드는데에 사용한 대칭키
    @param skeylen [out] key의 길이(바이트 수)
    @param cInfo [in] 암호화 대상인 ContentInfo 인스턴스의 포인터
    @param encAlg [in] 암호화 알고리즘 Nid
    @param numRecp [in] 수신자의 수
    @param recpCert [in] 수신자들의 Certificate
    @param domainParam [in] 수신자들의 도메인 파라미터
    @param hashAlg [in] 공개키 암호화에 사용될 해쉬 알고리즘들
    @sa EnvelopedData_GetContentInfo

    ContentInfo를 hybrid 방식으로 암호화하여 암호화 결과물인 EnvelopedData를
    생성, 설정하여 출력한다. hybrid 방식이란 평문을 대칭키로 암호화한 다음,
    그 대칭키를 다시 공개키 알고리즘으로 암호화하는 방식을 말한다. encAlg는
    바로 대칭키 알고리즘의 Nid이다. (EncryptedData_CheckAlg 참고)

    EnvelopedData는 암호문을 전달할 대상(수신자)을 복수개로 설정할 수 있는데,
    수신자의 수(numRecp)와 recpCert, domainParam, hashAlg를 배열로 받는
    이유가 그것이다. 수신자1은 recpCert[0], domainParam[0], hashAlg[0]를
    사용하여 암호화하며, 수신자2는 recpCert[1], domainParam[1], hashAlg[1]과
    같은 방식으로 파라미터가 사용된다.
    
    Certificate, Paramter에 대한 옵션 사항들은 CKM_Encrypt를 참고하기 바란다.
    
    EnvelopedData는 함수 내부에서 메모리에 할당되므로, 사용이 끝난 시점에서
    반드시 ASN_Del을 사용하여 메모리를 해제하여야 한다.

    이 함수는 EnvelopedData_Gen함수와 동일하나 key를 내뱉어준다.
*/
LIBSPEC_SP
ERT EnvelopedData_GenOutputKey( EnvelopedData **envData,
                                BYTE           *skey,
                                BWT            *skeylen,
                                ContentInfo    *cInfo,
                                Nid             encAlg,
                                BWT             numResp,
                                Certificate    *recpCert[],
                                Parameter      *domainParam[],
                                AlgDesc         hashAlg[]);

/** @ingroup CMS
    @brief EnvelopedData를 복호화하여 ContentInfo를 출력
    @param cInfo [out] ContentInfo의 포인터 변수의 포인터
    @param recpPriInfo [in] 수신자의 PrivateKeyInfo
    @param recpCert [in] 수신자의 Certificate
    @param domainParam [in] 수신자의 도메인 파라미터
    @sa EnvelopedData_Gen

    수신자의 비공개키(recpPriInfo), Certificate, 도메인 파라미터(domainParam)을
    입력받아 EnvelopedData 내의 수신자중 일치하는 수신자가 있을 경우, 복호화
    하여 복호화 결과물인 ContentInfo를 생성하여 출력한다.
    PrivateKeyInfo, Certificate, Parameter 에 대한 옵션 사항들은 CKM_Decrypt를
    참고하기 바란다.
    
    ContentInfo는 함수 내부에서 메모리에 할당되므로, 사용이 끝난 시점에서
    반드시 ASN_Del을 사용하여 메모리를 해제하여야 한다.
*/
LIBSPEC_SP
ERT EnvelopedData_GetContentInfo( ContentInfo   **cInfo,
                                  EnvelopedData  *envData,
                                  PrivateKeyInfo *recpPriInfo,
                                  Certificate    *recpCert,
                                  Parameter      *domainParam);


LIBSPEC_SP
ERT GetKeyFromRecipientInfo( BYTE           *key,
                             BWT            *keyLen,
                             RecipientInfo  *recpInfo,
                             PrivateKeyInfo *recpPriInfo,
                             Certificate    *recpCert,
                             Parameter      *domainParam);

LIBSPEC_SP
RecipientInfo* GetRecipientInfoFromEnvelopedData( EnvelopedData  *envData,
                                                  Certificate    *recpCert);

/******************************************************************************
 * SignedData manipulating functions
 */

/** @ingroup CMS
    @brief SignedData를 생성한다.
    @param signedData [out]
    @param cInfo [in] 서명 대상인 ContentInfo 인스턴스의 포인터
    @param signerPriInfo [in] 서명자의 PrivateKeyInfo
    @param signerCert [in] 서명자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param hashAlg [in] 서명시 사용될 해쉬 알고리즘 descriptor
    @param signTime [in] 서명 생성시 시각
    @param caCerts [in] CA 들의 인증서들(검증 체인 혹은 기타 인증서)
    @param crls [in] CRL
    @sa SignedData_AddSignerInfo

    SignedData는 서명된 데이터를 의미하는 것으로 PKCS.7 에 기술되어 있는
    ASN.1 타입이다. SignedData는 복수개의 서명을 포함할 수 있다.

    이 함수는 SignedData를 기본적으로 하나의 서명을 포함하는 SignedData를
    생성한다. 서명에 필요한 입력으로는 서명 대상 메시지인 ContentInfo,
    서명 알고리즘에 필요한 비공개키(signerPriInfo), 인증서(Certificate),
    도메인 파라미터(domainParam), 해쉬 알고리즘(hashAlg) 가 있다.
    PrivateKeyInfo, Certificate, Parameter에 대한 옵션 정보는 CKM_Sign을
    참고하기 바란다. 그외, signTime, caCerts, crls를 옵션으로 하여, NULL일
    경우는 해당 정보를 포함하지 않는다.

    만약, 하나 이상의 SignerInfo를 추가하고 싶을 경우에는 별도로
    SignedData_AddSign을 사용하여 추가할 수 있다. 주의할 점은 추가 대상이 되는
    SignedData는 반드시 SignedData_Gen을 거친 후여야 한다.

    또한, SignedData는 SignerInfo를 하나도 포함하지 않고, 단지 Certificate들과
    CRL을 전달하기 위한 수단으로도 사용할 수 있다. 이 경우에는,
    signerPriInfo, signerCert, domainParam, hashAlg, signTime을 NULL 값으로
    설정하면 된다.

    생성된 SignedData는 함수 내부에서 메모리에 할당되므로, 사용이 끝난
    시점에서 반드시 ASN_Del을 사용하여 메모리를 해제하기 바란다.

    NOTE: signerPriInfo를 NULL로 주면 서명값을 가지지 않는 SignedData를
    그냥 생성한다.  ISSAC-SDK의 SG_VerifyCore() 함수 등에서 활용 가능하다.
*/
LIBSPEC_SP
ERT SignedData_Gen( 
               SignedData    **signedData,
               ContentInfo    *cInfo,
               PrivateKeyInfo *signerPriInfo,
               Certificate    *signerCert, 
               Parameter      *domainParam,
               AlgDesc         hashAlg,
               struct tm      *signTime,
               Certificates   *caCerts,
               CertificateRevocationLists  *crls);

LIBSPEC_SP
ERT SignedData_GenWithSignature( 
               SignedData                   **signedData,
               ContentInfo                   *cInfo,
               Certificate                   *signerCert,
               PrivateKeyAlgorithmIdentifier *signAlg,
               ASNBuf                        *signBuf,
               AlgDesc                        hashAlg,
               Certificates                  *caCerts,
               CertificateRevocationLists    *crls);

LIBSPEC_SP
ERT SignedData_GenWithASN(
               SignedData    **signedData,
               Nid             contentType,
               ASN            *content,
               PrivateKeyInfo *signerPriInfo,
               Certificate    *signerCert, 
               Parameter      *domainParam,
               AlgDesc         hashAlg,
               struct tm      *signTime,
               Certificates   *caCerts,
               CertificateRevocationLists  *crls);

LIBSPEC_SP
ERT SignedData_GenWithContent(
               SignedData    **signedData,
               const char     *content,
               int             contentLen,
               PrivateKeyInfo *signerPriInfo,
               Certificate    *signerCert, 
               Parameter      *domainParam,
               AlgDesc         hashAlg,
               struct tm      *signTime,
               Certificates   *caCerts,
               CertificateRevocationLists  *crls);

LIBSPEC_SP
ERT SignedData_GenWithContentAndSignature(
               SignedData                   **signedData,
               const char                    *content,
               int                            contentLen,
               Certificate                   *signerCert,
               PrivateKeyAlgorithmIdentifier *signAlg,
               ASNBuf                        *signBuf,
               AlgDesc                        hashAlg,
               Certificates                  *caCerts,
               CertificateRevocationLists    *crls);


/** @ingroup CMS
    @brief SignedData에 SignerInfo를 추가한다.
    @param signedData [out] 서명을 추가할 대상인 SignedData의 포인터
    @param signerPriInfo [in] 서명자의 PrivateSignInfo
    @param signerCert [in] 서명자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param hashAlg [in] 서명시 사용할 해쉬 알고리즘
    @param signTime [in] 서명 생성시 시각
    @sa SignedData_Gen

    SignedData에 서명을 하나 추가한다. 각 파라미터들은 SignedData_Gen의
    그것들과 동일하므로 SignedData_Gen을 참고하기 바란다.  주의할 점은
    여기서 signedData는 반드시 SignedData_Gen을 통하여 하나이상의 서명을
    가지고 있는 것이어야 한다.
*/
LIBSPEC_SP
ERT SignedData_AddSign( SignedData     *signedData,
                        PrivateKeyInfo *signerPriInfo,
                        Certificate    *signerCert,
                        Parameter      *domainParam,
                        AlgDesc         hashAlg,
                        struct tm      *signTime);

/** @ingroup CMS
    @brief SignedData에서 인증서들을 가져온다.
    @param certs [out] Certificates의 포인터 변수의 포인터
    @param signedData [in] SignedData 인스턴스의 포인터
    @sa SignedData_GetCRLs

    SignedData에 포함되어 있는 인증서들을 Certificates 타입에 설정하여
    출력한다. SignedData에 포함되는 인증서 형식으로 ExtendedCertificate도
    있으나, 이 함수에서는 ExtendedCertificate 내부의 Certificate 타입만을
    가져온다.

    Certificates는 사용이 끝나는 시점에서 ASN_Del을 사용하여 메모리를
    해제하여야 한다.
*/
LIBSPEC_SP
ERT SignedData_GetCertificates( Certificates **certs,
                                SignedData    *signedData);

/** @ingroup CMS
    @brief SignedData에서 CRL들을 가져온다.
    @param crls [out] CRLs의 포이터의 포인터
    @param signedData [in] SignedData 인스턴스의 포인터
    @sa SignedData_GetCertificates

    SignedData에 포함되어 있는 CRL들ㅇ르 CertificateRevocationLists 타입에
    설정하여 출력한다.
    
    CertificateRevocationLists 는 사용이 끝나는 시점에서 ASN_Del을
    사용하여 메모리를 해제하여야 한다.
*/
LIBSPEC_SP
ERT SignedData_GetCRLs( CertificateRevocationLists **crls,
                        SignedData                  *signedData);

/** @ingroup CMS
    @brief SignedData가 가지고 있는 서명의 수를 리턴한다.
    @param signedData [in] SignedData 인스턴스의 포인터
    @ret 서명의 수, 없을 경우 0을 리턴
    @sa SignedData_GetIssuerAndSerialNumber SignedData_VerifySign SignedData_GetContentInfo

    SignedData내의 서명 수를 리턴한다. 만약, 서명의 갯수가 5 라면,
    SignerInfo는 0, 1, 2, 3, 4 로 인덱싱 될 수 있으며 , 이 값은 
    SignedData_VerifySign 혹은 SignedData_GetIssuerAndSerialNumber에서
    입력값으로 사용할 수 있다.
*/
LIBSPEC_SP
int SignedData_GetNumSignerInfo( SignedData *signedData);

/** @ingroup CMS
    @brief issuer와 serial number를 가져온다.
    @param issuer [out] Name 포인터 변수의 포인터
    @param serialNumber [out] CertificateSerialNumber 포인터 변수의 포인터
    @param signedData [in] SignedData 인스턴스의 포인터
    @param signerIndex [in] SignerInfo의 index(Signer_GetNumSignerInfo 참고)
    @sa SignedData_GetNumSignerInfo SignedData_VerifySign SignedData_GetContentInfo

    SignedData 내부에 포함된 SignerInfo들은 기본적으로 서명자의 공개키 인증서의
    issuer와 serial number로 구분된다. signerIndex가 가리키는 인덱스의
    SignerInfo의 issuer와 serial number 값을 가져온다.

    issuer와 serialNumber 는 사용이 끝나는 시점에서 ASN_Del을
    사용하여 메모리를 해제하여야 한다.
*/
LIBSPEC_SP
ERT SignedData_GetIssuerAndSerialNumber( Name                    **issuer,
                                         CertificateSerialNumber **serialNumber,
                                         SignedData               *signedData,
                                         int                       signerIndex);
/** @ingroup CMS
    @brief SignedData 내의 SignerInfo를 검증한다.
    @param signedData [in] SignedData 인스턴스의 포인터
    @param signerCert [in] 서명자의 인증서
    @param domainParam [in] 도메인 파라미터
    @param signerIndex [in] SignerInfo의 index(Signer_GetNumSignerInfo 참고)
    @retval SUCCESS 검증 성공
    @retval FAIL 검증 실패
    @retval CMS_SIGNED_DATA_CANNOT_FIND_SIGNER_INFO 검증에 필요한 서명정보가 없음
    @sa SignedData_GetNumSignerInfo SignedData_GetIssuerAndSerialNumber SignedData_GetContentInfo


    서명에 대한 검증은 두 가지로 나눌 프로세스로 나뉜다.

    첫째, 검증과정 : Signer가 예측되고, Cert를 가지고 있을 경우 
    - Cert를 명시적으로 Verify 함수에 넘겨줌. 
    - 넘겨받은 Cert로 해당 signerInfo를 검색하여 검증 
         
    두번째 검증과정 : Signer를 모르지만, 검증을 하고 싶을 경우. 
    - GetNumSignerInfo 로 SignedData 내의 SignerInfo의 수를 구한다. 
    - GetIssuerAndSerialNumber에 signer의 index값을 주어
      signer의 Cert 정보를 얻는다. 
    - 검증해보고 싶은 signer를 찾을 때까지 index를 증가시켜 signer의 
      Cert정보를 얻는다.
    - 검증을 원하는 signer와 일치하면, Verify에 그 index값을 주어 검증한다. 
      (이 경우 signer의 인증서를 명시적으로 줄 수도 있으며, 만약 명시적으로
      주지 않으면 SignedData 내부에서 인증서를 검색하여 검증을 시도할 것이다.
*/
LIBSPEC_SP
ERT SignedData_VerifySign( SignedData              *signedData,
                           Certificate             *signerCert,
                           Parameter               *domainParam,
                           int                      signerIndex);

LIBSPEC_SP
ERT _SignedDataWithoutContent_VerifySign( SignedData              *signedData,
										  Certificate             *signerCert,
										  Parameter               *domainParam,
										  int                      signerIndex,
										  char                    *content,
										  int                      content_len );

LIBSPEC_SP
ERT SignedDataWithoutContent_VerifySign( Pkcs7                   *pkcs7,
										 Certificate             *signerCert,
										 Parameter               *domainParam,
										 int                      signerIndex,
										 char                    *content,
										 int                      content_len );

LIBSPEC_SP
ERT SignedDataWithoutContent_Gen( Pkcs7         			**pkcs7,
								  char           			 *content,
								  int             			  content_len,
								  PrivateKeyInfo 			 *signerPriInfo,
								  Certificate    			 *signerCert,
								  Parameter      			 *domainParam,
								  AlgDesc         			  hashAlg,
								  struct tm      			 *signTime,
								  Certificates   			 *caCerts,
								  CertificateRevocationLists *crls );

/** @ingroup CMS
    @brief SignedData 에서 서명되었던 본래 메시지를 가져온다.
    @param content [out] 본래 메시지의 내용이 저장된 메모리
    @param contentLen [out] 본래 메시지의 길이
    @param signedData [in] SignedData 인스턴스의 포인터
    @sa SignedData_GetNumSignerInfo SignedData_GetIssuerAndSerialNumber SignedData_VerifySign

    SignedData로부터 서명 대상인 ContentInfo를 생성, 설정하여 출력한다.
    만약, ContentInfo가 없으면 cInfo에 NULL값이 설정된다.

    ContentInfo는 사용이 끝나는 시점에서 ASN_Del을
    사용하여 메모리를 해제하여야 한다.
*/
LIBSPEC_SP
ERT SignedData_GetContentInfo( ContentInfo **cInfo,
                               SignedData   *signedData);



/** @ingroup CMS
    @brief SignedData 형식으로 RootCA와 CA 인증서를 포함하는 인증서 집합체 생성
    @param signedData [out] SignedData 인스턴스의 포인터
    @param userCert [in] 사용자 인증서
    @param caCerts [in] CA 들의 인증서들(검증 체인 혹은 기타 인증서)
    @param crls [in] CRL
    @sa SignedData_Gen CERTS_WriteP7CFile

    SignedData 형식의 인증서 집합체를 생성한다.
    SignedData_Gen의 파라미터 값을 조정하여 생성하는 함수를 제작하는 방법도 있었으나,
    서명값이 존재하지 않는 SignedData 생성과의 혼동이 우려되어
    별도의 함수로 인터페이스를 제공한다.

    실제로 P7C 파일로 출력하기 위해서는 General Syntax에 맞추어서
    ContentInfo 형식으로 SignedData임을 알리는 OID와 함께 데이터를 넣어주어야 한다.
*/
LIBSPEC_SP
ERT SignedData_GenP7Certificate( SignedData   **signedData,
                                 Certificate   *signerCert, 
                                 Certificates  *caCerts,
                                 CertificateRevocationLists  *crls);

/** @ingroup CERT
    @brief SignedData 형식으로 인증서 집합체(P7C)를 General syntax로 가공하여 출력
    @param userCert [in] P7C 형식으로 전달하고자 하는 사용자 인증서
    @param caCerts [in] CA 들의 인증서들(검증 체인 혹은 기타 인증서)
    @param crls [in] CRL
    @param filePath[in] P7C 형식으로 가공하여 출력할 파일 경로
    @sa SignedData_GenP7Certificate CERT_WriteFile

    SignedData_GenP7Certificate() 함수를 이용하여 SignedData 형태로 가공한 후
    ContentInfo 형식에 SignedData 임을 나타내는 OID와 함께 데이터를 구성하여 출력한다.

    caCerts 값으로 NULL을 입력할 경우, 사용자 인증서만을 포함한 P7C 형식의 SignedData가
    출력된다.
    crls 값으로 NULL을 입력할 경우, CRL 정보는 포함되지 않는다.
*/
LIBSPEC_SP
ERT CERTS_WriteP7CFile(Certificate                 *userCert,
                       Certificates                *caCerts,
                       CertificateRevocationLists  *crls,
                       const char                  *filePath,
                       enum                         CERT_FILE_TYPE  flag);

#define CERTS_WriteP7CFileDER(cert, certs, crls, filePath) \
        CERTS_WriteP7CFile((cert), (certs), (crls), (filePath), CERT_DER)

#define CERTS_WriteP7CFilePEM(cert, certs, crls, filePath) \
        CERTS_WriteP7CFile((cert), (certs), (crls), (filePath), CERT_PEM)




#ifdef __cplusplus
}
#endif

#endif /* _CMS_H_ */
