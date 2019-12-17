#ifndef _KCDSA_H_
#define _KCDSA_H_

/** @defgroup KCDSA
 * @ingroup PKCRYPT_ALG
 * @brief KCDSA (Korean Certificate-based Digital Signature Algorithm)
 */

/** @file kcdsa.h
    @ingroup KCDSA
    @brief KCDSA �˰����� ����ϱ� ���� �������̽�
*/

#include <stdio.h>
#include "cc_define.h"
#include "mint_common.h"
#include "hash_op.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KCDSA_PARAM_MAX_Q_SIZE 32
#define KCDSA_PARAM_MAX_J_SIZE 228

/** @ingroup KCDSA
    @brief KCDSA ���� ����ü
    @sa KCDSAParam, KCDSAPriKey

    KCDSASig�� KCDSA ���� ���� �� ���� �Լ����� KCDSA ������ ����� ��
    ����ϱ� ���� ����ü�̴�. KCDSA ������ �� ������(r, s)�̴�.
*/
typedef struct {
  BYTE r[HASH_MAX_DIGEST_SIZE];
  MINT s;
} KCDSASig;

/** @ingroup KCDSA
    @brief KCDSA �ý��� �Ķ���� ����ü
    @sa KCDSASig,KCDSAPriKey

    KCDSAParam�� KCDSA ���� ���� �� ���� �Լ����� KCDSA �ý��� �Ķ���͵���
    ����� �� ����ϱ� ���� ����ü�̴�.  �ý��� �Ķ���ʹ� p, q, g�� �ִ�.
*/
typedef struct {
  MINT p; /**< KCDSA �ý��� �Ķ���� p */
  MINT q; /**< KCDSA �ý��� �Ķ���� q */
  MINT g; /**< KCDSA �ý��� �Ķ���� g */
  BYTE seed[KCDSA_PARAM_MAX_Q_SIZE]; /**< �Ķ���� ������ ���Ǵ� seed */
  BYTE j[KCDSA_PARAM_MAX_J_SIZE]; /**< �Ķ���� ���� �� PRNG���� ������ J */
  BYTE XKEY[KCDSA_PARAM_MAX_Q_SIZE]; /**< Ű ���� �� ���� XKEY */
  BYTE gbuf[256]; /**< ������ G */
  BYTE OUPRI[KCDSA_PARAM_MAX_Q_SIZE]; /**< Ű ���� �� PRNG ��� */
  BWT  jLen; /**< j�� ����Ʈ ���� */
  BWT  seedLen; /**< seed�� ����Ʈ ���� = q/8 */
  BWT  count; /**< �Ķ���� ������ ���Ǵ� Count */
} KCDSAParam;

/** @ingroup KCDSA
    @brief KCDSA ����Ű
    @sa KCDSAPriKey

    KCDSA�� ����Ű Ÿ���̴�.
*/    
typedef MINT  KCDSAPubKey;

/** @ingroup KCDSA
    @brief KCDSA �����Ű
    @sa KCDSAPubKey

    KCDSA�� �����Ű Ÿ���̴�.
*/    
typedef MINT  KCDSAPriKey;

/** @brief KCDSA �˰��� ����ü (PKCryptAlgorithm �� ����)
 *  @sa PKCryptAlgorithm
 */
typedef struct {
  ERT   (*signFunc)();
  ERT   (*verifyFunc)();
  ERT   (*signFileFunc)();
  ERT   (*verifyFileFunc)();
  ERT   (*encFunc)();
  ERT   (*decFunc)();
  ERT   (*genParam)();
  ERT   (*genKey)();
  ERT   (*checkParam)();
  ERT   (*checkKey)();
  ERT   (*checkKeyPair)();
  BWT     priKeySize;
  BWT     pubKeySize;
  BWT     paramSize;
  BWT     sigSize;
  BWT     idx;
  
  ERT   (*signHashFunc)();
  ERT   (*verifyHashFunc)();
} KCDSADescriptor;

LIBSPEC
extern KCDSADescriptor popkcdsa;

LIBSPEC
extern KCDSADescriptor pcis_kcdsa;

/** @ingroup KCDSA
    @brief KCDSA �˰��� descriptor�� pcis_kcdsa ���� ������ �ּҰ� rename
*/
#define KCDSA   &pcis_kcdsa

/** @ingroup KCDSA
    @brief KCDSA0 �˰��� descriptor�� popkcdsa ���� ������ �ּҰ� rename
*/
#define KCDSA0  &popkcdsa

#ifdef __cplusplus
}
#endif

#endif
