#ifndef _ocsp_h
#define _ocsp_h

#include "ckm_pkcrypt.h"
#include "x509pkc.h"

/** @defgroup OCSP OCSP handling
 * @ingroup CKM
    @brief OCSP �޽��� ���� ���
*/

/** @file ocsp.h
    @ingroup OCSP
    @brief OCSP Ÿ�԰� ocsp �޽��� ���� �Լ� ����
    
    OCSP ������ Ŭ���̾�Ʈ���� �ְ� �޴� �޽����� Ÿ�԰� �޽��� ���� �Լ�
    OCSP(Online Certificate Status Protocol) Ÿ��
    OCSP ���� �Լ�
*/
  
#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Type defines
 ****************************************************************************/


/****************************************************************
 * CertID
 */

typedef struct {
  ASNSeqClass             Klass;
  AlgorithmIdentifier     *hashAlgorithm;
  OctetString             *issuerNameHash;
  OctetString             *issuerKeyHash;
  CertificateSerialNumber *serialNumber;
} CertID;

LIBSPEC_CKM
extern ASNDescriptor AD_CertID;




/****************************************************************
 * Request
 */

typedef struct {
  ASNSeqClass  klass;
  CertID      *reqCert;
  Extensions  *singleRequestExtensions; /**< optional */
} Request;

LIBSPEC_CKM
extern ASNDescriptor AD_Request;



/****************************************************************
 * Version
 */

enum {
  OCSP_REQUEST_VER1 = 0, /**< default */
  OCSP_REQUEST_VER2
};


/*****************************************************************
 * TBSRequest
 */

typedef struct {
  ASNSeqOfClass  klass;
  int            size;
  Request      **member;
} SeqOfRequest;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfRequest;

typedef struct {
  ASNSeqClass   klass;
  Version      *version;
  GeneralName  *requestorName;     /**< optional */
  SeqOfRequest *requestList;
  Extensions   *requestExtensions; /**< optional */
} TBSRequest;

LIBSPEC_CKM
extern ASNDescriptor AD_TBSRequest;



/*****************************************************************
 * Signature
 */

typedef struct {
  ASNSeqClass           klass;
  AlgorithmIdentifier  *signatureAlgorithm;
  BitString            *signature;
  SeqOfCertificate     *certs;
} Signature;

LIBSPEC_CKM
extern ASNDescriptor AD_Signature;



/*****************************************************************
 * OCSPRequest
 */

typedef struct {
  ASNSeqClass    klass;
  TBSRequest    *tbsRequest;
  Signature     *optionalSignature; /**< optional */

} OCSPRequest;

LIBSPEC_CKM 
extern ASNDescriptor AD_OCSPRequest;
    


/*********************************************************
 * RevokedInfo
 */

typedef struct {
  ASNSeqClass       klass;
  GeneralizedTime  *revocationTime;
  CRLReason        *revocationReason;
} RevokedInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_RevokedInfo;



/*********************************************************
 * UnknownInfo
 */

typedef ASNNull UnknownInfo;
#define AD_UnknownInfo AD_ASNNull



/*********************************************************
 * ArchiveCutoff
 */

typedef GeneralizedTime ArchiveCutoff;
#define AD_ArchiveCutoff AD_GeneralizedTime


/*********************************************************
 * CrlID
 */
typedef struct {
  ASNSeqClass       klass;
  IA5String        *crlUrl;
  Integer          *crlNum;
  GeneralizedTime  *crlTime;
} CrlID;

LIBSPEC_CKM
extern ASNDescriptor AD_CrlID;

/*********************************************************
 * AcceptableResponses
 */

typedef struct {
  ASNSeqOfClass  klass;
  int            size;
  ASNOid       **member;
} AcceptableResponses;

LIBSPEC_CKM
extern ASNDescriptor AD_AcceptableResponses;




/*********************************************************
 * ServiceLocator
 */

typedef struct {
  ASNSeqClass                 klass;
  Name                       *issuer;
  AuthorityInfoAccessSyntax  *locator;
} ServiceLocator;


