#ifndef _PKCRYPT_OP_H_
#define _PKCRYPT_OP_H_

/** @defgroup PKCRYPT Public-Key Cryptography
 * @ingroup CC
 * @brief Public-Key Cryptography
 */ 

/** @defgroup PKCRYPT_ALG Algorithm Descriptors
 * @ingroup PKCRYPT
 * @brief PKCRYPT Algorithm Descriptors
 */

/** @file pkcrypt_op.h
 * @ingroup PKCRYPT
 */

#include <stdio.h>
#include "cc_define.h"
#include "mint_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup PKCRYPT
    @brief PKCryptAlgorithm ����ü

		�˰��� descriptor, �˰����� ������ ������ �ִ�. �� ����ü�� �����
    �� �˰��� ��� ���ο��� �����Ǵ� ������ ����ڰ� ���Ƿ� ������ �����ϸ�
    �ȵȴ�. ���� �����Ǵ� descriptor�δ� KCDSA, KCDSA1, RSA, DSA, ECDSA, ECKCDSA �� �ִ�.
*/
typedef struct {
  ERT   (*signFunc)(); /**< ���� ���� �Լ� ������ */
  ERT   (*verifyFunc)(); /**< ���� ���� �Լ� ������ */
  ERT   (*signFileFunc)(); /**< ���� ���� �Լ� ���� ������ */
  ERT   (*verifyFileFunc)(); /**< ���� ���� ���� �Լ� ������ */
  ERT   (*encFunc)(); /**< ��ȣȭ �Լ� ������ */
  ERT   (*decFunc)(); /**< ��ȣȭ �Լ� ������ */
  ERT   (*genParam)(); /**< �Ķ���� ���� �Լ� ������ */
  ERT   (*genKey)(); /**< Ű ���� �Լ� ������ */
  ERT   (*checkParam)(); /**< �Ķ���� ��ȿ�� ���� �Լ� ������ */
  ERT   (*checkKey)(); /**< Ű ��ġ Ȯ�� �Լ� ������ */
  ERT   (*checkKeyPair)(); /**< ����Ű ����ü �� ����Ű�� ����Ű ��ġ Ȯ�� �Լ� ������ */
  BWT     priKeySize; /**< ����Ű�� ����Ʈ ũ��*/
  BWT     pubKeySize; /**< ����Ű�� ����Ʈ ũ�� */ 
  BWT     paramSize; /**< �Ķ������ ����Ʈ ũ�� */ 
  BWT     sigSize; /**< ���� ���� ����Ʈ ũ�� */ 
  BWT     idx; /**< KCDSA�� �ƴ� ��� 0, KCDSA�� ���, old version = 1, new version = 2*/

  ERT   (*signHashFunc)(); /**< �ؽ� ���� ���� ���� ���� �Լ� ������ */
  ERT   (*verifyHashFunc)(); /**< �ؽ� ���� ���� ���� ���� �Լ� ������ */
} PKCryptAlgorithm;

/** @brief ����Ű ���� ���� �ִ� ����Ʈ ���� */
#define PKCRYPT_MAX_SIG_LEN (MINT_SIZE<<1)

/** @ingroup PKCRYPT
    @brief ������ �ǹ��ϴ� ����ü
*/
typedef struct {
  AlgDesc alg;
  BYTE val[PKCRYPT_MAX_SIG_LEN];
} PKCryptSig;

struct _pkc_data {
  AlgDesc alg; /**< �˰��� ������ */
  void *val; /**< ������(ex. ���Ű, ����Ű, ��) */
}; 


/** @ingroup PKCRYPT
    @brief ������ �Ķ���͸� �ǹ��ϴ� ����ü
*/
typedef struct _pkc_data PKCryptParam;

/** @ingroup PKCRYPT
    @brief �����Ű�� �ǹ��ϴ� ����ü
*/
typedef struct _pkc_data PKCryptPriKey;

/** @ingroup PKCRYPT
    @brief ����Ű�� �ǹ��ϴ� ����ü
*/
typedef struct _pkc_data PKCryptPubKey;

