#ifndef _PIEX_H_
#define _PIEX_H_

/** @defgroup PIEX Private Information Exchange
 * @ingroup CKM
    @brief PIEX(Private Information EXchange) ���

    Private Infomation EXchange(PIEX) �� ���� ����̴�.
    ��ü������ PKCS#12�� PFX Ÿ�԰� PKCS#5�� PrivateKeyInfo Ÿ����
    �ٷ�� �Լ����̴�.
    */

/** @ingroup PIEX
    @file piex.h
    @brief PIEX ����� �������̽� ����
    */

#include "asn1.h"
#include "x509pkc.h"
#include "x509com.h"
#include "pkcs.h"
#include "ckm_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ER_PIEX_PFX_AUTH_FAIL -1001


/*****************************************************************************
 * PKCS8 interface
 */

/** @ingroup PIEX
    @brief PrivateKeyInfo�κ��� EncryptedPrivateKeyInfo�� �����Ѵ�.

    @param derEpki [out] DER-encoding �� ������ EncryptedPrivateKeyInfo�� ��µ� ASNBuf
    @param pki [in] encrypt�� ����� PrivateKeyInfo
    @param pbeEncAlg [in] PBE(password-based encryption) scheme
    @param passwd [in] null-terminated string Ÿ���� ��ȣ ���ڿ�
    @param salt [in] PBE scheme�� ���� salt
    @param saltLen [in] PBE scheme�� ���� salt�� ����Ʈ ���� ����
    @param iteration [in] PBE scheme�� ���� iteration

    PrivateKeyInfo�� ���ϴ� password-based encryption(PBE) scheme�� ����Ͽ�
    EncryptePrivateKeyInfo�� �����ϴ� �Լ��̴�.

    �Է� �Ķ���ͷδ� ũ�� 3������ ���� �� �ִ�. �� �Լ� ���۷��̼���
    ����� PrivateKeyInfo, �׸��� ����ϰ��� �ϴ� PBE algorithm, ����������,
    PBE algorithm�� ��ü���� ���ڵ��� salt�� iteration, password�� �װ͵��̴�.

    salt�� iteration�� ���ؼ��� PKCS#5�� �����ϱ� �ٶ���. ��κ��� ���
    PBKDF_DEFAULT_SALT�� PBKDF_DEFAULT_ITERATION�� ����ϸ� �ȴ�. (pbkdf.h�� ����)
    PBE algorithm �� pbe.h�� �����Ǿ� �ִ� Nid�� ���� �ϳ��� �� ���̴�.
    ��, �� �Լ��������� PKCS5_PBE1�� PKCS12_PBE ���� �����Ѵ�.

    PrivateKeyInfo�� EncryptedPrivateKeyInfo�� ���� �����
    PIEX_GetPKInfoFromEPKInfo�� ����Ǿ� �����Ƿ� ���� �ٶ���.

    @sa PIEX_GetPKInfoFromEPKInfo
    */
LIBSPEC_CKM
ERT PIEX_GenEPKInfoBufFromPKInfo( ASNBuf         **derEpki,
                                  PrivateKeyInfo  *pki,
                                  Nid              pbeEncAlg,
                                  const char      *passwd,
                                  const BYTE      *salt,
                                  BWT              saltLen,
                                  BWT              iteration);

/* for backward compatibility */
#define PIEX_GenEPKInfoFromPKInfo PIEX_GenEPKInfoBufFromPKInfo

LIBSPEC_CKM
ERT PIEX_GenEPKInfoAsnFromPKInfo( EncryptedPrivateKeyInfo  **epki,
                                  PrivateKeyInfo            *pki,
                                  Nid                        pbeEncAlg,
                                  const char                *passwd,
                                  const BYTE                *salt,
                                  BWT                        saltLen,
                                  BWT                        iteration);

/* for backward compatibility */
#define PIEX_GenEPKInfoFromPKInfoEx PIEX_GenEPKInfoAsnFromPKInfo

