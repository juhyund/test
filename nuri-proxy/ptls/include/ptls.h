#ifndef __PTLS_H__
#define __PTLS_H__

#include <stddef.h>

#if defined(__cplusplus)
# define EXTERNC        extern "C"
#else
# define EXTERNC
#endif

#ifdef WIN32
#ifdef EXPORT_PTLS
#define LIBSPEC_PTLS EXTERNC __declspec(dllexport)
#else //EXPORT_PTLS
#define LIBSPEC_PTLS EXTERNC __declspec(dllimport)
#endif //EXPORT_PTLS
#else //WIN32
#define LIBSPEC_PTLS EXTERNC
#endif //WIN32

#if defined(KEPCO)
#define PTLS_VERSION_STR "3.0.1.2_kepco"
#elif defined(AMI)
#define PTLS_VERSION_STR "3.0.1.2_ami"
#else
#define PTLS_VERSION_STR "3.0.1.2"
#endif

#define PTLS_ERR_FATAL                         -0x0001
#define PTLS_ERR_SSL_TIMEOUT                   -0x6780  /**< The operation timed out. */
#define PTLS_ERR_SSL_HELLO_VERIFY_REQUIRED     -0x6A00  /**< DTLS client must retry for hello verification */
#define PTLS_ERR_SSL_WANT_READ                 -0x6880  /**< No data of requested type currently available on underlying transport. */
#define PTLS_ERR_SSL_WANT_WRITE                -0x6800  /**< Connection requires a write call. */
#define PTLS_ERR_SSL_BAD_INPUT_DATA            -0x7100  /**< Bad input parameters to function. */

#define PTLS_SSL_MAX_HOST_NAME_LEN           255    /*!< Maximum host name defined in RFC 1035 */
#define PTLS_SSL_MAX_CONTENT_LEN             16384  /**< Size of the input / output buffer */

// init 함수의 입력 파라미터 transport의 정의값
#define PTLS_SSL_TRANSPORT_STREAM            0   /*!< TLS      */
#define PTLS_SSL_TRANSPORT_DATAGRAM          1   /*!< DTLS     */

// CONF_VERIFY_MODE 카테고리의 값 설정 시 사용되는 value 정의값
#define PTLS_SSL_VERIFY_NONE                 0 /*!< server default value */
#define PTLS_SSL_VERIFY_OPTIONAL             1
#define PTLS_SSL_VERIFY_REQUIRED             2 /*!< client default value */
#define PTLS_SSL_VERIFY_UNSET                3

#define PTLS_SSL_VERIFY_TYPE_CRL             0 /*!< default */
#define PTLS_SSL_VERIFY_TYPE_OCSP            1
#define PTLS_SSL_VERIFY_TYPE_OCSP_STAPLING   2

// CONF_CIPHER_SUITE 카테고리의 값 설정 시 사용되는 value 정의값
#define PTLS_CIPHERSUITE_DEFAULT             0 // all supported ciphersuites
#define PTLS_CIPHERSUITE_ARIA256             1
#define PTLS_CIPHERSUITE_ARIA128             2

// CONF_DEBUG_LEVEL 카테고리의 값 설정 시 사용되는 value 정의값
#define PTLS_DEBUG_NO                        0
#define PTLS_DEBUG_ERROR                     1
#define PTLS_DEBUG_STATE_CHANGE              2
#define PTLS_DEBUG_INFORMATIONAL             3
#define PTLS_DEBUG_VERBOSE                   4

// ptls_config 함수에서 사용되는 confType 정의값
typedef enum {
    CONF_CIPHER_SUITE, /*!< preset cipher suite 변경 설정 */
    CONF_VERIFY_MODE, /*!< 검증 모드 설정 */
    CONF_VERIFY_TYPE, /*!< 검증 방식(CRL/OCSP) 설정 */
    CONF_READ_TIMEOUT, /*!< 데이터 수신을 기다리는 timeout 설정 */
    CONF_DEBUG_LEVEL /*!< debug threshold 설정 */
} confType;

/**
  @brief tls/dtls 세션 생성을 위해 사용되는 구조체
  @note 자신의 키, 인증서, CA 인증서 리스트, CRL 등을 포함한다.

  ptls_ctx *ctx = NULL;

  // 생성
  if (NULL == (ctx = ptls_ctx_malloc()))
      return -1;

  // 소멸
  ptls_ctx_free(ctx);
 */
typedef struct ptls_context ptls_ctx;

