#ifndef _MINT_H_
#define _MINT_H_

#include "mint_common.h"
#ifdef EXPORT_CE
#include "ce_dll.h"
#else
#define LIBSPEC_CE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
    @ingroup MINT
    @brief n 비트보다 작거나 같은 크기를 갖는 임의의 값 a를 생성하는 함수
    @param[out] a 생성된 임의의 출력값 a
    @param[in] n 임의의 값 a가 가질 수 있는 최대의 비트 크기 입력
    @sa MINT, MINT_Rand_Functions

    n 비트보다 작거나 같은 크기를 갖는 임의의 값 a를 생성한다.
    즉, 0 <= n < 2^n 을 갖는다.
*/
LIBSPEC_CE
void MINT_Rand(MINT *a, BWT n);

/**
    @ingroup MINT
    @brief y = a + b
    @param[out] y 덧셈의 결과
    @param[in] a MINT* 타입의 operand
    @param[in] b MINT* 타입의 operand
    @sa MINT, MINT_Arith_Functions

    y = a + b
    y->len = MAX(a->len, b->len)
*/
LIBSPEC_CE
void MINT_Add(MINT *y, const MINT *a, const MINT *b);

/**
    @ingroup MINT
    @brief y = a + n
    @sa MINT, MINT_Arith_Functions

    y = a + n
*/
LIBSPEC_CE
void MINT_AddInteger(
		MINT *y, /**< [out] result */
		const MINT *a, /**< [in] 1st operand */
		BWT n /**< [in] 2nd operand */
		);

/**
    @ingroup MINT
    @brief y = |a - b|
    @param[out] y 뺄셈의 결과
    @param[in] a MINT* 타입의 operand
    @param[in] b MINT* 타입의 operand
    @return y == 0 이면 0, a > b 이면 1, a < b 이면 -1을 return 한다.
    @sa MINT, MINT_Arith_Functions

    y = |a - b|
    y는 a - b의 절대값을 출력하고 a - b의 부호를 0, 1, -1로 return 한다.
*/
LIBSPEC_CE
int MINT_Sub(MINT *y, const MINT *a, const MINT *b);

/**
    @ingroup MINT
    @brief y = |a - n|
    @param[out] y 뺄셈의 결과
    @param[in] a MINT* 타입의 operand
    @param[in] n BWT 타입의 operand
    @return y == 0 이면 0, a > n 이면 1, a < n 이면 -1을 return 한다.
    @sa MINT, MINT_Arith_Functions

    y = |a - n|
    y는 (a - n)의 절대값을 출력하고, (a - n)의 부호를 0, 1, -1로 return 한다.
*/
LIBSPEC_CE
int MINT_SubInteger(MINT *y, const MINT *a, BWT n);

/** @ingroup MINT
 * @brief y = a - b mod m
 */
#define MINT_Sub_mod(y, a, b, m) {\
	if (_MINT_Compare((a), (b)) < -1) {\
		MINT_Sub((y), (a), (b));\
		MINT_Sub((y), (m), (y));\
	} else if (_MINT_Compare((a), (b)) > -1) {\
		MINT_Sub((y), (a), (b));\
	}\
	MINT_RefreshLength((y));\
}

/** @ingroup MINT
 * @brief y = a + b mod m
 */
#define MINT_Add_mod(y, a, b, m) {\
	MINT_Add((y), (a), (b));\
	while (_MINT_Compare((y), (m)) >= 0) MINT_Sub((y), (y), (m));\
	MINT_RefreshLength((y));\
}

/** @ingroup MINT
 * @brief y = 2*a mod m
 */
#define MINT_Double_mod(y, a, m) {\
	MINT_LeftShift2((y), (a), 1);\
	while (_MINT_Compare((y), (m)) > 0) MINT_Sub((y), (y), (m));\
	MINT_RefreshLength((y));\
}

/**
    @ingroup MINT
    @brief y = GCD(a, b)
    @param[out] y a와 b의 최대공약수(GCD) 출력
    @param[in] a MINT* 타입의 operand
    @param[in] b MINT* 타입의 operand
    @sa MINT, MINT_Arith_Functions

    y = GCD(a, b)
    a, b의 최대공약수 y를 출력한다.

*/
LIBSPEC_CE
void MINT_BinGCD(MINT *y, const MINT *a, const MINT *b);

