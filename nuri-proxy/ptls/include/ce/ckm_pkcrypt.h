#ifndef _CKM_PKCRYPT_H_
#define _CKM_PKCRYPT_H_

/** @defgroup CKM_PKCRYPT CKM PKC Wrapper
 * @ingroup CKM
    @brief ����Ű ��ȣ �ý��ۿ� ���õ� Ÿ��, �Լ�

    ����Ű ��ȣ �ý����� �����Ű, ����Ű, ������ �Ķ����, ���� �
    ���� ASN.1 sytax�� �����ϰ�, PKCRYPT����� �� Ÿ�Ե����
    ��ȯ �Լ��� �����Ѵ�.
*/

/** @ingroup CKM_PKCRYPT
    @file ckm_pkcrypt.h
    @brief CKM_PKCRYPT ����� �������̽� ����
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

/* 2005/8/5 �Ӹ�ö �븮�� ��û�� ���� �ٸ� ��ü�� ������ PKCS#7 
�޽��� ���� ������ ������ draft���� ǥ�ؿ��� pkAlg�� hashAlg�� 
�����ص� �����ϴ� ���� �˰ԵǾ� �̸� ����ϱ� ���� 
  1. AlgNid_CheckPKAlg�� AlgNid_CheckPKAlg__�� �̸��� �ٲٰ� ��� 
  2. AlgNid_CheckPKAlg�� 
     AlgNid_CheckPKAlg__(algNid) || AlgNid_CheckSigAlg(algNid)
     �� ���� �����ϰ� 
  3. AlgNid_GetSigAlgNid��   if (AlgNid_CheckSigAlg(pkAlg))
     return pkAlg; �κ��� �� �տ� �߰��Ѵ�.
������
*/

/**
 *  �־��� �˰��� Nid�� ��ĪŰ �˰����� Nid���� Ȯ���Ѵ�. 
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
    @brief �ش� ����Ű �˰��� Nid�� ����
    @param pkAlg [in] ����Ű �˰��� descriptor
    @ret �ش� ����Ű �˰����� Nid�� ����
         �Է°��� �߸��Ǿ��ų� �ش�Ǵ� �˰����� ������ 0�� ����
    @sa AlgNid_GetPKAlgDesc AlgDesc_GetHashAlgNid AlgDesc_GetSigAlgNid

    ����Ű �˰��� descriptor�� ��ġ�ϴ� Nid�� �����Ѵ�.
    Nid�� oid.h�� ���ǵǾ� ������, Object Identifier�� �ǹ��ϴ�
    ���̴�.

    �ݴ��, ����Ű �˰��� Nid�κ��� descriptor�� ��������,
    AlgNid_GetPKAlgDesc �Լ��� ����Ѵ�.
*/
LIBSPEC_CKM
Nid AlgDesc_GetPKAlgNid(AlgDesc pkAlg);

