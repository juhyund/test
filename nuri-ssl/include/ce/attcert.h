#ifndef _ATTCERT_H_
#define _ATTCERT_H_

#include "cert.h"
#include "x509ac.h"

/** @defgroup ATTRIBUTE_CERTIFICATE Attribute Certificate
 * @ingroup CKM
    @brief attribute certificate과 관련된 타입, 함수

    Sign, Verify 함수가 정의 되어 있고,
    Atribute Certificate의 쓰일 주요 attribute type들과 그것들을
    다룰 수 있는 함수들이 정의되어 있다. 
*/

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  ER_ATTCERT_ATTRIBUTETYPE_NOT_UNIQUE = ER_ATTCERT,
  ER_ATTCERT_SAME_ATTRIBUTETYPE,
  ER_ATTCERT_NO_ATTRIBUTE
} ATTCERT_ERRORS;

/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef ACContext
    @brief 속성 인증서에서 사용하는 Context 타입을 정의

    ACContext는 타입은 OctetString 으로 정의한다. 
    OctetString은 ASN 모듈에 정의되어 있으며,
    octet 단위의 문자열을 의미한다.
    ASN.1 type에서 문자열의 종류에는 여러 가지가 있으나, 향후의 유연성에
    비중을 두어 가장 일반적인 OctetString 으로 정의한다.
  */
typedef OctetString  ACContext; 
#define AD_ACContext AD_OctetString

/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef ACRuleIdentifier
    @brief  ACRule을 구분하는 Identifier 타입을 정의

    ACRuleIdentifier는 타입은 OctetString으로 정의되어 있다.
    OctetString에 대해서는 ACContext를 참조하기 바란다.
  */
typedef OctetString ACRuleIdentifier;
#define AD_ACRuleIdentifier AD_OctetString
  
/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef ACRule
    @brief 속성 인증서에서 사용하는 접근 제어 단위 ACRule 타입 정의

    ACRule은 사용자가 이용하고자 하는 서비스에 대한 Access Control의 
    단위이다.
  */
typedef struct _ACRule {
  ASNSeqClass       klass;
  ACRuleIdentifier *ruleId;
  ACContext        *ruleCtx;
} ACRule;

LIBSPEC_CKM
extern ASNDescriptor AD_ACRule;

typedef struct {
  ASNSeqOfClass   klass;
  int             size;
  ACRule        **member;
} ACRules;

LIBSPEC_CKM
extern ASNDescriptor AD_ACRules;

LIBSPEC_CKM
ERT ACRules_Add(ACRules *rules, void *id, int idLen, void *ctx, int ctxLen);


/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef ServiceIdentifier
    @brief  Service을 구분하는 Identifier 타입을 정의

    ServiceIdentifier는 타입은 OctetString으로 정의되어 있다.
    OctetString에 대해서는 AAIdentifier를 참조하기 바란다.
  */
typedef OctetString ServiceIdentifier;
#define AD_ServiceIdentifier AD_OctetString


/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef Permission
    @brief   서비스에 대한 사용 권한 정보 Permission 정의 
  */
typedef struct _Permission {
  ASNSeqClass        klass;
  ServiceIdentifier *serviceId;
  ACContext         *serviceCtx;
  ACRules           *rules;
} Permission;

LIBSPEC_CKM
extern ASNDescriptor AD_Permission;

typedef struct {
  ASNSeqOfClass   klass;
  int             size;
  Permission    **member;
} SeqOfPermission;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfPermission;

typedef struct {
  ASNSeqClass      klass;
  GeneralNames    *policyAuthority;  /* [0] OPTIONAL */
  SeqOfPermission *permissions;  
} Permissions;

LIBSPEC_CKM
extern ASNDescriptor AD_Permissions;

LIBSPEC_CKM
ERT Permissions_Add(Permissions *permissions, 
                    void *id, int idLen, void *ctx, int ctxLen,
                    ACRules *rules);

/*****************************************************************************
 * ATTCERT Setting
 */

LIBSPEC_CKM
ERT Holder_SetByName(Holder *holder, Name *name);

