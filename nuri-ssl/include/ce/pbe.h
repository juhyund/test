#ifndef _PBE_H_
#define _PBE_H_

/** @defgroup PBE Password-Based Encryption
 * @ingroup CKM
    @brief PBE(Password-Based Encryption) 모듈

    PBKDF(password-based key derivation func)을 이용하여 키를 유도하고
    암복호화를 수행하는 모듈
    */

/** @ingroup PBE
    @file pbe.h
    @brief PBE 모듈의 인터페이스
    */

#include "bcipher_op.h"
#include "hash_op.h"

#include "asn1.h"
#include "oid.h"
#include "x509com.h"

#include "pbkdf.h"

#include "ckm_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
# 2006년 10월 11일
# SEED 알고리즘 OID 보정(RFC4009)
*/

const static unsigned int NID_pbeWithSHA1AndSEED_CBC = NID_seedCBCwithSHA1;

LIBSPEC_CKM
extern Oid Oid_pbeWithSHA1AndSEED_CBC;

const static unsigned int NID_pbeWithSHA256AndSEED_CBC = NID_seedCBCWithSHA256;

LIBSPEC_CKM
extern Oid Oid_pbeWithSHA256AndSEED_CBC;

#define ER_PBE_UNSUPPORTED_SCHEME         -1001
#define ER_PKCS5_PBES2_UNSUPPORTED_SCHEME -1002


/*****************************************************************************
 * PKCS5 ASN.1 types
 */

/* PBKDF 2 */
typedef struct {
  ASNChoiceClass klass;
  int select;
  union {
    OctetString *specified;
    AlgorithmIdentifier *otherSource;
  } choice;
} Salt;

LIBSPEC_CKM
extern ASNDescriptor AD_Salt;

typedef struct {
  ASNSeqClass klass;
  Salt *salt;
  Integer *iterationCount;
  Integer *keyLength; /* optional */
  AlgorithmIdentifier *prf; /* default algid-hmacWithSHA1 */
} PBKDF2_params;
  
LIBSPEC_CKM
extern ASNDescriptor AD_PBKDF2_params;

/* PBE 1 */
typedef struct {
  ASNSeqClass klass;
  OctetString *salt;
  Integer *iterationCount;
} PBEParameter;

LIBSPEC_CKM
extern ASNDescriptor AD_PBEParameter;

/* PBE 2 */
typedef struct {
  ASNSeqClass klass;
  AlgorithmIdentifier *keyDerivationFunc;
  AlgorithmIdentifier *encryptionScheme;
} PBES2_params;

LIBSPEC_CKM
extern ASNDescriptor AD_PBES2_params;


/*****************************************************************************
 * PKCS12 ASN.1 types
 */

typedef struct {
  ASNSeqClass klass;
  OctetString *salt;
  Integer *iterations;
} pkcs_12PbeParams;

LIBSPEC_CKM
extern ASNDescriptor AD_pkcs_12PbeParams;


/*****************************************************************************
 * Encryption parameter type
 */

typedef struct {
  ASNSeqClass klass;
  Integer *rc2ParameterVersion; /* optional */
  OctetString *iv; /* size(8) */
} RC2_CBC_Parameter;

LIBSPEC_CKM
extern ASNDescriptor AD_RC2_CBC_Parameter;

typedef struct {
  ASNSeqClass klass;
  Integer *version; 
  Integer *rounds; /* 8 .. 127 */
  Integer *blockSizeInBits; /* 64 | 128 */
  OctetString *iv; /* optional */
} RC5_CBC_Parameters;

LIBSPEC_CKM
extern ASNDescriptor AD_RC5_CBC_Parameters;


/*****************************************************************************
 * PBE Module Interface
 */

typedef struct {
  Nid               pbeNid;
  char              passwd[PBKDF_MAX_PASSWORD_LEN];
  BYTE              salt[PBKDF_MAX_SALT_LEN];
  BWT               saltLen;
  BWT               iteration;
  BWT               keyLen;
  HashAlgorithm    *hashAlg;
  BCipherAlgorithm *bcAlg;
  BYTE              bcOperMode;
  ERT             (*pbkdf)(); 
  BYTE              pkcs5pbe2iv[BCIPHER_MAX_IV_SIZE];
} PBEContext;


#define IsPKCS5_PBE1(nid)      (nid == NID_pbeWithMD2AndDES_CBC || \
								nid == NID_pbeWithMD2AndRC2_CBC || \
  								nid == NID_pbeWithMD5AndDES_CBC || \
  								nid == NID_pbeWithMD5AndRC2_CBC || \
  								nid == NID_pbeWithSHA1AndDES_CBC || \
  								nid == NID_pbeWithSHA1AndRC2_CBC)

#define IsPKCS5_PBE1_old(nid)  (nid == NID_pbeWithSHA1AndSEED_CBC_old || \
  								nid == NID_pbeWithSHA1AndPACA_CBC_old)

