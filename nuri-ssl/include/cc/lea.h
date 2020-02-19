#ifndef _PCIS_LEA_H_
#define _PCIS_LEA_H_

/** @defgroup LEA LEA
 * @ingroup BCIPHER_ALG
 * @brief LEA (Lightweight Encryption Algorithm)
 *
 * 128-bit block cipher LEA(Lightweight Encryption Algorithm) by NSRI.
 * Block size 128 bits. Key size 128, 192, or 256 bits.
 */

/** @file
 * @ingroup LEA
 * @brief LEA interface
 */

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PCIS_LEA_ROUND_KEY_SIZE 24
#define PCIS_LEA_MAX_ROUND 32
#define PCIS_LEA_BLOCK_SIZE 16

typedef struct {
	BWT     blockLen;
	BWT     rKeySize;
	void  (*keyFunc)();
	void  (*encFunc)();
	void  (*decFunc)();
	BWT   (*apadFunc)();
	BWT   (*rpadFunc)();
} PCIS_LEA_Descriptor;

/** @addtogroup LEA
 * @{ */
LIBSPEC
extern PCIS_LEA_Descriptor pcis_lea_128;

LIBSPEC
extern PCIS_LEA_Descriptor pcis_lea_192;

LIBSPEC
extern PCIS_LEA_Descriptor pcis_lea_256;

/** alias to LEA128 */
#define LEA (&pcis_lea_128)
/** LEA-128 descriptor */
#define LEA128 (&pcis_lea_128)
/** LEA-192 descriptor */
#define LEA192 (&pcis_lea_192)
/** LEA-256 descriptor */
#define LEA256 (&pcis_lea_256)
/** @} */

typedef struct {
	/** encryption round key */
	BYTE eRoundKey[PCIS_LEA_ROUND_KEY_SIZE*PCIS_LEA_MAX_ROUND];
	/** decryption round key */
	BYTE dRoundKey[PCIS_LEA_ROUND_KEY_SIZE*PCIS_LEA_MAX_ROUND];
} PCIS_LEA_Key;

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_LEA_H_ */
