#ifndef _CKM_PKCRYPT_H_
#define _CKM_PKCRYPT_H_

/** @defgroup CKM_PKCRYPT CKM PKC Wrapper
 * @ingroup CKM
    @brief 공개키 암호 시스템에 관련된 타입, 함수

    공개키 암호 시스템의 비공개키, 공개키, 도메인 파라미터, 서명 등에
    관한 ASN.1 sytax를 구현하고, PKCRYPT모듈의 각 타입들과의
    변환 함수를 포함한다.
*/

/** @ingroup CKM_PKCRYPT
    @file ckm_pkcrypt.h
    @brief CKM_PKCRYPT 모듈의 인터페이스 정의
*/

#include "pkcrypt_op.h"
#include "pkcrypt_exp.h"
#include "ckm_define.h"
#include "asn1.h"
#include "x509com.h"
#include "x509pkc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _CKM_ERRORS {
  ER_CKM_NO_DOMAIN_PARAMETER = ER_CKM,
  ER_CKM_NOT_SUPPORTED_FUNCTION
} CKM_ERRORS;


/******************************************************************************
 * RSA Key & Parameters type
 */
typedef struct _RSAPublicKey {
  ASNSeqClass  klass;
  Integer     *modulus;
  Integer     *publicExponent;
} RSAPublicKey;  

LIBSPEC_CKM
extern ASNDescriptor AD_RSAPublicKey;

typedef struct _RSAPrivateKey {
  ASNSeqClass  klass;
  Integer     *version;
  Integer     *modulus;
  Integer     *publicExponent;
  Integer     *privateExponent;
  Integer     *prime1;
  Integer     *prime2;
  Integer     *exponent1;
  Integer     *exponent2;
  Integer     *coefficient;
} RSAPrivateKey;  

LIBSPEC_CKM
extern ASNDescriptor AD_RSAPrivateKey;

typedef struct _RSAES_OAEP_params {
  ASNSeqClass          klass;
  AlgorithmIdentifier *hashFunc;
  AlgorithmIdentifier *maskGenFunc;
  AlgorithmIdentifier *pSourceFunc;
} RSAES_OAEP_params;

LIBSPEC_CKM
extern ASNDescriptor AD_RSAES_OAEP_params;

typedef struct _RSASSA_PSS_params {
  ASNSeqClass          klass;
  AlgorithmIdentifier *hashFunc;
  AlgorithmIdentifier *maskGenFunc;
  Integer             *saltLength;
  Integer     		  *trailerField;
} RSASSA_PSS_params;

LIBSPEC_CKM
extern ASNDescriptor AD_RSASSA_PSS_params;

/******************************************************************************
 * DH Key & Parameters type
 */ 
typedef struct _ValidationParms {
  ASNSeqClass  klass;
  BitString   *seed;
  Integer     *pgenCounter;
} ValidationParms;

LIBSPEC_CKM
extern ASNDescriptor AD_ValidationParms;


typedef struct _DomainParameters {
  ASNSeqClass      klass;
  Integer         *p;
  Integer         *g;
  Integer         *q;
  Integer         *j;
  ValidationParms *validationParms;
} DomainParameters;

LIBSPEC_CKM
extern ASNDescriptor AD_DomainParameters;

typedef Integer DHPublicKey;
#define AD_DHPublicKey AD_Integer

typedef Integer DHPrivateKey;
#define AD_DHPrivateKey AD_Integer

/******************************************************************************
 * DSA Key & Parameters type
 */ 
typedef struct _Dss_Parms {
  ASNSeqClass  klass;
  Integer     *p;
  Integer     *q;
  Integer     *g;
} Dss_Parms;

LIBSPEC_CKM
extern ASNDescriptor AD_Dss_Parms;

typedef struct _Dss_Sig_Value {
  ASNSeqClass  klass;
  Integer     *r;
  Integer     *s;
} Dss_Sig_Value;

LIBSPEC_CKM
extern ASNDescriptor AD_Dss_Sig_Value;

typedef Integer DSAPublicKey;
#define AD_DSAPublicKey AD_Integer

typedef Integer DSAPrivateKey;
#define AD_DSAPrivateKey AD_Integer

/******************************************************************************
 * KCDSA Key & Parameters type
 */ 
typedef struct _ValidationParams {
  ASNSeqClass  klass;
  OctetString *seed;
  Integer     *count;
} ValidationParams;

LIBSPEC_CKM
extern ASNDescriptor AD_ValidationParams;

typedef struct _KCDSAParamters_new {
  ASNSeqClass  klass;
  Integer     *p;
  Integer     *q;
  Integer     *g;
  Integer     *j;
  ValidationParams *validationParams;
} KCDSAParameters2;

LIBSPEC_CKM
extern ASNDescriptor AD_KCDSAParameters2;

typedef struct _KCDSAParameters {
  ASNSeqClass  klass;
  Integer     *p;
  Integer     *q;
  Integer     *g;
  Integer     *j;
  OctetString *seed;
  Integer     *count;
} KCDSAParameters;

LIBSPEC_CKM
extern ASNDescriptor AD_KCDSAParameters;

typedef struct _KCDSASignatureValue {
  ASNSeqClass  klass;
  BitString   *r;
  Integer     *s;
} KCDSASignatureValue;

LIBSPEC_CKM
extern ASNDescriptor AD_KCDSASignatureValue;

typedef Integer KCDSAPublicKey;
#define AD_KCDSAPublicKey AD_Integer

typedef Integer KCDSAPrivateKey;
#define AD_KCDSAPrivateKey AD_Integer

/******************************************************************************
 * old KCDSA Key & Parameters type
 */ 
typedef struct _KCDSA_Parms {
  ASNSeqClass  klass;
  Integer     *p;
  Integer     *q;
  Integer     *g;
} KCDSA_Parms;

LIBSPEC_CKM
extern ASNDescriptor AD_KCDSA_Parms;

typedef struct _KCDSA_Sig_Value {
  ASNSeqClass  klass;
  Integer     *r;
  Integer     *s;
} KCDSA_Sig_Value;

LIBSPEC_CKM
extern ASNDescriptor AD_KCDSA_Sig_Value;

/******************************************************************************
 * ECDSA Key & Parameters type
 */ 
typedef struct _EC_Parms {
  ASNChoiceClass  klass;
  int             select;
  union {
    ASNOid     *namedCurve;
  } choice;
} EC_Parms;

LIBSPEC_CKM
extern ASNDescriptor AD_EC_Parms;

typedef struct _ECDSA_Sig_Value {
  ASNSeqClass  klass;
  Integer     *r;
  Integer     *s;
} ECDSA_Sig_Value;

LIBSPEC_CKM
extern ASNDescriptor AD_ECDSA_Sig_Value;

typedef OctetString EC_PublicKey;
#define AD_EC_PublicKey AD_OctetString

typedef struct _ECPrivateKey {
  ASNSeqClass  klass;
  Integer     *version;
  OctetString *privateKey;
  EC_Parms    *parameters;
  BitString   *publicKey;
} ECPrivateKey;

LIBSPEC_CKM
extern ASNDescriptor AD_ECPrivateKey;

typedef struct _ECKCDSA_Sig_Value {
  ASNSeqClass  klass;
  BitString   *r;
  Integer     *s;
} ECKCDSA_Sig_Value;

LIBSPEC_CKM
extern ASNDescriptor AD_ECKCDSA_Sig_Value;

/*****************************************************************************
 * PublicKeyInfo - RFC2459 rename SubjectPublicKeyInfo
 */
typedef SubjectPublicKeyInfo PublicKeyInfo;
#define AD_PublicKeyInfo AD_SubjectPublicKeyInfo

/*****************************************************************************
 * PrivateKeyInfo - PKCS8
 */
typedef AlgorithmIdentifier PrivateKeyAlgorithmIdentifier;
#define AD_PrivateKeyAlgorithmIdentifier AD_AlgorithmIdentifier

typedef OctetString PrivateKey;
#ifdef ASN_SAFE
#define AD_PrivateKey AD_Safe_OctetString
#else
#define AD_PrivateKey AD_OctetString
#endif

typedef struct _PrivateKeyInfo {
  ASNSeqClass klass;
  Version *version;
  PrivateKeyAlgorithmIdentifier *privateKeyAlgorithm;
  PrivateKey *privateKey;
  Attributes *attributes;
} PrivateKeyInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PrivateKeyInfo;

/*****************************************************************************
 * Domain Parameter - not standard
 */
typedef ASNAny Parameter;
#define AD_Parameter AD_Any





/*****************************************************************************
 * Public-Key type manipulating functions 
 */

#define AlgDesc_CheckPKAlg(algDesc)\
          (((algDesc) == RSA15) ||\
		   ((algDesc) == RSA21) ||\
           ((algDesc) == DSA) ||\
           ((algDesc) == ECDSA) ||\
           ((algDesc) == ECKCDSA) ||\
           ((algDesc) == KCDSA) ||\
           ((algDesc) == KCDSA0))