/** @ingroup PKCRYPT
    @brief ������ �Ķ���� ����ü�� PKCryptParam�� �Ҵ��Ѵ�.
    @param[in]  pkAlg �˰��� descriptor
    @return [out] �Ҵ�� ����ü�� �����Ͱ��� ����
    @sa PKCRYPT_DelParam PKCRYPT_NewPriKey PKCRYPT_NewPubKey

    �˰��� descriptor�� �Է� �޾�, �˰��� �ش��ϴ�
    ������ �Ķ����, PKCryptParam ����ü�� �Ҵ��Ͽ� �����͸� �����Ѵ�.

    �˰��� descriptor�� �˰����� ���� ������ ��� �ִ� global ����ü
    �ν��Ͻ��μ�, KCDSA, KCDSA1, RSA, DSA�� �����Ѵ�.
*/
LIBSPEC
PKCryptParam*  PKCRYPT_NewParam(AlgDesc pkAlg);

/** @ingroup PKCRYPT
    @brief �޸𸮿� �Ҵ�� PKCryptParam ����ü�� �����Ѵ�.
    @param[in]  param PKCryptParam ����ü�� �����Ͱ�
    @sa PKCRYPT_NewParam PKCRYPT_DelPriKey PKCRYPT_DelPubKey

*/
LIBSPEC
void PKCRYPT_DelParam(PKCryptParam *param);

/** @ingroup PKCRYPT
    @brief �����Ű ����ü�� PKCryptPriKey�� �Ҵ��Ѵ�.
    @param[in]  pkAlg �˰��� descriptor
    @return [out] �Ҵ�� ����ü�� �����Ͱ��� ����
    @sa PKCRYPT_DelPriKey PKCRYPT_NewParam PKCRYPT_NewPubKey

    �˰��� descriptor�� �Է����� �޾�, �˰��� �ش��ϴ�
    �����Ű�� PKCryptPriKey ����ü�� �Ҵ��Ͽ� �����͸� �����Ѵ�.
*/
LIBSPEC
PKCryptPriKey* PKCRYPT_NewPriKey(AlgDesc pkAlg);

/** @ingroup PKCRYPT
    @brief �޸𸮿� �Ҵ�� PKCryptPriKey ����ü�� ����ȭ�ϰ�, �����Ѵ�.
    @sa PKCRYPT_NewPriKey PKCRYPT_DelParam PKCRYPT_DelPubKey
*/
LIBSPEC
void PKCRYPT_DelPriKey(
		PKCryptPriKey *priKey /**< [in] PKCryptPriKey ����ü�� �����Ͱ� */
		);

/** @ingroup PKCRYPT
    @brief ����Ű ����ü�� PKCryptPubKey�� �Ҵ��Ѵ�.
    @param pkAlg [in] �˰��� descriptor
    @return [out] �Ҵ�� ����ü�� �����Ͱ��� ����
    @sa PKCRYPT_DelPriKey PKCRYPT_NewParam PKCRYPT_NewPriKey

    �˰��� descriptor�� �Է����� �޾�, �˰��� �ش��ϴ�
    ����Ű�� PKCryptPubKey ����ü�� �Ҵ��Ͽ� �����͸� �����Ѵ�.
*/
LIBSPEC
PKCryptPubKey* PKCRYPT_NewPubKey(AlgDesc pkAlg);

/** @ingroup PKCRYPT
    @brief �޸𸮿� �Ҵ�� PKCryptPubKey ����ü�� ����ȭ�ϰ�, �����Ѵ�.
    @sa PKCRYPT_NewPubKey PKCRYPT_DelParam PKCRYPT_DelPriKey
*/
LIBSPEC
void PKCRYPT_DelPubKey(
		PKCryptPubKey *pubKey /**< [in] public key to be deleted */
		);

