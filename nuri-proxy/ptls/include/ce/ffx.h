#ifndef _POPFFX_H_
#define _POPFFX_H_

#include "pe_define.h"
#include "fpe_common.h"

#ifdef __cplusplus
extern "C" {
#endif


LIBSPEC_PE
extern FpeAlgorithmDescriptor popffx;

LIBSPEC_PE
extern FpeAlgorithmDescriptor popffx16;

LIBSPEC_PE
extern FpeAlgDescriptor popffxex;

LIBSPEC_PE
extern FpeAlgDescriptor popffx16ex;

#define POPFFX &popffx

#define POPFFX16 &popffx16

#define POPFFXEX &popffxex

#define POPFFX16EX &popffx16ex


BWT F4ARBBYTE(BYTE *out, BWT *outLen, BYTE *in, BWT inLen, BWT xLen, BWT radix, AlgDesc bcipherAlg, AlgDesc hashAlg, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv, BWT l, BWT r, BWT i);

BWT F4ARBBT16(BT16 *out, BWT *outLen, BT16 *in, BWT inLen, BWT xLen, BWT radix, AlgDesc bcipherAlg, AlgDesc hashAlg, BCipherKey *bcKey, BT16 *tweak, BWT tweakLen, BYTE *iv, BWT l, BWT r, BWT i);


#ifdef __cplusplus
}
#endif

#endif /* _FFX_H_ */
