/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _MINT_COMMON_H_
#define _MINT_COMMON_H_

/** @defgroup MATH Mathematical Foundation
 * @ingroup CC
 * Mathematical Foundation
 */

/** @defgroup MINT Multi-Precision Integer
 * @ingroup MATH
 * @brief Multi-Precision Integer Arithmetic
 *
 * MINT는 다정도 정수 연산 모듈로서, 정수를 표현하는 기본 타입인 MINT를
 * 정의하고 그에 관련된 Set/Get 등의 기본 함수들과 연산함수들이 정의되어 있다.
 */

/** @ingroup MINT
    @file mint.h
    @brief MINT 타입과 연산 함수 선언

    큰수의 계산을 위한 데이터 형과 연산 함수
    MINT(Multi Precision Integer) 타입
    MINT 연산 함수
*/

#include <memory.h>
#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
    @ingroup MINT
    @brief MINT를 이용하여 다룰 수 있는 큰수의 비트 크기
    @sa MINT_MAX_LEN, MINT

    MINT를 이용하여 다룰 수 있는 큰수의 비트 크기이다.

    즉, 1024 비트의 RSA나 DLP를 다룰 경우 1024 이상,
    2048 비트를 다룰 경우 2048 이상,
    4096 비트를 다를 경우 4096 이상이 되어야 한다.
*/
#define MINT_MANIPULATED_DATA_BIT_LEN 2048

/**
    @ingroup MINT
    @brief MINT의 data 어레이의 최대 크기
    @sa MINT_MANIPULATED_DATA_BIT_LEN, BWT_BIT_LEN, MINT

    MINT의 data 에레이의 최대 크기를 정의한다.
    단위는 BWT 타입의 어레이 크기이다.
    다루는 큰 수 크기의 2배의 크기를 다룰 수 있도록 값을 정해야 한다.

    즉, BWT 타입이 32 비트 타입이라고 가정할 때, 최대 1024 비트의 연산을 지원할려면 2*1024/32의 크기를 정해준다.
*/
#define MINT_MAX_LEN  ((MINT_MANIPULATED_DATA_BIT_LEN/BWT_BIT_LEN)*2+2)


/** 
    @ingroup MINT
    @brief MINT 타입의 크기 

    MINT타입의 바이트 단위 크기이다.
*/
#define MINT_SIZE ((MINT_MAX_LEN+1)*BWT_BYTE_LEN)

/**
    @ingroup MINT
    @brief Window 알고리즘을 이용한 멱승 연산에서 사용하는 Windows의 비트 크기
    @sa MINT_ExpWin()

    Window 알고리즘을 이용한 멱승 연산에서 사용하는 Windows의 비트 크기이다.
*/
#define MINT_WINDOW_BIT_LEN_FOR_EXP 4

/**
    @ingroup MINT
    @brief MINT_WINDOW_BIT_LEN_FOR_EXP의 간략한 표현
    @sa MINT_WINDOW_BIT_LEN_FOR_EXP, MINT_ExpWin()

    프로그램시 MINT_WINDOW_BIT_LEN_FOR_EXP를 매번 쓰기에는 너무 길기에 MINT_WIN_LEN으로 alias 한 것이다.
*/
#define MINT_WIN_LEN  (MINT_WINDOW_BIT_LEN_FOR_EXP)
    
/** @ingroup MINT
 * @brief Multi-precision (large) integer
 * @note Since this struct uses fixed size array as a data store,
 * it is easy to increase memory footage. <strong>So, be careful.</strong>
 * @see BWT, MINT_MAX_LEN
*/
typedef struct {
  BWT len;                /**< @brief number of used elements in data array */
  BWT data[MINT_MAX_LEN]; /**< @brief actual data array contains
							(msb) data[len-1]....data[0] (lsb). */
} MINT;


/** @ingroup MINT */
typedef struct {
  BWT ri;
  MINT RR;
  MINT N;
  MINT Ni;
  BWT Ni_0[2];
} MONT;

/** @ingroup MINT
    @brief MINT가 홀수인지를 테스트
    @sa MINT_IsEven

    MINT가 홀수인지를 테스트한다. 훌수이면 1을, 아니면 0을 리턴한다.
    */
#define MINT_IsOdd(a)  (((a)->len > 0) && ((a)->data[0] & 0x01))

/** @ingroup MINT
    @brief MINT가 짝수인지를 테스트
    @sa MINT_IsOdd

    MINT가 짝수인지를 테스트한다. 훌수이면 1을, 아니면 0을 리턴한다.
    */
