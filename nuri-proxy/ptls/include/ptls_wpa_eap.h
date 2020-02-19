#ifndef __PTLS_WPA_EAP_H__
#define __PTLS_WPA_EAP_H__

typedef int ptls_ssl_send_tt(void *ctx, const unsigned char *buf, size_t len);
typedef int ptls_ssl_recv_tt(void *ctx, unsigned char *buf, size_t len);
typedef enum {
    cert_version,
    serial_number,
    issuer_name,
    subject_name,
    issued_on,
    expires_on,
    signed_using,
    EC_key_size,
    basic_constraints,
    subject_alt_name,
    cert_type,
    key_usage,
    ext_key_usage
} cert_contents;

int ptls_connection_established(ptls_session_ctx *sctx);
int ptls_connection_set_params(ptls_session_ctx *sctx, ptls_ctx *ctx,
                               void *p_bio, ptls_ssl_send_tt *f_send, ptls_ssl_recv_tt *f_recv);
int ptls_connection_get_random(ptls_session_ctx *sctx, unsigned char **client_rand, unsigned char **server_rand);
int ptls_connection_export_key(ptls_session_ctx *sctx, const char *label, unsigned char *out, size_t out_len);
int ptls_connection_handshake(ptls_session_ctx *sctx);

int ptls_get_peer_cert_info(ptls_session_ctx *sctx, cert_contents cnt, char *buf, int size);
int ptls_get_cert_cn(unsigned char *cn, int *cn_len, int cn_buflen, const char *cert_buf, int cert_buflen);

#endif //__PTLS_WPA_EAP_H__
