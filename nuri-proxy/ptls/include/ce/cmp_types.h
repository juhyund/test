#ifndef _CMP_TYPES_H
#define _CMP_TYPES_H

#include "x509com.h"
#include "x509pkc.h"
#include "pkcs.h"
#include "cms.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
 * RFC 2511 - Certificate Request Message Format
 */

/* 6. Control */
typedef SeqOfAttributeTypeAndValue Controls;

#define AD_Controls AD_SeqOfAttributeTypeAndValue

#define Controls_GetByType SeqOfAttributeTypeAndValue_GetByType

/* 5. CertRequest */
typedef struct _OptionalValidity {
   ASNSeqClass klass;
   Time *notBefore; /*optional [0] */
   Time *notAfter;  /*optional [1] */
} OptionalValidity;

LIBSPEC_CKM
extern ASNDescriptor AD_OptionalValidity;

typedef struct _CertTemplate {
   ASNSeqClass klass;
   Version *version; /*optional [0] */
   Integer *serialNumber; /*optional [1] */
   AlgorithmIdentifier *signingAlg; /*optional [2] */
   Name *issuer; /*optional [3] */
   OptionalValidity *validity; /*optional [4] */
   Name *subject; /*optional [5] */
   SubjectPublicKeyInfo *publicKey; /*optional [6] */
   UniqueIdentifier *issuerUID; /*optional [7] */
   UniqueIdentifier *subjectUID; /*optional [8] */
   Extensions *extensions; /*optional [9] */
} CertTemplate;

LIBSPEC_CKM
extern ASNDescriptor AD_CertTemplate;


typedef struct _CertRequest {
   ASNSeqClass klass;
   Integer *certReqId;
   CertTemplate *certTemplate;
   Controls *controls;  /* optional */
} CertRequest;

LIBSPEC_CKM
extern ASNDescriptor AD_CertRequest;


/* 4. Proof of Possession */
typedef Integer SubsequentMessage;
enum {
  SubsequentMessage_encrCert = 0,
  SubsequentMessage_challengeResp = 1,
};
#define AD_SubsequentMessage AD_Integer

enum {
  POPOPrivKey_thisMessage = 1,
  POPOPrivKey_subsequentMessage = 2,
  POPOPrivKey_dhMAC = 3,
};

typedef struct _POPOPrivKey {
   ASNChoiceClass klass;
   int		select;
   union{
      BitString *thisMessage;	            /* [0] */
      SubsequentMessage *subsequentMessage;	/* [1] */
      BitString *dhMAC;	                    /* [2] */
   } choice;
} POPOPrivKey;

LIBSPEC_CKM
extern ASNDescriptor AD_POPOPrivKey;

typedef struct _PKMACValue {
   ASNSeqClass klass;
   AlgorithmIdentifier *algId;
   BitString *value;
} PKMACValue;

LIBSPEC_CKM
extern ASNDescriptor AD_PKMACValue;

enum {
  ChoiceAuthInfo_sender = 1,
  ChoiceAuthInfo_publicKeyMAC = 2,
};

typedef struct _ChoiceAuthInfo {
  ASNChoiceClass klass;
  int select;
  union {
    GeneralName *sender; /* [0] */
    PKMACValue *publicKeyMAC; /* No Tag */
  } choice;
} ChoiceAuthInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_ChoiceAuthInfo;

typedef struct _POPOSigningKeyInput {
  ASNSeqClass klass;
  ChoiceAuthInfo *authInfo;
  SubjectPublicKeyInfo *publicKey;
} POPOSigningKeyInput;

LIBSPEC_CKM
extern ASNDescriptor AD_POPOSigningKeyInput;

/**
 * signature는 다음과 같은 값을 가져야 한다.
 * 1. CertReqMsg의 certReq의 CertTemplate가 subject와 publicKey값을 가지고 있는 경우,
 *    poposkInput은 반드시 없어야 되며, 
 *    signature는 반드시 der encoding된 CertReqMsg의 certReq에 대한 서명값이어야 한다.
 *    이어야 한다.
 * 2. CertReqMsg certReq의 CertTemplate가 subject와 publicKey값을 가지고 없는 경우,
 *    popskInput은 반드시 존재해야 하며, 
 *    signature는 반드시 der encoding된 poposkInput에 대한 서명값이어야 한다.
 * (이는 publicKey가 CertTemplate와 poposkInput에 동시에 존재하지 않도록 하기 위해서임)
 */
