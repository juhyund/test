#ifndef _CERT_H_
#define _CERT_H_

#ifdef WIN32
#include <time.h>
#endif

#include "ckm_pkcrypt.h"
#include "me.h"
#include "x509pkc.h"

/** @defgroup CERT Certificate General
 * @ingroup CKM
 * @brief certificate과 관련된 타입, 함수
 * @{ */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  ER_CERT_PUBKEYALG_MISMATCH = ER_CERT,
  ER_CERT_WRONG_SIGNATURE,
  ER_CERT_VALIDITY_NOT_STARTED,
  ER_CERT_VALIDITY_EXPIRED,
  ER_CERT_WRONG_ISSUER,
  ER_CERT_WRONG_CRLISSUER,
  ER_CERT_IN_CRL
} CERT_ERRORS;

typedef enum {
  ER_CERTS_WRONG_CA_CERTIFICATE = ER_CERTS,
  ER_CERTS_WRONG_PATH_LEN_CONSTRAINT,
  ER_CERTS_WRONG_CA_KEYUSAGE,
  ER_CERTS_NO_CERTPOLICY_IN_CERT,
  ER_CERTS_NO_CERTPOLICY_IN_INITIAL_POLICIES,
  ER_CERTS_NO_CERTPOLICY_IN_ACCEPTABLE_POLICIES,
  ER_CERTS_ACCPOLICY_INIPOLICY_INTERSECTION_NULL,
  ER_CERTS_WRONG_NAMECONSTRAINTS,
  ER_CERTS_WRONG_POLICYMAPPING,
  ER_CERTS_WRONG_UNKNOWN,
} CERTS_ERRORS;


/*****************************************************************************
 * CERT manipulation functions
 */


/* serialNumber가 NULL인 경우 내부적으로 생성(issuer, subject가 NULL이면 에러)
   signature가 NULL인 경우에는 set하지 않는다. 나중에 셋팅이 가능.
   extensions가 NULL인 경우 Version 1.
 */
LIBSPEC_CKM
ERT TBSCertificate_Set(TBSCertificate          *tbsCertificate,
                       CertificateSerialNumber *serialNumber,
                       Name                    *issuer,
                       struct tm               *notBefore,
                       struct tm               *notAfter,
                       Name                    *subject,
                       SubjectPublicKeyInfo    *subjectPublicKeyInfo,
                       Extensions              *extensions);


/*
   @ingroup CERT
   @define CERT_GetPublicKey
   @param a [out] PKCryptParam의 포인터의 포인터
                  내부에서 메모리가 할당되어 출력된다.
   @param b [in] Certificate 타입의 인증서
   @return PKCryptPubKey의 포인터, 실패하면 NULL

   PKCryptPubkey_New를 이용하기 때문에 출력으로 PKCryptPubKey의 포인터가
   메모리 할당되어 나온다. PublicKeyInfo에 시스템 변수가 포함되어 있으면
   PKCryptParam 타입으로 메모리가 할당되어 출력된다.
   NID_kCDSA1의 서명 생성 및 검증을 위한 kcdsaPubInfo로 활용 가능하다. 
*/
#define CERT_GetPublicKey(a, b) \
        PKCryptPubKey_New((a), \
                          (PublicKeyInfo *)((b)->tbsCertificate->subjectPublicKeyInfo))

#define CERT_GetPublicKeyAlgNid(cert) \
          ((cert)->tbsCertificate->subjectPublicKeyInfo->algorithm->algorithm->nid)

/* 지원하는 공개키 알고리즘이 아니면 0 출력 */
  /*
LIBSPEC_CKM
Nid CERT_GetPublicKeyAlgNid(Certificate *cert);
*/

/* Certificate의 Hash값을 얻는다. 
   NID_kCDSA의 서명 생성 및 검증을 위한
   kcdsaPubInfo로 활용 가능하다. 
   certHash에는 적어도 HASH_MAX_DIGEST_SIZE이상의 메모리 공간이
   할당되어 있어야 한다.
 */
LIBSPEC_CKM
ERT CERT_GetCertHash(BYTE        *certHash, 
                     BWT         *certHashLen, 
                     Certificate *cert,
                     AlgDesc      hashAlg);

LIBSPEC_CKM
ASNBuf* CERT_GetSignatureValue(Certificate *cert);

