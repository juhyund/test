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
 * PKIMessage ó���ÿ� �ʿ��� �����͵��� �����ϴ� ����ü
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
 * PKIContext ���� �����Ѵ�.
 *
 * @param nidSymmAlg  (In) �޽��� ����, �ؼ��ÿ� ���� ��ĪŰ algorithm
 * @return 
 *  - SUCCESS : ����
 */
LIBSPEC_CKM
int PKIContext_Set(PKIContext *pPKIContext, Nid nidSymmAlg);

/****************************************************************/
/* PKI Header */

#define PKIMSG_NONCE_LEN 16 /* bytes */

LIBSPEC_CKM
int PKIMSG_MakeNonce(OctetString *nonce);

/**
 * PKIHeader�� �����Ѵ�.
 *
 * @param *header         (Out) ������ Header���� ������ ����, 
 *                              �̸� ASN_New(PKIHeader,NULL)�� �̿��Ͽ� �ʱ�ȭ �Ǿ� �־�� �Ѵ�.
 * @param *senderName     (In)  sender�� DN
 * @param *recipientName  (In)  recipient�� DN
 * @param nowTime         (In)  �޽��� ���� �ð�, 0�̸� ���� �ð��� �̿�
 * @param protectNid      (In)  protection�� �����ϴµ� ����� algorithm, 0�̸� ������� ����
 * @param *senderKID      (In)  senderKID, NULL�� ��� ������� ����
 * @param *recipientKID   (In)  recipientKID, NULL�� ��� ������� ����
 * @param *tranID         (In)  transaction ID, NULL�� ��� ������� ����
 * @param *senderNonce    (In)  �޽����� reply attack�� ���� ���� Nonce��, NULL�̸� ���������� ���� 
 * @param *recipientNonce (In)  ���� �޽����� �����ϴ� ���, ������ ��û �޽����� sender Nonce��
 *
 * @return 
 *  - SUCCESS : ����
 *  - �׿��� ���� ����...
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
 * CertReqMsg�� �����Ѵ�.
 *
 * @param pCertReqMsg     (Out) ������ CertReqMsg���� ������ ����, 
 *                              �̸� ASN_New(CertReqMsg,NULL)�� �̿��Ͽ� �ʱ�ȭ �Ǿ� �־�� �Ѵ�.
 * @param nCertReqId      (In)  certReqId��
 * @param pEntityInfo     (In)  ������ �߱� ��� ���� ����
 * @param pSenderAuthInfo (In)  ��û�� ������ ���� ����(POP ����� �����ϱ� ���� ���)
 * @param pReqCertInfo     (In)  ������ �߱� ��û�� ���� Ű ����
 * @param pCACert         (In)  CA�� ������(POP�� thisMessage ����϶�, �����Ű�� ��ȣȭ �ϱ� ���� ���
 *                                        ��, ir�� ��쿡�� �� ���� NULL�̸� secret value�� �̿��Ͽ� ��ȣȭ)
 * @param pSymmAlg        (In)  ��ĪŰ �˰���(CertReqMsg���� �����͸� ��ȣȭ �� �� ���)
 * @return 
 *  - SUCCESS : ����
 */