LIBSPEC_CKM
extern ASNDescriptor AD_ServiceLocator;


/**********************************************************
 * CertStatus
 */

typedef struct {
  ASNChoiceClass klass;
  int            select;
  union {
    Null         *good;
    RevokedInfo  *revoked;
    UnknownInfo  *unknown;
  } choice;
} CertStatus;

LIBSPEC_CKM
extern ASNDescriptor AD_CertStatus;

enum {
    CERTSTATUS_GOOD = 1, /**< �������� �������� ���� ���� */
    CERTSTATUS_REVOKED,  /**< �������� ������ ���� */
    CERTSTATUS_UNKNOWN   /**< �������� ���¸� �� �� ���� */
};



/**********************************************************
 * SingleResponse
 */

typedef struct {
  ASNSeqClass       klass;
  CertID           *certID;
  CertStatus       *certStatus;
  GeneralizedTime  *thisUpdate;
  GeneralizedTime  *nextUpdate;       /**< optional */
  Extensions       *singleExtensions; /**< optional */
} SingleResponse;

LIBSPEC_CKM
extern ASNDescriptor AD_SingleResponse;



/*************************************************************
 * KeyHash
 */

typedef OctetString KeyHash;
#define AD_KeyHash AD_OctetString


#define KeyHash_set(KeyHash, in, len) ASNOctStr_Set(KeyHash, in, len)
#define KeyHash_Get(out, mlen, KeyHash) ASNOctStr_Get(out, mlen, KeyHash)



/***********************************************************
 * ResponderID
 */

typedef struct {
  ASNChoiceClass klass;
  int            select;
  union  {
  Name     *byName;
  KeyHash  *byKey;
  } choice;
} ResponderID;

LIBSPEC_CKM
extern ASNDescriptor AD_ResponderID;





/*************************************************************
 * ResponseData
 */

typedef struct {
  ASNSeqOfClass    klass;
  int              size;
  SingleResponse **member;
} SeqOfSingleResponse;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfSingleResponse;

typedef struct {
  ASNSeqClass           klass;
  Version              *version;
  ResponderID          *responderID;
  GeneralizedTime      *producedAt;
  SeqOfSingleResponse  *responses;
  Extensions           *responseExtensions; /**< optional */
} ResponseData;

LIBSPEC_CKM
extern ASNDescriptor AD_ResponseData;



/**************************************************************
 * BasicOCSPResponse
 */

typedef struct {
  ASNSeqClass           klass;
  ResponseData         *tbsResponseData;
  AlgorithmIdentifier  *signatureAlgorithm;
  BitString            *signature;
  SeqOfCertificate     *certs;   /**< optional */
} BasicOCSPResponse;

LIBSPEC_CKM
extern ASNDescriptor AD_BasicOCSPResponse;





/**************************************************************
 * ResponseBytes
 */

typedef struct {
  ASNSeqClass   klass;
  ASNOid       *responseType;
  OctetString  *response;
} ResponseBytes;


LIBSPEC_CKM
extern ASNDescriptor AD_ResponseBytes;





/***************************************************************
 * OCSPResponseStatus
 */

typedef Enumerate OCSPResponseStatus;
#define AD_OCSPResponseStatus AD_Enumerate


enum {
  OCSPResponseStatus_successful      = 0,
  OCSPResponseStatus_malformedRequest  = 1,  /**< request�� ocsp ������ ���� ���� ��� */
  OCSPResponseStatus_internalError    = 2,   /**< responder�� ���� ���� �߻��� */
  OCSPResponseStatus_tryLater      = 3,      /**< responder�� ���񽺸� ��� �ߴ��� ��� */
  OCSPResponseStatus_sigRequired    = 5,     /**< OCSPRequest�� Ŭ���̾�Ʈ ������ ���ԵǾ� �־�߸� ���� ��� */
  OCSPResponseStatus_unauthorized    = 6,    /**< ���� ������ �㰡���� ���� ����ڿ��Լ� ��û�� �� ��� */
};