#define AlgDesc_CheckDlpPKAlg(algDesc)\
          (((algDesc) == DSA) ||\
           ((algDesc) == ECDSA) ||\
           ((algDesc) == ECKCDSA) ||\
           ((algDesc) == KCDSA0) ||\
           ((algDesc) == KCDSA))
#define AlgDesc_CheckHashAlg(algDesc)\
          (((algDesc) == SHA1) ||\
           ((algDesc) == SHA256) ||\
           ((algDesc) == SHA384) ||\
           ((algDesc) == SHA512) ||\
           ((algDesc) == MD5) ||\
           ((algDesc) == HAS160))


#define AlgNid_CheckPKAlg__(algNid)\
          (((algNid) == NID_rsaEncryption) ||\
		   ((algNid) == NID_id_RSASSA_PSS) ||\
           ((algNid) == NID_dsa) ||\
           ((algNid) == NID_id_ecPublicKey) ||\
           ((algNid) == NID_id_ecPublicKey_KISA) ||\
           ((algNid) == NID_eckcdsa) ||\
           ((algNid) == NID_kCDSA1) ||\
           ((algNid) == NID_kCDSA0))

#define AlgNid_CheckDlpPKAlg(algNid)\
          (((algNid) == NID_dsa) ||\
           ((algNid) == NID_id_ecPublicKey) ||\
           ((algNid) == NID_id_ecPublicKey_KISA) ||\
           ((algNid) == NID_eckcdsa) ||\
           ((algNid) == NID_kCDSA1) ||\
           ((algNid) == NID_kCDSA0))

#define AlgNid_CheckHashAlg(algNid)\
          (((algNid) == NID_SHA1) ||\
           ((algNid) == NID_SHA256) ||\
           ((algNid) == NID_SHA384) ||\
           ((algNid) == NID_SHA512) ||\
           ((algNid) == NID_md5) ||\
           ((algNid) == NID_has160))

#define AlgNid_CheckSigAlg(algNid)\
          (((algNid) == NID_md5WithRSAEncryption) ||\
           ((algNid) == NID_sha1WithRSAEncryption) ||\
           ((algNid) == NID_sha256WithRSAEncription) ||\
           ((algNid) == NID_sha384WithRSAEncription) ||\
           ((algNid) == NID_sha512WithRSAEncription) ||\
		   ((algNid) == NID_id_RSASSA_PSS) ||\
           ((algNid) == NID_dsa_with_sha1) ||\
           ((algNid) == NID_ecdsa_with_SHA1) ||\
           ((algNid) == NID_ecdsa_with_SHA2) ||\
           ((algNid) == NID_ecdsa_with_SHA256) ||\
           ((algNid) == NID_ecdsa_with_SHA384) ||\
           ((algNid) == NID_ecdsa_with_SHA512) ||\
           ((algNid) == NID_eckcdsa_with_HAS160) ||\
           ((algNid) == NID_eckcdsa_with_SHA1) ||\
           ((algNid) == NID_eckcdsa_with_SHA224) ||\
           ((algNid) == NID_eckcdsa_with_SHA256) ||\
           ((algNid) == NID_kcdsa1WithHAS160) ||\
           ((algNid) == NID_kcdsa1WithSHA1) ||\
           ((algNid) == NID_kcdsa1WithSHA256) ||\
           ((algNid) == NID_kcdsa0WithHAS160) ||\
           ((algNid) == NID_kcdsa0WithSHA256) ||\
           ((algNid) == NID_kcdsa0WithSHA1))


#define AlgNid_CheckPKAlg(algNid) (AlgNid_CheckPKAlg__(algNid) || AlgNid_CheckSigAlg(algNid))

/* 2005/8/5 임명철 대리의 요청에 의해 다른 업체가 생성한 PKCS#7 
메시지 검증 오류를 검토중 draft중인 표준에서 pkAlg에 hashAlg를 
포함해도 인정하는 것을 알게되어 이를 허용하기 위해 
  1. AlgNid_CheckPKAlg를 AlgNid_CheckPKAlg__로 이름을 바꾸고 대신 
  2. AlgNid_CheckPKAlg를 
     AlgNid_CheckPKAlg__(algNid) || AlgNid_CheckSigAlg(algNid)
     로 새로 정의하고 
  3. AlgNid_GetSigAlgNid는   if (AlgNid_CheckSigAlg(pkAlg))
     return pkAlg; 부분을 맨 앞에 추가한다.
조현래
*/

/**
 *  주어진 알고리즘 Nid가 대칭키 알고리즘의 Nid인지 확인한다. 
 */


#define AlgNid_CheckSymmAlg(algNid)\
          (((algNid) == NID_seedECB) ||\
           ((algNid) == NID_seedCBC) ||\
           ((algNid) == NID_seedOFB) ||\
           ((algNid) == NID_seedCFB) ||\
           ((algNid) == NID_rc2CBC) ||\
           ((algNid) == NID_rc5_CBC_PAD) ||\
           ((algNid) == NID_des_EDE3_CBC) ||\
           ((algNid) == NID_desCBC) ||\
           ((algNid) == NID_pACA_CBC))

/** @ingroup CKM_PKCRYPT
    @brief 해당 공개키 알고리즘 Nid를 리턴
    @param pkAlg [in] 공개키 알고리즘 descriptor
    @ret 해당 공개키 알고리즘의 Nid를 리턴
         입력값이 잘못되었거나 해당되는 알고리즘이 없으면 0을 리턴
    @sa AlgNid_GetPKAlgDesc AlgDesc_GetHashAlgNid AlgDesc_GetSigAlgNid

    공개키 알고리즘 descriptor와 일치하는 Nid를 리턴한다.
    Nid는 oid.h에 정의되어 있으며, Object Identifier를 의미하는
    값이다.

    반대로, 공개키 알고리즘 Nid로부터 descriptor를 얻으려면,
    AlgNid_GetPKAlgDesc 함수를 사용한다.
*/
LIBSPEC_CKM
Nid AlgDesc_GetPKAlgNid(AlgDesc pkAlg);

