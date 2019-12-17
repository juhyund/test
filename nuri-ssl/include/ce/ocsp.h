#ifndef _ocsp_h
#define _ocsp_h

#include "ckm_pkcrypt.h"
#include "x509pkc.h"

/** @defgroup OCSP OCSP handling
 * @ingroup CKM
    @brief OCSP 메시지 생성 모듈
*/

/** @file ocsp.h
    @ingroup OCSP
    @brief OCSP 타입과 ocsp 메시지 생성 함수 선언
    
    OCSP 서버와 클라이언트간에 주고 받는 메시지의 타입과 메시지 생성 함수
    OCSP(Online Certificate Status Protocol) 타입
    OCSP 생성 함수
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
    CERTSTATUS_GOOD = 1, /**< 인증서가 폐지되지 않은 상태 */
    CERTSTATUS_REVOKED,  /**< 인증서가 폐지된 상태 */
    CERTSTATUS_UNKNOWN   /**< 인증서의 상태를 알 수 없음 */
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
  OCSPResponseStatus_malformedRequest  = 1,  /**< request가 ocsp 문법에 맞지 않은 경우 */
  OCSPResponseStatus_internalError    = 2,   /**< responder의 내부 에러 발생시 */
  OCSPResponseStatus_tryLater      = 3,      /**< responder가 서비스를 잠시 중단한 경우 */
  OCSPResponseStatus_sigRequired    = 5,     /**< OCSPRequest에 클라이언트 서명이 포함되어 있어야만 했을 경우 */
  OCSPResponseStatus_unauthorized    = 6,    /**< 현재 서버로 허가받지 않은 사용자에게서 요청이 온 경우 */
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
  @brief Request 메시지를 생성한다.
  @param unverifiedCert  [in] 유효성을 검증하고자 하는 인증서
  @param issuerCert      [in] 검증하고자 하는 인증서를 발급한 CA 인증서
  
  return : success이면 Request*, fail이면 NULL
           Request -> CertID와 singleRequestExtension으로 이루어진다.
                         
  unverifiedCert에서 DN과 serlalNumber를 꺼내고 issuerCert에서 public Key를 꺼내어 
  CertID를 만든다.
  
*/
LIBSPEC_CKM
extern Request* OCSP_NewRequest(Certificate *unverifiedCert,
                                Certificate *issuerCert);

/** @ingroup OCSP
    @brief Request 메시지를 생성한다.
    @param[in] unverifiedCert  유효성을 검증하고자 하는 인증서
    @param[in] issuerCert      검증하고자 하는 인증서를 발급한 CA 인증서
    @param[in] hashNid         해시 알고리즘의 NID

    return : success이면 Request*, fail이면 NULL
             Request -> CertID와 singleRequestExtension으로 이루어진다.
                         
    unverifiedCert에서 DN과 serlalNumber를 꺼내고 issuerCert에서 public Key를 꺼내어 
    CertID를 만든다.
*/
LIBSPEC_CKM
extern Request* OCSP_NewRequest_WithHashNid(Certificate *unverifiedCert,
                                            Certificate *issuerCert,
                                            Nid         hashNid);

/** @ingroup OCSP
    @brief Request 메시지의 singleRequestExtensions 필드 처리
    @param[in] extension  serviceLocator
    @param[in] nid        id-pkix-ocsp-service-locator와 일치하는 nid

    return : success이면 SUCCESS, fail이면 FAIL
             Request나 extension이 NULL일 경우에도 INVALID_ARG가 리턴된다.

    Request 메시지의 singleRequestExtension 필드에 serviceLocator를 표시한다.
*/
LIBSPEC_CKM
extern int OCSP_AddSingleRequestExtensions(Request *request,
             ASN *extension, Nid nid);


/**
    @ingroup OCSP
    @brief OCSPRequest 메시지를 생성한다.
    @param nonce     [out] replay attack을 막기 위해 nonce 생성
    @param nonceLen  [out] nonce의 바이트 길이

	return : success이면 OCSPRequest*, fail이면 NULL
		 OCSPRequest -> Request  메시지와 인증서 검증 요청자의 서명으로 이루어진다.
    
	  
    OCSPRequest 메시지를 생성하고 nonce와 nonceLen을 생성한다. 
    만약 nonce의 입력으로 NULL이 들어온다면 nonce를 만들지 않는다.
    
*/
LIBSPEC_CKM
extern OCSPRequest* OCSP_NewOCSPRequest(char *nonce, int *nonceLen); 

