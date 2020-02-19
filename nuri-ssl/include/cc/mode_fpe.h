/* vim:set ts=4:sw=4:cino=>4: */
#ifndef PCIS_CC_MODE_FPE_H
#define PCIS_CC_MODE_FPE_H

/** @defgroup MODE_FPE Format-Preserving Encryption
 * @ingroup BCIPHER
 * @brief Mode of operatoin: Format-Preserving Encryption
 * @since v3.2.2.0
 *
 * Standard-compliant NIST FPE methods: FF1(FFX) and FF3(BPS).
 * Unlike POPFFXEX and POPBPS, this FPE implementation is standard-compliant.
 * It produces correct output when used correctly.
 *
 * First initialize FpeParam structure using PCIS_CC_FPE_Initialize().
 * @code
 * FpeParam fpeParam;
 * ER_RET_IF(PCIS_CC_FPE_Initialize(&fpeParam, 10, PCIS_CC_FF1) != SUCCESS);
 * @endcode
 *
 * Before calling encryption and decryption function, we must prepare
 * BCipherKey. Note that we must use AES cipher only.
 * @code
 * BCipherKey *bcKey = NULL;
 * bcKey = BCIPHER_NewKey(AES);
 * BCIPHER_MakeKey(bcKey, test_key, keyLen, AES);
 * @endcode
 *
 * Now, we are ready to encrypt and decrypt.
 * @code
 * ret = PCIS_CC_FPE_Encrypt(ct, &ctLen, pt, ptLen, &fpeParam, bcKey, tweak, tweakLen);
 * @endcode
 *
 * Decryption is the same as encryption: same param, same key, same tweak.
 * @code
 * ret = PCIS_CC_FPE_Decrypt(pt, &ptLen, ct, ctLen, &fpeParam, bcKey, tweak, tweakLen);
 * @endcode
 */

/** @file
 * @ingroup MODE_FPE
 * Format Preserving Encryption modes */

#include "cc_define.h"
#include "bcipher_op.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup MODE_FPE
 * @{ */

#define FPE_MODE_FF1 1
#define FPE_MODE_FF2 2
#define FPE_MODE_FF3 3

/** @brief NIST FPE FF1 (FFX) method
 *
 * conceptually equivalent to POPFFXEX method
 */
#define PCIS_CC_FF1 FPE_MODE_FF1
/** @brief NIST FPE FF3 (BPS) method.
 *
 * conceptually equivalent to POPBPS method
 */
#define PCIS_CC_FF3 FPE_MODE_FF3

/** FPE pre-requisite parameter.
 * Must be initialized by PCIS_CC_FPE_Initialize() */
typedef struct {
	int mode; /**< @brief one of FPE_MODE_FF1 and FPE_MODE_FF3 */
	size_t radix;
	int minLen;
	int maxLen;
	int maxTLen;
	BYTE P[16]; /**< @brief pseudorandom permutation, current description of FPE uses fixed size P */
} FpeParam;

/** Initialize FPE parameter.
 * Must be called before using FpeParam structure.
 * @param[out] param
 * @param[in] radix
 * @param[in] mode must be one of PCIS_CC_FF1 and PCIS_CC_FF3.
 * @retval FAIL on fail
 * @retval SUCCESS on success
 */
LIBSPEC
ERT PCIS_CC_FPE_Initialize(FpeParam *param, BWT radix, int mode);

/** Encrypt input byte sequence.
 * @param[out] out must be of the size as \e outLen
 * @param[in,out] outlen IN: memory size of out, OUT: must be greater than or equal to \e inLen
 * @param[in] in must be of the size as \e inLen
 * @param[in] inLen
 * @param[in] param must be initialized by PCIS_CC_FPE_Initialize().
 * @param[in] bcKey must be prepared by BCIPHER_NewKey() and BCIPHER_MakeKey().
 * @param[in] tweak is optional(may be NULL) for PCIS_CC_FF1 but mandatory for
 * PCIS_CC_FF3. When not NULL, must be of the size as \e tweakLen.
 * @param[in] tweakLen
 * @retval FAIL on fail
 * @retval SUCCESS on success
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL out buffer's memmory is small.
 */
LIBSPEC
ERT PCIS_CC_FPE_Encrypt(BYTE *out, BWT *outLen, BYTE *in, BWT inLen,
		FpeParam* param, void *bcKey, BYTE *tweak, BWT tweakLen);

/** Decrypt input byte sequence.
 * This decryption function has the same signature as the encryption function.
 * @param[out] out must be of the size as \e outLen
 * @param[in,out] outlen IN: memory size of out, OUT: must be greater than or equal to \e inLen
 * @param[in] in must be of the size as \e inLen
 * @param[in] inLen
 * @param[in] param must be initialized by PCIS_CC_FPE_Initialize().
 * @param[in] bcKey must be prepared by BCIPHER_NewKey() and BCIPHER_MakeKey().
 * @param[in] tweak is optional(may be NULL) for PCIS_CC_FF1 but mandatory for
 * PCIS_CC_FF3. When not NULL, must be of the size as \e tweakLen.
 * @param[in] tweakLen
 * @retval FAIL on fail
 * @retval SUCCESS on success
 * @retval ER_OUT_BUFFER_SIZE_IS_SMALL out buffer's memmory is small.
 */
LIBSPEC
ERT PCIS_CC_FPE_Decrypt(BYTE *out, BWT *outLen, BYTE *in, BWT inLen,
		FpeParam* param, void *bcKey, BYTE *tweak, BWT tweakLen);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PCIS_CC_MODE_FPE_H */