LIBSPEC_CKM
ERT CERT_GetSignatureValuePK(PKCryptSig *sigVal, Certificate *cert);

#define CERT_GetSignatureAlgNid(a) ((a)->signatureAlgorithm->algorithm->nid)

/*
   @param cert [out]
   @param tbsCertificate [in]
 */
LIBSPEC_CKM
ERT CERT_GenPK(Certificate    *cert,
               TBSCertificate *tbsCertificate,
               PKCryptPriKey  *issuerKey,
               PKCryptParam   *domainParam,
               AlgDesc         hashAlg,
               const void     *kcdsaPub);

LIBSPEC_CKM
ERT CERT_Gen(Certificate    *cert,
             TBSCertificate *tbsCertificate,
             PrivateKeyInfo *issuerPriKeyInfo,
             Parameter      *domainParam,
             AlgDesc         hashAlg,
             Certificate    *issuerCert);

LIBSPEC_CKM
ERT CERT_Gen_RSAPSS(Certificate    *cert,
		TBSCertificate *tbsCertificate,
		PrivateKeyInfo *issuerPriKeyInfo,
		Parameter      *domainParam,
		Certificate    *issuerCert);


/*
 ER_CERT_PUBKEYALG_MISMATCH
 */
LIBSPEC_CKM
ERT CERT_VerifySignPK(Certificate         *cert,
                      const PKCryptPubKey *pubKey,
                      const PKCryptParam  *param,
                      const void          *kcdsaPubInfo);

LIBSPEC_CKM
ERT CERT_VerifySign(Certificate         *cert,
                    Certificate         *issuerCert,
                    Parameter           *domainParam);

LIBSPEC_CKM
ERT CERT_VerifySign_RSAPSS(Certificate         *cert,
		Certificate         *issuerCert,
		Parameter           *domainParam);

/*
   ER_CERT_VALIDITY_NOT_STARTED
   ER_CERT_VALIDITY_EXPIRED
*/
/* Deprecated....use CERT_VerifyTime(Certificate, struct tm)
LIBSPEC_CKM
ERT CERT_VerifyTime(Certificate *cert,
                    time_t      now);
*/

/*
   ER_CERT_VALIDITY_NOT_STARTED
   ER_CERT_VALIDITY_EXPIRED
*/
LIBSPEC_CKM
ERT CERT_VerifyTime(Certificate *cert,
                    struct tm   *now);

/*
   ER_CERT_VALIDITY_NOT_STARTED,
   ER_CERT_VALIDITY_EXPIRED,
   ER_CERT_WRONG_ISSUER,
   ER_CERT_WRONG_CRLISSUER,
   ER_CERT_IN_CRL
 */
LIBSPEC_CKM
ERT CERT_Verify(Certificate     *cert,
                Certificate     *issuerCert,
                time_t           now,
                CRL             *trustedCrl,
                Parameter       *domainParam);

LIBSPEC_CKM
ERT CERT_CheckKeyPairPK(const Certificate   *cert, 
                        const PKCryptPriKey *priKey, 
                        const PKCryptParam  *param);

/**
 * 인증서안의 공개키와 비공개키가 키쌍이 맞는지 확인한다.
 *
 * @param *cert       (In) 공개키 인증서
 * @param *priKeyInfo (In) 키쌍을 비교하려는 비공개키
 * @param *param      (In) DomainParameter값
 *
 * @return 
 *  - SUCCESS : 성공
 *  - 그외     : 실패
 */
LIBSPEC_CKM
ERT CERT_CheckKeyPair(const Certificate    *cert, 
                      const PrivateKeyInfo *priKeyInfo, 
                      const Parameter      *param);


/***********************************************************************
 * READ & WRITE 함수
 */


/**
 * 파일로부터 인증서를 읽어온다.(파일의 내용으로부터 인증서 파일의 형식을 판단함)
 *
 * @param *filePath (In) 인증서 파일 이름
 *
 * @return 
 *    인증서 값, 읽기에 실패한 경우에는 NULL
 */
LIBSPEC_CKM
Certificate *CERT_NewFromFile(const char *filePath);

enum CERT_FILE_TYPE {
  CERT_DER = 1,
  CERT_PEM
};