/** @ingroup PIEX
    @brief EncryptedPrivateKeyInfo�κ��� PrivateKeyInfo�� ��´�.

    @param pkinfo [out] ��µ� PrivateKeyInfo
    @param derEpki [in] DER-encoding �� ������ EncryptedPrivateKeyInfo
    @param passwd [in] null-terminated string Ÿ���� ��ȣ ���ڿ�
    
    PKCS#5�� ���ǵ� PrivateKeyInfo�� EncryptedPrivateKeyInfo�� ����
    �Լ��̴�. PIEX_GenEPKInfoFromPKInfo�� ���� �̷�� �Լ��̹Ƿ�
    PIEX_GenEPKInfoFromPKInfo�� �����ϱ� �ٶ���.

    PrivateKeyInfo�� �Ϲ����� private key�� �����ϴ� ASN.1 Ÿ���̸�,
    EncryptedPrivateKeyInfo�� PrivateKeyInfo�� ��ȣȭȭ�� ���� ������ �ִ�
    ASN.1 Ÿ���̴�. ��ȣȭ ����� password-based encryption scheme�� ������,
    �̿� ���� ǥ���� PKCS#5�� PKCS#12�� �����Ǿ� �ִ�.

    �� �Լ��� DER-encoding�� EncryptedPrivateKeyInfo�� ���� PrivateKeyInfo��
    ��� ����� �Ѵ�. EncryptedPrivateKeyInfo��, ��ȣȭ ������ password��
    �Է¹޾� EcnryptedPrivateKeyInfo�� �켱 decoding�ϸ�, �Է¹��� password��
    �������� ��ȣȭ�� PrivateKeyInfo�� ��ȣȭ�Ѵ�. ��ȣȭ�� �����ϸ�,
    PrivateKeyInfo�� �����Ϳ� �޸𸮸� �Ҵ��ϰ� ���� �����Ѵ�.
    �׷��Ƿ�, PrivateKeyInfo�� ����ϰ� ������ ASN_Del�� ����Ͽ� �Ҵ��
    �޸𸮸� �����ϵ��� �Ѵ�.

    @sa PIEX_GenEPKInfoFromPKInfo
    */
LIBSPEC_CKM
ERT PIEX_GetPKInfoFromEPKInfoBuf( PrivateKeyInfo **pkInfo,
                                  ASNBuf          *derEpki,
                                  const char      *passwd);

/* for backward compatibility */
#define PIEX_GetPKInfoFromEPKInfo PIEX_GetPKInfoFromEPKInfoBuf

LIBSPEC_CKM
ERT PIEX_GetPKInfoFromEPKInfoAsn( PrivateKeyInfo         **pkInfo,
                                  EncryptedPrivateKeyInfo *epki,
                                  const char              *passwd);

/* for backward compatibility */
#define PIEX_GetPKInfoFromEPKInfoEx PIEX_GetPKInfoFromEPKInfoAsn

LIBSPEC_CKM
PrivateKeyInfo* PIEX_GetPKInfoFromFile( const char      *filePath,
                                        const char      *passwd);

LIBSPEC_CKM
ERT PIEX_ChangeEPKInfoPasswd( EncryptedPrivateKeyInfo *epki,
                              const char              *newPasswd,
                              const char              *oldPasswd );
