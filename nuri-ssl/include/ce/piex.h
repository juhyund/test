#ifndef _PIEX_H_
#define _PIEX_H_

/** @defgroup PIEX Private Information Exchange
 * @ingroup CKM
    @brief PIEX(Private Information EXchange) 모듈

    Private Infomation EXchange(PIEX) 에 관한 모듈이다.
    구체적으로 PKCS#12의 PFX 타입과 PKCS#5의 PrivateKeyInfo 타입을
    다루는 함수들이다.
    */

/** @ingroup PIEX
    @file piex.h
    @brief PIEX 모듈의 인터페이스 정의
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
    @brief PrivateKeyInfo로부터 EncryptedPrivateKeyInfo를 생성한다.

    @param derEpki [out] DER-encoding 된 상태의 EncryptedPrivateKeyInfo가 출력될 ASNBuf
    @param pki [in] encrypt할 대상인 PrivateKeyInfo
    @param pbeEncAlg [in] PBE(password-based encryption) scheme
    @param passwd [in] null-terminated string 타입의 암호 문자열
    @param salt [in] PBE scheme에 사용될 salt
    @param saltLen [in] PBE scheme에 사용될 salt의 바이트 단위 길이
    @param iteration [in] PBE scheme에 사용될 iteration

    PrivateKeyInfo를 원하는 password-based encryption(PBE) scheme을 사용하여
    EncryptePrivateKeyInfo를 생성하는 함수이다.

    입력 파라미터로는 크게 3가지로 나눌 수 있다. 이 함수 오퍼레이션의
    대상인 PrivateKeyInfo, 그리고 사용하고자 하는 PBE algorithm, 마지막으로,
    PBE algorithm의 구체적인 인자들인 salt와 iteration, password가 그것들이다.

    salt와 iteration에 관해서는 PKCS#5를 참고하기 바란다. 대부분의 경우
    PBKDF_DEFAULT_SALT와 PBKDF_DEFAULT_ITERATION을 사용하면 된다. (pbkdf.h에 정의)
    PBE algorithm 은 pbe.h에 참조되어 있는 Nid들 중의 하나가 될 것이다.
    단, 이 함수에서만은 PKCS5_PBE1과 PKCS12_PBE 만을 지원한다.

    PrivateKeyInfo와 EncryptedPrivateKeyInfo에 대한 배경은
    PIEX_GetPKInfoFromEPKInfo에 설명되어 있으므로 참고 바란다.

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
    @brief EncryptedPrivateKeyInfo로부터 PrivateKeyInfo를 얻는다.

    @param pkinfo [out] 출력될 PrivateKeyInfo
    @param derEpki [in] DER-encoding 된 상태의 EncryptedPrivateKeyInfo
    @param passwd [in] null-terminated string 타입의 암호 문자열
    
    PKCS#5에 정의된 PrivateKeyInfo와 EncryptedPrivateKeyInfo에 대한
    함수이다. PIEX_GenEPKInfoFromPKInfo와 쌍을 이루는 함수이므로
    PIEX_GenEPKInfoFromPKInfo도 참조하기 바란다.

    PrivateKeyInfo는 일반적인 private key를 저장하는 ASN.1 타입이며,
    EncryptedPrivateKeyInfo는 PrivateKeyInfo를 암호화화한 값을 가지고 있는
    ASN.1 타입이다. 암호화 방식은 password-based encryption scheme을 따르며,
    이에 관한 표준은 PKCS#5와 PKCS#12에 규정되어 있다.

    이 함수는 DER-encoding된 EncryptedPrivateKeyInfo로 부터 PrivateKeyInfo를
    얻는 기능을 한다. EncryptedPrivateKeyInfo와, 암호화 시점의 password를
    입력받아 EcnryptedPrivateKeyInfo를 우선 decoding하며, 입력받은 password를
    바탕으로 암호화된 PrivateKeyInfo를 복호화한다. 복호화에 성공하면,
    PrivateKeyInfo의 포인터에 메모리를 할당하고 값을 설정한다.
    그러므로, PrivateKeyInfo를 사용하고 나서는 ASN_Del을 사용하여 할당된
    메모리를 해제하도록 한다.

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
    @brief Secret Key 버퍼로부터 EncryptedSecretKeyInfo를 생성한다.

    @param derEski [out] DER-encoding 된 상태의 EncryptedSecretKeyInfo가 출력될 ASNBuf
    @param key [in] 암호화 대상인 secret key가 저장된 버퍼의 포인터
    @param keyLen [in] secret key의 바이트 단위 길이
    @param pbeEncAlg [in] PBE(password-based encryption) scheme
    @param passwd [in] null-terminated string 타입의 암호 문자열
    @param salt [in] PBE scheme에 사용될 salt
    @param saltLen [in] PBE scheme에 사용될 salt의 바이트 단위 길이
    @param iteration [in] PBE scheme에 사용될 iteration

    secret key를 원하는 password-based encryption(PBE) scheme을 사용하여
    EncrypteSecretKeyInfo를 생성하는 함수이다.

    입력 파라미터로는 크게 3가지로 나눌 수 있다. 이 함수 오퍼레이션의
    대상인 secret key, 그리고 사용하고자 하는 PBE algorithm, 마지막으로,
    PBE algorithm의 구체적인 인자들인 salt와 iteration, password가 그것들이다.

    salt와 iteration에 관해서는 PKCS#5를 참고하기 바란다. 대부분의 경우
    PBKDF_DEFAULT_SALT와 PBKDF_DEFAULT_ITERATION을 사용하면 된다. (pbkdf.h에 정의)
    PBE algorithm 은 pbe.h에 참조되어 있는 Nid들 중의 하나가 될 것이다.
    단, 이 함수에서만은 PKCS5_PBE1과 PKCS12_PBE 만을 지원한다.

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
    @brief EncryptedSecretKeyInfo로부터 secret key를 얻는다.

    @param key [out] Secret key가 출력될 버퍼의 포인터
    @param keyLen [out] Secret key의 바이트 단위 길이
    @param derEski [in] DER-encoding 된 상태의 EncryptedSecretKeyInfo
    @param passwd [in] null-terminated string 타입의 암호 문자열
    
    이 함수는 DER-encoding된 EncryptedSecretKeyInfo로 부터 Secret key를
    얻는 기능을 한다. EncryptedSecretKeyInfo와, 암호화 시점의 password를
    입력받아 EcnryptedSecretKeyInfo를 우선 decoding하며, 입력받은 password를
    바탕으로 암호화된 Secret Key를 복호화한다. 복호화에 성공하면,
    입력받은 key 버퍼의 포인터에 그 값을 복사한다.

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
    @brief KeyBag을 생성한다.

    @param safeBag [out] 생성될 SafeBag의 포인터가 복사될 SafeBag의 포인터 변수
    @param pkinfo  [in] PrivateKeyInfo

    KeyBag 타입의 SafeBag을 생성한다. 내부적으로는 PrivateKeyInfo의
    DER-encoding 된 값을 value로 가진다.
    */
