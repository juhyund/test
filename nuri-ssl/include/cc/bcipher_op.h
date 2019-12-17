#ifndef _BCIPHER_OP_H_
#define _BCIPHER_OP_H_

/** @defgroup BCIPHER Block Cipher
 * @ingroup CC
 * @brief Block Cipher
 */ 

/** @defgroup BCIPHER_ALG Algorithm Descriptors
 * @ingroup BCIPHER
 * @brief BCIPHER Algorithm Descriptors
 */

/** @file bcipher_op.h
 * @ingroup BCIPHER
 * @brief 블록암호 서비스를 이용하기 위한 API
 */

#include "cc_define.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BCIPHER
 * @{ */

/** No padding */
#define NPAD		0 
/** PKCS5 and PKCS7 padding */
#define PAD_PKCS7	1
/** X9.23 padding.
 * not popular compared to PKCS7 padding method */
#define PAD_X9_23	2
/** for compatibility */
#define PAD PAD_PKCS7

/** 블록 암호의 비밀키로 사용할 수 있는 최대 바이트 크기 */
#define BCIPHER_MAX_KEY_SIZE          32
/** 블록 암호를 이용한 메시지 인증의 태그 길이의 최대 바이트 크기 */
#define BCIPHER_MAX_TAG_SIZE          16
/** 블록 암호 운영모드에서의 초기 벡터의 최대 바이트 크기 */
#define BCIPHER_MAX_IV_SIZE           16
/** 블록 암호의 블록의 최대 바이트 크기 */
#define BCIPHER_MAX_BLOCK_SIZE        16
/** 블록 암호의 블록의 32비트 당 최대 크기 */
#define BCIPHER_MAX_BLOCK_BT32_SIZE    4

/** @name Modes of operation
 * @{ */

/** @brief ECB mode
 *
 * Chaining vector 없이 한 block씩 독립적으로 암호화한다. 따라서, \e
 * MODE_ECB로 \e BCIPHER_Initialize 할 때에는 \e iv값을 NULL로 넘겨주면 된다.
 * (\e iv 는 initiali vecotr의 약자로 chaining vector의 초기값을 의미한다.)
 * MODE_ECB를 제외한 나머지 모드에서는 모두 chaining vector를 사용하므로 \e iv
 * 값을 세팅하는 것이 필요하다. 물론, NULL값을 주면 iv 가 디폴트로 0으로
 * 셋팅되지만, 보안 측면에서 iv 는 key 만큼 중요한 값이므로 key와 마찬가지로
 * 적절한 값이 주어져야 하고 또한, 기밀이 유지되어야 한다.
 * @sa BCIPHER_Initialize
 */
#define MODE_ECB        1
/** @brief CBC mode.
 *
 * CBC 모드의 정의는 다음과 같다.
 * - Chaining vector와 plain text를 exclusive OR 한 블럭을 암호화하여 cipher
 *   text를 생성한다.
 * - Chaining vector는 이전 plain text의 cipher text이다.
 * - Chaining vector의 초기값은 \e BCIPHER_Intialize 함수의 \e iv 값으로
 *   주어진다.
 *
 * Chaining vector값은 \e BCipherContext에 유지되므로, 암호화용
 * BCipherContext와 복호화용 BCipherContext를 별도로 초기화하여 사용하여야
 * 한다. MODE_ECB를 제외한 다른 모든 모드에서도 chaining vector를 사용하므로
 * 역시 암복호화용 Context를 각각 따로 운영하여야 한다.
 * @sa BCIPHER_Initialize
 */
#define MODE_CBC        2
/** @brief CFB mode with full block feedback.
 *
 * 일반적인 CFB 모드의 정의에 대한 개괄적인 정의는 다음과 같다.
 * - Chaining vector를 암호화한 블럭 중 상위 j-bits을 plain text j-bits과
 *   EXOR하여 cipher text j-bits을 생성한다.
 * - Chaining vector는 이전 chaing vector를 j-bits만큼 shift한 다음, 하위
 *   j-bits을 이전 cipher text로 교체한다.
 *
 * MODE_CFB가 의미하는 바는 위의 설명 중 j-bits이 사용하는 알고리즘의 블럭
 * 크기와 동일할 때의 모드를 의미한다. feedback 크기가 다른 다른 모드는
 * MODE_CFB_BYTE와 MODE_CFB1을 참조한다.
 * @sa BCIPHER_Initialize, MODE_CFB_BYTE
 */
#define MODE_CFB        3
/** @brief CFB mode with byte feedback.
 *
 * MODE_CFB에서 설명한 CFB 모드의 정의 중, j-bits이 8-bits 즉, 1 바이트일 때의
 * 모드이다.
 * @sa BCIPHER_Initialize, MODE_CFB
 */
#define MODE_CFB_BYTE   4
/** @brief OFB mode with full block feedback.
 *
 * 일반적인 OFB 모드의 정의에 대한 개괄적인 정의는 다음과 같다.
 * - Chaining vector를 암호화한 블럭 중 상위 j-bits을 plain text j-bits과
 *   EXOR하여 cipher text j-bits를 생성한다.
 * - Chaining vector는 이전 chaing vector를 j-bits만큼 shift한 다음, 하위
 *   j-bits을 이전 pain text와 EXOR한 j-bits으로 교체한다.
 *
 * MODE_OFB가 의미하는 바는 위의 설명 중 j-bits이 사용하는 알고리즘의 블럭
 * 크기와 동일할 때의 모드를 의미한다.
 * @sa BCIPHER_Initialize, MODE_OFB_BYTE
 */
#define MODE_OFB        5
/** @brief OFB mode with byte feedback.
 *
 * MODE_OFB에서 설명한 OFB 모드의 정의 중, j-bits이 8-bits 즉, 1 바이트일 때의
 * 모드이다.
 * @sa BCIPHER_Initialize, MODE_OFB
 */
#define MODE_OFB_BYTE   6
/** @brief CTS mode.
 *
 * CTS 모드는 암호화된 후의 cipher text의 길이가 plain text의 길이와 동일할
 * 필요가 있을 때 사용할 수 있는 모드이다.
 *
 * PAD 옵션이 유효한 ECB, CBC, CTS 모드 중 CTS를 제외하고는 마지막에 패딩을 할
 * 때, 사용하는 알고리즘의 블럭 크기의 배수가 되도록 필요한 길이만큼의 특정
 * 값을 추가한다. 따라서, ECB, CBC 모드에서는 paint text 길이보다 cipher text의
 * 길이가 길어지게 된다. CTS모드는 패딩 방법상 plain text와 cipher text의
 * 길이가 동일하다. 마지막 패딩 방법을 제외하고는 CBC 모드와 동일하다.
 * @sa BCIPHER_Initialize, BCIPHER_Encrypt, BCIPHER_Decyrypt
 */
#define MODE_CTS        7
/** @brief CFB mode with bit feedback.
 *
 * @sa BCIPHER_Initialize
 */
#define MODE_CFB1       8
/** @brief CTR mode
 *
 * @sa BCIPHER_Initialize
 */
#define MODE_CTR        9
/** @brief CFB mode with variable-sized message input.
 *
 * @sa BCIPHER_Initialize, BCIPHER_Encrypt, BCIPHER_Decyrypt
 */
#define MODE_MCFB       10
/** @brief GCM mode.
 *
 * @sa BCIPHER_Initialize
 */
#define MODE_GCM        11
/** @brief CCM mode.
 *
 * @sa BCIPHER_Initialize
 */
#define MODE_CCM        12

/** @} */ /* end of modes of operation */

/**
 * @brief 알고리즘 지시자를 의미하는 구조체
 *
 * 블록 암호 알고리즘을 규정하는 각종 정보를 나타내는 구조체이며, BCIPHER
 * 모듈에서 제공되는 API에서 개별 알고리즘들 구분하기 위한 지시자(descriptor)로
 * 사용된다.
 *
 * @sa BCIPHER_Initialize
 */
typedef struct {
	BWT     blockLen; /**< 알고리즘이 사용하는 기본 블럭의 바이트 단위 길이 */
	BWT     rKeySize; /**< 알고리즘이 사용하는 round key의 바이트 단위 길이 */
	void  (*keyFunc)(); /**< 라운드키를 생성하는 함수 포인터 */
	void  (*encFunc)(); /**< 암호화 함수 포인터 */
	void  (*decFunc)(); /**< 복호화 함수 포인터 */
	BWT   (*apadFunc)(); /**< 패딩 함수 포인터 */
	BWT   (*rpadFunc)(); /**< 패딩 제거 함수 포인터 */
} BCipherAlgorithm;

/**
 * @brief Block cipher의 운영에 대한 정보를 가지는 구조체
 *
 * \e mode는 ECB, CBC, CFB, OFB, CTS등의 block cipher의 operation mode를
 * 가리키며, \e iv는 이들 각 모드에서 사용될 initial vector를 저장할 버퍼이다.
 * \e alg는 사용하고자 하는 알고리즘의 지시자이다.
 *
 * @sa BCIPHER_Initialize
 */
typedef struct {
	BYTE    mode; /**< 운영 모드 */
	BYTE    iv[BCIPHER_MAX_IV_SIZE]; /**< chaining vector를 저장할 버퍼 */
	AlgDesc alg; /**< 알고리즘 지시자의 포인터 */ 
	BYTE    index; /**< MCFB 모드를 사용할 때 iv 입력 범위를 설정 */
} BCipherContext;

/**
 * @brief Block cipher key 구조체
 * @sa BCIPHER_NewKey BCIPHER_MakeKey BCIPHER_DelKey
 */
typedef struct {
	AlgDesc alg; /**< 알고리즘 지시자의 포인터 */
	BYTE  keyMat[BCIPHER_MAX_KEY_SIZE]; /**< 비밀키 */
	BWT   keyMatLen; /**< 비밀키의 바이트 길이 */
	/** keyMat로부터 생성된 round key 정보.
	 * 각 알고리즘마다 다르게 활용된다. 구체적인 활용법은 각 알고리즘의 내부
	 * 코드에서 규정되고 외부에 노출되지 않는다. */
	BYTE *roundKey;
} BCipherKey;

/**
 * @brief BCipherKey를 생성한다.
 * @return [out] 생성된 BCipherKey 구조체의 pointer
 *
 * 알고리즘 descriptor를 입력으로 받아, 해당 알고리즘의 키를 메모리에 할당하여
 * 그 포인터를 리턴한다. 리턴된 포인터가 가리키는 BCipherKey는 사용하기 전,
 * 반드시 BCIPHER_MakeKey를 사용하여 key material로부터 값을 설정한 후에
 * 사용해야 한다.
 *
 * @sa BCIPHER_DupKey BCIPHER_DelKey BCIPHER_MakeKey
 */
LIBSPEC
BCipherKey* BCIPHER_NewKey(
		AlgDesc bcipherAlg /**< [in] 알고리즘 descriptor */
		);

/**
 * @brief BCipherKey를 복제한다.
 * @return [out] 복제된 키
 *
 * 입력으로 받은 BCipherKey와 동일한 키를 복제하여 메모리를 할당한 후
 * return한다.
 *
 * @sa BCIPHER_NewKey BCIPHER_DelKey BCIPHER_MakeKey
 */
LIBSPEC
BCipherKey* BCIPHER_DupKey(
		const BCipherKey *bcKey /**< [in] 복제할 BCiopherKey의 포인터 */
		);

/**
 * @brief BCipherKey를 메모리에서 제거한다.
 *
 * BCIPHER_NewKey로 부터 생성된 키를 사용이 끝난 뒤에는 이 함수로 할당된
 * 메모리를 제로화하고, 해제한다.
 *
 * @sa BCIPHER_NewKey BCIPHER_MakeKey
 */
LIBSPEC
void BCIPHER_DelKey(
		BCipherKey *bcKey /**< [in] BCipherKey의 포인터 */
		);

/** @ingroup KEYGEN
 * @brief BCIPHER에 사용되기 적합한 비밀키를 무작위로 생성한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 키 바이트 열 생성 성공
 *
 * 생성할 비밀키의 바이트 단위 길이(KeyLen)를 입력으로 받아 검증대상
 * 난수발생기(HASHDRBG)를 내부적으로 사용하여 비밀키를 안전하게 생성한다.
 * BCIPHER에 사용할 키를 반드시 이 방법으로 만들 필요가 있는 것은 아니며
 * 외부로부터 입력받은 키를 그대로 사용할 수도 있다. 이 API는 예측 불가능한
 * 새로운 키를 임의로 생성하고자 할 때 사용한다.
 *
 * @sa BCIPHER_NewKey BCIPHER_MakeKey
 */
LIBSPEC
ERT BCIPHER_GenKey(
		BYTE *Key, /**< [out] 생성된 비밀키가 저장된 버퍼를 가리키는 포인터 */
		BWT KeyLen /**< [in] 생성할 비밀키의 바이트 단위 길이 */
		);

/**
 * @brief Block Cipher의 키를 초기화한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 암호화 수행 성공
 * @retval ER_NOT_APPROVED_ALGOTITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_KEY_LENGTH 옳지 못한 키 길이를 입력하였을 때

    Block cipher에 쓰일 \e keyMat를, 바이트 단위 길이와 함께 입력
    받은 후, \e key 구조체를 초기화한다. key 구조체는 각 알고리즘의 헤더 파일에
    정의 되어 있다. 예를 들어 DES 알고리즘의 키 구조체는 des.h에 \e DesKey로
    정의되어 있다. Key의 바이트 단위 길이는 각 알고리즘 헤더에 정의되어 있다.
    
    \e alg 는 사용하고자 하는 알고리즘의 지시자로, 각 알고리즘의
    헤더 파일에 구조체로 정의 되어 있고, global instance로 선언되어 있다.
    사용자가 이 지시자를 직접 다루어서는 안 되며, 단지 지시자를
    넘겨주는 것으로 충분하다. 지시자 이름은 알고리즘 명칭과 동일하다.

    다음은 몇 개의 공개적인 알고리즘에 대한 예시이다.

    \code
    BYTE keyMat1[8]  = {0x01,0x23, ...};
    BYTE keyMat2[16] = {0xf1,0xf2, ...};
    BYTE keyMat3[16] = {0x11,0x22, ...};

    BCipherKey *desKey;
    BCipherKey *bfKey;
    BCipherKey *ideaKey;

    desKey = BCIPHER_NewKey(DES);
    BCIPHER_MakeKey(desKey, keyMat1, DES_KEY_SIZE,  DES);
    BCIPHER_DelKey(desKey);

    bfKey = BCIPHER_NewKey(BLOWFISH);
    BCIPHER_MakeKey(bfKey,  keyMat2, 16, BLOWFISH);
    BCIPHER_DelKey(bfKey);

    ideaKeyKey = BCIPHER_NewKey(IDEA);
    BCIPHER_MakeKey(ideaKey,keyMat3, IDEA_KEY_SIZE, IDEA);
    BCIPHER_DelKey(ideaKeyKey);
    \endcode

    Blowfish 알고리즘의 경우, \e BLOWFISH_KEY_SIZE를 쓰지 않았는데,
    키의 길이가 가변적이기 때문이다. 최대 길이는 blowfish.h 에
    BLOWFISH_MAX_KEY_SIZE로 정의되어 있다.

    사용한 키는 BCIPHER_DelKey를 사용하여 할당된 메모리를 해제하여야 한다.
    사용한 비밀키는 ZEROIZE()를 이용하여 응용프로그램에서 제로화한다.

 * @sa BCIPHER_NewKey BCIPHER_DelKey
 */
LIBSPEC
ERT BCIPHER_MakeKey(
		BCipherKey *key, /**< [in,out] 초기화하고자 하는 key 구조체의 포인터값 */
		const BYTE *keyMat, /**< [in] Octet string 타입의 key binary 데이터 */
		BWT keyLen, /**< [in] keyMat의 바이트 단위의 길이 */
		AlgDesc bcipherAlg /**< [in] 사용할 block cipher 알고리즘 */
		);

/**
 * @brief BCipherContext를 초기화한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS BCipherContext를 초기화 성공
 * @retval ER_NOT_APPROVED_ALGOTITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시

    Block cipher의 운영에 관한 정보를 입력받아 BCipherContext를 초기화한다.

    ECB 모드 이외의 모드를 사용할 경우, 블록암호의 블록 크기만큼 iv는 반드시 입력해야 한다.

    한가지 주의할 것은 chaining vector는 
    암호화할 때와, 복호화할 때 계속 업데이트 되는 값이므로 
    암호화용 \e BCipherContext와 복호화용 \e BcipherContext가 각기
    따로 생성해서 사용해야 한다는 것이다. 즉, 하나의 Context를 가지고
    암호화와 복호화에 번갈아 사용해서는 안 되며, 하나의 용도에만 사용해야
    한다는 것이다. 단, chaining vecotr와 상관없는 ECB모드일 경우에는 하나의
    context가 암복호화에 모두 사용될 수 있다.

    다음은 그 예이다.

    \code
    BWT pLen1, cLen, dLen;    

    BYTE plain[256];
    BYTE cipher[256];
    BYTE decrypted[256];
    BYTE iv[8];
    BYTE key[8];

    BCipherKey *key;
    BCipherContext enc, dec, ctx;

    .
    .
    initialize
    .
    .

    BCIPHER_Initialize(&ctx, MODE_ECB, iv, DES);
    BCIPHER_Initialize(&enc, MODE_CBC, iv, DES);
    BCIPHER_Initialize(&dec, MODE_CBC, iv, DES);

    cLen = sizeof(cipher);
    BCIPHER_Encrypt(cipher,   &cLen, plain,  pLen, &ctx, key, PAD);
    dLen = sizeof(decrypted);
    BCIPHER_Decrypt(decrypted, &dLen, cipher, cLen, &ctx, key, PAD);

    cLen = sizeof(cipher);
    BCIPHER_Encrypt(cipher,   &cLen, plain,  pLen, &enc, key, PAD);
    dLen = sizeof(decrypted);
    BCIPHER_Decrypt(decrypted, &dLen, cipher, cLen, &dec, key, PAD);

    .
    .
    .
    finalize
    .
    .
    .

    \endcode

    위의 코드에서 MODE_ECB의 경우 같은 BCipherContext를 암복호화에 
    모두 사용하였지만, MODE_CBC 경우에는 별도의 BCipherContext를
    사용한다.

 * @sa BCipherContext
 */
LIBSPEC
ERT BCIPHER_Initialize(
		BCipherContext *bcipher, /**< [out] 초기화할 BcipherContext */
		BYTE mode, /**< [in] Operation mode */
		const BYTE *iv, /**< [in] Initial vector */
		AlgDesc bcipherAlg /**< [in] 사용하고자 하는 알고리즘의 지시자 */
		); 

/**
 * @brief Block cipher 암호화를 수행한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 암호화 수행 성공
 * @retval ER_NOT_APPROVED_ALGOTITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD include invalid padding bytes
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL 출력 버퍼의 메모리 크기가 출력할 데이터의 메모리보다 작을 시

    \e in 버퍼에 저장되어 있는 데이터를 BCipherContext와 BCipherKey의 정보에
    따라 암호화하여 결과를 \e out 버퍼에 출력한다. 이 때, 입출력 길이는 바이트
    단위이며 출력길이는 \e outLen이 가리키고 있는 BWT 타입의 변수에 저장된다.
    한가지 주의할 것은 데이터가 저장되는 버퍼는 반드시 octet string으로써 
    다루어져야지만 올바른 결과를 얻을 수 있다.

    \e padFlag는 주어진 버퍼가 block cipher의 block단위가 되도록 padding을
    할 것인가를 지시한다. \b NPAD이면 padding을 하지 않고, \b PAD이면 padding을
    하게 된다. 물론, NPAD일 경우에는 버퍼 길이는 block cipher가 다루는 
    블럭 단위의 배수로 주어져야 하며 이것은 사용자의 구현상의 문제이다. 
    이 모듈에서는 성능을 저하시키는 어떠한 코드(ex. error return)도 없으므로
    이것을 체크하지 않는다.

    PAD 옵션의 경우, ECB, CBC, CTS 모드에서만 유효하다. 나머지 모드에서는 모두 
    NPAD 이며, PAD 옵션은 사용할 수 없다.

	\e bcipher와 \e key는 각각 BCIPHER_Initialize와 BCIPHER_MakeKey를 통해서
	초기화가 이루어진 후에 사용해야 한다.

 * @sa BCIPHER_Decrypt, BCipherContext
 */
LIBSPEC
ERT BCIPHER_Encrypt(
		BYTE *out, /**< [out] 출력 암호문 */
		BWT *outLen, /**< [in, out] in: out의 메모리 버퍼 크기, out: 출력 암호문의 바이트 길이 */
		const BYTE *in, /**< [in] 입력 평문 */
		BWT inLen, /**< [in] 입력 평문의 바이트 길이 */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding 종류 */
		);

/**
 * @brief GCM 모드와 CCM 모드일 때의 Block cipher 암호화를 수행한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 인증암호화 알고리즘 암호화 수행 성공
 * @retval ER_NOT_APPROVED_ALGOTITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL 출력 버퍼의 메모리 크기가 출력할 데이터의 메모리보다 작을 시
 * @retval ER_BCIPHER_INVALID_TAG_LENGTH 출력 가능한 태그길이가 아닐 때
 * @retval ER_BCIPHER_INVALID_NONCE_LENGTH 입력 가능한 난스길이가 아닐 때
 *
 * BCIPHER_Encrypt()와 동일하나 운영 모드가 GCM이나 CCM일 때 사용한다.
 * CCM 모드의 경우, 4 <= tLen <= 16, 7 <= ivLen(nonceLen) <= 13 이어야 한다.
 * GCM 모드의 경우, tLen <= 16(블록크기) 이어야 하고, 12 <= ivLen 를 권장한다.
 */
LIBSPEC
ERT BCIPHER_EncryptAuth(
		BYTE *out, /**< [out] 출력 암호문 */
		BWT *outLen, /**< [in, out] in: out의 메모리 버퍼 크기, out: 출력 암호문의 바이트 길이 */
		const BYTE *in, /**< [in] 입력 평문 */
		BWT inLen, /**< [in] 입력 평문의 바이트 길이 */
		BYTE *authData, /**< [in] CCM/GCM의 추가 입력 정보 */
		BWT authDataLen, /**< [in] authData의 바이트 길이 */
		BYTE *iv, /**< [in] GCM의 iv, CCM의 nonce*/
		BWT ivLen, /**< [in] iv의 바이트 길이 */
		BCipherContext *bcipher, /**< [in] context */
		const BCipherKey *key, /**< [in] key */
		BWT tLen /**< [in] 메시지 인증 태그의 바이트 길이 */
		);

/**
 * @brief Block cipher 복호화를 수행한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 복호화 수행 성공
 * @retval ER_NOT_APPROVED_ALGOTITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_BCIPHER_INVALID_PAD include invalid padding bytes
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL 출력 버퍼의 메모리 크기가 출력할 데이터의 메모리보다 작을 시

    \e in 버퍼에 저장되어 있는 데이터를 BCipherContext와 BCipherKey의 정보에
    따라 복호화하여 결과를 \e out 버퍼에 출력한다. 이 때, 입출력 길이는 바이트
    단위이며 출력길이는 \e outLen이 가리키고 있는 BWT 타입의 변수에 저장된다.
    한가지 주의할 것은 데이터가 저장되는 버퍼는 반드시 octet string으로써 
    다루어져야지만 올바른 결과를 얻을 수 있다.

    \e padFlag는 주어진 버퍼가 암호화될 때, padding이 된 상태인가를 지시한다.
    \b PAD이면 마지막 바이트의 정보를 보고 padding된 부분을 제거하여 결과를
    출력하며, \b NPAD일 경우 복화화된 전체를 그대로 출력한다. 암호화할 때와
    마찬가지로 NPAD일 경우에는 입력 버퍼의 길이기 block cipher가 다루는
    블럭 단위의 배수가 되어야 한다.
    
    PAD 옵션의 경우, ECB, CBC 모드에서만 유효하다. 나머지 모드에서는 모두 
    NPAD 이며, PAD 옵션은 사용할 수 없다.

	\e bcipher와 \e key는 각각 BCIPHER_Initialize와 BCIPHER_MakeKey를 통해서
	초기화가 이루어진 후에 사용해야 한다.

 * @sa BCIPHER_Encrypt, BCipherContext
 */
LIBSPEC
ERT BCIPHER_Decrypt(
		BYTE *out, /**< [out] 출력 평문 */
		BWT *outLen, /**< [in, out] in: out의 메모리 버퍼 크기, out: 출력 암호문의 바이트 길이 */
		const BYTE *in, /**< [in] 입력 암호문 */
		BWT inLen, /**< [in] 입력 암호문의 바이트 길이 */
		BCipherContext *bcipher, /**< [in,out] context */
		const BCipherKey *key, /**< [in] key */
		BYTE padFlag /**< [in] Padding 종류 */
		);

/**
 * @brief GCM 모드와 CCM 모드일 때의 Block cipher 복호화를 수행한다.
 * @retval FAIL NULL 값 입력 등의 실패
 * @retval SUCCESS 인증암호화 알고리즘 복호화 수행 성공
 * @retval ER_NOT_APPROVED_ALGOTITHM 검증대상 운영 상태에서 비검증대상 암호알고리즘 호출 시
 * @retval ER_BCIPHER_BAD_OP_MODE bad operation mode
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL 출력 버퍼의 메모리 크기가 출력할 데이터의 메모리보다 작을 시
 * @retval ER_BCIPHER_INVALID_TAG_LENGTH 출력 가능한 태그길이가 아닐 때
 * @retval ER_BCIPHER_INVALID_NONCE_LENGTH 입력 가능한 난스길이가 아닐 때
 *
 * BCIPHER_Decrypt()와 동일하나 운영 모드가 GCM이나 CCM일 때 사용한다.
 * CCM 모드의 경우, 4 <= tLen <= 16, 7 <= ivLen(nonceLen) <= 13 이어야 한다.
 * GCM 모드의 경우, tLen <= 16(블록크기) 이어야 하고, 12 <= ivLen 를 권장한다.
 */
LIBSPEC
ERT BCIPHER_DecryptAuth(
		BYTE *out, /**< [out] 출력 평문 */
		BWT *outLen, /**< [in, out] in: out의 메모리 버퍼 크기, out: 출력 암호문의 바이트 길이 */
		const BYTE *in, /**< [in] 입력 암호문 */
		BWT inLen, /**< [in] 입력 암호문의 바이트 길이 */
		BYTE *authData, /**< [in] CCM/GCM의 추가 입력 정보 */
		BWT authDataLen, /**< [in] authData의 바이트 길이 */
		BYTE *iv, /**< [in] GCM의 iv, CCM의 nonce*/
		BWT ivLen, /**< [in] iv의 바이트 길이 */
		BCipherContext *bcipher, /**< [in] context */
		const BCipherKey *key, /**< [in] key */
		BWT tLen /**< [in] 메시지 인증 태그의 바이트 길이 */
		);

/** @ingroup ZERO
 * @brief BcipherContext의 iv를 제로화한다. */
LIBSPEC
void BCIPHER_WipeIV(
		BCipherContext  *bcipher /**< [in] 제로화할 iv가 있는 BcipherContext */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _BCIPHER_OP_H_ */
