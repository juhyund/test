#ifndef _HAS160_H_
#define _HAS160_H_

/** @defgroup HAS160 HAS160
 * @ingroup HASH_ALG
 */

/** @file has160.h
    @ingroup HAS160
    @brief HAS160을 사용하기 위한 알고리즘 descriptor 선언
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup HAS160
 * @{ */

#define HAS160_DIGEST_SIZE 20

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} Has160Descriptor;

LIBSPEC
extern Has160Descriptor pophas160;

/** @brief HAS160 알고리즘 descriptor */
#define HAS160 &pophas160

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _HAS160_H_ */