/***************************************************************
 * OCSPResponse
 */

typedef struct {
  ASNSeqClass          klass;
  OCSPResponseStatus  *responseStatus;
  ResponseBytes       *responseBytes;  /**< optional */
} OCSPResponse;

LIBSPEC_CKM
extern ASNDescriptor AD_OCSPResponse;




/****************************************************************************
 * OCSP API defines
 ****************************************************************************/

/***************************************************************
 * Create OCSP Request
 */

/**
  @ingroup OCSP
  @brief Request �޽����� �����Ѵ�.
  @param unverifiedCert  [in] ��ȿ���� �����ϰ��� �ϴ� ������
  @param issuerCert      [in] �����ϰ��� �ϴ� �������� �߱��� CA ������
  
  return : success�̸� Request*, fail�̸� NULL
           Request -> CertID�� singleRequestExtension���� �̷������.
                         
  unverifiedCert���� DN�� serlalNumber�� ������ issuerCert���� public Key�� ������ 
  CertID�� �����.
  
*/
LIBSPEC_CKM
extern Request* OCSP_NewRequest(Certificate *unverifiedCert,
                                Certificate *issuerCert);

/** @ingroup OCSP
    @brief Request �޽����� �����Ѵ�.
    @param[in] unverifiedCert  ��ȿ���� �����ϰ��� �ϴ� ������
    @param[in] issuerCert      �����ϰ��� �ϴ� �������� �߱��� CA ������
    @param[in] hashNid         �ؽ� �˰����� NID

    return : success�̸� Request*, fail�̸� NULL
             Request -> CertID�� singleRequestExtension���� �̷������.
                         
    unverifiedCert���� DN�� serlalNumber�� ������ issuerCert���� public Key�� ������ 
    CertID�� �����.
*/
LIBSPEC_CKM
extern Request* OCSP_NewRequest_WithHashNid(Certificate *unverifiedCert,
                                            Certificate *issuerCert,
                                            Nid         hashNid);

/** @ingroup OCSP
    @brief Request �޽����� singleRequestExtensions �ʵ� ó��
    @param[in] extension  serviceLocator
    @param[in] nid        id-pkix-ocsp-service-locator�� ��ġ�ϴ� nid

    return : success�̸� SUCCESS, fail�̸� FAIL
             Request�� extension�� NULL�� ��쿡�� INVALID_ARG�� ���ϵȴ�.

    Request �޽����� singleRequestExtension �ʵ忡 serviceLocator�� ǥ���Ѵ�.
*/
LIBSPEC_CKM
extern int OCSP_AddSingleRequestExtensions(Request *request,
             ASN *extension, Nid nid);


/**
    @ingroup OCSP
    @brief OCSPRequest �޽����� �����Ѵ�.
    @param nonce     [out] replay attack�� ���� ���� nonce ����
    @param nonceLen  [out] nonce�� ����Ʈ ����

	return : success�̸� OCSPRequest*, fail�̸� NULL
		 OCSPRequest -> Request  �޽����� ������ ���� ��û���� �������� �̷������.
    
	  
    OCSPRequest �޽����� �����ϰ� nonce�� nonceLen�� �����Ѵ�. 
    ���� nonce�� �Է����� NULL�� ���´ٸ� nonce�� ������ �ʴ´�.
    
*/
LIBSPEC_CKM
extern OCSPRequest* OCSP_NewOCSPRequest(char *nonce, int *nonceLen); 

/**
    @ingroup OCSP
    @brief OCSPRequest �޽����� requestExtensions �ʵ� ó��     
    @param extension  [in] nonce, Acceptable Response Types
    @param nid        [in] id-pkix-ocsp-nonce�� ��ġ�ϴ� nid, id-pkix-ocsp-basic�� ��ġ�ϴ� nid

	return : success�̸� SUCCESS, fail�̸� FAIL
		 ocspRequest�� extension�� NULL�� ��쿡�� INVALID_ARG�� ���ϵȴ�.
    
    OCSPRequest �޽����� requestExtensions �ʵ忡 nonce, Acceptable Response Types�� �߰��Ѵ�.
    
*/
LIBSPEC_CKM
extern int OCSP_AddRequestExtensions(OCSPRequest *ocspRequest,
             ASN *extension, Nid nid);