/** @ingroup PIEX
    @brief Secret Key ���۷κ��� EncryptedSecretKeyInfo�� �����Ѵ�.

    @param derEski [out] DER-encoding �� ������ EncryptedSecretKeyInfo�� ��µ� ASNBuf
    @param key [in] ��ȣȭ ����� secret key�� ����� ������ ������
    @param keyLen [in] secret key�� ����Ʈ ���� ����
    @param pbeEncAlg [in] PBE(password-based encryption) scheme
    @param passwd [in] null-terminated string Ÿ���� ��ȣ ���ڿ�
    @param salt [in] PBE scheme�� ���� salt
    @param saltLen [in] PBE scheme�� ���� salt�� ����Ʈ ���� ����
    @param iteration [in] PBE scheme�� ���� iteration

    secret key�� ���ϴ� password-based encryption(PBE) scheme�� ����Ͽ�
    EncrypteSecretKeyInfo�� �����ϴ� �Լ��̴�.

    �Է� �Ķ���ͷδ� ũ�� 3������ ���� �� �ִ�. �� �Լ� ���۷��̼���
    ����� secret key, �׸��� ����ϰ��� �ϴ� PBE algorithm, ����������,
    PBE algorithm�� ��ü���� ���ڵ��� salt�� iteration, password�� �װ͵��̴�.

    salt�� iteration�� ���ؼ��� PKCS#5�� �����ϱ� �ٶ���. ��κ��� ���
    PBKDF_DEFAULT_SALT�� PBKDF_DEFAULT_ITERATION�� ����ϸ� �ȴ�. (pbkdf.h�� ����)
    PBE algorithm �� pbe.h�� �����Ǿ� �ִ� Nid�� ���� �ϳ��� �� ���̴�.
    ��, �� �Լ��������� PKCS5_PBE1�� PKCS12_PBE ���� �����Ѵ�.

    @sa PIEX_GetSKeyFromESKInfo
*/
LIBSPEC_CKM
ERT PIEX_GenESKInfoFromSKey( ASNBuf     **derEski,
                             BYTE        *key,
                             BWT          keyLen,
                             Nid          pbeEncAlg,
                             const char  *passwd, 
                             const BYTE  *salt,
                             BWT          saltLen,
                             BWT          iteration);


/** @ingroup PIEX
    @brief EncryptedSecretKeyInfo�κ��� secret key�� ��´�.

    @param key [out] Secret key�� ��µ� ������ ������
    @param keyLen [out] Secret key�� ����Ʈ ���� ����
    @param derEski [in] DER-encoding �� ������ EncryptedSecretKeyInfo
    @param passwd [in] null-terminated string Ÿ���� ��ȣ ���ڿ�
    
    �� �Լ��� DER-encoding�� EncryptedSecretKeyInfo�� ���� Secret key��
    ��� ����� �Ѵ�. EncryptedSecretKeyInfo��, ��ȣȭ ������ password��
    �Է¹޾� EcnryptedSecretKeyInfo�� �켱 decoding�ϸ�, �Է¹��� password��
    �������� ��ȣȭ�� Secret Key�� ��ȣȭ�Ѵ�. ��ȣȭ�� �����ϸ�,
    �Է¹��� key ������ �����Ϳ� �� ���� �����Ѵ�.

    @sa PIEX_GenESKInfoFromSKey
    */
LIBSPEC_CKM
ERT PIEX_GetSKeyFromESKInfo( BYTE       *key,
                             BWT        *keyLen,
                             ASNBuf     *derEski,
                             const char *passwd);


/*****************************************************************************
 * PKCS12 interface - Encode PFX
 */

/** @ingroup PIEX
    @brief KeyBag�� �����Ѵ�.

    @param safeBag [out] ������ SafeBag�� �����Ͱ� ����� SafeBag�� ������ ����
    @param pkinfo  [in] PrivateKeyInfo

    KeyBag Ÿ���� SafeBag�� �����Ѵ�. ���������δ� PrivateKeyInfo��
    DER-encoding �� ���� value�� ������.
    */
LIBSPEC_CKM
ERT PIEX_GenKeyBag(
    SafeBag **safeBag, PrivateKeyInfo *pkinfo);

/** @ingroup PIEX
    @brief PKCS8ShroudedKeyBag�� �����Ѵ�.

    @param safeBag [out] ������ SafeBag�� �����Ͱ� ����� SafeBag�� ������ ����
    @param epkinfo [in] EncryptedPrivateKeyInfo

    PKCS9ShroudedKeyBag Ÿ���� SafeBag�� �����Ѵ�. EncryptedPrivateKeyInfo��
    DER-encoding �� ���� value�� ������.
    */
