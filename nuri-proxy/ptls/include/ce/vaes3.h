
#ifndef _POPVAES3_H_
#define _POPVAES3_H_

#include "bcipher_op.h"
#include "pe_define.h"
#include "fpe_common.h"
#include "mint_common.h"

#ifdef __cplusplus
extern "C" {
#endif


LIBSPEC_PE
extern FpeAlgDescriptor popvaes3;

#define POPVAES3 &popvaes3

LIBSPEC_PE
BWT VAES3_KENGEN(BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BWT inLen, BWT radix , AlgDesc bcipherAlg);

//LIBSPEC_PE
//BWT VAES3_ENCRYPTION(MINT *out, BWT *outLen, MINT *in, BWT inLen, BWT xLen, BWT radix, AlgDesc bcipherAlg, AlgDesc hashAlg, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv, BWT l, BWT r, BWT i, MINT *radix_m);

#ifdef __cplusplus
}
#endif

#endif /* _VAES3_H_ */