/**
    @ingroup OCSP
    @brief OCSPRequest 메시지의 requestExtensions 필드 처리     
    @param extension  [in] nonce, Acceptable Response Types
    @param nid        [in] id-pkix-ocsp-nonce와 일치하는 nid, id-pkix-ocsp-basic과 일치하는 nid

	return : success이면 SUCCESS, fail이면 FAIL
		 ocspRequest나 extension이 NULL일 경우에도 INVALID_ARG가 리턴된다.
    
    OCSPRequest 메시지의 requestExtensions 필드에 nonce, Acceptable Response Types를 추가한다.
    
*/
LIBSPEC_CKM
extern int OCSP_AddRequestExtensions(OCSPRequest *ocspRequest,
             ASN *extension, Nid nid);


/**
    @param Request 메시지가 한개 이상일 경우 모아서 보낸다.
*/
#define OCSP_AddRequestP(ocspRequest, request)  \
ASNSeqOf_AddP(ASN_SEQOF((ocspRequest)->tbsRequest->requestList), ASN(request));

/**
    @ingroup OCSP
    @brief OCSPReqeust 메시지에 서명하는 함수이다.
    @param[out] ocspRequest   OCSPRequest
    @param[in]  clientPriInfo 검증 요청자의 비공개키
    @param[in]  clientCert    검증 요청자의 인증서
    @param[in]  domainParam   도메인 파라메터
    @param[in]  certs         검증하고자 하는 인증서의 인증 경로

    return : success이면 SUCCESS, fail이면 FAIL
             clientCert 또는 clientPriInfo가 NULL인 경우에도 FAIL

    OCSPRequest 메시지를 인증서 검증 요청자의 비공개키로 서명한다.
*/
LIBSPEC_CKM
ERT OCSP_SignOCSPRequest(OCSPRequest    *ocspRequest,
                         PrivateKeyInfo *clientPriInfo,
                         Certificate    *clientCert,
                         Parameter      *domainParam,
                         Certificates   *certs);

/**
    @ingroup OCSP
    @brief OCSPReqeust 메시지에 서명하는 함수이다.
    @param[out] ocspRequest  OCSPRequest
    @param[in] clientPriInfo 검증 요청자의 비공개키
    @param[in] clientCert    검증 요청자의 인증서
    @param[in] domainParam   도메인 파라메터
    @param[in] certs         검증하고자 하는 인증서의 인증 경로
    @param[in] hashNid       해시 알고리즘의 NID

    return : success이면 SUCCESS, fail이면 FAIL
             clientCert 또는 clientPriInfo가 NULL인 경우에도 FAIL

    OCSPRequest 메시지를 인증서 검증 요청자의 비공개키로 서명한다.
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
 * @brief   OCSPRequest 메시지에 있는 검증 요청자의 서명을 검중한다.
 * @param[in]   request  OCSPRequest 메시지
 * @param[in]   param    검증하고자하는 인증서에 도메인 파라메터가 들어있지
 * 						 않은 경우에도 처리할 수 있도록 함
 * @retval SUCCESS valid signature
 * @retval 1 no signature
 * @retval FAIL invalid signature
 *
 * 수신한 OCSPRequest 메시지에서 인증서 검증 요청자의 서명을 검증할 경우
 * 검증하고자하는 인증서에 도메인 파라메터가 들어있지 않더라도 도메인
 * 파라메터를 처리할 수 있다.
*/
LIBSPEC_CKM
ERT OCSP_ValidateRequestSignature( OCSPRequest *request,
                                   Parameter   *domainParam);

/**
    @ingroup OCSP
    @brief   OCSPRequest 메시지에서 nonce 추출 
    @param   nonce   [out] OCSPRequest 메시지의 requestExtensions 필드의 nonce
    @param   maxLen  [in] nonce가 들어갈 버퍼의 최대 길이
    @param   request [in] OCSPRequest 메시지

    return : success이면 양수값, fail이면 0

    OCSPRequest 메시지의 requestExtensions필드에 있는 nonce를 꺼낸다.
*/
LIBSPEC_CKM
extern int OCSP_GetRequestNonce(char *nonce, int maxLen, 
                                OCSPRequest *request);


/**
    @ingroup OCSP
    @brief   검증을 요청한 인증서의 갯수
    @param   request [in] OCSPRequest 메시지

    검증 요청한 인증서의 갯수를 검사한다.

*/
LIBSPEC_CKM
extern int OCSP_GetRequestNumber(OCSPRequest *request);


