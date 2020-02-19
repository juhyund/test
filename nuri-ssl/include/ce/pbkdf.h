#ifndef _PBKDF_H_
#define _PBKDF_H_

/** @defgroup PBKDF Password-Based Key Derivation Function
 * @ingroup CKM
    @brief PBKDF(Password Based Key Derivation Fucntion) ���

    PBKDF(Password Based Key Derivation Function) ������ ���� �־���
    ��ȣ(password)�� ���� ������ Ű�� ���ϴ� ����� �Ѵ�.
    */

/** @ingroup PBKDF
    @file pbkdf.h
    @brief PBKDF ��� �������̽� ����
   */

#include "ckm_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PBKDF_MAX_PASSWORD_LEN  128
#define PBKDF_MAX_SALT_LEN      32
#define PBKDF_DEFAULT_SALT      "\x87\x56\x23\x06\x48\x32\x27\x14"
#define PBKDF_DEFAULT_SALT_LEN  8
#define PBKDF_DEFAULT_ITERATION 1353
#define PBKDF_DEFAULT_HASH_ALGORITHM  SHA1


/******************************************************************************
 * PKCS #5
 */

/** @ingroup PBKDF
    @brief PKCS5 �� password-based key derivation fuction - 1
    @param derivedKey [out] ������ Ű�� ����� ����
    @param dkLen [in] ������ Ű�� ����Ʈ ����
    @param passwd [in] password�� ��� �ִ� null-terminated string
    @param salt [in] salt�� ��� �ִ� ����
    @param saltLen [in] salt�� ����Ʈ ���� ����
    @param iteration [in] �˰��� �ݺ� ȸ��, PCS5_DEFAULT_ITERATION �� ���� �ٶ�.
    @param hashAlg [in] �� �Լ����� ����� hash �˰��� descriptor

    �� �Լ��� �־��� password�� ����Ͽ� Ű�� �����ϴ� �Լ��̴�. �Է����δ�
    password �̿ܿ� salt, iteration ���� �־����� �Ѵ�. �ᱹ, ���� �Է°���
    ��� ��ġ�ϸ� ���� derived key �� �����Ǵ� ���̴�.

    dkLen ��, ������ Ű�� ���̴� �� �Լ����� ����� �ؽ� �˰����� digest
    ���̿� ���ѵȴ�. ���� ���, SHA1�� ����� ���, digest ���̴� 20����Ʈ��
    �Ƿ� dkLen �� 20 ������ ���� ������ �Ѵ�. ���� �� �̻��� ���̸� �Է��ϸ�
    ������ ����ϰ� �ȴ�.

    @sa PBKDF_PKCS5_2
    */
LIBSPEC_CKM
ERT PBKDF_PKCS5_1( BYTE       *derivedKey, 
                   BWT         dkLen, /* < hLen */
                   const char *passwd,
                   const BYTE *salt,
                   BWT         saltLen,
                   BWT         iteration, 
                   const void *hashAlg);

/** @ingroup PBKDF
    @brief PKCS5 �� password-based key derivation fuction - 2
    @param derivedKey [out] ������ Ű�� ����� ����
    @param dkLen [in] ������ Ű�� ����Ʈ ����
    @param passwd [in] password�� ��� �ִ� null-terminated string
    @param salt [in] salt�� ��� �ִ� ����
    @param saltLen [in] salt�� ����Ʈ ���� ����
    @param iteration [in] �˰��� �ݺ� ȸ��, PCS5_DEFAULT_ITERATION �� ���� �ٶ�.
    @param hashAlg [in] �� �Լ����� ����� hash �˰��� descriptor
    
    �� �Լ��� �־��� password�� ����Ͽ� Ű�� �����ϴ� �Լ��̴�. �Է����δ�
    password �̿ܿ� salt, iteration ���� �־����� �Ѵ�. �ᱹ, ���� �Է°���
    ��� ��ġ�ϸ� ���� derived key �� �����Ǵ� ���̴�.

    ���������δ� PBKDF_PKCS5_1 �Լ��ʹ� �ٸ� �˰����� ������. �ܺ�������
    �ٸ� ���� ������ Ű�� ���̰� �ؽ� �˰����� digest ���̿� ���ѵ��� ��
    �´�. �̷������δ� (2^32 - 1) * length of digest �� ���� ������, 
    ������ �̷��� Ű ų�̰� �ʿ��� ���� ���� ���̴�.

    @sa PBKDF_PKCS5_1
    */
LIBSPEC_CKM
ERT PBKDF_PKCS5_2( BYTE       *derivedKey,
                   BWT         dkLen, /* < (2^32-1)*hLen */
                   const char *passwd,
                   const BYTE *salt,
                   BWT         saltLen, 
                   BWT         iteration, 
                   const void *hashAlg);

