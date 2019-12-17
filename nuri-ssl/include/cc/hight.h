/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_HIGHT_H_
#define _PCIS_HIGHT_H_

/** @defgroup HIGHT HIGHT
 * @ingroup BCIPHER_ALG
 * @brief HIGHT (High Security and Lightweight)
 *
 * 64-bit block cipher HIGHT.
 * Block size 64 bits. Key size 128 bits.
 *
 * @note TTA 표준 문서에는 byte order가 혼동하기 쉽게 적혀 있다. 다른 논문들을
 * 찾아 봐도 기술 방법이 완전히 같다. 표준 문서에 따르면 byte sequence를 P3 ||
 * P2 || P1 || P0으로 표현하고 있다. 여기에서 P3를 실제 첫번째 byte로 볼 수도
 * 있고 index가 가장 작은 P0를 실제 첫번째 byte로 볼 수도 있다. 두가지 방법이
 * 전혀 다른 결과를 낸다. 현재 구현은 P0를 실제 첫번째 byte로 보고 있다. 이는
 * KISA에서 배포하는 HIGHT 소스 코드를 기준으로 한 것이다. 따라서, 표준 문서의
 * 참조구현값도 적절히 처리해 줘야 한다. 표준 문서의 test vector에 ff ee dd
 * cc라고 적혀 있다면 여기에서 ff가 P3가 되고 cc가 P0가 되고 P0인 cc가 첫번째
 * byte이다. C 코드로 나타내자면 unsigned char text = {0xcc, 0xdd, 0xee,
 * 0xff}가 된다.
 */

/** @file
 * @ingroup HIGHT
 * @brief HIGHT interface
 */

#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PCIS_HIGHT_ROUND_KEY_SIZE 4
#define PCIS_HIGHT_MAX_ROUND 32
#define PCIS_HIGHT_BLOCK_SIZE 8

typedef struct {
	BWT     blockLen;
	BWT     rKeySize;
	void  (*keyFunc)();
	void  (*encFunc)();
	void  (*decFunc)();
	BWT   (*apadFunc)();
	BWT   (*rpadFunc)();
} PCIS_HIGHT_Descriptor;

/** @ingroup HIGHT */
LIBSPEC
extern PCIS_HIGHT_Descriptor pcis_hight;

/** @ingroup HIGHT
 * alias to HIGHT descriptor */
#define HIGHT (&pcis_hight)

typedef struct {
	/** encryption whitening key */
	BYTE ewKey[PCIS_HIGHT_ROUND_KEY_SIZE*2];
	/** encryption sub key */
	BYTE esKey[PCIS_HIGHT_ROUND_KEY_SIZE*PCIS_HIGHT_MAX_ROUND];
	/** decryption whitening key */
	BYTE dwKey[PCIS_HIGHT_ROUND_KEY_SIZE*2];
	/** decryption sub key */
	BYTE dsKey[PCIS_HIGHT_ROUND_KEY_SIZE*PCIS_HIGHT_MAX_ROUND];
} PCIS_HIGHT_Key;

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_HIGHT_H_ */
