#ifndef _RC2_H_
#define _RC2_H_

/** @defgroup RC2 RC2
 * @ingroup BCIPHER_ALG
 */

/** @file rc2.h
    @ingroup RC2
    @brief RC2 알고리즘을 사용하기 위한 인터페이스
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RC2_MAX_KEY_SIZE  128  /* 1 - 128 bytes */
#define RC2_BLOCK_SIZE    8    /* fixed */

#define RC2_EFF_KEY_LEN(len) (len<<16)

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} Rc2Descriptor;

/** @ingroup RC2 */
LIBSPEC
extern Rc2Descriptor pcis_rc2;

/** @ingroup RC2
 * @brief RC2 알고리즘 descriptor */
#define RC2 &pcis_rc2

typedef struct {
  BYTE roundKey[RC2_MAX_KEY_SIZE]; /**< subkey를 저장할 버퍼 */
} Rc2Key;

#ifdef __cplusplus
}
#endif

#endif /* _RC2_H_ */