LIBSPEC_CKM
ERT PBKDF_PKCS5_2_old(BYTE       *derivedKey,
                      BWT         dkLen,
                      const char *passwd,
                      const BYTE *salt,
                      BWT         saltLen, 
                      BWT         iteration, 
                      const void *hashAlg);

/** @ingroup PBKDF
    @brief PKCS5 �� password-based key derivation fuction - 1
    @param derivedKey [out] ������ Ű�� ����� ����
    @param dkLen [in] ������ Ű�� ����Ʈ ����
    @param passwd [in] password�� ��� �ִ� null-terminated string
    @param salt [in] salt�� ��� �ִ� ����
    @param saltLen [in] salt�� ����Ʈ ���� ����
    @param iteration [in] �˰��� �ݺ� ȸ��, PCS5_DEFAULT_ITERATION �� ���� �ٶ�.
    @param hashAlg [in] �� �Լ����� ����� hash �˰��� descriptor

    �� �Լ��� �־��� password�� ����Ͽ� Ű�� �����ϴ� �Լ��̴�. �Է����δ�
    password �̿ܿ� salt, iteration ���� �־����� �Ѵ�. �ᱹ, ���� �Է°���
    ��� ��ġ�ϸ� ���� derived key �� �����Ǵ� ���̴�.

    OpenSSL �� EVP_BytesToKey �Լ��� �����ߴ�.
    ������ Ű�� ���� ������ ����.

    @sa PBKDF_PKCS5_2
    */
LIBSPEC_CKM
ERT PBKDF_PKCS5_OPENSSL( BYTE       *derivedKey, 
                   BWT         dkLen, /* < hLen */
                   BYTE       *derivedIv, 
                   BWT         diLen,
                   const char *passwd,
                   const BYTE *salt,
                   BWT         saltLen,
                   BWT         iteration, 
                   const void *hashAlg);

/******************************************************************************
 * PKCS #12
 */

/** 
    @def PBKDF_PKCS12_ID_ENCKEY 
    @ingroup PBKDF

    PKCS #12 ����� Ű ���� �Լ��� ���, ���� password�� 
    �Ķ����(salt�� iteration ��)�� ���Ͽ� ���� �ٸ� ��������
    Ű�� ������ �� �ִ�.
    ��ȣȭ�� Ű, �ʱ� ����, �׸��� ���Ἲ Ȯ�ο� Ű�� �װ��ε�,
    ������ ��ȣȭ�� ���ؼ� ����� Ű�� �����ϰ� ���� ��쿡��
    �Լ� \e PBKDF_PKCS12�� �Է����� PKCS12_ID_ENCKEY�� �ش�.

    @sa PBKDF_PKCS12 PBKDF_PKCS12_ID_IV PBKDF_PKCS12_ID_MACKEY
*/
/** 
    @def PBKDF_PKCS12_ID_IV
    @ingroup PBKDF

    PKCS #12 ����� Ű ���� �Լ����� ��ȣȭ �Ǵ� ��ȣȭ�� ����
    �ʱ� ���͸� ����� ���� ���ؼ��� �Լ� \e PBKDF_PKCS12�� �Է����� 
    PKCS12_ID_IV�� �ش�.

    @sa PBKDF_PKCS12 PBKDF_PKCS12_ID_ENCKEY PBKDF_PKCS12_ID_MACKEY
*/
/** 
    @def PBKDF_PKCS12_ID_MACKEY
    @ingroup PBKDF

    PKCS #12 ����� Ű ���� �Լ����� ���Ἲ ������ ���� MAC�� Ű�� ����
    ���ؼ��� �Լ� \e PBKDF_PKCS12�� �Է����� PKCS12_ID_MACKEY�� �ش�.

    @sa PBKDF_PKCS12 PBKDF_PKCS12_ID_ENCKEY PBKDF_PKCS12_ID_IV
*/
#define PBKDF_PKCS12_ID_ENCKEY  1
#define PBKDF_PKCS12_ID_IV      2
#define PBKDF_PKCS12_ID_MACKEY  3


