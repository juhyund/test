#ifndef _PCIS_ECDSA_H_
#define _PCIS_ECDSA_H_

#include "pkcrypt_op.h"
#include "ecc.h"
#include "ec_curve.h"

/** @defgroup ECDSA ECDSA
 * @ingroup PKCRYPT_ALG
 * @brief ECDSA	(Elliptic-Curve Digital Signature Algorithm)
 *
 * You need to include these files in the application code.
 * @code
	#include "ecdsa.h" // for ECDSA operations
	#include "sha256.h" // for SHA256 symbol
 * @endcode
 *
 * code example
 * @code
	PCIS_ECDSA_Sig *sig = NULL;
	PCIS_ECDSA_PriKey *skey = NULL;
	PCIS_ECDSA_PubKey *pkey = NULL;
	PCIS_ECC_Param *param = NULL;
	BYTE M[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	PCIS_CC_Initialize(); // This must be called before using CIS.

	sig = PCIS_ECDSA_Sig_New();
	skey = PCIS_ECDSA_PriKey_New();
	pkey = PCIS_ECDSA_PubKey_New();
	param = PCIS_ECC_Param_New();

	// simple usage
	PCIS_ECC_SetParam(param, PCIS_EC_CURVE_P256);
	PCIS_ECDSA_GenKey(skey, pkey, param);
	PCIS_ECDSA_Sign(sig, M, sizeof(M), skey, param, SHA256);
	PCIS_ECDSA_Verify(sig, M, sizeof(M), pkey, param, SHA256);

	PCIS_ECDSA_Sig_Del(sig);
	PCIS_ECDSA_PriKey_Del(skey);
	PCIS_ECDSA_PubKey_Del(pkey);
	PCIS_ECC_Param_Del(param);

	PCIS_CC_Finalize(); // It is recommended to call this when you are done with CIS.
 * @endcode
 *
 * You can access some of the operations via algorithm descriptor. So, the
 * above code snippet can be re-written as follows:
 * @code
	AlgDesc sigAlg;

	// You can use PCIS_ECDSA and ECDSA interchangeably. But, in the future
	// release ECDSA symbol may disappear. So, it is recommended to use
	// PCIS_ECDSA instead of ECDSA.
	//sigAlg = ECDSA;
	sigAlg = PCIS_ECDSA;
	sigAlg->genParam(param, PCIS_EC_CURVE_P256);
	sigAlg->genKey(skey, pkey, param);
	sigAlg->signFunc(sig, M, sizeof(M), skey, param, SHA256);
	sigAlg->verifyFunc(sig, M, sizeof(M), pkey, param, SHA256);
 * @endcode
 *
 * You can use pre-generated keys via manipulating underlying EC structures.
 * @code
	PCIS_ECDSA_PubKey *pkey = PCIS_ECDSA_PubKey_New();

	// for uncompressed pub key
	MINT_SetByHexString(pkey->P->x,
			"e424dc61d4bb3cb7ef4344a7f8957a0c5134e16f7a67c074f82e6e12f49abf3c");
	MINT_SetByHexString(pkey->P->y,
			"970eed7aa2bc48651545949de1dddaf0127e5965ac85d1243d6f60e7dfaee927");
	MINT_SetByInteger(pkey->P->z, 1); // This is required.
 * @endcode
 *
 * But, it may be rather common to use octet strings.
 * @code
	// Assume that buf already holds pubkey encoded in octet string.
	BYTE buf[] = {0x04, 0x12, 0x34, 0x56, ... }; // 0x04 for uncompressed
	PCIS_ECDSA_PubKey *pkey = PCIS_ECDSA_PubKey_New();
	PCIS_ECC_Param *param = PCIS_ECC_Param_New();

	// Note that for some serious EC or ECDSA operation, you need
	// PCIS_ECC_Param almost always.
	PCIS_ECC_SetParam(param, PCIS_EC_CURVE_P256);
	// This function can handle uncompressed, compressed (aka LSB compressed),
	// and hybrid format.
	PCIS_EC_Point_ConvertFromOctetString(pkey->P, buf, sizeof(buf), param->E);
 * @endcode
 */

/** @file
 * @ingroup ECDSA
 * ECDSA Signature algorithm interface
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ECDSA
 * @{ */

/** @brief ECDSA Private Key */
typedef PCIS_ECC_PriKey PCIS_ECDSA_PriKey;

/** @brief ECDSA Public Key */
typedef PCIS_ECC_PubKey PCIS_ECDSA_PubKey;

/** ECDSA signature structure
 * ECDSA의 서명값은 두 가지값(r, s)이다.
 */
typedef struct {
	MINT *r;
	MINT *s;
} PCIS_ECDSA_Sig;

LIBSPEC
extern PKCryptAlgorithm pcis_ecdsa;
#ifdef _HPUX // for unknown export error on HP-UX
LIBSPEC
extern PKCryptAlgorithm pcis_ecdsa;
#endif

/** @brief ECDSA Algorithm descriptor alias */
#define ECDSA (&pcis_ecdsa)
/** @brief ECDSA Algorithm descriptor alias */
#define PCIS_ECDSA (&pcis_ecdsa)

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_ECDSA_H_ */
