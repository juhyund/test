#ifndef _FPE_OP_H_
#define _FPE_OP_H_

#include "pe_define.h"
#include "bcipher_op.h"
#include "fpe_common.h"
#include <stdio.h>

/**
 * @defgroup FPE Format-Preserving Encryption
 * @ingroup PE
 * @brief Block Cipher Mode of Operation: Format-Preserving Encryption
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup FPE
 * @brief FPE parameter set
 */
typedef struct {
	BWT radix; /**< prerequisites: aka base */
	BWT minLen; /**< prerequisites: input range min */
	BWT maxLen; /**< prerequisites: input range max */
	AlgDesc fpeAlg;
	AlgDesc bcipherAlg; /**< prerequisites: underlying block cipher */
	AlgDesc hashAlg;
	BYTE *P;
	BWT PLen;
	BCipherKey *bcKey; /**< prerequisites: key to underlying block cipher */
} FPEParameterSet;

/** @ingroup FPE */
LIBSPEC_PE
BWT POPFPE_GetMinLength(AlgDesc fpeAlg, BWT radix);

/** @ingroup FPE */
LIBSPEC_PE
BWT POPFPE_GetMaxLength(AlgDesc fpeAlg, BWT radix);

/** @ingroup FPE
    @brief FPEParameterSet를 초기화한다.
    @param param [out] 초기화할 FPEParameterSet를 가리키는 포인터
    @param radix[in] 입력, 출력 스트링을 구성하는 Character Set의 Radix
	@param fpeAlg [in] 사용할 FPE 알고리즘 지시자
    @param bcipherAlg [in] 암복호화 과정에서 사용할 블록암호 알고리즘 지시자
    @param hashAlg [in] 암복호화 과정에서 사용할 해시함수 알고리즘 지시자
    @retval ER_FPE_NULL_PARAM null parameterset pointer
    @retval ER_FPE_INVALID_RADIX invald radix value

    FPE의 운영에 관한 정보를 입력받아 FPEParameterSet를 초기화한다.
	radix는 2<= radix <= 0x10000 를 만족하는 범위에서만 유효하며, FPEMJ
	알고리즘을 사용할 때 Long 버전은 radix가 10보다 작을 때 8 미만의 길이를
	갖는 스트링을 암호화하지 못하므로 이 경우엔 Short 버전을 사용해야 한다.
	사용하는 블록암호 알고리즘은 블록 사이즈가 128bit 이상인 알고리즘으로
	사용하는 것이 안전한다. 한 번 초기화한 FPEParameterSet 구조체는 암호화,
	복호화에 모두 제약없이 쓰일 수 있다.
*/
LIBSPEC_PE
BWT POPFPE_Initialize(FPEParameterSet *param, BWT radix, AlgDesc fpeAlg, AlgDesc bcipherAlg, AlgDesc hashAlg);

/** @ingroup FPE
    @brief x로 입력받은 스트링를 암호화하여 y으로 출력한다.
    @param y [out] 암호화된 결과가 저장될 버퍼를 가리키는 포인터
    @param yLen [out] 암호화된 결과의 길이가 저장될 변수의 포인터
    @param x [in] 암호화할 스트링이 저장되어 있는 버퍼를 가리키는 포인터
    @param xLen [in] 암호화할 스트링의 길이
    @param param [in] FPEParameterSet 포인터
    @param key [in] Octet string 타입의 key binary 데이터
    @param keyLen [in] key material의 바이트 단위 길이
    @param tweak [in] tweak 스트링이 저장되어 있는 버퍼를 가리키는 포인터
    @param tweakLen [in] tweak 스트링의 길이
    @param iv [in] 이니셜 벡터
    @retval ER_FPE_INVALID_RADIX invald radix value
    @retval ER_FPE_INVALID_X_LENGTH invald x length
    @retval ER_FPE_INVALID_Y_LENGTH invald y length
    @retval ER_FPE_INVALID_ADDITION invald blockwise addition input lenth

    \e in 버퍼에 저장되어 있는 스트링을 FPEParameterSet와 key, tweak의 정보에
    따라 암호화하여 결과를 \e out 버퍼에 출력한다. 주의할 점은, Octet string 형태인 key와 달리
    x, tweak은 0x00..(0x00+radix-1) 범위의 Charater set으로 구성된 스트링의 형태여야 점이다.
    따라서 x, tweak을 구성하는 Character 중에서 0x00+radix-1보다 큰 값을 갖는 Charater가 존재할 시
    정상적인 암복호화가 이루어질 수 없다.
    출력값인 y 역시 위의 Charater set으로 구성된 스트링의 형태이다.
*/
LIBSPEC_PE
BWT POPFPE_Encrypt(void *y, BWT *yLen, void *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, void *tweak, BWT tweakLen, BYTE *iv);

