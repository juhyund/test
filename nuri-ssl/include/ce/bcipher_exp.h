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
 * @brief ���Ͽ� ���ؼ� Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode

    �������̽��� BCIPHER_Encrypt()�� ���� ����ϸ�, ���� ����� �����Ͱ�
    file �����Ͷ�� �͸��� �ٸ���. inLen�� ��ȣȭ�� �������� ����Ʈ ���� ���̸�
    �ǹ��ϸ�, ���������� WHOLE_FILE�� �����Ͽ��� ���, file ��ü�� ��ȣȭ
    ����� �ȴ�. ������ ���׿� ���ؼ��� BCIPHER_Encrypt�� �����ϱ� �ٶ���.

	\e out�� \e in�� fopen()���� ������ ���̾�� �Ѵ�.

 * @sa BCIPHER_Encrypt BCIPHER_DecryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_EncryptFile(
		FILE *out, /**< [out] ��� ��ȣ���� ����� ���� */
		BWT *outLen, /**< [out] ��� ��ȣ���� ����Ʈ ���� */
		FILE *in, /**< [in] �Է� ���� ����� ���� */
		BWT inLen, /**< [in] �Է� ���� ����Ʈ ���� (������ �Ϻ��� �� ����) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding ����, (NPAD, PAD, �� �� �� �ϳ�) */
		);

/**
 * @brief ���Ͽ� ���ؼ� Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD cipher includes invalid padding bytes

    �������̽��� BCIPHER_Decrypt()�� ���� ����ϸ�, ���� ����� �����Ͱ�
    file �����Ͷ�� �͸��� �ٸ���. inLen�� ��ȣȭ�� �������� ����Ʈ ���� ���̸�
    �ǹ��ϸ�, ���������� WHOLE_FILE�� �����Ͽ��� ���, file ��ü�� ��ȣȭ
    ����� �ȴ�. ������ ���׿� ���ؼ��� BCIPHER_Decrypt�� �����ϱ� �ٶ���.

	\e out�� \e in�� fopen()���� ������ ���̾�� �Ѵ�.

 * @sa BCIPHER_Decrypt BCIPHER_EncryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_DecryptFile(
		FILE *out, /**< [out] ��� ���� ����� ���� */
		BWT *outLen, /**< [out] ��� ���� ���� */
		FILE *in, /**< [in] �Է� ��ȣ���� ����� ���� */
		BWT inLen, /**< [in] �Է� ��ȣ���� ����Ʈ ���� (������ �Ϻ��� �� ����) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding ����, (NPAD, PAD, �� �� �� �ϳ�) */
		);

/**
 * @brief ���Ͽ� ���ؼ� bufSize ������ Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 *
 * BCIPHER_EncryptFile()�� ������ ������ ����������, ���� ���� ����� Ư����
 * �� �ִٴ� �͸� �ٸ���.
 *
 * @sa BCIPHER_EncryptFile
 */
LIBSPEC_CE
ERT BCIPHER_EncryptFile_BSize(
		FILE *out, /**< [out] ��� ��ȣ���� ����� ���� */
		BWT *outLen, /**< [out] ��� ��ȣ���� ����Ʈ ���� */
		FILE *in, /**< [in] �Է� ���� ����� ���� */
		BWT inLen, /**< [in] �Է� ���� ����Ʈ ���� (������ �Ϻ��� �� ����) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag, /**< [in] Padding ����, (NPAD, PAD, �� �� �� �ϳ�) */
		BWT bufSize /**< [in] ���� ���� ũ�� */
		);

/**
 * @brief ���Ͽ� ���ؼ� bufSize ������ Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 *
 * BCIPHER_DecryptFile()�� ������ ������ ����������, ���� ���� ����� Ư����
 * �� �ִٴ� �͸� �ٸ���.
 *
 * @sa BCIPHER_EncryptFile
 */
LIBSPEC_CE
ERT BCIPHER_DecryptFile_BSize(
		FILE *out, /**< [out] ��� ���� ����� ���� */
		BWT *outLen, /**< [out] ��� ���� ���� */
		FILE *in, /**< [in] �Է� ��ȣ���� ����� ���� */
		BWT inLen, /**< [in] �Է� ��ȣ���� ����Ʈ ���� (������ �Ϻ��� �� ����) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag, /**< [in] Padding ����, (NPAD, PAD, �� �� �� �ϳ�) */
		BWT bufSize /**< [in] ���� ���� ũ�� */
		);