/** @ingroup PKCRYPT
    @brief �Ķ���� ���� �Լ�
    @sa PKCRYPT_CheckParam PKCRYPT_GenKey PKCRYPT_CheckKey
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��

    �������� ���� �Ķ���͸� �����Ѵ�. param�� Param ����ü�̸�,
    �� �˰��򺰷�, DSAParam, KCDSAParam �� ����ü ������
    �ԷµǾ�� �Ѵ�.
*/
LIBSPEC
ERT PKCRYPT_GenParam(
		PKCryptParam *param, /**< [in,out] ������ �Ķ���� */
		BWT pBitLen, /**< [in] p�� ��Ʈ ���� */
		BWT qBitLen /**< [in] q�� ��Ʈ ���� */
		);

/** @ingroup PKCRYPT
 * @return [out] check result
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @brief �Ķ���� ���� �Լ�
    @sa PKCRYPT_GenParam PKCRYPT_GenKey PKCRYPT_CheckKey

    param �� ����� ������ ������ ��ȿ�� ���������� �����Ѵ�.
*/
LIBSPEC
ERT PKCRYPT_CheckParam(
		const PKCryptParam *param /**< [in] parameter to be checked */
		);

/** @ingroup KEYGEN
    @brief Ű ���� �Լ�
    @sa PKCRYPT_GenParam PKCRYPT_CheckParam PKCRYPT_CheckKey
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @retval ER_CONDITIONAL_SELFTEST Ű�� ��ġ ���� �����Ͽ��� ���

    Private/Public key pair�� �����ϴ� �Լ��̴�. ������ ������ ������
    �˰��� Param(DsaParam, KcdsaParam, RsaParam) ����ü�� �˰���
    descriptor�� �Է��ϸ�, priKey�� pubKey�� ������ key pair�� ����ȴ�.
    priKey�� pubKey�� �� �˰����� key ����ü�� �����Ͱ��̴�.

    RSA�� ����� ���, dlParam = NULL, rsaNLen = |n|�� �Է��ϰ�,
    �̿��� ���, rsaNLen = 0�� �Է��ؾ��Ѵ�.
*/
LIBSPEC
ERT PKCRYPT_GenKey(
		PKCryptPriKey *priKey, /**< [in,out] generated private key */
		PKCryptPubKey *pubKey, /**< [in,out] generated public key */
		const PKCryptParam *dlParam, /**< [in] parameter for discret
									   logarithm-based algorithms */
		BWT rsaNLen /**< [in] desired modulus length for RSA algorithm */
		);

/** @ingroup PKCRYPT
    @brief Ű ��ȿ�� ���� �Լ�
	@return [out] check result
    @param[in]  priKey private key
    @param[in]  pubKey public key
    @param[in]  param Param ����ü
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @sa PKCRYPT_GenParam PKCRYPT_CheckParam PKCRYPT_GenKey PKCRYPT_CheckKeyPair

    Private/Public key�� ��ȿ�� key������ �����Ѵ�. PKCRYPT_CheckKeyPair�� ����
    �ϴ� Ű���� �´� ��(����Ű �� ����Ű�� ����Ű�� ��ġ�ϴ���)�� ���ο� ���� Ȯ�ε� ���Եȴ�.
*/
LIBSPEC
ERT PKCRYPT_CheckKey(const PKCryptPriKey *priKey,
                     const PKCryptPubKey *pubKey,
                     const PKCryptParam  *param);

