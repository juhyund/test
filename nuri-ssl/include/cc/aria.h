#ifndef _ARIA_H_
#define _ARIA_H_

/** @defgroup ARIA ARIA
 * @ingroup BCIPHER_ALG
 * @brief ARIA block cipher
 */

/** @file aria.h
    @ingroup ARIA
    @brief ARIA �˰����� ����ϱ� ���� �������̽�

    @note ����� ARIA_EncryptBlock, ARIA_DecryptBlock�� 32bit�� ����ȭ�Ǿ� �����Ǿ�
          �ֱ� ������ 8bit, 16bit �ӽſ����� ����� �������� �ʴ´�.
          8bit or 16bit machine���� ���� �ʿ䰡 ���� ������ �ӵ��� �������� aria ��
          �� ������ �����ִ� 8bit ������ �����ϴ� ����� �״�� �����ϸ� �ȴ�.
*/

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ARIA_MAX_KEY_SIZE 32

#define ARIA_KEY_SIZE    16
#define ARIA_BLOCK_SIZE  16

/* ARIA_NK : Key size in BT32
   ARIA_NR : Number of rounds */

#define ARIA_NK (ARIA_KEY_SIZE/4)

#if (ARIA_NK == 4)
  #define ARIA_NR 12
#elif (ARIA_NK == 6)
  #define ARIA_NR 14
#else
  #define ARIA_NR 16
#endif

/* Round Key size */
#define ARIA_NRK (ARIA_BLOCK_SIZE*(ARIA_NR+1))

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} AriaDescriptor;

/** @ingroup ARIA */
LIBSPEC
extern AriaDescriptor pcis_aria;

/** @ingroup ARIA
 * @brief ARIA �˰��� descriptor */
/** alias to AES128 */
#define ARIA &pcis_aria
/** ARIA-128 descriptor */
#define ARIA128 &pcis_aria

typedef struct {
  BT32 eRoundKey[4*(ARIA_NR+1)]; /**< ��ȣȭ�� subkey�� ������ ���� */
  BT32 dRoundKey[4*(ARIA_NR+1)]; /**< ��ȣȭ�� subkey�� ������ ���� */
} AriaKey;

#ifdef __cplusplus
}
#endif

#endif /* _ARIA_H_ */
