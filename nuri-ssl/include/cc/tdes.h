#ifndef _TDES_H_
#define _TDES_H_

/** @defgroup TDES Triple-DES
 * @ingroup BCIPHER_ALG
 */

/** @file tdes.h
    @ingroup TDES
    @brief Triple DES �˰����� ����ϱ� ���� �������̽�
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TDES_KEY_SIZE    24
#define TDES_BLOCK_SIZE   8

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} TDesDescriptor;

/** @ingroup TDES */
LIBSPEC
extern TDesDescriptor pcis_tdes;

/** @ingroup TDES
 * @brief Triple DES �˰��� descriptor */
#define TDES &pcis_tdes

typedef struct {
  BYTE    roundKey[384]; /**< subkey�� ������ ���� */
} TDesKey;

#ifdef __cplusplus
}
#endif

#endif /* _TDES_H_ */