LIBSPEC_CKM
ERT PIEX_GenKeyBag(
    SafeBag **safeBag, PrivateKeyInfo *pkinfo);

/** @ingroup PIEX
    @brief PKCS8ShroudedKeyBag을 생성한다.

    @param safeBag [out] 생성될 SafeBag의 포인터가 복사될 SafeBag의 포인터 변수
    @param epkinfo [in] EncryptedPrivateKeyInfo

    PKCS9ShroudedKeyBag 타입의 SafeBag을 생성한다. EncryptedPrivateKeyInfo의
    DER-encoding 된 값을 value로 가진다.
    */
LIBSPEC_CKM
ERT PIEX_GenPKCS8ShroudedKeyBag(
    SafeBag **safeBag, EncryptedPrivateKeyInfo *epkinfo);

/** @ingroup PIEX
    @brief CertBag을 생성한다.

    @param safeBag [out] 생성될 SafeBag의 포인터가 복사될 SafeBag의 포인터 변수
    @param certId  [in] type of Certificate
    @param cert    c[in] Certificate

    Certificate을 담는 CertBag 타입의 SafeBag을 생성한다.
    */
LIBSPEC_CKM
ERT PIEX_GenCertBag(
    SafeBag **safeBag, Nid certId, Certificate *cert);

/** @ingroup PIEX
    @brief CRLBag을 생성한다.

    @param safeBag [out] 생성될 SafeBag의 포인터가 복사될 SafeBag의 포인터 변수
    @param crlId   [in] type of Certificate
    @param crl     [in] CRL

    CRL을 담는 CRLBag 타입의 SafeBag을 생성한다.
    */
LIBSPEC_CKM
ERT PIEX_GenCRLBag(
    SafeBag **safeBag, Nid crlId, CRL *crl);

LIBSPEC_CKM
/** @ingroup PIEX
    @brief SecretBag을 생성한다.

    @param safeBag   [out] 생성될 SafeBag의 포인터가 복사될 SafeBag의 포인터 변수
    @param secTypeId [in] type of secret value
    @param secValue  [in] secret value

    임의의 정보를 담는 SecretBag 타입의 SafeBag을 생성한다.
    */