/** @ingroup CKM_PKCRYPT
    @brief �ش� �ؽ� �˰��� Nid�� ����
    @param hashAlg [in] �ؽ� �˰��� descriptor
    @ret �ش� �ؽ� �˰����� Nid�� ����
         �Է°��� �߸��Ǿ��ų� �ش� Nid�� ������ 0�� ����
    @sa AlgNid_GetHashAlgDesc AlgDesc_GetPKAlgNid AlgDesc_GetSigAlgNid

    �ؽ� �˰��� descriptor�� ��ġ�ϴ� Nid�� �����Ѵ�.
    
    �ݴ��, �ؽ� �˰��� Nid�κ��� descriptor�� ��������,
    AlgNid_GetHashAlgDesc �Լ��� ����Ѵ�.
*/
LIBSPEC_CKM
Nid AlgDesc_GetHashAlgNid(AlgDesc hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief �ش� ���� �˰��� Nid�� ����
    @param pkAlg [in] ����Ű �˰��� descriptor
    @param hashAlg [in] �ؽ� �˰��� descriptor
    @ret �ش� ���� �˰����� Nid�� ����
         �Է°��� �߸��Ǿ��ų� �ش� Nid�� ������ 0�� ����
    @sa AlgDesc_GetPKAlgDesc AlgDesc_GetHashAlgNid

    ���� �˰����� ����Ű �˰���� ����� ���� �ؽ� �˰�����
    �������� �����ȴ�. ����Ű �˰��� descriptor�� �ؽ� �˰���
    descriptor�� �Է� �޾� ���� �˰����� Nid�� �����Ѵ�.
*/
LIBSPEC_CKM
Nid AlgDesc_GetSigAlgNid(AlgDesc pkAlg,  AlgDesc hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief �ش� ����Ű �˰��� descriptor�� ����
    @param pkAlgOrSigAlg [in] ����Ű �˰��� Ȥ�� ���� �˰��� Nid
    @ret �ش� ����Ű �˰��� descriptor�� ����
         �Է°��� �߸��Ǿ��ų� �ش� descriptor�� ������ NULL�� ����
    @sa AlgDesc_GetPKAlgNid AlgNid_GetHashAlgDesc AlgNid_GetSigAlgNid

    ����Ű �˰��� Ȥ�� ���� �˰��� Nid�κ��� �ش� ����Ű �˰���
    descriptor�� ���Ѵ�.
 */
LIBSPEC_CKM
AlgDesc AlgNid_GetPKAlgDesc(Nid pkAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief �ش� �ؽ� �˰��� descriptor�� ����
    @param hashAlgOrSigAlg [in] �ؽ� �˰��� Ȥ�� ���� �˰��� Nid
    @ret �ش� �ؽ� �˰��� descriptor�� ����
         �Է°��� �߸��Ǿ��ų� �ش� descriptor�� ������ NULL�� ����
    @sa AlgDesc_GetHashAlgNid AlgNid_GetPKAlgDesc AlgNid_GetSigAlgNid

    �ؽ� �˰��� Ȥ�� ���� �˰��� Nid�κ��� �ش� �ؽ� �˰���
    descriptor�� ���Ѵ�.
*/
LIBSPEC_CKM
AlgDesc AlgNid_GetHashAlgDesc(Nid hashAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief �ش� ���� �˰��� Nid�� ����
    @param pkAlg [in] ����Ű �˰��� Nid
    @param hashAlg [in] �ؽ� �˰��� Nid
    @ret �ش� ����Ű �˰��� descriptor�� ����
         �Է°��� �߸��Ǿ��ų� �ش� Nid�� ������ 0�� ����
    @sa AlgDesc_GetSigAlgNid AlgNid_GetPKAlgDesc AlgNid_GetHashAlgNid

    ���� �˰����� ����Ű �˰���� ����� ���� �ؽ� �˰�����
    �������� �����ȴ�.  ����Ű �˰���� �ؽ� �˰��� Nid�κ���
    ���� �˰��� Nid�� ���Ѵ�.
*/
LIBSPEC_CKM
Nid AlgNid_GetSigAlgNid(Nid pkAlg, Nid hashAlg);

/** @ingroup CKM_PKCRYPT
    @biref BCIPHER���� ����ϱ� ���� ��ĪŰ �˰��� NID�κ��� AlgDesc���� mode���� ���Ѵ�.
    @param nidSymmAlg [in]  ��ĪŰ �˰����� ��Ÿ���� NID
    @param pMode     [out] ��ĪŰ mode( MODE_ECB, MODE_CBC, ...), mode���� �ʿ� ���� ������ NULL�� �Է�
    @ret ��ĪŰ �˰��� descriptor, Nid�� �Է°��� �߸��Ǿ��ų�, �ش� �˰����� ������ 0�� ����
*/
LIBSPEC_CKM
AlgDesc AlgNid_GetSymmAlgDesc(Nid nidSymmAlg, BYTE *pMode);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPubKey�� DER-encoding �Ѵ�.
    @param pubKey [in] PKCryptPubKey ����ü ��Ʈ������ ������
    @ret encoding�� ���� ���� ASNBuf�� �����͸� ����
         ���н� NULL�� ����
    @sa PublicKey_Decode PrivateKey_Encode PrivateKey_Decode

    PKCRYPT ����� ����Ű ����ü�� PKCryptPubKey�� �� �˰���
    ASN.1 syntax�� ���� DER-encoding�Ͽ� �̰��� ������ ASNBuf��
    �����Ͽ� �� �����͸� �����Ѵ�.

    ���ϵ� ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ� �����
    ������ �������� �ݵ�� ASNBuf_Del�� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
ASNBuf* PublicKey_Encode(PKCryptPubKey *pubKey);

/** @ingroup CKM_PKCRYPT
    @brief DER-encoding�� ����Ű���۸� decoding�Ͽ� PKCryptPubKey�� �����Ѵ�.
    @param pubKeyBuf [in] encoding�� ����Ű�� ���� ASNBuf�� ������
    @param pkAlg [in] ����Ű �˰����� Nid
    @ret ������ PKCryptPubKey�� �����͸� ����
         �������� �ʴ� �˰����̰ų� decoding�� ���н� NULL�� ����
    @sa PublicKey_Encode PrivateKey_Encode PrivateKey_Decode

    DER-encoding�� ����Ű�� ����� ASNBuf�� �� Ű�� �˰��� Nid��
    �Է¹޾� PKCRYPT ����� ����Ű ����ü�� PKCryptPubKey�� ����,
    �����Ͽ� �� �����͸� �����Ѵ�.

    ���ϵ� PKCryptPubKey�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ� �����
    ������ �������� �ݵ�� PKCRYPT_DelPubKey�� �޸𸮸� �����Ͽ���
    �Ѵ�.
*/
LIBSPEC_CKM
PKCryptPubKey* PublicKey_Decode(ASNBuf *pubKeyBuf, Nid pkAlg);

LIBSPEC_CKM
PKCryptPubKey* PublicKey_Decode_EC(ASNBuf *pubKeyBuf, Nid pkAlg,
		PKCryptParam *param);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPriKey�� DER-encoding �Ѵ�.
    @param priKey [in] PKCryptPriKey ����ü �ν��Ͻ��� ������
    @ret encoding�� ���� ���� ASNBuf�� �����͸� ����
         ���н� NULL�� ����
    @sa PrivateKey_Decode PublicKey_Encode PublicKey_Decode
    
    PKCRYPT ����� �����Ű ����ü�� PKCryptPriKey�� �� �˰���
    ASN.1 syntax�� ���� DER-encoding�Ͽ� �̰��� ������ ASNBuf��
    �����Ͽ� �� �����͸� �����Ѵ�.

    ���ϵ� ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ� �����
    ������ �������� �ݵ�� ASNBuf_Del�� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
ASNBuf* PrivateKey_Encode(PKCryptPriKey *priKey);

/** @ingroup CKM_PKCRYPT
    @brief ECC�� ����Ű�� DER-encoding �Ѵ�.
    @param priKey [in] PKCryptPriKey ����ü �ν��Ͻ��� ������
    @param pubKey [in] PKCryptPubKey ����ü �ν��Ͻ��� ������ or NULL
    @param param [in] PKCryptParam ����ü �ν��Ͻ��� ������ or NULL
    @ret encoding�� ���� ���� ASNBuf�� �����͸� ����
         ���н� NULL�� ����
    @sa PrivateKey_Decode_EC PublicKey_Encode PublicKey_Decode_ex
    
    PKCRYPT ����� �����Ű ���� ����ü���� ECC �˰�����
    ASN.1 syntax�� ���� DER-encoding�Ͽ� �̰��� ������ ASNBuf��
    �����Ͽ� �� �����͸� �����Ѵ�.
    
    pubKey �� param �Ķ���Ϳ� NULL�� �Ѱ��� ��쿡�� PrivateKey��
    publicKey�� curveName�� �������� �ʴ´�.

    ���ϵ� ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ� �����
    ������ �������� �ݵ�� ASNBuf_Del�� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
ASNBuf* PrivateKey_Encode_EC(PKCryptPriKey *priKey, PKCryptPubKey *pubKey, PKCryptParam *param);

/** @ingroup CKM_PKCRYPT
    @brief DER-encoding�� �����Ű ���۸� decoding�Ͽ� PKCryptPriKey�� �����Ѵ�.
    @param priKeyBuf [in] encoding�� �����Ű�� ���� ASNBuf�� ������
    @param pkAlg [in] �����Ű �˰����� Nid
    @ret ������ PKCryptPriKey�� �����͸� ����
         �������� �ʴ� �˰����̰ų� decoding�� ���н� NULL�� ����
    @sa PrivateKey_Encode PublicKey_Encode PublicKey_Decode
    
    DER-encoding�� �����Ű�� ����� ASNBuf�� �� Ű�� �˰��� Nid��
    �Է¹޾� PKCRYPT ����� �����Ű ����ü�� PKCryptPriKey�� ����,
    �����Ͽ� �� �����͸� �����Ѵ�.

    ���ϵ� PKCryptPriKey�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ� �����
    ������ �������� �ݵ�� PKCRYPT_DelPriKey�� �޸𸮸� �����Ͽ���
    �Ѵ�.
*/
LIBSPEC_CKM
PKCryptPriKey* PrivateKey_Decode(ASNBuf *priKeyBuf, Nid pkAlg);

/** @ingroup CKM_PKCRYPT
    @brief DER-encoding�� �����Ű ���۸� decoding�Ѵ�.
    @param priKey [out] PKCryptPriKey �ν��Ͻ��� �����͸� ���� ������
    @param pubKey [out] PKCryptPubKey �ν��Ͻ��� �����͸� ���� ������
    @param param [out] PKCryptParam �ν��Ͻ��� �����͸� ���� ������
    @param priKeyBuf [in] encoding�� �����Ű�� ���� ASNBuf�� ������
    @param pkAlg [in] �����Ű �˰����� Nid
    @ret SUCCESS, FAIL
    @sa PrivateKey_Encode_EC PublicKey_Encode PublicKey_Decode_ex
    
    DER-encoding�� �����Ű�� ����� ASNBuf�� �� Ű�� �˰��� Nid��
    �Է¹޾� PKCRYPT ����� �����Ű ����ü�� PKCryptPriKey�� Optional
    ���� PKCryptPubKey, PKCryptParam�� �����Ͽ� �� �����͸� �����ϰ�
    ����� �����Ѵ�.

    ���ϵ� PKCryptPriKey, PKCryptPubKey, PKCryptParam �� �Լ� ���ο���
    �޸𸮿� �Ҵ�ǹǷ� ����� ������ �������� �ݵ�� PKCRYPT_DelPriKey��
    �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
PKCryptPriKey* PrivateKey_Decode_EC(ASNBuf *priKeyBuf, Nid pkAlg,
		PKCryptPubKey **pubKey, PKCryptParam **param);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptSig�� DER-encoding �Ѵ�.
    @param pkcSig [in] PKCryptSig �ν��Ͻ��� ������
    @ret DER-encoding�� ����� �����ϰ� �ִ� ASNBuf�� �����͸� ����.
         encoding�� ������ ��� NULL�� ����.
    @sa Sig_Decode

    PKCRYPT ����� ������ �ǹ��ϴ� ����ü�� PKCryptSig�� �� �˰���
    ASN.1 syntax�� ���� DER-encoding�Ͽ� �̰��� ������ ASNBuf��
    �����Ͽ� �� �����͸� �����Ѵ�.

    ���ϵ� ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ� �����
    ������ �������� �ݵ�� ASNBuf_Del�� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
ASNBuf* Sig_Encode( PKCryptSig *pkcSig);

/** @ingroup CKM_PKCRYPT
    @brief DER-encoding�� ������ ���� ASNBuf�� decoding �Ѵ�.
    @param pkcSig [out] PKCryptSig �ν��Ͻ��� ������
    @param sigBuf [in] encoding�� ������ ���� ASNBuf�� ������
    @param pkAlgOrSigAlg ���� �˰��� Ȥ�� ����Ű �˰����� Nid
    @ret SUCCESS, FAIL
    @sa Sig_Encode

    ������ ����� ASNBuf�� ���� �˰��� Ȥ�� ����Ű �˰��� Nid��
    �Է¹޾� PKCryptSig�� �����Ѵ�. PKCryptSig�� PKCryptPriKey,
    PKCryptPubKey�ʹ� �޸� �޸� �Ҵ�, ������ �ʿ���� �ν��Ͻ��̴�.
*/
LIBSPEC_CKM
ERT Sig_Decode( PKCryptSig *pkcSig, ASNBuf *sigBuf, Nid pkAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPriKey�κ��� PrivateKeyInfo�� �����Ѵ�.
    @param priKey [in] PKCryptPriKey �ν��Ͻ��� ������
    @param param [in] PKCryptParam �ν��Ͻ��� ������ or NULL
    @ret ������ PrivateKeyInfo �ν��Ͻ��� �����͸� ����, ���н� NULL�� ����
    @sa PKCryptPriKey_New PublicKeyInfo_New PKCryptPubKey_New

    PrivateKeyInfo�� DER-encoding�� �����Ű�� ���� �˰��� OID,
    �׿� ���� ������ �Ķ���͵��� ���� �� �ִ� ASN.1 ����ü�̴�.

    �� �Լ��� PKCRYPT ����� �����Ű�� ������ �Ķ���� ����ü��
    PKCryptPriKey, PKCryptParam�� �Է����� �޾� PrivateKeyInfo��
    ����, �����Ͽ� �� �����͸� �����Ѵ�. param �Ķ���Ϳ� NULL��
    �Ѱ��� ��쿡�� PrivateKeyInfo�� ������ �Ķ���ʹ� ��������
    �ʴ´�.

    ���ϵ� PrivateKeyInfo�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�
    ����� ������ �������� �ݵ�� ASN_Del�� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
PrivateKeyInfo* PrivateKeyInfo_New( PKCryptPriKey  *priKey,
                                    PKCryptParam   *param);

LIBSPEC_CKM
PrivateKeyInfo* PrivateKeyInfo_New_RSAPSS( PKCryptPriKey *priKey, AlgDesc hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief ECC ����Ű�κ��� PrivateKeyInfo�� �����Ѵ�.
    @param priKey [in] PKCryptPriKey �ν��Ͻ��� ������
    @param pubKey [in] PKCryptPubKey �ν��Ͻ��� ������ or NULL
    @param param [in] PKCryptParam �ν��Ͻ��� ������ or NULL
    @ret ������ PrivateKeyInfo �ν��Ͻ��� �����͸� ����, ���н� NULL�� ����
    @sa PKCryptPriKey_New PublicKeyInfo_New PKCryptPubKey_New PKCryptParam_New

    PrivateKeyInfo�� DER-encoding�� �����Ű�� ���� �˰��� OID,
    �׿� ���� ������ �Ķ���͵��� ���� �� �ִ� ASN.1 ����ü�̴�.

    �� �Լ��� PKCRYPT ����� �����Ű�� ������ �Ķ���� ����ü��
    PKCryptPriKey, PKCryptPubKey, PKCryptParam�� �Է����� �޾�
    PrivateKeyInfo�� ����, �����Ͽ� �� �����͸� �����Ѵ�. pubKey��
    param �Ķ���Ϳ� NULL�� �Ѱ��� ��쿡�� PrivateKey�� publicKey��
    curveName�� �������� �ʴ´�.

    ���ϵ� PrivateKeyInfo�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�
    ����� ������ �������� �ݵ�� ASN_Del�� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
PrivateKeyInfo* PrivateKeyInfo_New_EC( PKCryptPriKey  *priKey,
                                       PKCryptPubKey  *pubKey,
                                       PKCryptParam   *param);

/** @ingroup CKM_PKCRYPT
    @brief PrivateKeyInfo�� attributes�� ������ �����Ѵ�.
    @param param [in] PrivateKeyInfo_New���� ������ PrivateKeyInfo �ν��Ͻ��� ������
    @ret ������ ����� PrivateKeyInfo �ν��Ͻ��� �����͸� ����
    @sa PKCryptPubKey_New PrivateKeyInfo_New PKCryptPriKey_New

*/
LIBSPEC_CKM
PrivateKeyInfo* PrivateKeyInfo_New2(PrivateKeyInfo  *priInfo);

/** @ingroup CKM_PKCRYPT
    @brief PrivateKeyInfo�κ��� PKCryptPriKey�� �����Ѵ�.
    @param param [out] PKCryptParam �ν��Ͻ��� ������ ������ ������ or NULL
    @param priInfo [in] PrivateKeyInfo �ν��Ͻ��� ������
    @ret ������ PKCryptPriKey �ν��Ͻ��� �����͸� ����
         �������� �ʴ� �˰����̰ų� decoding�� ���н� NULL�� ���� 
    @sa PriavateKeyInfo_New PublicKeyInfo_New PKCryptPubKey_New

    �����Ű�� ������ ��� �ִ� ASN.1 ����ü�� PrivateKeyInfo �κ���
    PKCRYPT ����� PKCryptPriKey, PKCryptParam �� ����, �����Ͽ�
    �����Ѵ�. param �Ķ���Ϳ��� NULL���� �Ѱ� �� �� ������,
    �׷� ��쿡�� PKCryptParam�� �������� �ʴ´�.

    ���ϵ� PKCryptPriKey�� PKCryptParam�� �Լ� ���ο��� �޸𸮿�
    �Ҵ�ǹǷ� ����� ������ �������� �ݵ�� ASN_Del�� �޸𸮸�
    �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
PKCryptPriKey* PKCryptPriKey_New(PKCryptParam         **param,
                                 const PrivateKeyInfo  *priInfo);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPriKey�� �����͸� �����Ѵ�.
    @param priKey [in] PKCryptPriKey �ν��Ͻ��� ������
    @ret ������ PrivateKeyInfo �ν��Ͻ��� �����͸� ����, ���н� NULL�� ����
    @sa PKCryptPriKey_New PublicKeyInfo_New PKCryptPubKey_New

    PrivateKeyInfo �� ASN.1 Ÿ������ ME ����� ASN_Del�� ����Ͽ�,
    �޸𸮿� �Ҵ�� ������ �����ϰ� �ȴ�. �׷���, �޸𸮿� ������ ����
    ��������� ������ ��� �����ϹǷ� ���Ȼ��� ������ �� �� �ִ�.
    ����, ASN_Del�� �����ϱ� ��, �޸� ������ �����͸� �����ϴ� ����
    �ٶ����ϴ�. �� ������ �����ϴ� �Լ��̴�.
*/
LIBSPEC_CKM
void PrivateKeyInfo_Wipe( PrivateKeyInfo *priInfo);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptPubKey�κ��� PublicKeyInfo�� �����Ѵ�.
    @param priKey [in] PKCryptPubKey �ν��Ͻ��� ������
    @param param [in] PKCryptParam �ν��Ͻ��� ������ or NULL
    @ret ������ PublicKeyInfo �ν��Ͻ��� �����͸� ����, ���н� NULL�� ����
    @sa PKCryptPubKey_New PrivateKeyInfo_New PKCryptPriKey_New
    
    PublicKeyInfo�� DER-encoding�� ����Ű�� ���� �˰��� OID,
    �׿� ���� ������ �Ķ���͵��� ���� �� �ִ� ASN.1 ����ü�̴�.

    �� �Լ��� PKCRYPT ����� ����Ű�� ������ �Ķ���� ����ü��
    PKCryptPubKey, PKCryptParam�� �Է����� �޾� PublicKeyInfo��
    ����, �����Ͽ� �� �����͸� �����Ѵ�. param �Ķ���Ϳ� NULL��
    �Ѱ��� ��쿡�� PrivateKeyInfo�� ������ �Ķ���ʹ� ��������
    �ʴ´�.

    ���ϵ� PublicKeyInfo�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�
    ����� ������ �������� �ݵ�� ASN_Del�� �޸𸮸� �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
PublicKeyInfo* PublicKeyInfo_New( PKCryptPubKey  *pubKey,
                                  PKCryptParam   *param);

LIBSPEC_CKM
PublicKeyInfo* PublicKeyInfo_New_RSAPSS( PKCryptPubKey *pubKey, AlgDesc hashAlg);

/** @ingroup CKM_PKCRYPT
    @brief PublicKeyInfo�κ��� PKCryptPubKey�� �����Ѵ�.
    @param param [out] PKCryptParam �ν��Ͻ��� ������ ������ ������ or NULL
    @param pubInfo [in] PublicKeyInfo �ν��Ͻ��� ������
    @ret ������ PKCryptPubKey �ν��Ͻ��� �����͸� ����
         �������� �ʴ� �˰����̰ų� decoding�� ���н� NULL�� ���� 
    @sa PublicKeyInfo_New PrivateKeyInfo_New PKCryptPriKey_New
    
    ����Ű�� ������ ��� �ִ� ASN.1 ����ü�� PublicKeyInfo �κ���
    PKCRYPT ����� PKCryptPubKey, PKCryptParam �� ����, �����Ͽ�
    �����Ѵ�. param �Ķ���Ϳ��� NULL���� �Ѱ� �� �� ������,
    �׷� ��쿡�� PKCryptParam�� �������� �ʴ´�.

    ���ϵ� PKCryptPubKey�� PKCryptParam�� �Լ� ���ο��� �޸𸮿�
    �Ҵ�ǹǷ� ����� ������ �������� �ݵ�� ASN_Del�� �޸𸮸�
    �����Ͽ��� �Ѵ�.
*/
LIBSPEC_CKM
PKCryptPubKey* PKCryptPubKey_New( PKCryptParam  **param,
                                  PublicKeyInfo  *pubInfo);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptParam���κ��� Parameter�� �����Ѵ�.
    @param pkcParam[in] PKCryptParam �ν��Ͻ��� ������
    @ret ������ Paramter �ν��Ͻ��� �����͸� ����, ���н� NULL�� ����
    @sa PKCryptParam_New

    Paramter ����ü�� ����Ű �˰����� ������ �Ķ���͸� �ǹ��ϴ� ������
    ASN.1 base type ���� �ϳ��� ANY Ÿ���� �״�� ������ �ϰ� �ִ�. 
    ANY Ÿ���� AlgorithmIdentifier��� ASN.1 ����ü�� parameters ������
    Ÿ���̴�. �� �������� ���� ������ �Ķ���Ͱ� encoding�� ���·� ����ǰ�
    �Ǵµ�, �� �Լ������� ������ �Ķ���͸� encoding�Ͽ� ANY Ÿ�� ����ü��
    �״�� �����ϴ� ���̴�.

    ���ϵǴ� Parameter �ν��Ͻ��� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�,
    ����� ������ �������� �ݵ�� ASN_Del�� �޸𸮸� �����ϱ� �ٶ���.
    Ȥ��, �ٸ� ASN.1 ����ü�� ������ �� �����͸� �Ѱ��� ��쿡��
    �����̴�.
*/
LIBSPEC_CKM
Parameter* Parameter_New(PKCryptParam *pkcParam);

/** @ingroup CKM_PKCRYPT
    @brief Parameter�κ��� PKCryptParam�� �����Ѵ�.
    @param param[in] Paramter �ν��Ͻ��� ������
    @param pkAlgOrSigAlg[in] ���� Ȥ�� ����Ű �˰����� Nid
    @ret ������ PKCryptParam �ν��Ͻ��� �����͸� ����
         �������� �ʴ� �˰����̰ų� decoding ���н� NULL�� ����
    @sa Paramter_New

    Parameter ����ü�κ��� ������ �Ķ���͸� decoding�Ͽ� PKCRYPT �����
    PKCryptParam�� ����, �����Ͽ� �� �����͸� �����Ѵ�.

    �̸��ϵǴ� PKCryptParam �ν��Ͻ��� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�,
    ����� ������ �������� �ݵ�� PKCRYPT_DelParam���� �޸𸮸� �����Ͽ���
    �Ѵ�.
*/
LIBSPEC_CKM
PKCryptParam* PKCryptParam_New(const Parameter *param, Nid pkAlgOrSigAlg);


/** doxygen needed
*/
LIBSPEC_CKM
int Parameter_GetAlgBitLen(Parameter *param);

/** @ingroup CKM_PKCRYPT
 *  @brief �ΰ��� ������ �Ķ������ ������ ������ ���Ѵ�.
 *
 * ASNInt�� ���� ó�� ���� ������ ���� ���� ���� ���� �ΰ��� ������
 * �Ķ���Ͱ� �ٸ� �������� ���ڵ��Ǵ� ��찡 �߻��Ѵ�.  �̸� ����
 * ���� ���ڵ��Ͽ� ���� ������ ���Ͽ� �Ǵ��ϵ��� �Ѵ�
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
    @brief �޽����� �����Ѵ�.
    @param sig [out] DER-encoding �� ���� ����� ����� ASNBuf �������� ������
    @param sigAlg [out] ���� �˰��� Nid
    @param msg [in] ������ �޽����� ����� ����Ʈ ������ ������
    @param msgLen [in] �޽����� ����Ʈ ���� ����
    @param signerPriInfo [in] �������� PrivateKeyInfo
    @param signerCert [in] �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param hashAlg [in] �ؽ� �˰��� descriptor
    @sa CKM_VerifySign CKM_Encrypt CKM_Decrypt

    �޽����� ����Ʈ ���۷� �޾Ƽ� ������ ����� DER-encoding�Ͽ� ������
    ASNBuf�� �����Ͽ� ����� ��������.

    �������� Certificate�� KCDSA �˰����� ����� ��쿡�� �ݵ�� �ʿ���
    �Է°��̴�. �� �� �˰����� �������̴�. �ٸ�, Certificate���� ������
    �Ķ���Ͱ� ��� �ִٸ�, �ݵ�� �Է°����� �־�� �� ���̴�.
    
    ���� �ʿ��� ������ �Ķ���ʹ� signerPriInfo, signerCert, domainParam
    ������ �켱�Ͽ� �˻��ϰ� �ȴ�. ������ ������ ������ �Ķ���Ͱ� ����ִ���
    �ڿ� �͵��� ���õȴ�. �� ������ ���� �߿��� �ݵ�� ��� �ϳ� �̻󿡴�
    ������ �Ķ���Ͱ� ���ԵǾ� �־�� �Ѵ�.

    ������ ����� �� �˰��� ���� DER-encoding�Ͽ� ASNBuf ���·� ����Ѵ�.
    ����, ������ �˰��� Nid�� �Բ� ����Ѵ�.
    ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ������ ��������
    �ݵ�� ASNBuf_Del�� ����Ͼ� �޸𸮸� �����Ͽ��� �Ѵ�. 
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
    @brief ������ �����Ѵ�.
    @param sig [in] DER-encoding �� ������ ����� ASNBuf�� ������
    @param msg [in] ����Ǿ��� �޽����� ����� ����Ʈ ������ ������
    @param msgLen [in] �޽����� ����Ʈ ���� ����
    @param signerCert [in] �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param sigAlg [in] ���� �˰��� Nid
    @retval SUCCESS ���� ����
    @retval FAIL ���� ����
    @retval ER_CKM_SIG_OUT_OF_RANGE ������ ������ ���
    @retval ER_CKM_ALG_MISMATCH ���� �˰���� ����Ű �˰����� ����ġ
    @sa CKM_Sign CKM_Encrypt CKM_Decrypt

    ������ ���� ����� �޽����� �޾Ƽ� ������ �ùٸ��� �����Ͽ�,
    ����� SUCCESS, FAIL�� �����Ѵ�.

    sigAlg�� ���� �˰����� Nid�� DER-encoding�� ������ ��� �˰�������
    ����Ǿ������� ���� ������ �ִ� ���̴�. ���� �˰����̶� ����Ű �˰���
    �Ӹ� �ƴ϶� �ؽ� �˰������ �������� ��Ÿ���Ƿ�, �ݵ�� �־����� �ϴ�
    ���̴�.
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
    @brief �޽����� �����Ѵ�.
    @param sig [out] DER-encoding �� ���� ����� ����� ASNBuf �������� ������
    @param sigAlg [out] ���� �˰��� Nid
    @param msg [in] ������ ���� ������
    @param msgLen [in] ���� �� ������ �κ��� ����Ʈ ���� ����
    @param signerPriInfo [in] �������� PrivateKeyInfo
    @param signerCert [in] �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param hashAlg [in] �ؽ� �˰��� descriptor
    @sa CKM_VerifySignFile

    �޽����� ���Ϸ�, ���ϴ� ���̸�ŭ�� �޾Ƽ� ������ ����� DER-encoding�Ͽ�
    ������ ASNBuf�� �����Ͽ� ����� ��������.

    �������� Certificate�� KCDSA �˰����� ����� ��쿡�� �ݵ�� �ʿ���
    �Է°��̴�. �� �� �˰����� �������̴�. �ٸ�, Certificate���� ������
    �Ķ���Ͱ� ��� �ִٸ�, �ݵ�� �Է°����� �־�� �� ���̴�.
    
    ���� �ʿ��� ������ �Ķ���ʹ� signerPriInfo, signerCert, domainParam
    ������ �켱�Ͽ� �˻��ϰ� �ȴ�. ������ ������ ������ �Ķ���Ͱ� ����ִ���
    �ڿ� �͵��� ���õȴ�. �� ������ ���� �߿��� �ݵ�� ��� �ϳ� �̻󿡴�
    ������ �Ķ���Ͱ� ���ԵǾ� �־�� �Ѵ�.

    ������ ����� �� �˰��� ���� DER-encoding�Ͽ� ASNBuf ���·� ����Ѵ�.
    ����, ������ �˰��� Nid�� �Բ� ����Ѵ�.
    ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ������ ��������
    �ݵ�� ASNBuf_Del�� ����Ͼ� �޸𸮸� �����Ͽ��� �Ѵ�. 
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
    @brief ������ �����Ѵ�.
    @param sig [in] DER-encoding �� ������ ����� ASNBuf�� ������
    @param msg [in] ����Ǿ��� ���� ������
    @param msgLen [in] ���� �� ���� ����̾��� �������� ����Ʈ ���� ����
    @param signerCert [in] �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param sigAlg [in] ���� �˰��� Nid
    @retval SUCCESS ���� ����
    @retval FAIL ���� ����
    @retval ER_CKM_SIG_OUT_OF_RANGE ������ ������ ���
    @retval ER_CKM_ALG_MISMATCH ���� �˰���� ����Ű �˰����� ����ġ
    @sa CKM_SignFile

    ������ ���� ����� ������ �޾Ƽ� ������ �ùٸ��� �����Ͽ�,
    ����� SUCCESS, FAIL�� �����Ѵ�.

    sigAlg�� ���� �˰����� Nid�� DER-encoding�� ������ ��� �˰�������
    ����Ǿ������� ���� ������ �ִ� ���̴�. ���� �˰����̶� ����Ű �˰���
    �Ӹ� �ƴ϶� �ؽ� �˰������ �������� ��Ÿ���Ƿ�, �ݵ�� �־����� �ϴ�
    ���̴�.
*/
LIBSPEC_CKM
ERT CKM_VerifySignFile( ASNBuf      *sig,
                        FILE        *msg,
                        BWT          msgLen,
                        Certificate *signerCert,
                        Parameter   *domainParam,
                        Nid          sigAlg);

/** @ingroup CKM_PKCRYPT
    @brief ����Ű �˰������� ��ȣȭ�Ѵ�.
    @param cipher [out] ��ȣ���� ����� ����Ʈ ������ ������
    @param cipherLen [out] ��ȣ���� ����Ʈ ���� ����
    @param encAlg [out] ��ȣȭ �˰��� Nid
    @param plain [in] ��ȣȭ�� ����� ���� ����Ʈ ������ ������
    @param plainLen [in] ���� ����Ʈ ���� ����
    @param recpCert [in] ��ȣ���� �ް� �� �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param hashAlg [in] �ؽ� �˰��� descriptor
    @retval ER_CKM_PLAIN_TOO_LONG ��ȣȭ ����� ���� ���̰� ������ �ʰ�
    @sa CKM_Decrypt CKM_Sign CKM_VerifySign

    �������� ������(recpCErt)�� ��� �ִ� ����Ű�� �־��� ���� ��ȣȭ
    �Ͽ� ����� ����Ѵ�. �� �� �Ķ���Ϳ� ���� ������ CKM_Sign�� CKM_Verify��
    �����ϱ� �ٶ���.
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
    @brief ����Ű �˰������� ��ȣȭ�Ѵ�.
    @param plain [out] ���� ����� ����Ʈ ������ ������
    @param plainLen [out] ���� ����Ʈ ���� ����
    @param cipher [in] ����ȭ�� ����� ��ȣ���� ����Ʈ ������ ������
    @param cipherLen [in] ��ȣ���� ����Ʈ ���� ����
    @param recpPriInfo [in] ��ȣ���� ���� �������� PrivateKeyInfo
    @param recpCert [in] ��ȣ���� ���� �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param encAlg [in] ��ȣȭ �˰��� Nid
    @retval ER_CKM_WRONG_CIPHER_LEN ��ȣ���� ���̰� �߸��Ǿ���
    @retval ER_CKM_ALG_MISMATCH ���� �˰���� ����Ű �˰����� ����ġ
    @sa CKM_Encrypt CKm_Sign CKm_VerifySign

    �������� �����Ű(recpPriInfo)�� ��ȣ���� ��ȣȭ�Ͽ� ����� ����Ѵ�.
    �� �� �Ķ���Ϳ� ���� ������ CKM_Sign�� CKM_Verify�� �����϶�.
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
 * ����Ű�� �̿��Ͽ� �����͸� ����Ű ��ȣȭ �Ѵ�.
 *
 * @param *cipher       (Out) ��ȣ���� ����� ����Ʈ ������ ������
 * @param *cipherLen    (Out) ��ȣ���� ����Ʈ ���� ����
 * @param *encAlg       (Out) ��ȣȭ �˰��� Nid
 * @param *plain        (In)  ��ȣȭ�� ����� ���� ����Ʈ ������ ������
 * @param plainLen      (In)  ���� ����Ʈ ���� ����
 * @param recpPubKey    (In)  ��ȣ���� �ް� �� �������� ����Ű
 * @param *domainParam  (In)  ������ �Ķ����(���� Ȯ�强�� ���� ������ ���� ������ ����)
 * @param hashAlg       (In)  ����Ű ��ȣȭ�� ���� �ؽ� �˰��� descriptor
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
    @brief ����Ű�� �̿��Ͽ� ������ �����Ѵ�.
    @param sig          [in] DER-encoding �� ������ ����� ASNBuf�� ������
    @param msg          [in] ����Ǿ��� �޽����� ����� ����Ʈ ������ ������
    @param msgLen       [in] �޽����� ����Ʈ ���� ����
    @param signerPubKey [in] ������ �����ϱ� ���� �������� ����Ű
    @param domainParam  [in] ������ �Ķ����
    @param sigAlg       [in] ���� �˰��� Nid
    @retval SUCCESS ���� ����
    @retval FAIL ���� ����
    @retval ER_CKM_SIG_OUT_OF_RANGE ������ ������ ���
    @retval ER_CKM_ALG_MISMATCH ���� �˰���� ����Ű �˰����� ����ġ
    @sa CKM_Sign CKM_Encrypt CKM_Decrypt

    ������ ���� ����� �޽����� �޾Ƽ� ������ �ùٸ��� �����Ͽ�,
    ����� SUCCESS, FAIL�� �����Ѵ�.

    sigAlg�� ���� �˰����� Nid�� DER-encoding�� ������ ��� �˰�������
    ����Ǿ������� ���� ������ �ִ� ���̴�. ���� �˰����̶� ����Ű �˰���
    �Ӹ� �ƴ϶� �ؽ� �˰������ �������� ��Ÿ���Ƿ�, �ݵ�� �־����� �ϴ�
    ���̴�.

    KCDSA������ kcdsa public info ������ ���� �������� Cetificate�� �ʿ�� 
    �ϳ� ���⿡���� null data�� ���� hash���� �����Ͽ� ����Ѵ�.

*/
LIBSPEC_CKM
ERT CKM_VerifySignByPublicKeyInfo( ASNBuf        *sig,
                                   BYTE          *msg,
                                   BWT            msgLen,
                                   PublicKeyInfo *signerPubKey,
                                   Parameter     *domainParam,
                                   Nid            sigAlg);

/** @ingroup CKM_PKCRYPT
    @brief �޽����� �����Ѵ�.
    @param sig [out] DER-encoding �� ���� ����� ����� ASNBuf �������� ������
    @param sigAlg [out] ���� �˰��� Nid
    @param msg [in] ������ �޽����� ����� ����Ʈ ������ ������
    @param msgLen [in] �޽����� ����Ʈ ���� ����
    @param signerPriInfo [in] �������� PrivateKeyInfo
    @param signerPubInfo [in] �������� PublicKeyInfo
    @param domainParam [in] ������ �Ķ����
    @param hashAlg [in] �ؽ� �˰��� descriptor
    @sa CKM_VerifySign CKM_Encrypt CKM_Decrypt

    �޽����� ����Ʈ ���۷� �޾Ƽ� ������ ����� DER-encoding�Ͽ� ������
    ASNBuf�� �����Ͽ� ����� ��������.

    ���� �ʿ��� ������ �Ķ���ʹ� signerPriInfo, signerPubInfo, domainParam
    ������ �켱�Ͽ� �˻��ϰ� �ȴ�. ������ ������ ������ �Ķ���Ͱ� ����ִ���
    �ڿ� �͵��� ���õȴ�. �� ������ ���� �߿��� �ݵ�� ��� �ϳ� �̻󿡴�
    ������ �Ķ���Ͱ� ���ԵǾ� �־�� �Ѵ�.

    ������ ����� �� �˰��� ���� DER-encoding�Ͽ� ASNBuf ���·� ����Ѵ�.
    ����, ������ �˰��� Nid�� �Բ� ����Ѵ�.
    ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ������ ��������
    �ݵ�� ASNBuf_Del�� ����Ͼ� �޸𸮸� �����Ͽ��� �Ѵ�. 

    �������� ����Ű�� KCDSA1 �˰����� ����� ��쿡�� �ݵ�� �ʿ��� �Է°��̴�.
    KCDSA������ kcdsa public info ������ ���� �������� Cetificate�� �ʿ�� 
    �ϳ� ���⿡���� null data�� ���� hash���� �����Ͽ� ����Ѵ�.
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
 * Ű ���� �����Ѵ�.
 *
 * @param **ppPubKeyInfo  (Out) ������ ����Ű
 * @param **ppPriKeyInfo  (Out) ������ �����Ű
 * @param *pDomainParam   (In)  KCDSA�� DSA Ű�� ������ �� ���Ǵ� ������ ����,
 *                              NULL�� ��� ���������� ������ ������ �����Ͽ� Ű�� �����Ѵ�.
 * @param nidPKAlg        (In)  ������ ����Ű�� �˰���
 * @param nPubKeyLen      (In)  Ű ����
 *
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int CKM_GenKeyPair(PublicKeyInfo  **ppPubKeyInfo,
                   PrivateKeyInfo **ppPriKeyInfo,
                   Parameter       *pDomainParam,
                   Nid              nidPkOrSigAlg,
                   int              nPubKeyLen);

/** @ingroup CKM_PKCRYPT
 * Ű ���� �����Ѵ�.
 *
 * @param **ppPubKeyInfo  (Out) ������ ����Ű
 * @param **ppPriKeyInfo  (Out) ������ �����Ű
 * @param *pDomainParam   (In)  KCDSA�� DSA Ű�� ������ �� ���Ǵ� ������ ����,
 *                              NULL�� ��� ���������� ������ ������ �����Ͽ� Ű�� �����Ѵ�.
 * @param nidPKAlg        (In)  ������ ����Ű�� �˰���
 * @param nPubKeyLen      (In)  Ű ����
 * @param inputVal        (In)  user input value
 * @param inputLen        (In)  user input value length
 *
 * @return 
 *  - SUCCESS : ����
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
 * ����Ű�� �����Ű Ű���� ��ġ�ϴ��� Ȯ���Ѵ�.
 *
 * @param *pubKeyInfo (In) Ű ���� ��ġ�ϴ��� Ȯ���� ����Ű
 * @param *priKeyInfo (In) Ű ���� ��ġ�ϴ��� Ȯ���� �����Ű
 * @param *param      (In) ������ �Ķ����
 *
 * @return 
 *  - SUCCESS : Ű�� ��ġ 
 *  - �׿�     : ����
 */
LIBSPEC_CKM
ERT CKM_CheckKeyPair(PublicKeyInfo   *pubKeyInfo,
                     PrivateKeyInfo  *priKeyInfo,
                     Parameter       *param);

/** @ingroup CKM_PKCRYPT
 * DER-encoding���� ���� ������ �����Ͽ� �޽����� �����Ѵ�.
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
 * DER-encoding���� ���� ������ �̿��Ͽ� �޽����� �����Ѵ�.
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
 * DER-encoding���� ���� ������ �����Ѵ�.
 */

LIBSPEC_CKM
ASNBuf* Sig_Encode2(ASNBuf **sig2, PKCryptSig *pkcSig);

/** @ingroup CKM_PKCRYPT
 * DER-encoding���� ���� ������ �����Ѵ�.
 */

LIBSPEC_CKM
ERT Sig_Decode2(PKCryptSig *pkcSig, ASNBuf *sigBuf, ASNBuf *sigBuf2, Nid pkAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief ����Ÿ���� PKCryptSig�� ��ǥ���̱�� �ϳ� �Ϲ������� ���̴� �ܼ� ����Ʈ������ ��ȯ�Լ� 
    @param buffer [out] ��ȯ�� ����� ����� ���۸� ����Ű�� ������
    @param bufferByteLen [out] ���� ������ ����
    @param alg [out] �˰���
    @param sig [in] ��ȯ�� ����ü
    @retval SUCCESS/FAIL

    �̷��� ��ȯ�� ����Ʈ ���� �ּ����� �������� ����� �� �ִ�.
*/
LIBSPEC_CKM
ERT PKCryptSigToByteArray(       BYTE       *buffer,
                                 BWT        *bufferByteLen,
                                 AlgDesc    *alg,
                           const PKCryptSig *sig);

/** @ingroup CKM_PKCRYPT
    @brief ����Ÿ���� PKCryptSig�� ��ǥ���̱�� �ϳ� �Ϲ������� ���̴� byte arra
    y���� ��ȯ�Լ� 
    @param sig [out] ��ȯ�� ����ü
    @param buffer [in] ��ȯ�� ����Ʈ ��
    @param bufferByteLen [in] ��ȯ�� ����Ʈ ���� ����
    @param alg [in] �˰��� (NULL can be given) 
    @retval SUCCESS/FAIL
*/
LIBSPEC_CKM
ERT PKCryptSigFromByteArray(       PKCryptSig  *sig,
                             const BYTE        *buffer,
                                   BWT          bufferByteLen,
                                   AlgDesc      alg);

/** @ingroup CKM_PKCRYPT
    @brief PKCryptSig�� �ܼ� ����Ʈ���� ��ȯ�Ѵ�.
    @param pkcSig [in] PKCryptSig �ν��Ͻ��� ������
    @ret �ܼ� ����Ʈ���ε� ����� �����ϰ� �ִ� ASNBuf�� �����͸� ����.
         ������ ��� NULL�� ����.
    @sa Sig_DecodeRawBytes

    PKCRYPT ����� ������ �ǹ��ϴ� ����ü�� PKCryptSig�� �� �˰���
    ���࿡ ���� ����Ʈ���� ��ȯ�Ͽ� �̰��� ������ ASNBuf��
    �����Ͽ� �� �����͸� �����Ѵ�.

    ���ϵ� ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ� �����
    ������ �������� �ݵ�� ASNBuf_Del�� �޸𸮸� �����Ͽ��� �Ѵ�.
*/

LIBSPEC_CKM
ASNBuf* Sig_EncodeRawBytes( PKCryptSig *pkcSig);

/** @ingroup CKM_PKCRYPT
    @brief �� ������ �ܼ� ����Ʈ���� ���� ASNBuf�� ��ȯ �Ѵ�.
    @param pkcSig [out] PKCryptSig �ν��Ͻ��� ������
    @param sigBuf [in] �ܼ� ����Ʈ���ε� ������ ���� ASNBuf�� ������
    @param pkAlgOrSigAlg ���� �˰��� Ȥ�� ����Ű �˰����� Nid
    @ret SUCCESS, FAIL
    @sa Sig_EncodeRawBytes

    ������ ����� ASNBuf�� ���� �˰��� Ȥ�� ����Ű �˰��� Nid��
    �Է¹޾� PKCryptSig�� �����Ѵ�. PKCryptSig�� PKCryptPriKey,
    PKCryptPubKey�ʹ� �޸� �޸� �Ҵ�, ������ �ʿ���� �ν��Ͻ��̴�.
*/
LIBSPEC_CKM
ERT Sig_DecodeRawBytes( PKCryptSig *pkcSig, ASNBuf *sigBuf, Nid pkAlgOrSigAlg);

/** @ingroup CKM_PKCRYPT
    @brief �޽����� �����Ѵ�.
    @param sig [out] �ܼ� ����Ʈ ���ε� ���� ����� ����� ASNBuf ������
    @param sigAlg [out] ���� �˰��� Nid
    @param msg [in] ������ �޽����� ����� ����Ʈ ������ ������
    @param msgLen [in] �޽����� ����Ʈ ���� ����
    @param signerPriInfo [in] �������� PrivateKeyInfo
    @param signerCert [in] �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param hashAlg [in] �ؽ� �˰��� descriptor
    @sa CKM_VerifySignRaw CKM_VerifySign CKM_Encrypt CKM_Decrypt CKM_Sign

    �޽����� ����Ʈ ���۷� �޾Ƽ� ������ ����� �Ͽ� ������
    ASNBuf�� �����Ͽ� ����� ��������.

    �������� Certificate�� KCDSA �˰����� ����� ��쿡�� �ݵ�� �ʿ���
    �Է°��̴�. �� �� �˰����� �������̴�. �ٸ�, Certificate���� ������
    �Ķ���Ͱ� ��� �ִٸ�, �ݵ�� �Է°����� �־�� �� ���̴�.
    
    ���� �ʿ��� ������ �Ķ���ʹ� signerPriInfo, signerCert, domainParam
    ������ �켱�Ͽ� �˻��ϰ� �ȴ�. ������ ������ ������ �Ķ���Ͱ� ����ִ���
    �ڿ� �͵��� ���õȴ�. �� ������ ���� �߿��� �ݵ�� ��� �ϳ� �̻󿡴�
    ������ �Ķ���Ͱ� ���ԵǾ� �־�� �Ѵ�.

    ������ ����� �� �˰��� ���� ǥ���� �ƴ����� �������ϰ� ���̴� �ܼ�
    ����Ʈ���� ���� ASNBuf ���·� ����Ѵ�.
    ����, ������ �˰��� Nid�� �Բ� ����Ѵ�.
    ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�ǹǷ�, ����� ������ ��������
    �ݵ�� ASNBuf_Del�� ����Ͼ� �޸𸮸� �����Ͽ��� �Ѵ�. 
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
    @brief ������ �����Ѵ�.
    @param sig [in] �ܼ� ����Ʈ ���ε� ������ ����� ASNBuf�� ������
    @param msg [in] ����Ǿ��� �޽����� ����� ����Ʈ ������ ������
    @param msgLen [in] �޽����� ����Ʈ ���� ����
    @param signerCert [in] �������� Certificate
    @param domainParam [in] ������ �Ķ����
    @param sigAlg [in] ���� �˰��� Nid
    @retval SUCCESS ���� ����
    @retval FAIL ���� ����
    @retval ER_CKM_SIG_OUT_OF_RANGE ������ ������ ���
    @retval ER_CKM_ALG_MISMATCH ���� �˰���� ����Ű �˰����� ����ġ
    @sa CKM_SignRaw CKM_Sign CKM_Encrypt CKM_Decrypt

    ������ ���� ����� �޽����� �޾Ƽ� ������ �ùٸ��� �����Ͽ�,
    ����� SUCCESS, FAIL�� �����Ѵ�.

    sigAlg�� ���� �˰����� Nid�� �ܼ� ����Ʈ ���ε� ������ ��� 
    �˰������� ����Ǿ������� ���� ������ �ִ� ���̴�. 
    ���� �˰����̶� ����Ű �˰���
    �Ӹ� �ƴ϶� �ؽ� �˰������ �������� ��Ÿ���Ƿ�, �ݵ�� �־����� �ϴ�
    ���̴�.
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

