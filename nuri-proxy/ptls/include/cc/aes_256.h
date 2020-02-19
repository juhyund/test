#ifndef _AES256_H_
#define _AES256_H_

/** @file
 * @ingroup AES
 * @brief AES256 알고리즘을 사용하기 위한 인터페이스
 */

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AES256_MAX_KEY_SIZE    32
#define AES256_MAX_BLOCK_SIZE  32

#define AES256_BLOCK_SIZE      16 /* 16, 24, 32 */
#define AES256_KEY_SIZE        32 /* 16, 24, 32 */


/* NB : Block size in BT32
   AES256_NK : Key size in BT32
   AES256_NR : Number of rounds */

#define AES256_NB (AES256_BLOCK_SIZE/4)
#define AES256_NK (AES256_KEY_SIZE/4)

#if (AES256_NB == 4 && AES256_NK == 4)
  #define AES256_NR 10
#elif ((AES256_NB == 6 && AES256_NK != 8) || (AES256_NB != 8 && AES256_NK == 6))
  #define AES256_NR 12
#else
  #define AES256_NR 14
#endif

#define AES256_NRK (AES256_NB*(AES256_NR+1))

/* for backward-compatibility */
#define RIJNDAEL256_MAX_KEY_SIZE     AES256_MAX_KEY_SIZE
#define RIJNDAEL256_MAX_BLOCK_SIZE   AES256_MAX_BLOCK_SIZE
#define RIJNDAEL256_BLOCK_SIZE       AES256_BLOCK_SIZE
#define RIJNDAEL256_KEY_SIZE         AES256_KEY_SIZE
#define RIJNDAEL256_NB               AES256_NB
#define RIJNDAEL256_NK               AES256_NK
#define RIJNDAEL256_NR               AES256_NR
#define RIJNDAEL256_NRK              AES256_NRK

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} AES256Descriptor;

/** @ingroup AES */
LIBSPEC
extern AES256Descriptor pcis_aes256;

/** @ingroup AES
 * @brief AES256 알고리즘 descriptor */
#define AES256 &pcis_aes256
/* for backward-compatibility */
#define RIJNDAEL256 AES256

LIBSPEC
extern AES256Descriptor pcis_aesni256;

#define AESNI256 &pcis_aesni256

typedef struct {
  BT32 eRoundKey[AES256_NRK]; /**< 암호화용 subkey를 저장할 버퍼 */
  BT32 dRoundKey[AES256_NRK]; /**< 복호화용 subkey를 저장할 버퍼 */
} AES256Key;

#ifdef __cplusplus
}
#endif

#endif /* _AES256_H_ */
