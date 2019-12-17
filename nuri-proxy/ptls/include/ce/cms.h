#ifndef _CMS_H_
#define _CMS_H_

/** @defgroup CMS CMS handling
 * @ingroup SP
    @brief Cryptographic Message Syntax(PKCS#7 TYPE) Manipulation Module
*/

/** @file cms.h
    @ingroup CMS
    @brief CMS ����� Ÿ�� ����� �������̽� ����
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
    @brief ContentInfo�� ��ȣȭ�Ͽ� EncryptedData�� �����Ѵ�.
    @param encData [out] EncryptedData�� ������ ������ ������
    @param cInfo [in] ��ȣȭ ����� ContentInfo �ν��Ͻ��� ������
    @param encAlg [in]  ��ȣȭ �˰��� Nid
    @param key [in] ��ĪŰ ���� ����� ����Ʈ ������ ������
    @param keyLen [in] ��ĪŰ�� ����Ʈ ���� ����
    @sa EncryptedData_GetContentInfo

    ContentInfo�� encAlg�� ���õ� ��ȣȭ �˰������� ��ȣȭ�Ͽ�
    EncryptedData�� ����, �����Ͽ� ����Ѵ�.

    EncryptedData�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ���� ��������
    �ݵ�� ASN_Del�� ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.

    encAlg���� EncryptedData_CheckAlg�� ǥ�õ� �˰��� Nid�� ����� �� �ִ�.

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
    @brief EncryptedData�� ��ȣȭ�Ͽ� ContentInfo�� ����Ѵ�.
    @param cInfo [out] ContentInfo�� ������ ������ ������
    @param encData [in] ��ȣȭ ����� EnvryptedData �ν��Ͻ��� ������
    @param key [in] ��ĪŰ�� ����� ����Ʈ ������ ������
    @param keyLen [in] ��ĪŰ�� ����Ʈ ���� ����
    @sa EncryptedData_Gen

    EncryptedData�� �Է¹��� ��ĪŰ�� ��ȣȭ�Ͽ� ��ȣȭ �������
    ContentInfo�� ����Ѵ�.

    ContentInfo�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ���� ��������
    �ݵ�� ASN_Del�� ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.
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
    @brief ContentInfo�� hybrid ������� ��ȣȭ�Ͽ� EnvelopedData�� ����
    @param envData [out] EnvelopedData�� ������ ������ ������
    @param cInfo [in] ��ȣȭ ����� ContentInfo �ν��Ͻ��� ������
    @param encAlg [in] ��ȣȭ �˰��� Nid
    @param numRecp [in] �������� ��
    @param recpCert [in] �����ڵ��� Certificate
    @param domainParam [in] �����ڵ��� ������ �Ķ����
    @param hashAlg [in] ����Ű ��ȣȭ�� ���� �ؽ� �˰����
    @sa EnvelopedData_GetContentInfo

    ContentInfo�� hybrid ������� ��ȣȭ�Ͽ� ��ȣȭ ������� EnvelopedData��
    ����, �����Ͽ� ����Ѵ�. hybrid ����̶� ���� ��ĪŰ�� ��ȣȭ�� ����,
    �� ��ĪŰ�� �ٽ� ����Ű �˰������� ��ȣȭ�ϴ� ����� ���Ѵ�. encAlg��
    �ٷ� ��ĪŰ �˰����� Nid�̴�. (EncryptedData_CheckAlg ����)

    EnvelopedData�� ��ȣ���� ������ ���(������)�� �������� ������ �� �ִµ�,
    �������� ��(numRecp)�� recpCert, domainParam, hashAlg�� �迭�� �޴�
    ������ �װ��̴�. ������1�� recpCert[0], domainParam[0], hashAlg[0]��
    ����Ͽ� ��ȣȭ�ϸ�, ������2�� recpCert[1], domainParam[1], hashAlg[1]��
    ���� ������� �Ķ���Ͱ� ���ȴ�.
    
    Certificate, Paramter�� ���� �ɼ� ���׵��� CKM_Encrypt�� �����ϱ� �ٶ���.
    
    EnvelopedData�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ���� ��������
    �ݵ�� ASN_Del�� ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.
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
    @brief ContentInfo�� hybrid ������� ��ȣȭ�Ͽ� EnvelopedData�� ����
    @param envData [out] EnvelopedData�� ������ ������ ������
    @param skey [out] EnvelopedData�� ����µ��� ����� ��ĪŰ
    @param skeylen [out] key�� ����(����Ʈ ��)
    @param cInfo [in] ��ȣȭ ����� ContentInfo �ν��Ͻ��� ������
    @param encAlg [in] ��ȣȭ �˰��� Nid
    @param numRecp [in] �������� ��
    @param recpCert [in] �����ڵ��� Certificate
    @param domainParam [in] �����ڵ��� ������ �Ķ����
    @param hashAlg [in] ����Ű ��ȣȭ�� ���� �ؽ� �˰����
    @sa EnvelopedData_GetContentInfo

    ContentInfo�� hybrid ������� ��ȣȭ�Ͽ� ��ȣȭ ������� EnvelopedData��
    ����, �����Ͽ� ����Ѵ�. hybrid ����̶� ���� ��ĪŰ�� ��ȣȭ�� ����,
    �� ��ĪŰ�� �ٽ� ����Ű �˰������� ��ȣȭ�ϴ� ����� ���Ѵ�. encAlg��
    �ٷ� ��ĪŰ �˰����� Nid�̴�. (EncryptedData_CheckAlg ����)

    EnvelopedData�� ��ȣ���� ������ ���(������)�� �������� ������ �� �ִµ�,
    �������� ��(numRecp)�� recpCert, domainParam, hashAlg�� �迭�� �޴�
    ������ �װ��̴�. ������1�� recpCert[0], domainParam[0], hashAlg[0]��
    ����Ͽ� ��ȣȭ�ϸ�, ������2�� recpCert[1], domainParam[1], hashAlg[1]��
    ���� ������� �Ķ���Ͱ� ���ȴ�.
    
    Certificate, Paramter�� ���� �ɼ� ���׵��� CKM_Encrypt�� �����ϱ� �ٶ���.
    
    EnvelopedData�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ���� ��������
    �ݵ�� ASN_Del�� ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.

    �� �Լ��� EnvelopedData_Gen�Լ��� �����ϳ� key�� ������ش�.
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
    @brief EnvelopedData�� ��ȣȭ�Ͽ� ContentInfo�� ���
    @param cInfo [out] ContentInfo�� ������ ������ ������
    @param recpPriInfo [in] �������� PrivateKeyInfo
    @param recpCert [in] �������� Certificate
    @param domainParam [in] �������� ������ �Ķ����
    @sa EnvelopedData_Gen

    �������� �����Ű(recpPriInfo), Certificate, ������ �Ķ����(domainParam)��
    �Է¹޾� EnvelopedData ���� �������� ��ġ�ϴ� �����ڰ� ���� ���, ��ȣȭ
    �Ͽ� ��ȣȭ ������� ContentInfo�� �����Ͽ� ����Ѵ�.
    PrivateKeyInfo, Certificate, Parameter �� ���� �ɼ� ���׵��� CKM_Decrypt��
    �����ϱ� �ٶ���.
    
    ContentInfo�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ���� ��������
    �ݵ�� ASN_Del�� ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.
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
    @brief SignedData�� �����Ѵ�.
    @param signedData [out]
    @param cInfo [in] ���� ����� ContentInfo �ν��Ͻ��� ������
    @param signerPriInfo [in] �������� PrivateKeyInfo
    @param signerCert [in] �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param hashAlg [in] ����� ���� �ؽ� �˰��� descriptor
    @param signTime [in] ���� ������ �ð�
    @param caCerts [in] CA ���� ��������(���� ü�� Ȥ�� ��Ÿ ������)
    @param crls [in] CRL
    @sa SignedData_AddSignerInfo

    SignedData�� ����� �����͸� �ǹ��ϴ� ������ PKCS.7 �� ����Ǿ� �ִ�
    ASN.1 Ÿ���̴�. SignedData�� �������� ������ ������ �� �ִ�.

    �� �Լ��� SignedData�� �⺻������ �ϳ��� ������ �����ϴ� SignedData��
    �����Ѵ�. ���� �ʿ��� �Է����δ� ���� ��� �޽����� ContentInfo,
    ���� �˰��� �ʿ��� �����Ű(signerPriInfo), ������(Certificate),
    ������ �Ķ����(domainParam), �ؽ� �˰���(hashAlg) �� �ִ�.
    PrivateKeyInfo, Certificate, Parameter�� ���� �ɼ� ������ CKM_Sign��
    �����ϱ� �ٶ���. �׿�, signTime, caCerts, crls�� �ɼ����� �Ͽ�, NULL��
    ���� �ش� ������ �������� �ʴ´�.

    ����, �ϳ� �̻��� SignerInfo�� �߰��ϰ� ���� ��쿡�� ������
    SignedData_AddSign�� ����Ͽ� �߰��� �� �ִ�. ������ ���� �߰� ����� �Ǵ�
    SignedData�� �ݵ�� SignedData_Gen�� ��ģ �Ŀ��� �Ѵ�.

    ����, SignedData�� SignerInfo�� �ϳ��� �������� �ʰ�, ���� Certificate���
    CRL�� �����ϱ� ���� �������ε� ����� �� �ִ�. �� ��쿡��,
    signerPriInfo, signerCert, domainParam, hashAlg, signTime�� NULL ������
    �����ϸ� �ȴ�.

    ������ SignedData�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ����
    �������� �ݵ�� ASN_Del�� ����Ͽ� �޸𸮸� �����ϱ� �ٶ���.

    NOTE: signerPriInfo�� NULL�� �ָ� ������ ������ �ʴ� SignedData��
    �׳� �����Ѵ�.  ISSAC-SDK�� SG_VerifyCore() �Լ� ��� Ȱ�� �����ϴ�.
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
    @brief SignedData�� SignerInfo�� �߰��Ѵ�.
    @param signedData [out] ������ �߰��� ����� SignedData�� ������
    @param signerPriInfo [in] �������� PrivateSignInfo
    @param signerCert [in] �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param hashAlg [in] ����� ����� �ؽ� �˰���
    @param signTime [in] ���� ������ �ð�
    @sa SignedData_Gen

    SignedData�� ������ �ϳ� �߰��Ѵ�. �� �Ķ���͵��� SignedData_Gen��
    �װ͵�� �����ϹǷ� SignedData_Gen�� �����ϱ� �ٶ���.  ������ ����
    ���⼭ signedData�� �ݵ�� SignedData_Gen�� ���Ͽ� �ϳ��̻��� ������
    ������ �ִ� ���̾�� �Ѵ�.
*/
LIBSPEC_SP
ERT SignedData_AddSign( SignedData     *signedData,
                        PrivateKeyInfo *signerPriInfo,
                        Certificate    *signerCert,
                        Parameter      *domainParam,
                        AlgDesc         hashAlg,
                        struct tm      *signTime);

