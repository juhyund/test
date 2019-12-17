#ifndef _IDEA_H_
#define _IDEA_H_

/** @defgroup IDEA IDEA
 * @ingroup BCIPHER_ALG
 */

/** @file idea.h
    @ingroup IDEA
    @brief IDEA �˰����� ����ϱ� ���� �������̽�
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IDEA_KEY_SIZE    16
#define IDEA_BLOCK_SIZE   8

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} IdeaDescriptor;

/** @ingroup IDEA */
LIBSPEC
extern IdeaDescriptor pcis_idea;

/** @ingroup IDEA
 * @brief IDEA �˰��� descriptor */
#define IDEA &pcis_idea

typedef struct {
  BT16    eRoundKey[56]; /**< ��ȣȭ�� subkey�� ������ ���� */
  BT16    dRoundKey[56]; /**< ��ȣȭ�� subkey�� ������ ���� */
} IdeaKey;

#ifdef __cplusplus
}
#endif

#endif /* _IDEA_H_ */
