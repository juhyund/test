#ifndef _PACAOLD_H_
#define _PACAOLD_H_

/** @defgroup PACAOLD PACA (Penta Cipher) legacy
 * @ingroup BCIPHER_ALG
 * @deprecated Use other block ciphers
 */

/** @file pacaold.h
    @ingroup PACAOLD
    @brief PACAOLD 알고리즘을 사용하기 위한 인터페이스

    이 모듈에서는 128bit PACAOLD만을 지원한다.
    따라서, 키와 블럭 크기가 모두 16바이트 이다.
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PACAOLD_KEY_SIZE    16
#define PACAOLD_BLOCK_SIZE  16

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} PacaOldDescriptor;

/** @ingroup PACAOLD */
LIBSPEC
extern PacaOldDescriptor pacaold;

/** @ingroup PACAOLD
 * @brief PACAOLD 알고리즘 descriptor
 * @deprecated Use other block ciphers
 */
#define PACAOLD &pacaold

typedef struct {
  BT32    q32[8];
  BT16    q16[16];
  BT16    roundKey[96];
} PacaOldKey;

#ifdef __cplusplus
}
#endif

#endif /* _PACAOLD_H_ */
