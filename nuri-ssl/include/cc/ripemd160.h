#ifndef _RIPEMD160_H_
#define _RIPEMD160_H_

/** @defgroup RIPEMD160 RIPEMD-160
 * @ingroup HASH_ALG
 */

/** @file ripemd160.h
    @ingroup RIPEMD160
    @brief RIPEMD160을 사용하기 위한 알고리즘 descriptor 선언
*/

#include "cc_define.h"

#ifdef  __cplusplus
extern "C" {
#endif

/** @addtogroup RIPEMD160
 * @{ */

#define RIPEMD160_DIGEST_SIZE 20

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} Ripemd160Descriptor;

LIBSPEC
extern Ripemd160Descriptor pcis_ripemd160;

/** @brief RIPEMD160 알고리즘 descriptor */
#define RIPEMD160 &pcis_ripemd160

/** @} */

#ifdef  __cplusplus
}
#endif

#endif /* _RIPEMD160_H_ */
