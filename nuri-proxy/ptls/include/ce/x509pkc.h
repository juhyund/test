#ifndef _X509PKC_H_
#define _X509PKC_H_

#include "asn1.h"
#include "x509com.h"

/** @ingroup X509
    @file x509pkc.h
    @brief X509 모듈 중에서 공개키 인증서와 관련된 데이터 형과 함수 정의

    X509 모듈 중에서 Certificate, CRL과 관련된 데이터 형을 정의한다.
    RFC2459에서 제시하는 ASN.1 표준 규격을 따른다.
  */

/** @addtogroup X509
 * @{ */
#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
  
                    Basic Certificate Fields (RFC 2459 - 4.1)

******************************************************************************/


/******************************************************************************
 * Time
 */

typedef struct _Time {
  ASNChoiceClass klass;
  int            select;  
  union {
    UTCTime         *utcTime;
    GeneralizedTime *generalTime;
  } choice;
} Time;

LIBSPEC_CKM
extern ASNDescriptor AD_Time; 

/* select가 1이면 UTCTime으로 셋하고 2(또는 0)이면 GenTime으로 셋한다.*/
LIBSPEC_CKM
Time *Time_New(struct tm *input, int select);

/* 기본적으로 GeneralizedTime으로 셋팅 */
LIBSPEC_CKM
ERT Time_Set(Time *ti, struct tm *input);

/* GenTime과 UTCTime은 동일 */
#define Time_Get(out, t) \
        ((t)->select ? ASNGenTime_Get(out, (t)->choice.generalTime) : 0)

LIBSPEC_CKM
ERT Time_Sprint(char *str, int str_maxlen, Time *ti);

/* 2005 07 ... hrcho... 
   format is composed of "YYYYMMDD hhmmss" */
LIBSPEC_CKM
ERT 
Time_SprintByFormat(
        char *str, 
        int str_maxlen, 
        Time *ti, 
        const char *format
        );

/******************************************************************************
 * Validity
 */

typedef struct _Validity {
  ASNSeqClass klass;
  Time        *notBefore;
  Time        *notAfter;
} Validity;  

LIBSPEC_CKM
extern ASNDescriptor AD_Validity; 

#define Validity_Set(valid, not_before, not_after) \
        { Time_Set(valid->notBefore, not_before); \
          Time_Set(valid->notAfter, not_after); }

#define Validity_Get(not_before, not_after, valid) \
        { Time_Get(not_before, (valid)->notBefore); \
          Time_Get(not_after, (valid)->notAfter); }

/* start 가 0 이면 현재가 된다. */
LIBSPEC_CKM
int Validity_SetByPeriod(Validity *valid, 
                         struct tm *start, 
                         int year, 
                         int month, 
                         int day);


/******************************************************************************
 * TBSCertificate
 */

typedef struct _TBSCertificate {
  ASNSeqClass klass;
  Version                 *version;
  CertificateSerialNumber *serialNumber;
  AlgorithmIdentifier     *signature;
  Name                    *issuer;
  Validity                *validity;
  Name                    *subject;
  SubjectPublicKeyInfo    *subjectPublicKeyInfo;
  UniqueIdentifier        *issuerUniqueId; /* optional */
  UniqueIdentifier        *subjectUniqueId; /* optional */
  Extensions              *extensions; /* optional */
} TBSCertificate;  

LIBSPEC_CKM
extern ASNDescriptor AD_TBSCertificate;   


/******************************************************************************
 * Certificate
 */

typedef struct _Certificate {
  ASNSeqClass klass;
  TBSCertificate      *tbsCertificate;
  AlgorithmIdentifier *signatureAlgorithm;
  BitString           *signatureValue;
} Certificate;

LIBSPEC_CKM
extern ASNDescriptor AD_Certificate; 

typedef Certificate CERT;
#define AD_CERT AD_Certificate

/******************************************************************************
 * Sequence of Certificate
 */
typedef struct _SeqOfCertificate {
  ASNSeqOfClass klass;
  int           size;
  Certificate **member;
} SeqOfCertificate;

typedef SeqOfCertificate Certificates;
typedef SeqOfCertificate CERTS;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfCertificate;

#define AD_Certificates AD_SeqOfCertificate
#define AD_CERTS        AD_SeqOfCertificate