enum {
  ER_PKIMSG_CERTREQMSG_FAIL_TO_MAKEPOP = -200,   /**< POP ���� ���� */
  ER_PKIMSG_CERTREQMSG_FAIL_TO_MAKEARCHIVEOPT,   /**< PKIArchiveOptions ���� ���� */
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
 * RevDetails�� �����Ѵ�.
 *
 * @param *pRevDetails    (Out) ������ RevDetails���� ������ ����
 *                              �̸� ASN_New(CertReqMsg,NULL)�� �̿��Ͽ� �ʱ�ȭ �Ǿ� �־�� �Ѵ�.
 * @param *pSerialNumber  (In)  ������ �������� �ø��� ��ȣ
 * @param *pIssuer        (In)  ������ �������� issuer ��
 * @param *pSubject       (In)  ������ �������� subject ��
 * @param nReasonFlag     (In)  ���� ����(x509pkc.h ����), 0�̸� ���������� �������� �ʴ´�.
 * @param *pCrlEntryDetails (In) crlEntryDetails��, NULL�̸� ������� ����
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
 * certReqMsg�� �ؼ��Ѵ�.
 * certReqMsg�� �ؼ��ϴ� ������ ������ �Ϸ��� �������� �����Ѵ�.
 *  1. certTemplate ���� �˻�
 *    1.1. version �˻�
 *    1.2. issuer ���� �˻�
 *    1.3. signingAlg ���� �˻�
 *    1.4. subject ���� �˻�
 *    1.5. publicKey ���� �˻�(POPȮ�� �� publicKey �˻絵 �̷�����Ƿ� ����),
 *    1.6. �׿�(serialNumber, issuerUID, subjectUID, validity���� CA�� ����)
 *  2. POP �˻�
 *  3. ���� ������� �̿��Ͽ� PKIReqCertInfo ����
 *
 * @param *pReqCertInfo      (Out) ������ PKIReqCertInfo
 * @param *pCertReqMsg      (In)  CertReqMsg ��
 * @param  nowTime          (In)  �޽��� ������ ���� ���� �ð�(0�̸� System�� ���� �ð��� ���)
 * @param *pEntityInfo      (In)  ������� ������ ��� �մ� PKIEntityInfo
 * @param *pSenderAuthInfo  (In)  ��û�� ������ ���� ������ ��� �ִ� PKIEntityInfo
 * @param *pCACert          (In)  CA ������
 * @param *pCAPrivateKey    (In)  CA �����Ű, NULL�̸� ��ȣȭŰ POP ������ ����.
 * @param *pDomainParameter (In)  ������ �Ķ����(NULL ����)
 */
enum{
  ER_PKIMSG_RESOLVE_CERTREQMSG_INVALID_VERSION = -200,
  ER_PKIMSG_RESOLVE_CERTREQMSG_ISSUER_MISMATCH,
  ER_PKIMSG_RESOLVE_CERTREQMSG_INVALID_SIGNINGALG,
  ER_PKIMSG_RESOLVE_CERTREQMSG_SUBJECT_MISMATCH,
  ER_PKIMSG_RESOLVE_CERTREQMSG_FAIL_TO_VERIFY_POP,
  ER_PKIMSG_RESOLVE_CERTREQMSG_FAIL_TO_DECRYPT_PRIKEY_IN_ARCHIVEOPT,
  ER_PKIMSG_RESOLVE_CERTREQMSG_UNSUPPORTED_ARCHIVEOPT,                /**< �������� �ʴ� ����� PKIArchiveOptions */
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
 * �־��� PKIBody�� ���� PKIMessage�� �����Ѵ�.
 *
 * @param *pRequestMsg        (Out) ������ PKI Message
 * @param *pPKIContext        (In,Out) PKIMessage ó���� ���Ǵ� ������ ������ �δ� Context
 * @param  nowTime            (In)  �޽��� ���� �ð�(0�̸� System�� ���� �ð��� ���)
 * @param *pPKIEntityInfo     (In)  ������ �߱�(����) ��� ���� ����
 * @param *pPKISenderAuthInfo (In)  ��û�� ������ ���� ����
 * @param *pPKIBody           (In)  PKIMessage�� ���� PKIBody
 * @param *pRecipientCert     (In)  �������� ������(NULL ����)
 * @param *pCACert            (In)  CA�� ������(�����Ű�� ��ȣȭ �ϴµ� ���, NULL ����)
 *
 * @return �����ڵ�� PKIMSG_MakeRequest�� ����
 */
LIBSPEC_CKM
int PKIMSG_MakePKIMessage(PKIMessage         *pRequestMsg,
                          PKIContext         *pPKIContext,
                          time_t              nowTime,
                          PKISenderAuthInfo  *pSenderAuthInfo,
                          PKIBody            *pPKIBody,
                          Certificate        *pRecipientCert);

/**
 * PKIMessage �� request �޽����� �����Ѵ�.(ir, cr, kur, ccr, rr)
 *
 * @param *pRequestMsg        (Out) ������ PKI Message
 * @param *pPKIContext        (In,Out) PKIMessage ó���� ���Ǵ� ������ ������ �δ� Context
 * @param  nowTime            (In)  �޽��� ���� �ð�(0�̸� System�� ���� �ð��� ���)
 * @param  nMsgType           (In)  �޽��� ����(PKIBody_ir, PKIBody_cr... : PKIBody ����)
 * @param *pPKIEntityInfo     (In)  ������ �߱� ��� ���� ����(������ �߱� ��û�� �ƴ� ��쿡�� NULL ����)
 * @param *pPKISenderAuthInfo (In)  ��û�� ������ ���� ����
 * @param *pSeqOfReqInfo      (In)  ������ ��û�� ���� Ű ����
 *                                  ������ �߱� ��û�� ��� certReqInfo�� publicKey�� privateKey���� NULL�̸� ���ο��� Ű���� �����Ѵ�.
 * @param *pRecipientCert     (In)  �������� ������(NULL ����)
 * @param *pCACert            (In)  CA�� ������(�����Ű�� ��ȣȭ �ϴµ� ���, NULL ����)
 *
 * @return 
 */
enum{
  ER_PKIMSG_REQUEST_INVALID_MSGTYPE = -200,   /**< �߸��� MsgType �� */
  ER_PKIMSG_REQUEST_INVALID_SENDERAUTHINFO,   /**< �߸��� PKISenderAuthInfo �� */
  ER_PKIMSG_REQUEST_INVALID_REQINFO,          /**< �߸��� PKIReqInfo �� */
  ER_PKIMSG_REQUEST_FAIL_TO_GEN_KEYPAIR,      /**< Ű �� ���� ���� */
  ER_PKIMSG_REQUEST_FAIL_TO_MAKE_CERTREQMSG,  /**< CertReqMsg ���� ���� */
  ER_PKIMSG_REQUEST_FAIL_TO_MAKE_REVDETAILS,  /**< RevDetails ���� ���� */
  ER_PKIMSG_REQUEST_FAIL_TO_MAKE_HEADER,      /**< Header ���� ���� */
  ER_PKIMSG_REQUEST_FAIL_TO_MAKE_MESSAGE,     /**< Message ���� ���� */
  ER_PKIMSG_REQUEST_CANNOT_FIND_OLDCERT,      /**< ���� ������ ���� PKIReqCertInfo�� �����Ǿ� ���� ����. 
                                                   kur�� rr�޽��� �������� ���� ���������� �����Ǿ� �־�� �Ѵ�.*/
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
 * PKIMessage�� �����Ѵ�. (Nonce, Protection, etc)
 *
 * ���� �ڵ�� PKIMSG_ResolveResponse�� ���� ���
 */
LIBSPEC_CKM
int PKIMSG_VerifyResponse(PKIMessage        *pPKIMessage,
                            PKIContext        *pPKIContext,
                            time_t             nowTime);

/**
 * response �޽����� �ؼ��Ѵ�.(ip, cp, kup, ccp, rp)
 * 
 * @param *pPKIRepInfo  (Out) ��û ����� ������ ����ü
 * @param *pPKIContext  (In,Out) PKIMessage ó���� ���Ǵ� ������ ������ �δ� Context
 * @param *pResonseMsg  (In) response �޽���
 * @param  nowTime      (In) �޽��� ������ ���� ���� �ð�(0�̸� System�� ���� �ð��� ���)
 */
enum{
  ER_PKIMSG_RESPONSE_INVALID_PVNO = -200,   /**< Response�� pvno���� 1�� �ƴ� */
  ER_PKIMSG_RESPONSE_INVALID_RECIPIENT,     /**< Recipient ���� directoryName�� �ƴ� */
  ER_PKIMSG_RESPONSE_RECIPIENT_MISMATCH,    /**< Response�� Recipient ���� Request�� Sender���� ��ġ���� ���� */
  ER_PKIMSG_RESPONSE_INVALID_SENDER,        /**< Sender ���� directoryName�� �ƴ� */
  ER_PKIMSG_RESPONSE_SENDER_MISMATCH,       /**< Response�� Sender ���� Request�� Recipient ��ġ���� ���� */
  ER_PKIMSG_RESPONSE_CANNOT_FIND_RECIPNONCE,/**< Response�� recipNonce ���� �������� ���� */
  ER_PKIMSG_RESPONSE_RECIPNONCE_MISMATCH,   /**< Response�� recipNonce ���� Request�� senderNonce�� ��ġ���� ����*/
  ER_PKIMSG_RESPONSE_CANNOT_FIND_SENDERNONCE, /**< Response�� senderNonce ���� �������� ���� */
  ER_PKIMSG_RESPONSE_CANNOT_FIND_TRANSID,   /**< Response�� transactionID ���� �������� ���� */
  ER_PKIMSG_RESPONSE_TRANSID_MISMATCH,      /**< Response�� transactionID ���� Request�� transactionID�� ��ġ���� ����*/
  ER_PKIMSG_RESPONSE_CANNOT_FIND_PROTECTIONALG, /**< Response�� protectionAlg ���� �������� ���� */
  ER_PKIMSG_RESPONSE_IMPROPER_PROTECTIONALG,/**< �߸��� ����� protection(MAC ����� �䱸�ɶ� signature�� ��� Ȥ�� �� �ݴ� */
  ER_PKIMSG_RESPONSE_FAIL_TO_VERIFY_PROTECTION, /**< Protection ���� ���� */
  ER_PKIMSG_RESPONSE_BAD_PROTECTION_ERROR_MSG,  /**< Protection ������ ������ ���� �޽��� */