/**
    @param Request �޽����� �Ѱ� �̻��� ��� ��Ƽ� ������.
*/
#define OCSP_AddRequestP(ocspRequest, request)  \
ASNSeqOf_AddP(ASN_SEQOF((ocspRequest)->tbsRequest->requestList), ASN(request));

/**
    @ingroup OCSP
    @brief OCSPReqeust �޽����� �����ϴ� �Լ��̴�.
    @param[out] ocspRequest   OCSPRequest
    @param[in]  clientPriInfo ���� ��û���� �����Ű
    @param[in]  clientCert    ���� ��û���� ������
    @param[in]  domainParam   ������ �Ķ����
    @param[in]  certs         �����ϰ��� �ϴ� �������� ���� ���

    return : success�̸� SUCCESS, fail�̸� FAIL
             clientCert �Ǵ� clientPriInfo�� NULL�� ��쿡�� FAIL

    OCSPRequest �޽����� ������ ���� ��û���� �����Ű�� �����Ѵ�.
*/
LIBSPEC_CKM
ERT OCSP_SignOCSPRequest(OCSPRequest    *ocspRequest,
                         PrivateKeyInfo *clientPriInfo,
                         Certificate    *clientCert,
                         Parameter      *domainParam,
                         Certificates   *certs);

/**
    @ingroup OCSP
    @brief OCSPReqeust �޽����� �����ϴ� �Լ��̴�.
    @param[out] ocspRequest  OCSPRequest
    @param[in] clientPriInfo ���� ��û���� �����Ű
    @param[in] clientCert    ���� ��û���� ������
    @param[in] domainParam   ������ �Ķ����
    @param[in] certs         �����ϰ��� �ϴ� �������� ���� ���
    @param[in] hashNid       �ؽ� �˰����� NID

    return : success�̸� SUCCESS, fail�̸� FAIL
             clientCert �Ǵ� clientPriInfo�� NULL�� ��쿡�� FAIL

    OCSPRequest �޽����� ������ ���� ��û���� �����Ű�� �����Ѵ�.
*/
LIBSPEC_CKM
ERT OCSP_SignOCSPRequest_WithHashNid(OCSPRequest    *ocspRequest,
                                     PrivateKeyInfo *clientPriInfo,
                                     Certificate    *clientCert,
                                     Parameter      *domainParam,
                                     Certificates   *certs,
                                     Nid            hashNid);

/***************************************************************
 * Receive OCSP Request
 */

/** @ingroup OCSP
 * @brief   OCSPRequest �޽����� �ִ� ���� ��û���� ������ �����Ѵ�.
 * @param[in]   request  OCSPRequest �޽���
 * @param[in]   param    �����ϰ����ϴ� �������� ������ �Ķ���Ͱ� �������
 * 						 ���� ��쿡�� ó���� �� �ֵ��� ��
 * @retval SUCCESS valid signature
 * @retval 1 no signature
 * @retval FAIL invalid signature
 *
 * ������ OCSPRequest �޽������� ������ ���� ��û���� ������ ������ ���
 * �����ϰ����ϴ� �������� ������ �Ķ���Ͱ� ������� �ʴ��� ������
 * �Ķ���͸� ó���� �� �ִ�.
*/
LIBSPEC_CKM
ERT OCSP_ValidateRequestSignature( OCSPRequest *request,
                                   Parameter   *domainParam);

