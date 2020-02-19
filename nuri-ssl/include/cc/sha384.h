#ifndef _SHA384_H_
#define _SHA384_H_

/** @file sha384.h
    @ingroup SHA2
    @brief SHA-384�� ����ϱ� ���� �˰��� descriptor ����
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/* HASH Size Specification */
#define SHA384_DIGEST_SIZE      48
#define SHA384_DIGEST_BT64_SIZE  6

/** @addtogroup SHA2
 * @{ */

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} Sha384Descriptor;

LIBSPEC
extern Sha384Descriptor pcis_sha384;

/** @brief SHA384 �˰��� descriptor */
#define SHA384 &pcis_sha384

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _SHA384_H_ */