#define MINT_IsEven(a) (((a)->len == 0) || !(((a)->data[0])&0x01))

/** @ingroup MINT
    @brief MINT가 1인지를 테스트한다.
    @sa MINT_IsZero MINT_IsNonZero

    MINT가 1인지를 테스트한다. 1이면 1을, 아니면 0을 리턴한다.
    */
#define MINT_IsOne(a)  (((a)->data[0]==0x01) && ((a)->len==1))

/** @ingroup MINT
    @brief MINT가 0인지를 테스트한다.
    @sa MINT_IsOne MINT_IsNonZero

    MINT가 0인지를 테스트한다. 0이면 1을, 아니면 0을 리턴한다.
    */
#define MINT_IsZero(a) (!((a)->len))

/** @ingroup MINT
    @brief MINT가 0이 아닌인지를 테스트한다.
    @sa MINT_IsOne MINT_IsZero

    MINT가 0인지를 테스트한다. 0이 아니면 1을, 0이면 0을 리턴한다.
    */
#define MINT_IsNonZero(a) ((a)->len)


/**
    @ingroup MINT
    @brief a를 0으로 설정
    @sa MINT, MINT_Set_Functions

    MINT* 값 a를 0으로 설정한다.
    즉, a->len = 0 이 된다.
*/
#define MINT_Set0(a)    (((a)->len) = 0)

/** @ingroup MINT
 * @brief Allocate new memory for a MINT structure and set to zero.
 * @return [out] NULL if an error occurred
 * @see MINT
 */
LIBSPEC
MINT* MINT_New(void);

/** @ingroup MINT
 * @brief Free memory held by a MINT structure.
 * @param[in] a MINT to be deleted
 * @return nothing even if there was an error
 * @see MINT
 */
LIBSPEC
void MINT_Del(MINT* a);

/**
    @ingroup MINT
    @brief a를 n으로 설정
    @param[out] a MINT* 타입으로 n 값이 설정되어 출력된다.
    @param[in] n BWT 타입으로 a를 설정할 입력이다.
    @sa MINT, MINT_Set_Functions

    MINT* 값 a를 n으로 설정한다.
    n은 BWT가 표현할 수 있는 최대값 보다 작아야 한다.
    즉, a->len = 1; a->data[0] = n; 이 된다.
*/
LIBSPEC
void MINT_SetByInteger(MINT *a, BWT n);

/**
    @ingroup MINT
    @brief a를 hexaString의 값으로 설정
    @param[out] a MINT* 타입으로 hexaString의 값이 설정되어 출력된다.
    @param[in] hexaString const char * 타입으로 a를 설정할 16진수로 표현된 null-terminated ASCII 스트링 입력이다.
    @retval SUCCESS 정상적으로 수행되었을 때의 리턴 값이다.
    @retval FAIL hexaString의 입력중에 '0'~'9', 'a'~'f', 'A'~'F'에 해당하지 않는
    문자가 포함되어 있을때 발생하는 에러이다.
    @sa MINT, MINT_Set_Functions, MINT_RefreshLength()

    MINT* 값 a를 16진수로 표현된 null-terminated ASCII 스트링인 hexaString으로 설정한다.
    hexaString[0]에 저장된 ASCII 값은 msb 4 비트를 표현하는 값이 된다.
    hexaString[strlen(hexaString)-1]에 저장된 ASCII 값은 lsb 4 비트를 표현하는 값이 된다.

    a->len는 a->data의 유효값의 크기가 아닌 hexaString의 입력크기에 따라 결정된다.
    그러므로 이 함수안에 MINT_RefreshLength()의 효과는 없다. 
*/
LIBSPEC
ERT MINT_SetByHexString(MINT *a, const char *hexaString);

/**
    @ingroup MINT
    @brief a를 byteLen 바이트 길이 만큼의 byteArray에 있는 값으로 설정
    @param[out] a MINT* 타입으로 byte의 값이 설정되어 출력된다.
    @param[in] byteArray const BYTE* 타입으로 a를 설정할 바이너리 스트링 입력이다.
    @param[in] byteLen BWT 타입으로 byteArray의 저장된 값의 바이트 길이 입력이다.
    @sa MINT, MINT_Set_Functions

    MINT* 값 a를 byteLen 바이트 길이 만큼의 byteArray에 있는 값으로 설정한다.
    즉 a = (msb) byteArray[0]||byteArray[1]||...||byteArray[byteLen-1] (lsb) 의
    값으로 설정된다.
*/
LIBSPEC
void MINT_SetByByteArray(MINT *a, const BYTE *byteArray, BWT byteLen);

