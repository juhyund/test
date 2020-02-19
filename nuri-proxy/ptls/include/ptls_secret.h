#ifndef __PTLS_SECRET_H__
#define __PTLS_SECRET_H__

#include "ptls.h"

LIBSPEC_PTLS int ptls_get_session_secret_info(ptls_session_ctx *sctx, int *client_port,
    char *client_ip, int *client_iplen, int client_ip_buflen,
    unsigned char *enc_fixed_iv, int *enc_fixed_ivlen, int enc_fixed_iv_buflen,
    unsigned char *dec_fixed_iv, int *dec_fixed_ivlen, int dec_fixed_iv_buflen,
    unsigned char *enc_key, int *enc_keylen, int enc_key_buflen,
    unsigned char *dec_key, int *dec_keylen, int dec_key_buflen);

#endif //__PTLS_SECRET_H__
