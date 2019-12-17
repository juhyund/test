#ifndef _DRBG_H_
#define _DRBG_H_

/** @defgroup RNG Random Number
 * @ingroup CC
 * @brief Random Number Generation
 */

#include <stdio.h>
#include "mint_common.h"
#include "hash_op.h"
#include "bcipher_op.h"

/** @file
 * @ingroup RNG
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup HASHDRBG HASHDRBG
 * @ingroup RNG
 * @brief HASHDRBG algorithm
 */

/** @defgroup HMACDRBG HMACDRBG
 * @ingroup RNG
 * @brief HMACDRBG algorithm
 */

/** @defgroup CTRDRBG CTRDRBG
 * @ingroup RNG
 * @brief CTRDRBG algorithm
 */

#define HASH_MAX_OUT_LEN 64
#define MAX_BLOCK_LEN 32
#define RESEED_INTERVAL 16

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/** @ingroup HASHDRBG
 * @brief HASH_DRBG instance state */
typedef struct {
	BYTE V[112]; /**< 내부 버퍼 */
	BYTE C[112]; /**< 내부 버퍼 */
	BWT reseed_counter; /**< reseed 시행 횟수 */
	BWT reseed_interval; /**< reseed 최대 횟수 */
	BWT seedLen; /**< V, C의 실제 사용 크기 */
	BWT prediction_resistance_flag; /**< 예측 내성 여부 */
	BYTE prev_rand[2050]; /**< 이전 출력 난수 */
	AlgDesc hashAlg; /**< 알고리즘 지시자 */
} HashDrbgState;

/** @ingroup HMACDRBG
 * @brief HMAC_DRBG instance state */
typedef struct {
	BYTE V[64]; /**< 내부 버퍼 */
	BYTE Key[64]; /**< HMAC 키 */
	BWT outLen; /**< V의 실제 사용 크기 */
	BWT reseed_counter; /**< reseed 시행 횟수 */
	BWT reseed_interval; /**< reseed 최대 횟수 */
	BWT prediction_resistance_flag; /**< 예측 내성 여부 */
	BYTE prev_rand[2050]; /**< 이전 출력 난수 */
	AlgDesc hashAlg; /**< 알고리즘 지시자 */
} HmacDrbgState;

/** @ingroup CTRDRBG
 * @brief CTR_DRBG instance state */
typedef struct {
	BYTE V[112]; /**< 내부 버퍼 */
	BYTE Key[112]; /**< BCIPHER 키 */
	BWT reseed_counter; /**< reseed 시행 횟수 */
	BWT reseed_interval; /**< reseed 최대 횟수 */
	BWT blockLen; /**< BCIPHER 블록 크기 */
	BWT keyLen; /**< Key의 실제 크기 */
	BWT prediction_resistance_flag; /**< 예측 내성 여부 */
	BWT df_flag; /**< 유도 함수 사용 여부 */
	BYTE prev_rand[2050]; /**< 이전 출력 난수 */
	AlgDesc bcipherAlg; /**< 알고리즘 지시자 */
} CtrDrbgState;

/** @ingroup RNG */
enum
{
	ALG_SHA224 = 0,
	ALG_SHA256,
	ALG_SHA384,
	ALG_SHA512,
	ALG_SEED,
	ALG_HIGHT,
	ALG_ARIA,
	ALG_ARIA192,
	ALG_ARIA256,
	ALG_LEA128,
	ALG_LEA192,
	ALG_LEA256
};

/** @addtogroup HASHDRBG
 * @{ */

/** @brief 내장 HASHDRBG instance로부터 난수를 발생한다. */
LIBSPEC
ERT HASHDRBG_GetRandNum(
		BYTE* rand, /**< [out] 생성된 난수가 저장될 버퍼를 가리키는 포인터 */
		BWT randBitLen /**< [in] 생성할 난수의 비트 단위 길이 */
		);

/** @ingroup CC
 * @brief 내장 HASHDRBG 내부 상태를 제로화한다. */
