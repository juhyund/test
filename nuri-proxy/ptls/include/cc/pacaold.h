#ifndef _PACAOLD_H_
#define _PACAOLD_H_

/** @defgroup PACAOLD PACA (Penta Cipher) legacy
 * @ingroup BCIPHER_ALG
 * @deprecated Use other block ciphers
 */

/** @file pacaold.h
    @ingroup PACAOLD
    @brief PACAOLD �˰����� ����ϱ� ���� �������̽�

    �� ��⿡���� 128bit PACAOLD���� �����Ѵ�.
    ����, Ű�� �� ũ�Ⱑ ��� 16����Ʈ �̴�.
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PACAOLD_KEY_SIZE    16
#define PACAOLD_BLOCK_SIZE  16

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} PacaOldDescriptor;

/** @ingroup PACAOLD */
LIBSPEC
extern PacaOldDescriptor pacaold;

/** @ingroup PACAOLD
 * @brief PACAOLD �˰��� descriptor
 * @deprecated Use other block ciphers
 */
#define PACAOLD &pacaold

typedef struct {
  BT32    q32[8];
  BT16    q16[16];
  BT16    roundKey[96];
} PacaOldKey;

#ifdef __cplusplus
}
#endif

#endif /* _PACAOLD_H_ */