LIBSPEC_CKM
ERT CERT_WriteFile(Certificate         *cert, 
                   const char          *filePath,
                   enum CERT_FILE_TYPE  flag);

#define CERT_WriteFileDER(cert, filePath) \
        CERT_WriteFile((cert), (filePath), CERT_DER)

#define CERT_WriteFilePEM(cert, filePath) \
        CERT_WriteFile((cert), (filePath), CERT_PEM)


/* CERT타입에 대한 스트링 출력을 위해서 CERTPrintCtx를 만듬 */
typedef struct {
  char version[8];
  char serialNumber[128];
  char signature[128];
  NamePrintCtx *issuer;
  struct {
    char      notBefore[64];
    struct tm notBeforeTm;
    char      notAfter[64];
    struct tm notAfterTm;
  } validity;
  NamePrintCtx *subject;
  struct {
    char algorithm[32];
    int  keyBitLen;
    char publicKey[1028];
  } subjectPublicKeyInfo;
  ExtsPrintCtx *extensions;
} CERTPrintCtx;

LIBSPEC_CKM
CERTPrintCtx *CERT_NewPrintCtx(const Certificate *cert);

LIBSPEC_CKM
void CERT_DelPrintCtx(CERTPrintCtx *print);


/*****************************************************************************
 * PolcySet defines and manipulation functions
 */

typedef struct {
  ASNSeqClass        klass;
  SeqOfCertPolicyId *policies;
  ASNBool           *anyPolicy;
} PolicySet;

LIBSPEC_CKM
extern ASNDescriptor AD_PolicySet;

/**
   @param any_policy [in] ANY-POLICY인지의 여부를 나타냄
  */
LIBSPEC_CKM
PolicySet *PolicySet_New(int anyPolicy);

LIBSPEC_CKM
ERT PolicySet_Add(PolicySet *ps, CertPolicyId *policy); 

LIBSPEC_CKM
ERT PolicySet_AddP(PolicySet *ps, CertPolicyId *policy); 

LIBSPEC_CKM
ERT PolicySet_AddByOIDStr(PolicySet *ps, const char *oidStr); 

#define PolicySet_Del(ps) ASN_Del(ps)

/** policy가 policySet에 포함되어 있으면 SUCCESS
 */
LIBSPEC_CKM
ERT PolicySet_CheckInclusion(PolicySet *policySet,
                             CertPolicyId *policy);

/** policies가 policySet에 모두 포함되어 있으면 SUCCESS
 */
LIBSPEC_CKM
ERT PolicySet_CheckInclusion2(PolicySet *policySet, PolicySet *policies);

/**
  두개의 PolicySet의 Intersection이 non-null인지 여부를 판단한다.
  */
LIBSPEC_CKM
ERT PolicySet_CheckIntersection(PolicySet *policySet,
                                PolicySet *policies);

/**
  두 개의 PolicySet의 Intersection을 찾아서 새로운 PolicySet을
  할당하여 출력한다.
  */
LIBSPEC_CKM
PolicySet *PolicySet_GetIntersection(PolicySet *policySet,
                                     PolicySet *policies);


/** @ingroup CERT
   @param ext [in] 확장영역 BasicConstraints를 포함고 있는 extension
   CA 인증서의 속성인 BasicConstraints의 CA 여부를 확인하고
   pathConstraints가 존재하는 경우 주어진 certificationDepth와
   비교하여 적법함을 비교한다.

   여기서 certificationDepth란 CA가 자신의 신뢰 경로 아래에 둘
   수 있는 CA의 수를 이야기 한다. 예를 들어 사용자에게 인증서를
   발급하는 CA의 certificationDepth는 0이다. 
 */
LIBSPEC_CKM
ERT CERT_CheckCABasicConstraints(int certificationDepth, 
                                 Extension *ext);

/** @ingroup CERT
    @param ext [in] 확장영역 KeyUsage를 포함하고 있는 extension
 */
LIBSPEC_CKM
ERT CERT_CheckCAKeyUsage(Extension *ext);

LIBSPEC_CKM
ERT CERTS_CheckPolicies(PolicySet  **acceptablePolicies,
                        PolicySet   *initialPolicies,
                        int          explicitPolicy,
                        int          verificationStage,
                        Extension   *ext);

LIBSPEC_CKM
ERT CERTS_CheckPolicyMappings(PolicySet *initialPolicies, 
                              int        policyMapping,
                              int        verificationStage,
                              Extension *ext);