LIBSPEC
void PCIS_CC_InternalDrbgZeroize(void);

/** @brief 주어진 HASHDRBG instance를 초기화한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 난수 생성 성공
 * @retval ER_NULL_STATE HashDrbgState 인스턴스화할 context 메모리가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * nonce와 pers의 경우 난수의 보안 강도를 높혀주는 역할을 하며 NULL을 입력해도
 * 난수는 생성된다.
 */
LIBSPEC
ERT HASHDRBG_Instantiate(
		HashDrbgState *drbg, /**< [out] 초기화하고자 하는 HASHDRBG instance */
		BWT hashAlg, /**< [in] 사용할 해쉬 함수 알고리즘 지시자
					   (SHA224, SHA256, SHA384, SHA512 중 하나) */
		BWT pResist, /**< [in] 예측 내성 여부 (TRUE, FALSE 두 값 중 하나) */
		BYTE *nonce, /**< [in] 초기화에 사용할 논스 */
		BWT nonceLen, /**< [in] 논스의 바이트 단위 길이 */
		BYTE *pers, /**< [in] 초기화에 사용할 개별화 문자열 */
		BWT persLen /**< [in] 개별화 문자열의 바이트 단위 길이 */
		);

/** @brief 주어진 HASHDRBG instance를 Reseeding한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 난수 생성 성공
 * @retval ER_NULL_STATE HashDrbgState context가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_REQUEST_TOO_LONG_RANDOM 16384비트보다 긴 난수 발생을 요구하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * addString은 Reseeding 과정에서 보다 강한 예측 내성이 생기도록 하며, NULL을
 * 입력해도 Reseeding은 가능하다.
 *
 * instance 초기화 시 예측 내성 플래그를 TRUE로 입력하면 HASHDRBG_GenerateRand
 * 내부에서 매 난수 생성시마다 Reseeding이 이루어지지만, FALSE인 경우
 * reseed_interval만큼 호출된 경우를 제외하고는 Reseeding이 이루어지지 않기
 * 때문에 필요한 경우엔 직접 함수를 호출하여 Reseeding을 해주도록 한다.
 */
LIBSPEC
ERT HASHDRBG_Reseed(
		HashDrbgState *drbg, /**< [in,out] Reseeding할 DRBG instance */
		BYTE *addString, /**< [in] Reseeding에 필요한 추가 문자열 */
		BWT addLen /**< [in] 추가 문자열의 바이트 단위 길이 */
		);

/** @brief 주어진 HASHDRBG instance로부터 난수를 발생한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 난수 생성 성공
 * @retval ER_NULL_STATE HashDrbgState context가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_REQUEST_TOO_LONG_RANDOM 16384비트보다 긴 난수 발생을 요구하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * addString은 reseeding이 이루어지는 경우에 필요하다. HASHDRBG_GenerateRand
 * 내부에서 Reseeding이 이루어지는 경우는 예측 내성 여부가 TRUE이거나,
 * reseed_counter 값이 reseed_interval 값과 같아진 경우가 있다.
 */
LIBSPEC
ERT HASHDRBG_GenerateRand(
		BYTE *rand, /**< [out] 생선된 난수가 저장될 버퍼를 가리키는 포인터 */
		HashDrbgState *drbg, /**< [in,out] 사용할 DRBG instance */
		BWT bitNo, /**< [in] 생성할 난수의 비트 단위 길이, 최대 16384(비트) */
		BYTE *addString, /**< [in] reseeding에 필요한 추가 문자열 */
		BWT addLen /**< [in] 추가 문자열의 바이트 단위 길이 */
		);

/** @ingroup ZERO
 * @brief HASHDRBG의 내부 상태를 제로화한다. */
LIBSPEC
void HASHDRBG_Zeroize(
		HashDrbgState *drbg /**< [in] 사용할 DRBG instance*/
		);

/** @} */

/** @addtogroup HMACDRBG
 * @{ */

#define HMACDRBG_GetRandNum HASHDRBG_GetRandNum

