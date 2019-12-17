/** @defgroup CC Cryptographic Core
 */

/** @defgroup ZERO Zeroization
 * @ingroup CC
 * @brief Clear Securely
 */

/** @defgroup KEYGEN Key Generation
 * @ingroup CC
 * @brief Cryptographic Key Generation
 */

/** @file cc_define.h
    @brief 공통 define 

    CC(Cryptographic Core)모듈에서 사용되는 공통의 값과
    데이터형 등을 정의한다.
*/

#ifndef _CC_DEFINE_H_
#define _CC_DEFINE_H_

#include "cis_error.h"

#if defined(WIN32) || defined(_WIN32_WCE)
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "base_define.h"

/* Library Specification */
#if defined(EXPORT_CC) && defined(IMPORT_CC)
  #error "Invalid Library Specification"
#endif

/** @def LIBSPEC
 * @ingroup CC
 * @brief declaration spec when imported as dynamic library
 */

#ifdef LIBSPEC
#undef LIBSPEC
#endif

#if defined(EXPORT_CC)
#define LIBSPEC __declspec(dllexport)
#elif defined(IMPORT_CC)
#define LIBSPEC __declspec(dllimport)
#else
#define LIBSPEC
#endif

#if !defined(_BIG_ENDIAN_) && !defined(_LITTLE_ENDIAN_)
  #error "There is no \"Endianness Specification\""
#endif

#if defined(_BIG_ENDIAN_) && defined(_LITTLE_ENDIAN_)
  #error "Invalid Endianness Specification"
#endif
 
typedef const void* AlgDesc;

#define FILE_BUFFER_SIZE 65536 /* 65536 byte = 64 Kbyte */

/** @ingroup PKCRYPT
    @def WHOLE_FILE
    
    파일 관련 인터페이스(PKCRYTP, BCIPHER 모듈)의 처리할 부분의 길이값으로
    입력될 수 있으며, 파일 전체를 의미하는 값이다. 물론, 파일 일부분을 의미
    할 때에는 구체적인 정수값을 입력으로 주어야 한다.
  */
#define WHOLE_FILE (~0) /* bitwise complement of 0, means 4GByte file */

/** @ingroup CC */
enum CIS_STATE_CODE
{
	/** Error state */
    CIS_STATE_ERROR = -100,
	/** CIS module loaded but not initialized */
    CIS_STATE_LOADED = 0x00,
	/** CIS module state managing SSP */
    CIS_STATE_SSP = 0x01,
	/* uninitialized */
#ifndef SELF_TEST
	/** Performing self test */
	CIS_STATE_SELFTEST_NONE = 0x10,
#endif
	/** Performing self test */
	CIS_STATE_SELFTEST_KCMVP = 0x12,
	/* initialized states. target modes */
	/** Providing all algorithms without restriction */
	CIS_STATE_APPROVED_NONE = 0x40,
	/** Providing KCMVP-approved algorithms */
	CIS_STATE_APPROVED_KCMVP = 0x42,
};

