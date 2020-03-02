#ifndef _ARIA_192_H_
#define _ARIA_192_H_

/** @file
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

#define ARIA192_MAX_KEY_SIZE 24

#define ARIA192_KEY_SIZE    24
#define ARIA192_BLOCK_SIZE  16

/* ARIA_NK : Key size in BT32
   ARIA192_NR : Number of rounds */


#define ARIA192_NK (ARIA192_KEY_SIZE/4)

#if (ARIA192_NK == 4)
  #define ARIA192_NR 12
#elif (ARIA192_NK == 6)
  #define ARIA192_NR 14
#else
  #define ARIA192_NR 16
#endif

/* Round Key size */
#define ARIA192_NRK (ARIA192_BLOCK_SIZE*(ARIA192_NR+1))

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} Aria192Descriptor;

/** @ingroup ARIA */
LIBSPEC
extern Aria192Descriptor pcis_aria192;

/**
    @ingroup ARIA
    @brief ARIA �˰��� descriptor�� aria ���������� �ּҰ��� rename
*/
#define ARIA192 &pcis_aria192

typedef struct {
  BT32 eRoundKey[4*(ARIA192_NR+1)]; /**< ��ȣȭ�� subkey�� ������ ���� */
  BT32 dRoundKey[4*(ARIA192_NR+1)]; /**< ��ȣȭ�� subkey�� ������ ���� */
} Aria192Key;

#ifdef __cplusplus
}
#endif

#endif /* _ARIA_H_ */