typedef struct _POPOSigningKey {
  ASNSeqClass klass;
  POPOSigningKeyInput *poposkInput; /* optional [0] */
  AlgorithmIdentifier *algorithmIdentifier;
  BitString *signature;
} POPOSigningKey;

LIBSPEC_CKM
extern ASNDescriptor AD_POPOSigningKey;


enum {
  ProofOfPossession_raVerified = 1,
  ProofOfPossession_signature,
  ProofOfPossession_keyEncipherment,
  ProofOfPossession_keyAgreement
};

typedef struct _ProofOfPossession {
   ASNChoiceClass klass;
   int		select;
   union{
      ASNNull *raVerified;	        /* [0] */
      POPOSigningKey *signature;	/* [1] */
      POPOPrivKey *keyEncipherment;	/* [2] */
      POPOPrivKey *keyAgreement;	/* [3] */
   } choice;
} ProofOfPossession;

LIBSPEC_CKM
extern ASNDescriptor AD_ProofOfPossession;


typedef struct _CertReqMsg {
  ASNSeqClass klass;
  CertRequest *certReq;
  ProofOfPossession *pop; /* optional */
  SeqOfAttributeTypeAndValue *regInfo; /* optional */
} CertReqMsg;

LIBSPEC_CKM
extern ASNDescriptor AD_CertReqMsg;

typedef struct _CertReqMessages {
  ASNSeqOfClass klass;
  int size;
  CertReqMsg **member;
} CertReqMessages;

LIBSPEC_CKM
extern ASNDescriptor AD_CertReqMessages;

/* 6.3 Publication Information Control */
typedef struct _SinglePubInfo {
  ASNSeqClass klass;
  Integer *pubMethod;
  GeneralName *pubLocation; /* optional */
} SinglePubInfo;
enum {
  PubMethod_dontCare = 0,
  PubMethod_x500     = 1,
  PubMethod_web      = 2,
  PubMethod_ldap     = 3,
};

LIBSPEC_CKM
extern ASNDescriptor AD_SinglePubInfo;

typedef struct _SeqOfSinglePubInfo {
  ASNSeqOfClass klass;
  int size;
  SinglePubInfo **member;
} SeqOfSinglePubInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfSinglePubInfo;

typedef struct _PKIPublicationInfo {
  ASNSeqClass klass;
  Integer *action;
  SeqOfSinglePubInfo *pubinfos;
} PKIPublicationInfo;
enum {
  Action_dontPublish  = 0,
  Action_plesePublish = 1,
};

LIBSPEC_CKM
extern ASNDescriptor AD_PKIPublicationInfo;

/* 6.4 Archive Options Control */
typedef OctetString KeyGenParameters;
#define AD_KeyGenParameters AD_OctetString

typedef struct _EncryptedValue {
  ASNSeqClass klass;
  AlgorithmIdentifier *intendedAlg; /* optional [0] */
  AlgorithmIdentifier *symmAlg;     /* optional [1] */
  BitString *encSymmKey;            /* optional [2] */
  AlgorithmIdentifier *keyAlg;      /* optional [3] */
  OctetString *valueHint;           /* optional [4] */
  BitString *encValue;
} EncryptedValue;

LIBSPEC_CKM
extern ASNDescriptor AD_EncryptedValue;

enum{
  CRMFEncryptedKey_encryptedValue = 1,
  CRMFEncryptedKey_envelopedData
};
typedef struct _CRMFEncryptedKey {
   ASNChoiceClass klass;
   int		select;
   union{
      EncryptedValue *encryptedValue;
      EnvelopedData *envelopedData;	/* [0] */
   }choice;
} CRMFEncryptedKey;

LIBSPEC_CKM
extern ASNDescriptor AD_CRMFEncryptedKey;

enum{
  PKIArchiveOptions_encryptedPrivKey = 1,
  PKIArchiveOptions_keyGenParameters,
  PKIArchiveOptions_archiveRemGenPrivKey
};
typedef struct _PKIArchiveOptions {
  ASNChoiceClass klass;
  int select;
  union {
    CRMFEncryptedKey *encryptedPrivKey;     /* [0] */
    KeyGenParameters *keyGenParameters; /* [1] */
    Boolean *archiveRemGenPrivKey;      /* [2] */
  } choice;
} PKIArchiveOptions;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIArchiveOptions;

