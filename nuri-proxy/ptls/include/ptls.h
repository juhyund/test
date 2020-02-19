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

// init �Լ��� �Է� �Ķ���� transport�� ���ǰ�
#define PTLS_SSL_TRANSPORT_STREAM            0   /*!< TLS      */
#define PTLS_SSL_TRANSPORT_DATAGRAM          1   /*!< DTLS     */

// CONF_VERIFY_MODE ī�װ��� �� ���� �� ���Ǵ� value ���ǰ�
#define PTLS_SSL_VERIFY_NONE                 0 /*!< server default value */
#define PTLS_SSL_VERIFY_OPTIONAL             1
#define PTLS_SSL_VERIFY_REQUIRED             2 /*!< client default value */
#define PTLS_SSL_VERIFY_UNSET                3

#define PTLS_SSL_VERIFY_TYPE_CRL             0 /*!< default */
#define PTLS_SSL_VERIFY_TYPE_OCSP            1
#define PTLS_SSL_VERIFY_TYPE_OCSP_STAPLING   2

// CONF_CIPHER_SUITE ī�װ��� �� ���� �� ���Ǵ� value ���ǰ�
#define PTLS_CIPHERSUITE_DEFAULT             0 // all supported ciphersuites
#define PTLS_CIPHERSUITE_ARIA256             1
#define PTLS_CIPHERSUITE_ARIA128             2

// CONF_DEBUG_LEVEL ī�װ��� �� ���� �� ���Ǵ� value ���ǰ�
#define PTLS_DEBUG_NO                        0
#define PTLS_DEBUG_ERROR                     1
#define PTLS_DEBUG_STATE_CHANGE              2
#define PTLS_DEBUG_INFORMATIONAL             3
#define PTLS_DEBUG_VERBOSE                   4

// ptls_config �Լ����� ���Ǵ� confType ���ǰ�
typedef enum {
    CONF_CIPHER_SUITE, /*!< preset cipher suite ���� ���� */
    CONF_VERIFY_MODE, /*!< ���� ��� ���� */
    CONF_VERIFY_TYPE, /*!< ���� ���(CRL/OCSP) ���� */
    CONF_READ_TIMEOUT, /*!< ������ ������ ��ٸ��� timeout ���� */
    CONF_DEBUG_LEVEL /*!< debug threshold ���� */
} confType;

/**
  @brief tls/dtls ���� ������ ���� ���Ǵ� ����ü
  @note �ڽ��� Ű, ������, CA ������ ����Ʈ, CRL ���� �����Ѵ�.

  ptls_ctx *ctx = NULL;

  // ����
  if (NULL == (ctx = ptls_ctx_malloc()))
      return -1;

  // �Ҹ�
  ptls_ctx_free(ctx);
 */
typedef struct ptls_context ptls_ctx;

/**
  @brief tls/dtls ���ǿ� ���Ǵ� ����ü
  @note ���� ����, ���� �Ǵ� Ŭ���̾�Ʈ fd ���� �����Ѵ�.

  ptls_session_ctx *sctx = NULL;

  // ����
  if (NULL == (sctx = ptls_session_ctx_malloc()))
      return -1;

  // �Ҹ�
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
  @return 0 �Ǵ� ���ڿ� ��ȯ ���� �� -1 ��ȯ
 */
LIBSPEC_PTLS int ptls_get_error_string(char *buf, size_t buflen, int err_code);

/**
  @defgroup commonAPI
  @addtogroup commonAPI
  @{ */

/**
  @brief ptls_ctx �޸𸮸� �Ҵ��Ѵ�.
  @return ptls_ctx*
 */
LIBSPEC_PTLS ptls_ctx* ptls_ctx_malloc(void);
/**
  @brief ptls_ctx �޸𸮸� �����Ѵ�.
  @param[out] ctx ptls_ctx
 */
LIBSPEC_PTLS void ptls_ctx_free(ptls_ctx *ctx);

/**
  @brief ptls_session_ctx �޸𸮸� �Ҵ��Ѵ�.
  @return ptls_session_ctx*
 */
