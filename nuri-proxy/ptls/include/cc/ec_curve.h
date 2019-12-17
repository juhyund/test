/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_EC_CURVE_H_
#define _PCIS_EC_CURVE_H_

#include "ec_common.h"

/** @file
 * @brief Well-known elliptic curves
 */

/** @addtogroup EC
 * @{ */
/* 0x01000000: defined SEC
 * 0x02000000: defined ANSI X9.62 
 * 0x04000000: defined NIST
 * 0x08000000: defined BSI (ex. brainpool)
 * 0x00100000: is random curve
 * 0x00200000: is koblitz curve
 * 0x00400000: is twist curve
 * 0x00010000: over prime field
 * 0x00020000: over binary field
 * lower 16 bits: field size
 */
#define PCIS_EC_CURVE_P192     (0x07110000|192) /**< NIST curve P-192 */
#define PCIS_EC_CURVE_P224     (0x05110000|224) /**< NIST curve P-224 */
#define PCIS_EC_CURVE_P256     (0x07110000|256) /**< NIST curve P-256 */
#define PCIS_EC_CURVE_P384     (0x05110000|384) /**< NIST curve P-384 */
#define PCIS_EC_CURVE_P521     (0x05110000|521) /**< NIST curve P-521 */

#define PCIS_EC_CURVE_B163     (0x05120000|163) /**< NIST curve B-163 */
#define PCIS_EC_CURVE_B233     (0x05120000|233) /**< NIST curve B-233 */
#define PCIS_EC_CURVE_B283     (0x05120000|283) /**< NIST curve B-283 */
#define PCIS_EC_CURVE_B409     (0x05120000|409) /**< NIST curve B-409 */
#define PCIS_EC_CURVE_B571     (0x05120000|571) /**< NIST curve B-571 */

#define PCIS_EC_CURVE_K163     (0x05220000|163) /**< NIST curve K-163 */
#define PCIS_EC_CURVE_K233     (0x05220000|233) /**< NIST curve K-233 */
#define PCIS_EC_CURVE_K283     (0x05220000|283) /**< NIST curve K-283 */
#define PCIS_EC_CURVE_K409     (0x05220000|409) /**< NIST curve K-409 */
#define PCIS_EC_CURVE_K571     (0x05220000|571) /**< NIST curve K-571 */

#define PCIS_EC_CURVE_P256K1   (0x03210000|256) /**< SECP curve secp256k1 */
#define PCIS_EC_CURVE_BPP256R1 (0x08110000|256) /**< BSI curve brainpoolP256r1 */
#define PCIS_EC_CURVE_BPP384R1 (0x08110000|384) /**< BSI curve brainpoolP384r1 */

/** @} */

/** @ingroup EC
 * @brief Set group parameter by curve nid
 * @retval SUCCESS on success
 * @retval FAIL on failure
 */
LIBSPEC
ERT PCIS_EC_Group_SetByNid(
		PCIS_EC_Group *E, /**< [out] 타원 곡선 context */
		unsigned int curve_id /**< [in] context를 구성할 정의된 타원 곡선 ID*/
		);

#endif /* _PCIS_EC_CURVE_H_ */
