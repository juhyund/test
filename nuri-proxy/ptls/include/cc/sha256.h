#ifndef _SHA256_H_
#define _SHA256_H_

/** @file sha256.h
    @ingroup SHA2
    @brief SHA-256을 사용하기 위한 알고리즘 descriptor 선언
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/* HASH Size Specification */
#define SHA256_DIGEST_SIZE      32
#define SHA256_DIGEST_BT32_SIZE  8

/** @addtogroup SHA2
 * @{ */

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} Sha256Descriptor;

LIBSPEC
extern Sha256Descriptor pcis_sha256;

/** @brief SHA256 알고리즘 descriptor */
#define SHA256 &pcis_sha256

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _SHA256_H_ */