LIBSPEC_CKM
ERT Holder_SetByCertificate(Holder *holder, Certificate *cert);

/*
   RFC3281

   The roleName field MUST be present, and roleName MUST use the
   uniformResourceIdentifier CHOICE of the GeneralName.
*/
LIBSPEC_CKM
ERT Holder_SetByRoleName(Holder *holder, const char *roleName);

/*
   ACs conforming to RFC3281 MUST use the v2Form choice, which MUST
   contain one and only one GeneralName in the issuerName, which MUST
   contain a non-empty distinguished name in the directoryName field.
   This means that all AC issuers MUST have non-empty distinguished
   names.  ACs conforming to this profile MUST omit the
   baseCertificateID and objectDigestInfo fields.

   serialNumber가 NULL인 경우 내부적으로 생성(issuer, subject가 NULL이면 에러)

   AC issuers MUST force the serialNumber to be a positive integer.
   This removes a potential ambiguity in mapping between a
   string of octets and an integer value.
   AC users MUST be able to handle serialNumber values longer than 4 octets.  
   Conformant ACs MUST NOT contain serialNumber values longer than 20 octets.

   An AC MUST contain at least one attribute.  That is, the SEQUENCE OF
   Attributes MUST NOT be of zero length.
   따라서, attributes가 NULL이면 함수 내부에서 zero length의 SEQUENCE OF
   Attributes를 attCertInfo에 설정하지만, 
   그 상태에서 AC를 생성(ATTCERT_Gen 함수)하면 에러 발생.
   attributes 안에는 적어도 하나의 attribute는 들어 있어야 하므로,
   그러한 경우에는 AttributeCertificateInfo_AddAttribute를 이용하여
   Attribute 추가한 후에 AC 생성해야 한다.

   IssuerUniqueIdentifier MUST NOT be used unless it is also used in the AC issuer's
   PKC, in which case it MUST be used.
   Issuer Unique Identifier는 사용하지 않음.

   An AC that has no extensions conforms to RFC3281.
   Extensions를 사용하지 않을 경우 NULL 입력
*/
LIBSPEC_CKM
ERT AttributeCertificateInfo_Set(AttributeCertificateInfo *attCertInfo,
                                 Holder *holder,
                                 Name   *issuer,
                                 CertificateSerialNumber *serialNumber,
                                 struct tm               *notBefore,
                                 struct tm               *notAfter,
                                 SeqOfAttribute          *attributes,
                                 Extensions              *extensions);

/*
   For a given AC, each
   AttributeType OBJECT IDENTIFIER in the sequence MUST be unique.  That
   is, only one instance of each attribute can occur in a single AC, but
   each instance can be multi-valued.

   AttributeCertificateInfo의 attributes에 att를 추가하는 함수이다.
   동일한 type을 갖는 attribute가 존재해서는 안되는 원칙에 맞도록
   attCertInfo이 이 조건에 맞지 않는 경우 ER_ATTCERT_ATTRIBUTETYPE_NOT_UNIQUE를
   리턴한다.

   att의 type이 이미 attCertInfo의 attributes에 존재하는 경우 
   mode의 값에 따라 다음과 같이 처리한다.

   mode = "r" : 해당 type에 들어있는 attribute의 vales를 replace한다.
                SeqOf의 뒤에 추가되는 것이 아니라, 이미 존재하는 
                attribute의 위치에 들어가기 때문에
                기존의 attribute values를 수정하고자 하는 경우에도 사용할 수
                있다.
   mode = "a" : 해당 type에 들어있는 attribute의 vales에 att의 values를 추가한다.
   mode = 그외(NULL포함) : ER_ATTCERT_SAME_ATTRIBUTETYPE를 리턴.
*/
LIBSPEC_CKM
ERT AttributeCertificateInfo_AddAttribute(AttributeCertificateInfo *attCertInfo,
                                          Attribute                *att,
                                          const char               *mode);