LIBSPEC_CKM
ERT PIEX_GenPKCS8ShroudedKeyBag(
    SafeBag **safeBag, EncryptedPrivateKeyInfo *epkinfo);

/** @ingroup PIEX
    @brief CertBag�� �����Ѵ�.

    @param safeBag [out] ������ SafeBag�� �����Ͱ� ����� SafeBag�� ������ ����
    @param certId  [in] type of Certificate
    @param cert    c[in] Certificate

    Certificate�� ��� CertBag Ÿ���� SafeBag�� �����Ѵ�.
    */
LIBSPEC_CKM
ERT PIEX_GenCertBag(
    SafeBag **safeBag, Nid certId, Certificate *cert);

/** @ingroup PIEX
    @brief CRLBag�� �����Ѵ�.

    @param safeBag [out] ������ SafeBag�� �����Ͱ� ����� SafeBag�� ������ ����
    @param crlId   [in] type of Certificate
    @param crl     [in] CRL

    CRL�� ��� CRLBag Ÿ���� SafeBag�� �����Ѵ�.
    */
LIBSPEC_CKM
ERT PIEX_GenCRLBag(
    SafeBag **safeBag, Nid crlId, CRL *crl);

LIBSPEC_CKM
/** @ingroup PIEX
    @brief SecretBag�� �����Ѵ�.

    @param safeBag   [out] ������ SafeBag�� �����Ͱ� ����� SafeBag�� ������ ����
    @param secTypeId [in] type of secret value
    @param secValue  [in] secret value

    ������ ������ ��� SecretBag Ÿ���� SafeBag�� �����Ѵ�.
    */
ERT PIEX_GenSecretBag(
    SafeBag **safeBag, Nid secTypeId, ASNBuf *secValue);

/** @ingroup PIEX
    @brief SafeContentsBag�� �����Ѵ�.

    @param safeBag [out] ������ SafeBag�� �����Ͱ� ����� SafeBag�� ������ ����
    @param sc      [in] SafeContents

    SafeContents�� ��� SafeContentsBag Ÿ���� SafeBag�� �����Ѵ�.
    */
LIBSPEC_CKM
ERT PIEX_GenSafeContentsBag(
    SafeBag **safeBag, SafeContents *sc);


/** @ingroup PIEX
    @brief SafeBag�� SafeContents�� �߰��Ѵ�.

    AuthenticateSafe�� SafeBag�� SequenceOf Ÿ���̴�. ����,
    ASN ����� ASNSeqOf_AddP �Լ��� ������ �ϴ� ������ SafeBag��
    SafeContents�� �߰��ϴ� ����� ����� �� �ִ�. ASNSeqOf_AddP
    �� �������̽��� ASN ����� ������ �����ϱ� �ٶ���.

    @sa PIEX_DelSafeBagFromSafeContents
        PIEX_GenSafeBag_Data PIEX_GenSafeBag_EncData PIEX_GenPFX
    */
#define PIEX_AddSafeBagPToSafeContents(safeContents, safeBag) \
        ASNSeqOf_AddP((ASNSeqOf*)(safeContents), (ASN*)(safeBag))

/** @ingroup PIEX
    @brief SafeBag�� SafeContents�κ��� �����Ѵ�.

    AuthenticateSafe�� SafeBag�� SequenceOf Ÿ���̴�. ����,
    ASN ����� ASNSeqOf_Remove �Լ��� ������ �ϴ� ������ SafeBag��
    SafeContents�κ��� �����ϴ� ����� ����� �� �ִ�. ASNSeqOf_Remove
    �� �������̽��� ASN ����� ������ �����ϱ� �ٶ���.
    
    @sa PIEX_AddSafeBagFromSafeContents
        PIEX_GenSafeBag_Data PIEX_GenSafeBag_EncData PIEX_GenPFX
    */
#define PIEX_DelSafeBagFromSafeContents(safeContents, index) \
        ASNSeqOf_Remove(safeContents, index)

