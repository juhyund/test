#ifndef _ARIA_256_H_
#define _ARIA_256_H_

/** @file
    @ingroup ARIA
    @brief ARIA 알고리즘을 사용하기 위한 인터페이스
    
    @note 현재는 ARIA_EncryptBlock, ARIA_DecryptBlock이 32bit에 최적화되어 구현되어
          있기 때문에 8bit, 16bit 머신에서는 제대로 동작하지 않는다.
          8bit or 16bit machine에서 돌릴 필요가 있을 때에는 속도는 느리지만 aria 관
          련 문서에 적혀있는 8bit 단위로 동작하는 방법을 그대로 구현하면 된다.
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
    @brief ARIA 알고리즘 descriptor인 aria 전역변수의 주소값을 rename
*/
#define ARIA256 &pcis_aria256

typedef struct {
  BT32 eRoundKey[4*(ARIA256_NR+1)]; /**< 암호화용 subkey를 저장할 버퍼 */
  BT32 dRoundKey[4*(ARIA256_NR+1)]; /**< 복호화용 subkey를 저장할 버퍼 */
} Aria256Key;

#ifdef __cplusplus
}
#endif

#endif /* _ARIA_H_ */
