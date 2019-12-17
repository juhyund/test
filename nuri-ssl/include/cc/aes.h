/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _AES_H_
#define _AES_H_

/** @defgroup AES AES
 * @ingroup BCIPHER_ALG
 * @brief AES (Advanced Encryption Standard)
 */

/** @file
 * @ingroup AES
 * @brief AES 알고리즘을 사용하기 위한 인터페이스
 */

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AES_MAX_KEY_SIZE    32
#define AES_MAX_BLOCK_SIZE  32

#define AES_BLOCK_SIZE      16 /* 16, 24, 32 */
#define AES_KEY_SIZE        16 /* 16, 24, 32 */


/* NB : Block size in BT32
   AES_NK : Key size in BT32
   AES_NR : Number of rounds */

#define AES_NB (AES_BLOCK_SIZE/4)
#define AES_NK (AES_KEY_SIZE/4)

#if (AES_NB == 4 && AES_NK == 4)
  #define AES_NR 10
#elif ((AES_NB == 6 && AES_NK != 8) || (AES_NB != 8 && AES_NK == 6))
  #define AES_NR 12
#else
  #define AES_NR 14
#endif

#define AES_NRK (AES_NB*(AES_NR+1))

/* for backward-compatibility */
#define RIJNDAEL_MAX_KEY_SIZE    AES_MAX_KEY_SIZE
#define RIJNDAEL_MAX_BLOCK_SIZE  AES_MAX_BLOCK_SIZE
#define RIJNDAEL_BLOCK_SIZE      AES_BLOCK_SIZE
#define RIJNDAEL_KEY_SIZE        AES_KEY_SIZE
#define RIJNDAEL_NB              AES_NB
#define RIJNDAEL_NK              AES_NK
#define RIJNDAEL_NR              AES_NR
#define RIJNDAEL_NRK             AES_NRK

typedef struct {
  BWT     blockLen;
  BWT     rKeySize;
  void  (*keyFunc)();
  void  (*encFunc)();
  void  (*decFunc)();
  BWT   (*apadFunc)();
  BWT   (*rpadFunc)();
} AESDescriptor;

/** @ingroup AES */
LIBSPEC
extern AESDescriptor pcis_aes;

/** @ingroup AES
 * @brief AES 알고리즘 descriptor */
/** alias to AES128 */
#define AES &pcis_aes
/** AES-128 descriptor */
#define AES128 &pcis_aes
/* for backward-compatibility */
#define RIJNDAEL AES128

LIBSPEC
extern AESDescriptor pcis_aesni;

#define AESNI &pcis_aesni

typedef struct {
  BT32 eRoundKey[AES_NRK]; /**< 암호화용 subkey를 저장할 버퍼 */
  BT32 dRoundKey[AES_NRK]; /**< 복호화용 subkey를 저장할 버퍼 */
} AESKey;

#ifdef __cplusplus
}
#endif

#endif /* _AES_H_ */