/** @ingroup PIEX
    @brief Data type�� ContentInfo�� �����Ѵ�.

    @param cinfo [out] ������ ContentInfo�� �����Ͱ� ����� ContentInfo*�� ������
    @param sc    [in] ContentInfo�� ���� �� SafeContent

    SafeContents�� Data �������� ������ ContentInfo�� �����Ѵ�.
    �� ������ ContentInfo�� ���, SafeContents�� ������ ��ȣ���� ����
    �����̹Ƿ� private key�� ���� ��� ������ ��� �ִ� SafeContents����
    �������ϸ�, �������� ���� �������� ������ ��� ���� ��쿡 ����ϴ�
    �����̴�.

    @sa PIEX_GenContentInfo_EncData PIEX_GenPFX
    */
LIBSPEC_CKM
ERT PIEX_GenContentInfo_Data(
    ContentInfo **cinfo, SafeContents *sc);

/** @ingroup PIEX
    @brief EncryptedData type�� ContentInfo�� �����Ѵ�.

    @param cinfo     [out] ������ ContentInfo�� �����Ͱ� ����� ContentInfo*�� ������
    @param sc        [out] ContentInfo�� ���� �� SafeContent
    @param pbeEncAlg [in] PBE(password-based encryption) scheme
    @param passwd    [in] null-terminated string Ÿ���� ��ȣ ���ڿ�
    @param salt      [in] PBE scheme�� ���� salt
    @param saltLen   [in] PBE scheme�� ���� salt�� ����Ʈ ���� ����
    @param iteration [in] PBE scheme�� ���� iteration

    SafeContents�� EncryptedData �������� ������ ContentInfo�� �����Ѵ�.
    ��ȣȭ ����� password-based encryption ���� PKCS#5, PKCS#12��
    �����Ǿ� �ִ�. SafeContents�� ��ȣȭ�Ǵ� ����̹Ƿ� private key�� ����
    �����Ǿ�� �� �� ������ ���ؼ� ����ϴ� ����̴�.
    
    �Է� �Ķ���ͷδ� ũ�� 3������ ���� �� �ִ�. �� �Լ� ���۷��̼���
    ����� PrivateKeyInfo, �׸��� ����ϰ��� �ϴ� PBE algorithm, ����������,
    PBE algorithm�� ��ü���� ���ڵ��� salt�� iteration, password�� �װ͵��̴�.

    salt�� iteration�� ���ؼ��� PKCS#5�� �����ϱ� �ٶ���. ��κ��� ���
    PBKDF_DEFAULT_SALT�� PBKDF_DEFAULT_ITERATION�� ����ϸ� �ȴ�. (pbkdf.h�� ����)
    PBE algorithm �� pbe.h�� �����Ǿ� �ִ� Nid�� ���� �ϳ��� �� ���̴�.
    ��, �� �Լ��������� PKCS5_PBE1�� PKCS12_PBE ���� �����Ѵ�.

    @sa PIEX_GenContentInfo_Data PIEX_GenPFX
    */
LIBSPEC_CKM
ERT PIEX_GenContentInfo_EncData(
    ContentInfo **cinfo, SafeContents *sc,
    Nid pbeEncAlg, const char *passwd, const BYTE *salt, BWT saltLen, BWT iteration);

/** @ingroup PIEX
    @brief not implemented

    @param cinfo
    @param sc

    @sa
    */
LIBSPEC_CKM
ERT PIEX_GenContentInfo_EnvData(
    ContentInfo **cinfo, SafeContents *sc);

/** @ingroup PIEX
    @brief ContentInfo�� AuthenticatedSafe�� �߰��Ѵ�.

    AuthenticateSafe�� ContentInfo�� SequenceOf Ÿ���̴�. ����,
    ASN ����� ASNSeqOf_AddP �Լ��� ������ �ϴ� ������ ContentInfo��
    AuthenticatedSafe�� �߰��ϴ� ����� ����� �� �ִ�. ASNSeqOf_AddP
    �� �������̽��� ASN ����� ������ �����ϱ� �ٶ���.

    @sa PIEX_DelContentInfoFromAuthenticatedSafe
        PIEX_GenContentInfo_Data PIEX_GenContentInfo_EncData PIEX_GenPFX
    */