  ER_PKIMSG_RESPONSE_INVALID_BODY_TYPE,     /**< �߸��� PKIBody choice �� */
  ER_PKIMSG_RESPONSE_WRONG_REP_SIZE,        /**< ���� �޽��� ���� ���� ������ ��û ������ ��ġ���� ���� */
  ER_PKIMSG_RESPONSE_CANNOT_FIND_CERTIFIEDKEYPAIR,  
                                            /**< ���� �޽��� ���� certifiedKeyPair���� �������� ���� */
  ER_PKIMSG_RESPONSE_WRONG_CERTORENCCERT,   /**< �߸��� certOrEncCert �� */
  ER_PKIMSG_RESPONSE_INVALID_CERTIFICATE,   /**< �߸��� certificate �� */
  ER_PKIMSG_RESPONSE_FAIL_TO_DECRYPT_ENCCERT,
                                            /**< ���� �޽��� ���� encryptedCert�� ��ȣȭ ���� */
  /* ER_PKIMSG_RESPONSE_ */
};
LIBSPEC_CKM
int PKIMSG_ResolveResponse(PKIRepInfo     *pPKIRepInfo,
                           PKIContext     *pPKIContext,
                           PKIMessage     *pResponseMsg,
                           time_t          nowTime);


/**
 * Confirm �޽����� �����Ѵ�.
 *
 * @param *pConfirmMsg  (Out) ������ confirm �޽���
 * @param *pPKIContext  (In,Out) PKIMessage ó���� ���Ǵ� ������ ������ �δ� Context
 * @param  nowTime      (In) �޽��� ���� �ð�(0�̸� System�� ���� �ð��� ���)
 */
enum{
  ER_PKIMSG_MAKE_CONF_FAIL_TO_MAKE_HEADER = -200, /**< Header ���� ���� */
  ER_PKIMSG_MAKE_CONF_FAIL_TO_MAKE_MESSAGE,       /**< Message ���� ���� */
};
LIBSPEC_CKM
int PKIMSG_MakeConfirm(PKIMessage *pConfirmMsg,
                       PKIContext *pPKIContext,
                       time_t      nowTime);

/**
 * KeyPolicy�� CA/RA���Լ� ���ϱ� ���� ��û �޽����� �����Ѵ�.
 * FIXME : �������� KeyPolicy�� ���ÿ� ��û�� �� ����, ���Ѵ�� ���
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
 *  CA/RA���Լ� �� ���� �޽������� KeyPolicies�� ���س���.
 * FIXME : �������� KeyPolicy�� ���ÿ� ���� �� ����, ���Ѵ�� ���
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