#define CERTS_Add(certs, cert) ASNSeqOf_Add(ASN_SEQOF(certs), ASN(cert))
#define CERTS_AddP(certs, cert) ASNSeqOf_AddP(ASN_SEQOF(certs), ASN(cert))


/******************************************************************************
  
                   Standard Extensions (RFC 2459 - 4.2.1)

******************************************************************************/


/******************************************************************************
 * Authority Key Identifier
 */

/** @ingroup X509
    @typedef KeyIdentifier
    @brief 공개키를 쉽게 구분할 수 있는 키 식별자

    KeyIdentifier는 주로 복수 개의 공개키 중에서 원하는 하나의
    공개키를 쉽게 구별하기 위해 사용한다.
  */
typedef OctetString KeyIdentifier;
#define AD_KeyIdentifier AD_OctetString 

#define KeyId_Set(keyId, in, len)   ASNOctStr_Set(keyId, in, len)
#define KeyId_Get(out, mlen, keyId) ASNOctStr_Get(out, mlen, keyId)

/** @ingroup X509 
    @brief 공개키로부터 키 식별자를 만들어 낸다.

    공개키로부터 KeyIdentifer를 계산해내는 방법 중의 하나를 제공한다.
    인증서에 포함되는 공개키 정보인 SubjectPublicKeyInfo의 
    subjcetPublicKey로부터 이것의 ASN.1 tag와 length, 그리고 unused bits를
    제외한 데이터 영역만을 SHA1을 이용하여 해쉬한 결과값 160bits를 출력한다.
*/
LIBSPEC_CKM
KeyIdentifier *KeyIdentifier_Gen(ASNBitStr *subjectPubKey);

/** @ingroup X509 
    @def KeyIdentifier_Compare
    @brief 키 식별자를 비교한다.
    @return kid1이 kid2보다 큰 경우 양수를, 같으면 0을, 작으면 음수

    키 식별자 kid1과 kid2를 비교한 결과를 출력한다.

    @sa ASNOctStr_Cmp ASNStr_Cmp
*/
#define KeyIdentifier_Compare(a, b) ASNOctStr_Cmp((a), (b))


typedef struct _AuthorityKeyIdentifier {
  ASNSeqClass klass;
  KeyIdentifier           *keyIdentifier; /* optional */
  GeneralNames            *authorityCertIssuer; /* optional */
  CertificateSerialNumber *authorityCertSerialNumber; /* optional */
} AuthorityKeyIdentifier;

LIBSPEC_CKM
extern ASNDescriptor AD_AuthorityKeyIdentifier;


/*
  AuthorityKeyIdentifier_Set
  AuthorityKeyIdentifier_GetKeyIdentifier
  AuthorityKeyIdentifier_GetAuthorityCertSerialNumber
  AuthorityKeyIdentifier_Sprint

  to get authorityCertIssuer, use get method of GeneralNames type.
*/

LIBSPEC_CKM
int AuthorityKeyIdentifier_Set(
    AuthorityKeyIdentifier *target, const char *keyIdentifier, int keyIdLen,
    GeneralNames *authCertIssuer, const char *authCertSerialNumber, int snLen);

#define AuthorityKeyIdentifier_GetKeyIdentifier(out, mlen, authKeyId) \
  KeyId_Get(out, mlen, authKeyId->keyIdentifier)

#define AuthorityKeyIdentifier_GetAuthorityCertSerialNumber(out, mlen, authKeyId) \
  CertificateSerialNumber_Get(out, mlen, authKeyId->authorityCertSerialNumber)

LIBSPEC_CKM
int AuthorityKeyIdentifier_Sprint(char *content, int contentLen, AuthorityKeyIdentifier *aki);


/******************************************************************************
 * Subject Key Identifier
 */

typedef KeyIdentifier SubjectKeyIdentifier;
#define AD_SubjectKeyIdentifier AD_KeyIdentifier


#define SubjectKeyIdentifier_Set(keyId, in, len)   KeyId_Set(keyId, in, len)
#define SubjectKeyIdentifier_Get(out, mlen, keyId) KeyId_Get(out, mlen, keyId)


/******************************************************************************
 * Key Usage
 */

typedef BitString KeyUsage;
#define AD_KeyUsage AD_BitString 

