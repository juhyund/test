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
    @brief n ��Ʈ���� �۰ų� ���� ũ�⸦ ���� ������ �� a�� �����ϴ� �Լ�
    @param[out] a ������ ������ ��°� a
    @param[in] n ������ �� a�� ���� �� �ִ� �ִ��� ��Ʈ ũ�� �Է�
    @sa MINT, MINT_Rand_Functions

    n ��Ʈ���� �۰ų� ���� ũ�⸦ ���� ������ �� a�� �����Ѵ�.
    ��, 0 <= n < 2^n �� ���´�.
*/
LIBSPEC_CE
void MINT_Rand(MINT *a, BWT n);

/**
    @ingroup MINT
    @brief y = a + b
    @param[out] y ������ ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] b MINT* Ÿ���� operand
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
    @param[out] y ������ ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] b MINT* Ÿ���� operand
    @return y == 0 �̸� 0, a > b �̸� 1, a < b �̸� -1�� return �Ѵ�.
    @sa MINT, MINT_Arith_Functions

    y = |a - b|
    y�� a - b�� ���밪�� ����ϰ� a - b�� ��ȣ�� 0, 1, -1�� return �Ѵ�.
*/
LIBSPEC_CE
int MINT_Sub(MINT *y, const MINT *a, const MINT *b);

/**
    @ingroup MINT
    @brief y = |a - n|
    @param[out] y ������ ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] n BWT Ÿ���� operand
    @return y == 0 �̸� 0, a > n �̸� 1, a < n �̸� -1�� return �Ѵ�.
    @sa MINT, MINT_Arith_Functions

    y = |a - n|
    y�� (a - n)�� ���밪�� ����ϰ�, (a - n)�� ��ȣ�� 0, 1, -1�� return �Ѵ�.
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
    @param[out] y a�� b�� �ִ�����(GCD) ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] b MINT* Ÿ���� operand
    @sa MINT, MINT_Arith_Functions

    y = GCD(a, b)
    a, b�� �ִ����� y�� ����Ѵ�.

*/
LIBSPEC_CE
void MINT_BinGCD(MINT *y, const MINT *a, const MINT *b);

/**
    @ingroup MINT
    @brief mod n���� a�� ���� ���� y(= a^(-1) mod n)�� ���Ѵ�.
    @param[out] y a�� mod n�� ���� ���� ���� ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] n MINT* Ÿ���� operand
    @retval ER_MINT_NOT_INVERTIBLE if a is not invertible
    @sa MINT, MINT_Arith_Functions

    y = a^(-1) mod n
    mod n�� ���� a�� ���� ���� y�� ����Ѵ�.
    GCD(a, n) == 1 �� ��쿡�� ������ ������ y�� ��µǰ�, 1�� return �ȴ�.
    GCD(a, n) != 1 �� ��쿡�� ������ ������ �������� �����Ƿ� -1�� return �ȴ�.
*/
LIBSPEC_CE
ERT MINT_Inverse(MINT *y, const MINT *a, const MINT *n);

/**
    @ingroup MINT
    @brief y = a * n
    @param[out] y ������ ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] n BWT Ÿ���� operand
    @sa MINT, MINT_Mult_Functions
*/
LIBSPEC_CE
void MINT_MultInteger(MINT *y, const MINT *a, BWT n);

/**
    @ingroup MINT
    @brief y = a * b
    @param[out] y ������ ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] b MINT* Ÿ���� operand
    @sa MINT, MINT_Mult_Functions
*/
LIBSPEC_CE
void MINT_Mult(MINT *y, const MINT *a, const MINT *b);

/**
    @ingroup MINT
    @brief y = a^2 = a * a
    @param[out] y ������ ���
    @param[in] a MINT* Ÿ���� operand
    @sa MINT, MINT_Mult_Functions
*/
LIBSPEC_CE
void MINT_Square(MINT *y, const MINT *a);

/**
    @ingroup MINT
    @brief q = (a / n), r = (a % n)
    @param[out] q MINT* Ÿ���� �������� �� ���
    @param[out] r BWT* Ÿ���� �������� ������ ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] n BWT Ÿ���� operand
    @sa MINT, MINT_Div_Functions

    a�� n���� ���� ���� q, �������� r�� ����Ѵ�.
*/
LIBSPEC_CE
ERT MINT_DivInteger(MINT *q, BWT *r, const MINT *a, BWT n);

/**
    @ingroup MINT
    @brief q = (a / n), r = (a % n)
    @param[out] q MINT* Ÿ���� �������� �� ���
    @param[out] r MINT* Ÿ���� �������� ������ ���
    @param[in] a MINT* Ÿ���� operand
    @param[in] n MINT* Ÿ���� operand
    @sa MINT, MINT_Div_Functions

    a�� n���� ���� ���� q, �������� r�� ����Ѵ�.
*/
LIBSPEC_CE
ERT MINT_Div(MINT *q, MINT *r, const MINT *a, const MINT *n);

/**
    @ingroup MINT
    @brief a = a mod n
    @param[in,out] a MINT* Ÿ���� �Է°� ���
    @param[in] n MINT* Ÿ���� �Է�
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