/**
    @ingroup MINT
    @brief a를 b의 값으로 설정한다.
    @sa MINT, MINT_Set_Functions, MINT_Copy()

    a를 b의 값으로 설정한다.
    즉, a = b 가 된다.
    MINT_Copy()는 b의 모든 데이터를 a에 그대로 '복제'하지만,
    MINT_SetByMINT()는 큰수 b의 값을 a에 '설정'한다.
*/
#define MINT_SetByMINT(a, b) { (a)->len = (b)->len; memcpy((a)->data, (b)->data, ((a)->len)*BWT_BYTE_LEN); }

/**
    @ingroup MINT
    @brief a를 2^n의 값으로 설정한다.
    @param[out] a MINT* 타입의 출력이다.
    @param[in] n BWT 타입의 입력으로 2^n의 지수 n을 나타내는 입력이다. n은 MINT_MANIPULATED_DATA_BIT_LEN보다 작은 값이어야 한다.
    @sa MINT, MINT_Set_Functions

    a를 2^n의 값으로 설정한다(a = 2^n).
    즉, 1이후에 n개의 0을 갖는(1000...00) 이진수 값을 설정한다.
    n은 MINT_MANIPULATED_DATA_BIT_LEN보다 작은 값이어야 한다.
*/
LIBSPEC
void MINT_SetBy2ExpN(MINT *a, BWT n);

/**
    @ingroup MINT
    @brief a의 값을 16 진수로 표현한 ASCII 스트링을 buf에 출력한다.
    @param[out] buf char* 타입으로 a의 값이 null-terminated ASCII 스트링이 출력된다.
    @param[in,out] byteLen IN: buf의 메모리 버퍼 크기, OUT: BWT* 타입의 buf에 저장된 바이너리의 바이트 크기 출력이다.
    @param[in] a const MINT* 타입으로 buf에 출력할 값을 가진 입력이다.
    @retval FAIL NULL 값 입력 등의 실패
    @retval SUCCESS mint to hex string 변환 성공
    @retval ER_OUT_BUFF_ERSIZE_IS_SMALL 출력 버퍼의 메모리 크기가 출력할 데이터의 메모리보다 작을 시
    @sa MINT, MINT_Write_Functions

    a의 0이 아닌 msb의 4 비트가 buf[0]에 출력되고, lsb의 4 비트가 buf[strlen(buf)-1]에 출력된다.

    buf는 a의 값을 16 진수로 효현한 null-terminated ASCII 스트링으로 출력할 수 있을 만큼 충분한 메모리가 할당되어 있어야 한다.
    즉, ((MINT_GetBitLength(a)/4)+1) 바이트 이상의 메모리가 할당되어 있어야 한다.
    또는 ((a->len)*BWT_BYTE_LEN*2)+1 바이트 이상을 할당하여 사용하거나,
    a->data의 최대 크기인 ((MINT_MAX_LEN*BWT_BYTE_LEN*2)+1) 바이트 이상을 할당하여 사용하여도 된다.
*/
LIBSPEC
ERT MINT_WriteInHexString_N(char *buf, BWT *bytelen, const MINT *a);

/**
    @ingroup MINT
    @brief a의 값을 16 진수로 표현한 ASCII 스트링을 BWT_BIT_LEN 비트 단위로 buf에 출력한다.
    @param[out] buf char* 타입으로 a의 값이 null-terminated ASCII 스트링이 출력된다.
    @param[in,out] byteLen IN: buf의 메모리 버퍼 크기, OUT: BWT* 타입의 buf에 저장된 바이너리의 바이트 크기 출력이다.
    @param[in] a const MINT* 타입으로 buf에 출력할 값을 가진 입력이다.
    @retval FAIL NULL 값 입력 등의 실패
    @retval SUCCESS mint to hex string 변환 성공
    @retval ER_OUT_BUFF_ERSIZE_IS_SMALL 출력 버퍼의 메모리 크기가 출력할 데이터의 메모리보다 작을 시
    @sa MINT, MINT_Write_Functions

    a의 msb의 4 비트가 buf[0]에 출력되고, lsb의 4 비트가 buf[strlen(buf)-1]에 출력된다.
    a의 msb가 0 으로 이루어진 경우에도 앞에 0이 출력된다.
        
    buf는 a의 값을 16 진수로 BWT_BIT_LEN 비트 단위씩 null-terminated ASCII 스트링으로 출력할 수 있을 만큼 충분한 메모리가 할당되어 있어야 한다.
    즉, ((MINT_GetBitLength(a)/4)+(MINT_GetBitLength(a)/BWT_BIT_LEN)+1) 바이트 이상의 메모리가 할당되어 있어야 한다.
    또는 (a->len)*((BWT_BYTE_LEN*2)+1)+1 바이트 이상을 할당하여 사용하거나,
    a->data의 최대 크기인 ((MINT_MAX_LEN*((BWT_BYTE_LEN*2)+1))+1) 바이트 이상을 할당하여 사용하여도 된다.
*/
LIBSPEC
ERT MINT_WriteInHexStringBWT_N(char *buf, BWT *bytelen, const MINT *a);

