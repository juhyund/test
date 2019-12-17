#ifndef _KCDSA_H_
#define _KCDSA_H_

/** @defgroup KCDSA
 * @ingroup PKCRYPT_ALG
 * @brief KCDSA (Korean Certificate-based Digital Signature Algorithm)
 */

/** @file kcdsa.h
    @ingroup KCDSA
    @brief KCDSA 알고리즘을 사용하기 위한 인터페이스
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
    @brief KCDSA 서명값 구조체
    @sa KCDSAParam, KCDSAPriKey

    KCDSASig는 KCDSA 서명 생성 및 검증 함수에서 KCDSA 서명값의 입출력 시
    사용하기 위한 구조체이다. KCDSA 서명값은 두 가지값(r, s)이다.
*/
typedef struct {
  BYTE r[HASH_MAX_DIGEST_SIZE];
  MINT s;
} KCDSASig;

/** @ingroup KCDSA
    @brief KCDSA 시스템 파라미터 구조체
    @sa KCDSASig,KCDSAPriKey

    KCDSAParam는 KCDSA 서명 생성 및 검증 함수에서 KCDSA 시스템 파라미터들의
    입출력 시 사용하기 위한 구조체이다.  시스템 파라미터는 p, q, g가 있다.
*/
typedef struct {
  MINT p; /**< KCDSA 시스템 파라미터 p */
  MINT q; /**< KCDSA 시스템 파라미터 q */
  MINT g; /**< KCDSA 시스템 파라미터 g */
  BYTE seed[KCDSA_PARAM_MAX_Q_SIZE]; /**< 파라미터 생성에 사용되는 seed */
  BYTE j[KCDSA_PARAM_MAX_J_SIZE]; /**< 파라미터 생성 중 PRNG에서 유도된 J */
  BYTE XKEY[KCDSA_PARAM_MAX_Q_SIZE]; /**< 키 생성 중 최종 XKEY */
  BYTE gbuf[256]; /**< 생성원 G */
  BYTE OUPRI[KCDSA_PARAM_MAX_Q_SIZE]; /**< 키 생성 중 PRNG 출력 */
  BWT  jLen; /**< j의 바이트 길이 */
  BWT  seedLen; /**< seed의 바이트 길이 = q/8 */
  BWT  count; /**< 파라미터 생성에 사용되는 Count */
} KCDSAParam;

/** @ingroup KCDSA
    @brief KCDSA 공개키
    @sa KCDSAPriKey

    KCDSA의 공개키 타입이다.
*/    
typedef MINT  KCDSAPubKey;

/** @ingroup KCDSA
    @brief KCDSA 비공개키
    @sa KCDSAPubKey

    KCDSA의 비공개키 타입이다.
*/    
typedef MINT  KCDSAPriKey;

/** @brief KCDSA 알고리즘 구조체 (PKCryptAlgorithm 과 동일)
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
    @brief KCDSA 알고리즘 descriptor인 pcis_kcdsa 전역 변수의 주소값 rename
*/
#define KCDSA   &pcis_kcdsa

/** @ingroup KCDSA
    @brief KCDSA0 알고리즘 descriptor인 popkcdsa 전역 변수의 주소값 rename
*/
#define KCDSA0  &popkcdsa

#ifdef __cplusplus
}
#endif

#endif
