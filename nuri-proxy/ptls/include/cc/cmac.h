#ifndef _CMAC_H_
#define _CMAC_H_

/** @file
 * @ingroup MAC
 * CMAC을 운영하기 위한 인터페이스
 */

#include "cc_define.h"
#include "bcipher_op.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CMAC_Initialize PCIS_CMAC_Initialize
#define CMAC_Update PCIS_CMAC_Update
#define CMAC_Finalize PCIS_CMAC_Finalize

/** @addtogroup MAC
 * @{ */

typedef struct {
	BWT index; /**< 업데이트된 평문 블록 개수 */
	BYTE input[BCIPHER_MAX_BLOCK_SIZE]; /**< 평문 한 블록 */
	BYTE cipher[BCIPHER_MAX_BLOCK_SIZE]; /**< 암호문 한 블록 */
	BCipherKey *key; /**< 블록암호 키 */
	BCipherContext bCtx; /**< 블록암호 context */
	BYTE key1[BCIPHER_MAX_KEY_SIZE]; /**< CMAC K1 */
	BYTE key2[BCIPHER_MAX_KEY_SIZE]; /**< CMAC K2 */
} CmacContext;

/** CmacContext를 초기화한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS cmac context 초기화 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 * @retval ER_BCIPHER_INVALID_KEY_LENGTH 옳지 못한 키 길이를 입력하였을 때
 * 사용한 비밀키는 ZEROIZE()를 이용하여 응용프로그램에서 제로화한다.
*/
LIBSPEC
ERT PCIS_CMAC_Initialize(
		CmacContext* cmCtx, /**< [out] CMAC context */
		const BYTE *key, /**< [in] 비밀키 */
		BWT keyLen, /**< [in] 비밀키의 바이트 길이 */
		AlgDesc bcipherAlg /**< [in] 블록암호 지시자 */
		);

/** CmacContext를 업데이트한다.
 * 최대 1GB만큼 메시지를 Update할 수 있다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS cmac context 업데이터 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
*/
LIBSPEC
ERT PCIS_CMAC_Update(
		CmacContext *cmCtx, /**< [in,out] CMAC context */
		const BYTE *msg, /**< [in] 추가 메시지 */
		BWT msgLen /**< [in] 메시지의 바이트 길이 */
		);

/** 최종적으로 CMAC 값을 구한다.
 * cmacLen는 블록암호의 블록 크기보다 작거나 같아야 한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS cmac context 업데이터 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 * @retval ER_BCIPHER_INVALID_TAG_LENGTH cmacLen를 블록크기보다 크게 입력하였을 때
 */
LIBSPEC
ERT PCIS_CMAC_Finalize(
		BYTE *cmac, /**< [out] 최종 MAC 값 */
		BWT cmacLen, /**< [in] MAC의 길이 */
		CmacContext *cmCtx /**< [in,out] CMAC context */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif



