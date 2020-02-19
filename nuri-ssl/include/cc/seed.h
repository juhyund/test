#ifndef _SEED_H_
#define _SEED_H_

/** @defgroup SEED SEED
 * @ingroup BCIPHER_ALG
 */

/** @file seed.h
    @ingroup SEED
    @brief SEED 알고리즘을 사용하기 위한 인터페이스
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SEED_KEY_SIZE    16
#define SEED_BLOCK_SIZE  16

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} SeedDescriptor;

/** @ingroup SEED */
LIBSPEC
extern SeedDescriptor pcis_seed;

/** @ingroup SEED
 * @brief SEED 알고리즘 descriptor */
#define SEED &pcis_seed

typedef struct {
  BT32    roundKey[32]; /**< subkey를 저장할 버퍼 */
} SeedKey;

#ifdef __cplusplus
}
#endif

#endif /* _SEED_H_ */
