/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_CC_COMPAT_H_
#define _PCIS_CC_COMPAT_H_

#include "ce_dll.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 운영환경의 CPU가 AES-NI를 지원하는지 여부를 확인한다.
 * @retval nonzero 지원
 * @retval 0 미지원
 */
LIBSPEC_CE
int Check_CPU_support_AES(void);

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_CC_COMPAT_H_ */
