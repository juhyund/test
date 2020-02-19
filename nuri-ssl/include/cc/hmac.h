/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_HMAC_H_
#define _PCIS_HMAC_H_

/** @defgroup MAC Message Authentication Code
 * @ingroup CC
 * @brief Message Authentication Code
 */

/** @file hmac.h
    @ingroup MAC
    @brief HMAC을 운영하기 위한 인터페이스

    HMAC 알고리즘을 사용하기 위한 인터페이스를 정의하고 있다.
    HMAC에 사용되는 해쉬 알고리즘에 독립적인 모듈로서, initialize과정에서
    사용하고자 하는 해쉬 알고리즘을 지정해야 한다.
*/

#include "cc_define.h"
#include "hash_op.h"

#ifdef __cplusplus
extern "C" {
#endif

/* for symbol name compatibility */
#define HMAC_Initialize PCIS_HMAC_Initialize
#define HMAC_Finalize PCIS_HMAC_Finalize
#define HMAC_Update PCIS_HMAC_Update

#define HMAC_MAX_KEY_LEN 32 /* temporary max */

/** @addtogroup MAC
 * @{ */

/**
    @brief HMAC을 운영하기 위한 정보를 담을 구조체

    HMAC 모듈을 운영할 때, 필요한 정보들을 유지하기 위한
    구조체이다. initialize, update 과정에서 이들 정보가
    갱신된다. 모듈 내부적으로 갱신하는 구조체이므로 사용자가
    외부에서 임의로 데이터를 바꾸어서는 안 된다.

    @sa PCIS_HMAC_Initialize, PCIS_HMAC_Update, PCIS_HMAC_Finalize
*/
typedef struct {
  HashContext ihCtx; /**< hash of inner padding key */
  HashContext ohCtx; /**< hash of outer padding Key */
} HmacContext;

/**
    @brief HmacContext를 초기화한다.

    HmacContext를 초기화한다. HMAC을 사용하기 위해서는 
    HmacContext를 선언해야 하며, 그것을 초기화하는 인터페이스가
    이 함수이다. 다음은 그 예이다.
    \code
    HmacContext ctx1, ctx2;
    BYTE key1[] = "\x01\x23\x45\x67";
    BYTE key2[] = "\x01\x23\x45\x67\x01\x23\x45\x67";
    
    PCIS_HMAC_Initialize(&ctx1, key1, 4, SHA1);
    PCIS_HMAC_Initialize(&ctx2, key2, 8, HAS160);
    \endcode
    위의 코드는 SHA1 해쉬 알고리즘과 HAS160 해쉬 알고리즘을 사용하기
    위하여 두 개의 HmacContext를 선언하고 key1과 key2와 함께 
    초기화하는 과정을 나타낸다. SHA1 알고리즘과 key1을 키로 하는 HMAC과
    HAS160 알고리즘과 key2를 키로 하는 HMAC 을 사용하기 위함이다.

    해쉬 알고리즘 descriptor는 그 알고리즘의 이름과 동일하다. HASH 모듈에
    대한 설명을 보면, 더 자세한 정보를 얻을 수 있을 것이다. 위의 예에서는
    SHA1 과 HAS160 이라는 알고리즘명과 동일한 descriptor를 넘겨 주고 있다.

    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @sa PCIS_HMAC_Update, PCIS_HMAC_Finalize
*/
LIBSPEC
ERT PCIS_HMAC_Initialize(
		HmacContext *hmCtx, /**< [out] 초기화 대상인 HmacContext의 포인터 */
		const BYTE *key, /**< [in] key to HMAC */
		BWT keyLen, /**< [in] key length in bytes */
		AlgDesc hashAlg /**< [in] 사용하고자 하는 hash 알고리즘 descriptor */
		);

/**
    @brief HmacContext를 업데이트한다.

    \code
    BYTE hmac[20];
    int hmacLen = sizeof(hmac);
    BYTE key[] = "\x01\x23\x45\x67\x01\x23\x45\x67";
    HmacContext ctx;
    PCIS_HMAC_Initialize(&ctx, key, 8, MD5);
    PCIS_HMAC_Update(&ctx, "abcdefg", strlen("abcdefg");
    PCIS_HMAC_Finalize(hmac, &hmacLen, &ctx);
    \endcode

    위의 예는 MD5 알고리즘과 key로 "abcdefg"라는 메시지에 대한 HMAC값을
    계산하는 과정이다.
    위의 예에서는 메시지가 알파벳이므로, 길이를 바로 strlen()을 사용하였지만,
    바이너리 데이터일 경우는, strlen()을 사용할 수 없음에 주의해야 한다.
    (바이너리 0x00값이 데이터의 끝을 의미하는 것이 아니므로.)
    
    @sa PCIS_HMAC_Initialize, PCIS_HMAC_Finalize
*/
LIBSPEC
void PCIS_HMAC_Update( HmacContext *hmCtx, /**< [in,out] 업데이트 대상이 되는 HmacContext의 포인터*/
                    const BYTE  *msg, /**< [in] 메시지 데이터를 저장하고 있는 버퍼의 포인터*/
                    BWT          msgLen /**< [in] msg의 바이트 단위 길이 */
                    );

/**
    @brief 최종적으로 HMAC값을 구한다.

    함수가 성공하였다면, hmacLen = digestLen으로 출력된다.

    이 함수를 사용함으로써, 최종적으로 HMAC값을 구할 수가 있다. 그 예는
    PCIS_HASH_Update에 대한 설명 중의 예제 코드를 참조하기 바란다.
    hmCtx 파라미터가 const로 정의되어 있음에도 알수 있듯이, Finailze과정에서는
    HmacContext의 내용을 갱신하지 않는다. 따라서, Finalize과정을 거친 
    HmacContext일 지라도 계속 Update 할 수 있는 것이다.  다음은 그 예이다.

    \code
    BYTE hmac1[16], hmac2[16];
    BWT hmacLen;
    BYTE key[] = "\x01\x23\x45\x67\x01\x23\x45\x67";
    HmacContext ctx;

    PCIS_HMAC_Initialize(&ctx, key, 8, MD5);
    PCIS_HMAC_Update(&ctx, "abcdefg", strlen("abcdefg");
    PCIS_HMAC_Update(&ctx, "hi", strlen("hi");
    hmacLen = sizeof(hmac1);
    PCIS_HMAC_Finalize(hmac1, &hmacLen, &ctx);
    PCIS_HMAC_Update(&ctx, "jklmnopq", strlen("jklmnopq");
    hmacLen = sizeof(hmac2);
    PCIS_HMAC_Finalize(hmac2, &hmacLen, &ctx);
    \endcode

    위의 결과에서 hmac1과 hmac2모두 유효한 hmac값이다.
    즉, hmac1은 "abcdefghi"의 hmac값이고,
    \e hmac2는 "abcdefghijklmnopq"의 hmac값이다.

    @sa PCIS_HMAC_Initialize, PCIS_HMAC_Update
*/
LIBSPEC
void PCIS_HMAC_Finalize( BYTE         *hmac, /**< [out] 계산되어진 HMAC 값이 저장될 버퍼의 포인터*/
                    BWT               *hmacLen, /**< [in,out] IN: hmac의 메모리 버퍼 크기, OUT: hmac의 길이가 저장될 변수의 포인터 */
                    const HmacContext *hmCtx /**< [in] HmacContext 인스턴스의 포인터*/
                    );

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_HMAC_H_ */
