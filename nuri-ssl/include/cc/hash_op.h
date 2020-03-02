#ifndef _HASH_OPERATION_H_
#define _HASH_OPERATION_H_

/** @defgroup HASH Hash Function
 * @ingroup CC
 * @brief Cryptographic Hash Functions
 */

/** @defgroup HASH_ALG Algorithm Descriptors
 * @ingroup HASH
 * @brief HASH Algorithm Descriptors
 */

/** @file hash_op.h
 * @ingroup HASH
 */
    
#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup HASH
 * @{ */

#define HASH_MAX_DIGEST_BIT_SIZE   512
#define HASH_MAX_DIGEST_SIZE        64
#define HASH_MAX_DIGEST_BT32_SIZE   16
#define HASH_MAX_DIGEST_BT64_SIZE   16
#define HASH_MAX_BLOCK_BIT_SIZE   1024
#define HASH_MAX_BLOCK_SIZE        128
#define HASH_MAX_BLOCK_BT32_SIZE    32
#define HASH_MAX_BLOCK_BT64_SIZE    32
#define HASH_MAX_INPUT_BT32_SIZE     4
#define HASH_MAX_INPUT_BT64_SIZE     4

/* for backward compatibility */
#define HASH_Update_PCIS PCIS_HASH_Update
#define HASH_Update_clone PCIS_HASH_Update
#define HASH_Initialize PCIS_HASH_Initialize
#define HASH_Finalize PCIS_HASH_Finalize
#define HASH_Update PCIS_HASH_Update

/**
 * @brief 알고리즘 지시자를 의미하는 구조체
 *
 * 해시 함수 알고리즘을 규정하는 각종 정보를 나타내는 구조체이며, HASH
 * 모듈에서 제공되는 API에서 개별 알고리즘들 구분하기 위한 지시자(descriptor)로
 * 사용된다.
 *
 * @sa PCIS_HASH_Initialize
 */
typedef struct {
  BWT    digestLen; /**< 출력 값의 길이 */
  void (*initFunc)(); /**< 초기화 함수 포인터 */
  void (*compressFunc)(); /**< 블록 처리 함수 포인터 */
  void (*padFunc)(); /**< 패딩 함수 포인터 */
  void (*dumpFunc)(); /**< 32비트 digest를 8비트로 변환하는 함수 포인터 */
} HashAlgorithm;

/**
    @brief Hash 알고리즘을 운영하기 위한 정보를 담을 구조체

    32bit Hash 알고리즘을 운영하는 데 필요한 다양한 정보들을 담고 있다.
    구조체 멤버들은 모두 내부적으로  값들이므로, 멤버들을 
    직접 읽거나 수정하지 않아야 한다.

    @sa PCIS_HASH_Initialize, PCIS_HASH_Update, PCIS_HASH_Finalize
*/
typedef struct {
  AlgDesc alg; /**< 알고리즘 지시자 */
  BT32 digest[HASH_MAX_DIGEST_BT32_SIZE]; /**< hash값을 저장하는 버퍼 */
  BT32 input [HASH_MAX_BLOCK_BT32_SIZE]; /**< 하나의 메시지 블럭을 저장하는 버퍼 */
  BT32 count [HASH_MAX_INPUT_BT32_SIZE]; /**< 처리된 메시지의 길이를 저장하는 버퍼 */
} Hash32Context; 

/**
    @brief Hash 알고리즘을 운영하기 위한 정보를 담을 구조체

    64bit Hash 알고리즘을 운영하는 데 필요한 다양한 정보들을 담고 있다.
    구조체 멤버들은 모두 내부적으로  값들이므로, 멤버들을 
    직접 읽거나 수정하지 않아야 한다.

    @sa PCIS_HASH_Initialize, PCIS_HASH_Update, PCIS_HASH_Finalize
*/
typedef struct {
  AlgDesc alg; /**< 알고리즘 지시자 */
  BT64 digest[HASH_MAX_DIGEST_BT64_SIZE]; /**< hash값을 저장하는 버퍼 */
  BT64 input [HASH_MAX_BLOCK_BT64_SIZE]; /**< 하나의 메시지 블럭을 저장하는 버퍼 */
  BT64 count [HASH_MAX_INPUT_BT64_SIZE]; /**< 처리된 메시지의 길이를 저장하는 버퍼 */
} Hash64Context;

/**
    @brief Hash 알고리즘을 운영하기 위한 정보를 담을 구조체

	32bit Hash 알고리즘과 64bit Hash 알고리즘을 운영하는 데 필요한 다양한
	정보들을 담고 있다. 구조체 멤버들은 모두 내부적으로  값들이므로, 멤버들을
	직접 읽거나 수정하지 않아야 한다.

    @sa PCIS_HASH_Initialize, PCIS_HASH_Update, PCIS_HASH_Finalize
*/
typedef struct {
  AlgDesc alg; /**< 알고리즘 지시자 */
  Hash32Context hash32; /**< 32bit 연산 해시 context */
  Hash64Context hash64; /**< 64bit 연산 해시 context */
} HashContext;
/**
    @brief HashContext를 초기화한다.

    HashContext를 초기화한다. Hash 알고리즘을 사용하기 위해서는 HashContext
    구조체의 인스턴스가 필요하다. \e alg는 사용하고자 하는 알고리즘의
    descriptor 구조체의 포인터값이다. 예를 들어 MD5 경우 \e MD5라는 descritor가
    global로 선언되어 있다. 다음은 그 예이다.
   
    \code
    BYTE md[20];
    BWT dlen;
    HashContext ctx;
    PCIS_HASH_Initialize(&ctx, MD5);
    PCIS_HASH_Update(&ctx, "abcdefg", strlen("abcdefg");
    dlen = sizeof(md);
    PCIS_HASH_Finalize(md, &dlen, &ctx);
    \endcode
    
    \b MD5 외에도 \b SHA1, \b RIPEMD160, \b HAS160 알고리즘을 사용할 수 있다.
    모든 알고리즘의 이름 자체가 descriptor가 된다. 다음은 SHA1과 HAS160으로
    context를 초기화하는 예제이다.
   
    \code
    HashContext ctx1, ctx2;
    PCIS_HASH_Initialize(&ctx1, SHA1);
    PCIS_HASH_Initialize(&ctx2, HAS160);
    \endcode
    
    위의 예에서 \e ctx1은 SHA1 알고리즘의 context이며, \e ctx2는 HAS160
    알고리즘의 context이다.

    64비트 워드 기반 해쉬 알고리즘인 SHA-384, SHA-512도 사용 가능하다.
    
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
    @sa PCIS_HASH_Update, PCIS_HASH_Finalize
*/
LIBSPEC
ERT PCIS_HASH_Initialize(
		HashContext *ctx, /**< [out] 초기화하고자 하는 HashContext의 포인터값 */
		AlgDesc hashAlg /**< [in] 사용할 hash 알고리즘의 descriptor */
		);

/**
    @brief 입력 받은 메시지로부터 hash값을 업데이트한다.

	한 번에 1GB만큼의 메시지를 입력할 수 있다.
    \e msg가 가리키고 있는 버퍼에서 입력 메시지값을 읽어와서 현재 HashContext의
    hash값을 업데이트한다. 최종적인 hash값을 얻기 위해서는 반드시
    \e PCIS_HASH_Finalize함수를 통해서 출력된 버퍼값을 사용하여야한다.

    같은 메시지라도 여러번 나누어 업데이트하는 것이 가능하다. 예를 들어,

    \code
    HashContext ctx1, ctx2;
    PCIS_HASH_Initialize(&ctx1, MD5);
    PCIS_HASH_Initialize(&ctx2, MD5);
    
    PCIS_HASH_Update(&ctx1, "abcdefg", strlen("abcdefg");
    
    PCIS_HASH_Update(&ctx2, "ab", strlen("ab");
    PCIS_HASH_Update(&ctx2, "c", strlen("c");
    PCIS_HASH_Update(&ctx2, "defg", strlen("defg");
    \endcode

    위의 \e ctx1, \e ctx2 업데이트 결과는 동일하다.

    64비트 워드 기반 해쉬 알고리즘인 SHA-384, SHA-512도 사용 가능하다.

    2007.07.04
    Netscape 웹 서버에 embed되는 경우에 openssl 라이브러리 심벌과 충돌하는 것을 피하기
    위하여 PCIS_HASH_Update 로 이름 변경

    @sa PCIS_HASH_Initialize, PCIS_HASH_Finalize
*/
LIBSPEC
void PCIS_HASH_Update(
		HashContext *ctx, /**< [in,out] update된 HashContext의 포인터값 */
		const BYTE *msg, /**< [in] 입력할 메시지 버퍼의 바이트 포인터값 */
		BWT msgLen /**< [in] 입력할 메시지 버퍼의 바이트 단위 길이 */
		);

/**
    @brief 최종적인 hash값을 계산한 다음, 결과를 버퍼에 복사한다. 
    함수 실패 시, mdLen = 0으로 출력
    함수 성공 시, mdLen = digestLen으로 출력

    최종적인 hash값을 \e md가 가리키고 있는 버퍼에 복사한다.
    이 함수에서 padding을 하여 최종 hash값을 계산하므로 이 함수를 수행한
    후의 \e md버퍼값만이 유효한 hash값이 된다.

    내부적으로 HashContext를 복사한 후, 처리를 하므로, 입력되는 HashContext
    는 변함이 없다. 따라서, 한 번 \e PCIS_HASH_Finalize를 수행한 HashContext라도
    계속하여 \e PCIS_HASH_Update를 수행할 수 있다. 예를 들어,
   
    \code
    BYTE md1[16], md2[16];
    BWT dlen;
    HashContext ctx;
    PCIS_HASH_Initialize(&ctx, MD5);
    
    PCIS_HASH_Update(&ctx, "abcdefg", strlen("abcdefg");
    PCIS_HASH_Update(&ctx, "hi", strlen("hi");
    dlen = sizeof(md1);
    PCIS_HASH_Finalize(md1, &dlen, &ctx);

    PCIS_HASH_Update(&ctx, "jklmnopq", strlen("jklmnopq");
    dlen = sizeof(md2);
    PCIS_HASH_Finalize(md2, &dlen, &ctx);
    \endcode

    위의 결과에서 md1과 md2모두 유효한 hash값이다.
    즉, \e md1은 "abcdefghi"의 hash값이고,
    \e md2는 "abcdefghijklmnopq"의 hash값이다.

    64비트 워드 기반 해쉬 알고리즘인 SHA-384, SHA-512도 사용 가능하다.

    @sa PCIS_HASH_Initialize, PCIS_HASH_Update
*/
LIBSPEC
void PCIS_HASH_Finalize(
		BYTE *md, /**< [out] 최종적인 결과를 복사할 버퍼의 포인터 */
		BWT *mdLen, /**< [in, out] IN: md의 메모리 버퍼 크기, OUT: 출력값의 바이트 단위 길이 */
		const HashContext *ctx /**< [in] HashContext의 포인터값 */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _HASH_OPERATION_H_ */
