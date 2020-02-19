/* 
   $Id: pkimessage.h,v 1.24 2002/09/16 10:55:03 clhitter Exp $
*/

#ifndef _pkimessage_h
#define _pkimessage_h

#include "pkiinfo.h"
#include "cmp.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * PKIMessage 처리시에 필요한 데이터들을 저장하는 구조체
 */
typedef struct _PKIContext {
   ASNSeqClass klass;
   AlgorithmIdentifier *symmAlg;
   PKIHeader *previousHeader;   /*optional [0] */
   PKISenderAuthInfo *authInfo; /*optional [1] */
   SeqOfPKIReqInfo *reqInfos;   /*optional [2] */
   Certificate *recipientCert;  /*optional [3] */
} PKIContext;

LIBSPEC_CKM
extern ASNDescriptor AD_PKIContext;


/**
 * PKIContext 값을 설정한다.
 *
 * @param nidSymmAlg  (In) 메시지 생성, 해석시에 사용될 대칭키 algorithm
 * @return 
 *  - SUCCESS : 성공
 */
LIBSPEC_CKM
int PKIContext_Set(PKIContext *pPKIContext, Nid nidSymmAlg);

/****************************************************************/
/* PKI Header */

#define PKIMSG_NONCE_LEN 16 /* bytes */

LIBSPEC_CKM
int PKIMSG_MakeNonce(OctetString *nonce);

/**
 * PKIHeader를 생성한다.
 *
 * @param *header         (Out) 생성된 Header값을 저장할 버퍼, 
 *                              미리 ASN_New(PKIHeader,NULL)를 이용하여 초기화 되어 있어야 한다.
 * @param *senderName     (In)  sender의 DN
 * @param *recipientName  (In)  recipient의 DN
 * @param nowTime         (In)  메시지 생성 시간, 0이면 현재 시간을 이용
 * @param protectNid      (In)  protection을 생성하는데 사용할 algorithm, 0이면 사용하지 않음
 * @param *senderKID      (In)  senderKID, NULL인 경우 사용하지 않음
 * @param *recipientKID   (In)  recipientKID, NULL인 경우 사용하지 않음
 * @param *tranID         (In)  transaction ID, NULL인 경우 사용하지 않음
 * @param *senderNonce    (In)  메시지의 reply attack을 막기 위한 Nonce값, NULL이면 내부적으로 생성 
 * @param *recipientNonce (In)  응답 메시지를 생성하는 경우, 원래의 요청 메시지의 sender Nonce값
 *
 * @return 
 *  - SUCCESS : 성공
 *  - 그외의 경우는 없음...
 */
LIBSPEC_CKM
int PKIMSG_MakePKIHeader
             (PKIHeader           *header, 
              Name                *senderName,
              Name                *recipientName,        
              time_t               nowTime,
              AlgorithmIdentifier *protectionAlg,
              KeyIdentifier       *senderKID,
              KeyIdentifier       *recipientKID,
              OctetString         *transactionID,
              OctetString         *senderNonce,
              OctetString         *recipientNonce);

/**
 * CertReqMsg를 생성한다.
 *
 * @param pCertReqMsg     (Out) 생성된 CertReqMsg값을 저장할 버퍼, 
 *                              미리 ASN_New(CertReqMsg,NULL)를 이용하여 초기화 되어 있어야 한다.
 * @param nCertReqId      (In)  certReqId값
 * @param pEntityInfo     (In)  인증서 발급 대상에 대한 정보
 * @param pSenderAuthInfo (In)  신청자 인증을 위한 정보(POP 방식을 결정하기 위해 사용)
 * @param pReqCertInfo     (In)  인증서 발급 신청에 대한 키 정보
 * @param pCACert         (In)  CA의 인증서(POP가 thisMessage 방식일때, 비공개키를 암호화 하기 위해 사용
 *                                        단, ir의 경우에는 이 값이 NULL이면 secret value를 이용하여 암호화)
 * @param pSymmAlg        (In)  대칭키 알고리즘(CertReqMsg내의 데이터를 암호화 할 때 사용)
 * @return 
 *  - SUCCESS : 성공
 */