/** @brief 주어진 HMACDRBG instance를 초기화한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 난수 생성 성공
 * @retval ER_NULL_STATE HmacDrbgState 인스턴스화할 context 메모리가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * nonce와 pers의 경우 난수의 보안 강도를 높혀주는 역할을 하며 NULL을 입력해도
 * 난수는 생성된다.
 */
LIBSPEC
ERT HMACDRBG_Instantiate(
		HmacDrbgState *drbg, /**< [out] 초기화하고자 하는 HMACDRBG instance */
		BWT hashAlg, /**< [in] 사용할 해쉬 함수 알고리즘 지시자
					   (SHA224, SHA256, SHA384, SHA512 중 하나) */
		BWT pResist, /**< [in] 예측 내성 여부, (TRUE, FALSE 두 값 중 하나) */
		BYTE *nonce, /**< [in] 초기화에 사용할 논스 */
		BWT nonceLen, /**< [in] 논스의 바이트 단위 길이 */
		BYTE *pers, /**< [in] 초기화에 사용할 개별화 문자열 */
		BWT persLen /**< [in] 개별화 문자열의 바이트 단위 길이 */
		);

/** @brief 주어진 HMACDRBG instance를 Reseeding한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 난수 생성 성공
 * @retval ER_NULL_STATE HmacDrbgState context가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * addString은 Reseeding 과정에서 보다 강한 예측 내성이 생기도록 하며, NULL을
 * 입력해도 Reseeding은 가능하다.
 *
 * instance 초기화 시 예측 내성 플래그를 TRUE로 입력하면 HMACDRBG_GenerateRand
 * 내부에서 매 난수 생성시마다 Reseeding이 이루어지지만, FALSE인 경우
 * reseed_interval만큼 호출된 경우를 제외하고는 Reseeding이 이루어지지 않기
 * 때문에 필요한 경우엔 직접 함수를 호출하여 Reseeding을 해주도록 한다.
 */
LIBSPEC
ERT HMACDRBG_Reseed(
		HmacDrbgState *drbg, /**< [in,out] Reseeding할 DRBG instance */
		BYTE *addString, /**< [in] Reseeding에 필요한 추가 문자열 */
		BWT addLen /**< [in] 추가 문자열의 바이트 단위 길이 */
		);

/** @brief 주어진 HMACDRBG instance로부터 난수를 발생한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 난수 생성 성공
 * @retval ER_NULL_STATE HmacDrbgState context가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_REQUEST_TOO_LONG_RANDOM 16384비트보다 긴 난수 발생을 요구하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * addString은 reseeding이 이루어지는 경우에 필요하다. HMACDRBG_GenerateRand
 * 내부에서 Reseeding이 이루어지는 경우는 예측 내성 여부가 TRUE이거나,
 * reseed_counter 값이 reseed_interval 값과 같아진 경우가 있다.
 */
LIBSPEC
ERT HMACDRBG_GenerateRand(
		BYTE *rand, /**< [out] 생선된 난수가 저장될 버퍼를 가리키는 포인터 */
		HmacDrbgState *drbg, /**< [in,out] 사용할 DRBG instance */
		BWT bitNo, /**< [in] 생성할 난수의 비트 단위 길이, 최대 16384(비트) */
		BYTE *addString, /**< [in] reseeding에 필요한 추가 문자열 */
		BWT addLen /**< [in] 추가 문자열의 바이트 단위 길이 */
		);

/** @ingroup ZERO
 * @brief HMACDRBG의 내부 상태를 제로화한다. */
LIBSPEC
void HMACDRBG_Zeroize(
		HmacDrbgState *drbg /**< [in] 사용할 DRBG instance*/
		);

/** @} */

/** @addtogroup CTRDRBG
 * @{ */

