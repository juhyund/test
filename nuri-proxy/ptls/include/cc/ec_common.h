/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_EC_COMMON_H_
#define _PCIS_EC_COMMON_H_

/** @defgroup EC Elliptic Curve
 * @brief Elliptic Curve Arithmetic
 * @ingroup MATH
 */

/** @file
 * @ingroup EC
 * @brief Elliptic curve operation interface
 */

#include "mint_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup EC
 * @brief point on an elliptic curve
 * @see PCIS_EC_Group
 *
 * In affine coordinates a point on a curve represented as (x, y). For better
 * point addition cost, we use Jacobian coordinates. A point P(x, y) is
 * represented as (X, Y, Z) with x = X/Z^2 and y = Y/Z^3. When Z = 1, we have
 * x = X and y = Y, the same as affine coordinates. But, point addition will
 * usually gives Z not equal to 1. So when converting (X, Y, Z) to (x, y) we
 * need some additional multiplications and inversions.
 */
typedef struct {
	MINT *x; /**< @brief x-coordinate */
	MINT *y; /**< @brief y-coordinate */
	MINT *z; /**< @brief z-coordinate for projective coordinates. */
} PCIS_EC_Point;

#define EC_MULT_WINDOW 4
#define EC_MULT_WINDOW_MASK 0xf
#define EC_MULT_WINDOW_HALF 8
#define EC_MULT_WINDOW_FULL 16

/** @ingroup EC
 * @brief description of elliptic curve group
 * @see PCIS_EC_Point
 */
typedef struct _ec_group_st {
	int curve; /**< @brief curve name if named curve is used */
	int cofactor; /**< @brief cofactor of the group */
	MINT *p; /**< @brief underlying finite field definition.
			   modulus for prime field. reduction polynomial for binary field.
			   */
	MINT *a; /**< @brief coefficient a of the curve equation.
			   y^2 = x^3 + a*x + b for prime curve.
			   y^2 + x*y = x^3 + a*x^2 + b for binary curve
			   */
	MINT *b; /**< @brief coefficient b of the curve equation.
			   y^2 = x^3 + a*x + b for prime curve.
			   y^2 + x*y = x^3 + a*x^2 + b for binary curve
			   */
	MINT *order; /**< @brief order of the group */
	PCIS_EC_Point *G; /**< @brief generator of the group */
	int a_fast; /**< @brief fast determination of a
					- -1 for general case
					- -3 if a = -3 mod p
					- 0 if a = 0 in GF2m
					- 1 if a = 1 in GF2m */
	int b_fast; /**< @brief fast determination of b
					- -1 for general case
					- 1 if b = 1 in GF2m */
	ERT (*point_isoncurve)(const PCIS_EC_Point*, const struct _ec_group_st *); /**< 타원곡선 위의 점인지 확인하는 함수 */
	ERT (*point_add)(PCIS_EC_Point*, const PCIS_EC_Point*, const PCIS_EC_Point*,
			const struct _ec_group_st *); /**< 점 덧셈 연산 함수 */
	ERT (*point_dbl)(PCIS_EC_Point*, const PCIS_EC_Point*,
			const struct _ec_group_st *); /**< 점 x2 연산 함수 */
	ERT (*point_inv)(PCIS_EC_Point*, const PCIS_EC_Point*,
			const struct _ec_group_st *); /**< 점 덧셈 역원 연산 함수 */
	int (*point_compress)(const PCIS_EC_Point*, const struct _ec_group_st *); /**< 점 표현 방식을 compress로 바꾸는 함수 */
	ERT (*point_decompress)(PCIS_EC_Point*, int, const struct _ec_group_st *); /**< 점 표현 방식을 decompress로 바꾸는 함수 */
	void (*field_add)(MINT*, const MINT*, const MINT*); /**< 필드 덧셈 연산 */
	void (*field_sub)(MINT*, const MINT*, const MINT*); /**< 필드 뺄셈 연산 */
	void (*field_mul)(MINT*, const MINT*, const MINT*); /**< 필드 곱셈 연산 */
	void (*field_sqr)(MINT*, const MINT*); /**< 필드 제곱 연산 */
	void (*field_inv)(MINT*, const MINT*); /**< 필드 역원 연산 */

	PCIS_EC_Point *Gi[EC_MULT_WINDOW_FULL]; /**< 점 곱셈 연산을 위한 사전 계산 데이터 */
	PCIS_EC_Point *Gin[EC_MULT_WINDOW_FULL]; /**< 점 곱셈 연산을 위한 사전 계산 데이터 */
	int precompute; /**< 사전 계산된 데이터가 존재하는 경우 1, 아니면 0 */
} PCIS_EC_Group;

/** @ingroup EC
 * @brief Set input point to be the point at infinity.
 */
#define PCIS_EC_Point_Set0(P) MINT_Set0((P)->z)

/** @ingroup EC
 * @brief Test if a point is the point at infinity
 */
#define PCIS_EC_Point_IsZero(P) MINT_IsZero((P)->z)

#define PCIS_EC_Point_Copy(P, A) {\
	MINT_Copy((P)->x, (A)->x);\
	MINT_Copy((P)->y, (A)->y);\
	MINT_Copy((P)->z, (A)->z);\
}

