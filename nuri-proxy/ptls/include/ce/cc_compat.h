/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_CC_COMPAT_H_
#define _PCIS_CC_COMPAT_H_

#include "ce_dll.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief �ȯ���� CPU�� AES-NI�� �����ϴ��� ���θ� Ȯ���Ѵ�.
 * @retval nonzero ����
 * @retval 0 ������
 */
LIBSPEC_CE
int Check_CPU_support_AES(void);

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_CC_COMPAT_H_ */
