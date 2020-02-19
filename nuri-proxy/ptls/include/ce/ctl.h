#ifndef _CTL_H_
#define _CTL_H_

#include "cc_define.h"
#include "me.h"
#include "x509com.h"
#include "x509pkc.h"
#include "cms.h"

/** @defgroup CTL CTL handling
 * @ingroup CKM
    @brief 직접적으로 CTL을 다루는 APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  DURMY
} CTL_ERRORS;

typedef struct {
  ASNSeqOfClass klass;
  int size;
  ASNOid **member;
} SubjectUsage;

LIBSPEC_CKM
extern ASNDescriptor AD_SubjectUsage;

typedef OctetString ListIdentifier;
#define AD_ListIdentifier AD_OctetString

typedef struct {
  ASNSeqClass klass;
  OctetString *subjectIdentifier;
  Attributes *attributes; /* optional */
} TrustedSubject;

LIBSPEC_CKM
extern ASNDescriptor AD_TrustedSubject;

typedef struct {
  ASNSeqOfClass klass;
  int size;
  TrustedSubject **member;
} TrustedSubjects;

LIBSPEC_CKM
extern ASNDescriptor AD_TrustedSubjects;

typedef struct {
  ASNSeqClass klass;
  Version *version; /* default 1 */
  SubjectUsage *subjectUsage;
  ListIdentifier *listIdentifier; /* optional */
  Integer *sequenceNumber; /* optional */
  Time *thisUpdate;
  Time *nextUpdate;
  AlgorithmIdentifier *subjectAlgorithm;
  TrustedSubjects *trustedSubjects;
  Extensions *extensions; /* optional */
} CertificateTrustList;

LIBSPEC_CKM
extern ASNDescriptor AD_CertificateTrustList;

typedef CertificateTrustList CTL;
#define AD_CTL AD_CertificateTrustList

LIBSPEC_CKM
ERT CTL_Set(CTL          *ctl,
            Oid           subjectUsage[],
            unsigned int  numSubjectUsage,
            char         *listId,
            unsigned int  listIdLen,
            int           seqNum,
            struct tm    *thisUpdate,
            struct tm    *nextUpdate,
            AlgDesc       hashAlg,
            CERTS        *trustedCerts,
            Extensions   *ext);

LIBSPEC_CKM
ERT CTL_Sign(ASNBuf         **ctlBuf,
             CTL             *ctl,
             PrivateKeyInfo  *signerPriInfo,
             CERT            *signerCert,
             Parameter       *domainParam,
             AlgDesc          hashAlg,
             struct tm       *signTime,
             CERTS           *trustedCerts);

LIBSPEC_CKM
ERT CTL_VerifySign(ASNBuf    *ctlBuf,
                   CERT      *signerCert,
                   Parameter *domainParam);

LIBSPEC_CKM
ERT CTL_GetCTL(CTL    **ctl,
               ASNBuf  *ctlBuf);

LIBSPEC_CKM
ERT CTL_CheckCertIn(CTL  *ctl,
                    CERT *cert);

LIBSPEC_CKM
CTL* CTL_NewFromFile(SignedData **signeddata,
                     const char *filePath) ;

LIBSPEC_CKM
CTL* CTL_NewFromMemory(SignedData **signeddata,
                       const void  *buffer,
                       int          buffer_len);

#ifdef __cplusplus
}
#endif
        
#endif /* _CTL_H_ */ 