/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   속성 인증서를 발급자가 비공개키로 서명
   @param attCert [out] 속성 인증서
   @param attCertInfo [in] 서명될 속성 인증서 정보
   @param issuerCert [in] 서명할 발급자의 인증서
   @param priInfo [in] 서명할 발급자의 PrivateSignInfo
   @sa ATTCERT_Verify, PrivateKeyInfo_MakePrivateSignInfo

   속성 인증서의 발급자가 속성 인증서를 서명한다.
*/
LIBSPEC_CKM
ERT ATTCERT_Gen(AttributeCertificate     *attCert,
                AttributeCertificateInfo *attCertInfo,
                PrivateKeyInfo           *issuerPriKeyInfo,
                Parameter                *domainParam,
                AlgDesc                   hashAlg,
                Certificate              *issuerCert);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   속성 인증서의 전자 서명을 검증한다.
   @param attCert    [in] 속성 인증서 입력
   @param issuerCert [in] 발급자의 인증서
   @param param      [in] DSA나 KCDSA를 사용할 경우, 각 알고리즘의  parameter
   @return 검증 성공 시에는 SUCCESS, 실패 시에는 FAIL
   @sa ATTCERT_Gen

   속성 인증서의 서명이 올바른 것인지 검증한다.
   서명이 DSA나 KCDSA를 사용하고 발급자의 인증서 SubjectPublicKeyInfo 영역에
   이들 알고리즘의 파라메터가 기입되어 있지 않은 경우, 이를 입력으로 줄 수
   있다.  그렇지 않은 경우에는 세번째 입력 param은 NULL로 주면 된다.
*/
LIBSPEC_CKM
ERT ATTCERT_VerifySign( AttributeCertificate *attCert,
                        Certificate          *issuerCert,
                        Parameter            *domainParam);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   속성 인증서의 유효기간이 옳바른지 확인한다.
   @param attCert   [in] 속성 인증서 입력.
   @param now   [in] 유효기간을 확인할 기준 시간. NULL이면 시스템 시간 사용.
   @sa ATTCERT_GetValidity

   CERT_VerifyTime과 에러코드가 동일하다.
*/
LIBSPEC_CKM
ERT ATTCERT_VerifyTime( AttributeCertificate *attCert,
                        struct tm            *now);



/*****************************************************************************
 * ATTCERT Getting
 */

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   속성 인증서의 발급 대상자를 구한다
   @param serial       [out] 속성 인증서의 일련번호
   @param issuerName   [out] 발급 대상자의 인증서를 발급한 issuer
   @param holderName   [out] 발급 대상자의 Name
   @param holderSID    [out] 발급 대상자의 SID, NULL을 주어 받지 않을 수도 있다.
   @param holderSIDLen [in] holderSID 버퍼의 길이 입력,
   @param attCert      [in] 속성 인증서 입력
   @sa ATTCERT_Set

   속성 인증서에서 그 속성 인증서의 발급 대상자가 누구인지를 구한다.
   속성 인증서의 일련번호, 발급 대상자의 Name, 발급 대상자의 issuer 등등을
   구한다.
*/
LIBSPEC_CKM
ERT ATTCERT_GetHolder( CertificateSerialNumber *serial,
                       Name                    *issuerName,
                       Name                    *holderName,
                       char                    *holderSID,
                       int                      holderSIDLen,
                       AttributeCertificate    *attCert);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   ebrief   속성 인증서의 발급자를 구한다
   @param issuerName [out] 발급자의 Name
   @param attCert    [in] 속성 인증서 입력
   @sa ATTCERT_Set

   속성 인증서에서 그 속성 인증서의 발급자의 Name을 구한다.
*/
LIBSPEC_CKM
ERT ATTCERT_GetIssuer( Name                 *issuerName,
                       AttributeCertificate *attCert);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   속성 인증서의 유효기간을 구한다
   @param notBefore [out] 유효기간 시작 시간.  gmtime이다.
   @param notAfter [out] 유효기간 끝 씨간.  gmtime이다.
   @param attCert   [in] 속성 인증서 입력
   @sa ATTCERT_Set, ATTCERT_VerifyValidity, GmtimeToLocaltime

   속성 인증서에서 그 속성 인증서의 유효기간이 언제부터 언제까지인지
   구한다.  구한 struct tm은 전 지구적인 GMT 시간이므로 지역 시간을 구하려면
   반드시 결과를 GmtimeToLocaltime()등의 함수를 통해 변환하여야만 한다.

