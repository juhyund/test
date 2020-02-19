#ifndef _ARIA_192_H_
#define _ARIA_192_H_

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
    @brief ARIA 알고리즘 descriptor인 aria 전역변수의 주소값을 rename
*/
#define ARIA192 &pcis_aria192

typedef struct {
  BT32 eRoundKey[4*(ARIA192_NR+1)]; /**< 암호화용 subkey를 저장할 버퍼 */
  BT32 dRoundKey[4*(ARIA192_NR+1)]; /**< 복호화용 subkey를 저장할 버퍼 */
} Aria192Key;

#ifdef __cplusplus
}
#endif

#endif /* _ARIA_H_ */