/* 6.5 OldCert ID Control */
typedef struct _CertId {
  ASNSeqClass klass;
  GeneralName *issuer;
  Integer *serialNumber;
} CertId;

LIBSPEC_CKM
extern ASNDescriptor AD_CertId;

typedef CertId OldCertId;
#define AD_OldCertId AD_CertId

typedef struct _SeqOfCertId {
  ASNSeqOfClass klass;
  int size;
  CertId **member;
} SeqOfCertId;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfCertId;

typedef UTF8String UTF8Pairs;
#define AD_UTF8Pairs AD_UTF8String

typedef SubjectPublicKeyInfo ProtocolEncrKey;
#define AD_ProtocolEncrKey AD_SubjectPublicKeyInfo


typedef struct _PBMParameter {
   ASNSeqClass klass;
   OctetString *salt;
   AlgorithmIdentifier *owf;
   Integer *iterationCount;
   AlgorithmIdentifier *mac;
} PBMParameter;

LIBSPEC_CKM
extern ASNDescriptor AD_PBMParameter;



/******************************************************************************
 * RFC 2510 - Certificate Management Protocol
 */

typedef struct _PKIFreeText {
  ASNSeqOfClass klass;
  int size;
  UTF8String **member;
} PKIFreeText;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIFreeText;

/* 3.2 Common Data Structures */

/* 3.2.1 Requested Certificate Contents - See CRMF for CertTemplate */

/* 3.2.2 Encrypted Values - See CRMF for EncryptedValue */

/* 3.2.3 Status Codes and Failure  Information for PKI messages */
typedef Integer PKIStatus;
enum {
  PKIStatus_accepted               = 0,
  PKIStatus_grantedWithMods        = 1,
  PKIStatus_rejection              = 2,
  PKIStatus_waiting                = 3,
  PKIStatus_revocationWarning      = 4,
  PKIStatus_revocationNotification = 5,
  PKIStatus_keyUpdateWaring        = 6,
};
#define AD_PKIStatus AD_Integer

typedef BitString PKIFailureInfo;
/*
enum {
  PKIFailureInfo_badAlg               = (0x80000000 >> 0),
  PKIFailureInfo_badMessageCheck      = (0x80000000 >> 1),
  PKIFailureInfo_badRequest           = (0x80000000 >> 2),
  PKIFailureInfo_badTime              = (0x80000000 >> 3),
  PKIFailureInfo_badCertId            = (0x80000000 >> 4),   0x08000000 */
/*  PKIFailureInfo_badDataFormat        = (0x80000000 >> 5),
  PKIFailureInfo_wrongAuthority       = (0x80000000 >> 6),
  PKIFailureInfo_incorrectData        = (0x80000000 >> 7),
  PKIFailureInfo_missingTimeStamp     = (0x80000000 >> 8),   0x00800000 */
/*  PKIFailureInfo_badPOP               = (0x80000000 >> 9),
   defined in rfc2510-draft(04) */
/*  PKIFailureInfo_certRevoked          = (0x80000000 >> 10),
  PKIFailureInfo_certConfirmed        = (0x80000000 >> 11),
  PKIFailureInfo_wrongIntegrity       = (0x80000000 >> 12),  0x00080000 */
/*  PKIFailureInfo_badRecipientNonce    = (0x80000000 >> 13),
  PKIFailureInfo_timeNotAvailable     = (0x80000000 >> 14),
  PKIFailureInfo_unacceptedPolicy     = (0x80000000 >> 15),
  PKIFailureInfo_unacceptedExtension  = (0x80000000 >> 16),  0x00008000 */
/*  PKIFailureInfo_addInfoNotAvailable  = (0x80000000 >> 17),
  PKIFailureInfo_badSenderNonce       = (0x80000000 >> 18),
  PKIFailureInfo_badCertTemplate      = (0x80000000 >> 19),
  PKIFailureInfo_signerNotTrusted     = (0x80000000 >> 20),  0x00000800 */
/*  PKIFailureInfo_transactionIdInUse   = (0x80000000 >> 21), 
  PKIFailureInfo_unsupportedVersion   = (0x80000000 >> 22),
  PKIFailureInfo_notAuthorized        = (0x80000000 >> 23),
  PKIFailureInfo_systemUnavail        = (0x80000000 >> 24),  0x00000080 */
