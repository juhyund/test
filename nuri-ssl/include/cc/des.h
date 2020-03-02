#ifndef _DES_H_
#define _DES_H_

/** @defgroup DES
 * @ingroup BCIPHER_ALG
 * @brief DES (Data Encryption Standard)
 */

/** @file des.h
    @ingroup DES
    @brief DES �˰����� ����ϱ� ���� �������̽�
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DES_KEY_SIZE    8
#define DES_BLOCK_SIZE  8

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} DesDescriptor;

/** @ingroup DES */
LIBSPEC
extern DesDescriptor pcis_des;

/** @ingroup DES
 * @brief DES �˰��� descriptor */
#define DES &pcis_des

typedef struct {
  BYTE    roundKey[128]; /**< subkey�� ������ ���� */
} DesKey;

#ifdef __cplusplus
}
#endif

#endif /* _DES_H_ */
