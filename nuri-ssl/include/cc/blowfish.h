#ifndef _BLOWFISH_H_
#define _BLOWFISH_H_

/** @defgroup BLOWFISH BlowFish 
 * @ingroup BCIPHER_ALG
 */

/** @file blowfish.h
 * @ingroup BLOWFISH
 * @brief BLOWFISH 알고리즘을 사용하기 위한 인터페이스
 */

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLOWFISH_MAX_KEY_SIZE  56
#define BLOWFISH_BLOCK_SIZE     8

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} BlowfishDescriptor;

/** @ingroup BLOWFISH */
LIBSPEC
extern BlowfishDescriptor pcis_blowfish;

/** @ingroup BLOWFISH
 * @brief BLOWFISH 알고리즘 descriptor */
#define BLOWFISH &pcis_blowfish

typedef struct {
  BT32    roundKey[18]; /**< subkey를 저장할 버퍼 */
  BT32    sBox[1024]; /**< sbox를 저장할 버퍼 */
} BlowfishKey;

#ifdef __cplusplus
}
#endif

#endif /* _BLOWFISH_H_ */