/*  PKIFailureInfo_systemFailure        = (0x80000000 >> 25),
  PKIFailureInfo_duplicateCertReq     = (0x80000000 >> 26),
};
*/
#define PKIFailureInfo_badAlg               0x80000000
#define PKIFailureInfo_badMessageCheck      0x40000000
#define PKIFailureInfo_badRequest           0x20000000
#define PKIFailureInfo_badTime              0x10000000
#define PKIFailureInfo_badCertId            0x08000000
#define PKIFailureInfo_badDataFormat        0x04000000
#define PKIFailureInfo_wrongAuthority       0x02000000
#define PKIFailureInfo_incorrectData        0x01000000
#define PKIFailureInfo_missingTimeStamp     0x00800000
#define PKIFailureInfo_badPOP               0x00400000
/* defined in rfc2510-draft(04) */
#define PKIFailureInfo_certRevoked          0x00200000
#define PKIFailureInfo_certConfirmed        0x00100000
#define PKIFailureInfo_wrongIntegrity       0x00080000
#define PKIFailureInfo_badRecipientNonce    0x00040000
#define PKIFailureInfo_timeNotAvailable     0x00020000
#define PKIFailureInfo_unacceptedPolicy     0x00010000
#define PKIFailureInfo_unacceptedExtension  0x00008000
#define PKIFailureInfo_addInfoNotAvailable  0x00004000
#define PKIFailureInfo_badSenderNonce       0x00002000
#define PKIFailureInfo_badCertTemplate      0x00001000
#define PKIFailureInfo_signerNotTrusted     0x00000800
#define PKIFailureInfo_transactionIdInUse   0x00000400
#define PKIFailureInfo_unsupportedVersion   0x00000200
#define PKIFailureInfo_notAuthorized        0x00000100
#define PKIFailureInfo_systemUnavail        0x00000080
#define PKIFailureInfo_systemFailure        0x00000040
#define PKIFailureInfo_duplicateCertReq     0x00000020

#define AD_PKIFailureInfo AD_BitString

typedef struct _PKIStatusInfo {
  ASNSeqClass klass;
  PKIStatus *status;
  PKIFreeText *statusString; /* optional */
  PKIFailureInfo *failInfo; /* optional */
} PKIStatusInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIStatusInfo;

typedef struct _SeqOfPKIStatusInfo {
  ASNSeqOfClass klass;
  int size;
  PKIStatusInfo **member;
} SeqOfPKIStatusInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfPKIStatusInfo;

/* 3.2.4 Certificate Identification - See CRMF for CertId */

/* 3.2.5 "Out-of-band" root CA public key */
typedef Certificate OOBCert;
#define AD_OOBCert AD_Certificate

typedef struct _OOBCertHash {
  ASNSeqClass klass;
  AlgorithmIdentifier *hashAlg; /* optional [0] */
  CertId *certId; /* optional [1] */
  BitString *hashVal;
} OOBCertHash;

LIBSPEC_CKM
extern ASNDescriptor AD_OOBCertHash;



/* 3.3 Operation-Specific Data Structures */

/* 3.3.1 Initialization Request - See CRMF for CertReqMessages */

/* 3.3.2 Initialization Response - See 3.3.4 for CertReqMessage */

/* 3.3.3 Registration/Certification Request - See CRMF for CertReqMessages */

/* 3.3.4 Registration/Certification Response */

enum {
  CertOrEncCert_certificate = 1,
  CertOrEncCert_encryptedCert = 2,
};

typedef struct{
   ASNChoiceClass klass;
   int		select;
   union {
      Certificate *certificate;	/* [0] */
      EncryptedValue *encryptedCert;	/* [1] */
   } choice;
} CertOrEncCert;

LIBSPEC_CKM
extern ASNDescriptor AD_CertOrEncCert;

typedef struct _CertifiedKeyPair {
  ASNSeqClass klass;
  CertOrEncCert *certOrEncCert;
  EncryptedValue *privateKey;          /* optional [0] */
  PKIPublicationInfo *publicationInfo; /* optional [1] */
} CertifiedKeyPair;

LIBSPEC_CKM
extern ASNDescriptor AD_CertifiedKeyPair;

