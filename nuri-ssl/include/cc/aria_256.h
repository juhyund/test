#ifndef _ARIA_256_H_
#define _ARIA_256_H_

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

#define ARIA256_MAX_KEY_SIZE 32

#define ARIA256_KEY_SIZE    32
#define ARIA256_BLOCK_SIZE  16

/* ARIA_NK : Key size in BT32
   ARIA256_NR : Number of rounds */


#define ARIA256_NK (ARIA256_KEY_SIZE/4)

#if (ARIA256_NK == 4)
  #define ARIA256_NR 12
#elif (ARIA256_NK == 6)
  #define ARIA256_NR 14
#else
  #define ARIA256_NR 16
#endif

/* Round Key size */
#define ARIA256_NRK (ARIA256_BLOCK_SIZE*(ARIA256_NR+1))

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} Aria256Descriptor;

/** @ingroup ARIA */
LIBSPEC
extern Aria256Descriptor pcis_aria256;

/**
    @ingroup ARIA
    @brief ARIA �˰��� descriptor�� aria ���������� �ּҰ��� rename
*/
#define ARIA256 &pcis_aria256

typedef struct {
  BT32 eRoundKey[4*(ARIA256_NR+1)]; /**< ��ȣȭ�� subkey�� ������ ���� */
  BT32 dRoundKey[4*(ARIA256_NR+1)]; /**< ��ȣȭ�� subkey�� ������ ���� */
} Aria256Key;

#ifdef __cplusplus
}
#endif

#endif /* _ARIA_H_ */
