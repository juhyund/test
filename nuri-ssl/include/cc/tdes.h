#ifndef _TDES_H_
#define _TDES_H_

/** @defgroup TDES Triple-DES
 * @ingroup BCIPHER_ALG
 */

/** @file tdes.h
    @ingroup TDES
    @brief Triple DES 알고리즘을 사용하기 위한 인터페이스
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
 * @brief Triple DES 알고리즘 descriptor */
#define TDES &pcis_tdes

typedef struct {
  BYTE    roundKey[384]; /**< subkey를 저장할 버퍼 */
} TDesKey;

#ifdef __cplusplus
}
#endif

#endif /* _TDES_H_ */