/**
  @brief tls/dtls 세션에 사용되는 구조체
  @note 세션 정보, 서버 또는 클라이언트 fd 등을 포함한다.

  ptls_session_ctx *sctx = NULL;

  // 생성
  if (NULL == (sctx = ptls_session_ctx_malloc()))
      return -1;

  // 소멸
  ptls_session_ctx_free(sctx);
 */
typedef struct ptls_session_context ptls_session_ctx;


/**
  @brief print WA-SSL library version
  @return char*
 */
LIBSPEC_PTLS char* ptls_get_version(void);

/**
  @brief Translate a penta TLS error code into a string representation,
          Result is truncated if necessary and always includes a terminating
          null byte.

  @param[out] buf buffer to place representation in
  @param[in] buflen length of the buffer
  @param[in] err_code error code
  @return 0 또는 문자열 변환 실패 시 -1 반환
 */
LIBSPEC_PTLS int ptls_get_error_string(char *buf, size_t buflen, int err_code);

/**
  @defgroup commonAPI
  @addtogroup commonAPI
  @{ */

/**
  @brief ptls_ctx 메모리를 할당한다.
  @return ptls_ctx*
 */
LIBSPEC_PTLS ptls_ctx* ptls_ctx_malloc(void);
/**
  @brief ptls_ctx 메모리를 해제한다.
  @param[out] ctx ptls_ctx
 */
LIBSPEC_PTLS void ptls_ctx_free(ptls_ctx *ctx);

/**
  @brief ptls_session_ctx 메모리를 할당한다.
  @return ptls_session_ctx*
 */
LIBSPEC_PTLS ptls_session_ctx* ptls_session_ctx_malloc(void);
/**
  @brief ptls_session_ctx 메모리를 해제한다.
  @param[out] ctx ptls_session_ctx
 */
LIBSPEC_PTLS void ptls_session_ctx_free(ptls_session_ctx *sctx);

/**
  @brief cipher suite, 인증 방법, timeout, debug threshold를 설정한다.
  @note ctx를 ptls_*_init() API를 통해 초기화한 후 입력해야 한다.

  @param[out] ctx ptls_ctx
  @param[in] type 설정할 유형
  @param[in] value 설정 값
 */
LIBSPEC_PTLS void ptls_config(ptls_ctx *ctx, confType type, int value);

/**
  @brief CA 인증서 리스트, CRL를 다시 로드한다.
  @note ctx를 ptls_*_init() API를 통해 초기화한 후 입력해야 한다.

  @param[out] ctx ptls_ctx
  @param[in] ca CA 인증서 리스트, CRL 파일 경로가 설정된 파일의 경로
 */
LIBSPEC_PTLS int ptls_reload_ca(ptls_ctx *ctx, char *ca);

/**
  @brief 세션에서 사용하도록 설정된 cipher suite를 문자열을 반환한다.
  @param[in] sctx ptls_session_ctx
  @return char*
 */
LIBSPEC_PTLS const char *ptls_get_session_ciphersuite(ptls_session_ctx *sctx);

/**
  @brief 세션에서 생성된 socket fd 값을 반환한다.
  @param[in] sctx ptls_session_ctx
  @return int
 */
LIBSPEC_PTLS int ptls_get_socket_fd(ptls_session_ctx *sctx);

/** @} */


/**
  @defgroup serverAPI
  @addtogroup serverAPI
  @{ */

/**
  @brief ctx를 초기화
  사용할 프로토콜, 자신의 키(와 비밀번호), 인증서, CA 인증서 리스트, CRL 파일 경로를 입력하여 ctx를 구성
  @note ca_conf는 다음과 같은 특정 형식에 맞춰 작성되어야 한다.
  <ca>
  <chain>
  // CA 인증서 파일 경로
  </chain>
  <crl>
  // CRL 파일 경로
  </crl>
  </ca>
  <ca>
  ...
  </ca>

  @param[out] ctx ptls_ctx
  @param[in] transport TLS/DTLS 설정
    PTLS_SSL_TRANSPORT_STREAM: TLS
    PTLS_SSL_TRANSPORT_DATAGRAM: DTLS
  @param[in] own_key 키 파일 경로
  @param[in] own_pwd 키 파일의 비밀번호
  @param[in] own_crt 인증서 파일 경로
  @param[in] ca_conf CA 인증서 리스트, CRL 파일 경로가 설정된 파일의 경로
 */
LIBSPEC_PTLS int ptls_server_init(ptls_ctx *ctx, int transport, char *own_key, char *own_pwd, char *own_crt, char *ca_conf);
/**
  @brief listen fd를 bind

  @param[in,out] ctx ptls_ctx
  @param[in] bind_ip bind할 IP address
  @param[in] port 포트 번호
 */
