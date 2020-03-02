#ifndef _qsl_h_
#define _qsl_h_

#include "sp_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/* QSL Constants */

#define QSL_MASTER_LEN         6
#define QSL_MAGIC_NUMBER  0x2125
#define QSL_VERSION       0x0100  /* 1.0 */
#define QSL_DATAHEAD_LEN       4

#define QSL_MAX_KEY_LEN       32  /* 256bit */
#define QSL_DEFAULT_KEY_LEN   16  /* 128bit */

#define QSL_CLIENT_INFO_LEN 512
#define QSL_TICKET_LEN      512
#define QSL_ERROR_MSG_LEN   256


#define QSL_DEFAULT_TS (3600 * 2) /* 2 hours */

enum QSL_ALG {
  QSL_NOENC = 0x00,  // no-encryption 
  QSL_SEED  = 0x01,  // use SEED 
  QSL_AES   = 0x02,  // use RJINDAEL 
};

enum QSL_ERR {
  ER_QSL_FAIL = ER_QSL,
  ER_QSL_CANNOT_RESOLVE, /* cannot resolve master, header or something else */
  ER_QSL_TICKET_EXPIRED, /* ticket expired */
  ER_QSL_ERROR_RETURNED, /* error returned from server */
  ER_QSL_BUF_TOO_SMALL,  /* too small buffer */
  ER_QSL_ENCRYPTION_FAILED,
  ER_QSL_DECRYPTION_FAILED,
};

enum QSL_STATUS {
  QSL_STATUS_INIT = 0,  /* 아무 일도 이루어지지 않은 상태 */
  QSL_STATUS_SENT_CLSK, /* client가 자신의 SK를 서버에 보내놓은 상태 */
  QSL_STATUS_HAVE_CLSK, /* client가 보낸 SK를 획득한 상태 */
  QSL_STATUS_HAVE_SVSK, /* 서버가 보낸 SK를 획득한 상태 */
  QSL_STATUS_ERROR      /* 서버가 에러를 감지하고 client에게 리턴해야할 때 */
};

typedef struct _QSLSession {
  enum QSL_STATUS status;
  enum QSL_ALG    cipher;

  BYTE  sessionKey[QSL_MAX_KEY_LEN];
  int   sessionKeyLen;
  BYTE  newKey[QSL_MAX_KEY_LEN];
  int   newKeyLen;

  Certificate *serverCertificate;
  char         clientInfo[QSL_CLIENT_INFO_LEN];

  /* ticket */
  char  ticket[QSL_TICKET_LEN];
  int   ticketLen;

  /* errors */
  int   errorCode;
  char  errorMsg[QSL_ERROR_MSG_LEN];

  /* only for server */
  PrivateKeyInfo *serverPriKey;
  BYTE            sessionMasterKey[QSL_MAX_KEY_LEN];
  int             sessionMasterKeyLen;
  time_t          validPeriod;
} QSLSession;

#define QSL_Client_New POPQSL_Client_New
#define QSL_Server_New POPQSL_Server_New
#define QSL_Del POPQSL_Del
#define QSL_GetErrorMsg POPQSL_GetErrorMsg
#define QSL_GetErrorCode POPQSL_GetErrorCode
#define QSL_SetValidPeriod POPQSL_SetValidPeriod
#define QSL_MASTER_Read POPQSL_MASTER_Read
#define QSL_MASTER_Write POPQSL_MASTER_Write
#define QSL_HEADER_Read POPQSL_HEADER_Read
#define QSL_HEADER_Write POPQSL_HEADER_Write
#define QSL_DATAHEAD_Read POPQSL_DATAHEAD_Read
#define QSL_DATAHEAD_Write POPQSL_DATAHEAD_Write
#define QSL_DATA_Decrypt POPQSL_DATA_Decrypt
#define QSL_DATA_Encrypt POPQSL_DATA_Encrypt
#define QSL_TICKET_CreateNewBase64 POPQSL_TICKET_CreateNewBase64
#define QSL_TICKET_DecodeBase64 POPQSL_TICKET_DecodeBase64

LIBSPEC_SP
QSLSession *POPQSL_Client_New(const Certificate  *serverCert,
                           enum QSL_ALG  alg);

LIBSPEC_SP
QSLSession *POPQSL_Server_New(const PrivateKeyInfo *priKey, 
                           const Certificate    *cert);

LIBSPEC_SP
void POPQSL_Del(QSLSession *session);


/************************************************************************/

LIBSPEC_SP
ERT POPQSL_GetErrorMsg(char *errorMsg, int msgMaxLen, QSLSession *session);

LIBSPEC_SP
ERT POPQSL_GetErrorCode(int *errorCode, QSLSession *session);

LIBSPEC_SP
ERT POPQSL_SetValidPeriod(QSLSession *session, unsigned int validSeconds);


/************************************************************************/
/* MASTER */

LIBSPEC_SP
ERT POPQSL_MASTER_Read(int  *protocolVersion,
                    int  *headerLen,
                    BYTE  master[QSL_MASTER_LEN]);

LIBSPEC_SP
ERT POPQSL_MASTER_Write(BYTE master[QSL_MASTER_LEN],
                     int  protocolVersion,
                     int  headerLen);

/************************************************************************/
/* HEADER */

LIBSPEC_SP
ERT POPQSL_HEADER_Read(QSLSession *session,
                    BYTE       *header,
                    int         headerLen);

LIBSPEC_SP
ERT POPQSL_HEADER_Write(BYTE       *header,
                     int        *headerLen,
                     int         headerMaxLen,
                     QSLSession *session);

/************************************************************************/
/* DATAHEAD */

LIBSPEC_SP
ERT POPQSL_DATAHEAD_Read(int  *encFlag,
                      int  *dataLen,
                      BYTE  datahead[QSL_DATAHEAD_LEN]);

LIBSPEC_SP
ERT POPQSL_DATAHEAD_Write(BYTE datahead[QSL_DATAHEAD_LEN],
                       int  encFlag,
                       int  dataLen);

/************************************************************************/
/* DATA Encryption & Decryption */

LIBSPEC_SP
ERT POPQSL_DATA_Decrypt(BYTE *data, int *dataLen, 
                     const BYTE *input, int inputLen,
                     QSLSession *session);

LIBSPEC_SP
ERT POPQSL_DATA_Encrypt(BYTE *data, int *dataLen,
                     const BYTE *input, int inputLen,
                     QSLSession *session);


/************************************************************************/
/* Extented APIs for Web Express V3 */
LIBSPEC_SP
ERT POPQSL_TICKET_CreateNewBase64(BYTE        *ticketBase64,
                               unsigned int ticketBase64Max,
                               QSLSession  *session);

LIBSPEC_SP
ERT POPQSL_TICKET_DecodeBase64(BYTE        sessionKey[16],
                            const char *ticketBase64,
                            QSLSession *session);


#ifdef __cplusplus
}
#endif

#endif /* _qsl_h_ */
