#ifndef _RC4_H
#define _RC4_H

/** @defgroup SCIPHER Stream Cipher
 * @ingroup CC
 * @brief Stream Cipher
 */

/** @defgroup RC4 RC4
 * @ingroup SCIPHER
 * RC4 stream cipher
 */

/** @file
 * @ingroup RC4
 */

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup RC4
 * @{ */

typedef struct _rc4context{
  BYTE sbox[256]; /**< rc4 permuatation array */
  int i; /**< index pointer i*/
  int j; /**< index pointer j*/
} RC4_CTX;

/** @brief RC4 context�� �����Ͽ� �ʱ�ȭ�Ѵ�. */
LIBSPEC
void RC4_init(
		RC4_CTX *context, /**< [out] RC4 context */
		const void *key, /**< [in] ���Ű */
		int keylen /**< [in] ���Ű�� ��Ʈ ���� */
		);

/** @brief RC4 ��ȣȭ�� �����Ѵ�. */
LIBSPEC
void RC4_crypt(
		void *output, /**< [out] ��� ��*/
		const void *input, /**< [in] �Է� �� */
		int len, /**< [in] �Է� ���� ����Ʈ ���� */
		RC4_CTX *context /**< [in,out] RC4 context */
		);

/**< @brief RC4 ��ȣȭ �Լ� */
#define RC4_encrypt(a,b,c,d) RC4_crypt((a),(b),(c),(d))
/**< @brief RC4 ��ȣȭ �Լ� */
#define RC4_decrypt(a,b,c,d) RC4_crypt((a),(b),(c),(d))

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _RC4_H */
