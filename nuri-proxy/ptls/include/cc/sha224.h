#ifndef _SHA224_H_
#define _SHA224_H_

/** @defgroup SHA2 SHA2 family
 * @ingroup HASH_ALG
 */

/** @file sha224.h
    @ingroup SHA2
    @brief SHA-224를 사용하기 위한 알고리즘 descriptor 선언
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/* HASH Size Specification */
#define SHA224_DIGEST_SIZE      28
#define SHA224_DIGEST_BT32_SIZE  7

/** @addtogroup SHA2
 * @{ */

typedef struct {
  BWT  digestLen ;
  void (*initFunc)() ;
  void (*compressFunc)() ;
  void (*padFunc)() ;
  void (*dumpFunc)() ;
} Sha224Descriptor ;

LIBSPEC
extern Sha224Descriptor pcis_sha224;

/** @brief SHA224 알고리즘 descriptor */
#define SHA224 &pcis_sha224

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _SHA224_H_ */
