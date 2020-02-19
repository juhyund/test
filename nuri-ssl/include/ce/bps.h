#ifndef _BPS_H_
#define _BPS_H_

#include "mint_common.h"
#include "pe_define.h"
#include "bcipher_op.h"
#include "fpe_common.h"



#ifdef __cplusplus
extern "C" {
#endif


LIBSPEC_PE
extern FpeAlgDescriptor popbps;


#define POPBPS &popbps

LIBSPEC_PE
BWT FPE_BPS_BC(BYTE *out, BYTE *in, BWT inlen, BCipherKey *rkey, BYTE *tweak, AlgDesc bcipherAlg, BWT radix, BWT is_Encrypt);

LIBSPEC_PE
BWT Rev_String(BYTE *X, BWT len);

LIBSPEC_PE
BWT NUM2Radix(MINT *out, BYTE *in, BWT len, BWT radix);

LIBSPEC_PE
BWT Radix2NUM(BYTE *out, MINT *in, BWT len, BWT radix);


#ifdef __cplusplus
}
#endif

#endif /* _BPS_H_ */
