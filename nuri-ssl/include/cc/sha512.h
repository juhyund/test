#ifndef _SHA512_H_
#define _SHA512_H_

/** @file sha512.h
    @ingroup SHA2
    @brief SHA-512을 사용하기 위한 알고리즘 descriptor 선언
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/* HASH Size Specification */
#define SHA512_DIGEST_SIZE      64
#define SHA512_DIGEST_BT64_SIZE  8

/** @addtogroup SHA2
 * @{ */

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} Sha512Descriptor;

LIBSPEC
extern Sha512Descriptor pcis_sha512;

/** @brief SHA512 알고리즘 descriptor */
#define SHA512 &pcis_sha512

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _SHA512_H_ */
