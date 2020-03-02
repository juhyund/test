#ifndef _BCIPHER_EXP_H_
#define _BCIPHER_EXP_H_

/** @defgroup BCIPHER Block Cipher Expand
 * @ingroup CE
 * @brief Block Cipher Expand function
 */ 

#include "bcipher_op.h"
#include <stdio.h>

#ifdef EXPORT_CE
#include "ce_dll.h"
#else
#define LIBSPEC_CE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 파일에 대해서 Block cipher 암호화를 수행한다.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode

    인터페이스는 BCIPHER_Encrypt()와 거의 흡사하며, 단지 입출력 데이터가
    file 포인터라는 것만이 다르다. inLen은 암호화할 데이터의 바이트 단위 길이를
    의미하며, 예외적으로 WHOLE_FILE로 지정하였을 경우, file 전체가 암호화
    대상이 된다. 나머지 사항에 대해서는 BCIPHER_Encrypt를 참조하기 바란다.

	\e out과 \e in은 fopen()으로 생성된 것이어야 한다.

 * @sa BCIPHER_Encrypt BCIPHER_DecryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_EncryptFile(
		FILE *out, /**< [out] 출력 암호문이 저장될 파일 */
		BWT *outLen, /**< [out] 출력 암호문의 바이트 길이 */
		FILE *in, /**< [in] 입력 평문이 저장된 파일 */
		BWT inLen, /**< [in] 입력 평문의 바이트 길이 (파일의 일부일 수 있음) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding 여부, (NPAD, PAD, 두 값 중 하나) */
		);

/**
 * @brief 파일에 대해서 Block cipher 복호화를 수행한다.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD cipher includes invalid padding bytes

    인터페이스는 BCIPHER_Decrypt()와 거의 흡사하며, 단지 입출력 데이터가
    file 포인터라는 것만이 다르다. inLen은 복호화할 데이터의 바이트 단위 길이를
    의미하며, 예외적으로 WHOLE_FILE로 지정하였을 경우, file 전체가 복호화
    대상이 된다. 나머지 사항에 대해서는 BCIPHER_Decrypt를 참조하기 바란다.

	\e out과 \e in은 fopen()으로 생성된 것이어야 한다.

 * @sa BCIPHER_Decrypt BCIPHER_EncryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_DecryptFile(
		FILE *out, /**< [out] 출력 평문이 저장될 파일 */
		BWT *outLen, /**< [out] 출력 평문의 길이 */
		FILE *in, /**< [in] 입력 암호문이 저장된 파일 */
		BWT inLen, /**< [in] 입력 암호문의 바이트 길이 (파일의 일부일 수 있음) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding 여부, (NPAD, PAD, 두 값 중 하나) */
		);

/**
 * @brief 파일에 대해서 bufSize 단위로 Block cipher 암호화를 수행한다.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 *
 * BCIPHER_EncryptFile()과 동일한 동작을 수행하지만, 내부 버퍼 사이즈를 특정할
 * 수 있다는 것만 다르다.
 *
 * @sa BCIPHER_EncryptFile
 */
LIBSPEC_CE
ERT BCIPHER_EncryptFile_BSize(
		FILE *out, /**< [out] 출력 암호문이 저장될 파일 */
		BWT *outLen, /**< [out] 출력 암호문의 바이트 길이 */
		FILE *in, /**< [in] 입력 평문이 저장된 파일 */
		BWT inLen, /**< [in] 입력 평문의 바이트 길이 (파일의 일부일 수 있음) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag, /**< [in] Padding 여부, (NPAD, PAD, 두 값 중 하나) */
		BWT bufSize /**< [in] 내부 버퍼 크기 */
		);

/**
 * @brief 파일에 대해서 bufSize 단위로 Block cipher 복호화를 수행한다.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 *
 * BCIPHER_DecryptFile()과 동일한 동작을 수행하지만, 내부 버퍼 사이즈를 특정할
 * 수 있다는 것만 다르다.
 *
 * @sa BCIPHER_EncryptFile
 */
LIBSPEC_CE
ERT BCIPHER_DecryptFile_BSize(
		FILE *out, /**< [out] 출력 평문이 저장될 파일 */
		BWT *outLen, /**< [out] 출력 평문의 길이 */
		FILE *in, /**< [in] 입력 암호문이 저장된 파일 */
		BWT inLen, /**< [in] 입력 암호문의 바이트 길이 (파일의 일부일 수 있음) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag, /**< [in] Padding 여부, (NPAD, PAD, 두 값 중 하나) */
		BWT bufSize /**< [in] 내부 버퍼 크기 */
		);