enum {
  KeyUsage_digitalSignature = 0x8000,
  KeyUsage_nonRepudiation   = 0x4000,
  KeyUsage_keyEncipherment  = 0x2000,
  KeyUsage_dataEncipherment = 0x1000,
  KeyUsage_keyAgreement     = 0x0800,
  KeyUsage_keyCertSign      = 0x0400,
  KeyUsage_cRLSign          = 0x0200,
  KeyUsage_encipherOnly     = 0x0100,
  KeyUsage_decipherOnly     = 0x0080,
};


LIBSPEC_CKM
int KeyUsage_Set(KeyUsage *ku, int input);

LIBSPEC_CKM
int KeyUsage_Get(KeyUsage *ku);

LIBSPEC_CKM
int KeyUsage_Sprint(char *content, int contentLen, KeyUsage *ku);


/******************************************************************************
 * Private Key Usage Period
 */

typedef struct _PrivateKeyUsagePeriod {
  ASNSeqClass klass;
  GeneralizedTime *notBefore; /* optional */
  GeneralizedTime *notAfter; /* optional */
} PrivateKeyUsagePeriod;

LIBSPEC_CKM
extern ASNDescriptor AD_PrivateKeyUsagePeriod;


LIBSPEC_CKM
int PrivateKeyUsagePeriod_Set(
    PrivateKeyUsagePeriod *target, struct tm *notBefore, struct tm *notAfter);

LIBSPEC_CKM
int PrivateKeyUsagePeriod_GetNotBefore(
    struct tm *notBefore, PrivateKeyUsagePeriod *source);

LIBSPEC_CKM
int PrivateKeyUsagePeriod_GetNotAfter(
    struct tm *notAfter, PrivateKeyUsagePeriod *source);

LIBSPEC_CKM
int PrivateKeyUsagePeriod_Sprint(
    char *content, int contentLen, PrivateKeyUsagePeriod *keyPeriod);


/******************************************************************************
 * Certificate Policy
 */

enum {
  DisplayText_visibleString = 1,
  DisplayText_bmpString,
  DisplayText_utf8String
};

typedef struct _DisplayText {
  ASNChoiceClass klass;
  int            select;
  union {
    VisibleString *visibleString;
    BMPString     *bmpString;
    UTF8String    *utf8String;
  } choice;
} DisplayText;

LIBSPEC_CKM
extern ASNDescriptor AD_DisplayText;


typedef struct _SeqOfInteger {
  ASNSeqOfClass klass;
  int           size;
  Integer     **member;
} SeqOfInteger;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfInteger;


typedef struct _NoticeReference {
  ASNSeqClass klass;
  DisplayText  *organization;
  SeqOfInteger *noticeNumbers;
} NoticeReference;

LIBSPEC_CKM
extern ASNDescriptor AD_NoticeReference;


typedef struct _UserNotice {
  ASNSeqClass klass;
  NoticeReference *noticeRef; /* optional */ 
  DisplayText     *explicitText; /* optional */
} UserNotice;

LIBSPEC_CKM
extern ASNDescriptor AD_UserNotice;


typedef IA5String CPSuri;
#define AD_CPSuri AD_IA5String


enum {
  Qualifier_cPSuri = 1,
  Qualifier_userNotice
};

typedef struct _Qualifier {
  ASNChoiceClass klass;
  int             select;
  union {
    CPSuri       *cPSuri;
    UserNotice   *userNotice;
  } choice;
} Qualifier;

LIBSPEC_CKM
extern ASNDescriptor AD_Qualifier;


typedef ASNOid PolicyQualifierId;
#define AD_PolicyQualifierId AD_Oid


typedef struct _PolicyQualifierInfo {
  ASNSeqClass klass;
  PolicyQualifierId *policyQualifierId;
  Any               *qualifier;
} PolicyQualifierInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PolicyQualifierInfo;

typedef struct _SeqOfPolicyQualifierInfo {
  ASNSeqOfClass klass;
  int                   size;
  PolicyQualifierInfo **member;
} SeqOfPolicyQualifierInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfPolicyQualifierInfo;

typedef ASNOid CertPolicyId;
#define AD_CertPolicyId AD_Oid

typedef struct _SeqOfCertPolicyId {
  ASNSeqOfClass   klass;
  int             size;
  CertPolicyId  **member;
} SeqOfCertPolicyId;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfCertPolicyId;



typedef struct _PolicyInformation {
  ASNSeqClass klass;
  CertPolicyId             *policyIdentifier;
  SeqOfPolicyQualifierInfo *policyQualifiers; /* optional */ 
} PolicyInformation;

