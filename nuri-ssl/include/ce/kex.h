/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_KEX_H_
#define _PCIS_KEX_H_

#include "sp_define.h"
#include "mint_common.h"
#include "ec_common.h"
#include "asn1.h"

/** @defgroup KEX Key Exchange Algorithms
 * @ingroup SP
 * @brief KEX(Key Exchange Algorithm) 모듈
 *
 * DH와 ECDH를 포함한다. Legacy 방식으로 KEDH와 KEHMAC 방식(@ref KEA)이 있으나
 * KEX interface와는 별도로 사용해야 한다.
 *
 * OpenSSL의 경우(1.0.2g 기준) PKCS#3 형식의 protocol과 X9.64 방식(RFC2631)의
 * protocol을 구분해서 지원하고 있다. parameter의 형태가 다르다. CIS에서도
 * 구분해서 지원하게 될 것이다. (아직 아님)
 *
 * key agreement를 위해 전달되는 pub key는 SubjectPublicKeyInfo를 따른다.
 * SubjectPublicKey.AlgorithmIdentifier.parameters를 위한 Domain Parameters와
 * SubjectPublicKeyInfo.subjectPublicKey를 위한 DHPublicKey의 format은 RFC3279
 * 2.3.3을 따른다.
 *
 * @code{.unparsed}
	DomainParameters ::= SEQUENCE {
		p	INTEGER, -- odd prime, p=jq +1
		g	INTEGER, -- generator, g
		q	INTEGER, -- factor of p-1
		j	INTEGER OPTIONAL, -- subgroup factor
		validationParms ValidationParms OPTIONAL }

	ValidationParms ::= SEQUENCE {
		seed		BIT STRING,
		pgenCounter	INTEGER }

	DHPublicKey ::= INTEGER -- public key, y = g^x mod p
 * @endcode
 *
 * ECDH를 위한 format은 RFC 5480을 따른다.
 * @todo add ASN.1 format to the doc
 *
 * KEX interface를 사용하기 위해서는 다음과 같이 한다:
 * @code
	PCIS_KEX_ctx *ctx = NULL;
	ASNBuf *info_from_me = NULL;
	BYTE shared_key[100];
	BWT shared_key_len;

	ctx = PCIS_KEX_New(PCIS_KEX_ECDH);
	PCIS_KEX_SetParam_ECDH(ctx, PCIS_EC_CURVE_P256);
	PCIS_KEX_SetKDF(ctx, 32, SHA256);
	info_from_me = PCIS_KEX_GenShareInfo(ctx);
	// send info_from_me to the peer

	// upon receiving info from the peer
	PCIS_KEX_GetKey(ctx, shared_key, &shared_key_len, info_from_peer));

	// collect resource
	PCIS_KEX_Del(ctx);
 * @endcode
 * For collecting resources related to ASN, see @ref ASN.
 */

/** @file
 * @ingroup KEX
 * @brief KEX interface abstraction
 */

/**
 *
	*/

/** @ingroup KEX */
typedef enum {
	PCIS_KEX_DH, /**< defined in PKCS#3 */
	PCIS_KEX_DH_X9_42, /**< defined in X9.42 */
	PCIS_KEX_ECDH,
	PCIS_KEX_ECCDH,
} PCIS_KEX_type;

#define PCIS_KEX_DEFAULT PCIS_KEX_DH_X9_42
#define PCIS_KEX_ECDHE PCIS_KEX_ECDH

typedef struct {
	PCIS_KEX_type type;
	void *param;
	void *key;
	void *kdf;
	size_t keyLen;
	const void * hashAlg;
} PCIS_KEX_ctx;

typedef struct {
	ASNSeqClass klass;
	BitString *y;
	OctetString *keyInfo;
} PCIS_KEX_ShareInfo;

LIBSPEC_SP 
extern ASNDescriptor AD_PCIS_KEX_ShareInfo;

/** @ingroup KEX */
LIBSPEC_SP
PCIS_KEX_ctx* PCIS_KEX_New(PCIS_KEX_type type);

/** @ingroup KEX */
LIBSPEC_SP
void PCIS_KEX_Del(PCIS_KEX_ctx *ctx);

/** @ingroup KEX */
LIBSPEC_SP
ERT PCIS_KEX_Initialize_DH(
		PCIS_KEX_ctx *ctx,
		const MINT *p,
		const MINT *q,
		const MINT *g,
		const MINT *x,
		const MINT *yR,
		BWT keyLen,
		const void *hashAlg
		);

/** @ingroup KEX */
LIBSPEC_SP
ERT PCIS_KEX_SetParam_DH(
		PCIS_KEX_ctx *ctx,
		const MINT *p,
		const MINT *q,
		const MINT *g
		);

/** @ingroup KEX */
LIBSPEC_SP
ERT PCIS_KEX_SetParam_ECDH(
		PCIS_KEX_ctx *ctx,
		unsigned int curve_id
		);

/** @ingroup KEX */
LIBSPEC_SP
ERT PCIS_KEX_GenParam(PCIS_KEX_ctx *ctx);

/** @ingroup KEX */
LIBSPEC_SP
ERT PCIS_KEX_GetParam(
		PCIS_KEX_ctx *ctx,
		MINT *p,
		MINT *q,
		MINT *g
		);

/** @ingroup KEX */
LIBSPEC_SP
ERT PCIS_KEX_SetKDF(
		PCIS_KEX_ctx *ctx,
		BWT keyLen,
		const void *hashAlg
		);

/** @ingroup KEX */
LIBSPEC_SP
ASNBuf* PCIS_KEX_GenShareInfo(PCIS_KEX_ctx *ctx);

/** @ingroup KEX */
LIBSPEC_SP
ERT PCIS_KEX_GetKey(
		PCIS_KEX_ctx *ctx,
		BYTE* keyBuf,
		BWT *keyLen,
		ASNBuf *shareInfo
		);

#endif /* _PCIS_KEX_H_ */