/**
 * @brief ����(filename)�� ���ؼ� Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode

    �������̽��� BCIPHER_Encrypt()�� ���� ����ϸ�, ���� ����� �����Ͱ�
    filename�̶�� �͸� �ٸ���. inLen�� ��ȣȭ�� �������� ����Ʈ ���� ���̸�
    �ǹ��ϸ�, ���������� WHOLE_FILE�� �����Ͽ��� ���, file ��ü�� ��ȣȭ
    ����� �ȴ�. ������ ���׿� ���ؼ��� BCIPHER_Encrypt�� �����ϱ� �ٶ���.

 * @sa BCIPHER_Encrypt BCIPHER_DecryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_EncryptFilePath(
		const char *outfilepath, /**< [out] ��� ��ȣ���� ����� ���� */
		BWT *outLen, /**< [out] ��� ��ȣ���� ����Ʈ ���� */
		const char *infilepath, /**< [in] �Է� ���� ����� ���� */
		BWT inLen, /**< [in] �Է� ���� ����Ʈ ���� (������ �Ϻ��� �� ����) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding ����, (NPAD, PAD, �� �� �� �ϳ�) */
		);

/**
 * @brief ����(filename)�� ���ؼ� Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD cipher includes invalid padding bytes

    �������̽��� BCIPHER_Decrypt()�� ���� ����ϸ�, ���� ����� �����Ͱ�
    filename�̶�� �͸� �ٸ���. inLen�� ��ȣȭ�� �������� ����Ʈ ���� ���̸�
    �ǹ��ϸ�, ���������� WHOLE_FILE�� �����Ͽ��� ���, file ��ü�� ��ȣȭ
    ����� �ȴ�. ������ ���׿� ���ؼ��� BCIPHER_Decrypt�� �����ϱ� �ٶ���.

 * @sa BCIPHER_Decrypt BCIPHER_EncryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_DecryptFilePath(
		const char *outfilepath, /**< [out] ��� ���� ����� ���� */
		BWT *outLen, /**< [out] ��� ���� ����Ʈ ���� */
		const char *infilepath, /**< [in] �Է� ��ȣ���� ����� ���� */
		BWT inLen, /**< [in] �Է� ��ȣ���� ����Ʈ ���� (������ �Ϻ��� �� ����) */
		BCipherContext *bcipher, /**< [in] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding ����, (NPAD, PAD, �� �� �� �ϳ�) */
		);

/**
 * @brief ����(filename)�� Ư�� offset���� Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode

    �������̽��� BCIPHER_Encrypt()�� ���� ����ϸ�, ���� ����� �����Ͱ�
    filename�̶�� �͸� �ٸ���. inLen�� ��ȣȭ�� �������� ����Ʈ ���� ���̸�
    �ǹ��ϸ�, ���������� WHOLE_FILE�� �����Ͽ��� ���, file ��ü�� ��ȣȭ
    ����� �ȴ�. ������ ���׿� ���ؼ��� BCIPHER_Encrypt�� �����ϱ� �ٶ���.

 * @sa BCIPHER_Encrypt BCIPHER_DecryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_EncryptFilePath_Offset(
		const char *outfilepath, /**< [out] ��� ��ȣ���� ����� ���� */
		BWT *outLen, /**< [out] ��� ��ȣ���� ����Ʈ ���� */
		const char *infilepath, /**< [in] �Է� ���� ����� ���� */
		long offset, /**< [in] ��ȣȭ�� ������ offset */
		BWT inLen, /**< [in] �Է� ���� ����Ʈ ���� (������ �Ϻ��� �� ����) */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding ����, (NPAD, PAD, �� �� �� �ϳ�) */
		);

/**
 * @brief ����(filename)�� Ư�� offset���� Block cipher ��ȣȭ�� �����Ѵ�.
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD cipher includes invalid padding bytes

    �������̽��� BCIPHER_Decrypt()�� ���� ����ϸ�, ���� ����� �����Ͱ�
    filename�̶�� �͸� �ٸ���. inLen�� ��ȣȭ�� �������� ����Ʈ ���� ���̸�
    �ǹ��ϸ�, ���������� WHOLE_FILE�� �����Ͽ��� ���, file ��ü�� ��ȣȭ
    ����� �ȴ�. ������ ���׿� ���ؼ��� BCIPHER_Decrypt�� �����ϱ� �ٶ���.

 * @sa BCIPHER_Decrypt BCIPHER_EncryptFile, BCipherContext
 */
LIBSPEC_CE
ERT BCIPHER_DecryptFilePath_Offset(
		const char *outfilepath, /**< [out] ��� ���� ����� ���� */
		BWT *outLen, /**< [out] ��� ���� ����Ʈ ���� */
		const char *infilepath, /**< [in] �Է� ��ȣ���� ����� ���� */
		long offset, /**< [in] ��ȣȭ�� ������ offset */
		BWT inLen, /**< [in] �Է� ��ȣ���� ����Ʈ ���� (������ �Ϻ��� �� ����) */
		BCipherContext *bcipher, /**< [in] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding ����, (NPAD, PAD, �� �� �� �ϳ�) */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _BCIPHER_EXP_H_ */