typedef struct _SeqOfCertifiedKeyPair {
  ASNSeqOfClass klass;
  int size;
  CertifiedKeyPair **member;
} SeqOfCertifiedKeyPair;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfCertifiedKeyPair;

typedef struct _CertResponse {
  ASNSeqClass klass;
  Integer *certReqId;
  PKIStatusInfo *status;
  CertifiedKeyPair *certifiedKeyPair; /* optional */
  OctetString *rspInfo;               /* optional */
} CertResponse;

LIBSPEC_CKM
extern ASNDescriptor AD_CertResponse;

typedef struct _SeqOfCertResponse {
  ASNSeqOfClass klass;
  int size;
  CertResponse **member;
} SeqOfCertResponse;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfCertResponse;

typedef struct _CertRepMessage {
  ASNSeqClass klass;
  SeqOfCertificate *caPubs; /* optional [1] */
  SeqOfCertResponse *response;
} CertRepMessage;

LIBSPEC_CKM
extern ASNDescriptor AD_CertRepMessage;

/* 3.3.5 Key Update Request - See CRMF for CertReqMessages */

/* 3.3.6 Key Update Response - See CRMF for CertReqMessages */

/* 3.3.7 Key Recovery Request - See CRMF for CertReqMessages */

/* 3.3.8 Key Recovery Response */
typedef struct _KeyRecRepContent {
  ASNSeqClass klass;
  PKIStatusInfo *status;
  Certificate *newSigCert;            /* optional [0] */
  SeqOfCertificate *caCerts;          /* optional [1] */
  SeqOfCertifiedKeyPair *keyPairHist; /* optional [2] */
} KeyRecRepContent;

LIBSPEC_CKM
extern ASNDescriptor AD_KeyRecRepContent;

/* 3.3.9 Revocation Request */
typedef struct _RevDetails {
  ASNSeqClass klass;
  CertTemplate *certDetails;
  ReasonFlags *revocationReason; /* optional */
  GeneralizedTime *badSinceData; /* optional */
  Extensions *crlEntryDetails;   /* optional */
} RevDetails;

LIBSPEC_CKM
extern ASNDescriptor AD_RevDetails;

typedef struct _RevReqContent {
  ASNSeqOfClass klass;
  int size;
  RevDetails **member;
} RevReqContent;

LIBSPEC_CKM
extern ASNDescriptor AD_RevReqContent;

/* 3.3.10 Revocation Response */
typedef struct _RevRepContent {
  ASNSeqClass klass;
  SeqOfPKIStatusInfo *status;
  SeqOfCertId *revCerts;      /* optional [0] */
  SeqOfCertificateList *crls; /* optional [1] */
} RevRepContent;

LIBSPEC_CKM
extern ASNDescriptor AD_RevRepContent;

/* 3.3.11 Cross Certification Request - See CRMF for CertReqMessages */

/* 3.3.12 Cross Certification Response - See CRMF for CertRepMessages */

/* 3.3.13 CA Key Update Announcement */
typedef struct _CAKeyUpdAnnContent {
  ASNSeqClass klass;
  Certificate *oldWithNew;
  Certificate *newWithOld;
  Certificate *newWithNew;
} CAKeyUpdAnnContent;

LIBSPEC_CKM
extern ASNDescriptor AD_CAKeyUpdAnnContent;

/* 3.3.14 Certificate Announcement */
typedef Certificate CertAnnContent;
#define AD_CertAnnContent AD_Certificate

/* 3.3.15 Revocation Announcement */
typedef struct _RevAnnContent {
  ASNSeqClass klass;
  PKIStatus *status;
  CertId *certId;
  GeneralizedTime *willBeRevokedAt;
  GeneralizedTime *badSinceDate;
  Extensions *crlDetails; /* optional */
} RevAnnContent;

LIBSPEC_CKM
extern ASNDescriptor AD_RevAnnContent;

/* 3.3.16 CRL Announcement */
typedef SeqOfCertificateList CRLAnnContent;
#define AD_CRLAnnContent AD_SeqOfCertificateList

/* 3.3.17 PKI Confirmation */
typedef ASNNull PKIConfirmContent;
#define AD_PKIConfirmContent AD_ASNNull

/* 3.3.18 PKI General Message */
typedef struct _InfoTypeAndValue {
  ASNSeqClass klass;
  ASNOid *infoType;
  ASNAny *infoValue; /* optional */
} InfoTypeAndValue;