LIBSPEC_PTLS ptls_session_ctx* ptls_session_ctx_malloc(void);
/**
  @brief ptls_session_ctx �޸𸮸� �����Ѵ�.
  @param[out] ctx ptls_session_ctx
 */
LIBSPEC_PTLS void ptls_session_ctx_free(ptls_session_ctx *sctx);

/**
  @brief cipher suite, ���� ���, timeout, debug threshold�� �����Ѵ�.
  @note ctx�� ptls_*_init() API�� ���� �ʱ�ȭ�� �� �Է��ؾ� �Ѵ�.

  @param[out] ctx ptls_ctx
  @param[in] type ������ ����
  @param[in] value ���� ��
 */
LIBSPEC_PTLS void ptls_config(ptls_ctx *ctx, confType type, int value);

/**
  @brief CA ������ ����Ʈ, CRL�� �ٽ� �ε��Ѵ�.
  @note ctx�� ptls_*_init() API�� ���� �ʱ�ȭ�� �� �Է��ؾ� �Ѵ�.

  @param[out] ctx ptls_ctx
  @param[in] ca CA ������ ����Ʈ, CRL ���� ��ΰ� ������ ������ ���
 */
LIBSPEC_PTLS int ptls_reload_ca(ptls_ctx *ctx, char *ca);

/**
  @brief ���ǿ��� ����ϵ��� ������ cipher suite�� ���ڿ��� ��ȯ�Ѵ�.
  @param[in] sctx ptls_session_ctx
  @return char*
 */
LIBSPEC_PTLS const char *ptls_get_session_ciphersuite(ptls_session_ctx *sctx);

/**
  @brief ���ǿ��� ������ socket fd ���� ��ȯ�Ѵ�.
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
  @brief ctx�� �ʱ�ȭ
  ����� ��������, �ڽ��� Ű(�� ��й�ȣ), ������, CA ������ ����Ʈ, CRL ���� ��θ� �Է��Ͽ� ctx�� ����
  @note ca_conf�� ������ ���� Ư�� ���Ŀ� ���� �ۼ��Ǿ�� �Ѵ�.
  <ca>
  <chain>
  // CA ������ ���� ���
  </chain>
  <crl>
  // CRL ���� ���
  </crl>
  </ca>
  <ca>
  ...
  </ca>

  @param[out] ctx ptls_ctx
  @param[in] transport TLS/DTLS ����
    PTLS_SSL_TRANSPORT_STREAM: TLS
    PTLS_SSL_TRANSPORT_DATAGRAM: DTLS
  @param[in] own_key Ű ���� ���
  @param[in] own_pwd Ű ������ ��й�ȣ
  @param[in] own_crt ������ ���� ���
  @param[in] ca_conf CA ������ ����Ʈ, CRL ���� ��ΰ� ������ ������ ���
 */
LIBSPEC_PTLS int ptls_server_init(ptls_ctx *ctx, int transport, char *own_key, char *own_pwd, char *own_crt, char *ca_conf);
/**
  @brief listen fd�� bind

  @param[in,out] ctx ptls_ctx
  @param[in] bind_ip bind�� IP address
  @param[in] port ��Ʈ ��ȣ
 */
LIBSPEC_PTLS int ptls_server_bind(ptls_ctx *ctx, const char *bind_ip, const char *port);
/**
  @brief Ŭ���̾�Ʈ�� ������ �δ´�.
  Ŭ���̾�Ʈ�� ������ connect�� ������ ��ٸ���, accept�Ѵ�.
  @note sctx�� �Ź� �ʱ�ȭ�� �� ���ο� ���� �����ȴ�.

  @param[out] sctx ptls_session_ctx
  @param[in] ctx ptls_ctx
 */
LIBSPEC_PTLS int ptls_server_accept(ptls_session_ctx *sctx, ptls_ctx *ctx);
/**
  @brief �޼��� ����
  @return ���� �ڵ� �Ǵ� ���������� ���� �޽����� ũ��

  @param[in,out] sctx ptls_session_ctx
  @param[out] buf �޽���
  @param[in] buf_len buf�� �޸� �Ҵ� ũ��
 */