/** @ingroup CMS
    @brief SignedData���� ���������� �����´�.
    @param certs [out] Certificates�� ������ ������ ������
    @param signedData [in] SignedData �ν��Ͻ��� ������
    @sa SignedData_GetCRLs

    SignedData�� ���ԵǾ� �ִ� ���������� Certificates Ÿ�Կ� �����Ͽ�
    ����Ѵ�. SignedData�� ���ԵǴ� ������ �������� ExtendedCertificate��
    ������, �� �Լ������� ExtendedCertificate ������ Certificate Ÿ�Ը���
    �����´�.

    Certificates�� ����� ������ �������� ASN_Del�� ����Ͽ� �޸𸮸�
    �����Ͽ��� �Ѵ�.
*/
LIBSPEC_SP
ERT SignedData_GetCertificates( Certificates **certs,
                                SignedData    *signedData);

/** @ingroup CMS
    @brief SignedData���� CRL���� �����´�.
    @param crls [out] CRLs�� �������� ������
    @param signedData [in] SignedData �ν��Ͻ��� ������
    @sa SignedData_GetCertificates

    SignedData�� ���ԵǾ� �ִ� CRL�餷�� CertificateRevocationLists Ÿ�Կ�
    �����Ͽ� ����Ѵ�.
    
    CertificateRevocationLists �� ����� ������ �������� ASN_Del��
    ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_SP
ERT SignedData_GetCRLs( CertificateRevocationLists **crls,
                        SignedData                  *signedData);

/** @ingroup CMS
    @brief SignedData�� ������ �ִ� ������ ���� �����Ѵ�.
    @param signedData [in] SignedData �ν��Ͻ��� ������
    @ret ������ ��, ���� ��� 0�� ����
    @sa SignedData_GetIssuerAndSerialNumber SignedData_VerifySign SignedData_GetContentInfo

    SignedData���� ���� ���� �����Ѵ�. ����, ������ ������ 5 ���,
    SignerInfo�� 0, 1, 2, 3, 4 �� �ε��� �� �� ������ , �� ���� 
    SignedData_VerifySign Ȥ�� SignedData_GetIssuerAndSerialNumber����
    �Է°����� ����� �� �ִ�.
*/
LIBSPEC_SP
int SignedData_GetNumSignerInfo( SignedData *signedData);

