#ifndef _DSA_H_
#define _DSA_H_

/** @defgroup DSA
 * @ingroup PKCRYPT_ALG
 * @brief DSA (Digital Signature Algorithm)
 */

/** @file
    @ingroup DSA
    @brief DSA 알고리즘을 사용하기 위한 인터페이스 
*/

#include <stdio.h>
#include "cc_define.h"
#include "mint_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup DSA
    @brief DSA 서명값 구조체
    @sa DSAParam DSAPriKey

    DSASig는 DSA 서명 생성 및 검증 함수에서 DSA 서명값의 입출력 시
    사용하기 위한 구조체이다.
    DSA 서명값은 두 가지값(r, s)이다. 
*/    
typedef struct {
  MINT r;
  MINT s;
} DSASig;

/** @ingroup DSA
    @brief DSA 시스템 파라미터 구조체
    @sa DSASig DSAPriKey

    DSA 서명 알고리즘에서 사용하기 위한 시스템 파라미터값을 담고 있는
    구조체이다. 시스템 파라미터는 p, q, g 세 가지이다.
*/    
typedef struct {
  MINT p;
  MINT q;
  MINT g;
} DSAParam;

/** @ingroup DSA
    @brief DSA 공개키
    @sa DSAPriKey

    DSA의 공개키 타입이다.
*/    
typedef MINT  DSAPubKey;

/** @ingroup DSA
    @brief DSA 비공개키
    @sa DSAPubKey

    DSA의 비공개키 타입이다.
*/    
typedef MINT  DSAPriKey;

/** @brief DSA 알고리즘 구조체 (PKCryptAlgorithm 과 동일)
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
    @brief DSA 알고리즘 descriptor인 dsa 전역 변수의 주소값 rename
    */
#define DSA &pcis_dsa

#ifdef __cplusplus
}
#endif

#endif /* _DSA_H_ */  
