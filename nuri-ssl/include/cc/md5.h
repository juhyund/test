#ifndef _MD5_H_
#define _MD5_H_

/** @defgroup MD5 MD5
 * @ingroup HASH_ALG
 */

/** @file md5.h
    @ingroup MD5
    @brief MD5를 사용하기 위한 알고리즘 descriptor 선언
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup MD5
 * @{ */

#define MD5_DIGEST_SIZE 16

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} Md5Descriptor;

LIBSPEC
extern Md5Descriptor popmd5;

/** @brief MD5 알고리즘 descriptor */
#define MD5 &popmd5

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MD5_H_ */