/** @ingroup CMS
    @brief issuer�� serial number�� �����´�.
    @param issuer [out] Name ������ ������ ������
    @param serialNumber [out] CertificateSerialNumber ������ ������ ������
    @param signedData [in] SignedData �ν��Ͻ��� ������
    @param signerIndex [in] SignerInfo�� index(Signer_GetNumSignerInfo ����)
    @sa SignedData_GetNumSignerInfo SignedData_VerifySign SignedData_GetContentInfo

    SignedData ���ο� ���Ե� SignerInfo���� �⺻������ �������� ����Ű ��������
    issuer�� serial number�� ���еȴ�. signerIndex�� ����Ű�� �ε�����
    SignerInfo�� issuer�� serial number ���� �����´�.

    issuer�� serialNumber �� ����� ������ �������� ASN_Del��
    ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_SP
ERT SignedData_GetIssuerAndSerialNumber( Name                    **issuer,
                                         CertificateSerialNumber **serialNumber,
                                         SignedData               *signedData,
                                         int                       signerIndex);
/** @ingroup CMS
    @brief SignedData ���� SignerInfo�� �����Ѵ�.
    @param signedData [in] SignedData �ν��Ͻ��� ������
    @param signerCert [in] �������� ������
    @param domainParam [in] ������ �Ķ����
    @param signerIndex [in] SignerInfo�� index(Signer_GetNumSignerInfo ����)
    @retval SUCCESS ���� ����
    @retval FAIL ���� ����
    @retval CMS_SIGNED_DATA_CANNOT_FIND_SIGNER_INFO ������ �ʿ��� ���������� ����
    @sa SignedData_GetNumSignerInfo SignedData_GetIssuerAndSerialNumber SignedData_GetContentInfo


    ���� ���� ������ �� ������ ���� ���μ����� ������.

    ù°, �������� : Signer�� �����ǰ�, Cert�� ������ ���� ��� 
    - Cert�� ��������� Verify �Լ��� �Ѱ���. 
    - �Ѱܹ��� Cert�� �ش� signerInfo�� �˻��Ͽ� ���� 
         
    �ι�° �������� : Signer�� ������, ������ �ϰ� ���� ���. 
    - GetNumSignerInfo �� SignedData ���� SignerInfo�� ���� ���Ѵ�. 
    - GetIssuerAndSerialNumber�� signer�� index���� �־�
      signer�� Cert ������ ��´�. 
    - �����غ��� ���� signer�� ã�� ������ index�� �������� signer�� 
      Cert������ ��´�.
    - ������ ���ϴ� signer�� ��ġ�ϸ�, Verify�� �� index���� �־� �����Ѵ�. 
      (�� ��� signer�� �������� ��������� �� ���� ������, ���� ���������
      ���� ������ SignedData ���ο��� �������� �˻��Ͽ� ������ �õ��� ���̴�.
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
    @brief SignedData ���� ����Ǿ��� ���� �޽����� �����´�.
    @param content [out] ���� �޽����� ������ ����� �޸�
    @param contentLen [out] ���� �޽����� ����
    @param signedData [in] SignedData �ν��Ͻ��� ������
    @sa SignedData_GetNumSignerInfo SignedData_GetIssuerAndSerialNumber SignedData_VerifySign

    SignedData�κ��� ���� ����� ContentInfo�� ����, �����Ͽ� ����Ѵ�.
    ����, ContentInfo�� ������ cInfo�� NULL���� �����ȴ�.

    ContentInfo�� ����� ������ �������� ASN_Del��
    ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_SP
ERT SignedData_GetContentInfo( ContentInfo **cInfo,
                               SignedData   *signedData);



/** @ingroup CMS
    @brief SignedData �������� RootCA�� CA �������� �����ϴ� ������ ����ü ����
    @param signedData [out] SignedData �ν��Ͻ��� ������
    @param userCert [in] ����� ������
    @param caCerts [in] CA ���� ��������(���� ü�� Ȥ�� ��Ÿ ������)
    @param crls [in] CRL
    @sa SignedData_Gen CERTS_WriteP7CFile

    SignedData ������ ������ ����ü�� �����Ѵ�.
    SignedData_Gen�� �Ķ���� ���� �����Ͽ� �����ϴ� �Լ��� �����ϴ� ����� �־�����,
    ������ �������� �ʴ� SignedData �������� ȥ���� ����Ǿ�
    ������ �Լ��� �������̽��� �����Ѵ�.

    ������ P7C ���Ϸ� ����ϱ� ���ؼ��� General Syntax�� ���߾
    ContentInfo �������� SignedData���� �˸��� OID�� �Բ� �����͸� �־��־�� �Ѵ�.
*/
LIBSPEC_SP
ERT SignedData_GenP7Certificate( SignedData   **signedData,
                                 Certificate   *signerCert, 
                                 Certificates  *caCerts,
                                 CertificateRevocationLists  *crls);

/** @ingroup CERT
    @brief SignedData �������� ������ ����ü(P7C)�� General syntax�� �����Ͽ� ���
    @param userCert [in] P7C �������� �����ϰ��� �ϴ� ����� ������
    @param caCerts [in] CA ���� ��������(���� ü�� Ȥ�� ��Ÿ ������)
    @param crls [in] CRL
    @param filePath[in] P7C �������� �����Ͽ� ����� ���� ���
    @sa SignedData_GenP7Certificate CERT_WriteFile

    SignedData_GenP7Certificate() �Լ��� �̿��Ͽ� SignedData ���·� ������ ��
    ContentInfo ���Ŀ� SignedData ���� ��Ÿ���� OID�� �Բ� �����͸� �����Ͽ� ����Ѵ�.

    caCerts ������ NULL�� �Է��� ���, ����� ���������� ������ P7C ������ SignedData��
    ��µȴ�.
    crls ������ NULL�� �Է��� ���, CRL ������ ���Ե��� �ʴ´�.
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