LIBSPEC_CKM
extern ASNDescriptor AD_InfoTypeAndValue;

typedef struct _SeqOfInfoTypeAndValue {
  ASNSeqOfClass klass;
  int size;
  InfoTypeAndValue **member;
} SeqOfInfoTypeAndValue;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfInfoTypeAndValue;

typedef SeqOfInfoTypeAndValue GenMsgContent;
#define AD_GenMsgContent AD_SeqOfInfoTypeAndValue

/* 3.3.19 PKI General Response */
typedef SeqOfInfoTypeAndValue GenRepContent;
#define AD_GenRepContent AD_SeqOfInfoTypeAndValue

/* 3.3.20 Error Message */
typedef struct _ErrorMsgContent {
  ASNSeqClass klass;
  PKIStatusInfo *pKIStatusInfo;
  Integer *errorCode; /* optional */
  PKIFreeText *errorDetails; /* optional */
} ErrorMsgContent;

LIBSPEC_CKM
extern ASNDescriptor AD_ErrorMsgContent;



/* 3.1 Overall PKI Message */
typedef struct _PKIHeader {
  ASNSeqClass klass;
  Integer *pvno;
  GeneralName *sender;
  GeneralName *recipient;
  GeneralizedTime *messageTime;       /* optional [0] */
  AlgorithmIdentifier *protectionAlg; /* optional [1] */
  KeyIdentifier *senderKID;           /* optional [2] */
  KeyIdentifier *recipKID;            /* optional [3] */
  OctetString *transactionID;         /* optional [4] */
  OctetString *senderNonce;           /* optional [5] */
  OctetString *recipNonce;            /* optional [6] */
  PKIFreeText *freeText;              /* optional [7] */
  SeqOfInfoTypeAndValue *generalInfo; /* optional [8] */
} PKIHeader;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIHeader;

enum {
  PKIBody_ir  = 1,
  PKIBody_ip,
  PKIBody_cr,
  PKIBody_cp,
  /*PKIBody_p10cr, */
  /*PKIBody_popdecc, */
  /*PKIBody_popdecr, */
  PKIBody_kur,
  PKIBody_kup,
  PKIBody_krr,
  PKIBody_krp,
  PKIBody_rr,
  PKIBody_rp,
  PKIBody_ccr,
  PKIBody_ccp,
  PKIBody_ckuann,
  PKIBody_cann,
  PKIBody_rann,
  PKIBody_crlann,
  PKIBody_conf,
  /*PKIBody_nested, */
  PKIBody_genm,
  PKIBody_genp,
  PKIBody_error
};

typedef struct {
  ASNChoiceClass klass;
  int select;
  union {
    CertReqMessages *ir;             /* [0] */
    CertRepMessage *ip;              /* [1] */
    CertReqMessages *cr;             /* [2] */
    CertRepMessage *cp;              /* [3] */
/*    CertificationRequest *p10cr;     *//* [4] */
/*    POPODecKeyChallContent *popdecc; *//* [5] */
/*    POPODecKeyRespContent *popdecr;  *//* [6] */
    CertReqMessages *kur;            /* [7] */
    CertRepMessage *kup;             /* [8] */
    CertReqMessages *krr;            /* [9] */
    KeyRecRepContent *krp;           /* [10] */
    RevReqContent *rr;               /* [11] */
    RevRepContent *rp;               /* [12] */
    CertReqMessages *ccr;            /* [13] */
    CertRepMessage *ccp;             /* [14] */
    CAKeyUpdAnnContent *ckuann;      /* [15] */
    CertAnnContent *cann;            /* [16] */
    RevAnnContent *rann;             /* [17] */
    CRLAnnContent *crlann;           /* [18] */
    PKIConfirmContent *conf;         /* [19] */
/*    NestedMessageContent *nested;    *//* [20] */
    GenMsgContent *genm;             /* [21] */
    GenRepContent *genp;             /* [22] */
    ErrorMsgContent *error;          /* [23] */
  } choice;
} PKIBody;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIBody;

typedef BitString PKIProtection;
#define AD_PKIProtection AD_BitString

typedef struct _ProtectedPart {
  ASNSeqClass klass;
  PKIHeader *header;
  PKIBody *body;
} ProtectedPart;

LIBSPEC_CKM
extern ASNDescriptor AD_ProtectedPart;

