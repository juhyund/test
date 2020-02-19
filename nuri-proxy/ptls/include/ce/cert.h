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
 * @brief certificate�� ���õ� Ÿ��, �Լ�
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


/* serialNumber�� NULL�� ��� ���������� ����(issuer, subject�� NULL�̸� ����)
   signature�� NULL�� ��쿡�� set���� �ʴ´�. ���߿� ������ ����.
   extensions�� NULL�� ��� Version 1.
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
   @param a [out] PKCryptParam�� �������� ������
                  ���ο��� �޸𸮰� �Ҵ�Ǿ� ��µȴ�.
   @param b [in] Certificate Ÿ���� ������
   @return PKCryptPubKey�� ������, �����ϸ� NULL

   PKCryptPubkey_New�� �̿��ϱ� ������ ������� PKCryptPubKey�� �����Ͱ�
   �޸� �Ҵ�Ǿ� ���´�. PublicKeyInfo�� �ý��� ������ ���ԵǾ� ������
   PKCryptParam Ÿ������ �޸𸮰� �Ҵ�Ǿ� ��µȴ�.
   NID_kCDSA1�� ���� ���� �� ������ ���� kcdsaPubInfo�� Ȱ�� �����ϴ�. 
*/
#define CERT_GetPublicKey(a, b) \
        PKCryptPubKey_New((a), \
                          (PublicKeyInfo *)((b)->tbsCertificate->subjectPublicKeyInfo))

#define CERT_GetPublicKeyAlgNid(cert) \
          ((cert)->tbsCertificate->subjectPublicKeyInfo->algorithm->algorithm->nid)

/* �����ϴ� ����Ű �˰����� �ƴϸ� 0 ��� */
  /*
LIBSPEC_CKM
Nid CERT_GetPublicKeyAlgNid(Certificate *cert);
*/

/* Certificate�� Hash���� ��´�. 
   NID_kCDSA�� ���� ���� �� ������ ����
   kcdsaPubInfo�� Ȱ�� �����ϴ�. 
   certHash���� ��� HASH_MAX_DIGEST_SIZE�̻��� �޸� ������
   �Ҵ�Ǿ� �־�� �Ѵ�.
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
 * ���������� ����Ű�� �����Ű�� Ű���� �´��� Ȯ���Ѵ�.
 *
 * @param *cert       (In) ����Ű ������
 * @param *priKeyInfo (In) Ű���� ���Ϸ��� �����Ű
 * @param *param      (In) DomainParameter��
 *
 * @return 
 *  - SUCCESS : ����
 *  - �׿�     : ����
 */
LIBSPEC_CKM
ERT CERT_CheckKeyPair(const Certificate    *cert, 
                      const PrivateKeyInfo *priKeyInfo, 
                      const Parameter      *param);


/***********************************************************************
 * READ & WRITE �Լ�
 */


/**
 * ���Ϸκ��� �������� �о�´�.(������ �������κ��� ������ ������ ������ �Ǵ���)
 *
 * @param *filePath (In) ������ ���� �̸�
 *
 * @return 
 *    ������ ��, �б⿡ ������ ��쿡�� NULL
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


/* CERTŸ�Կ� ���� ��Ʈ�� ����� ���ؼ� CERTPrintCtx�� ���� */
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
   @param any_policy [in] ANY-POLICY������ ���θ� ��Ÿ��
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

/** policy�� policySet�� ���ԵǾ� ������ SUCCESS
 */
LIBSPEC_CKM
ERT PolicySet_CheckInclusion(PolicySet *policySet,
                             CertPolicyId *policy);

/** policies�� policySet�� ��� ���ԵǾ� ������ SUCCESS
 */
LIBSPEC_CKM
ERT PolicySet_CheckInclusion2(PolicySet *policySet, PolicySet *policies);

/**
  �ΰ��� PolicySet�� Intersection�� non-null���� ���θ� �Ǵ��Ѵ�.
  */
LIBSPEC_CKM
ERT PolicySet_CheckIntersection(PolicySet *policySet,
                                PolicySet *policies);

/**
  �� ���� PolicySet�� Intersection�� ã�Ƽ� ���ο� PolicySet��
  �Ҵ��Ͽ� ����Ѵ�.
  */
LIBSPEC_CKM
PolicySet *PolicySet_GetIntersection(PolicySet *policySet,
                                     PolicySet *policies);


/** @ingroup CERT
   @param ext [in] Ȯ�念�� BasicConstraints�� ���԰� �ִ� extension
   CA �������� �Ӽ��� BasicConstraints�� CA ���θ� Ȯ���ϰ�
   pathConstraints�� �����ϴ� ��� �־��� certificationDepth��
   ���Ͽ� �������� ���Ѵ�.

   ���⼭ certificationDepth�� CA�� �ڽ��� �ŷ� ��� �Ʒ��� ��
   �� �ִ� CA�� ���� �̾߱� �Ѵ�. ���� ��� ����ڿ��� ��������
   �߱��ϴ� CA�� certificationDepth�� 0�̴�. 
 */
LIBSPEC_CKM
ERT CERT_CheckCABasicConstraints(int certificationDepth, 
                                 Extension *ext);

/** @ingroup CERT
    @param ext [in] Ȯ�念�� KeyUsage�� �����ϰ� �ִ� extension
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
 
/* ������ ���� inCerts �ȿ� �־��� subjectName�� ���� ������ ���� */
LIBSPEC_CKM
CERTS* CERTS_GetBySubjectName( CERTS *inCerts,
                               Name  *subjecName);

/* ������ ���� inCerts �ȿ� subjectKeyId�� ���� �������� �����ϴٰ� ���� */
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

/* ���� VRF_XXX �÷��׸� �̿��Ͽ� flags�� �־��ָ� verify�ϴ� ��������
    ������ verify�� ������ ������ �� �ִ�. ���� VRF_IGNOREPOLICYCHECKING��
    ������ ��쿡�� initialPolices�� NULL���� �����ص� �ȴ�. ���� endPathIndex
    ������ ������ ������ endPathIndex�� NULL�� ��Ƶ� �����ϴ�. */
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

