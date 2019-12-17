/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_DH_H_
#define _PCIS_DH_H_

/** @defgroup DH
 * @ingroup PKCRYPT
 * @brief DH (Diffie-Hellman) Key Agreement
 */

/** @file
 * @ingroup DH
 */

#include "ffc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup DH
 * @{ */

typedef struct {
	MINT p; /**< 시스템 파라미터 p */
	MINT q; /**< 시스템 파라미터 q */
	MINT g; /**< 시스템 파라미터 g */
	MINT x;    /**< 자신의 private info or private key */
	MINT yR;   /**< 상대방의 public info or public key */
	BWT  keyLen;         /**< 키생성시 사용할 키길이 */
	const void *hashAlg; /**< 키생성시 사용할 해쉬 알고리즘 디스크립터 */
} KEDH_Context;

/** @brief DH context를 초기화한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS dh context 초기화 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
*/
LIBSPEC
ERT PCIS_DH_Initialize(
		KEDH_Context *ctx, /**< [out] context */
		MINT *p, /**< [in] parameter p */
		MINT *q, /**< [in] parameter q */
		MINT *g, /**< [in] parameter g */
		MINT *x, /**< [in] optional private key */
		MINT *yR /**< [in] optional peer public key */
		);

/** @brief context에 비밀키를 생성하여 저장하고, 해당 공개키(y)를 생성
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 자신의 공개키 생성 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 */
LIBSPEC
ERT PCIS_DH_GenShareInfo(
		KEDH_Context *ctx, /**< [in,out] context 내장 난수발생기를 이용하여 개인키(개인정보)를 생성하여 저장됨 */
		MINT *y /**< [out] 생성된 공개키(공유정보) */
		);

/** @brief context에 저장된 자신의 비밀키와 입력한 상대방의 공개키를 이용하여 최종 공유키(zz)를 생성
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 공유키 생성 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 */
LIBSPEC
ERT PCIS_DH_GetKey(
		KEDH_Context *ctx, /**< [in] context */
		MINT *yR, /**< [in] 상대방의 공개키(공개정보) */
		MINT *zz /**< [out] 최종 공유키 */
		);

/** @brief generate DH parameter 
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS DH 파라미터 생성 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
*/
LIBSPEC
ERT PCIS_DH_GenParam(
		PCIS_FFC_Param *param, /**< [out] parameter to be generated */
		BWT pLen, /**< [in] desired length of P */
		BWT qLen /**< [in] desired length of Q */
		);

/** @brief set DH parameter 
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS DH 파라미터 설정 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
*/
LIBSPEC
ERT PCIS_DH_SetParam(
		PCIS_FFC_Param *param, /**< [out] target parameter */
		const MINT *p, /**< [in] prime modulus */
		const MINT *q, /**< [in] factor of p-1 */
		const MINT *g /**< [in] generator */
		);

/** @brief generate DH key pair 
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS DH 키쌍 생성 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 * @retval ER_CONDITIONAL_SELFTEST 키쌍 일치 시험 실패하였을 경우
 */
LIBSPEC
ERT PCIS_DH_GenKey(
		PCIS_FFC_Key *key /**< [in,out] 유한체 상의 키 쌍 */
		);

/** @brief compute DH shared key from two peer keys
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 공유키 생성 성공
 * @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
*/
LIBSPEC
ERT PCIS_DH_ComputeSharedKey(
		MINT *shared, /**< [out] 최종 공유키 */
		PCIS_FFC_Key *myKey, /**< [in] 자신의 비밀키(비밀정보) */
		MINT *peerKey /**< [in] 상대방의 공개키(공개정보) */
		);

/** @brief wipe DH private key */
LIBSPEC
void PCIS_DH_WipeKey(
		KEDH_Context *ctx /**< [in] DH context */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_DH_H_ */
