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
    @brief ���� define 

    CC(Cryptographic Core)��⿡�� ���Ǵ� ������ ����
    �������� ���� �����Ѵ�.
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
    
    ���� ���� �������̽�(PKCRYTP, BCIPHER ���)�� ó���� �κ��� ���̰�����
    �Էµ� �� ������, ���� ��ü�� �ǹ��ϴ� ���̴�. ����, ���� �Ϻκ��� �ǹ�
    �� ������ ��ü���� �������� �Է����� �־�� �Ѵ�.
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

/** @brief CIS-CC�� version�� ���
 * @return [out] string representing version, ex) pointer to "3.3"
 */
LIBSPEC
const char* PCIS_CC_Version(void);

/** @brief CIS-CC�� ��Ī�� ������ ���
 * @return [out] string representing name & version, ex) pointer to "CIS-CC v3.3"
 */
LIBSPEC
const char* PCIS_CC_Name_Version(void);

/** @brief CIS-CC ��ȣ��⿡ �����ΰ� �ڰ������� ������ �ʱ�ȭ�� �����Ѵ�.
 * @return ��ȣ��� �ʱ�ȭ ��������
 * @retval SUCCESS ��ȣ��� �ʱ�ȭ ����
 * @retval ER_SELFTEST_MODULE_INTEGRITY ���Ἲ ���� ���� ��
 * @retval -9102~-9208 ���� �� �ڰ����� ���� �� �ش� �����ڵ� ��ȯ
 *
 * ��ȣ��� �ڰ������� �����Ͽ� ������ ��� ������ȣ � ���·� õ���Ͽ� ��ȣ
 * ���� ������ �����ϵ��� �Ѵ�. ������ ��� ���� ���·� õ���Ͽ� ��ȣ ����
 * ������ �����Ѵ�. �ٽ� �ʱ�ȭ�ϱ� ���ؼ��� ���� PCIS_CC_Finalize() �Լ���
 * ȣ���Ͽ��� �Ѵ�.
 *
 * @note ������ ���� PCIS_CC_Initialize()�� �ʱ�ȭ ������ ��ȣ����� ������¸�
 * return�ϴ� ���� �ƴϰ�, �ʱ�ȭ ���� ���θ� return�Ѵٴ� ���̴�.
 *
 * @sa PCIS_CC_Finalize
 */
LIBSPEC
ERT PCIS_CC_Initialize(void);

/** @brief CIS-CC ��ȣ��� ����� �����Ѵ�.
 * @return [out] ��� ������ ��ȣ��� ����
 *
 * ��ȣ����� �ε�� ���·� õ���Ͽ� ��ȣ ���� ������ ���� �����Ѵ�. ����
 * ����(CIS_STATE_ERROR)�� ���� ���� ��� ���� ���¸� �������� �ٽ� �ʱ�ȭ ����
 * ������ CIS_STATE_LOADED ���·� ���ư� �� ������ ���� �ٽ� �ʱ�ȭ�� �õ��� ��
 * �ִ�.
 *
 * @sa PCIS_CC_Initialize
 */
LIBSPEC
int PCIS_CC_Finalize(void);

/** @brief CIS-CC ��ȣ����� ���� ���¸� ����Ѵ�.
 * @return [out] ��ȣ����� ���� ����
 * @sa PCIS_CC_SetState
  */
LIBSPEC
int PCIS_CC_GetState(void);

/** @brief CIS-CC ��ȣ����� ���¸� �����Ѵ�.
 * @param[in] state �����ϰ��� �ϴ� ��ȣ��� ����
 * @retval SUCCESS ��ȣ��� ���� ��ȯ ����
 * @retval ER_INVALID_STATE ��ȯ�� �� ���� ���¸� �Է��Ͽ��� ��
 * @retval ER_SELFTEST_MODULE_INTEGRITY ���Ἲ ���� ���� ��
 * @retval -9102~-9208 ���� �� �ڰ����� ���� �� �ش� �����ڵ� ��ȯ
 *
 * �����ϰ��� �ϴ� ��ȣ ����� ���´� ������ ���� �� ����, ���� ���·κ���
 * õ���� �� ���� ���°� �Էµ� ��� ������ ����Ѵ�.
 *
 * @sa PCIS_CC_GetState
 */
LIBSPEC
ERT PCIS_CC_SetState(int state);

/** @brief CIS-CC ��ȣ����� ���¸� ������ȣ � ���·� �����Ѵ�.
 * @return [out] ���� õ�� �� ��ȣ����� ���� ����
 * @sa PCIS_CC_SetStateNotVerifiedService
 */
LIBSPEC
int PCIS_CC_SetStateVerifiedService(void);

/** @brief CIS-CC ��ȣ����� ���¸� �������ȣ � ���·� �����Ѵ�.
 * @return [out] ���� õ�� �� ��ȣ����� ���� ����
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
