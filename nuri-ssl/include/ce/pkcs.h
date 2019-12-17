#ifndef _PKCS_H_
#define _PKCS_H_

#include "ckm_pkcrypt.h"
#include "asn1.h"
#include "x509com.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * PKCS7 type definition
 */

/* Object Identifier of PKCS7

   pkcs-7                             OBJECT IDENTIFIER ::= {pkcs 7}
   data                               OBJECT IDENTIFIER ::= {pkcs-7 1}
   signedData                         OBJECT IDENTIFIER ::= {pkcs-7 2}
   envelopedData                      OBJECT IDENTIFIER ::= {pkcs-7 3}
   signedAndEnvelopedData             OBJECT IDENTIFIER ::= {pkcs-7 4}
   digestedData                       OBJECT IDENTIFIER ::= {pkcs-7 5}
   encryptedData                      OBJECT IDENTIFIER ::= {pkcs-7 6}
   */

/* Useful types */
typedef AlgorithmIdentifier ContentEncryptionAlgorithmIdentifier;
#define AD_ContentEncryptionAlgorithmIdentifier AD_AlgorithmIdentifier

typedef AlgorithmIdentifier DigestAlgorithmIdentifier;
#define AD_DigestAlgorithmIdentifier AD_AlgorithmIdentifier

typedef AlgorithmIdentifier DigestEncryptionAlgorithmIdentifier;
#define AD_DigestEncryptionAlgorithmIdentifier AD_AlgorithmIdentifier

typedef AlgorithmIdentifier KeyEncryptionAlgorithmIdentifier;
#define AD_KeyEncryptionAlgorithmIdentifier AD_AlgorithmIdentifier

/* DigestInfo */
typedef OctetString Digest;
#define AD_Digest AD_OctetString

typedef struct _DigestInfo {
  ASNSeqClass klass;
  DigestAlgorithmIdentifier *digestAlgorithm;
  Digest *digest;
} DigestInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_DigestInfo;

/* ContentInfo */
typedef ASNOid ContentType;
#define AD_ContentType AD_ASNOid

typedef struct _ContentInfo {
  ASNSeqClass klass;
  ContentType *contentType;
  Any *content;
} ContentInfo;

typedef ContentInfo Pkcs7;

LIBSPEC_CKM
extern ASNDescriptor AD_ContentInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_Pkcs7;

LIBSPEC_CKM
ERT ContentInfo_SetData(ContentInfo *cInfo, ASN *content, Nid contentType);