LIBSPEC_CKM
extern ASNDescriptor AD_PolicyInformation;


typedef struct _CertificatePolicies {
  ASNSeqOfClass klass;
  int                 size;
  PolicyInformation **member;
} CertificatePolicies;

LIBSPEC_CKM
extern ASNDescriptor AD_CertificatePolicies;

LIBSPEC_CKM
int CertificatePolicies_Sprint(char *content, int contentLen, CertificatePolicies *cps);

LIBSPEC_CKM
int DisplayText_Set(DisplayText *target, int choice, const char *in, int len);

LIBSPEC_CKM
int DisplayText_Get(char *out, int maxLen, DisplayText *source);

LIBSPEC_CKM
int Qualifier_SetCPSuri(Qualifier *target, const char *uri, int uriLen);

LIBSPEC_CKM
int Qualifier_GetCPSuri(char *uri, int maxLen, Qualifier *source);

LIBSPEC_CKM
int Qualifier_SetUserNotice_noticeRef(
    Qualifier *target,
    int choice, const char *noticeRef_organization, int len,
    int numOfNoticeNum, ...);

LIBSPEC_CKM
int Qualifier_SetUserNotice_explicitText(
    Qualifier *target, int choice, const char *explicitText, int len);

LIBSPEC_CKM
int PolicyInformation_SetCertPolicyId(
    PolicyInformation *target, Oid *certPolicyId);

LIBSPEC_CKM
int PolicyInformation_AddPolicyQualifier(
    PolicyInformation *target, Oid *policyQualifierId, ASNBuf *qualifier);

LIBSPEC_CKM
int CertificatePolicies_AddPolicyInformation(
    CertificatePolicies *target, PolicyInformation *policyInfo);


/******************************************************************************
 * Policy Mappings
 */

typedef struct _PolicyMapping {
  ASNSeqClass klass;
  CertPolicyId *issuerDomainPolicy;
  CertPolicyId *subjectDomainPolicy;
} PolicyMapping;

LIBSPEC_CKM
extern ASNDescriptor AD_PolicyMapping;


typedef struct _PolicyMappings {
  ASNSeqOfClass klass;
  int             size;
  PolicyMapping **member;
} PolicyMappings;

LIBSPEC_CKM
extern ASNDescriptor AD_PolicyMappings;


LIBSPEC_CKM
int PolicyMapping_Set(
    PolicyMapping *target, Oid *issuerDomainPolicy, Oid *subjectDomainPolicy);

LIBSPEC_CKM
int PolicyMapping_Get(
    Oid *issuerDomainPolicy, Oid *subjectDomainPolicy, PolicyMapping *source);

LIBSPEC_CKM
int PolicyMappings_Add(
    PolicyMappings *target, PolicyMapping *policyMapping);

LIBSPEC_CKM
int PolicyMappings_Sprint(
    char *content, int contentLen, PolicyMappings *pm);


/******************************************************************************
 * Subject Alternative Name
 */

typedef GeneralNames SubjectAltName;
#define AD_SubjectAltName AD_GeneralNames

/* use functions of GeneralNames type */


/******************************************************************************
 * Issuer Alternative Name
 */

typedef GeneralNames IssuerAltName;
#define AD_IssuerAltName AD_GeneralNames

/* use functions of GeneralNames type */


/******************************************************************************
 * Subject Directory Attributes
 */

typedef struct _SubjectDirectoryAttributes {
  ASNSeqOfClass klass;
  int             size;
  Attribute     **member;
} SubjectDirectoryAttributes;

LIBSPEC_CKM
extern ASNDescriptor AD_SubjectDirectoryAttributes;


/******************************************************************************
 * Basic Constraints
 */

typedef struct _BasicConstraints {
  ASNSeqClass klass;
  Boolean     *cA;                /**< default : false */
  Integer     *pathLenConstraint; /**< optional */
} BasicConstraints;

LIBSPEC_CKM
extern ASNDescriptor AD_BasicConstraints;

/*!
 * \brief BasicConstraints의 내용을 설정
 *
 * \param target [out] 설정할 BasicConstraints
 * \param isCa [in] CA 인증서인지의 여부. 1이면 CA/0이면 CA가 아님.
 * \param pathLen [in] 인증경로의 허용 길이. isCa가 1일때만 의미가 있음.
 *                     -1이면 무한.
 *
 * \return int 성공 여부. SUCCESS or FAIL
 */