enum {
  ER_PKIMSG_CERTREQMSG_FAIL_TO_MAKEPOP = -200,   /**< POP 생성 실패 */
  ER_PKIMSG_CERTREQMSG_FAIL_TO_MAKEARCHIVEOPT,   /**< PKIArchiveOptions 생성 실패 */
};
LIBSPEC_CKM
int PKIMSG_MakeCertReqMsg(CertReqMsg          *pCertReqMsg,
                          int                  nCertReqId,
                          PKIEntityInfo       *pEntityInfo,
                          PKISenderAuthInfo   *pSenderAuthInfo,
                          PKIReqCertInfo       *pReqCertInfo,
                          Certificate         *pCACert,
                          AlgorithmIdentifier *pSymmAlg);

/**
 * RevDetails를 생성한다.
 *
 * @param *pRevDetails    (Out) 생성된 RevDetails값을 저장할 버퍼
 *                              미리 ASN_New(CertReqMsg,NULL)를 이용하여 초기화 되어 있어야 한다.
 * @param *pSerialNumber  (In)  폐지할 인증서의 시리얼 번호
 * @param *pIssuer        (In)  폐지할 인증서의 issuer 값
 * @param *pSubject       (In)  폐지할 인증서의 subject 값
 * @param nReasonFlag     (In)  폐지 사유(x509pkc.h 참조), 0이면 페지사유를 설정하지 않는다.
 * @param *pCrlEntryDetails (In) crlEntryDetails값, NULL이면 사용하지 않음
 */
enum {
  ER_PKIMSG_REVREQUEST_NO_SERIALNUMBER = -200,
};
LIBSPEC_CKM
int PKIMSG_MakeRevDetails(RevDetails              *pRevDetail,
                          CertificateSerialNumber *pSerialNumber,
                          Name                    *pIssuer,
                          Name                    *pSubject,
                          int                      nReasonFlags,
                          Extensions              *pCrlEntryDetails);
/**
 * certReqMsg를 해석한다.
 * certReqMsg를 해석하는 과정은 다음의 일련의 과정들을 포함한다.
 *  1. certTemplate 내용 검사
 *    1.1. version 검사
 *    1.2. issuer 영역 검사
 *    1.3. signingAlg 영역 검사
 *    1.4. subject 영역 검사
 *    1.5. publicKey 영역 검사(POP확인 시 publicKey 검사도 이루어지므로 생략),
 *    1.6. 그외(serialNumber, issuerUID, subjectUID, validity값은 CA가 지정)
 *  2. POP 검사
 *  3. 위의 결과값을 이용하여 PKIReqCertInfo 생성
 *
 * @param *pReqCertInfo      (Out) 생성된 PKIReqCertInfo
 * @param *pCertReqMsg      (In)  CertReqMsg 값
 * @param  nowTime          (In)  메시지 검증을 위한 기준 시간(0이면 System의 현재 시간값 사용)
 * @param *pEntityInfo      (In)  사용자의 정보를 담고 잇는 PKIEntityInfo
 * @param *pSenderAuthInfo  (In)  신청자 인증을 위한 정보를 담고 있는 PKIEntityInfo
 * @param *pCACert          (In)  CA 인증서
 * @param *pCAPrivateKey    (In)  CA 비공개키, NULL이면 암호화키 POP 검증은 무시.
 * @param *pDomainParameter (In)  도메인 파라메터(NULL 가능)
 */