#define ContentInfo_GetData(pasn, cInfo, desc) \
             _ContentInfo_GetData((pasn), (cInfo), (AD_##desc))

LIBSPEC_CKM
ERT _ContentInfo_GetData(ASN **pasn, ContentInfo *cInfo, ASNDescriptor desc);

/* Data content type */
typedef OctetString Data;
#define AD_Data AD_OctetString

/* EncryptedContentInfo */
typedef OctetString EncryptedContent;
#define AD_EncryptedContent AD_OctetString

typedef struct _EncryptedContentInfo {
  ASNSeqClass klass;
  ContentType *contentType;
  ContentEncryptionAlgorithmIdentifier *contentEncryptionAlgorithm;
  EncryptedContent *encryptedContent;
} EncryptedContentInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_EncryptedContentInfo;

typedef struct _EncryptedData {
  ASNSeqClass klass;
  Version *version;
  EncryptedContentInfo *encryptedContentInfo;
} EncryptedData;

LIBSPEC_CKM
extern ASNDescriptor AD_EncryptedData;

typedef OctetString EncryptedKey;
#define AD_EncryptedKey AD_OctetString


/*****************************************************************************
 * PKCS8
 */

typedef AlgorithmIdentifier EncryptionAlgorithmIdentifier;
#define AD_EncryptionAlgorithmIdentifier AD_AlgorithmIdentifier

typedef OctetString PKCS8_EncryptedData;
#define AD_PKCS8_EncryptedData AD_OctetString

typedef struct _EncryptedPrivateKeyInfo {
  ASNSeqClass klass;
  EncryptionAlgorithmIdentifier *encryptionAlgorithm;
  PKCS8_EncryptedData *encryptedData;
} EncryptedPrivateKeyInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_EncryptedPrivateKeyInfo;


/* not PKCS-8 */
#define SECRET_KEY_MAX_SIZE 32
typedef EncryptedPrivateKeyInfo EncryptedSecretKeyInfo;
#define AD_EncryptedSecretKeyInfo AD_EncryptedPrivateKeyInfo


/*****************************************************************************
 * PKCS10 type definition
 */
typedef struct _CertificationRequestInfo {
  ASNSeqClass           klass;
  Integer              *version;
  Name                 *subject;
  SubjectPublicKeyInfo *subjectPKInfo;
  Attributes           *attributes;
} CertificationRequestInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_CertificationRequestInfo;


typedef struct _CertificationRequest {
  ASNSeqClass               klass;
  CertificationRequestInfo *certificationRequestInfo;
  AlgorithmIdentifier      *signatureAlgorithm;
  BitString                *signature;
} CertificationRequest;

LIBSPEC_CKM
extern ASNDescriptor AD_CertificationRequest;

typedef enum {
  ER_PKCS_FAIL_TO_OPEN_PKCS10 = ER_PKCS,
  ER_PKCS_INVALID_PKCS10,
  ER_PKCS_INVALID_SIGNATURE
} PKCS10_ERRORS;

/** @brief PKCS#10 형식 인증서 요청 파일을 읽어들인다.
    @param cri [out] 읽어진 인증서 요청이 담길 이중 포인터
    @param filePath [in] 읽어들일 PKCS#10 파일 이름

    기본적으로 ASNBuf_NewFromFile과 같은 방법으로 Base64, PEM, DER encoding
    파일을 읽고, 추가로 e-mail 등의 본문에 삽입된 PEM encoded-data를 읽기위해서
    '-----BEGIN CERTIFICATE REQUEST-----'나
    '-----BEGIN NEW CERTIFICATE REQUEST-----'를 찾아서 읽어들이는 것도 지원한다.

    @ret ER_PKCS_FAIL_TO_OPEN_PKCS10 : 파일 읽기 실패
         ER_PKCS_INVALID_PKCS10 : 잘못된 형식의 PKCS#10 파일
         ER_PKCS_INVALID_SIGNATURE : PKCS#10 파일의 서명값이 잘못됨
    */

LIBSPEC_CKM
ERT PKCS_GetCRInfoFromFile(
  CertificationRequestInfo **cri, const char *filePath);

/*****************************************************************************
 * PKCS12 type definition
 */
typedef BMPString FriendlyName;
#define AD_FriendlyName AD_BMPString

typedef OctetString LocalKeyID;
#define AD_LocalKeyID AD_OctetString


/*****************************************************************************
 * PKCS12 type definition
 */

/* MacData */
typedef struct _MacData {
  ASNSeqClass klass;
  DigestInfo *mac;
  OctetString *macSalt;
  Integer *iterations; /* default 1 */
} MacData;

LIBSPEC_CKM
extern ASNDescriptor AD_MacData;

/* PFX */
typedef struct _PFX {
  ASNSeqClass klass;
  Integer *version;
  ContentInfo *authSafe;
  MacData *macData;
} PFX;

LIBSPEC_CKM
extern ASNDescriptor AD_PFX;

/* AuthenticatedSafe */
typedef struct _AuthenticatedSafe {
  ASNSeqOfClass klass;
  int size;
  ContentInfo **member;
} AuthenticatedSafe;

LIBSPEC_CKM
extern ASNDescriptor AD_AuthenticatedSafe;

/* SafeContents and SafeBag */
typedef Attribute PKCS12Attribute;
#define AD_PKCS12Attribute AD_Attribute

typedef SetOfAttribute SetOfPKCS12Attribute;
#define AD_SetOfPKCS12Attribute AD_SetOfAttribute

typedef struct _SafeBag {
  ASNSeqClass klass;
  ASNOid *bagId;
  ASNAny *bagValue;
  SetOfPKCS12Attribute *bagAttributes;
} SafeBag;

LIBSPEC_CKM
extern ASNDescriptor AD_SafeBag;

typedef struct _SafeContents {
  ASNSeqOfClass klass;
  int size;
  SafeBag **member;
} SafeContents;

LIBSPEC_CKM
extern ASNDescriptor AD_SafeContents;


/* Object Identifier of PKCS12 bag types

   bagtypes             {pkcs12 10 1}
   keyBag               {bagtypes 1}
   pkcs8ShroudedKeyBag  {bagtypes 2}
   certBag              {bagtypes 3}
   crlBag               {bagtypes 4}
   secretBag            {bagtypes 5}
   safeContentsBag      {bagtypes 6}
   */

/* KeyBag */
typedef PrivateKeyInfo KeyBag;
#define AD_KeyBag AD_PrivateKeyInfo

/* PKCS8ShroudedBag */
typedef EncryptedPrivateKeyInfo PKCS8ShroudedKeyBag;
#define AD_PKCS8ShroudedKeyBag AD_EncryptedPrivateKeyInfo

/* CertBag */
typedef struct _CertBag {
  ASNSeqClass klass;
  ASNOid *certId;
  ASNAny *certValue;
} CertBag;

LIBSPEC_CKM
extern ASNDescriptor AD_CertBag;

/* CRLBag */
typedef struct _CRLBag {
  ASNSeqClass klass;
  ASNOid *crlId;
  ASNAny *crlValue;
} CRLBag;

LIBSPEC_CKM
extern ASNDescriptor AD_CRLBag;

/* SecretBag */
typedef struct _SecretBag {
  ASNSeqClass klass;
  ASNOid *secretTypeId;
  ASNAny *secretValue;
} SecretBag;

LIBSPEC_CKM
extern ASNDescriptor AD_SecretBag;

/* SafeContentsBag */

#ifdef __cplusplus
}
#endif

#endif /* _PKCS_H_ */