LIBSPEC_CKM
int BasicConstraints_Set(BasicConstraints *target, int isCa, int pathLen);

LIBSPEC_CKM
int BasicConstraints_Sprint(
    char *content, int max_content, BasicConstraints *bc);


/******************************************************************************
 * Name Constraints
 */

typedef Integer BaseDistance;
#define AD_BaseDistance AD_Integer


typedef struct _GeneralSubtree {
  ASNSeqClass klass;
  GeneralName  *base;
  BaseDistance *minimum;
  BaseDistance *maximum; /* optional */
} GeneralSubtree;

LIBSPEC_CKM
extern ASNDescriptor AD_GeneralSubtree;


typedef struct _GeneralSubtrees {
  ASNSeqOfClass klass;
  int              size;
  GeneralSubtree **member;
} GeneralSubtrees;

LIBSPEC_CKM
extern ASNDescriptor AD_GeneralSubtrees;

LIBSPEC_CKM
int GeneralSubtrees_Sprint(char *content, int max_len, GeneralSubtrees *gss);


typedef struct _NameConstraints {
  ASNSeqClass klass;
  GeneralSubtrees *permittedSubtrees; /* optional */
  GeneralSubtrees *excludedSubtrees; /* optional */
} NameConstraints;

LIBSPEC_CKM
extern ASNDescriptor AD_NameConstraints;


LIBSPEC_CKM
extern int GeneralSubtree_Set(
    GeneralSubtree *target, GeneralName *generalName, int min, int max);

LIBSPEC_CKM
extern int GeneralSubtrees_Add(
    GeneralSubtrees *target, GeneralSubtree *generalSubtree);

LIBSPEC_CKM
extern int NameConstraints_Set(
    NameConstraints *target, 
    GeneralSubtrees *permitted, GeneralSubtrees *excluded);


/******************************************************************************
 * Policy Constraints
 */

typedef Integer SkipCerts;
#define AD_SkipCerts AD_Integer

typedef struct _PolicyConstraints {
  ASNSeqClass klass;
  SkipCerts   *requireExplicitPolicy;
  SkipCerts   *inhibitPolicyMapping;
} PolicyConstraints;

LIBSPEC_CKM
extern ASNDescriptor AD_PolicyConstraints;

LIBSPEC_CKM
int PolicyConstraints_Sprint(char *content, int contentLen, PolicyConstraints *pc);


/******************************************************************************
 * Extended key usage field
 */

typedef ASNOid KeyPurposeId;
#define AD_KeyPurposeId AD_Oid

typedef struct _ExtKeyUsageSyntax {
  ASNSeqOfClass klass;
  int            size;
  KeyPurposeId **member;
} ExtKeyUsageSyntax;

LIBSPEC_CKM
extern ASNDescriptor AD_ExtKeyUsageSyntax;


/******************************************************************************
 * CRL Distribution Points 
 */

typedef BitString ReasonFlags;
#define AD_ReasonFlags AD_BitString

enum {
  ReasonFlags_unused               = 0x8000,
  ReasonFlags_keyCompromise        = 0x4000,
  ReasonFlags_cACompromise         = 0x2000,
  ReasonFlags_affiliationChanged   = 0x1000,
  ReasonFlags_superseded           = 0x0800,
  ReasonFlags_cessationOfOperation = 0x0400,
  ReasonFlags_certificateHold      = 0x0200,
  ReasonFlags_privilegeWithdrawn   = 0x0100,
  ReasonFlags_aACompromise         = 0x0080
};

LIBSPEC_CKM
int ReasonFlags_Set(ReasonFlags *rf, int input);

LIBSPEC_CKM
int ReasonFlags_Get(ReasonFlags *rf);

LIBSPEC_CKM
int ReasonFlags_Sprint(char *content, int contentLen, ReasonFlags *rf);

enum {
  DistributionPointName_fullName = 1,
  DistributionPointName_nameRelativeToCRLIssuer
};

typedef struct _DistributionPointName {
  ASNChoiceClass klass;
  int                          select;
  union {
    GeneralNames              *fullName;
    RelativeDistinguishedName *nameRelativeToCRLIssuer;
  } choice;
} DistributionPointName;

LIBSPEC_CKM
extern ASNDescriptor AD_DistributionPointName;