/**
    @ingroup OCSP
    @brief 다수개의 Request 메시지중 검사하고자하는 Request 메시지를 선택
    @param request [in] OCSPRequest 메시지 
    @param number  [in] OCSPRequest 메시지에 있는 Request들 중 검증하고자 하는
                        Request 메시지의 index 번호

    return : success이면 Request*, fail이면 NULL

    OCSPRequest에 들어있는 다수개의 Request들 중 원하는 번호의 Request의 포인터를 가져온다.
*/
LIBSPEC_CKM
extern Request* OCSP_GetRequestP(OCSPRequest *request, int number);


/***************************************************************
 * Create OCSP Response
 */

/**
    @ingroup OCSP
    @brief OCSPResponse 메시지를 만든다.
    @param status [in] OCSPRequest 메시지 처리가 성공인지 실패인지를 나타낸다.

	return : success이면 OCSPResponse, fail이면 NULL
			 OCSPResponse -> ResponseStatus와 ResponseBytes로 이루어진다.
     
    OCSPRequest 메시지가 제대로 처리되었는지 알 수 있는 부분으로
    OCSPResponse 메시지에 성공 또는 에러를 표시하고 OCSPResponse 메시지를 만든다.
    
    @sa 성공한 상태이면 OCSPResponse* OCSP_NewOCSPResponse(OCSPResponseStatus_successful, CERTSTATUS_GOOD, ...);
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
    @brief BasicOCSPResponse 메시지를 생성한다.
    @param responderCert  [in] Responder의 Certificate
    @param responderOpt   [in] Responder의 Certificate에서 RESPONDER_DN이나
                               RESPONDER_KEYHASH 중 하나 선택
    @param nonce          [in] OCSPRequest 메시지에서 꺼낸 nonce
    @param nonceLen       [in] nonce의 바이트 길이

    return : success이면 BasicOCSPResponse*, fail이면 NULL
             BasicOCSPResponse -> ResponseData와 Responder의 서명, 검증한 인증서들로 이루어진다.

    BasicOCSPRespose 메시지를 생성한다.
*/
LIBSPEC_CKM
extern BasicOCSPResponse* OCSP_NewBasicOCSPResponse(
        Certificate *responderCert,
        int responderOpt, char *nonce, int nonceLen);

/**
    @ingroup OCSP
    @brief BasicOCSPResponse 메시지를 생성한다.
    @param[in] responderCert  Responder의 Certificate
    @param[in] responderOpt   Responder의 Certificate에서 RESPONDER_DN이나
                               RESPONDER_KEYHASH 중 하나 선택
    @param[in] nonce          OCSPRequest 메시지에서 꺼낸 nonce
    @param[in] nonceLen       nonce의 바이트 길이
    @param[in] hashNid        해시 알고리즘의 NID

    return : success이면 BasicOCSPResponse*, fail이면 NULL
             BasicOCSPResponse -> ResponseData와 Responder의 서명, 검증한 인증서들로 이루어진다.

    BasicOCSPRespose 메시지를 생성한다.
*/
LIBSPEC_CKM
extern BasicOCSPResponse* OCSP_NewBasicOCSPResponse_WithHashNid(
        Certificate *responderCert,
        int responderOpt, char *nonce, int nonceLen,
        Nid hashNid);

/**
    @ingroup OCSP
    @brief responseExtension을 추가한다.
    @param basicResponse      [in] BasicOCSPResponse
    @param extension          [in] 검증요청자에게 보내고 싶은 extension
    @param nid                [in] extension을 가리키는 nid

    return : success이면 SUCCESS, fail이면 FAIL
             basicResponse나 extension이 NULL일 경우에도 INVALID_ARG가 리턴된다.

    BasicOCSPResponse 메시지에 덧붙여보내고자 하는 responseExtensions를 추가한다.
*/
LIBSPEC_CKM
extern int OCSP_AddResponseExtensions(BasicOCSPResponse *basicResponse,
             ASN *extension, Nid nid);

/**
    @ingroup OCSP
    @brief BasicOCSPResponse 메시지에 서명한다.
    @param[out] basic            BasicOCSPResponse
    @param[in] responderPriInfo  Responder의 비공개키
    @param[in] responderCert     Responder Certificate
    @param[in] domainParam       도메인 파라메터
    @param[in] certs             검증을 요청했던 인증서들

    return : success이면 SUCCESS, fail이면 FAIL
             basic과 responderPriInfo가 NULL인 경우 FAIL

    BasicOCSPResponse 메시지를 Responder의 비공개키로 서명한다.
*/
LIBSPEC_CKM
ERT OCSP_SignBasicOCSPResponse(BasicOCSPResponse *basic, 
                               PrivateKeyInfo    *responderPriInfo,
                               Certificate       *responderCert,
                               Parameter         *domainParam,
                               Certificates      *certs);