typedef struct _PKIMessage {
  ASNSeqClass klass;
  PKIHeader *header;
  PKIBody *body;
  PKIProtection *protection; /* optional [0] */
  SeqOfCertificate *extraCerts; /* optional [1] */
} PKIMessage;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIMessage;

typedef PKIMessage NestedMessageContent;
#define AD_NestedMessageContent AD_PKIMessage

typedef ASNOid PasswordBasedMac;
#define AD_PasswordBasedMac AD_ASNOid

typedef ASNOid DHBasedMac;
#define AD_DHBasedMac AD_ASNOid

typedef struct _DHBMParameter {
   ASNSeqClass klass;
   AlgorithmIdentifier *owf;
   AlgorithmIdentifier *mac;
} DHBMParameter;

LIBSPEC_CKM
extern ASNDescriptor AD_DHBMParameter;

typedef struct _Challenge {
   ASNSeqClass klass;
   AlgorithmIdentifier *owf;
   OctetString *witness;
   OctetString *challenge;
} Challenge;

LIBSPEC_CKM
extern ASNDescriptor AD_Challenge;

typedef struct _POPODecKeyChallContent {
   ASNSeqOfClass klass;
   int		size;
   Challenge **member;
} POPODecKeyChallContent;

LIBSPEC_CKM
extern ASNDescriptor AD_POPODecKeyChallContent;

typedef struct _POPODecKeyRespContent {
   ASNSeqOfClass klass;
   int		size;
   Integer **member;
} POPODecKeyRespContent;

LIBSPEC_CKM
extern ASNDescriptor AD_POPODecKeyRespContent;

/******************************************************************************
 * Penta의 General Message와 General Response CMP 확장
 */

/*

KeyPolicyRequest  ::=  SEQUENCE {
        transacId          OCTET STRING,
        requesterRefNum    OCTET STRING OPTIONAL,
        requesterName      Name OPTIONAL,
        rAPolicy           NULL OPTIONAL }

KeyPolicy  ::=  SEQUENCE  {
     identifier           PrintableString,
     name                 UTF8String,
     keyAlgorithm         AlgorithmIdentifier,
     keyBitLength         INTEGER,
     additionalInfos      SEQUENCE SIZE (1..MAX) OF InfoTypeAndValue OPTIONAL  }

KeyPolicies  ::=  SEQUENCE  {
     transacId           OCTET STRING,
     policies            SEQUENCE SIZE (1..MAX) OF KeyPolicy,
     additionalInfos     SEQUENCE SIZE (1..MAX) OF InfoTypeAndValue OPTIONAL  }
*/

typedef struct _KeyPolicyRequest {
   ASNSeqClass   klass;
   OctetString  *transacId;
   OctetString  *requesterId;      /* OPTIONAL */
   Name         *requesterName;    /* OPTIONAL */
   ASNNull      *rAPolicy;         /* OPTIONAL */
} KeyPolicyRequest;

LIBSPEC_CKM
extern ASNDescriptor AD_KeyPolicyRequest;

typedef struct _KeyPolicy {
   ASNSeqClass            klass;
   OctetString           *identifier;
   UTF8String            *name;
   AlgorithmIdentifier   *keyAlgorithm;
   Integer               *keyBitLength;
   PrintableString       *validity;           /**< yy/mm/dd/hh 로 표시 */
   PrintableString       *ldapAttr;           /**< OPTIONAL */
   Extensions            *extensions;         /**< OPTIONAL Extensions 정보 */
   SeqOfInfoTypeAndValue *additionalInfos;    /* OPTIONAL */
   ASNNull               *rAIssuanceAllowed;  /* OPTIONAL */
} KeyPolicy;

LIBSPEC_CKM
extern ASNDescriptor AD_KeyPolicy;

typedef struct _SeqOfKeyPolicy {
   ASNSeqOfClass  klass;
   int            size;
   KeyPolicy    **member;
} SeqOfKeyPolicy;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfKeyPolicy;

typedef struct _KeyPolicies {
   ASNSeqClass            klass;
   OctetString           *transacId;
   SeqOfKeyPolicy        *policies;
   SeqOfInfoTypeAndValue *additionalInfos;  /* OPTIONAL */
} KeyPolicies;

LIBSPEC_CKM
extern ASNDescriptor AD_KeyPolicies;

#ifdef __cplusplus
}
#endif

#endif /* _CMP_H */