typedef struct _DistributionPoint {
  ASNSeqClass klass;
  DistributionPointName *distributionPoint;
  ReasonFlags           *reasons;
  GeneralNames          *cRLIssuer;
} DistributionPoint;

LIBSPEC_CKM
extern ASNDescriptor AD_DistributionPoint;

typedef struct _CRLDistPointsSyntax {
  ASNSeqOfClass klass;
  int                 size;
  DistributionPoint **member;
} CRLDistPointsSyntax;

LIBSPEC_CKM
extern ASNDescriptor AD_CRLDistPointsSyntax;

typedef CRLDistPointsSyntax CRLDistributionPoints;
#define  AD_CRLDistributionPoints AD_CRLDistPointsSyntax

LIBSPEC_CKM
int DistributionPointName_SetGeneralNames(
		DistributionPointName *target, GeneralNames *fullName);


LIBSPEC_CKM
int DistributionPoint_Set(
    DistributionPoint *target, DistributionPointName *distributionPoint,
    ReasonFlags *reasons, GeneralNames *cRLIssuer);


LIBSPEC_CKM
int CRLDistributionPoints_AddDistributionPoint(
		CRLDistributionPoints *target, DistributionPoint *dp);


LIBSPEC_CKM
int CRLDistributionPoints_Sprint(
    char *content, int contentLen, CRLDistributionPoints *cdp);


/******************************************************************************
 * Inhibit Any-Policy (new in RFC3280)
 */

typedef SkipCerts InhibitAnyPolicy;
#define AD_InhibitAnyPolicy AD_SkipCerts


/******************************************************************************
 * FreshestCRL (new in RFC3280)
 */

typedef CRLDistributionPoints FreshestCRL;
#define AD_FreshestCRL AD_CRLDistributionPoints


/******************************************************************************
  
                 Private Internet Extensions (RFC 2459 - 4.2.2)

******************************************************************************/


/******************************************************************************
 * Authority Information Access
 */

typedef struct _AccessDescription {
  ASNSeqClass klass;
  ASNOid      *accessMethod;
  GeneralName *accessLocation;
} AccessDescription;

LIBSPEC_CKM
extern ASNDescriptor AD_AccessDescription;

typedef struct _AuthorityInfoAccessSyntax {
  ASNSeqOfClass klass;
  int                 size;
  AccessDescription **member;
} AuthorityInfoAccessSyntax;

LIBSPEC_CKM
extern ASNDescriptor AD_AuthorityInfoAccessSyntax;

LIBSPEC_CKM
int AuthorityInfoAccessSyntax_Sprint(
    char *content, int contentLen, AuthorityInfoAccessSyntax *aias);

/******************************************************************************
 * SubjectInfoAccessSyntax (new in RFC3280)
 */

typedef AuthorityInfoAccessSyntax SubjectInfoAccessSyntax;
#define AD_SubjectInfoAccessSyntax AD_AuthorityInfoAccessSyntax


/******************************************************************************
  
                         CRL Fields (RFC 2459 - 5.1)

******************************************************************************/


/******************************************************************************
 * TBSCertList
 */

typedef struct _RevokedCertificate {
  ASNSeqClass klass;
  CertificateSerialNumber *userCertificate;
  Time                    *revocationDate;
  Extensions              *crlEntryExtensions;  /* optional */
} RevokedCertificate;

LIBSPEC_CKM
extern ASNDescriptor AD_RevokedCertificate;

LIBSPEC_CKM
extern RevokedCertificate* RevokedCertificate_New(
        CertificateSerialNumber *serialNumber,
        time_t revocationTime,
        int reasonFlags,
        Extensions *exts);


typedef struct _RevokedCertificates {
  ASNSeqOfClass klass;
  int           size;
  RevokedCertificate **member;
} RevokedCertificates;

LIBSPEC_CKM
extern ASNDescriptor AD_RevokedCertificates;

typedef struct _TBSCertList {
  ASNSeqClass klass;
  Version             *version;       /* optional */
  AlgorithmIdentifier *signature;   
  Name                *issuer;
  Time                *thisUpdate;
  Time                *nextUpdate;    /* optional */
  ASNAny              *revokedCertificates;  /* optional */
/*RevokedCertificates *revokedCertificates;*/ /* optional */
  Extensions          *crlExtensions; /* optional [0] */
} TBSCertList;

