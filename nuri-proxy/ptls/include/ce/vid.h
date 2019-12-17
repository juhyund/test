#ifndef _VID_H_
#define _VID_H_

#include "sp_define.h"

#include "asn1.h"
#include "pkcs.h"
#include "x509pkc.h"
#include "cms.h"
#include "hmac.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************
 * Type defines
 ***************************************************************/

/***********************************************
 * Virtual ID  
 */

typedef struct {
  ASNSeqClass          Klass;
  AlgorithmIdentifier *hashAlg;
  OctetString         *virtualID;
} VID;

LIBSPEC_SP
extern ASNDescriptor AD_VID;

typedef struct {
  ASNSeqClass        Klass;
  PrintableString   *idn;
  BitString         *randomNum;
} HashContent;

LIBSPEC_SP
extern ASNDescriptor AD_HashContent;

typedef struct {
  ASNSeqClass              Klass;
  Integer                 *version;
  AlgorithmIdentifier     *vidHashAlg; /* optional */
  AlgorithmIdentifier     *vidEncAlg;
  IssuerAndSerialNumber   *certID;
  OctetString             *encryptedVID;
} EncryptedVID;

LIBSPEC_SP
extern ASNDescriptor AD_EncryptedVID;

typedef struct {
  ASNSeqClass              Klass;
  VID                     *vid;
  BitString               *randomNum;
} EncryptContent;

LIBSPEC_SP
extern ASNDescriptor AD_EncryptContent;

typedef struct {
  ASNSeqClass                    Klass;
  UTF8String                    *realName;
  SeqOfAttributeTypeAndValue    *userInfo;
} IdentifyData;

LIBSPEC_SP
extern ASNDescriptor AD_IdentifyData;



/***************************************************************
 * Function defines
 ***************************************************************/

LIBSPEC_SP
ERT VID_CreateVID(
        VID   **ppVID,
        char   *idn,
        char    randNum160bit[20],
        Nid     hashNid );

LIBSPEC_SP
ERT VID_CreateEncryptContent(
        EncryptContent **ppEncryptContent,
        char            *idn,
        char             randNum160bit[20],
        Nid              hashNid );


LIBSPEC_SP
ERT VID_CreateEncryptedVID(
        EncryptedVID   **ppEncryptedVID,
        EncryptContent  *pEncryptContent,
        Certificate     *pCaCert );

LIBSPEC_SP
ERT VID_DecryptEncryptedVID(
                EncryptContent **ppEncryptContent,
                EncryptedVID    *pEncryptedVID,
                Certificate     *pCaCert,
                PrivateKeyInfo  *pCaKey );

LIBSPEC_SP
ERT VID_GetRandomNumFromPriKey(
        char             randNum160bit[20],
        PrivateKeyInfo  *priKey );

LIBSPEC_SP
ERT VID_SetRandomNumToPriKey(
        char             randNum160bit[20],
        PrivateKeyInfo  *priKey );

LIBSPEC_SP
ERT VID_FindVIDInCert(
        VID        **ppVID,
        Certificate *cert );

LIBSPEC_SP
ERT VID_CompareInputVIDWithCert(
        Certificate *cert,
        char        *idn,
        char         randNum160bit[20] );


#ifdef __cplusplus
}
#endif

#endif /* _VID_H_ */