enum{
  ER_PKIMSG_RESOLVE_CERTREQMSG_INVALID_VERSION = -200,
  ER_PKIMSG_RESOLVE_CERTREQMSG_ISSUER_MISMATCH,
  ER_PKIMSG_RESOLVE_CERTREQMSG_INVALID_SIGNINGALG,
  ER_PKIMSG_RESOLVE_CERTREQMSG_SUBJECT_MISMATCH,
  ER_PKIMSG_RESOLVE_CERTREQMSG_FAIL_TO_VERIFY_POP,
  ER_PKIMSG_RESOLVE_CERTREQMSG_FAIL_TO_DECRYPT_PRIKEY_IN_ARCHIVEOPT,
  ER_PKIMSG_RESOLVE_CERTREQMSG_UNSUPPORTED_ARCHIVEOPT,                /**< 지원되지 않는 방식의 PKIArchiveOptions */
};
LIBSPEC_CKM
int PKIMSG_ResolveCertReqMsg(PKIReqCertInfo     *pReqCertInfo,
                             CertReqMsg        *pCertReqMsg,
                             time_t             nowTime,
                             Name              *pEntityName,
                             PKISenderAuthInfo *pSenderAuthInfo,
                             Certificate       *pCACert,
                             PrivateKeyInfo    *pCAPrivateKey,
                             Parameter         *pDomainParam);

/**
 * 주어진 PKIBody를 가진 PKIMessage를 생성한다.
 *
 * @param *pRequestMsg        (Out) 생성된 PKI Message
 * @param *pPKIContext        (In,Out) PKIMessage 처리에 사용되는 값들을 저장해 두는 Context
 * @param  nowTime            (In)  메시지 생성 시간(0이면 System의 현재 시간값 사용)
 * @param *pPKIEntityInfo     (In)  인증서 발급(폐지) 대상에 대한 정보
 * @param *pPKISenderAuthInfo (In)  신청자 인증을 위한 정보
 * @param *pPKIBody           (In)  PKIMessage를 만들 PKIBody
 * @param *pRecipientCert     (In)  수신자의 인증서(NULL 가능)
 * @param *pCACert            (In)  CA의 인증서(비공개키를 암호화 하는데 사용, NULL 가능)
 *
 * @return 에러코드는 PKIMSG_MakeRequest와 공유
 */
LIBSPEC_CKM
int PKIMSG_MakePKIMessage(PKIMessage         *pRequestMsg,
                          PKIContext         *pPKIContext,
                          time_t              nowTime,
                          PKISenderAuthInfo  *pSenderAuthInfo,
                          PKIBody            *pPKIBody,
                          Certificate        *pRecipientCert);

/**
 * PKIMessage 중 request 메시지를 생성한다.(ir, cr, kur, ccr, rr)
 *
 * @param *pRequestMsg        (Out) 생성된 PKI Message
 * @param *pPKIContext        (In,Out) PKIMessage 처리에 사용되는 값들을 저장해 두는 Context
 * @param  nowTime            (In)  메시지 생성 시간(0이면 System의 현재 시간값 사용)
 * @param  nMsgType           (In)  메시지 종류(PKIBody_ir, PKIBody_cr... : PKIBody 참조)
 * @param *pPKIEntityInfo     (In)  인증서 발급 대상에 대한 정보(인증서 발급 요청이 아닌 경우에는 NULL 가능)
 * @param *pPKISenderAuthInfo (In)  신청자 인증을 위한 정보
 * @param *pSeqOfReqInfo      (In)  각각의 신청에 대한 키 정보
 *                                  인증서 발급 신청인 경우 certReqInfo의 publicKey와 privateKey값이 NULL이면 내부에서 키쌍을 생성한다.
 * @param *pRecipientCert     (In)  수신자의 인증서(NULL 가능)
 * @param *pCACert            (In)  CA의 인증서(비공개키를 암호화 하는데 사용, NULL 가능)
 *
 * @return 
 */