/**
    @ingroup OCSP
    @brief   OCSPRequest �޽������� nonce ���� 
    @param   nonce   [out] OCSPRequest �޽����� requestExtensions �ʵ��� nonce
    @param   maxLen  [in] nonce�� �� ������ �ִ� ����
    @param   request [in] OCSPRequest �޽���

    return : success�̸� �����, fail�̸� 0

    OCSPRequest �޽����� requestExtensions�ʵ忡 �ִ� nonce�� ������.
*/
LIBSPEC_CKM
extern int OCSP_GetRequestNonce(char *nonce, int maxLen, 
                                OCSPRequest *request);


/**
    @ingroup OCSP
    @brief   ������ ��û�� �������� ����
    @param   request [in] OCSPRequest �޽���

    ���� ��û�� �������� ������ �˻��Ѵ�.

*/
LIBSPEC_CKM
extern int OCSP_GetRequestNumber(OCSPRequest *request);


/**
    @ingroup OCSP
    @brief �ټ����� Request �޽����� �˻��ϰ����ϴ� Request �޽����� ����
    @param request [in] OCSPRequest �޽��� 
    @param number  [in] OCSPRequest �޽����� �ִ� Request�� �� �����ϰ��� �ϴ�
                        Request �޽����� index ��ȣ

    return : success�̸� Request*, fail�̸� NULL

    OCSPRequest�� ����ִ� �ټ����� Request�� �� ���ϴ� ��ȣ�� Request�� �����͸� �����´�.
*/
LIBSPEC_CKM
extern Request* OCSP_GetRequestP(OCSPRequest *request, int number);


/***************************************************************
 * Create OCSP Response
 */

/**
    @ingroup OCSP
    @brief OCSPResponse �޽����� �����.
    @param status [in] OCSPRequest �޽��� ó���� �������� ���������� ��Ÿ����.

	return : success�̸� OCSPResponse, fail�̸� NULL
			 OCSPResponse -> ResponseStatus�� ResponseBytes�� �̷������.
     
    OCSPRequest �޽����� ����� ó���Ǿ����� �� �� �ִ� �κ�����
    OCSPResponse �޽����� ���� �Ǵ� ������ ǥ���ϰ� OCSPResponse �޽����� �����.
    
    @sa ������ �����̸� OCSPResponse* OCSP_NewOCSPResponse(OCSPResponseStatus_successful, CERTSTATUS_GOOD, ...);
*/
LIBSPEC_CKM
extern OCSPResponse* OCSP_NewOCSPResponse(int status, ...);
                                      /* (0, Oid*, ASN*)  */
                                      /* (1)   */


typedef enum {
  RESPONDER_DN,
  RESPONDER_KEYHASH
} responderOption;

/**
    @ingroup OCSP
    @brief BasicOCSPResponse �޽����� �����Ѵ�.
    @param responderCert  [in] Responder�� Certificate
    @param responderOpt   [in] Responder�� Certificate���� RESPONDER_DN�̳�
                               RESPONDER_KEYHASH �� �ϳ� ����
    @param nonce          [in] OCSPRequest �޽������� ���� nonce
    @param nonceLen       [in] nonce�� ����Ʈ ����

    return : success�̸� BasicOCSPResponse*, fail�̸� NULL
             BasicOCSPResponse -> ResponseData�� Responder�� ����, ������ ��������� �̷������.

    BasicOCSPRespose �޽����� �����Ѵ�.
*/
LIBSPEC_CKM
extern BasicOCSPResponse* OCSP_NewBasicOCSPResponse(
        Certificate *responderCert,
        int responderOpt, char *nonce, int nonceLen);

/**
    @ingroup OCSP
    @brief BasicOCSPResponse �޽����� �����Ѵ�.
    @param[in] responderCert  Responder�� Certificate
    @param[in] responderOpt   Responder�� Certificate���� RESPONDER_DN�̳�
                               RESPONDER_KEYHASH �� �ϳ� ����
    @param[in] nonce          OCSPRequest �޽������� ���� nonce
    @param[in] nonceLen       nonce�� ����Ʈ ����
    @param[in] hashNid        �ؽ� �˰����� NID

    return : success�̸� BasicOCSPResponse*, fail�̸� NULL
             BasicOCSPResponse -> ResponseData�� Responder�� ����, ������ ��������� �̷������.

    BasicOCSPRespose �޽����� �����Ѵ�.
*/
LIBSPEC_CKM
extern BasicOCSPResponse* OCSP_NewBasicOCSPResponse_WithHashNid(
        Certificate *responderCert,
        int responderOpt, char *nonce, int nonceLen,
        Nid hashNid);