/**
    @ingroup OCSP
    @brief BasicOCSPResponse 메시지에 서명한다.
    @param[out] basic            BasicOCSPResponse
    @param[in] responderPriInfo  Responder의 비공개키
    @param[in] responderCert     Responder Certificate
    @param[in] domainParam       도메인 파라메터
    @param[in] certs             검증을 요청했던 인증서들
    @param[in] hashNid           해시 알고리즘의 NID

    return : success이면 SUCCESS, fail이면 FAIL
             basic과 responderPriInfo가 NULL인 경우 FAIL

    BasicOCSPResponse 메시지를 Responder의 비공개키로 서명한다.
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
    @brief SingleResponse 메시지를 생성한다.
    @param certID          [in] Request 메시지에 있던 certID
    @param certStatus      [in] CERTSTATUS_GOOD, CERTSTATUS_REVOKED,
                                CERTSTATUS_UNKNOWN중 하나 넣기
    @param thisUpdate      [in] SingleResponse 메시지에 포함된 인증서 상태 정보가 옳다고 여겨지는 시각
    @param nextUpdate      [in] 인증서의 상태에 대하여 새로운 정보가 갱신될 시각
    @param revocationTime  [in] 검증을 요청받은 인증서의 폐지시각으로서 CERTSTATUS_REVOKED인 경우에만 처리
    @param cRLReason       [in] 검증을 요청받은 인증서의 폐지이유로서 CERTSTATUS_REVOKED인 경우에만 처리

    return : SingleResponse*
             SingleResponse -> 검증을 요청받은 인증서의 certID와 certStatus가 있다.

    SingleResponse 메시지를 생성한다.
*/
LIBSPEC_CKM
extern SingleResponse * OCSP_NewSingleResponse(
        CertID *certID,
        int certStatus, 
        time_t thisUpdate, time_t nextUpdate,
        time_t revocationTime, int cRLReason);

/**
    @ingroup OCSP
    @brief SingleResponse 메시지에 SingleExtensions를 넣는다.
    @param singleResponse [in] SingleResponse 메시지
    @param extension      [in] Archive Cutoff, CRLEntry(Reason Code, 
                          Hold Instruction Code, Invalidity Date, 
                          Certificate Issuer), CRLReferences
    @param nid            [in] id-pkix-ocsp-archive-cutoff, id-ce-reasonCode, 
                          id-ce-instructionCode, id-ce-invalidityDate, 
                          id-ce-certificateIssuer, id-pkix-ocsp-crl과 일치하는 
                          nid
    
    return : success이면 SUCCESS, fail이면 FAIL
             singleResponse나 extension이 NULL일 경우에도 INVALID_ARG가 리턴된다.

    SingleResponse 메시지의 SingleExtension 필드에 Archive Cutoff, CRLEntry, CRLReferences를 추가한다.
 */
LIBSPEC_CKM
extern int OCSP_AddSingleExtensions(SingleResponse *singleResponse,
             ASN *extension, Nid nid);

/**
    @ingroup OCSP
    @brief SingleResponse 메시지를 추가한다.
    @param basic   [in] BasicOCSPResponse
    @param single  [in] SingleResponse

    return : success이면 SUCCESS
             basic과 single이 NULL인 경우 FAIL

    BasicOCSPResponse에 SingleResponse를 추가한다.
 */
LIBSPEC_CKM
extern int OCSP_AddSingleResponseP(BasicOCSPResponse *basic,
                                   SingleResponse *single);



/***************************************************************
 * Receive OCSP Response
 */


/**
    @ingroup OCSP
    @brief OCSPResponse 메시지의 ResponseStatus를 구한다.
    @param response [in] OCSPResponse

    return : success이면 SUCCESS
             basic과 single이 NULL인 경우 FAIL

    OCSPRequest 메시지의 처리 상태가 성공인지 에러인지 알기 위해 OCSPResponse 메시지의 
    ResponseStatus를 구한다.
*/
LIBSPEC_CKM
extern int OCSP_GetResponseStatus(OCSPResponse *response);

