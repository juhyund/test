#ifndef _CAST128_H_
#define _CAST128_H_

/** @defgroup CAST128 CAST128
 * @ingroup BCIPHER_ALG
 */

/** @file cast128.h
    @ingroup CAST128
    @brief CAST128 알고리즘을 사용하기 위한 인터페이스
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CAST128_KEY_SIZE    16
#define CAST128_BLOCK_SIZE  8

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} Cast128Descriptor;

/** @ingroup CAST128 */
LIBSPEC
extern Cast128Descriptor pcis_cast128;

/** @ingroup CAST128
 * @brief CAST128 알고리즘 descriptor */
#define CAST128 &pcis_cast128

typedef struct {
  BT32    roundKey[32]; /**< subkey를 저장할 버퍼 */
} Cast128Key;

#ifdef __cplusplus
}
#endif

#endif /* _CAST128_H_ */