/** @ingroup PKCRYPT
    @brief ����Ű ���� �����Լ� 
	@param[out]  sig ���� ������ ������
	@param[in]  msg ������ �޽��� ������ ����Ʈ ������
	@param[in]  msgLen ������ �޽��� ������ ����Ʈ ���� ����
	@param[in]  priKey �������� �����Ű ����ü�� ������
    @param[in]  param ������ �Ķ���� ����ü�� ������
	@param[in]  hashAlg Hash �˰����� descriptor
    @param[in]  kcdsaPubInfo KCDSA�� ����� ��� ���� ����
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @retval ER_RSA_ENCODING_ERROR RSA�� ���ڵ� ������ �߸��Ǿ��� ��
	@sa PKCRYPT_Verify, PKCRYPT_Verify, PKCRYPT_Decrypt, PKCRYPT_Create, PKCRYPT_Delete

		������ �޽��� ����, �������� �����Ű ����,
    �ؽ� �˰��� descriptor �Է����� �޾� ���� ������ �����͸� �����Ѵ�.

    kcdsaPubInfo�� KCDSA�� ����� ��쿡 �ʿ��� ���� �����̴�. �� ������
    KCDSA�� (descriptor KCDSA1) �������� ����Ű(PKCryptPubKey)�� �����͸�
    �Ѱ� �ְ�, ���� ������ KCDSA ����(descriptor KCDSA) �������� ����Ű
    �������� hash�� ���� ����� ����Ʈ ������ �����͸� �Ѱ� �ְ� �ȴ�.
    
		�˰��� ���� ���� Ÿ��, �����Ű Ÿ���� ���Ǵ� �� �˰��� ��� ������
    �����Ѵ�.
		
*/
LIBSPEC
ERT PKCRYPT_Sign(       PKCryptSig     *sig,
                  const BYTE           *msg, 
                        BWT             msgLen,
                  const PKCryptPriKey  *priKey,
                  const PKCryptParam   *param,
                        AlgDesc         hashAlg,
                  const void           *kcdsaPubInfo);
  
/** @ingroup PKCRYPT
    @brief ����Ű ���� �����Լ� 
	@param[in]  sig ���� ������ ������
	@param[in]  msg ���� ������ �޽��� ������ ����Ʈ ������
	@param[in]  msgLen ���� ������ �޽��� ������ ����Ʈ ���� ����
	@param[in]  pubKey �������� ����Ű ����ü�� ������
    @param[in]  param ������ �Ķ���� ����ü�� ������
	@param[in]  hashAlg Hash �˰����� descriptor
    @param[in]  kcdsaPubInfo KCDSA�� ����� ��� ���� ����
	@return [out] verification result
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @retval ER_RSA_VP1_SIG_OUT_OF_RANGE RSA �� ���� ���� �ùٸ��� ���� ��
    @retval ER_RSA_INCONSISTENT RSA �� ���� ���� ����� ���� ���� ����� ����ġ�� ��
    @retval ER_KCDSA_VP_SIG_OUT_OF_RANGE KCDSA �� ���� ���� �ùٸ��� ���� ��
	@sa PKCRYPT_Sign, PKCRYPT_Verify, PKCRYPT_Decrypt, PKCRYPT_Create, PKCRYPT_Delete

		���� ������ ������, ���� �������� �޽��� ����, �������� ����Ű ����,
    �ؽ� �˰��� descriptor�� �Է����� �޾� ���� ���� ����� �����Ѵ�.
   
    kcdsaPubInfo�� KCDSA�� ����� ��쿡 �ʿ��� ���� �����̴�. �� ������
    KCDSA(descriptor KCDSA1)�� �������� ����Ű�� �ǹǷ�, ������ �Է���
    �ʿ���� NULL���� �ѱ��. ���� ������ KCDSA(descriptor KCDSA)�� ��쿡��
    PKCRYPT_Sign�� ���������� �������� ����Ű �������� hash�� ���� �����
    ����Ʈ ������ �����͸� �Ѱ� �־�� �Ѵ�.
*/
LIBSPEC
ERT PKCRYPT_Verify( const PKCryptSig     *sig,
                    const BYTE           *msg,
                          BWT             msgLen,
                    const PKCryptPubKey  *pubKey,
                    const PKCryptParam   *param,
                          AlgDesc         hashAlg,
                    const void           *kcdsaPubInfo);

