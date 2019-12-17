#ifndef _X509AC_H_
#define _X509AC_H_

#include "asn1.h"
#include "x509com.h"
#include "x509pkc.h"

/** @ingroup X509
    @file x509ac.h
    @brief X509 모듈 중에서 속성 인증서와 관련된 데이터 형과 함수 정의

    X509 모듈 중에서 Attribute Certificate과 관련된 데이터 형을 정의한다.
  */

/** @addtogroup X509
 * @{ */
#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
 * X.509 Attribute Certificate
 */

typedef ASNInt AttCertVersion;
#define AD_AttCertVersion AD_Integer

#define AttCertVersion_Set(ver, num) ASNInt_SetInt(ver, num)
#define AttCertVersion_Get(num, ver) ASNInt_GetInt(num, ver)

enum {
  ATT_CERT_VER1 = 0,
  ATT_CERT_VER2 = 1
};

/*
RFC3281 중에서 GeneralName에 대하여

4.2 Profile of Standard Fields

   GeneralName offers great flexibility.  To achieve interoperability,
   in spite of this flexibility, this profile imposes constraints on the
   use of GeneralName.

   Conforming implementations MUST be able to support the dNSName,
   directoryName, uniformResourceIdentifier, and iPAddress options.
   This is compatible with the GeneralName requirements in [PKIXPROF]
   (mainly in section 4.2.1.7).

   Conforming implementations MUST NOT use the x400Address,
   ediPartyName, or registeredID options.

   Conforming implementations MAY use the otherName option to convey
   name forms defined in Internet Standards.  For example, Kerberos
   [KRB] format names can be encoded into the otherName, using a
   Kerberos 5 principal name OID and a SEQUENCE of the Realm and the
   PrincipalName.
*/

typedef struct {
  ASNSeqClass              klass;
  GeneralNames            *issuer;
  CertificateSerialNumber *serial;
  UniqueIdentifier        *issuerUID; /* optional */
} IssuerSerial;

LIBSPEC_CKM
extern ASNDescriptor AD_IssuerSerial;

LIBSPEC_CKM
extern int IssuerSerial_Set(IssuerSerial *is, Certificate *cert);


typedef struct {
  ASNSeqClass         klass;
  ASNEnum            *digestedObjectType;
  ASNOid             *otherObjectTypeID;  /* optional */
  AlgorithmIdentifier *digestAlgorithm;
  ASNBitStr          *objectDigest;
} ObjectDigestInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_ObjectDigestInfo;

/*
   RFC3281 

   The Holder field is a SEQUENCE allowing three different (optional)
   syntaxes: baseCertificateID, entityName and objectDigestInfo.  Where
   only one option is present, the meaning of the Holder field is clear.
   However, where more than one option is used, there is a potential for
   confusion as to which option is "normative", which is a "hint" etc.
   Since the correct position is not clear from [X.509-2000], this
   specification RECOMMENDS that only one of the options be used in any
   given AC.
*/
typedef struct {
  ASNSeqClass       klass;
  IssuerSerial     *baseCertificateID; /* optional */
  GeneralNames     *entityName;        /* optional */
  ObjectDigestInfo *objectDigestInfo;  /* optional */
} Holder;

LIBSPEC_CKM
extern ASNDescriptor AD_Holder;


typedef struct {
  ASNSeqClass       klass;
  GeneralNames     *issuerName;
  IssuerSerial     *baseCertificateID;
  ObjectDigestInfo *objectDigestInfo;
} V2Form;

LIBSPEC_CKM
extern ASNDescriptor AD_V2Form;

enum {
  AttCertiIssuser_v1Form = 1,
  AttCertiIssuser_v2Form
};

typedef struct {
  ASNChoiceClass   klass;
  int              select;
  union {
    GeneralNames  *v1Form;
    V2Form        *v2Form;
  } choice;
} AttCertIssuer;

LIBSPEC_CKM
extern ASNDescriptor AD_AttCertIssuer;


typedef struct {
  ASNSeqClass      klass;
  GeneralizedTime *notBeforeTime;
  GeneralizedTime *notAfterTime;
} AttCertValidityPeriod;

LIBSPEC_CKM
extern ASNDescriptor AD_AttCertValidityPeriod;

#define AttCertValidityPeriod_Set(valid, not_before, not_after) \
        { ASNGenTime_Set(valid->notBeforeTime, not_before); \
          ASNGenTime_Set(valid->notAfterTime, not_after); }
#define AttCertValidityPeriod_Get(not_before, not_after, valid) \
        { ASNGenTime_Get(not_before, (valid)->notBeforeTime); \
          ASNGenTime_Get(not_after, (valid)->notAfterTime); }



typedef struct {
  ASNSeqClass              klass;
  AttCertVersion          *version;
  Holder                  *holder;
  AttCertIssuer           *issuer;
  AlgorithmIdentifier     *signature;
  CertificateSerialNumber *serialNumber;
  AttCertValidityPeriod   *attrCertValidityPeriod;
  SeqOfAttribute          *attributes;
  UniqueIdentifier        *issuerUniqueID;           /* optional */
  Extensions              *extensions;               /* optional */
} AttributeCertificateInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_AttributeCertificateInfo;


