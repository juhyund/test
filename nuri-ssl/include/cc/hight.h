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
 * @note TTA ǥ�� �������� byte order�� ȥ���ϱ� ���� ���� �ִ�. �ٸ� ������
 * ã�� ���� ��� ����� ������ ����. ǥ�� ������ ������ byte sequence�� P3 ||
 * P2 || P1 || P0���� ǥ���ϰ� �ִ�. ���⿡�� P3�� ���� ù��° byte�� �� ����
 * �ְ� index�� ���� ���� P0�� ���� ù��° byte�� �� ���� �ִ�. �ΰ��� �����
 * ���� �ٸ� ����� ����. ���� ������ P0�� ���� ù��° byte�� ���� �ִ�. �̴�
 * KISA���� �����ϴ� HIGHT �ҽ� �ڵ带 �������� �� ���̴�. ����, ǥ�� ������
 * ������������ ������ ó���� ��� �Ѵ�. ǥ�� ������ test vector�� ff ee dd
 * cc��� ���� �ִٸ� ���⿡�� ff�� P3�� �ǰ� cc�� P0�� �ǰ� P0�� cc�� ù��°
 * byte�̴�. C �ڵ�� ��Ÿ���ڸ� unsigned char text = {0xcc, 0xdd, 0xee,
 * 0xff}�� �ȴ�.
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