/**
    @ingroup PBKDF
    @brief PKCS #12��Ŀ� ���� Ű ���� �Լ�. ������ ���� �߻���
    @param derivedKey [out] �Է����� �־��� password, salt, iterations ���� ���ʷ�
           ������ Ű ��.
    @param dkLen [in] ���ϰ��� �ϴ� Ű�� ����Ʈ ����
    @param pKCS12_ID [in] �����ϰ��� �ϴ� Ű�� ��� �뵵������ ǥ���ϴ� ������
           \b PBKDF_PKCS12_ID_ENCKEY, \b PBKDF_PKCS12_ID_IV, 
           \b PBKDF_PKCS12_ID_MACKEY�� ����� �� �ִ�.
           ������ �Ϻ�ȣȭ�� ���� Ű, �Ϻ�ȣȭ ��� ����� �ʱ⺤��, �׸���
           ���Ἲ�� Ȯ���ϱ� ���� MAC�� Ű�� ����� ��쿡 ���� ����Ѵ�.
    @param password [in] Ű ������ �Է��� �Ǵ� �н�����. Null-terminated ��Ʈ�� ���� 
    @param salt [in] ���� password��� �� ���� salt�� �ٸ� ��� �ٸ� Ű ���� �����ȴ�.
    @param saltLen [in] �־��� salt�� ����Ʈ ����
    @param iterations [in] ���ο��� ����ϴ� Ű ���� ������ ������ ���� ����� �ݺ�����
           �̷�� ���µ�, salt�� �Բ� Ű ���� �����ϴ� �Ķ���� ������ �Ѵ�.
           ����, iterations�� ��� 1000�̻��� ���� ���� ���� �ٶ����ϴ�.

    �־��� derivedKey(��Ʈ ����)�� ���� �� �ִ� �ּ����� ����Ʈ ���� ��ŭ��
    Ű ��(������ ������)�� derivedKey�� ��µȴ�. �뵵�� ���� pKCS12_ID�� �Է��ؾ�
    �ϸ�, Ű ���� password, salt, iterations�� ���� �����ȴ�.

    @sa PBKDF_PKCS12_UniCode
*/
LIBSPEC_CKM
ERT PBKDF_PKCS12( BYTE       *derivedKey, 
                  BWT         dkLen, 
                  BWT         idByte, 
                  const char *passwd, 
                  const BYTE *salt, 
                  BWT         saltLen,
                  BWT         iterations,
                  const void *hashAlg);

/** 
    @ingroup PBKDF
    @brief PBKDF_PKCS12�� ������ ������ ����� ���´�. ������, �Է����� �־�����
           password�� Uni-Code������ ��쿡 ����Ѵ�.
    @param derivedKey [out] �Է����� �־��� password, salt, iterations ���� ���ʷ�
           ������ Ű ��.
    @param dkLen [in] ���ϰ��� �ϴ� Ű�� ����Ʈ ����
    @param pKCS12_ID [in] �����ϰ��� �ϴ� Ű�� ��� �뵵������ ǥ���ϴ� ������
           \b PBKDF_PKCS12_ID_ENCKEY, \b PBKDF_PKCS12_ID_IV,
           \b PBKDF_PKCS12_ID_MACKEY�� ����� �� �ִ�.
           ������ �Ϻ�ȣȭ�� ���� Ű, �Ϻ�ȣȭ ��� ����� �ʱ⺤��, �׸���
           ���Ἲ�� Ȯ���ϱ� ���� MAC�� Ű�� ����� ��쿡 ���� ����Ѵ�.
    @param password [in] Ű ������ �Է��� �Ǵ� �н�����. Unicode ����
    @param passwordLen [in] password�� ����Ʈ���� ����
    @param salt [in] ���� password��� �� ���� salt�� �ٸ� ��� �ٸ� Ű ���� �����ȴ�.
    @param saltLen [in] �־��� salt�� ����Ʈ ����
    @param iterations [in] ���ο��� ����ϴ� Ű ���� ������ ������ ���� ����� �ݺ�����
           �̷�� ���µ�, salt�� �Բ� Ű ���� �����ϴ� �Ķ���� ������ �Ѵ�.
           ����, iterations�� ��� 1000�̻��� ���� ���� ���� �ٶ����ϴ�.

    �Լ��� �Ķ���ʹ� PBKDF_PKCS12�� �Ѱ����� �����ϰ� ������ ��ġ�Ѵ�.
    password�� ��� Null-terminated ��Ʈ���� �ƴϱ� ������ ���̸�
    �Է��� �ִ� ���� �߰��Ǿ���.

    @sa PBKDF_PKCS12
*/
LIBSPEC_CKM
ERT PBKDF_PKCS12_UniCode( BYTE       *derivedKey, 
                          BWT         dkLen, 
                          BWT         idByte,
                          const BYTE *passwd, 
                          BWT         passwdLen,
                          const void *salt, 
                          BWT         saltLen,
                          BWT         iterations,
                          const void *hashAlg);

#ifdef __cplusplus
}
#endif

#endif   /* _PBKDF_H_ */