/** @ingroup CKM_PKCRYPT
    @brief 해당 해쉬 알고리즘 Nid를 리턴
    @param hashAlg [in] 해쉬 알고리즘 descriptor
    @ret 해당 해쉬 알고리즘의 Nid를 리턴
         입력값이 잘못되었거나 해당 Nid가 없으면 0을 리턴
    @sa AlgNid_GetHashAlgDesc AlgDesc_GetPKAlgNid AlgDesc_GetSigAlgNid

    해쉬 알고리즘 descriptor와 일치하는 Nid를 리턴한다.
    
    반대로, 해쉬 알고리즘 Nid로부터 descriptor를 얻으려면,
    AlgNid_GetHashAlgDesc 함수를 사용한다.
*/
LIBSPEC_CKM
Nid AlgDesc_GetHashAlgNid(AlgDesc hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief 해당 서명 알고리즘 Nid를 리턴
    @param pkAlg [in] 공개키 알고리즘 descriptor
    @param hashAlg [in] 해쉬 알고리즘 descriptor
    @ret 해당 서명 알고리즘의 Nid를 리턴
         입력값이 잘못되었거나 해당 Nid가 없으면 0을 리턴
    @sa AlgDesc_GetPKAlgDesc AlgDesc_GetHashAlgNid

    서명 알고리즘은 공개키 알고리즘과 서명시 사용된 해쉬 알고리즘의
    조합으로 구성된다. 공개키 알고리즘 descriptor와 해쉬 알고리즘
    descriptor를 입력 받아 서명 알고리즘의 Nid를 리턴한다.
*/
LIBSPEC_CKM
Nid AlgDesc_GetSigAlgNid(AlgDesc pkAlg,  AlgDesc hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief 해당 공개키 알고리즘 descriptor를 리턴
    @param pkAlgOrSigAlg [in] 공개키 알고리즘 혹은 서명 알고리즘 Nid
    @ret 해당 공개키 알고리즘 descriptor를 리턴
         입력값이 잘못되었거나 해당 descriptor가 없으면 NULL을 리턴
    @sa AlgDesc_GetPKAlgNid AlgNid_GetHashAlgDesc AlgNid_GetSigAlgNid

    공개키 알고리즘 혹은 서명 알고리즘 Nid로부터 해당 공개키 알고리즘
    descriptor를 구한다.
 */
LIBSPEC_CKM
AlgDesc AlgNid_GetPKAlgDesc(Nid pkAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief 해당 해쉬 알고리즘 descriptor를 리턴
    @param hashAlgOrSigAlg [in] 해쉬 알고리즘 혹은 서명 알고리즘 Nid
    @ret 해당 해쉬 알고리즘 descriptor를 리턴
         입력값이 잘못되었거나 해당 descriptor가 없으면 NULL을 리턴
    @sa AlgDesc_GetHashAlgNid AlgNid_GetPKAlgDesc AlgNid_GetSigAlgNid

    해쉬 알고리즘 혹은 서명 알고리즘 Nid로부터 해당 해쉬 알고리즘
    descriptor를 구한다.
*/
LIBSPEC_CKM
AlgDesc AlgNid_GetHashAlgDesc(Nid hashAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief 해당 서명 알고리즘 Nid를 리턴
    @param pkAlg [in] 공개키 알고리즘 Nid
    @param hashAlg [in] 해쉬 알고리즘 Nid
    @ret 해당 공개키 알고리즘 descriptor를 리턴
         입력값이 잘못되었거나 해당 Nid가 없으면 0을 리턴
    @sa AlgDesc_GetSigAlgNid AlgNid_GetPKAlgDesc AlgNid_GetHashAlgNid

    서명 알고리즘은 공개키 알고리즘과 서명시 사용된 해쉬 알고리즘의
    조합으로 구성된다.  공개키 알고리즘과 해쉬 알고리즘 Nid로부터
    서명 알고리즘 Nid를 구한다.
*/
LIBSPEC_CKM
Nid AlgNid_GetSigAlgNid(Nid pkAlg, Nid hashAlg);

/** @ingroup CKM_PKCRYPT
    @biref BCIPHER에서 사용하기 위해 대칭키 알고리즘 NID로부터 AlgDesc값과 mode값을 구한다.
    @param nidSymmAlg [in]  대칭키 알고리즘을 나타내는 NID
    @param pMode     [out] 대칭키 mode( MODE_ECB, MODE_CBC, ...), mode값이 필요 없을 때에는 NULL을 입력
    @ret 대칭키 알고리즘 descriptor, Nid의 입력값이 잘못되었거나, 해당 알고리즘이 없으면 0을 리턴
*/
LIBSPEC_CKM
AlgDesc AlgNid_GetSymmAlgDesc(Nid nidSymmAlg, BYTE *pMode);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPubKey를 DER-encoding 한다.
    @param pubKey [in] PKCryptPubKey 구조체 인트슨스의 포인터
    @ret encoding된 값을 담은 ASNBuf의 포인터를 리턴
         실패시 NULL을 리턴
    @sa PublicKey_Decode PrivateKey_Encode PrivateKey_Decode

    PKCRYPT 모듈의 공개키 구조체인 PKCryptPubKey를 각 알고리즘별
    ASN.1 syntax에 따라서 DER-encoding하여 이값을 생성된 ASNBuf에
    저장하여 그 포인터를 리턴한다.

    리턴된 ASNBuf는 함수 내부에서 메모리에 할당되므로 사용이
    끝나는 시점에서 반드시 ASNBuf_Del로 메모리를 해제하여야 한다.
*/
LIBSPEC_CKM
ASNBuf* PublicKey_Encode(PKCryptPubKey *pubKey);

/** @ingroup CKM_PKCRYPT
    @brief DER-encoding된 공개키버퍼를 decoding하여 PKCryptPubKey를 생성한다.
    @param pubKeyBuf [in] encoding된 공개키를 담은 ASNBuf의 포인터
    @param pkAlg [in] 공개키 알고리즘의 Nid
    @ret 생성된 PKCryptPubKey의 포인터를 리턴
         지원하지 않는 알고리즘이거나 decoding에 실패시 NULL을 리턴
    @sa PublicKey_Encode PrivateKey_Encode PrivateKey_Decode

    DER-encoding된 공개키가 저장된 ASNBuf와 그 키의 알고리즘 Nid를
    입력받아 PKCRYPT 모듈의 공개키 구조체인 PKCryptPubKey를 생성,
    설정하여 그 포인터를 리턴한다.

    리턴된 PKCryptPubKey는 함수 내부에서 메모리에 할당되므로 사용이
    끝나는 시점에서 반드시 PKCRYPT_DelPubKey로 메모리를 헤제하여야
    한다.
*/
LIBSPEC_CKM
PKCryptPubKey* PublicKey_Decode(ASNBuf *pubKeyBuf, Nid pkAlg);

LIBSPEC_CKM
PKCryptPubKey* PublicKey_Decode_EC(ASNBuf *pubKeyBuf, Nid pkAlg,
		PKCryptParam *param);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPriKey를 DER-encoding 한다.
    @param priKey [in] PKCryptPriKey 구조체 인스턴스의 포인터
    @ret encoding된 값을 담은 ASNBuf의 포인터를 리턴
         실패시 NULL을 리턴
    @sa PrivateKey_Decode PublicKey_Encode PublicKey_Decode
    
    PKCRYPT 모듈의 비공개키 구조체인 PKCryptPriKey를 각 알고리즘별
    ASN.1 syntax에 따라서 DER-encoding하여 이값을 생성된 ASNBuf에
    저장하여 그 포인터를 리턴한다.

    리턴된 ASNBuf는 함수 내부에서 메모리에 할당되므로 사용이
    끝나는 시점에서 반드시 ASNBuf_Del로 메모리를 해제하여야 한다.
*/
LIBSPEC_CKM
ASNBuf* PrivateKey_Encode(PKCryptPriKey *priKey);

/** @ingroup CKM_PKCRYPT
    @brief ECC의 개인키를 DER-encoding 한다.
    @param priKey [in] PKCryptPriKey 구조체 인스턴스의 포인터
    @param pubKey [in] PKCryptPubKey 구조체 인스턴스의 포인터 or NULL
    @param param [in] PKCryptParam 구조체 인스턴스의 포인터 or NULL
    @ret encoding된 값을 담은 ASNBuf의 포인터를 리턴
         실패시 NULL을 리턴
    @sa PrivateKey_Decode_EC PublicKey_Encode PublicKey_Decode_ex
    
    PKCRYPT 모듈의 비공개키 관련 구조체들을 ECC 알고리즘의
    ASN.1 syntax에 따라서 DER-encoding하여 이값을 생성된 ASNBuf에
    저장하여 그 포인터를 리턴한다.
    
    pubKey 와 param 파라미터에 NULL을 넘겨줄 경우에는 PrivateKey에
    publicKey와 curveName은 설정하지 않는다.

    리턴된 ASNBuf는 함수 내부에서 메모리에 할당되므로 사용이
    끝나는 시점에서 반드시 ASNBuf_Del로 메모리를 해제하여야 한다.
*/
LIBSPEC_CKM
ASNBuf* PrivateKey_Encode_EC(PKCryptPriKey *priKey, PKCryptPubKey *pubKey, PKCryptParam *param);

/** @ingroup CKM_PKCRYPT
    @brief DER-encoding된 비공개키 버퍼를 decoding하여 PKCryptPriKey를 생성한다.
    @param priKeyBuf [in] encoding된 비공개키를 담은 ASNBuf의 포인터
    @param pkAlg [in] 비공개키 알고리즘의 Nid
    @ret 생성된 PKCryptPriKey의 포인터를 리턴
         지원하지 않는 알고리즘이거나 decoding에 실패시 NULL을 리턴
    @sa PrivateKey_Encode PublicKey_Encode PublicKey_Decode
    
    DER-encoding된 비공개키가 저장된 ASNBuf와 그 키의 알고리즘 Nid를
    입력받아 PKCRYPT 모듈의 비공개키 구조체인 PKCryptPriKey를 생성,
    설정하여 그 포인터를 리턴한다.

    리턴된 PKCryptPriKey는 함수 내부에서 메모리에 할당되므로 사용이
    끝나는 시점에서 반드시 PKCRYPT_DelPriKey로 메모리를 해제하여야
    한다.
*/
LIBSPEC_CKM
PKCryptPriKey* PrivateKey_Decode(ASNBuf *priKeyBuf, Nid pkAlg);

/** @ingroup CKM_PKCRYPT
    @brief DER-encoding된 비공개키 버퍼를 decoding한다.
    @param priKey [out] PKCryptPriKey 인스턴스의 포인터를 담을 포인터
    @param pubKey [out] PKCryptPubKey 인스턴스의 포인터를 담을 포인터
    @param param [out] PKCryptParam 인스턴스의 포인터를 담을 포인터
    @param priKeyBuf [in] encoding된 비공개키를 담은 ASNBuf의 포인터
    @param pkAlg [in] 비공개키 알고리즘의 Nid
    @ret SUCCESS, FAIL
    @sa PrivateKey_Encode_EC PublicKey_Encode PublicKey_Decode_ex
    
    DER-encoding된 비공개키가 저장된 ASNBuf와 그 키의 알고리즘 Nid를
    입력받아 PKCRYPT 모듈의 비공개키 구조체인 PKCryptPriKey와 Optional
    값인 PKCryptPubKey, PKCryptParam을 생성하여 그 포인터를 설정하고
    결과를 리턴한다.

    리턴된 PKCryptPriKey, PKCryptPubKey, PKCryptParam 은 함수 내부에서
    메모리에 할당되므로 사용이 끝나는 시점에서 반드시 PKCRYPT_DelPriKey로
    메모리를 해제하여야 한다.
*/
LIBSPEC_CKM
PKCryptPriKey* PrivateKey_Decode_EC(ASNBuf *priKeyBuf, Nid pkAlg,
		PKCryptPubKey **pubKey, PKCryptParam **param);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptSig를 DER-encoding 한다.
    @param pkcSig [in] PKCryptSig 인스턴스의 포인터
    @ret DER-encoding된 결과를 저장하고 있는 ASNBuf의 포인터를 리턴.
         encoding이 실패할 경우 NULL을 리턴.
    @sa Sig_Decode

    PKCRYPT 모듈의 서명값을 의미하는 구조체인 PKCryptSig를 각 알고리즘별
    ASN.1 syntax에 따라서 DER-encoding하여 이값을 생선된 ASNBuf에
    저장하여 그 포인터를 리턴한다.

    리턴된 ASNBuf는 함수 내부에서 메모리에 할당되므로 사용이
    끝나는 시점에서 반드시 ASNBuf_Del로 메모리를 해제하여야 한다.
*/
LIBSPEC_CKM
ASNBuf* Sig_Encode( PKCryptSig *pkcSig);

/** @ingroup CKM_PKCRYPT
    @brief DER-encoding된 서명값을 담은 ASNBuf를 decoding 한다.
    @param pkcSig [out] PKCryptSig 인스턴스의 포인터
    @param sigBuf [in] encoding된 서명값을 담은 ASNBuf의 포인터
    @param pkAlgOrSigAlg 서명 알고리즘 혹은 공개키 알고리즘의 Nid
    @ret SUCCESS, FAIL
    @sa Sig_Encode

    서명값이 저장된 ASNBuf와 서명 알고리즘 혹은 공개키 알고리즘 Nid를
    입력받아 PKCryptSig를 설정한다. PKCryptSig는 PKCryptPriKey,
    PKCryptPubKey와는 달리 메모리 할당, 해제가 필요없는 인스턴스이다.
*/
LIBSPEC_CKM
ERT Sig_Decode( PKCryptSig *pkcSig, ASNBuf *sigBuf, Nid pkAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPriKey로부터 PrivateKeyInfo를 생성한다.
    @param priKey [in] PKCryptPriKey 인스턴스의 포인터
    @param param [in] PKCryptParam 인스턴스의 포인터 or NULL
    @ret 생성된 PrivateKeyInfo 인스턴스의 포인터를 리턴, 실패시 NULL을 리턴
    @sa PKCryptPriKey_New PublicKeyInfo_New PKCryptPubKey_New

    PrivateKeyInfo는 DER-encoding된 비공개키의 값과 알고리즘 OID,
    그에 따른 도메인 파라미터들을 담을 수 있는 ASN.1 구조체이다.

    이 함수는 PKCRYPT 모듈의 비공개키와 도메인 파라미터 구조체인
    PKCryptPriKey, PKCryptParam을 입력으로 받아 PrivateKeyInfo를
    생성, 설정하여 그 포인터를 리턴한다. param 파라미터에 NULL을
    넘겨줄 경우에는 PrivateKeyInfo에 도메인 파라미터는 설정하지
    않는다.

    리턴된 PrivateKeyInfo는 함수 내부에서 메모리에 할당되므로
    사용이 끝나는 시점에서 반드시 ASN_Del로 메모리를 해제하여야 한다.
*/
LIBSPEC_CKM
PrivateKeyInfo* PrivateKeyInfo_New( PKCryptPriKey  *priKey,
                                    PKCryptParam   *param);

LIBSPEC_CKM
PrivateKeyInfo* PrivateKeyInfo_New_RSAPSS( PKCryptPriKey *priKey, AlgDesc hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief ECC 개인키로부터 PrivateKeyInfo를 생성한다.
    @param priKey [in] PKCryptPriKey 인스턴스의 포인터
    @param pubKey [in] PKCryptPubKey 인스턴스의 포인터 or NULL
    @param param [in] PKCryptParam 인스턴스의 포인터 or NULL
    @ret 생성된 PrivateKeyInfo 인스턴스의 포인터를 리턴, 실패시 NULL을 리턴
    @sa PKCryptPriKey_New PublicKeyInfo_New PKCryptPubKey_New PKCryptParam_New

    PrivateKeyInfo는 DER-encoding된 비공개키의 값과 알고리즘 OID,
    그에 따른 도메인 파라미터들을 담을 수 있는 ASN.1 구조체이다.

    이 함수는 PKCRYPT 모듈의 비공개키와 도메인 파라미터 구조체인
    PKCryptPriKey, PKCryptPubKey, PKCryptParam을 입력으로 받아
    PrivateKeyInfo를 생성, 설정하여 그 포인터를 리턴한다. pubKey와
    param 파라미터에 NULL을 넘겨줄 경우에는 PrivateKey에 publicKey와
    curveName은 설정하지 않는다.

    리턴된 PrivateKeyInfo는 함수 내부에서 메모리에 할당되므로
    사용이 끝나는 시점에서 반드시 ASN_Del로 메모리를 해제하여야 한다.
*/
LIBSPEC_CKM
PrivateKeyInfo* PrivateKeyInfo_New_EC( PKCryptPriKey  *priKey,
                                       PKCryptPubKey  *pubKey,
                                       PKCryptParam   *param);

/** @ingroup CKM_PKCRYPT
    @brief PrivateKeyInfo의 attributes에 난수를 저장한다.
    @param param [in] PrivateKeyInfo_New에서 생성된 PrivateKeyInfo 인스턴스의 포인터
    @ret 난수가 저장된 PrivateKeyInfo 인스턴스의 포인터를 리턴
    @sa PKCryptPubKey_New PrivateKeyInfo_New PKCryptPriKey_New

*/
LIBSPEC_CKM
PrivateKeyInfo* PrivateKeyInfo_New2(PrivateKeyInfo  *priInfo);

/** @ingroup CKM_PKCRYPT
    @brief PrivateKeyInfo로부터 PKCryptPriKey를 생성한다.
    @param param [out] PKCryptParam 인스턴스의 포인터 변수의 포인터 or NULL
    @param priInfo [in] PrivateKeyInfo 인스턴스의 포인터
    @ret 생성된 PKCryptPriKey 인스턴스의 포인터를 리턴
         지원하지 않는 알고리즘이거나 decoding에 실패시 NULL을 리턴 
    @sa PriavateKeyInfo_New PublicKeyInfo_New PKCryptPubKey_New

    비공개키의 정보를 담고 있는 ASN.1 구조체인 PrivateKeyInfo 로부터
    PKCRYPT 모듈의 PKCryptPriKey, PKCryptParam 을 생성, 설정하여
    리턴한다. param 파라미터에는 NULL값을 넘겨 줄 수 있으며,
    그런 경우에는 PKCryptParam은 생성되지 않는다.

    리턴된 PKCryptPriKey와 PKCryptParam은 함수 내부에서 메모리에
    할당되므로 사용이 끝나는 시점에서 반드시 ASN_Del로 메모리를
    해제하여야 한다.
*/
LIBSPEC_CKM
PKCryptPriKey* PKCryptPriKey_New(PKCryptParam         **param,
                                 const PrivateKeyInfo  *priInfo);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPriKey의 데이터를 삭제한다.
    @param priKey [in] PKCryptPriKey 인스턴스의 포인터
    @ret 생성된 PrivateKeyInfo 인스턴스의 포인터를 리턴, 실패시 NULL을 리턴
    @sa PKCryptPriKey_New PublicKeyInfo_New PKCryptPubKey_New

    PrivateKeyInfo 는 ASN.1 타입으로 ME 모듈의 ASN_Del를 사용하여,
    메모리에 할당된 영역을 삭제하게 된다. 그러나, 메모리에 쓰여진 값은
    덮어쓰여지기 전에는 계속 상존하므로 보안상의 허점이 될 수 있다.
    따라서, ASN_Del를 수행하기 전, 메모리 영역의 데이터를 삭제하는 것이
    바람직하다. 이 역할을 수행하는 함수이다.
*/
LIBSPEC_CKM
void PrivateKeyInfo_Wipe( PrivateKeyInfo *priInfo);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPubKey로부터 PublicKeyInfo를 생성한다.
    @param priKey [in] PKCryptPubKey 인스턴스의 포인터
    @param param [in] PKCryptParam 인스턴스의 포인터 or NULL
    @ret 생성된 PublicKeyInfo 인스턴스의 포인터를 리턴, 실패시 NULL을 리턴
    @sa PKCryptPubKey_New PrivateKeyInfo_New PKCryptPriKey_New
    
    PublicKeyInfo는 DER-encoding된 공개키의 값과 알고리즘 OID,
    그에 따른 도메인 파라미터들을 담을 수 있는 ASN.1 구조체이다.

    이 함수는 PKCRYPT 모듈의 공개키와 도메인 파라미터 구조체인
    PKCryptPubKey, PKCryptParam을 입력으로 받아 PublicKeyInfo를
    생성, 설정하여 그 포인터를 리턴한다. param 파라미터에 NULL을
    넘겨줄 경우에는 PrivateKeyInfo에 도메인 파라미터는 설정하지
    않는다.

    리턴된 PublicKeyInfo는 함수 내부에서 메모리에 할당되므로
    사용이 끝나는 시점에서 반드시 ASN_Del로 메모리를 헤제하여야 한다.
*/
LIBSPEC_CKM
PublicKeyInfo* PublicKeyInfo_New( PKCryptPubKey  *pubKey,
                                  PKCryptParam   *param);

LIBSPEC_CKM
PublicKeyInfo* PublicKeyInfo_New_RSAPSS( PKCryptPubKey *pubKey, AlgDesc hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief PublicKeyInfo로부터 PKCryptPubKey를 생성한다.
    @param param [out] PKCryptParam 인스턴스의 포인터 변수의 포인터 or NULL
    @param pubInfo [in] PublicKeyInfo 인스턴스의 포인터
    @ret 생성된 PKCryptPubKey 인스턴스의 포인터를 리턴
         지원하지 않는 알고리즘이거나 decoding에 실패시 NULL을 리턴 
    @sa PublicKeyInfo_New PrivateKeyInfo_New PKCryptPriKey_New
    
    공개키의 정보를 담고 있는 ASN.1 구조체인 PublicKeyInfo 로부터
    PKCRYPT 모듈의 PKCryptPubKey, PKCryptParam 을 생성, 설정하여
    리턴한다. param 파라미터에는 NULL값을 넘겨 줄 수 있으며,
    그런 경우에는 PKCryptParam은 생성되지 않는다.

    리턴된 PKCryptPubKey와 PKCryptParam은 함수 내부에서 메모리에
    할당되므로 사용이 끝나는 시점에서 반드시 ASN_Del로 메모리를
    해제하여야 한다.
*/
LIBSPEC_CKM
PKCryptPubKey* PKCryptPubKey_New( PKCryptParam  **param,
                                  PublicKeyInfo  *pubInfo);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptParam으로부터 Parameter를 생성한다.
    @param pkcParam[in] PKCryptParam 인스턴스의 포인터
    @ret 생성된 Paramter 인스턴스의 포인터를 리턴, 실패시 NULL을 리턴
    @sa PKCryptParam_New

    Paramter 구조체는 공개키 알고리즘의 도메인 파라미터를 의미하는 것으로
    ASN.1 base type 중의 하나인 ANY 타입을 그대로 재정의 하고 있다. 
    ANY 타입은 AlgorithmIdentifier라는 ASN.1 구조체의 parameters 변수의
    타입이다. 그 변수에는 보통 도메인 파라미터가 encoding된 상태로 저장되게
    되는데, 이 함수에서는 도메인 파라미터를 encoding하여 ANY 타입 구조체를
    그대로 리턴하는 것이다.

    리턴되는 Parameter 인스턴스는 함수 내부에서 메모리에 할당되므로,
    사용이 끝나는 시점에서 반드시 ASN_Del로 메모리를 해제하기 바란다.
    혹은, 다른 ASN.1 구조체의 변수에 이 포인터를 넘겼을 경우에는
    예외이다.
*/
LIBSPEC_CKM
Parameter* Parameter_New(PKCryptParam *pkcParam);

/** @ingroup CKM_PKCRYPT
    @brief Parameter로부터 PKCryptParam을 생성한다.
    @param param[in] Paramter 인스턴스의 포인터
    @param pkAlgOrSigAlg[in] 서명 혹은 공개키 알고리즘의 Nid
    @ret 생성된 PKCryptParam 인스턴스의 포인터를 리턴
         지원되지 않는 알고리즘이거나 decoding 실패시 NULL을 리턴
    @sa Paramter_New

    Parameter 구조체로부터 도메인 파라미터를 decoding하여 PKCRYPT 모듈의
    PKCryptParam을 생성, 설정하여 그 포인터를 리턴한다.

    이리턴되는 PKCryptParam 인스턴스는 함수 내부에서 메모리에 할당되므로,
    사용이 끝나는 시점에서 반드시 PKCRYPT_DelParam으로 메모리를 해제하여야
    한다.
*/
LIBSPEC_CKM
PKCryptParam* PKCryptParam_New(const Parameter *param, Nid pkAlgOrSigAlg);


/** doxygen needed
*/
LIBSPEC_CKM
int Parameter_GetAlgBitLen(Parameter *param);

/** @ingroup CKM_PKCRYPT
 *  @brief 두개이 도메인 파라메터의 내용이 같은지 비교한다.
 *
 * ASNInt의 음수 처리 버그 때문에 실제 같은 값을 가진 두개의 도메인
 * 파라메터가 다른 내용으로 인코딩되는 경우가 발생한다.  이를 위해
 * 둘을 디코딩하여 실제 내용을 비교하여 판단하도록 한다
 */
LIBSPEC_CKM
int Parameter_Compare(Parameter *paramA, Parameter *paramB, Nid algorithm);

/** doxygen needed
*/
LIBSPEC_CKM
int PKCryptParam_GetAlgBitLen(PKCryptParam *param);
/** doxygen needed
*/
LIBSPEC_CKM
int PublicKey_GetRsaBitLen(PublicKeyInfo *pubKey);

/** doxygen needed
*/
LIBSPEC_CKM
int PKCryptPubKey_GetRsaBitLen(PKCryptPubKey *pubKey);




#define ER_CKM_SIG_OUT_OF_RANGE -1001
#define ER_CKM_PLAIN_TOO_LONG   -1002
#define ER_CKM_WRONG_CIPHER_LEN -1003
#define ER_CKM_ALG_MISMATCH     -1004

/** @ingroup CKM_PKCRYPT
    @brief 메시지를 서명한다.
    @param sig [out] DER-encoding 된 서명 결과가 저장될 ASNBuf 포인터의 포인터
    @param sigAlg [out] 서명 알고리즘 Nid
    @param msg [in] 서명할 메시지가 저장된 바이트 버퍼의 포인터
    @param msgLen [in] 메시지의 바이트 단위 길이
    @param signerPriInfo [in] 서명자의 PrivateKeyInfo
    @param signerCert [in] 서명자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param hashAlg [in] 해쉬 알고리즘 descriptor
    @sa CKM_VerifySign CKM_Encrypt CKM_Decrypt

    메시지를 바이트 버퍼로 받아서 서명한 결과를 DER-encoding하여 생성된
    ASNBuf에 설정하여 결과를 내보낸다.

    서명자의 Certificate은 KCDSA 알고리즘을 사용할 경우에는 반드시 필요한
    입력값이다. 그 외 알고리즘은 선택적이다. 다만, Certificate에만 도메인
    파라미터가 들어 있다면, 반드시 입력값으로 주어야 할 것이다.
    
    서명에 필요한 도메인 파라미터는 signerPriInfo, signerCert, domainParam
    순으로 우선하여 검색하게 된다. 복수의 변수에 도메인 파라미터가 들어있더라도
    뒤에 것들은 무시된다. 이 세가지 변수 중에서 반드시 어느 하나 이상에는
    도메인 파라미터가 포함되어 있어야 한다.

    서명값의 출력은 각 알고리즘 별로 DER-encoding하여 ASNBuf 형태로 출력한다.
    또한, 서명한 알고리즘 Nid로 함께 출력한다.
    ASNBuf는 함수 내부에서 메모리에 할당되므로, 사용이 끝나는 시점에서
    반드시 ASNBuf_Del을 사용하아 메모리를 헤제하여야 한다. 
*/
LIBSPEC_CKM
ERT CKM_Sign( ASNBuf         **sig,
              Nid             *sigAlg,
              BYTE            *msg,
              BWT              msgLen,
              PrivateKeyInfo  *signerPriInfo,
              Certificate     *signerCert,
              Parameter       *domainParam,
              AlgDesc          hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief 서명을 검증한다.
    @param sig [in] DER-encoding 된 서명값이 저장된 ASNBuf의 포인터
    @param msg [in] 서명되었던 메시지가 저장된 바이트 버퍼의 포인터
    @param msgLen [in] 메시지의 바이트 단위 길이
    @param signerCert [in] 서명자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param sigAlg [in] 서명 알고리즘 Nid
    @retval SUCCESS 검증 성공
    @retval FAIL 검증 실패
    @retval ER_CKM_SIG_OUT_OF_RANGE 서명값이 범위를 벗어남
    @retval ER_CKM_ALG_MISMATCH 서명 알고리즘과 공개키 알고리즘의 불일치
    @sa CKM_Sign CKM_Encrypt CKM_Decrypt

    서명값과 서명 대상인 메시지를 받아서 서명값이 올바른지 검증하여,
    결과를 SUCCESS, FAIL로 리턴한다.

    sigAlg는 서명 알고리즘의 Nid로 DER-encoding된 서명값이 어떠한 알고리즘으로
    서명되었는지에 대한 정보를 주는 것이다. 서명 알고리즘이란 공개키 알고리즘
    뿐만 아니라 해쉬 알고리즘과의 조합으로 나타나므로, 반드시 주어져야 하는
    값이다.
*/
LIBSPEC_CKM
ERT CKM_VerifySign( ASNBuf      *sig,
                    BYTE        *msg,
                    BWT          msgLen,
                    Certificate *signerCert,
                    Parameter   *domainParam,
                    Nid          sigAlg);

LIBSPEC_CKM
ERT CKM_VerifySignEx( ASNBuf      *sig,
                    BYTE        *msg,
                    BWT          msgLen,
                    Certificate *signerCert,
                    Parameter   *domainParam,
                    Nid          sigAlg,
					Nid			 hashAlgNid);

LIBSPEC_CKM
ERT CKM_SignHash_PK (PKCryptSig      *sig,
                     Nid             *sigAlg,
                     BYTE            *hash,
                     BWT              hashLen,
                     PrivateKeyInfo  *signerPriInfo,
                     Certificate     *signerCert,
                     Parameter       *domainParam,
                     AlgDesc          hashAlg);

LIBSPEC_CKM
ERT CKM_SignHash( ASNBuf         **sig,
                  Nid             *sigAlg,
                  BYTE            *hash,
                  BWT              hashLen,
                  PrivateKeyInfo  *signerPriInfo,
                  Certificate     *signerCert,
                  Parameter       *domainParam,
                  AlgDesc          hashAlg);

LIBSPEC_CKM
ERT CKM_VerifySignHash_PK( PKCryptSig  *sig,
                           BYTE        *hash,
                           BWT          hashLen,
                           Certificate *signerCert,
                           Parameter   *domainParam,
                           Nid          sigAlg);

LIBSPEC_CKM
ERT CKM_VerifySignHash( ASNBuf      *sig,
                        BYTE        *hash,
                        BWT          hashLen,
                        Certificate *signerCert,
                        Parameter   *domainParam,
                        Nid          sigAlg);

/** @ingroup CKM_PKCRYPT
    @brief 메시지를 서명한다.
    @param sig [out] DER-encoding 된 서명 결과가 저장될 ASNBuf 포인터의 포인터
    @param sigAlg [out] 서명 알고리즘 Nid
    @param msg [in] 서명할 파일 포인터
    @param msgLen [in] 파일 중 서명할 부분의 바이트 단위 길이
    @param signerPriInfo [in] 서명자의 PrivateKeyInfo
    @param signerCert [in] 서명자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param hashAlg [in] 해쉬 알고리즘 descriptor
    @sa CKM_VerifySignFile

    메시지를 파일로, 원하는 길이만큼만 받아서 서명한 결과를 DER-encoding하여
    생성된 ASNBuf에 설정하여 결과를 내보낸다.

    서명자의 Certificate은 KCDSA 알고리즘을 사용할 경우에는 반드시 필요한
    입력값이다. 그 외 알고리즘은 선택적이다. 다만, Certificate에만 도메인
    파라미터가 들어 있다면, 반드시 입력값으로 주어야 할 것이다.
    
    서명에 필요한 도메인 파라미터는 signerPriInfo, signerCert, domainParam
    순으로 우선하여 검색하게 된다. 복수의 변수에 도메인 파라미터가 들어있더라도
    뒤에 것들은 무시된다. 이 세가지 변수 중에서 반드시 어느 하나 이상에는
    도메인 파라미터가 포함되어 있어야 한다.

    서명값의 출력은 각 알고리즘 별로 DER-encoding하여 ASNBuf 형태로 출력한다.
    또한, 서명한 알고리즘 Nid로 함께 출력한다.
    ASNBuf는 함수 내부에서 메모리에 할당되므로, 사용이 끝나는 시점에서
    반드시 ASNBuf_Del을 사용하아 메모리를 헤제하여야 한다. 
*/
LIBSPEC_CKM
ERT CKM_SignFile( ASNBuf         **sig,
                  Nid             *sigAlg,
                  FILE            *msg,
                  BWT              msgLen,
                  PrivateKeyInfo  *signerPriInfo,
                  Certificate     *signerCert,
                  Parameter       *domainParam,
                  AlgDesc          hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief 서명을 검증한다.
    @param sig [in] DER-encoding 된 서명값이 저장된 ASNBuf의 포인터
    @param msg [in] 서명되었던 파일 포인터
    @param msgLen [in] 파일 중 서명 대상이었던 데이터의 바이트 단위 길이
    @param signerCert [in] 서명자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param sigAlg [in] 서명 알고리즘 Nid
    @retval SUCCESS 검증 성공
    @retval FAIL 검증 실패
    @retval ER_CKM_SIG_OUT_OF_RANGE 서명값이 범위를 벗어남
    @retval ER_CKM_ALG_MISMATCH 서명 알고리즘과 공개키 알고리즘의 불일치
    @sa CKM_SignFile

    서명값과 서명 대상인 파일을 받아서 서명값이 올바른지 검증하여,
    결과를 SUCCESS, FAIL로 리턴한다.

    sigAlg는 서명 알고리즘의 Nid로 DER-encoding된 서명값이 어떠한 알고리즘으로
    서명되었는지에 대한 정보를 주는 것이다. 서명 알고리즘이란 공개키 알고리즘
    뿐만 아니라 해쉬 알고리즘과의 조합으로 나타나므로, 반드시 주어져야 하는
    값이다.
*/
LIBSPEC_CKM
ERT CKM_VerifySignFile( ASNBuf      *sig,
                        FILE        *msg,
                        BWT          msgLen,
                        Certificate *signerCert,
                        Parameter   *domainParam,
                        Nid          sigAlg);

/** @ingroup CKM_PKCRYPT
    @brief 공개키 알고리즘으로 암호화한다.
    @param cipher [out] 암호문이 저장될 바이트 버퍼의 포인터
    @param cipherLen [out] 암호문의 바이트 단위 길이
    @param encAlg [out] 암호화 알고리즘 Nid
    @param plain [in] 암호화할 대상인 평문의 바이트 버퍼의 포인터
    @param plainLen [in] 평문의 바이트 단위 길이
    @param recpCert [in] 암호문을 받게 될 수신자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param hashAlg [in] 해쉬 알고리즘 descriptor
    @retval ER_CKM_PLAIN_TOO_LONG 암호화 대상인 평문의 길이가 제한을 초과
    @sa CKM_Decrypt CKM_Sign CKM_VerifySign

    수신자의 인증서(recpCErt)에 들어 있는 공개키로 주어진 평문을 암호화
    하여 결과를 출력한다. 그 외 파라미터에 대한 사항은 CKM_Sign과 CKM_Verify를
    참조하기 바란다.
*/
LIBSPEC_CKM
ERT CKM_Encrypt( BYTE        *cipher,
                 BWT         *cipherLen,
                 Nid         *encAlg,
                 BYTE        *plain,
                 BWT          plainLen,
                 Certificate *recpCert,
                 Parameter   *domainParam,
                 AlgDesc      hashAlg);

LIBSPEC_CKM
ERT CKM_EncryptEx( BYTE                *cipher,
                   BWT                 *cipherLen,
                   AlgorithmIdentifier *encAlg,
                   BYTE                *plain,
                   BWT                  plainLen,
                   Certificate         *recpCert,
                   Parameter           *domainParam,
                   AlgDesc              hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief 공개키 알고리즘으로 복호화한다.
    @param plain [out] 평문이 저장될 바이트 버퍼의 포인터
    @param plainLen [out] 평문의 바이트 단위 길이
    @param cipher [in] 복고화할 대상인 암호문의 바이트 버퍼의 포인터
    @param cipherLen [in] 암호문의 바이트 단위 길이
    @param recpPriInfo [in] 암호문을 받은 수신자의 PrivateKeyInfo
    @param recpCert [in] 암호문을 받은 수신자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param encAlg [in] 암호화 알고리즘 Nid
    @retval ER_CKM_WRONG_CIPHER_LEN 암호문의 길이가 잘못되었음
    @retval ER_CKM_ALG_MISMATCH 서명 알고리즘과 공개키 알고리즘의 불일치
    @sa CKM_Encrypt CKm_Sign CKm_VerifySign

    수신자의 비공개키(recpPriInfo)로 암호문을 복호화하여 결과를 출력한다.
    그 외 파라미터에 대한 사항은 CKM_Sign과 CKM_Verify를 참고하라.
*/
LIBSPEC_CKM
ERT CKM_Decrypt( BYTE           *plain,
                 BWT            *plainLen,
                 BYTE           *cipher,
                 BWT             cipherLen,
                 PrivateKeyInfo *recpPriInfo,
                 Certificate    *recpCert,
                 Parameter      *domainParam,
                 Nid             encAlg);

LIBSPEC_CKM
ERT CKM_DecryptEx( BYTE                *plain,
                   BWT                 *plainLen,
                   BYTE                *cipher,
                   BWT                  cipherLen,
                   PrivateKeyInfo      *recpPriInfo,
                   Certificate         *recpCert,
                   Parameter           *domainParam,
                   AlgorithmIdentifier *encAlg);

/** @ingroup CKM_PKCRYPT
 * 공개키를 이용하여 데이터를 공개키 암호화 한다.
 *
 * @param *cipher       (Out) 암호문이 저장될 바이트 버퍼의 포인터
 * @param *cipherLen    (Out) 암호문의 바이트 단위 길이
 * @param *encAlg       (Out) 암호화 알고리즘 Nid
 * @param *plain        (In)  암호화할 대상인 평문의 바이트 버퍼의 포인터
 * @param plainLen      (In)  평문의 바이트 단위 길이
 * @param recpPubKey    (In)  암호문을 받게 될 수신자의 공개키
 * @param *domainParam  (In)  도메인 파라미터(추후 확장성을 위한 값으로 현재 사용되지 않음)
 * @param hashAlg       (In)  공개키 암호화에 사용될 해쉬 알고리즘 descriptor
 * @return ER_CKM_PLAIN_TOO_LONG
 * @see CKM_Encrypt CKM_Decrypt
 */
LIBSPEC_CKM
ERT CKM_EncryptByPublicKeyInfo( BYTE          *cipher,
                                BWT           *cipherLen,
                                Nid           *encAlg,
                                BYTE          *plain,
                                BWT            plainLen,
                                PublicKeyInfo *recpPubKey,
                                Parameter     *domainParam,
                                AlgDesc        hashAlg);

LIBSPEC_CKM
ERT CKM_EncryptByPublicKeyInfoEx( BYTE                *cipher,
                                  BWT                 *cipherLen,
                                  AlgorithmIdentifier *encAlg,
                                  BYTE                *plain,
                                  BWT                  plainLen,
                                  PublicKeyInfo       *recpPubKey,
                                  Parameter           *domainParam,
                                  AlgDesc              hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief 공개키를 이용하여 서명을 검증한다.
    @param sig          [in] DER-encoding 된 서명값이 저장된 ASNBuf의 포인터
    @param msg          [in] 서명되었던 메시지가 저장된 바이트 버퍼의 포인터
    @param msgLen       [in] 메시지의 바이트 단위 길이
    @param signerPubKey [in] 서명을 검증하기 위한 서명자의 공개키
    @param domainParam  [in] 도메인 파라미터
    @param sigAlg       [in] 서명 알고리즘 Nid
    @retval SUCCESS 검증 성공
    @retval FAIL 검증 실패
    @retval ER_CKM_SIG_OUT_OF_RANGE 서명값이 범위를 벗어남
    @retval ER_CKM_ALG_MISMATCH 서명 알고리즘과 공개키 알고리즘의 불일치
    @sa CKM_Sign CKM_Encrypt CKM_Decrypt

    서명값과 서명 대상인 메시지를 받아서 서명값이 올바른지 검증하여,
    결과를 SUCCESS, FAIL로 리턴한다.

    sigAlg는 서명 알고리즘의 Nid로 DER-encoding된 서명값이 어떠한 알고리즘으로
    서명되었는지에 대한 정보를 주는 것이다. 서명 알고리즘이란 공개키 알고리즘
    뿐만 아니라 해쉬 알고리즘과의 조합으로 나타나므로, 반드시 주어져야 하는
    값이다.

    KCDSA에서는 kcdsa public info 생성을 위해 서명자의 Cetificate를 필요로 
    하나 여기에서는 null data에 대한 hash값을 생성하여 대신한다.

*/
LIBSPEC_CKM
ERT CKM_VerifySignByPublicKeyInfo( ASNBuf        *sig,
                                   BYTE          *msg,
                                   BWT            msgLen,
                                   PublicKeyInfo *signerPubKey,
                                   Parameter     *domainParam,
                                   Nid            sigAlg);

/** @ingroup CKM_PKCRYPT
    @brief 메시지를 서명한다.
    @param sig [out] DER-encoding 된 서명 결과가 저장될 ASNBuf 포인터의 포인터
    @param sigAlg [out] 서명 알고리즘 Nid
    @param msg [in] 서명할 메시지가 저장된 바이트 버퍼의 포인터
    @param msgLen [in] 메시지의 바이트 단위 길이
    @param signerPriInfo [in] 서명자의 PrivateKeyInfo
    @param signerPubInfo [in] 서명자의 PublicKeyInfo
    @param domainParam [in] 도메인 파라미터
    @param hashAlg [in] 해쉬 알고리즘 descriptor
    @sa CKM_VerifySign CKM_Encrypt CKM_Decrypt

    메시지를 바이트 버퍼로 받아서 서명한 결과를 DER-encoding하여 생성된
    ASNBuf에 설정하여 결과를 내보낸다.

    서명에 필요한 도메인 파라미터는 signerPriInfo, signerPubInfo, domainParam
    순으로 우선하여 검색하게 된다. 복수의 변수에 도메인 파라미터가 들어있더라도
    뒤에 것들은 무시된다. 이 세가지 변수 중에서 반드시 어느 하나 이상에는
    도메인 파라미터가 포함되어 있어야 한다.

    서명값의 출력은 각 알고리즘 별로 DER-encoding하여 ASNBuf 형태로 출력한다.
    또한, 서명한 알고리즘 Nid로 함께 출력한다.
    ASNBuf는 함수 내부에서 메모리에 할당되므로, 사용이 끝나는 시점에서
    반드시 ASNBuf_Del을 사용하아 메모리를 헤제하여야 한다. 

    서명자의 공개키는 KCDSA1 알고리즘을 사용할 경우에는 반드시 필요한 입력값이다.
    KCDSA에서는 kcdsa public info 생성을 위해 서명자의 Cetificate를 필요로 
    하나 여기에서는 null data에 대한 hash값을 생성하여 대신한다.
*/
LIBSPEC_CKM
ERT CKM_SignByPublicKeyInfo( ASNBuf         **sig,
                             Nid             *sigAlg,
                             BYTE            *msg,
                             BWT              msgLen,
                             PrivateKeyInfo  *signerPriInfo,
                             PublicKeyInfo   *signerPubInfo,
                             Parameter       *domainParam,
                             AlgDesc          hashAlg);

enum {
  ER_KEYPAIR_INVALID_PARAM = -200,
  ER_KEYPAIR_INVALID_KEYALG,
  ER_KEYPAIR_CANNOT_GEN_KEY,
  ER_KEYPAIR_CANNOT_GEN_PRIKEY_INFO,
  ER_KEYPAIR_CANNOT_GEN_PUBKEY_INFO
};

/** @ingroup CKM_PKCRYPT
 * 키 쌍을 생성한다.
 *
 * @param **ppPubKeyInfo  (Out) 생성된 공개키
 * @param **ppPriKeyInfo  (Out) 생성된 비공개키
 * @param *pDomainParam   (In)  KCDSA와 DSA 키를 생성할 때 사용되는 도메인 변수,
 *                              NULL인 경우 내부적으로 도메인 변수를 생성하여 키를 생성한다.
 * @param nidPKAlg        (In)  생성할 공개키의 알고리즘
 * @param nPubKeyLen      (In)  키 길이
 *
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int CKM_GenKeyPair(PublicKeyInfo  **ppPubKeyInfo,
                   PrivateKeyInfo **ppPriKeyInfo,
                   Parameter       *pDomainParam,
                   Nid              nidPkOrSigAlg,
                   int              nPubKeyLen);

/** @ingroup CKM_PKCRYPT
 * 키 쌍을 생성한다.
 *
 * @param **ppPubKeyInfo  (Out) 생성된 공개키
 * @param **ppPriKeyInfo  (Out) 생성된 비공개키
 * @param *pDomainParam   (In)  KCDSA와 DSA 키를 생성할 때 사용되는 도메인 변수,
 *                              NULL인 경우 내부적으로 도메인 변수를 생성하여 키를 생성한다.
 * @param nidPKAlg        (In)  생성할 공개키의 알고리즘
 * @param nPubKeyLen      (In)  키 길이
 * @param inputVal        (In)  user input value
 * @param inputLen        (In)  user input value length
 *
 * @return 
 *  - SUCCESS : 성공
 */

LIBSPEC_CKM
int CKM_GenKeyPair_UDK(PublicKeyInfo  **ppPubKeyInfo,
											 PrivateKeyInfo **ppPriKeyInfo,
											 Parameter       *pDomainParam,
											 Nid              nidPkOrSigAlg,
											 int              nPubKeyLen,
											 BYTE						 *inputVal,
											 BWT							inputLen);

/** @ingroup CKM_PKCRYPT
 * 공개키와 비공개키 키쌍이 일치하는지 확인한다.
 *
 * @param *pubKeyInfo (In) 키 쌍이 일치하는지 확인할 공개키
 * @param *priKeyInfo (In) 키 쌍이 일치하는지 확인할 비공개키
 * @param *param      (In) 도메인 파라미터
 *
 * @return 
 *  - SUCCESS : 키쌍 일치 
 *  - 그외     : 실패
 */
LIBSPEC_CKM
ERT CKM_CheckKeyPair(PublicKeyInfo   *pubKeyInfo,
                     PrivateKeyInfo  *priKeyInfo,
                     Parameter       *param);

/** @ingroup CKM_PKCRYPT
 * DER-encoding하지 않은 서명값을 생성하여 메시지를 서명한다.
 */

LIBSPEC_CKM
ERT CKM_Sign2(ASNBuf         **sig,
              ASNBuf         **sig2,
              Nid             *sigAlg,
              BYTE            *msg,
              BWT              msgLen,
              PrivateKeyInfo  *signerPriInfo,
              Certificate     *signerCert,
              Parameter       *domainParam,
              AlgDesc          hashAlg);

/** @ingroup CKM_PKCRYPT
 * DER-encoding하지 않은 서명값을 이용하여 메시지를 검증한다.
 */

LIBSPEC_CKM
ERT CKM_VerifySign2(ASNBuf      *sig,
                    ASNBuf      *sig2,
                    BYTE        *msg,
                    BWT          msgLen,
                    Certificate *signerCert,
                    Parameter   *domainParam,
                    Nid          sigAlg);

/** @ingroup CKM_PKCRYPT
 * DER-encoding하지 않은 서명값을 생성한다.
 */

LIBSPEC_CKM
ASNBuf* Sig_Encode2(ASNBuf **sig2, PKCryptSig *pkcSig);

/** @ingroup CKM_PKCRYPT
 * DER-encoding하지 않은 서명값을 생성한다.
 */

LIBSPEC_CKM
ERT Sig_Decode2(PKCryptSig *pkcSig, ASNBuf *sigBuf, ASNBuf *sigBuf2, Nid pkAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief 내부타입인 PKCryptSig와 비표준이기는 하나 일반적으로 쓰이는 단순 바이트열간의 전환함수 
    @param buffer [out] 변환된 결과가 저장될 버퍼를 가리키는 포인터
    @param bufferByteLen [out] 사용된 버퍼의 길이
    @param alg [out] 알고리즘
    @param sig [in] 변환할 구조체
    @retval SUCCESS/FAIL

    이렇게 변환된 바이트 열은 최소한의 서명값으로 사용할 수 있다.
*/
LIBSPEC_CKM
ERT PKCryptSigToByteArray(       BYTE       *buffer,
                                 BWT        *bufferByteLen,
                                 AlgDesc    *alg,
                           const PKCryptSig *sig);

/** @ingroup CKM_PKCRYPT
    @brief 내부타입인 PKCryptSig와 비표준이기는 하나 일반적으로 쓰이는 byte arra
    y간의 전환함수 
    @param sig [out] 변환된 구조체
    @param buffer [in] 변환할 바이트 열
    @param bufferByteLen [in] 변환할 바이트 열의 길이
    @param alg [in] 알고리즘 (NULL can be given) 
    @retval SUCCESS/FAIL
*/
LIBSPEC_CKM
ERT PKCryptSigFromByteArray(       PKCryptSig  *sig,
                             const BYTE        *buffer,
                                   BWT          bufferByteLen,
                                   AlgDesc      alg);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptSig를 단순 바이트열로 변환한다.
    @param pkcSig [in] PKCryptSig 인스턴스의 포인터
    @ret 단순 바이트열로된 결과를 저장하고 있는 ASNBuf의 포인터를 리턴.
         실패할 경우 NULL을 리턴.
    @sa Sig_DecodeRawBytes

    PKCRYPT 모듈의 서명값을 의미하는 구조체인 PKCryptSig를 각 알고리즘별
    관행에 따라 바이트열로 변환하여 이값을 생선된 ASNBuf에
    저장하여 그 포인터를 리턴한다.

    리턴된 ASNBuf는 함수 내부에서 메모리에 할당되므로 사용이
    끝나는 시점에서 반드시 ASNBuf_Del로 메모리를 해제하여야 한다.
*/

LIBSPEC_CKM
ASNBuf* Sig_EncodeRawBytes( PKCryptSig *pkcSig);

/** @ingroup CKM_PKCRYPT
    @brief 된 서명값을 단순 바이트열로 담은 ASNBuf를 변환 한다.
    @param pkcSig [out] PKCryptSig 인스턴스의 포인터
    @param sigBuf [in] 단순 바이트열로된 서명값을 담은 ASNBuf의 포인터
    @param pkAlgOrSigAlg 서명 알고리즘 혹은 공개키 알고리즘의 Nid
    @ret SUCCESS, FAIL
    @sa Sig_EncodeRawBytes

    서명값이 저장된 ASNBuf와 서명 알고리즘 혹은 공개키 알고리즘 Nid를
    입력받아 PKCryptSig를 설정한다. PKCryptSig는 PKCryptPriKey,
    PKCryptPubKey와는 달리 메모리 할당, 해제가 필요없는 인스턴스이다.
*/
LIBSPEC_CKM
ERT Sig_DecodeRawBytes( PKCryptSig *pkcSig, ASNBuf *sigBuf, Nid pkAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief 메시지를 서명한다.
    @param sig [out] 단순 바이트 열로된 서명 결과가 저장될 ASNBuf 포인터
    @param sigAlg [out] 서명 알고리즘 Nid
    @param msg [in] 서명할 메시지가 저장된 바이트 버퍼의 포인터
    @param msgLen [in] 메시지의 바이트 단위 길이
    @param signerPriInfo [in] 서명자의 PrivateKeyInfo
    @param signerCert [in] 서명자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param hashAlg [in] 해쉬 알고리즘 descriptor
    @sa CKM_VerifySignRaw CKM_VerifySign CKM_Encrypt CKM_Decrypt CKM_Sign

    메시지를 바이트 버퍼로 받아서 서명한 결과를 하여 생성된
    ASNBuf에 설정하여 결과를 내보낸다.

    서명자의 Certificate은 KCDSA 알고리즘을 사용할 경우에는 반드시 필요한
    입력값이다. 그 외 알고리즘은 선택적이다. 다만, Certificate에만 도메인
    파라미터가 들어 있다면, 반드시 입력값으로 주어야 할 것이다.
    
    서명에 필요한 도메인 파라미터는 signerPriInfo, signerCert, domainParam
    순으로 우선하여 검색하게 된다. 복수의 변수에 도메인 파라미터가 들어있더라도
    뒤에 것들은 무시된다. 이 세가지 변수 중에서 반드시 어느 하나 이상에는
    도메인 파라미터가 포함되어 있어야 한다.

    서명값의 출력은 각 알고리즘 별로 표준은 아니지만 광범위하게 쓰이는 단순
    바이트열로 만들어서 ASNBuf 형태로 출력한다.
    또한, 서명한 알고리즘 Nid로 함께 출력한다.
    ASNBuf는 함수 내부에서 메모리에 할당되므로, 사용이 끝나는 시점에서
    반드시 ASNBuf_Del을 사용하아 메모리를 헤제하여야 한다. 
*/
LIBSPEC_CKM
ERT CKM_SignRawBytes( ASNBuf         **sig,
                      Nid             *sigAlg,
                      BYTE            *msg,
                      BWT              msgLen,
                      PrivateKeyInfo  *signerPriInfo,
                      Certificate     *signerCert,
                      Parameter       *domainParam,
                      AlgDesc          hashAlg);

LIBSPEC_CKM
ERT CKM_SignRawBytesEx( ASNBuf         **sig,
                        Nid             *sigAlg,
                        BYTE            *msg,
                        BWT              msgLen,
                        PrivateKeyInfo  *signerPriInfo,
                        PublicKeyInfo   *signerPubInfo,
                        Parameter       *domainParam,
                        AlgDesc          hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief 서명을 검증한다.
    @param sig [in] 단순 바이트 열로된 서명값이 저장된 ASNBuf의 포인터
    @param msg [in] 서명되었던 메시지가 저장된 바이트 버퍼의 포인터
    @param msgLen [in] 메시지의 바이트 단위 길이
    @param signerCert [in] 서명자의 Certificate
    @param domainParam [in] 도메인 파라미터
    @param sigAlg [in] 서명 알고리즘 Nid
    @retval SUCCESS 검증 성공
    @retval FAIL 검증 실패
    @retval ER_CKM_SIG_OUT_OF_RANGE 서명값이 범위를 벗어남
    @retval ER_CKM_ALG_MISMATCH 서명 알고리즘과 공개키 알고리즘의 불일치
    @sa CKM_SignRaw CKM_Sign CKM_Encrypt CKM_Decrypt

    서명값과 서명 대상인 메시지를 받아서 서명값이 올바른지 검증하여,
    결과를 SUCCESS, FAIL로 리턴한다.

    sigAlg는 서명 알고리즘의 Nid로 단순 바이트 열로된 서명값이 어떠한 
    알고리즘으로 서명되었는지에 대한 정보를 주는 것이다. 
    서명 알고리즘이란 공개키 알고리즘
    뿐만 아니라 해쉬 알고리즘과의 조합으로 나타나므로, 반드시 주어져야 하는
    값이다.
*/
LIBSPEC_CKM
ERT CKM_VerifySignRawBytes( ASNBuf      *sig,
                            BYTE        *msg,
                            BWT          msgLen,
                            Certificate *signerCert,
                            Parameter   *domainParam,
                            Nid          sigAlg);

LIBSPEC_CKM
ERT 
CKM_VerifySignRawBytesByPublicKeyInfo(
        ASNBuf      *sig,
        BYTE        *msg,
        BWT          msgLen,
        PublicKeyInfo *signerPubKey,
        Parameter   *domainParam,
        Nid          sigAlg
        );

LIBSPEC_CKM
int CKM_GetCurveFromNid(Nid namedCurve);

LIBSPEC_CKM
Nid CKM_GetNidFromCurve(int curve);

#ifdef __cplusplus
}
#endif
        
#endif /* _CKM_PKCRYPT_H */