/* for compatibility */
#define CIS_STATE_POWER_UP_SELFTEST		CIS_STATE_SELFTEST_KCMVP
#define CIS_STATE_NOT_VERIFIED_SERVICE	CIS_STATE_APPROVED_NONE
#define CIS_STATE_NON_APPROVED			CIS_STATE_APPROVED_NONE
#define CIS_STATE_VERIFIED_SERVICE		CIS_STATE_APPROVED_KCMVP

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CC
 * @{ */

/** @brief CIS-CC의 version을 출력
 * @return [out] string representing version, ex) pointer to "3.3"
 */
LIBSPEC
const char* PCIS_CC_Version(void);

/** @brief CIS-CC의 명칭과 버전을 출력
 * @return [out] string representing name & version, ex) pointer to "CIS-CC v3.3"
 */
LIBSPEC
const char* PCIS_CC_Name_Version(void);

/** @brief CIS-CC 암호모듈에 전원인가 자가시험을 포함한 초기화를 수행한다.
 * @return 암호모듈 초기화 성공여부
 * @retval SUCCESS 암호모듈 초기화 성공
 * @retval ER_SELFTEST_MODULE_INTEGRITY 무결성 검증 실패 시
 * @retval -9102~-9208 동작 전 자가시험 실패 시 해당 에러코드 반환
 *
 * 암호모듈 자가시험을 수행하여 성공할 경우 검증암호 운영 상태로 천이하여 암호
 * 서비스 제공이 가능하도록 한다. 실패할 경우 오류 상태로 천이하여 암호 서비스
 * 제공을 차단한다. 다시 초기화하기 위해서는 먼저 PCIS_CC_Finalize() 함수를
 * 호출하여야 한다.
 *
 * @note 주의할 것은 PCIS_CC_Initialize()는 초기화 이후의 암호모듈의 현재상태를
 * return하는 것이 아니고, 초기화 성공 여부를 return한다는 것이다.
 *
 * @sa PCIS_CC_Finalize
 */
LIBSPEC
ERT PCIS_CC_Initialize(void);

/** @brief CIS-CC 암호모듈 사용을 종료한다.
 * @return [out] 사용 종료후 암호모듈 상태
 *
 * 암호모듈을 로드됨 상태로 천이하여 암호 서비스 제공을 최종 중지한다. 오류
 * 상태(CIS_STATE_ERROR)에 빠져 있을 경우 오류 상태를 빠져나와 다시 초기화 직전
 * 상태인 CIS_STATE_LOADED 상태로 돌아갈 수 있으며 이후 다시 초기화를 시도할 수
 * 있다.
 *
 * @sa PCIS_CC_Initialize
 */
LIBSPEC
int PCIS_CC_Finalize(void);

/** @brief CIS-CC 암호모듈의 현재 상태를 출력한다.
 * @return [out] 암호모듈의 현재 상태
 * @sa PCIS_CC_SetState
  */
LIBSPEC
int PCIS_CC_GetState(void);

/** @brief CIS-CC 암호모듈의 상태를 설정한다.
 * @param[in] state 설정하고자 하는 암호모듈 상태
 * @retval SUCCESS 암호모듈 상태 변환 성공
 * @retval ER_INVALID_STATE 변환할 수 없는 상태를 입력하였을 때
 * @retval ER_SELFTEST_MODULE_INTEGRITY 무결성 검증 실패 시
 * @retval -9102~-9208 동작 전 자가시험 실패 시 해당 에러코드 반환
 *
 * 설정하고자 하는 암호 모듈을 상태는 임의의 값일 수 없고, 현재 상태로부터
 * 천이할 수 없는 상태가 입력될 경우 오류를 출력한다.
 *
 * @sa PCIS_CC_GetState
 */
LIBSPEC
ERT PCIS_CC_SetState(int state);

/** @brief CIS-CC 암호모듈의 상태를 검증암호 운영 상태로 설정한다.
 * @return [out] 상태 천이 후 암호모듈의 현재 상태
 * @sa PCIS_CC_SetStateNotVerifiedService
 */
LIBSPEC
int PCIS_CC_SetStateVerifiedService(void);

/** @brief CIS-CC 암호모듈의 상태를 비검증암호 운영 상태로 설정한다.
 * @return [out] 상태 천이 후 암호모듈의 현재 상태
 * @sa PCIS_CC_SetStateVerifiedService
 */
LIBSPEC
int PCIS_CC_SetStateNotVerifiedService(void);

/** @} */

#define ZEROIZE(target, size)\
{\
	int zeroi;\
	volatile BYTE* v_target = (BYTE*)(target);\
	for (zeroi = 0; zeroi < (size); zeroi++) v_target[zeroi] = 0x00;\
}

/* not in selftest, and not in approved */
#define CIS_STATE_NOT_READY \
	((PCIS_CC_GetState() == CIS_STATE_LOADED) || CIS_STATE_IN_SELFTEST)

#define CIS_STATE_IN_KCMVP (PCIS_CC_GetState() == CIS_STATE_APPROVED_KCMVP)
#define CIS_STATE_IN_NONE (PCIS_CC_GetState() == CIS_STATE_APPROVED_NONE)
#define CIS_STATE_IN_SELFTEST ((PCIS_CC_GetState() & ~0xf) == 0x10)

#define ER_RET_VAL_IF_STATE_NOT_READY() \
{\
 ER_RET_VAL_IF(CIS_STATE_NOT_READY, ER_CIS_NOT_READY);\
 ER_RET_VAL_IF((PCIS_CC_GetState() == CIS_STATE_SSP), ER_INVALID_STATE);\
 ER_RET_VAL_IF((PCIS_CC_GetState() == CIS_STATE_ERROR), ER_INVALID_STATE);\
}
#define ER_RET_VAL_IF_STATE_NOT_IN_SELFTEST()\
 ER_RET_VAL_IF(!CIS_STATE_IN_SELFTEST, ER_INVALID_STATE)
#define ER_RET_VAL_IF_STATE_IN_KCMVP()\
 ER_RET_VAL_IF(CIS_STATE_IN_KCMVP, ER_NOT_APPROVED_ALGORITHM)

#define ER_RET_NULL_IF_STATE_NOT_READY() \
{\
	ER_RET_NULL_IF(CIS_STATE_NOT_READY);\
	ER_RET_NULL_IF(PCIS_CC_GetState() == CIS_STATE_SSP);\
	ER_RET_NULL_IF(PCIS_CC_GetState() == CIS_STATE_ERROR);\
}
#define ER_RET_NULL_IF_STATE_NOT_IN_SELFTEST() ER_RET_NULL_IF(!CIS_STATE_IN_SELFTEST)
#define ER_RET_NULL_IF_STATE_IN_KCMVP() ER_RET_NULL_IF(CIS_STATE_IN_KCMVP)

#define ER_RET_VOID_IF_STATE_NOT_READY() \
{\
	ER_RET_VOID_IF(CIS_STATE_NOT_READY);\
	ER_RET_VOID_IF(PCIS_CC_GetState() == CIS_STATE_SSP);\
	ER_RET_VOID_IF(PCIS_CC_GetState() == CIS_STATE_ERROR);\
}
#define ER_RET_VOID_IF_STATE_NOT_IN_SELFTEST() ER_RET_VOID_IF(!CIS_STATE_IN_SELFTEST)
#define ER_RET_VOID_IF_STATE_IN_KCMVP() ER_RET_VOID_IF(CIS_STATE_IN_KCMVP)

/* for backward compatibility */
#define ER_RET_VAL_IF_INVALID_STATE ER_RET_VAL_IF_STATE_NOT_READY
#define ER_RET_NULL_IF_INVALID_STATE ER_RET_NULL_IF_STATE_NOT_READY
#define ER_RET_VOID_IF_INVALID_STATE ER_RET_VOID_IF_STATE_NOT_READY
#define ER_RET_VAL_IF_VERIFIED_SERVICE ER_RET_VAL_IF_STATE_IN_KCMVP
#define ER_RET_NULL_IF_VERIFIED_SERVICE ER_RET_NULL_IF_STATE_IN_KCMVP
#define ER_RET_VOID_IF_VERIFIED_SERVICE ER_RET_VOID_IF_STATE_IN_KCMVP

#define ENFORCE_STATE_NONAPPROVED_VAL() {\
	ER_RET_VAL_IF_STATE_NOT_READY();\
	ER_RET_VAL_IF_STATE_IN_KCMVP();\
}

#define ENFORCE_STATE_KCMVP_VAL() {\
	ER_RET_VAL_IF_STATE_NOT_READY();\
}

#define ENFORCE_STATE_APPROVED_VAL() {\
	ER_RET_VAL_IF_STATE_NOT_READY();\
}

#define ENFORCE_STATE_NONAPPROVED_VOID() {\
	ER_RET_VOID_IF_STATE_NOT_READY();\
	ER_RET_VOID_IF_STATE_IN_KCMVP();\
}

#define ENFORCE_STATE_KCMVP_VOID() {\
	ER_RET_VOID_IF_STATE_NOT_READY();\
}

#define ENFORCE_STATE_APPROVED_VOID() {\
	ER_RET_VOID_IF_STATE_NOT_READY();\
}

#ifdef __cplusplus
}
#endif

#endif /* _CC_DEFINE_H_ */