LIBSPEC_PTLS int ptls_server_read(ptls_session_ctx *sctx, unsigned char *buf, int buf_len);
/**
  @brief �޼��� �۽�
  @return ���� �ڵ� �Ǵ� ���������� ���� �޽����� ũ��

  @param[in,out] sctx ptls_session_ctx
  @param[in] buf �޽���
  @param[in] len �޽����� ũ��
 */
LIBSPEC_PTLS int ptls_server_write(ptls_session_ctx *sctx, unsigned char *buf, int len);
/**
  @brief ���� ���� ����� ������ ������ ������.
  @param[in,out] sctx ptls_session_ctx
 */
LIBSPEC_PTLS int ptls_server_session_close_notify(ptls_session_ctx *_sctx);
/**
  @brief ctx�� ����ȭ
  @param[out] ctx ptls_ctx
 */
LIBSPEC_PTLS int ptls_server_final(ptls_ctx *ctx);

/** @} */


/**
  @defgroup clientAPI
  @addtogroup clientAPI
  @{ */

/**
  @brief ctx�� �ʱ�ȭ
  ����� ��������, �ڽ��� Ű(�� ��й�ȣ), ������, CA ������ ����Ʈ, CRL ���� ��θ� �Է��Ͽ� ctx�� ����
  @note ca_conf�� ������ ���� Ư�� ���Ŀ� ���� �ۼ��Ǿ�� �Ѵ�.
  <ca>
  <chain>
  // CA ������ ���� ���
  </chain>
  <crl>
  // CRL ���� ���
  </crl>
  </ca>
  <ca>
  ...
  </ca>

  @param[out] ctx ptls_ctx
  @param[in] transport TLS/DTLS ����
    PTLS_SSL_TRANSPORT_STREAM: TLS
    PTLS_SSL_TRANSPORT_DATAGRAM: DTLS
  @param[in] own_key Ű ���� ���
  @param[in] own_pwd Ű ������ ��й�ȣ
  @param[in] own_crt ������ ���� ���
  @param[in] ca_conf CA ������ ����Ʈ, CRL ���� ��ΰ� ������ ������ ���
 */
LIBSPEC_PTLS int ptls_client_init(ptls_ctx *ctx, int transport, char *own_key, char *own_pwd, char *own_crt, char *ca_conf);
/**
  @brief ������ ������ �δ´�.

  @param[out] sctx ptls_session_ctx
  @param[in] ctx ptls_ctx
  @param[in] host ������ CN
  @param[in] port ��Ʈ ��ȣ
 */
LIBSPEC_PTLS int ptls_client_connect(ptls_session_ctx *_sctx, ptls_ctx *ctx, const char *host, const char *port);
/**
  @brief �޼��� ����
  @return ���� �ڵ� �Ǵ� ���������� ���� �޽����� ũ��

  @param[in,out] sctx ptls_session_ctx
  @param[out] buf �޽���
  @param[in] buf_len buf�� �޸� �Ҵ� ũ��
 */
LIBSPEC_PTLS int ptls_client_read(ptls_session_ctx *sctx, unsigned char *buf, int buf_len);
/**
  @brief �޼��� �۽�
  @return ���� �ڵ� �Ǵ� ���������� ���� �޽����� ũ��

  @param[in,out] sctx ptls_session_ctx
  @param[in] buf �޽���
  @param[in] len �޽����� ũ��
 */
LIBSPEC_PTLS int ptls_client_write(ptls_session_ctx *sctx, unsigned char *buf, int len);
/**
  @brief ���� ���� ����� ������ ������ ������.
  @param[in,out] sctx ptls_session_ctx
 */
LIBSPEC_PTLS int ptls_client_session_close_notify(ptls_session_ctx *_sctx);
/**
  @brief ctx�� ����ȭ
  @param[out] ctx ptls_ctx
 */
LIBSPEC_PTLS int ptls_client_final(ptls_ctx *ctx);

/** @} */

#endif //__PTLS_H__