enum{
  ER_PKIMSG_REQUEST_INVALID_MSGTYPE = -200,   /**< 잘못된 MsgType 값 */
  ER_PKIMSG_REQUEST_INVALID_SENDERAUTHINFO,   /**< 잘못된 PKISenderAuthInfo 값 */
  ER_PKIMSG_REQUEST_INVALID_REQINFO,          /**< 잘못된 PKIReqInfo 값 */
  ER_PKIMSG_REQUEST_FAIL_TO_GEN_KEYPAIR,      /**< 키 쌍 생성 실패 */
  ER_PKIMSG_REQUEST_FAIL_TO_MAKE_CERTREQMSG,  /**< CertReqMsg 생성 실패 */
  ER_PKIMSG_REQUEST_FAIL_TO_MAKE_REVDETAILS,  /**< RevDetails 생성 실패 */
  ER_PKIMSG_REQUEST_FAIL_TO_MAKE_HEADER,      /**< Header 생성 실패 */
  ER_PKIMSG_REQUEST_FAIL_TO_MAKE_MESSAGE,     /**< Message 생성 실패 */
  ER_PKIMSG_REQUEST_CANNOT_FIND_OLDCERT,      /**< 기존 인증서 값이 PKIReqCertInfo에 지정되어 있지 않음. 
                                                   kur과 rr메시지 생성때는 기존 인증서값이 지정되어 있어야 한다.*/
};
LIBSPEC_CKM
int PKIMSG_MakeRequest(PKIMessage         *pRequestMsg,
                       PKIContext         *pPKIContext,
                       time_t              nowTime,
                       int                 nMsgType,
                       PKIEntityInfo      *pEntityInfo,
                       PKISenderAuthInfo  *pSenderAuthInfo,
                       SeqOfPKIReqInfo    *pSeqOfReqInfo,
                       Certificate        *pRecipientCert,
                       Certificate        *pCACert);

/**
 * PKIMessage를 검증한다. (Nonce, Protection, etc)
 *
 * 에러 코드는 PKIMSG_ResolveResponse와 같이 사용
 */
LIBSPEC_CKM
int PKIMSG_VerifyResponse(PKIMessage        *pPKIMessage,
                            PKIContext        *pPKIContext,
                            time_t             nowTime);

/**
 * response 메시지를 해석한다.(ip, cp, kup, ccp, rp)
 * 
 * @param *pPKIRepInfo  (Out) 신청 결과를 저장할 구조체
 * @param *pPKIContext  (In,Out) PKIMessage 처리에 사용되는 값들을 저장해 두는 Context
 * @param *pResonseMsg  (In) response 메시지
 * @param  nowTime      (In) 메시지 검증을 위한 기준 시간(0이면 System의 현재 시간값 사용)
 */
enum{
  ER_PKIMSG_RESPONSE_INVALID_PVNO = -200,   /**< Response의 pvno값이 1이 아님 */
  ER_PKIMSG_RESPONSE_INVALID_RECIPIENT,     /**< Recipient 값이 directoryName이 아님 */
  ER_PKIMSG_RESPONSE_RECIPIENT_MISMATCH,    /**< Response의 Recipient 값이 Request의 Sender값과 일치하지 않음 */
  ER_PKIMSG_RESPONSE_INVALID_SENDER,        /**< Sender 값이 directoryName이 아님 */
  ER_PKIMSG_RESPONSE_SENDER_MISMATCH,       /**< Response의 Sender 값이 Request의 Recipient 일치하지 않음 */
  ER_PKIMSG_RESPONSE_CANNOT_FIND_RECIPNONCE,/**< Response에 recipNonce 값이 존재하지 않음 */
  ER_PKIMSG_RESPONSE_RECIPNONCE_MISMATCH,   /**< Response의 recipNonce 값이 Request의 senderNonce와 일치하지 않음*/
  ER_PKIMSG_RESPONSE_CANNOT_FIND_SENDERNONCE, /**< Response에 senderNonce 값이 존재하지 않음 */
  ER_PKIMSG_RESPONSE_CANNOT_FIND_TRANSID,   /**< Response에 transactionID 값이 존재하지 않음 */
  ER_PKIMSG_RESPONSE_TRANSID_MISMATCH,      /**< Response의 transactionID 값이 Request의 transactionID와 일치하지 않음*/
  ER_PKIMSG_RESPONSE_CANNOT_FIND_PROTECTIONALG, /**< Response에 protectionAlg 값이 존재하지 않음 */
  ER_PKIMSG_RESPONSE_IMPROPER_PROTECTIONALG,/**< 잘못된 방식의 protection(MAC 방식이 요구될때 signature를 사용 혹은 그 반대 */
  ER_PKIMSG_RESPONSE_FAIL_TO_VERIFY_PROTECTION, /**< Protection 검증 실패 */
  ER_PKIMSG_RESPONSE_BAD_PROTECTION_ERROR_MSG,  /**< Protection 검증에 실패한 에러 메시지 */