/** @ingroup EC
 * @brief Allocate new memory for an EC Point sturcture.
 * @return [out] non-NULL pointer to new EC Point structure
 * @retval NULL if an error occurred
 * @see PCIS_EC_Point
 */
LIBSPEC
PCIS_EC_Point* PCIS_EC_Point_New(void);

/** @ingroup EC
 * @brief Convert octet string to an EC Point and alloc new memory.
 * @return [out] non-NULL pointer to new EC Point structure
 * @retval NULL if an error occurred
 * @see PCIS_EC_Point
 */
LIBSPEC
PCIS_EC_Point* PCIS_EC_Point_NewFromOctetString(
		BYTE *buf, /**< [in] input octet string */
		size_t len, /**< [in] byte size of an input */
		const PCIS_EC_Group *E /**< [in] curve information */
		);

/** @ingroup EC
 * @brief Convert ASN Bit string to an EC Point.
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @see PCIS_EC_Point
 */
LIBSPEC
ERT PCIS_EC_Point_ConvertFromASNBitStr(
		PCIS_EC_Point *P, /**< [out] target point */
		const BYTE *buf, /**< [in] input octet string */
		size_t len, /**< [in] byte size of an input */
		const PCIS_EC_Group *E /**< [in] curve information */
		);

/** @ingroup EC
 * @brief Convert octet string to an EC Point.
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @see PCIS_EC_Point
 */
LIBSPEC
ERT PCIS_EC_Point_ConvertFromOctetString(
		PCIS_EC_Point *P, /**< [out] target point */
		const BYTE *buf, /**< [in] input octet string */
		size_t len, /**< [in] byte size of an input */
		const PCIS_EC_Group *E /**< [in] curve information */
		);

/** @ingroup EC
 * @brief Compute comppressed y-bit
 * @return [out] result y-bit
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @see PCIS_EC_Point_Decompress
 */
LIBSPEC
int PCIS_EC_Point_Compress(
		const PCIS_EC_Point *P, /**< [in] original point */
		const PCIS_EC_Group *E /**< [in] curve information */
		);

/** @ingroup EC
 * @brief Recover y-coordinate from y-bit
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @see PCIS_EC_Point_Compress
 */
LIBSPEC
ERT PCIS_EC_Point_Decompress(
		PCIS_EC_Point *P, /**< [in,out] recovered point */
		int ybit, /**< [in] y-bit to determine y-coordinate */
		const PCIS_EC_Group *E /**< [in] curve information */
		);

/** @ingroup EC
 * @brief Convert an EC Point to octet string.
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @see PCIS_EC_Point
 */
LIBSPEC
ERT PCIS_EC_Point_ConvertToOctetString(
		const PCIS_EC_Point *P, /**< [in] target point */
		BYTE *buf, /**< [out] output octet string */
		BWT *len, /**< [out] output length */
		size_t field_len /**< [in] field size */
		);

/** @ingroup EC
 * @brief Convert coordinate of a point to affine.
 * @retval SUCCESS on success
 * @retval FAIL on fail
 * @retval ER_MINT_NOT_INVERTIBLE z좌표의 역원을 구할 수 없어 아핀변환 불가
 * @see PCIS_EC_Point, PCIS_EC_Group
 */
LIBSPEC
ERT PCIS_EC_Point_MakeAffine(
		PCIS_EC_Point *P, /**< [out] result */
		const PCIS_EC_Point *A, /**< [in] point to be made affine */
		const PCIS_EC_Group *E /**< [in] elliptic curve group */
		);

/** @ingroup EC
 * @brief Test if the two points are the same.
 * @return comparison result
 * @retval 0 same points
 * @retval 1 different points
 * @retval -1 error
 * @see PCIS_EC_Point
 *
 * @note There is no <em>'greater than'</em> or <em>'less than'</em>
 * between points over finite field.
 */
LIBSPEC
int PCIS_EC_Point_Compare(
		const PCIS_EC_Point *A, /**< [in] ec point */
		const PCIS_EC_Point *B, /**< [in] ec point */
		const PCIS_EC_Group *E /**< [in] elliptic curve group */
		);

/** @ingroup EC
 * @brief Free memory held by an EC Point structure.
 * @param[in] P EC Point to be deleted
 * @return nothing even if there was an error
 * @see PCIS_EC_Point
 */
LIBSPEC
void PCIS_EC_Point_Del(PCIS_EC_Point *P);

/** @ingroup EC
 * @brief Allocate new memory for an EC Group structure.
 * @return [out] non-NULL pointer to new EC Group structure
 * @retval NULL if an error occurred
 * @see PCIS_EC_Group
 */
LIBSPEC
PCIS_EC_Group* PCIS_EC_Group_New(void);

/** @ingroup EC
 * @brief Free memory held by an EC Group structure.
 * @param[in] E EC Group to be deleted
 * @return nothing even if there was an error
 * @see PCIS_EC_Group
 */
LIBSPEC
void PCIS_EC_Group_Del(PCIS_EC_Group *E);

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_EC_COMMON_H_ */
