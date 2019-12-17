#ifndef PTLS_OCSP_H
#define PTLS_OCSP_H

#if !defined(PTLS_CONFIG_FILE)
#include "config.h"
#else
#include PTLS_CONFIG_FILE
#endif

#if defined (PTLS_OCSP_C)

/*
 * OCSP Error codes
 */
#define PTLS_OCSP_CERT_STATUS_GOOD 1
#define PTLS_OCSP_CERT_STATUS_REVOKED 2
#define PTLS_OCSP_CERT_STATUS_UNKNOWN 3
#define PTLS_ERR_OCSP_BAD_INPUT_DATA                    -0x8100  /**< Bad input parameters. */
#define PTLS_ERR_OCSP_READ_PARAMS_FAILED                -0x8110  /**< Reading of the DHM parameters failed. */
#define PTLS_ERR_OCSP_MAKE_NEW_REQUEST                  -0x8120
#define PTLS_ERR_OCSP_MAKE_SERVICE_LOCATOR              -0x8130
#define PTLS_ERR_OCSP_ADD_SINGLE_EXTENSION              -0x8140
#define PTLS_ERR_OCSP_ADD_SINGLE_REQUEST                -0x8150
#define PTLS_ERR_OCSP_CREATE_NEW_OCSPREQ                -0x8160
#define PTLS_ERR_OCSP_RESP_STATUS_MALFORMED_REQUEST     -0x8170
#define PTLS_ERR_OCSP_RESP_STATUS_INTERNAL_ERROR        -0x8180
#define PTLS_ERR_OCSP_RESP_STATUS_NOT_USED              -0x8190
#define PTLS_ERR_OCSP_RESP_STATUS_SIGN_REQUIRED         -0x81A0
#define PTLS_ERR_OCSP_RESP_STATUS_UNAUTHORIZED          -0x81B0
#define PTLS_ERR_OCSP_RESP_STATUS_UNKNOWN               -0x81C0
#define PTLS_ERR_OCSP_REQ_TARGETCERTS_SIZE_LESSTHANONE  -0x81D0
#define PTLS_ERR_OCSP_ADD_REQUEST_EXTENSION             -0x81E0
#define PTLS_ERR_OCSP_NOT_FOUND_AIA                     -0x81F0
#define PTLS_ERR_OCSP_GET_OWN_AIA                       -0x8200
#define PTLS_ERR_OCSP_CHECKRSP_PARAM_IS_NULL            -0x8210
#define PTLS_ERR_OCSP_GET_BASIC_OCSPRSP                 -0x8220
#define PTLS_ERR_OCSP_GET_RESPONDER_CERT                -0x8230
#define PTLS_ERR_OCSP_GET_REQ_EXTENSION                 -0x8240
#define PTLS_ERR_OCSP_NONCE_NOT_VALID                   -0x8250
#define PTLS_ERR_OCSP_CHECK_RESPONDER_CERT              -0x8260
#define PTLS_ERR_OCSP_CHECK_RESPONDER_ID                -0x8270
#define PTLS_ERR_OCSP_RESPONDERCERT_TIME_NOT_VALID      -0x8280
#define PTLS_ERR_OCSP_SERIALNUMBER_NOT_EQUAL            -0x8290
#define PTLS_ERR_OCSP_PRDCTIME_BIGGER_THAN_NEXTUPDATE   -0x82A0
#define PTLS_ERR_OCSP_PRDCTIME_SMALLER_THAN_THISUPDATE  -0x82B0
#define PTLS_ERR_OCSP_GET_OCSP_BASICRSP                 -0x82C0
#define PTLS_ERR_OCSP_SINGLERSP_LESS_THAN_ONE           -0x82D0
#define PTLS_ERR_OCSP_CERT_COPY_FAIL                    -0x82E0
#define PTLS_ERR_OCSP_ENCODE_DER                        -0x82F0
#define PTLS_ERR_OCSP_INSUFFICIENT_MEMORY               -0x8300
#define PTLS_ERR_OCSP_RAW_RSPDATA_IS_NULL               -0x8310
#define PTLS_ERR_OCSP_GET_OCSPRSP                       -0x8320
#define PTLS_ERR_OCSP_REQ_DATA_NULL                     -0x8330
#define PTLS_ERR_OCSP_SEND_POLL_RTN_NEGATIVE            -0x8340
#define PTLS_ERR_OCSP_SEND_TO_SERVER_DATALEN            -0x8350
#define PTLS_ERR_OCSP_SEND_TO_SERVER_DATA               -0x8360
#define PTLS_ERR_OCSP_RCV_POLL_RTN_NEGATIVE             -0x8370
#define PTLS_ERR_OCSP_RCV_DATALEN_MSGPEEK               -0x8380
#define PTLS_ERR_OCSP_RCV_DATALEN                       -0x8390
#define PTLS_ERR_OCSP_RCV_EXCEED_LEN                    -0x83A0
#define PTLS_ERR_OCSP_RCV_DATA                          -0x83B0
#define PTLS_ERR_OCSP_HTTP_RECEIVE_FAIL                 -0x83C0
#define PTLS_ERR_OCSP_HTTP_RCVDATA_INVALID              -0x83D0
#define PTLS_ERR_OCSP_HTTP_HEADER_SIZE_WRONG            -0x83E0
#define PTLS_ERR_OCSP_MAKECONN_STADDR_NULL              -0x83F0
#define PTLS_ERR_OCSP_NOT_CONNECTTED                    -0x8400
#define PTLS_ERR_OCSP_NOT_BIND                          -0x8410

#ifdef __cplusplus
extern "C" {
#endif

int ptls_ocsp_verify_cert(unsigned char *tgt_cert, int tgt_cert_size, unsigned char *ca_cert, int ca_cert_size);

#ifdef __cplusplus
}
#endif

#endif

#endif // PTLS_OCSP_H