/**
 * @brief 파일(filename)에 대해서 Block cipher 암호화를 수행한다.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode

    인터페이스는 BCIPHER_Encrypt()와 거의 흡사하며, 단지 입출력 데이터가
    filename이라는 것만 다르다. inLen은 암호화할 데이터의 바이트 단위 길이를
    의미하며, 예외적으로 WHOLE_FILE로 지정하였을 경우, file 전체가 암호화
    대상이 된다. 나머지 사항에 대해서는 BCIPHER_Encrypt를 참조하기 바란다.

 * @sa BCIPHER_Encrypt BCIPHER_DecryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_EncryptFilePath(
		const char *outfilepath, /**< [out] 출력 암호문이 저장될 파일 */
		BWT *outLen, /**< [out] 출력 암호문의 바이트 길이 */
		const char *infilepath, /**< [in] 입력 평문이 저장된 파일 */
		BWT inLen, /**< [in] 입력 평문의 바이트 길이 (파일의 일부일 수 있음) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding 여부, (NPAD, PAD, 두 값 중 하나) */
		);

/**
 * @brief 파일(filename)에 대해서 Block cipher 복호화를 수행한다.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD cipher includes invalid padding bytes

    인터페이스는 BCIPHER_Decrypt()와 거의 흡사하며, 단지 입출력 데이터가
    filename이라는 것만 다르다. inLen은 복호화할 데이터의 바이트 단위 길이를
    의미하며, 예외적으로 WHOLE_FILE로 지정하였을 경우, file 전체가 복호화
    대상이 된다. 나머지 사항에 대해서는 BCIPHER_Decrypt를 참조하기 바란다.

 * @sa BCIPHER_Decrypt BCIPHER_EncryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_DecryptFilePath(
		const char *outfilepath, /**< [out] 출력 평문이 저장될 파일 */
		BWT *outLen, /**< [out] 출력 평문의 바이트 길이 */
		const char *infilepath, /**< [in] 입력 암호문이 저장된 파일 */
		BWT inLen, /**< [in] 입력 암호문의 바이트 길이 (파일의 일부일 수 있음) */
		BCipherContext *bcipher, /**< [in] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding 여부, (NPAD, PAD, 두 값 중 하나) */
		);

/**
 * @brief 파일(filename)의 특정 offset부터 Block cipher 암호화를 수행한다.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode

    인터페이스는 BCIPHER_Encrypt()와 거의 흡사하며, 단지 입출력 데이터가
    filename이라는 것만 다르다. inLen은 암호화할 데이터의 바이트 단위 길이를
    의미하며, 예외적으로 WHOLE_FILE로 지정하였을 경우, file 전체가 암호화
    대상이 된다. 나머지 사항에 대해서는 BCIPHER_Encrypt를 참조하기 바란다.

 * @sa BCIPHER_Encrypt BCIPHER_DecryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_EncryptFilePath_Offset(
		const char *outfilepath, /**< [out] 출력 암호문이 저장될 파일 */
		BWT *outLen, /**< [out] 출력 암호문의 바이트 길이 */
		const char *infilepath, /**< [in] 입력 평문이 저장된 파일 */
		long offset, /**< [in] 암호화를 시작할 offset */
		BWT inLen, /**< [in] 입력 평문의 바이트 길이 (파일의 일부일 수 있음) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding 여부, (NPAD, PAD, 두 값 중 하나) */
		);

/**
 * @brief 파일(filename)의 특정 offset부터 Block cipher 복호화를 수행한다.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD cipher includes invalid padding bytes

    인터페이스는 BCIPHER_Decrypt()와 거의 흡사하며, 단지 입출력 데이터가
    filename이라는 것만 다르다. inLen은 복호화할 데이터의 바이트 단위 길이를
    의미하며, 예외적으로 WHOLE_FILE로 지정하였을 경우, file 전체가 복호화
    대상이 된다. 나머지 사항에 대해서는 BCIPHER_Decrypt를 참조하기 바란다.

 * @sa BCIPHER_Decrypt BCIPHER_EncryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_DecryptFilePath_Offset(
		const char *outfilepath, /**< [out] 출력 평문이 저장될 파일 */
		BWT *outLen, /**< [out] 출력 평문의 바이트 길이 */
		const char *infilepath, /**< [in] 입력 암호문이 저장된 파일 */
		long offset, /**< [in] 복호화를 시작할 offset */
		BWT inLen, /**< [in] 입력 암호문의 바이트 길이 (파일의 일부일 수 있음) */
		BCipherContext *bcipher, /**< [in] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding 여부, (NPAD, PAD, 두 값 중 하나) */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _BCIPHER_EXP_H_ */
