#ifndef __SHA3_H__
#define __SHA3_H__

#include "ce_dll.h"

#ifdef __cplusplus
extern "C" {
#endif

LIBSPEC_CE
int PCIS_KECCAK(unsigned char pad, int c, unsigned char *D, unsigned char *M, int mlen, int d);

#define KECCAK(c, D, dlen, M, mlen)  PCIS_KECCAK(0x01, c, D, M, mlen, (dlen*8))
#define SHA3_224(D, M, mlen)    PCIS_KECCAK(0x06, 448, D, M, mlen, 224)
#define SHA3_256(D, M, mlen)    PCIS_KECCAK(0x06, 512, D, M, mlen, 256)
#define SHA3_384(D, M, mlen)    PCIS_KECCAK(0x06, 768, D, M, mlen, 384)
#define SHA3_512(D, M, mlen)    PCIS_KECCAK(0x06, 1024, D, M, mlen, 512)
#define SHAKE128(D, dlen, M, mlen)    PCIS_KECCAK(0x1f, 256, D, M, mlen, (dlen*8))
#define SHAKE256(D, dlen, M, mlen)    PCIS_KECCAK(0x1f, 512, D, M, mlen, (dlen*8))

#ifdef __cplusplus
}
#endif

#endif