#ifndef _DSA_H_
#define _DSA_H_

/** @defgroup DSA
 * @ingroup PKCRYPT_ALG
 * @brief DSA (Digital Signature Algorithm)
 */

/** @file
    @ingroup DSA
    @brief DSA �˰����� ����ϱ� ���� �������̽� 
*/

#include <stdio.h>
#include "cc_define.h"
#include "mint_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup DSA
    @brief DSA ���� ����ü
    @sa DSAParam DSAPriKey

    DSASig�� DSA ���� ���� �� ���� �Լ����� DSA ������ ����� ��
    ����ϱ� ���� ����ü�̴�.
    DSA ������ �� ������(r, s)�̴�. 
*/    
typedef struct {
  MINT r;
  MINT s;
} DSASig;

/** @ingroup DSA
    @brief DSA �ý��� �Ķ���� ����ü
    @sa DSASig DSAPriKey

    DSA ���� �˰��򿡼� ����ϱ� ���� �ý��� �Ķ���Ͱ��� ��� �ִ�
    ����ü�̴�. �ý��� �Ķ���ʹ� p, q, g �� �����̴�.
*/    
typedef struct {
  MINT p;
  MINT q;
  MINT g;
} DSAParam;

/** @ingroup DSA
    @brief DSA ����Ű
    @sa DSAPriKey

    DSA�� ����Ű Ÿ���̴�.
*/    
typedef MINT  DSAPubKey;

/** @ingroup DSA
    @brief DSA �����Ű
    @sa DSAPubKey

    DSA�� �����Ű Ÿ���̴�.
*/    
typedef MINT  DSAPriKey;

/** @brief DSA �˰��� ����ü (PKCryptAlgorithm �� ����)
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
} DSADescriptor;

LIBSPEC
extern DSADescriptor pcis_dsa;

/** @ingroup DSA
    @brief DSA �˰��� descriptor�� dsa ���� ������ �ּҰ� rename
    */
#define DSA &pcis_dsa

#ifdef __cplusplus
}
#endif

#endif /* _DSA_H_ */  
