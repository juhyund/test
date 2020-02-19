#ifndef _BLOWFISH_H_
#define _BLOWFISH_H_

/** @defgroup BLOWFISH BlowFish 
 * @ingroup BCIPHER_ALG
 */

/** @file blowfish.h
 * @ingroup BLOWFISH
 * @brief BLOWFISH �˰����� ����ϱ� ���� �������̽�
 */

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLOWFISH_MAX_KEY_SIZE  56
#define BLOWFISH_BLOCK_SIZE     8

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} BlowfishDescriptor;

/** @ingroup BLOWFISH */
LIBSPEC
extern BlowfishDescriptor pcis_blowfish;

/** @ingroup BLOWFISH
 * @brief BLOWFISH �˰��� descriptor */
#define BLOWFISH &pcis_blowfish

typedef struct {
  BT32    roundKey[18]; /**< subkey�� ������ ���� */
  BT32    sBox[1024]; /**< sbox�� ������ ���� */
} BlowfishKey;

#ifdef __cplusplus
}
#endif

#endif /* _BLOWFISH_H_ */