typedef struct {
  ASNSeqClass               klass;
  AttributeCertificateInfo *acinfo;
  AlgorithmIdentifier      *signatureAlgorithm;
  ASNBitStr                *signatureValue;
} AttributeCertificate;

LIBSPEC_CKM
extern ASNDescriptor AD_AttributeCertificate;


/*
   RFC3281

   The extensions field generally gives information about the AC as
   opposed to information about the AC holder.

   An AC that has no extensions conforms to the profile; however,
   section 4.3 defines the extensions that MAY be used with this
   profile, and whether or not they may be marked critical.  If any
   other critical extension is used, the AC does not conform to this
   profile.  However, if any other non-critical extension is used, the
   AC does conform to this profile.
*/
/*****************************************************************************/
/* Extensions 
   1. Audit Identity
   2. AC Targeting
   3. Authority Key Identifier
   4. Authority Information Access
   5. CRL Distribution Points
   6. No Revocation Available
*/

typedef struct {
  ASNSeqClass       klass;
  IssuerSerial     *targetCertificate;
  GeneralName      *targetName;
  ObjectDigestInfo *certDigestInfo;
} TargetCert;

LIBSPEC_CKM
extern ASNDescriptor AD_TargetCert;

typedef struct {
  ASNChoiceClass klass;
  int            select;
  union {
    GeneralName *targetName;
    GeneralName *targetGroup;
    TargetCert  *targetCert;
  } choice;
} Target;

LIBSPEC_CKM
extern ASNDescriptor AD_Target;

typedef struct {
  ASNSeqOfClass    klass;
  int              size;
  Target         **member;
} Targets;

LIBSPEC_CKM
extern ASNDescriptor AD_Targets;


/*****************************************************************************/
/* Attribute Types
   1. Service Authentication Information
   2. Access Identity
   3. Charging Identity
   4. Group
   5. Role
   6. Clearance
*/

typedef struct {
  ASNChoiceClass klass;
  int            select;
  union {
    ASNOctStr   *octets;
    ASNOid      *oid;
    UTF8String  *string;
  } choice;
} IetfAttrSyntaxValue;

LIBSPEC_CKM
extern ASNDescriptor AD_IetfAttrSyntaxValue;

typedef struct {
  ASNSeqOfClass         klass;
  int                   size;
  IetfAttrSyntaxValue **member;
} SeqOfIetfAttrSyntaxValue;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfIetfAttrSyntaxValue;

typedef struct {
  ASNSeqClass               klass;
  GeneralNames             *policyAuthority;
  SeqOfIetfAttrSyntaxValue *values;
} IetfAttrSyntax;

LIBSPEC_CKM
extern ASNDescriptor AD_IetfAttrSyntax;

typedef struct {
  ASNSeqClass   klass;
  GeneralName  *service;
  GeneralName  *ident;
  ASNOctStr    *authInfo;
} SvceAuthInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_SvceAuthInfo;

/*
   The roleName field MUST be present, and roleName MUST use the
   uniformResourceIdentifier CHOICE of the GeneralName.
*/
typedef struct {
  ASNSeqClass   klass;
  GeneralNames *roleAuthority; /* OPTIONAL */
  GeneralName  *roleName;
} RoleSyntax;

LIBSPEC_CKM
extern ASNDescriptor AD_RoleSyntax;

typedef struct {
  ASNSeqClass  klass;
  ASNOid      *type;
  ASNAny      *value;
} SecurityCategory;

LIBSPEC_CKM
extern ASNDescriptor AD_SecurityCategory;

typedef struct {
  ASNSetOfClass      klass;
  int                size;
  SecurityCategory **member;
} SetOfSecurityCategory;

LIBSPEC_CKM
extern ASNDescriptor AD_SetOfSecurityCategory;

typedef ASNBitStr ClassList;
#define AD_ClassList AD_BitString

typedef struct {
  ASNSeqClass            klass;
  ASNOid                *policyId;
  ClassList             *classList;
  SetOfSecurityCategory *securityCategories;
} Clearance;

LIBSPEC_CKM
extern ASNDescriptor AD_Clearance;


/*****************************************************************************/
/* Optional Features
   1. Attribute Encryption
   2. Proxying
   3. Use of ObjectDigestInfo
   4. AA Controls
*/

typedef struct {
  ASNSeqClass     klass;
  GeneralName    *acIssuer;
  ASNInt         *acSerial;
  SeqOfAttribute *attrs;
} ACClearAttrs;

LIBSPEC_CKM
extern ASNDescriptor AD_ACClearAttrs;

typedef struct {
  ASNSeqOfClass    klass;
  int              size;
  Targets        **member;
} ProxyInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_ProxyInfo;

typedef struct {
  ASNSeqOfClass    klass;
  int              size;
  ASNOid         **member;
} AttrSpec;

LIBSPEC_CKM
extern ASNDescriptor AD_AttrSpec;

typedef struct {
  ASNSeqClass   klass;
  ASNInt       *pathLenConstraint;
  AttrSpec     *permittedAttrs;
  AttrSpec     *excludedAttrs;
  ASNBool      *permitUnSpecified;
} AAControls;

LIBSPEC_CKM
extern ASNDescriptor AD_AAControls;


#ifdef __cplusplus
}
#endif
/** @} */
        
#endif /* _X509AC_H_ */