*/
LIBSPEC_CKM
ERT ATTCERT_GetValidity( struct tm            *notBefore,
                         struct tm            *notAfter,
                         AttributeCertificate *attCert);

LIBSPEC_CKM
ASNBuf* ATTCERT_GetSignatureValue(AttributeCertificate *attCert);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   속성 인증서에서 Oid에 따라 원하는 속성 type을 구한다.
   @param attCert    [in] 속성 인증서 입력
   @param oid   [in] 구하고자 하는 속성의 Oid
   @param number [in] 구하고자 하는 속성의 index 번호.
   @return  속성이 DER 인코딩된 ASNBuf
   @sa ATTCERT_SetAttributes, ATTCERT_AddAttribute

   속성 인증서에서 필요로 하는 속성을 Oid를 통해 구한다.  하나의 
   속성이 여러개의 value를 가지고 있을 수 있으므로 
   파라메터 number를 통해 각각을 구분하여
   구할 수 있다.  원하는 Oid와 number의 속성이 없을 경우에는 NULL을
   리턴한다.  속성을 구하면 이는 DER 인코딩된 ASNBuf type으로 리턴된다.
   이는 ASN_New()를 사용하여 원하는 속성 type으로 변환하여 사용할 수 있다.

   \code
   UserTicket *ut;

   i = 0;
   while((buf = ATTCERT_GetAttributeByOid(attCert, &Oid_UserTicket, i))) {
     if((ut = ASN_New(UserTicket, buf)) == NULL) break; 

     ....

     ASNBuf_Del(buf);
     ASN_Del(ut);
     i++;
   }
   \endcode

   
*/
LIBSPEC_CKM
ASNBuf* ATTCERT_GetAttributeByOid( AttributeCertificate *attCert,
                                   Oid                  *oid,
                                   int                   number);


/*****************************************************************************
 *  Attributes for RAAC and RSAC
 */

typedef enum {
  ATTCERT_TYPE_UNKNOWN = 0,
  ATTCERT_TYPE_RASC,
  ATTCERT_TYPE_RSSC
} ATTCERT_TYPE;
/*
LIBSPEC_CKM
int ATTCERT_GetType();*/

typedef SeqOfAttribute ATTSRoles;
#define AD_ATTSRoles AD_SeqOfAttribute

LIBSPEC_CKM
ERT ATTSRoles_Add(ATTSRoles *atts, const char *roleName);

typedef SeqOfAttribute ATTSRoleSpecs;
#define AD_ATTSRoleSpecs AD_SeqOfAttribute

LIBSPEC_CKM
ERT ATTSRoleSpecs_Add(ATTSRoleSpecs *atts, Permissions *perms);


/*****************************************************************************
 *  ATTCERT PrintCtx
 */

typedef struct {
  char             ruleId[128];
  char             ruleCtx[1024];
} ACRulesPrintCtx;

typedef struct {
  char              serviceId[128];
  char              serviceCtx[1024];
  int               size;
  ACRulesPrintCtx **rules;          /* ACRulesPrintCtx *rules[ruleSize]; */
} PermissionPrintCtx;

typedef struct {
  char                 policyAuthority[256];
  int                  size;
  PermissionPrintCtx **permissions; /* PermissionPrintCtx *permissions[permissionSize] */
} PermissionsPrintCtx;

typedef struct {
  int attCertType;
  
} ATTCERTPrintCtx;

LIBSPEC_CKM
PermissionPrintCtx *PermissionPrintCtx_New(int ruleSize);

LIBSPEC_CKM
void PermissionPrintCtx_Del(PermissionPrintCtx *permission);


LIBSPEC_CKM
PermissionsPrintCtx *PermissionsPrintCtx_New(int permissionSize);

LIBSPEC_CKM
void PermissionsPrintCtx_Del(PermissionsPrintCtx *permissions);


#ifdef __cplusplus
}
#endif
        
#endif /* _ATTCERT_H */

