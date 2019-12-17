#ifndef _MD2_H_
#define _MD2_H_

/** @defgroup MD2 MD2
 * @ingroup HASH_ALG
 */

/** @file md2.h
    @ingroup MD2
    @brief MD2를 사용하기 위한 인터페이스 선언

    MD2 알고리즘은 hash_op.h의 인퍼에이스를 사용할 수도 있으며,
    다른 알고리즘과는 달리 이 헤더의 인터페이스를 사용할 수도 있다.
*/

#include "cc_define.h"

#ifdef  __cplusplus
extern "C" {
#endif

/** @addtogroup MD2
 * @{ */

#define MD2_DIGEST_SIZE  16 /* 128 비트 = 16 * 8 */
#define MD2_BLOCK_NUMBER 16 

typedef struct {
  BWT    digestLen;
  void (*initFunc)();
  void (*compressFunc)();
  void (*padFunc)();
  void (*dumpFunc)();
} Md2Descriptor;

LIBSPEC
extern Md2Descriptor pcis_md2;

/** @brief MD2 알고리즘 descriptor */
#define MD2 &pcis_md2

/** @} */

#ifdef  __cplusplus
}
#endif

#endif /* _MD2_H_ */
