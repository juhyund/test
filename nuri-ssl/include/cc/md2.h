#ifndef _MD2_H_
#define _MD2_H_

/** @defgroup MD2 MD2
 * @ingroup HASH_ALG
 */

/** @file md2.h
    @ingroup MD2
    @brief MD2�� ����ϱ� ���� �������̽� ����

    MD2 �˰����� hash_op.h�� ���ۿ��̽��� ����� ���� ������,
    �ٸ� �˰������ �޸� �� ����� �������̽��� ����� ���� �ִ�.
*/

#include "cc_define.h"

#ifdef  __cplusplus
extern "C" {
#endif

/** @addtogroup MD2
 * @{ */

#define MD2_DIGEST_SIZE  16 /* 128 ��Ʈ = 16 * 8 */
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

/** @brief MD2 �˰��� descriptor */
#define MD2 &pcis_md2

/** @} */

#ifdef  __cplusplus
}
#endif

#endif /* _MD2_H_ */