#define PIEX_AddContentInfoPToAuthenticatedSafe(authSafe, contentInfo) \
        ASNSeqOf_AddP((ASNSeqOf*)(authSafe), (ASN*)(contentInfo))

/** @ingroup PIEX
    @brief ContentInfo�� AuthenticatedSafe�κ��� �����Ѵ�.

    AuthenticateSafe�� ContentInfo�� SequenceOf Ÿ���̴�. ����,
    ASN ����� ASNSeqOf_Remove �Լ��� ������ �ϴ� ������ ContentInfo��
    AuthenticatedSafe�κ��� �����ϴ� ����� ����� �� �ִ�. ASNSeqOf_Remove
    �� �������̽��� ASN ����� ������ �����ϱ� �ٶ���.
    
    @sa PIEX_AddContentInfoFromAuthenticatedSafe
        PIEX_GenContentInfo_Data PIEX_GenContentInfo_EncData PIEX_GenPFX
    */
#define PIEX_DelContentInfoFromAuthenticatedSafe(authSafe, index) \
        ASNSeqOf_Remove(authSafe, index)


/** @ingroup PIEX
    @brief PFX�� �����Ѵ�.

    @param pfx       [out] ������ PFX�� �����Ͱ� ����� PFX�� �����ͺ���
    @param authSafe  [in] PFX�� ������ AuthenticatedSafe
    @param hashAlgId [in] HMAC�� ���� �ؽ� �˰���
    @param passwd    [in] null-terminated string Ÿ���� ��ȣ ���ڿ�
    @param salt      [in] PBE scheme�� ���� salt
    @param saltLen   [in] PBE scheme�� ���� salt�� ����Ʈ ���� ����
    @param iteration [in] PBE scheme�� ���� iteration

    PFX�� ���������� AuthenticatedSafe�� ������ ���Ἲ�� ���� MAC����
    ������ �ִ�. �� �Լ��� AuthenticatedSafe�� �Է¹޾� MAC���� ����ϰ�
    PFX�� �����Ѵ�.
    
    PKCS#12���� �����ϰ� �ִ� ���Ἲ�� ���� ��Ŀ���
    MAC �Ӹ� �ƴ϶� ���� ��ĵ� ������, �� ���(�� �Լ�)������ HMAC ���
    ���� �����Ѵ�. HMAC�� ���̴� Ű�� password-based key derivation ��
    ���� PKCS#5�� �����Ǿ� �ִ�. �ϳ��� PFX������ ContentInfo�� ������
    ���� PFX�� ������ ���� ������ password�� ����Ͽ��� �Ѵ�.

    @sa PIEX_GenContentInfo_Data PIEX_GenContentInfo_EncData
        PIEX_AddContentInfoToAuthenticatedSafe
        PIEX_DelContentInfoFromAuthenticatedSafe
    */
LIBSPEC_CKM
ERT PIEX_GenPFX(
    PFX **pfx, AuthenticatedSafe *authSafe,
    Nid hashAlgId, const char *passwd, const BYTE *salt, BWT saltLen, BWT iteration);