ERT PIEX_GenSecretBag(
    SafeBag **safeBag, Nid secTypeId, ASNBuf *secValue);

/** @ingroup PIEX
    @brief SafeContentsBag을 생성한다.

    @param safeBag [out] 생성될 SafeBag의 포인터가 복사될 SafeBag의 포인터 변수
    @param sc      [in] SafeContents

    SafeContents를 담는 SafeContentsBag 타입의 SafeBag을 생성한다.
    */
LIBSPEC_CKM
ERT PIEX_GenSafeContentsBag(
    SafeBag **safeBag, SafeContents *sc);


/** @ingroup PIEX
    @brief SafeBag를 SafeContents에 추가한다.

    AuthenticateSafe는 SafeBag의 SequenceOf 타입이다. 따라서,
    ASN 모듈의 ASNSeqOf_AddP 함수를 재정의 하는 것으로 SafeBag를
    SafeContents에 추가하는 기능을 대신할 수 있다. ASNSeqOf_AddP
    의 인터페이스는 ASN 모듈의 설명을 참고하기 바란다.

    @sa PIEX_DelSafeBagFromSafeContents
        PIEX_GenSafeBag_Data PIEX_GenSafeBag_EncData PIEX_GenPFX
    */
#define PIEX_AddSafeBagPToSafeContents(safeContents, safeBag) \
        ASNSeqOf_AddP((ASNSeqOf*)(safeContents), (ASN*)(safeBag))

/** @ingroup PIEX
    @brief SafeBag를 SafeContents로부터 삭제한다.

    AuthenticateSafe는 SafeBag의 SequenceOf 타입이다. 따라서,
    ASN 모듈의 ASNSeqOf_Remove 함수를 재정의 하는 것으로 SafeBag를
    SafeContents로부터 삭제하는 기능을 대신할 수 있다. ASNSeqOf_Remove
    의 인터페이스는 ASN 모듈의 설명을 참고하기 바란다.
    
    @sa PIEX_AddSafeBagFromSafeContents
        PIEX_GenSafeBag_Data PIEX_GenSafeBag_EncData PIEX_GenPFX
    */
#define PIEX_DelSafeBagFromSafeContents(safeContents, index) \
        ASNSeqOf_Remove(safeContents, index)

/** @ingroup PIEX
    @brief Data type의 ContentInfo를 생성한다.

    @param cinfo [out] 생성된 ContentInfo의 포인터가 복사될 ContentInfo*의 포인터
    @param sc    [in] ContentInfo의 값이 될 SafeContent

    SafeContents를 Data 형식으로 가지는 ContentInfo를 생성한다.
    이 형식의 ContentInfo의 경우, SafeContents의 내용이 보호되지 않은
    상태이므로 private key와 같은 비밀 정보를 담고 있는 SafeContents에는
    부적합하며, 인증서와 같은 공개적인 정보를 담고 있을 경우에 사용하는
    형식이다.

    @sa PIEX_GenContentInfo_EncData PIEX_GenPFX
    */
LIBSPEC_CKM
ERT PIEX_GenContentInfo_Data(
    ContentInfo **cinfo, SafeContents *sc);

/** @ingroup PIEX
    @brief EncryptedData type의 ContentInfo를 생성한다.

    @param cinfo     [out] 생성된 ContentInfo의 포인터가 복사될 ContentInfo*의 포인터
    @param sc        [out] ContentInfo의 값이 될 SafeContent
    @param pbeEncAlg [in] PBE(password-based encryption) scheme
    @param passwd    [in] null-terminated string 타입의 암호 문자열
    @param salt      [in] PBE scheme에 사용될 salt
    @param saltLen   [in] PBE scheme에 사용될 salt의 바이트 단위 길이
    @param iteration [in] PBE scheme에 사용될 iteration

    SafeContents를 EncryptedData 형식으로 가지는 ContentInfo를 생성한다.
    암호화 방식은 password-based encryption 으로 PKCS#5, PKCS#12에
    규정되어 있다. SafeContents가 암호화되는 방식이므로 private key와 같은
    공개되어서는 안 될 정보에 대해서 사용하는 방식이다.
    
    입력 파라미터로는 크게 3가지로 나눌 수 있다. 이 함수 오퍼레이션의
    대상인 PrivateKeyInfo, 그리고 사용하고자 하는 PBE algorithm, 마지막으로,
    PBE algorithm의 구체적인 인자들인 salt와 iteration, password가 그것들이다.

    salt와 iteration에 관해서는 PKCS#5를 참고하기 바란다. 대부분의 경우
    PBKDF_DEFAULT_SALT와 PBKDF_DEFAULT_ITERATION을 사용하면 된다. (pbkdf.h에 정의)
    PBE algorithm 은 pbe.h에 참조되어 있는 Nid들 중의 하나가 될 것이다.
    단, 이 함수에서만은 PKCS5_PBE1과 PKCS12_PBE 만을 지원한다.

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
    @brief ContentInfo를 AuthenticatedSafe에 추가한다.

    AuthenticateSafe는 ContentInfo의 SequenceOf 타입이다. 따라서,
    ASN 모듈의 ASNSeqOf_AddP 함수를 재정의 하는 것으로 ContentInfo를
    AuthenticatedSafe에 추가하는 기능을 대신할 수 있다. ASNSeqOf_AddP
    의 인터페이스는 ASN 모듈의 설명을 참고하기 바란다.

    @sa PIEX_DelContentInfoFromAuthenticatedSafe
        PIEX_GenContentInfo_Data PIEX_GenContentInfo_EncData PIEX_GenPFX
    */