/**
    @ingroup MINT
    @brief a의 값을 바이너리로 byteArray에 출력하고 그 바이트 길이를 byteLen에 출력한다.
    @param[out] byteArray a 값이 BYTE* 타입의 바이너리로 저장되는 출력이다.
    @param[in,out] byteLen IN: byteArray의 메모리 버퍼 크기, OUT: BWT* 타입의 byteArray에 저장된 바이너리의 바이트 크기 출력이다.
    @param[in] a const MINT* 타입으로 byteArray에 출력할 값을 가진 입력이다.
    @sa MINT, MINT_Write_Functions

    a의 값을 바이너리로 byteArray에 출력하고 그 바이트 길이를 byteLen에 출력한다.
    즉, (msb) byteArray[0]||byteArray[1]||...||byteArray[byteLen-1] (lsb) = a 가 된다.

    byteArray는 a의 값이 출력될 수 있을 만큼 충분한 메모리가 할당되어 있어야 한다.
    즉, (MINT_GetBitLength(a)/8) 바이트 이상의 메모리가 할당되어 있어야 한다.
    또는 a->data의 최대 크기인 (MINT_MAX_LEN*BWT_BYTE_LEN) 바이트를 할당하여 사용하여도 된다.
*/
LIBSPEC
void MINT_WriteInByteArray(BYTE *byteArray, BWT *byteLen, const MINT *a);

/**
    @ingroup MINT
    @brief a의 값을 바이너리로 byteArray에 출력하고 그 바이트 길이를 byteLen에 출력한다.
    @param[out] byteArray a 값이 BYTE* 타입의 바이너리로 LSB부터 nByte만큼 저장되는 출력이다.
    @param[in] nByte BWT 타입의 byteArray에 저장할 a의 바이너리 바이트 크기(LSB부터) 출력이다.
    @param[in] a const MINT* 타입으로 byteArray에 출력할 값을 가진 입력이다.
    @sa MINT, MINT_Write_Functions

    a의 값을 LSB부터 nByte 만큼 바이너리로 byteArray에 출력한다.
    즉, (msb) byteArray[0]||byteArray[1]||...||byteArray[nByte-1] (lsb) = a mod ((2^8)^nByte) 가 된다.

    a의 값은 nByte이상의 충분한 메모리가 할당되어 있어야 한다.
    또는 a->data의 최대 크기인 (MINT_MAX_LEN*BWT_BYTE_LEN) 바이트를 할당하여 사용하여도 된다.
*/
LIBSPEC
void MINT_WriteLSNByteInByteArray(BYTE *byteArray, BWT nByte, const MINT *a);

/** @ingroup MINT
    @brief RSA 의 integer를 octet string으로 전환하는 함수
    @retval FAIL NULL 값 입력 등의 실패
    @retval SUCCESS Integer to Octet string 변환 성공
    @retval ER_OUT_BUFF_ERSIZE_IS_SMALL 출력 버퍼의 메모리 크기가 출력할 데이터의 메모리보다 작을 시
    @sa MINT_WriteInByteArray

    PKCS#1 ver 2.0(RFC2437)에 설명된 integer를 octet string으로
    전환하는 함수이다.  이전에는 MINT_WriteInByteArray() 함수를
    사용하였으나, 이 함수에서는 상위 byte들의 값이 0일 경우 이를 의미없는
    값으로 판단하고 삭제해버리기 때문에 항상 길이가 modulus 길이와
    같아야만 하는 RSA 서명값 생성에서 가끔 문제를
    일으켰다.  이 함수는 MINT_WriteInByteArray()와 거의 같은 역할을 하나
    PKCS#1에서 설명한 대로 입력의 길이를 절대 변환하지 않고 그대로 내보내는
    특성을 가진다.
    */
LIBSPEC
ERT MINT_I2OSP(
		BYTE *byteArray, /**< [out] 전환된 octet string */
		BWT *byteLen, /**< [in,out] IN: byteArray의 메모리 버퍼 크기, OUT: 전환된 octet string의 길이 */
		const MINT *a /**< [in] 전환하려는 integer */
		);

