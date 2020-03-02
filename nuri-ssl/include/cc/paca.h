#ifndef _PACA_H_
#define _PACA_H_

/** @defgroup PACA PACA (Penta Cipher)
 * @ingroup BCIPHER_ALG
 * @deprecated Use other block ciphers
 */

/** @file paca.h
    @ingroup PACA
    @brief PACA 알고리즘을 사용하기 위한 인터페이스

    이 모듈에서는 128bit PACA만을 지원한다.
    따라서, 키와 블럭 크기가 모두 16바이트 이다.
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PACA_KEY_SIZE    16
#define PACA_BLOCK_SIZE  16

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} PacaDescriptor;

/** @ingroup PACA */
LIBSPEC
extern PacaDescriptor paca;

/** @ingroup PACA
 * @brief PACA 알고리즘 descriptor
 * @deprecated Use other block ciphers
 */
#define PACA &paca

typedef struct {
  BT32    q32[8]; /**< Q32 constant를 저장할 버퍼 */
  BT16    q16[16]; /**< Q16 constant를 저장할 버퍼 */
  BT16    roundKey[96]; /**< subkey를 저장할 버퍼 */
} PacaKey;

#ifdef __cplusplus
}
#endif

#endif /* _PACA_H_ */