/**
    @ingroup OCSP
    @brief responseExtension�� �߰��Ѵ�.
    @param basicResponse      [in] BasicOCSPResponse
    @param extension          [in] ������û�ڿ��� ������ ���� extension
    @param nid                [in] extension�� ����Ű�� nid

    return : success�̸� SUCCESS, fail�̸� FAIL
             basicResponse�� extension�� NULL�� ��쿡�� INVALID_ARG�� ���ϵȴ�.

    BasicOCSPResponse �޽����� ���ٿ��������� �ϴ� responseExtensions�� �߰��Ѵ�.
*/
LIBSPEC_CKM
extern int OCSP_AddResponseExtensions(BasicOCSPResponse *basicResponse,
             ASN *extension, Nid nid);

/**
    @ingroup OCSP
    @brief BasicOCSPResponse �޽����� �����Ѵ�.
    @param[out] basic            BasicOCSPResponse
    @param[in] responderPriInfo  Responder�� �����Ű
    @param[in] responderCert     Responder Certificate
    @param[in] domainParam       ������ �Ķ����
    @param[in] certs             ������ ��û�ߴ� ��������

    return : success�̸� SUCCESS, fail�̸� FAIL
             basic�� responderPriInfo�� NULL�� ��� FAIL

    BasicOCSPResponse �޽����� Responder�� �����Ű�� �����Ѵ�.
*/
LIBSPEC_CKM
ERT OCSP_SignBasicOCSPResponse(BasicOCSPResponse *basic, 
                               PrivateKeyInfo    *responderPriInfo,
                               Certificate       *responderCert,
                               Parameter         *domainParam,
                               Certificates      *certs);

/**
    @ingroup OCSP
    @brief BasicOCSPResponse �޽����� �����Ѵ�.
    @param[out] basic            BasicOCSPResponse
    @param[in] responderPriInfo  Responder�� �����Ű
    @param[in] responderCert     Responder Certificate
    @param[in] domainParam       ������ �Ķ����
    @param[in] certs             ������ ��û�ߴ� ��������
    @param[in] hashNid           �ؽ� �˰����� NID

    return : success�̸� SUCCESS, fail�̸� FAIL
             basic�� responderPriInfo�� NULL�� ��� FAIL

    BasicOCSPResponse �޽����� Responder�� �����Ű�� �����Ѵ�.
*/
LIBSPEC_CKM
ERT OCSP_SignBasicOCSPResponse_WithHashNid(BasicOCSPResponse *basic, 
                                           PrivateKeyInfo    *responderPriInfo,
                                           Certificate       *responderCert,
                                           Parameter         *domainParam,
                                           Certificates      *certs,
                                           Nid               hashNid);

/**
    @ingroup OCSP
    @brief SingleResponse �޽����� �����Ѵ�.
    @param certID          [in] Request �޽����� �ִ� certID
    @param certStatus      [in] CERTSTATUS_GOOD, CERTSTATUS_REVOKED,
                                CERTSTATUS_UNKNOWN�� �ϳ� �ֱ�
    @param thisUpdate      [in] SingleResponse �޽����� ���Ե� ������ ���� ������ �Ǵٰ� �������� �ð�
    @param nextUpdate      [in] �������� ���¿� ���Ͽ� ���ο� ������ ���ŵ� �ð�
    @param revocationTime  [in] ������ ��û���� �������� �����ð����μ� CERTSTATUS_REVOKED�� ��쿡�� ó��
    @param cRLReason       [in] ������ ��û���� �������� ���������μ� CERTSTATUS_REVOKED�� ��쿡�� ó��

    return : SingleResponse*
             SingleResponse -> ������ ��û���� �������� certID�� certStatus�� �ִ�.

    SingleResponse �޽����� �����Ѵ�.
*/
LIBSPEC_CKM
extern SingleResponse * OCSP_NewSingleResponse(
        CertID *certID,
        int certStatus, 
        time_t thisUpdate, time_t nextUpdate,
        time_t revocationTime, int cRLReason);