#define PIEX_AddContentInfoPToAuthenticatedSafe(authSafe, contentInfo) \
        ASNSeqOf_AddP((ASNSeqOf*)(authSafe), (ASN*)(contentInfo))

/** @ingroup PIEX
    @brief ContentInfo를 AuthenticatedSafe로부터 삭제한다.

    AuthenticateSafe는 ContentInfo의 SequenceOf 타입이다. 따라서,
    ASN 모듈의 ASNSeqOf_Remove 함수를 재정의 하는 것으로 ContentInfo를
    AuthenticatedSafe로부터 삭제하는 기능을 대신할 수 있다. ASNSeqOf_Remove
    의 인터페이스는 ASN 모듈의 설명을 참고하기 바란다.
    
    @sa PIEX_AddContentInfoFromAuthenticatedSafe
        PIEX_GenContentInfo_Data PIEX_GenContentInfo_EncData PIEX_GenPFX
    */
#define PIEX_DelContentInfoFromAuthenticatedSafe(authSafe, index) \
        ASNSeqOf_Remove(authSafe, index)


/** @ingroup PIEX
    @brief PFX를 생성한다.

    @param pfx       [out] 생성된 PFX의 포인터가 복사될 PFX의 포인터변수
    @param authSafe  [in] PFX가 저장할 AuthenticatedSafe
    @param hashAlgId [in] HMAC에 사용될 해쉬 알고리즘
    @param passwd    [in] null-terminated string 타입의 암호 문자열
    @param salt      [in] PBE scheme에 사용될 salt
    @param saltLen   [in] PBE scheme에 사용될 salt의 바이트 단위 길이
    @param iteration [in] PBE scheme에 사용될 iteration

    PFX는 내부적으로 AuthenticatedSafe를 가지며 무결성을 위해 MAC값도
    가지고 있다. 이 함수는 AuthenticatedSafe를 입력받아 MAC값을 계산하고
    PFX를 생성한다.
    
    PKCS#12에서 규정하고 있는 무결성을 위한 방식에는
    MAC 뿐만 아니라 서명 방식도 있으나, 이 모듈(이 함수)에서는 HMAC 방식
    만을 지원한다. HMAC에 쓰이는 키는 password-based key derivation 을
    쓰며 PKCS#5에 규정되어 있다. 하나의 PFX에서는 ContentInfo를 생성할
    때나 PFX를 생성할 때나 동일한 password를 사용하여야 한다.

    @sa PIEX_GenContentInfo_Data PIEX_GenContentInfo_EncData
        PIEX_AddContentInfoToAuthenticatedSafe
        PIEX_DelContentInfoFromAuthenticatedSafe
    */
LIBSPEC_CKM
ERT PIEX_GenPFX(
    PFX **pfx, AuthenticatedSafe *authSafe,
    Nid hashAlgId, const char *passwd, const BYTE *salt, BWT saltLen, BWT iteration);

