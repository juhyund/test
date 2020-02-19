#ifndef _PKCRYPT_EXP_H_
#define _PKCRYPT_EXP_H_

/** @defgroup PKCRYPT Public-Key Cryptography Expand
 * @ingroup CE
 * @brief Public-Key Cryptography Expand function
 */ 

#include <stdio.h>
#include "pkcrypt_op.h"

#ifdef EXPORT_CE
#include "ce_dll.h"
#else
#define LIBSPEC_CE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup PKCRYPT
    @brief Ű�� Ȯ�� �Լ�
	@return [out] check result
    @param[in]  priKey private key
    @param[in]  pubKey public key
    @param[in]  param Param ����ü
    @sa PKCRYPT_CheckKey

    Private/Public key�� ���� ���� �´� ��(����Ű �� ����Ű�� ����Ű�� ��ġ�ϴ���)�� Ȯ���Ѵ�.
*/
LIBSPEC_CE
ERT PKCRYPT_CheckKeyPair(const PKCryptPriKey *priKey,
                         const PKCryptPubKey *pubKey,
                         const PKCryptParam  *param);

/** @ingroup PKCRYPT */
LIBSPEC_CE
ERT PKCRYPT_SignHash(       PKCryptSig     *sig, /**< [out] */
                      const BYTE           *hash,  /**< [in] */
                            BWT             hashLen, /**< [in] */
                      const PKCryptPriKey  *priKey, /**< [in] */
                      const PKCryptParam   *param, /**< [in] */
                            AlgDesc         hashAlg, /**< [in] */
                      const void           *kcdsaPub /**< [in] */
					  );

/** @ingroup PKCRYPT */
LIBSPEC_CE  
ERT PKCRYPT_VerifyHash( const PKCryptSig     *sig, /**< [in] */
                        const BYTE           *hash, /**< [in] */
                              BWT             hashLen, /**< [in] */
                        const PKCryptPubKey  *pubKey, /**< [in] */
                        const PKCryptParam   *param, /**< [in] */
                              AlgDesc         hashAlg, /**< [in] */
                        const void           *kcdsaPub /**< [in] */
						);

/** @ingroup PKCRYPT
    @brief ����Ű ���� �����Լ� 
		@param sig [out] ���� ������ ������
		@param msg [in] ������ �޽��� ������ ����Ʈ ������
		@param msgLen [in] ������ �޽��� ������ ����Ʈ ���� ����
		@param priKey [in] �������� �����Ű ����ü�� ������
    @param param [in] ������ �Ķ���� ����ü�� ������
		@param hashAlg [in] Hash �˰����� descriptor
    @param kcdsaPubInfo [in] KCDSA�� ����� ��� ���� ����
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
LIBSPEC_CE
ERT PKCRYPT_SignFile(       PKCryptSig     *sig,
                            FILE           *msg, 
                            BWT             msgLen,
                      const PKCryptPriKey  *priKey,
                      const PKCryptParam   *param,
                            AlgDesc         hashAlg,
                      const void           *kcdsaPubInfo);
  
/** @ingroup PKCRYPT
    @brief ����Ű ���� �����Լ� 
		@param sig [in] ���� ������ ������
		@param msg [in] ���� ������ �޽��� ������ ����Ʈ ������
		@param msgLen [in] ���� ������ �޽��� ������ ����Ʈ ���� ����
		@param pubKey [in] �������� ����Ű ����ü�� ������
    @param param [in] ������ �Ķ���� ����ü�� ������
		@param hashAlg [in] Hash �˰����� descriptor
    @param kcdsaPubInfo [in] KCDSA�� ����� ��� ���� ����
	@return [out] verification result
    @retval ER_PKCRYPT_VERIFY_SIG_OUT_OF_RANGE signature value is out of range
		@sa PKCRYPT_Sign, PKCRYPT_Verify, PKCRYPT_Decrypt, PKCRYPT_Create, PKCRYPT_Delete

		���� ������ ������, ���� �������� �޽��� ����, �������� ����Ű ����,
    �ؽ� �˰��� descriptor�� �Է����� �޾� ���� ���� ����� �����Ѵ�.
   
    kcdsaPubInfo�� KCDSA�� ����� ��쿡 �ʿ��� ���� �����̴�. �� ������
    KCDSA(descriptor KCDSA1)�� �������� ����Ű�� �ǹǷ�, ������ �Է���
    �ʿ���� NULL���� �ѱ��. ���� ������ KCDSA(descriptor KCDSA)�� ��쿡��
    PKCRYPT_Sign�� ���������� �������� ����Ű �������� hash�� ���� �����
    ����Ʈ ������ �����͸� �Ѱ� �־�� �Ѵ�.
*/
LIBSPEC_CE
ERT PKCRYPT_VerifyFile( const PKCryptSig     *sig,
                              FILE           *msg,
                              BWT             msgLen,
                        const PKCryptPubKey  *pubKey,
                        const PKCryptParam   *param,
                              AlgDesc         hashAlg,
                        const void           *kcdsaPubInfo);

#ifdef __cplusplus
}
#endif

#endif /* _PKCRYPT_EXP_H_ */  

