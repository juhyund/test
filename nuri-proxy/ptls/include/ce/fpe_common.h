#ifndef _FPE_COMMON_H_
#define _FPE_COMMON_H_

#include "pe_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ER_FPE_INVALID_ALG -1601
#define ER_FPE_NULL_PARAM -1602
#define ER_FPE_NULL_KEY -1603
#define ER_FPE_INVALID_RADIX -1604
#define ER_FPE_INVALID_X_LENGTH -1605
#define ER_FPE_INVALID_Y_LENGTH -1606
#define ER_FPE_INVALID_Y_SIZE -1607
#define ER_FPE_INVALID_ADDITION -1608

typedef struct {
	BWT (*F)();
	BWT (*ADDF)();
	BWT (*SUBF)();
	BWT (*FSE)(); //
	BWT (*FSD)();
} FpeAlgorithmDescriptor;

typedef struct {
	BWT (*INIT)();
	BWT (*FSE)(); //
	BWT (*FSD)();
	BWT (*F)();
} FpeAlgDescriptor;

#ifdef __cplusplus
}
#endif

#endif /* _FPE_COMMON_H_ */