#define IsPKCS5_PBE1_npki(nid) (nid == NID_seedCBCwithSHA1 || \
								nid == NID_seedCBC || \
								nid == NID_seedCBCWithSHA256)

#define IsPKCS5_gpki(nid)	   (nid == NID_ariaCBC || nid == NID_pbewithSHA1andARIA_CBC)

#define IsPKCS5_PBE2(nid)      (nid == NID_id_PBES2)

#define IsPKCS12_PBE(nid)      (nid == NID_pbeWithSHAAnd128BitRC4 || \
  								nid == NID_pbeWithSHAAnd40BitRC4 || \
  								nid == NID_pbeWithSHAAnd3_KeyTripleDES_CBC || \
  								nid == NID_pbeWithSHAAnd2_KeyTripleDES_CBC || \
  								nid == NID_pbeWithSHAAnd128BitRC2_CBC || \
  								nid == NID_pbewithSHAAnd40BitRC2_CBC || \
  								nid == NID_pbeWithSHA1AndSEED_CBC || \
  								nid == NID_pbeWithSHA1AndSEED_CBC_old2 || \
  								nid == NID_pbeWithSHA1AndPACA_CBC || \
									nid == NID_seedCBCWithSHA256)

#define PBE_Initialize POPPBE_Initialize
#define PBE_Encrypt POPPBE_Encrypt
#define PBE_Decrypt POPPBE_Decrypt

/** @ingroup PBE
    @brief PBEContext를 초기화한다.

    @param pbeCtx [out] 초기화할 PBEContext의 포인터
    @param pbeNid [in] 사용할 PBE scheme
    @param derPbeParam [in] PBE parameter를 담은 ASN.1 타입의 인코딩된 값
    @param passwd [in] PBE scheme에서 사용될 null-terminated string 타입의 password

    PBE scheme은 PKCS#5와 PKCS#12에 정의되어 있고, 구체적인 메커니즘으로
    3가지 종류로 구분지을 수 있다. 각각의 PBE 형식마다 여러 block cipher
    알고리즘을 적용할 수 있을 것이다. 
    
    이들 PBE scheme은 pbe.h에 나열되어
    있으며, 이들 중 하나를 pbeNid에 넘겨줌으로써, PBEContext를 그 scheme으로
    초기화하는 것이다. 더불어 각각의 PBE scheme에 필요한 parameter들은
    Parameter들을 가지는 인코딩된 ASN.1 타입으로 입력받는다.


    @sa PBE_Encrypt PBE_Decrypt
    */
LIBSPEC_CKM
ERT POPPBE_Initialize( PBEContext   *pbeCtx,
                    Nid           pbeNid, 
                    ASNBuf       *derPbeParam,
                    const BYTE   *passwd);

/** @ingroup PBE
    @brief PBEContext에 지정된 PBE scheme으로 암호화한다.

    @param out [out] 암호화된 데이터가 복사될 버퍼의 포인터
    @param outLen [out] 암호화된 데이터의 바이트 단위 길이
    @param in [in] 암호화할 데이터가 저장되어 있는 버퍼의 포인터
    @param inLen [in] 암호화할 데이터의 바이트 단위 길이
    @param pbeCtx [in] PBEContext

    PBEContext에서 정해진 PBE scheme으로 암호화한다. out 버퍼의
    길이는 padding정보가 추가되므로 in 버퍼보다 20바이트 정도 크게
    (정확하게는 사용하는 block cipher algorithm의 블럭크기) 여유를
    둬야 한다.

    @sa PBE_Initialize PBE_Decrypt
    */
LIBSPEC_CKM
ERT POPPBE_Encrypt( BYTE *out, BWT *outLen,
                 BYTE *in,  BWT  inLen,
                 const PBEContext *pbeCtx);

/** @ingroup PBE
    @brief PBEContext에 지정된 PBE scheme으로 복호화한다.

    @param out [out] 암호화된 데이터가 복사될 버퍼의 포인터
    @param outLen [out] 암호화된 데이터의 바이트 단위 길이
    @param in [in] 암호화할 데이터가 저장되어 있는 버퍼의 포인터
    @param inLen [in] 암호화할 데이터의 바이트 단위 길이
    @param pbeCtx [in] PBEContext

    PBEContext에서 정해진 PBE scheme으로 복호화한다. in 버퍼의
    길이는 out 버퍼의 길이와 동일하면 충분하다.

    @sa PBE_Initialize PBE_Encrypt
    */
LIBSPEC_CKM
ERT POPPBE_Decrypt( BYTE *out, BWT *outLen,
                 BYTE *in,  BWT  inLen,
                 const PBEContext *pbeCtx);


#ifdef __cplusplus
}
#endif

#endif /* _PBE_H_ */