LIBSPEC_CKM
ERT CERTS_CheckPolicyConstraints(int       *explicitPolicy,
                                 int       *policyMapping,
                                 int        verificationStage,
                                 Extension *ext);



/*****************************************************************************
 * CERTS manipulation functions
 */

LIBSPEC_CKM
int CERTS_GetIndexByIssuerAndSN( CERTS                   *inCerts,
                                 Name                    *issuerName,
                                 CertificateSerialNumber *sn);

LIBSPEC_CKM
CERT*  CERTS_GetByIssuerAndSN( CERTS                   *inCerts,
                               Name                    *issuerName,
                               CertificateSerialNumber *sn);
 
/* 인증서 집합 inCerts 안에 주어진 subjectName을 갖는 인증서 추출 */
LIBSPEC_CKM
CERTS* CERTS_GetBySubjectName( CERTS *inCerts,
                               Name  *subjecName);

/* 인증서 집합 inCerts 안에 subjectKeyId를 가진 인증서는 유일하다고 가정 */
LIBSPEC_CKM
CERTS* CERTS_GetBySubjectKeyId( CERTS                *inCerts,
                                SubjectKeyIdentifier *subjecKeyId);

/* if trustedCerts == NULL, suppose that all of root of paths are truted */
LIBSPEC_CKM
CERTS** CERTS_GetPath(int   *numOfPath,
                      CERTS *inCerts,
                      CERTS *trustedCerts,
                      CERT  *endCert);

LIBSPEC_CKM
void    CERTS_DelPath(int     numOfPath,
                      CERTS **path);

/*
  ER_CERTS_WRONG_CA_CERTIFICATE = ER_CERTS,
  ER_CERTS_WRONG_PATH_LEN_CONSTRAINT,
  ER_CERTS_WRONG_CA_KEYUSAGE
 */
LIBSPEC_CKM
ERT CERTS_VerifyBasicInfo( CERTS  *certPath,
                           time_t  verifyTime);

LIBSPEC_CKM
ERT CERTS_VerifyBasicInfo2( int    *endPathIndex,
                            CERTS  *certPath,
                            time_t  verifyTime);

/*
  ER_CERTS_NO_CERTPOLICY_IN_CERT,
  ER_CERTS_NO_CERTPOLICY_IN_INITIAL_POLICIES
  ER_CERTS_NO_CERTPOLICY_IN_ACCEPTABLE_POLICIES
  ER_CERTS_ACCPOLICY_INIPOLICY_INTERSECTION_NULL
*/

/* Deprecated. Use CERTS_VerifyEx */
LIBSPEC_CKM
ERT CERTS_Verify(CERTS     *certPath, 
                 time_t     verifyTime, 
                 PolicySet *initialPolicies);

/* Deprecated. Use CERTS_VerifyEx */
LIBSPEC_CKM
ERT CERTS_Verify2(int       *endPathIndex,
                  CERTS     *certPath, 
                  time_t     verifyTime, 
                  PolicySet *initialPolicies);

#define VRF_ALL                         0x0000
#define VRF_BASICONLY                   0x0004
#define VRF_IGNOREPOLICYCHECKING        0x0004
#define VRF_IGNORENAMECONSTRAINTS       0x0008
#define VRF_IGNOREPATHLENCONSTRAINT     0x0010
#define VRF_IGNOREBASICCONSTRAINTS      0x0020
#define VRF_NOEXPLICITPOLICY            0x0040

/* 위의 VRF_XXX 플래그를 이용하여 flags에 넣어주면 verify하는 과정에서
    무엇을 verify할 것인지 선택할 수 있다. 만약 VRF_IGNOREPOLICYCHECKING을
    선택할 경우에는 initialPolices는 NULL으로 설정해도 된다. 또한 endPathIndex
    정보에 관심이 없으면 endPathIndex는 NULL로 잡아도 무방하다. */
LIBSPEC_CKM
ERT CERTS_VerifyEx(int          *endPathIndex,
                   CERTS        *certPath,
                   time_t        verifyTime,
                   PolicySet    *initialPolicies,
                   unsigned int  flags) ;
  
#ifdef __cplusplus
}
#endif
        
/** @} */
#endif /* _CERT_H */