/** @brief 주어진 CTRDRBG instance를 초기화한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS CtrDrbgState 인스턴스화 성공
 * @retval ER_NULL_STATE CtrDrbgState 인스턴스화할 context 메모리가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * nonce와 pers의 경우 난수의 보안 강도를 높혀주는 역할을 하며 NULL을 입력해도
 * 난수는 생성된다.
*/
LIBSPEC
ERT CTRDRBG_Instantiate(
		CtrDrbgState *drbg, /**< [out] 초기화하고자 하는 CTRDRBG instance*/
		BWT bcipherAlg, /**< [in] 사용할 블록 암호 알고리즘 지시자
					   (SEED, HIGHT, ARIA, ARIA192, ARIA256, LEA128, LEA192, LEA256 중 하나)*/
		BWT pResist, /**< [in] 예측 내성 여부, (TRUE, FALSE 두 값 중 하나)*/
		BWT pDf, /**< [in] 유도 함수 사용 여부, (TRUE, FALSE 두 값 중 하나)*/
		BYTE *nonce, /**< [in] 초기화에 사용할 논스*/
		BWT nonceLen, /**< [in] 논스의 바이트 단위 길이*/
		BYTE *pers, /**< [in] 초기화에 사용할 개별화 문자열*/
		BWT persLen /**< [in] 개발화 문자열의 바이트 단위 길이*/
		);

/** @brief 주어진 CTRDRBG instance를 Reseeding한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 난수 생성 성공
 * @retval ER_NULL_STATE CtrDrbgState context가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * addString은 Reseeding 과정에서 보다 강한 예측 내성이 생기도록 하며, NULL을
 * 입력해도 Reseeding은 가능하다.
 *
 * instance 초기화 시 예측 내성 플래그를 TRUE로 입력하면 CTRDRBG_GenerateRand
 * 내부에서 매 난수 생성시마다 Reseeding이 이루어지지만, FALSE인 경우
 * reseed_interval만큼 호출된 경우를 제외하고는 Reseeding이 이루어지지 않기
 * 때문에 필요한 경우엔 직접 함수를 호출하여 Reseeding을 해주도록 한다.
*/
LIBSPEC
ERT CTRDRBG_Reseed(
		CtrDrbgState *drbg, /**< [in,out] Reseeding할 DRBG instance */
		BYTE *addString, /**< [in] Reseeding에 필요한 추가 문자열 */
		BWT addLen /**< [in] 추가 문자열의 바이트 단위 길이 */
		);

/** @brief 주어진 CTRDRBG instance로부터 난수를 발생한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 난수 생성 성공
 * @retval ER_NULL_STATE CtrDrbgState context가 null일 때
 * @retval ER_INVALID_BLOCKCIPHER_ALG 타당하지 않은 블록 암호 알고리즘을 입력하였을 때
 * @retval ER_REQUEST_TOO_LONG_RANDOM 16384비트보다 긴 난수 발생을 요구하였을 때
 * @retval ER_FAULT_DETECTION_RBG 난수발생기 오류 탐지 시험에 실패하였을 때
 * 
 * addString은 reseeding이 이루어지는 경우에 필요하다. CTRDRBG_GenerateRand
 * 내부에서 Reseeding이 이루어지는 경우는 예측 내성 여부가 TRUE이거나,
 * reseed_counter 값이 reseed_interval 값과 같아진 경우가 있다.
*/
LIBSPEC
ERT CTRDRBG_GenerateRand(
		BYTE *rand, /**< [out] 생선된 난수가 저장될 버퍼를 가리키는 포인터 */
		CtrDrbgState *drbg, /**< [in,out] 사용할 DRBG instance */
		BWT bitNo, /**< [in] 생성할 난수의 비트 단위 길이, 최대 16384(비트) */
		BYTE *addString, /**< [in] reseeding에 필요한 추가 문자열 */
		BWT addLen /**< [in] 추가 문자열의 바이트 단위 길이 */
		);

/** @ingroup ZERO
 * @brief HASHDRBG의 내부 상태를 제로화한다. */
LIBSPEC
void CTRDRBG_Zeroize(
		CtrDrbgState *drbg /**< [in] 사용할 DRBG instance*/
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