/** @ingroup PIEX
    @brief �����Ű�� �������� PFX�� �����Ѵ�.

    @param pfx       [out] ������ PFX�� �����Ͱ� ����� PFX�� �����ͺ���
    @param epki      [in] ��ȣȭ�� ������ �����Ű
    @param cert      [in] �����Ű�� ���� �̷�� ������
    @param caCerts   [in] ��Ÿ ���� ��ο� �ִ� ��������
    @param hashAlgId [in] HMAC�� ���� �ؽ� �˰���
    @param pbeEncAlg [in] SafeBag���� ��ȣȭ�� PBE �˰���
    @param passwd    [in] null-terminated string Ÿ���� ��ȣ ���ڿ�
    @param salt      [in] PBE scheme�� ���� salt
    @param saltLen   [in] PBE scheme�� ���� salt�� ����Ʈ ���� ����
    @param iteration [in] PBE scheme�� ���� iteration

    PFX�� ���������� AuthenticatedSafe�� ������ ���Ἲ�� ���� MAC����
    ������ �ִ�.
    �� �Լ��� �����Ű�� ���������� �Է¹޾� AuthenticatedSafe�� �����ϰ�
    MAC���� ����ϰ� PFX�� �����Ѵ�. PIEX_GenPFX�� �ٸ� ���� �����Ű��
    ��������� ���� AuthenticatedSafe�� �����Ѵٴ� ���̴�. ��,
    AuthenticatedSafe ���������� �ڵ�ȭ�ߴٰ� �� �� �ִ�.
    
    PKCS#12���� �����ϰ� �ִ� ���Ἲ�� ���� ��Ŀ���
    MAC �Ӹ� �ƴ϶� ���� ��ĵ� ������, �� ���(�� �Լ�)������ HMAC ���
    ���� �����Ѵ�. HMAC�� ���̴� Ű�� password-based key derivation ��
    ���� PKCS#5�� �����Ǿ� �ִ�. �ϳ��� PFX������ ContentInfo�� ������
    ���� PFX�� ������ ���� ������ password�� ����Ͽ��� �Ѵ�.

    @sa PIEX_GenContentInfo_Data PIEX_GenContentInfo_EncData
        PIEX_AddContentInfoToAuthenticatedSafe
        PIEX_DelContentInfoFromAuthenticatedSafe
    */
LIBSPEC_CKM
ERT PIEX_GenPFXFromKeyAndCert(
    PFX **pfx, EncryptedPrivateKeyInfo *epki, CERT *cert, CERTS *caCerts,
    Nid hashAlgId, Nid pbeEncAlg,
    const char *passwd, const BYTE *salt, BWT saltLen, BWT iteration);

LIBSPEC_CKM
ERT PIEX_GenPFXFromKeyAndCert2(
    PFX **pfx, EncryptedPrivateKeyInfo *epki1, CERT *cert1,
    EncryptedPrivateKeyInfo *epki2, CERT *cert2, CERTS *certs,
    Nid hashAlgId, Nid pbeEncAlg,
    const char *passwd, const BYTE *salt, BWT saltLen, BWT iteration);
/*****************************************************************************
 * PKCS12 interface - Decode PFX
 */

/** @ingroup PIEX
    @brief PFX�� ���ڵ��Ͽ� SafeBag ���� �����Ѵ�.

    @param safeBags [out] SafeBag�� ����Ʈ�� ����� ������
    @param numBags [out] SafeBag ����Ʈ�� ����� SafeBag�� ����
    @param passwd [in] null-terminated string Ÿ���� ��ȣ
    @param derPFX [in] DER-encoding ������ PFX ��, ASNBuf Ÿ��
    @retval ER_PIEX_PFX_AUTH_FAIL Authentication fail(invalid password)

    PFX�� PKCS#12�� ���ǵǾ� �ִ� Ÿ������ ���� ����
    (private key, certificate ���)�� �����ϰ� import/export�ϱ� ����
    �����ε� Ÿ���̴�. ���������δ� �������� SafeBag�� ������ ������,
    SafeBag�� ��ü���� ������ ��� �ȴ�.

    �� �Լ��� PFX�� ���ڵ��ϸ�, �޽����� ���Ἲ�� üũ�ϰ�, ��ȣȭ�� ��
    SafeBag�� ����Ʈ�� �����´�. �Լ� ���ο��� �޸𸮸� �Ҵ��ϹǷ� �ݵ��
    �޸𸮸� �����ϴ� ������ ���ľ� �ϸ�, �� �۾��� PIEX_DelSafeBags���
    �Լ��� ���� �̷������.

    SafeBag�� ����Ʈ�� ������ ����ü�� �ִ� ���� �ƴ϶�, SafeBag Ÿ����
    ����Ű�� �ִ� �����͵��� �迭�̴�. ������ ���� �ڵ带 ���� �ٶ���.
    (safeBag�� Ÿ�԰� ���õ� �κи��� ���)

    \code
    SafeBag **safeBags;

    PIEX_GetSafeBagsFromPFX(&safeBags, ....);
    
    safeBag[1] ...;
    safeBag[2] ...;

    PIEX_DelSafeBags(safeBags, ...);
    \endcode

    @sa PIEX_DelSafeBags
    */