  ER_PKIMSG_RESPONSE_INVALID_BODY_TYPE,     /**< 잘못된 PKIBody choice 값 */
  ER_PKIMSG_RESPONSE_WRONG_REP_SIZE,        /**< 응답 메시지 안의 응답 개수가 신청 개수와 일치하지 않음 */
  ER_PKIMSG_RESPONSE_CANNOT_FIND_CERTIFIEDKEYPAIR,  
                                            /**< 응답 메시지 내에 certifiedKeyPair값이 존재하지 않음 */
  ER_PKIMSG_RESPONSE_WRONG_CERTORENCCERT,   /**< 잘못된 certOrEncCert 값 */
  ER_PKIMSG_RESPONSE_INVALID_CERTIFICATE,   /**< 잘못된 certificate 값 */
  ER_PKIMSG_RESPONSE_FAIL_TO_DECRYPT_ENCCERT,
                                            /**< 응답 메시지 내의 encryptedCert값 복호화 실패 */
  /* ER_PKIMSG_RESPONSE_ */
};
LIBSPEC_CKM
int PKIMSG_ResolveResponse(PKIRepInfo     *pPKIRepInfo,
                           PKIContext     *pPKIContext,
                           PKIMessage     *pResponseMsg,
                           time_t          nowTime);


/**
 * Confirm 메시지를 생성한다.
 *
 * @param *pConfirmMsg  (Out) 생성된 confirm 메시지
 * @param *pPKIContext  (In,Out) PKIMessage 처리에 사용되는 값들을 저장해 두는 Context
 * @param  nowTime      (In) 메시지 생성 시간(0이면 System의 현재 시간값 사용)
 */
enum{
  ER_PKIMSG_MAKE_CONF_FAIL_TO_MAKE_HEADER = -200, /**< Header 생성 실패 */
  ER_PKIMSG_MAKE_CONF_FAIL_TO_MAKE_MESSAGE,       /**< Message 생성 실패 */
};
LIBSPEC_CKM
int PKIMSG_MakeConfirm(PKIMessage *pConfirmMsg,
                       PKIContext *pPKIContext,
                       time_t      nowTime);

/**
 * KeyPolicy를 CA/RA에게서 구하기 위한 요청 메시지를 생성한다.
 * FIXME : 여러개의 KeyPolicy를 동시에 요청할 수 없음, 급한대로 사용
 */
LIBSPEC_CKM
int PKIMSG_MakeKeyPolicyReq(
           PKIMessage*,
           PKIContext*,
           const char *szRefNum,
           const char *szScrtVal,
           Certificate *pSenderCert,
           PrivateKeyInfo *pSenderKey,
           int            rAPolicy,
           Certificate *pRecipCert,
           Certificate *pCACert);

/**
 *  CA/RA에게서 온 응답 메시지에서 KeyPolicies를 구해낸다.
 * FIXME : 여러개의 KeyPolicy를 동시에 얻을 수 없음, 급한대로 사용
 */
LIBSPEC_CKM
int PKIMSG_ResolveKeyPolicies(
           KeyPolicies**,
           PKIMessage*,
           PKIContext*
           );

#ifdef __cplusplus
}
#endif

#endif /* _pkimessage_h_ */
