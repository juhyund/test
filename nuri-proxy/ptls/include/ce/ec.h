/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_EC_H_
#define _PCIS_EC_H_

#include "ec_common.h"
#ifdef EXPORT_CE
#include "ce_dll.h"
#else
#define LIBSPEC_CE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup EC
 * @brief Check if an EC Point is on the curve
 * @return [out] result
 * @retval non-zero true
 * @retval 0 false
 * @see PCIS_EC_Point, PCIS_EC_Group
 */
LIBSPEC_CE
int PCIS_EC_Point_IsOnCurve(
		const PCIS_EC_Point *P, /**< [in] input point */
		const PCIS_EC_Group *E /**< [in] curve information */
		);

/** @ingroup EC
 * @brief Basic scalar multiplication (aka point multiplication) of a point
 */
LIBSPEC_CE
ERT PCIS_EC_Point_Mult(
		PCIS_EC_Point *P, /**< [out] multiplication result */
		const MINT *k, /**< [in] multiplier */
		const PCIS_EC_Point *A, /**< [in] base point */
		PCIS_EC_Group *E /**< [in] elliptic curve group */
		);

/** @ingroup EC
 * @brief Simultaneous scalar multiplication of points A and E->G
 */
LIBSPEC_CE
ERT PCIS_EC_Point_Mult2(
		PCIS_EC_Point *P, /**< [out] multiplication result */
		const MINT *k, /**< [in] multiplier */
		const PCIS_EC_Point *A, /**< [in] base point */
		const MINT *k2, /**< [in] multiplier to the generator */
		PCIS_EC_Group *E /**< [in] elliptic curve group */
		);

PCIS_EC_Point* _PCIS_EC_Point_New();
void _PCIS_EC_Point_Del(PCIS_EC_Point *P);
PCIS_EC_Group* _PCIS_EC_Group_New(void);
void _PCIS_EC_Group_Del(PCIS_EC_Group *E);
ERT _PCIS_EC_Group_SetByNid(PCIS_EC_Group *E, unsigned int curve_id);
int _PCIS_EC_Point_Compare(const PCIS_EC_Point *A, const PCIS_EC_Point *B,
		const PCIS_EC_Group *E);
ERT _PCIS_EC_Point_MakeAffine(PCIS_EC_Point *P,
		const PCIS_EC_Point *A, const PCIS_EC_Group *E);

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_EC_H_ */