LIBSPEC_CKM
extern ASNDescriptor AD_TBSCertList;


/******************************************************************************
 * CertificateList
 */

typedef struct _CertificateList {
  ASNSeqClass klass;
  TBSCertList         *tbsCertList;
  AlgorithmIdentifier *signatureAlgorithm;
  BitString           *signatureValue;
} CertificateList;

LIBSPEC_CKM
extern ASNDescriptor AD_CertificateList; 

typedef struct _SeqOfCertificateList {
  ASNSeqOfClass klass;
  int size;
  CertificateList **member;
} SeqOfCertificateList;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfCertificateList;
typedef CertificateList CRL;
#define AD_CRL          AD_CertificateList


/******************************************************************************
  
                      CRL Extensions (RFC 2459 - 5.2)

******************************************************************************/


/******************************************************************************
 * Authority Key Identifier
 * Same as authority key identifier in Certificate Standard Extenstions
 */


/******************************************************************************
 * Issuer Alternative Name
 * Same as authority key identifier in Certificate Standard Extenstions
 */


/******************************************************************************
 * CRL Number
 */

typedef Integer CRLNumber;
#define AD_CRLNumber AD_Integer


/******************************************************************************
 * Delta CRL Indicator
 */

typedef CRLNumber BaseCRLNumber;
#define AD_BaseCRLNumber AD_CRLNumber

typedef BaseCRLNumber DeltaCRLIndicator;
#define AD_DeltaCRLIndicator AD_BaseCRLNumber


/******************************************************************************
 * Issuing Distribution Point
 */

typedef struct _IssuingDistributionPoint {
  ASNSeqClass klass;
  DistributionPointName *distributionPoint;
  Boolean               *onlyContainsUserCerts;
  Boolean               *onlyContainsCACerts;
  ReasonFlags           *onlySomeReasons;
  Boolean               *indirectCRL;
} IssuingDistributionPoint;

LIBSPEC_CKM
extern ASNDescriptor AD_IssuingDistributionPoint;


/******************************************************************************
  
                   CRL Entry Extensions (RFC 2459 - 5.3)

******************************************************************************/


/******************************************************************************
 * Reason Code
 */
typedef Enumerate CRLReason;
#define AD_CRLReason AD_Enumerate

enum {
  CRLReason_unspecified          = 0,
  CRLReason_keyCompromise        = 1,
  CRLReason_cACompromise         = 2,
  CRLReason_affiliationChanged   = 3,
  CRLReason_superseded           = 4,
  CRLReason_cessationOfOperation = 5,
  CRLReason_certificateHold      = 6,
  CRLReason_removeFromCRL        = 8,
  CRLReason_privilegeWithdrawn   = 9,
  CRLReason_aACompromise         = 10
};

typedef CRLReason ReasonCode;
#define AD_ReasonCode AD_CRLReason 

LIBSPEC_CKM
int ReasonCode_Sprint(char *content, int max_content, ReasonCode *rc);


/******************************************************************************
 * Hold Instruction Code
 */

typedef ASNOid HoldInstructionCode;
#define AD_HoldInstructionCode AD_Oid


/******************************************************************************
 * Invalidity Date
 */

typedef GeneralizedTime InvalidityDate;
#define AD_InvalidityDate AD_GeneralizedTime


/******************************************************************************
 * Certificate Issuer
 */

typedef GeneralNames CertificateIssuer;
#define AD_CertificateIssuer AD_GeneralNames

/******************************************************************************
 * Penta Revocation Description
 *  폐지시 추가적인 정보를 보내기 위한 private extension
 *  호완성을 위해 타 회사 제품과 연동할 시에는 사용하면 안됩.
 */
typedef UTF8String PentaRevDescription;
#define AD_PentaRevDescription AD_UTF8String

/******************************************************************************
  
                               Miscelleneous

******************************************************************************/

LIBSPEC_CKM
ExtsPrintCtx* Extensions_NewPrintCtxInX509PKC(Extensions *exts);

LIBSPEC_CKM
void Extensions_DelPrintCtxInX509PKC(ExtsPrintCtx* print);

LIBSPEC_CKM
ERT Extension_SprintInX509PKC(
    char *name, int name_max, char *value, int value_max, Extension *ext);



#ifdef __cplusplus
}
#endif
/** @} */
        
#endif /* _X509PKC_H_ */
