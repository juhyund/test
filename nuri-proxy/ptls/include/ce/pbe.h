#ifndef _PBE_H_
#define _PBE_H_

/** @defgroup PBE Password-Based Encryption
 * @ingroup CKM
    @brief PBE(Password-Based Encryption) ���

    PBKDF(password-based key derivation func)�� �̿��Ͽ� Ű�� �����ϰ�
    �Ϻ�ȣȭ�� �����ϴ� ���
    */

/** @ingroup PBE
    @file pbe.h
    @brief PBE ����� �������̽�
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
# 2006�� 10�� 11��
# SEED �˰��� OID ����(RFC4009)
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
    @brief PBEContext�� �ʱ�ȭ�Ѵ�.

    @param pbeCtx [out] �ʱ�ȭ�� PBEContext�� ������
    @param pbeNid [in] ����� PBE scheme
    @param derPbeParam [in] PBE parameter�� ���� ASN.1 Ÿ���� ���ڵ��� ��
    @param passwd [in] PBE scheme���� ���� null-terminated string Ÿ���� password

    PBE scheme�� PKCS#5�� PKCS#12�� ���ǵǾ� �ְ�, ��ü���� ��Ŀ��������
    3���� ������ �������� �� �ִ�. ������ PBE ���ĸ��� ���� block cipher
    �˰����� ������ �� ���� ���̴�. 
    
    �̵� PBE scheme�� pbe.h�� �����Ǿ�
    ������, �̵� �� �ϳ��� pbeNid�� �Ѱ������ν�, PBEContext�� �� scheme����
    �ʱ�ȭ�ϴ� ���̴�. ���Ҿ� ������ PBE scheme�� �ʿ��� parameter����
    Parameter���� ������ ���ڵ��� ASN.1 Ÿ������ �Է¹޴´�.


    @sa PBE_Encrypt PBE_Decrypt
    */
LIBSPEC_CKM
ERT POPPBE_Initialize( PBEContext   *pbeCtx,
                    Nid           pbeNid, 
                    ASNBuf       *derPbeParam,
                    const BYTE   *passwd);

/** @ingroup PBE
    @brief PBEContext�� ������ PBE scheme���� ��ȣȭ�Ѵ�.

    @param out [out] ��ȣȭ�� �����Ͱ� ����� ������ ������
    @param outLen [out] ��ȣȭ�� �������� ����Ʈ ���� ����
    @param in [in] ��ȣȭ�� �����Ͱ� ����Ǿ� �ִ� ������ ������
    @param inLen [in] ��ȣȭ�� �������� ����Ʈ ���� ����
    @param pbeCtx [in] PBEContext

    PBEContext���� ������ PBE scheme���� ��ȣȭ�Ѵ�. out ������
    ���̴� padding������ �߰��ǹǷ� in ���ۺ��� 20����Ʈ ���� ũ��
    (��Ȯ�ϰԴ� ����ϴ� block cipher algorithm�� ��ũ��) ������
    �־� �Ѵ�.

    @sa PBE_Initialize PBE_Decrypt
    */
LIBSPEC_CKM
ERT POPPBE_Encrypt( BYTE *out, BWT *outLen,
                 BYTE *in,  BWT  inLen,
                 const PBEContext *pbeCtx);

/** @ingroup PBE
    @brief PBEContext�� ������ PBE scheme���� ��ȣȭ�Ѵ�.

    @param out [out] ��ȣȭ�� �����Ͱ� ����� ������ ������
    @param outLen [out] ��ȣȭ�� �������� ����Ʈ ���� ����
    @param in [in] ��ȣȭ�� �����Ͱ� ����Ǿ� �ִ� ������ ������
    @param inLen [in] ��ȣȭ�� �������� ����Ʈ ���� ����
    @param pbeCtx [in] PBEContext

    PBEContext���� ������ PBE scheme���� ��ȣȭ�Ѵ�. in ������
    ���̴� out ������ ���̿� �����ϸ� ����ϴ�.

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
