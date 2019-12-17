#ifndef _IDEA_H_
#define _IDEA_H_

/** @defgroup IDEA IDEA
 * @ingroup BCIPHER_ALG
 */

/** @file idea.h
    @ingroup IDEA
    @brief IDEA 알고리즘을 사용하기 위한 인터페이스
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
 * @brief IDEA 알고리즘 descriptor */
#define IDEA &pcis_idea

typedef struct {
  BT16    eRoundKey[56]; /**< 암호화용 subkey를 저장할 버퍼 */
  BT16    dRoundKey[56]; /**< 복호화용 subkey를 저장할 버퍼 */
} IdeaKey;

#ifdef __cplusplus
}
#endif

#endif /* _IDEA_H_ */
