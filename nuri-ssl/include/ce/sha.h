#ifndef _SHA_H_
#define _SHA_H_

/** @defgroup SHA
 * @ingroup HASH_ALG
 */

/** @file sha.h
    @ingroup SHA
    @brief SHA�� ����ϱ� ���� �˰��� descriptor ����
*/

#include "cc_define.h"
#include "ce_dll.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup SHA
 * @{ */

#define SHA_DIGEST_SIZE 20

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} ShaDescriptor;

LIBSPEC_CE
extern ShaDescriptor sha;

/** @brief SHA �˰��� descriptor
 * @deprecated
 */
#define SHA &sha

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _SHA_H_ */