/**
    @ingroup MINT
    @brief a의 값을 C 구조체 형식으로 str에 출력한다.
    @param[out] buf char* 타입으로 a 값을 구조체 형식으로 출력하는 null-terminated 스트링 출력이다.
    @param[in,out] byteLen IN: buf의 메모리 버퍼 크기, OUT: BWT* 타입의 buf에 저장된 바이너리의 바이트 크기 출력이다.
    @param[in] a const MINT* 타입으로 str에 출력할 값을 가진 입력이다.
    @retval FAIL NULL 값 입력 등의 실패
    @retval SUCCESS mint to hex string 변환 성공
    @retval ER_OUT_BUFF_ERSIZE_IS_SMALL 출력 버퍼의 메모리 크기가 출력할 데이터의 메모리보다 작을 시
    @sa MINT, MINT_Write_Functions

    str에 
    "{{a->len}, {a->data[0], a->data[1], ... , a->data[a->len-1]}}"
    으로 출력된다. (null-terminated string)
    buf는 (11+((a->len)*((BWT_BYTE_LEN*2)+2))) 바이트 이상이 할당되어 있어야 한다.
    또는 최대 크기인 (11+(MINT_MAX_LEN*((BWT_BYTE_LEN*2)+2))) 바이트를 할당하여 사용하여도 된다.
*/
LIBSPEC
ERT MINT_WriteInStructForm_N(char *buf, BWT* bytelen, const MINT *a);

/**
    @ingroup MINT
    @brief a를 y에 복제한다.
    @sa MINT, MINT_Basic_Functions, MINT_SetByMINT()

    a의 MINT struct의 모든 멤버 값을 y에 복제한다.

    MINT_Copy()는 a의 모든 데이터를 y에 그대로 '복제'하지만,
    MINT_SetByMINT()는 큰수의 값을 '설정'한다.
*/  
#define MINT_Copy(y, a) {if ((y) != (a)) memcpy((y), (a), MINT_SIZE);}

/**
    @ingroup MINT
    @brief a의 길이를 재정의 한다.
    @sa MINT, MINT_Basic_Functions

    a->len의 값을 a의 값을 가지고 재정의 한다.
    즉, a->data의 msb 영역부터 0을 가진 경우, 0을 갖지 않을 때까지 a->len의 길이를 줄인다.
*/
#define MINT_RefreshLength(a); { while(((a)->len) && ((a)->data[((a)->len)-1] == 0)) ((a)->len)--; }

/**
    @ingroup MINT
    @brief a의 비트 길이를 얻어낸다.
    @param[in] a const MINT* 타입의 비트 길이를 알고자하는 변수 입력이다.
    @return [out] a의 비트 길이가 BWT 타입으로 return 된다.
    @retval FAIL 함수가 실패하였을 때
    @sa MINT, MINT_Basic_Functions

    a 값을 2 진수로 표현할 때 가지는 비트 길이를 출력한다.
*/
LIBSPEC
int MINT_GetBitLength(const MINT *a);

/**
    @ingroup MINT
    @brief a의 bit_index 위치에 있는 비트값을 판별한다.
    @sa MINT, MINT_Basic_Functions
    
    a->len > (bit_index/BWT_BIT_LEN) 여야 한다.
    만약 이 조건이 만족하지 않을 때에는 임의의 값이 출력된다.
    a의 bit_index 위치에 있는 bit이 0이면 0이, 1이면 1이 출력된다.
    bit_index는 0부터(lsb) MINT_GetBitLength(a)-1까지(msb) 가능하다.
*/
#define MINT_CheckBitByIndex(a, bit_index) ((((a)->data[(bit_index)/BWT_BIT_LEN])>>((bit_index)%BWT_BIT_LEN))&1)

/**
    @ingroup MINT
    @brief a와 b의 값을 비교한다.
    @param[in] a
    @param[in] b
    @return int 타입으로 a == b 이면 0, a > b 이면 1, a < b 이면 -2 이 return 된다.
    @retval FAIL NULL 값 입력 등의 실패
    @sa MINT, MINT_Basic_Functions

    a와 b의 값을 비교한다.
    a == b 이면 0,
    a > b 이면 1,
    a < b 이면 -2
    이 return 된다.
*/
LIBSPEC
int MINT_Compare(const MINT *a, const MINT *b);

#ifdef __cplusplus
}
#endif

#endif /* _MINT_COMMON_H_ */