LIBSPEC_PTLS int ptls_server_bind(ptls_ctx *ctx, const char *bind_ip, const char *port);
/**
  @brief 클라이언트와 세션을 맺는다.
  클라이언트가 서버에 connect할 때까지 기다리고, accept한다.
  @note sctx는 매번 초기화된 후 새로운 값이 설정된다.

  @param[out] sctx ptls_session_ctx
  @param[in] ctx ptls_ctx
 */
LIBSPEC_PTLS int ptls_server_accept(ptls_session_ctx *sctx, ptls_ctx *ctx);
/**
  @brief 메세지 수신
  @return 에러 코드 또는 마지막으로 받은 메시지의 크기

  @param[in,out] sctx ptls_session_ctx
  @param[out] buf 메시지
  @param[in] buf_len buf의 메모리 할당 크기
 */
LIBSPEC_PTLS int ptls_server_read(ptls_session_ctx *sctx, unsigned char *buf, int buf_len);
/**
  @brief 메세지 송신
  @return 에러 코드 또는 마지막으로 보낸 메시지의 크기

  @param[in,out] sctx ptls_session_ctx
  @param[in] buf 메시지
  @param[in] len 메시지의 크기
 */
LIBSPEC_PTLS int ptls_server_write(ptls_session_ctx *sctx, unsigned char *buf, int len);
/**
  @brief 세션 종료 명령을 보내고 세션을 끝낸다.
  @param[in,out] sctx ptls_session_ctx
 */
LIBSPEC_PTLS int ptls_server_session_close_notify(ptls_session_ctx *_sctx);
/**
  @brief ctx를 제로화
  @param[out] ctx ptls_ctx
 */
LIBSPEC_PTLS int ptls_server_final(ptls_ctx *ctx);

/** @} */


/**
  @defgroup clientAPI
  @addtogroup clientAPI
  @{ */

/**
  @brief ctx를 초기화
  사용할 프로토콜, 자신의 키(와 비밀번호), 인증서, CA 인증서 리스트, CRL 파일 경로를 입력하여 ctx를 구성
  @note ca_conf는 다음과 같은 특정 형식에 맞춰 작성되어야 한다.
  <ca>
  <chain>
  // CA 인증서 파일 경로
  </chain>
  <crl>
  // CRL 파일 경로
  </crl>
  </ca>
  <ca>
  ...
  </ca>

  @param[out] ctx ptls_ctx
  @param[in] transport TLS/DTLS 설정
    PTLS_SSL_TRANSPORT_STREAM: TLS
    PTLS_SSL_TRANSPORT_DATAGRAM: DTLS
  @param[in] own_key 키 파일 경로
  @param[in] own_pwd 키 파일의 비밀번호
  @param[in] own_crt 인증서 파일 경로
  @param[in] ca_conf CA 인증서 리스트, CRL 파일 경로가 설정된 파일의 경로
 */
LIBSPEC_PTLS int ptls_client_init(ptls_ctx *ctx, int transport, char *own_key, char *own_pwd, char *own_crt, char *ca_conf);
/**
  @brief 서버와 세션을 맺는다.

  @param[out] sctx ptls_session_ctx
  @param[in] ctx ptls_ctx
  @param[in] host 서버의 CN
  @param[in] port 포트 번호
 */
LIBSPEC_PTLS int ptls_client_connect(ptls_session_ctx *_sctx, ptls_ctx *ctx, const char *host, const char *port);
/**
  @brief 메세지 수신
  @return 에러 코드 또는 마지막으로 받은 메시지의 크기

  @param[in,out] sctx ptls_session_ctx
  @param[out] buf 메시지
  @param[in] buf_len buf의 메모리 할당 크기
 */
LIBSPEC_PTLS int ptls_client_read(ptls_session_ctx *sctx, unsigned char *buf, int buf_len);
/**
  @brief 메세지 송신
  @return 에러 코드 또는 마지막으로 보낸 메시지의 크기

  @param[in,out] sctx ptls_session_ctx
  @param[in] buf 메시지
  @param[in] len 메시지의 크기
 */
LIBSPEC_PTLS int ptls_client_write(ptls_session_ctx *sctx, unsigned char *buf, int len);
/**
  @brief 세션 종료 명령을 보내고 세션을 끝낸다.
  @param[in,out] sctx ptls_session_ctx
 */
LIBSPEC_PTLS int ptls_client_session_close_notify(ptls_session_ctx *_sctx);
/**
  @brief ctx를 제로화
  @param[out] ctx ptls_ctx
 */
LIBSPEC_PTLS int ptls_client_final(ptls_ctx *ctx);

/** @} */

#endif //__PTLS_H__
