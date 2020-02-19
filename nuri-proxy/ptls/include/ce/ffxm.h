#ifndef _POPFFXM_H_
#define _POPFFXM_H_

#include "pe_define.h"
#include "fpe_common.h"

#ifdef __cplusplus
extern "C" {
#endif


LIBSPEC_PE
extern FpeAlgorithmDescriptor popffxms;

LIBSPEC_PE
extern FpeAlgorithmDescriptor popffxms16;

LIBSPEC_PE
extern FpeAlgorithmDescriptor popffxml;

LIBSPEC_PE
extern FpeAlgorithmDescriptor popffxml16;

LIBSPEC_PE
extern FpeAlgDescriptor popffxmsex;

LIBSPEC_PE
extern FpeAlgDescriptor popffxms16ex;

LIBSPEC_PE
extern FpeAlgDescriptor popffxmlex;

LIBSPEC_PE
extern FpeAlgDescriptor popffxml16ex;

#define POPFFXMS &popffxms

#define POPFFXMS16 &popffxms16

#define POPFFXML &popffxml

#define POPFFXML16 &popffxml16

#define POPFFXMSEX &popffxmsex

#define POPFFXMS16EX &popffxms16ex

#define POPFFXMLEX &popffxmlex

#define POPFFXML16EX &popffxml16ex


/*F Function for Short version*/
BWT F4S(BT16 *out, BWT *outLen, BT16 *in, BWT inLen, BWT xLen, BWT radix, AlgDesc bcipherAlg, AlgDesc hashAlg, BCipherKey *bcKey, BT16 *tweak, BWT tweakLen, BYTE iv, BWT l, BWT r, BWT i);

/*F Function for Long version*/
BWT F4L(BT16 *out, BWT *outLen, BT16 *in, BWT inLen, BWT xLen, BWT radix, AlgDesc bcipherAlg, AlgDesc hashAlg, BCipherKey *bcKey, BT16 *tweak, BWT tweakLen, BYTE iv, BWT l, BWT r, BWT i);

#ifdef __cplusplus
}
#endif

#endif /* _FPETV_H_ */