/** @ingroup PKCRYPT
    @brief ����Ű ��ȣȭ �Լ� 
	@param cipher [out] ��ȣȭ�� ����� ����� ���۸� ����Ű�� ������
	@param cipherLen [in,out] IN: cipher�� �޸� ���� ũ��, OUT: ��ȣȭ�� ����� ����Ʈ ���� ���̰� ����
	@param plain [in]  ��ȣȭ�� �����Ͱ� ����Ǿ� �ִ� ���۸� ����Ű�� ������
	@param plainLen [in]  ��ȣȭ�� �������� ����Ʈ ���� ����
	@param pubKey [in]  ����Ű ����ü�� ������
    @param param [in] ������ �Ķ���� ����ü�� ������
	@param hashAlg [in]  Hash �˰����� descriptor
	@param maskAlg [in]  Mask �˰����� descriptor; ���� ���� ����, ����� NULL�� �Է��Ͽ� ���
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL �Լ� ����� ����� �Ķ������ �޸� ���� ũ�Ⱑ ���� ��
    @retval ER_RSA_MESSAGE_TOO_LONG RSA �� �޽����� �� ��

    @sa PKCRYPT_Decrypt, PKCRYPT_Sign, PKCRYPT_Verify, PKCRYPT_Create, PKCRYPT_Delete

		��(plain), ����Ű ����, �ؽ� �˰��� descriptor, Mask �˰���
    descriptor�� �Է����� �޾� ��ȣȭ�ϰ� ��ȣ��(cipher)�� ����Ѵ�.
    
    maskAlg�� ��ȣȭ�� �ʿ��� mask algorithm�� �����ϱ� ���� ������ ����
    Ȯ���� ���Ͽ� �����ϴ� parameter�̴�. ����� NULL���� �ֱ� �ٶ���.
*/
LIBSPEC
ERT PKCRYPT_Encrypt(       BYTE           *cipher,
                           BWT            *cipherLen,
                     const BYTE           *plain,
                           BWT             plainLen,
                     const PKCryptPubKey  *pubKey,
                     const PKCryptParam   *param,
                           AlgDesc         hashAlg,
                     const void           *maskAlg);

/** @ingroup PKCRYPT
    @brief ����Ű ��ȣȭ �Լ� 
	@param plain [out] ��ȣȭ�� ����� ����� ���۸� ����Ű�� ������
	@param plainLen [in,out] IN: plain�� �޸� ���� ũ��, OUT: ��ȣȭ�� ����� ����Ʈ ���� ���̰� ����
	@param cipher [in] ��ȣȭ�� �����Ͱ� ����Ǿ� �ִ� ���۸� ����Ű�� ������
	@param cipherLen [in] ��ȣȭ�� �������� ����Ʈ ���� ����
	@param priKey [in] �����Ű ����ü�� ������
    @param param [in] ������ �Ķ���� ����ü�� ������
	@param hashAlg [in] Hash �˰����� descriptor
	@param maskAlg [in] Mask �˰����� descriptor; ���� ���� ����, ����� NULL�� �Է��Ͽ� ���
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @retval ER_OUT_BUFFER_SIZE_IS_SMALL �Լ� ����� ����� �Ķ������ �޸� ���� ũ�Ⱑ ���� ��
    @retval ER_RSA_WRONG_CIPHER_LEN The length of cipher is wrong
    @retval ER_RSA_DECRYPT_ERROR RSA �� ��ȣȭ ������ �߸��Ǿ��� ��
	@sa PKCRYPT_Encrypt, PKCRYPT_Sign, PKCRYPT_Verify, PKCRYPT_Create, PKCRYPT_Delete

		��ȣ��(cipher), ����Ű ����, �ؽ� �˰��� descriptor, Mask �˰���
    descriptor�� �Է����� �޾� ��ȣȭ�ϰ� ��(plain)�� ����Ѵ�.
    
    maskAlg�� ��ȣȭ�� �ʿ��� mask algorithm�� �����ϱ� ���� ������ ����
    Ȯ���� ���Ͽ� �����ϴ� parameter�̴�. ����� NULL���� �ֱ� �ٶ���.
*/
LIBSPEC
ERT PKCRYPT_Decrypt(       BYTE           *plain,
                           BWT            *plainLen,
                     const BYTE           *cipher,
                           BWT             cipherLen,
                     const PKCryptPriKey  *priKey,
                     const PKCryptParam   *param,
                           AlgDesc         hashAlg,
                     const void           *maskAlg);

#ifdef __cplusplus
}
#endif

#endif /* _PKCRYPT_OP_H_ */  

