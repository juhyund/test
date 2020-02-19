#ifndef _PACA_H_
#define _PACA_H_

/** @defgroup PACA PACA (Penta Cipher)
 * @ingroup BCIPHER_ALG
 * @deprecated Use other block ciphers
 */

/** @file paca.h
    @ingroup PACA
    @brief PACA �˰����� ����ϱ� ���� �������̽�

    �� ��⿡���� 128bit PACA���� �����Ѵ�.
    ����, Ű�� �� ũ�Ⱑ ��� 16����Ʈ �̴�.
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PACA_KEY_SIZE    16
#define PACA_BLOCK_SIZE  16

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} PacaDescriptor;

/** @ingroup PACA */
LIBSPEC
extern PacaDescriptor paca;

/** @ingroup PACA
 * @brief PACA �˰��� descriptor
 * @deprecated Use other block ciphers
 */
#define PACA &paca

typedef struct {
  BT32    q32[8]; /**< Q32 constant�� ������ ���� */
  BT16    q16[16]; /**< Q16 constant�� ������ ���� */
  BT16    roundKey[96]; /**< subkey�� ������ ���� */
} PacaKey;

#ifdef __cplusplus
}
#endif

#endif /* _PACA_H_ */