/**
    @ingroup OCSP
    @brief SingleResponse �޽����� SingleExtensions�� �ִ´�.
    @param singleResponse [in] SingleResponse �޽���
    @param extension      [in] Archive Cutoff, CRLEntry(Reason Code, 
                          Hold Instruction Code, Invalidity Date, 
                          Certificate Issuer), CRLReferences
    @param nid            [in] id-pkix-ocsp-archive-cutoff, id-ce-reasonCode, 
                          id-ce-instructionCode, id-ce-invalidityDate, 
                          id-ce-certificateIssuer, id-pkix-ocsp-crl�� ��ġ�ϴ� 
                          nid
    
    return : success�̸� SUCCESS, fail�̸� FAIL
             singleResponse�� extension�� NULL�� ��쿡�� INVALID_ARG�� ���ϵȴ�.

    SingleResponse �޽����� SingleExtension �ʵ忡 Archive Cutoff, CRLEntry, CRLReferences�� �߰��Ѵ�.
 */
LIBSPEC_CKM
extern int OCSP_AddSingleExtensions(SingleResponse *singleResponse,
             ASN *extension, Nid nid);

/**
    @ingroup OCSP
    @brief SingleResponse �޽����� �߰��Ѵ�.
    @param basic   [in] BasicOCSPResponse
    @param single  [in] SingleResponse

    return : success�̸� SUCCESS
             basic�� single�� NULL�� ��� FAIL

    BasicOCSPResponse�� SingleResponse�� �߰��Ѵ�.
 */
LIBSPEC_CKM
extern int OCSP_AddSingleResponseP(BasicOCSPResponse *basic,
                                   SingleResponse *single);



/***************************************************************
 * Receive OCSP Response
 */


/**
    @ingroup OCSP
    @brief OCSPResponse �޽����� ResponseStatus�� ���Ѵ�.
    @param response [in] OCSPResponse

    return : success�̸� SUCCESS
             basic�� single�� NULL�� ��� FAIL

    OCSPRequest �޽����� ó�� ���°� �������� �������� �˱� ���� OCSPResponse �޽����� 
    ResponseStatus�� ���Ѵ�.
*/
LIBSPEC_CKM
extern int OCSP_GetResponseStatus(OCSPResponse *response);

/**
    @ingroup OCSP
    @brief OCSPResponse �޽������� BasicOCSPResponse�� �����´�.
    @param  response [in] OCSPResponse �޽���

    return : success�̸� BasicOCSPResponse*, fail�̸� NULL
             BasicOCSPResponse -> ResponseData�� Responder�� ������ �ִ�.
*/
LIBSPEC_CKM
extern BasicOCSPResponse* OCSP_GetBasicOCSPResponse(OCSPResponse *response);

/**
    @ingroup OCSP
    @brief BasicOCSPResponse �޽������� ResponderCert�� �����´�.
    @param basic  [in] BasicOCSPResponse �޽���

    return : success�̸� Certificate*, fail�̸� NULL
             Certificate -> Responder�� ������
*/
LIBSPEC_CKM
extern Certificate* OCSP_GetResponderCert(BasicOCSPResponse *basic);

/**
    @ingroup OCSP
    @brief ResponderID�� �����Ѵ�. 
    @param basic          [in] BasicOCSPResponse
    @param responderCert  [in] Responder�� ������ 

    return : success�̸� SUCCESS, fail�̸� FAIL

    ResponseData�� �ִ� ResponderID�� ������ Responder�� �������� �ִ� 
    DN �Ǵ� ����Ű�� ���� ���� �´��� �˻��Ѵ�.
*/
LIBSPEC_CKM
extern int OCSP_CheckResponderID(BasicOCSPResponse *basic,
                                 Certificate *responderCert);

