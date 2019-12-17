#ifndef _SHA1_H_
#define _SHA1_H_

/** @defgroup SHA1 SHA1
 * @ingroup HASH_ALG
 */

/** @file sha1.h
    @ingroup SHA1
    @brief SHA-1을 사용하기 위한 알고리즘 descriptor 선언
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup SHA1
 * @{ */

#define SHA1_DIGEST_SIZE      20
#define SHA1_DIGEST_BT32_SIZE 5

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} Sha1Descriptor;

LIBSPEC
extern Sha1Descriptor popsha1;

/** @brief SHA1 알고리즘 descriptor */
#define SHA1 &popsha1

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _SHA1_H_ */