/** @ingroup PIEX
    @brief 비공개키와 인증서로 PFX를 생성한다.

    @param pfx       [out] 생성된 PFX의 포인터가 복사될 PFX의 포인터변수
    @param epki      [in] 암호화된 상태의 비공개키
    @param cert      [in] 비공개키와 쌍을 이루는 인증서
    @param caCerts   [in] 기타 인증 경로에 있는 인증서들
    @param hashAlgId [in] HMAC에 사용될 해쉬 알고리즘
    @param pbeEncAlg [in] SafeBag들을 암호화할 PBE 알고리즘
    @param passwd    [in] null-terminated string 타입의 암호 문자열
    @param salt      [in] PBE scheme에 사용될 salt
    @param saltLen   [in] PBE scheme에 사용될 salt의 바이트 단위 길이
    @param iteration [in] PBE scheme에 사용될 iteration

    PFX는 내부적으로 AuthenticatedSafe를 가지며 무결성을 위해 MAC값도
    가지고 있다.
    이 함수는 비공개키와 인증서들을 입력받아 AuthenticatedSafe를 생성하고
    MAC값을 계산하고 PFX를 생성한다. PIEX_GenPFX와 다른 점은 비공개키와
    인증서들로 직접 AuthenticatedSafe를 생성한다는 점이다. 즉,
    AuthenticatedSafe 생성과정을 자동화했다고 할 수 있다.
    
    PKCS#12에서 규정하고 있는 무결성을 위한 방식에는
    MAC 뿐만 아니라 서명 방식도 있으나, 이 모듈(이 함수)에서는 HMAC 방식
    만을 지원한다. HMAC에 쓰이는 키는 password-based key derivation 을
    쓰며 PKCS#5에 규정되어 있다. 하나의 PFX에서는 ContentInfo를 생성할
    때나 PFX를 생성할 때나 동일한 password를 사용하여야 한다.

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
    @brief PFX를 디코딩하여 SafeBag 값을 추출한다.

    @param safeBags [out] SafeBag의 리스트가 저장될 포인터
    @param numBags [out] SafeBag 리스트에 저장된 SafeBag의 개수
    @param passwd [in] null-terminated string 타입의 암호
    @param derPFX [in] DER-encoding 상태의 PFX 값, ASNBuf 타입
    @retval ER_PIEX_PFX_AUTH_FAIL Authentication fail(invalid password)

    PFX는 PKCS#12에 정의되어 있는 타입으로 개인 정보
    (private key, certificate 등등)를 안전하게 import/export하기 위해
    디자인된 타입이다. 내부적으로는 복수개의 SafeBag을 가지고 있으며,
    SafeBag은 구체적인 정보를 담게 된다.

    이 함수는 PFX를 디코딩하며, 메시지의 무결성을 체크하고, 복호화한 후
    SafeBag의 리스트를 가져온다. 함수 내부에서 메모리를 할당하므로 반드시
    메모리를 헤제하는 과정을 거쳐야 하며, 그 작업은 PIEX_DelSafeBags라는
    함수를 통해 이루어진다.

    SafeBag의 리스트는 별도의 구조체가 있는 것이 아니라, SafeBag 타입을
    가리키고 있는 포인터들의 배열이다. 다음의 예제 코드를 보기 바란다.
    (safeBag의 타입과 관련된 부분만을 기술)

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
    @brief 메모리에 할당된 SafeBag 리스트를 free한다.

    @param safeBags [in] SafeBag 포인터의 리스트의 첫번째 요소의 포인터
    @param numBags [in] SafeBag 리스트의 SafeBag 개수

    @sa PIEX_GetSafeBagsFromPFX
    */
LIBSPEC_CKM
void PIEX_DelSafeBags(SafeBag **safeBags, int numBags);

/** @ingroup PIEX
    @brief SafeBag의 타입을 얻는다.

    @param bagId [out] 타입이 저장될 Nid 포인터
    @param safeBag [in] 쿼리 대상인 SafeBag의 포인터

    SafeBag은 지니고 있는 value가 어떠한 타입인지를 지시하는 OID를 가지고,
    있으며, 이 함수는 그 값을 Nid형태로 출력한다.

    @sa PIEX_GetBagValueFromSafeBag PIEX_GetSafeBagsFromPFX PIEX_DelSafeBags
    */
LIBSPEC_CKM
ERT PIEX_GetBagIDFromSafeBag(Nid *bagId, const SafeBag *safeBag);

/** @ingroup PIEX
    @brief SafeBag이 지닌 value를 얻는다.

    @param derBagVal [out] value가 저장될 ASNBuf*의 포인터
    @param safeBag [in] 쿼리 대상인 SafeBag의 포인터

    SafeBag이 지니고 있는 value를 가져오는 함수이다. ASNBuf를 함수내부에서
    메모리에 할당하고 값을 설정하므로, 할당된 ASNBuf를 반드시 ASNBuf_Del을
    통해서 free해야 한다.

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
