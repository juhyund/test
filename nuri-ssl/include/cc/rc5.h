#ifndef _RC5_H_
#define _RC5_H_

/** @defgroup RC5 RC5
 * @ingroup BCIPHER_ALG
 */

/** @file rc5.h
    @ingroup RC5
    @brief RC5 알고리즘을 사용하기 위한 인터페이스
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RC5_MAX_KEY_SIZE  256  /* 0 - 256 bytes */
#define RC5_BLOCK_SIZE    8    /* fixed */
#define RC5_ROUND_NUM     12   /* 8, 12, 16 rounds*/

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} Rc5Descriptor;

/** @ingroup RC5 */
LIBSPEC
extern Rc5Descriptor pcis_rc5;

/** @ingroup RC5
 * @brief RC5 알고리즘 descriptor */
#define RC5 &pcis_rc5

typedef struct {
  BT32 roundKey[2*(RC5_ROUND_NUM+1)]; /**< subkey를 저장할 버퍼 */
} Rc5Key;

#ifdef __cplusplus
}
#endif

#endif /* _RC5_H_ */