/**
    @ingroup OCSP
    @brief OCSPResponse 메시지에서 BasicOCSPResponse를 가져온다.
    @param  response [in] OCSPResponse 메시지

    return : success이면 BasicOCSPResponse*, fail이면 NULL
             BasicOCSPResponse -> ResponseData와 Responder의 서명이 있다.
*/
LIBSPEC_CKM
extern BasicOCSPResponse* OCSP_GetBasicOCSPResponse(OCSPResponse *response);

/**
    @ingroup OCSP
    @brief BasicOCSPResponse 메시지에서 ResponderCert를 가져온다.
    @param basic  [in] BasicOCSPResponse 메시지

    return : success이면 Certificate*, fail이면 NULL
             Certificate -> Responder의 인증서
*/
LIBSPEC_CKM
extern Certificate* OCSP_GetResponderCert(BasicOCSPResponse *basic);

/**
    @ingroup OCSP
    @brief ResponderID를 검증한다. 
    @param basic          [in] BasicOCSPResponse
    @param responderCert  [in] Responder의 인증서 

    return : success이면 SUCCESS, fail이면 FAIL

    ResponseData에 있는 ResponderID가 실제로 Responder의 인증서에 있는 
    DN 또는 공개키로 만든 것이 맞는지 검사한다.
*/
LIBSPEC_CKM
extern int OCSP_CheckResponderID(BasicOCSPResponse *basic,
                                 Certificate *responderCert);

/**
    @ingroup OCSP
    @brief responderCert의 extendedKeyUsage 필드에 id-kp-OCSPSigning이 
           들어있는지 확인한다. 
    @param responderCert  [in] Responder의 인증서

    return : success이면 SUCCESS, fail이면 FAIL

    OCSP 제공자가 따로 있을 경우 responderCert의 extendedKeyUsage 필드에 id-kp-OCSPSigning을 명시한다.
*/
LIBSPEC_CKM
extern int OCSP_CheckCertOCSPSigning(Certificate *responderCert);


/**
    @ingroup OCSP
    @brief BasicOCSPResponse 메시지를 검증한다.
    @param[in] basicRes       BasicOCSPesponse
    @param[in] cert           Responder 인증서
    @param[in] domainParam    도메인 파라메터
    @param[in] nonce          OCSPRequest 메시지에 넣어보낸 nonce
    @param[in] nonceLen       nonce의 바이트 길이
  
    return : success이면 SUCCESS, fail이면 FAIL
             basicRes 또는 cert가 NULL이면 FAIL
*/
LIBSPEC_CKM
ERT OCSP_VerifyBasicResponse( BasicOCSPResponse *basicRes,
                              Certificate       *cert,
                              Parameter         *domainParam,
                              char              *nonce,
                              int                nonceLen);

/**
    @ingroup OCSP
    @brief SingleResponse 메시지를 가져온다. 
    @param response          [in] BasicOCSPResponce
    @param unverifiedCertSN  [in] 검증하고자 하는 인증서의 serial number
    @param issuerCert        [in] CA 인증서

    return : success이면 SingleResponse*, fail이면 NULL
             SingleResponse -> 검증한 인증서에 관한 정보가 들어있다.
*/
LIBSPEC_CKM
extern SingleResponse* OCSP_GetSingleResponseP( 
        BasicOCSPResponse *response,
        CertificateSerialNumber *unverifiedCertSN,
        Certificate *issuerCert);

/**
    @ingroup OCSP
    @brief SingleResponse 메시지를 가져온다. 
    @param[in] response          BasicOCSPResponce
    @param[in] unverifiedCertSN  검증하고자 하는 인증서의 serial number
    @param[in] issuerCert        CA 인증서
    @param[in] hashNid           해시 알고리즘의 NID

    return : success이면 SingleResponse*, fail이면 NULL
             SingleResponse -> 검증한 인증서에 관한 정보가 들어있다.
*/
LIBSPEC_CKM
extern SingleResponse* OCSP_GetSingleResponseP_WithHashNid( 
        BasicOCSPResponse *response,
        CertificateSerialNumber *unverifiedCertSN,
        Certificate *issuerCert,
        Nid hashNid);


/**
    @ingroup OCSP
    @brief 검증을 요청한 인증서의 상태를 검사한다.
    @param certStstus  [in] 인증서의 상태 
    @param thisUpdate  [in] 응답에 포함된 상태정보가 옳다고 여겨지는 시각
    @param nextUpdate  [in] 인증서 상태에 대하여 새로운 정보가 갱신될 시각
    @param singleRes   [in] SingleResponse

    return : success이면 RevokedInfo*, fail이면 NULL
             RevokedInfo ->  폐지시각 및 폐지이유가 들어있다.
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