/** @ingroup FPE
    @brief y로 입력받은 스트링를 복호화하여 x으로 출력한다.
    @param x [out] 복호화된 결과가 저장될 버퍼를 가리키는 포인터
    @param xLen [out] 복호화된 결과의 길이가 저장될 변수의 포인터
    @param y [in] 복호화할 스트링이 저장되어 있는 버퍼를 가리키는 포인터
    @param yLen [in] 복호화할 스트링의 길이
    @param param [in] FPEParameterSet 포인터
    @param key [in] Octet string 타입의 key binary 데이터
    @param keyLen [in] key material의 바이트 단위 길이
    @param tweak [in] tweak 스트링이 저장되어 있는 버퍼를 가리키는 포인터
    @param tweakLen [in] tweak 스트링의 길이
    @param iv [in] 이니셜 벡터
    @retval ER_FPE_INVALID_RADIX invald radix value
    @retval ER_FPE_INVALID_X_LENGTH invald x length
    @retval ER_FPE_INVALID_Y_LENGTH invald y length
    @retval ER_FPE_INVALID_ADDITION invald blockwise addition input lenth

    \e in 버퍼에 저장되어 있는 스트링을 FPEParameterSet와 key, tweak의 정보에
    따라 복호화하여 결과를 \e out 버퍼에 출력한다. 주의할 점은, Octet string 형태인 key와 달리
    y, tweak은 0x00..(0x00+radix-1) 범위의 Charater set으로 구성된 스트링의 형태여야 점이다.
    따라서 y, tweak을 구성하는 Character 중에서 0x00+radix-1보다 큰 값을 갖는 Charater가 존재할 시
    정상적인 암복호화가 이루어질 수 없다.
    출력값인 x 역시 위의 Charater set으로 구성된 스트링의 형태이다.
*/
LIBSPEC_PE
BWT POPFPE_Decrypt(void *x, BWT *xLen, void *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, void *tweak, BWT tweakLen, BYTE *iv);

BWT FSE2BT16(BT16 *y, BWT *yLen, BT16 *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, BT16 *tweak, BWT tweakLen, BYTE *iv);

BWT FSD2BT16(BT16 *x, BWT *xLen, BT16 *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, BT16 *tweak, BWT tweakLen, BYTE *iv);

BWT FSE2BYTE(BYTE *y, BWT *yLen, BYTE *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT FSD2BYTE(BYTE *x, BWT *xLen, BYTE *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT CHAR_ADD(char *a, char *b);

BWT BLOCK_ADDBT16(BT16 *a, BWT aLen, BT16 *b, BWT bLen, BWT radix);

BWT BLOCK_SUBBT16(BT16 *a, BWT aLen, BT16 *b, BWT bLen, BWT radix);

BWT BLOCK_ADDBYTE(BYTE *a, BWT aLen, BYTE *b, BWT bLen, BWT radix);

BWT BLOCK_SUBBYTE(BYTE *a, BWT aLen, BYTE *b, BWT bLen, BWT radix);

/** @ingroup FPE
 * @brief FPEParameterSet를 초기화한다(extended version).
 * @param[out] param 초기화할 FPEParameterSet를 가리키는 포인터
 *
 * FPE의 운영에 관한 정보를 입력받아 FPEParameterSet를 초기화한다.
 *
 * param은 미리 메모리 할당이 이루어진 상태여야 한다.
 */
LIBSPEC_PE
BWT POPFPE_InitializeEx(FPEParameterSet *param, void *bcKey, BWT radix, BYTE *key, BWT keyLen, BYTE *tweak, BWT tweakLen, BWT inLen, AlgDesc fpeAlg, AlgDesc bcipherAlg, AlgDesc hashAlg);

/** @ingroup FPE
 * @brief x로 입력받은 스트링를 암호화하여 y으로 출력한다.
 * @param[out] y output ciphertext
 * @param[out] yLen output ciphertext length
 * @param[in] x input plaintext
 * @param[in] xLen input plaintext length
 * @param[in] param POPFPE_InitializeEx()로 initialize한 FPEParameterSet
 */
LIBSPEC_PE
BWT POPFPE_EncryptEx(void *y, BWT *yLen, void *x, BWT xLen, FPEParameterSet *param, void *bcKey, void *tweak, BWT tweakLen, BYTE *iv);

/** @ingroup FPE
 * @brief y로 입력받은 스트링를 복호화하여 x으로 출력한다.
 * @param[out] x
 * @param[out] xLen
 * @param[in] y
 * @param[in] yLen
 * @param[in] param POPFPE_InitializeEx()로 initialize한 FPEParameterSet
 */
LIBSPEC_PE
BWT POPFPE_DecryptEx(void *x, BWT *xLen, void *y, BWT yLen, FPEParameterSet *param, void *bcKey, void *tweak, BWT tweakLen, BYTE *iv);

/** @ingroup FPE */
LIBSPEC_PE
void FPEParameterSet_Free(FPEParameterSet *param);

BWT FSE2BYTEEX(BYTE *y, BWT *yLen, BYTE *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT FSD2BYTEEX(BYTE *x, BWT *xLen, BYTE *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT FSE2BT16EX(BT16 *y, BWT *yLen, BT16 *x, BWT xLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

BWT FSD2BT16EX(BT16 *x, BWT *xLen, BT16 *y, BWT yLen, FPEParameterSet *param, BCipherKey *bcKey, BYTE *tweak, BWT tweakLen, BYTE *iv);

#ifdef __cplusplus
}
#endif

#endif /* _FPE_OP_H_ */