/**
    @ingroup OCSP
    @brief responderCert�� extendedKeyUsage �ʵ忡 id-kp-OCSPSigning�� 
           ����ִ��� Ȯ���Ѵ�. 
    @param responderCert  [in] Responder�� ������

    return : success�̸� SUCCESS, fail�̸� FAIL

    OCSP �����ڰ� ���� ���� ��� responderCert�� extendedKeyUsage �ʵ忡 id-kp-OCSPSigning�� ����Ѵ�.
*/
LIBSPEC_CKM
extern int OCSP_CheckCertOCSPSigning(Certificate *responderCert);


/**
    @ingroup OCSP
    @brief BasicOCSPResponse �޽����� �����Ѵ�.
    @param[in] basicRes       BasicOCSPesponse
    @param[in] cert           Responder ������
    @param[in] domainParam    ������ �Ķ����
    @param[in] nonce          OCSPRequest �޽����� �־�� nonce
    @param[in] nonceLen       nonce�� ����Ʈ ����
  
    return : success�̸� SUCCESS, fail�̸� FAIL
             basicRes �Ǵ� cert�� NULL�̸� FAIL
*/
LIBSPEC_CKM
ERT OCSP_VerifyBasicResponse( BasicOCSPResponse *basicRes,
                              Certificate       *cert,
                              Parameter         *domainParam,
                              char              *nonce,
                              int                nonceLen);

/**
    @ingroup OCSP
    @brief SingleResponse �޽����� �����´�. 
    @param response          [in] BasicOCSPResponce
    @param unverifiedCertSN  [in] �����ϰ��� �ϴ� �������� serial number
    @param issuerCert        [in] CA ������

    return : success�̸� SingleResponse*, fail�̸� NULL
             SingleResponse -> ������ �������� ���� ������ ����ִ�.
*/
LIBSPEC_CKM
extern SingleResponse* OCSP_GetSingleResponseP( 
        BasicOCSPResponse *response,
        CertificateSerialNumber *unverifiedCertSN,
        Certificate *issuerCert);

/**
    @ingroup OCSP
    @brief SingleResponse �޽����� �����´�. 
    @param[in] response          BasicOCSPResponce
    @param[in] unverifiedCertSN  �����ϰ��� �ϴ� �������� serial number
    @param[in] issuerCert        CA ������
    @param[in] hashNid           �ؽ� �˰����� NID

    return : success�̸� SingleResponse*, fail�̸� NULL
             SingleResponse -> ������ �������� ���� ������ ����ִ�.
*/
LIBSPEC_CKM
extern SingleResponse* OCSP_GetSingleResponseP_WithHashNid( 
        BasicOCSPResponse *response,
        CertificateSerialNumber *unverifiedCertSN,
        Certificate *issuerCert,
        Nid hashNid);


/**
    @ingroup OCSP
    @brief ������ ��û�� �������� ���¸� �˻��Ѵ�.
    @param certStstus  [in] �������� ���� 
    @param thisUpdate  [in] ���信 ���Ե� ���������� �Ǵٰ� �������� �ð�
    @param nextUpdate  [in] ������ ���¿� ���Ͽ� ���ο� ������ ���ŵ� �ð�
    @param singleRes   [in] SingleResponse

    return : success�̸� RevokedInfo*, fail�̸� NULL
             RevokedInfo ->  �����ð� �� ���������� ����ִ�.
*/
LIBSPEC_CKM
extern RevokedInfo* OCSP_CheckCertStatus(
        int *certStatus,               
        time_t *thisUpdate,             
        time_t *nextUpdate,             
        SingleResponse *singleRes); 

#ifdef __cplusplus
}
#endif

#endif /* _ocsp_h */