/**
    @ingroup MINT
    @brief mod n에서 a의 곱셈 역원 y(= a^(-1) mod n)를 구한다.
    @param[out] y a의 mod n에 대한 곱셈 역원 출력
    @param[in] a MINT* 타입의 operand
    @param[in] n MINT* 타입의 operand
    @retval ER_MINT_NOT_INVERTIBLE if a is not invertible
    @sa MINT, MINT_Arith_Functions

    y = a^(-1) mod n
    mod n에 대한 a의 곱셈 역원 y를 출력한다.
    GCD(a, n) == 1 인 경우에만 곱셈의 역원이 y에 출력되고, 1이 return 된다.
    GCD(a, n) != 1 인 경우에는 곱셈의 역원이 존재하지 않으므로 -1이 return 된다.
*/
LIBSPEC_CE
ERT MINT_Inverse(MINT *y, const MINT *a, const MINT *n);

/**
    @ingroup MINT
    @brief y = a * n
    @param[out] y 곱셈의 결과
    @param[in] a MINT* 타입의 operand
    @param[in] n BWT 타입의 operand
    @sa MINT, MINT_Mult_Functions
*/
LIBSPEC_CE
void MINT_MultInteger(MINT *y, const MINT *a, BWT n);

/**
    @ingroup MINT
    @brief y = a * b
    @param[out] y 곱셈의 결과
    @param[in] a MINT* 타입의 operand
    @param[in] b MINT* 타입의 operand
    @sa MINT, MINT_Mult_Functions
*/
LIBSPEC_CE
void MINT_Mult(MINT *y, const MINT *a, const MINT *b);

/**
    @ingroup MINT
    @brief y = a^2 = a * a
    @param[out] y 제곱의 결과
    @param[in] a MINT* 타입의 operand
    @sa MINT, MINT_Mult_Functions
*/
LIBSPEC_CE
void MINT_Square(MINT *y, const MINT *a);

/**
    @ingroup MINT
    @brief q = (a / n), r = (a % n)
    @param[out] q MINT* 타입의 나눗셈의 몫 결과
    @param[out] r BWT* 타입의 나눗셈의 나머지 결과
    @param[in] a MINT* 타입의 operand
    @param[in] n BWT 타입의 operand
    @sa MINT, MINT_Div_Functions

    a를 n으로 나눈 몫을 q, 나머지를 r에 출력한다.
*/
LIBSPEC_CE
ERT MINT_DivInteger(MINT *q, BWT *r, const MINT *a, BWT n);

/**
    @ingroup MINT
    @brief q = (a / n), r = (a % n)
    @param[out] q MINT* 타입의 나눗셈의 몫 결과
    @param[out] r MINT* 타입의 나눗셈의 나머지 결과
    @param[in] a MINT* 타입의 operand
    @param[in] n MINT* 타입의 operand
    @sa MINT, MINT_Div_Functions

    a를 n으로 나눈 몫을 q, 나머지를 r에 출력한다.
*/
LIBSPEC_CE
ERT MINT_Div(MINT *q, MINT *r, const MINT *a, const MINT *n);

/**
    @ingroup MINT
    @brief a = a mod n
    @param[in,out] a MINT* 타입의 입력과 출력
    @param[in] n MINT* 타입의 입력
    @sa MINT, MINT_Div_Functions

    a = a mod n
*/
LIBSPEC_CE
ERT MINT_ModClassic(MINT *a, const MINT *n);

/**
    @ingroup MINT
    @brief y = g^e mod n
    @return
    @sa MINT, MINT_Exp_Functions

    y = g^e mod n
*/
LIBSPEC_CE
ERT MINT_ExpWin(
		MINT *y, /**< [out] result */
		const MINT *g, /**< [in] base */
		const MINT *e, /**< [in] exponent */
		const MINT *n, /**< [in] modulus */
		BWT winsize /**< [in] window size */
		);

#define MINT_wbits_of_expsize(b) \
	((b) > 671 ? 6 : \
	 (b) > 239 ? 5 : \
	 (b) >  79 ? 4 : \
	 (b) >  23 ? 3 : 1)

#define LWORD(t)    (((BWT)(t))&BWT_MASK)
#define HWORD(t)    (((BWT)((t)>>32))&BWT_MASK)

#define mul_add(r,a,w,c) { \
	DWT t; \
	t=(DWT)w * (a) + (r) + (c); \
	(r)= LWORD(t); \
	(c)= HWORD(t); \
}

#ifdef __cplusplus
}
#endif

#endif /* _MINT_H_ */