LIBSPEC_CKM
ERT PIEX_GetSafeBagsFromPFX(
    SafeBag ***safeBags, int *numBags, const char *passwd, ASNBuf *derPFX);

/** @ingroup PIEX
    @brief �޸𸮿� �Ҵ�� SafeBag ����Ʈ�� free�Ѵ�.

    @param safeBags [in] SafeBag �������� ����Ʈ�� ù��° ����� ������
    @param numBags [in] SafeBag ����Ʈ�� SafeBag ����

    @sa PIEX_GetSafeBagsFromPFX
    */
LIBSPEC_CKM
void PIEX_DelSafeBags(SafeBag **safeBags, int numBags);

/** @ingroup PIEX
    @brief SafeBag�� Ÿ���� ��´�.

    @param bagId [out] Ÿ���� ����� Nid ������
    @param safeBag [in] ���� ����� SafeBag�� ������

    SafeBag�� ���ϰ� �ִ� value�� ��� Ÿ�������� �����ϴ� OID�� ������,
    ������, �� �Լ��� �� ���� Nid���·� ����Ѵ�.

    @sa PIEX_GetBagValueFromSafeBag PIEX_GetSafeBagsFromPFX PIEX_DelSafeBags
    */
LIBSPEC_CKM
ERT PIEX_GetBagIDFromSafeBag(Nid *bagId, const SafeBag *safeBag);

/** @ingroup PIEX
    @brief SafeBag�� ���� value�� ��´�.

    @param derBagVal [out] value�� ����� ASNBuf*�� ������
    @param safeBag [in] ���� ����� SafeBag�� ������

    SafeBag�� ���ϰ� �ִ� value�� �������� �Լ��̴�. ASNBuf�� �Լ����ο���
    �޸𸮿� �Ҵ��ϰ� ���� �����ϹǷ�, �Ҵ�� ASNBuf�� �ݵ�� ASNBuf_Del��
    ���ؼ� free�ؾ� �Ѵ�.

    @sa PIEX_GetBagIDFromSafeBag PIEX_GetSafeBagsFromPFX PIEX_DelSafeBags
    */
LIBSPEC_CKM
ERT PIEX_GetBagValueFromSafeBag(ASNBuf **derBagVal, const SafeBag *safeBag);


/* Manipulating the SafeBag of each types */

/* KeyBag */
/* DER-encoded PrivateKeyInfo, and doesn't need manipulating functions */

/* PKCS8ShroudedKeyBag */
/* DER-encoded EncryptedPrivateKeyInfo */

/* CertBag */
/** @ingroup PIEX
    @brief

    @param certId 
    @param certVal
    @param safeBag

    @sa
    */
LIBSPEC_CKM
ERT PIEX_GetCertFromCertBag(
    Nid *certId, ASNBuf **certVal, SafeBag *safeBag);

/* CRLBag */
/** @ingroup PIEX
    @brief

    @param crlId
    @param crlVal
    @param safeBag

    @sa
    */
LIBSPEC_CKM
ERT PIEX_GetCRLFromCertBag(
    Nid *crlId, ASNBuf **crlVal, SafeBag *safeBag);

/* SecrteBag */

/* SafeContentsBag */

#ifdef __cplusplus
}
#endif

#endif /* _PIEX_H_ */
