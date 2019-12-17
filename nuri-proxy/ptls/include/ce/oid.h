
/***************************************************************************
  DO NOT touch this file.  It is automatically generated.
 ***************************************************************************/
#ifndef _oid_h_
#define _oid_h_

#include "me_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup OID Object Identifier
    @ingroup ME
    @brief Object Identifier 를 처리하는 모듈

    알려진 OID(Object Identifier)들을 인식하고 다룰 수 있도록 해주는
    모듈이다.  구조체 형태인 Oid type과 이를 정수 형식의 일련 번호로 표시한
    Nid type 및 이미 일려진 OID들의 정의를 제공한다.  이 모듈을 통해
    임의의 OID의 내용을 파악하거나 특정 OID를 모듈간에 전달할 수 있다.
*/

/** @ingroup OID
    @brief 이 모듈에서 처리할 수 있는 OID의 최대 길이

    이 모듈에서 처리할 수 있는 OID의 최대 길이이다.
*/
#define MAX_DEPTH_OF_OID    16

/** @ingroup OID
    @brief OID를 표현한 C 구조체
*/
typedef struct _Oid {
  int len;
  int id[MAX_DEPTH_OF_OID];
} Oid;

/** @ingroup OID
    @brief 알려진 OID들에 일련 번호를 붙여 표현하는 타입

    알려진 OID들에 대해서 각각 일련번호를 붙여 표현하는 타입이다.
    OID들과 1대1 대응한다.  단순한 정수 타입이므로 다루기 쉬워
    알려진 OID들만을 다루는 일반적인 상황에서 Oid type 대신 많이 쓰인다.
*/
typedef unsigned int Nid;

/** @ingroup OID
    @brief Oid 구조체를 복사한다.
    @param src 복사될 원본 Oid 구조체
    @param dest 복사 대상인 Oid 구조체

    한 Oid 구조체의 내용을 다른 Oid 구조체로 복사한다.
*/
LIBSPEC_ME
extern int  Oid_Copy(Oid *dest, const Oid *src);

/** @ingroup OID
    @brief 두개의 Oid 구조체의 내용이 동일한지 비교한다.
*/
LIBSPEC_ME
extern int  Oid_Compare(const Oid *a, const Oid *b);
#define Oid_Cmp(a, b) Oid_Compare(a, b) /* for backward compablity */

/** @ingroup OID
    @brief Oid 구조체에서 이에 대응하는 Nid를 얻는다.
    @param in 대응하는 Nid를 얻고자하는 Oid 구조체.

    특정 Oid 구조체에서 이에 대응하는 Nid를 구한다.
    만일 Oid가 '알려진' OID가 아니어서 대응하는 Nid가
    존재하지 않는다면 0을 리턴한다.
*/
LIBSPEC_ME
extern Nid Oid_GetNid(const Oid *in);

/** @ingroup OID
    @brief 주어진 문자열로부터 Oid 구조체를 얻는다.
    @param oid 얻어온 내용이 들어갈 Oid 구조체의 포인터.
    @param str OID를 표현하는 문자열. "1.2.3.4"와 같은 내용이 들어간다.

    OID를 표현하는 특정한 문자열(예:"1.2.3.4")에서 내용을 읽어와
    주어진 Oid 구조체에 입력한다.
*/
LIBSPEC_ME
extern int  Oid_Sread(Oid *oid, const char *str);

/** @ingroup OID
    @brief 주어진 Oid type의 내용을 문자열로 출력한다.
    @param buffer Oid type의 내용이 적힐 문자열 버퍼
    @param oid 내용 출력을 원하는 Oid type
    @sa Nid_Sprint Oid_SprintEx

    주어진 Oid 구조체의 내용을 문자열로 출력한다.
    OID가 알려진 내용일 경우 이에 대응하는 설명 문자열(예:id_SHA1)로
    그렇지 않을 경우에는 일반적인 방식(예:"1.2.3.4")으로 출력한다.
*/
LIBSPEC_ME
extern void Oid_Sprint(char *buffer, const Oid *oid);

/** @ingroup OID
    @brief 주어진 Oid type의 내용을 문자열로 출력한다.
    @param buffer Oid type의 내용이 적힐 문자열 버퍼
    @param oid 내용 출력을 원하는 Oid type
    @sa Nid_Sprint Oid_Sprint

    주어진 Oid 구조체의 내용을 번호만으로 된 문자열로 출력한다.
    (예:"1.2.3.4")
*/
LIBSPEC_ME
extern void Oid_SprintEx(char *buffer, const Oid *oid);

/** @ingroup OID
    @brief Nid에서 이에 대응하는 Oid 구조체의 내용을 얻는다.
    @param out Nid에 대응하는 Oid 내용이 들어갈 Oid 구조체의 포인터
    @param in  대응하는 Oid를 구하고자하는 Nid 값

    주어진 Nid에서 이에 대응하는 특정 Oid 구조체의 내용을 구한다.
*/
LIBSPEC_ME
extern void Nid_GetOid(Oid *out, Nid in);

/** @ingroup OID
    @brief 주어진 Nid의 내용을 문자열로 출력한다.
    @param buffer Nid의 내용이 적힐 문자열 버퍼
    @param oid 내용 출력을 원하는 Nid
    @sa Oid_Sprint

    주어진 Nid의 내용을 문자열로 출력한다.
    Nid가 가리키는 OID가 알려진 내용일 경우 이에 대응하는 설명 
    문자열(예:id_SHA1)로 그렇지 않을 경우에는 일반적인
    방식(예:"1.2.3.4")으로 출력한다.
*/
LIBSPEC_ME
extern void Nid_Sprint(char *buffer, Nid nid);

/** @ingroup OID
    @brief 주어진 문자열로부터 Nid 값을 얻는다.
    @param str OID를 표현하는 문자열. "1.2.3.4"와 같은 내용이 들어간다.
    @return Nid

    OID를 표현하는 특정한 문자열(예:"1.2.3.4")에서 내용을 읽어와
    맞는 Nid값을 리턴한다.
*/
LIBSPEC_ME
extern Nid Nid_Sread(const char *str);



/***************************************************************************
 * Numeric Idenditifer(NID)
 */

typedef enum {

  NID_UNDEF,
  NID_kisa,
  NID_kisa_algorithm,
  NID_kCDSA0,
  NID_has160,
  NID_seedECB,
  NID_seedCBC,
  NID_pbeWithSHA1AndSEED_CBC_old,
  NID_seedOFB,
  NID_seedCFB,
  NID_seedMAC,
  NID_kcdsa0WithHAS160,
  NID_kcdsa0WithSHA1,
  NID_kCDSA1,
  NID_kcdsa1WithHAS160,
  NID_kcdsa1WithSHA1,
  NID_kisa_npki_cp,
  NID_npki_cp_sign,
  NID_kisa_npki_kp,
  NID_kisa_npki_at,
  NID_kisa_npki_lca,
  NID_signKOREA,
  NID_signKOREA_cp,
  NID_signKOREA_cp_signPlatinum_Pe,
  NID_signKOREA_cp_signPlatinum_PeSvr,
  NID_signKOREA_cp_signPlatinum_Co,
  NID_signKOREA_cp_signPlatinum_CoSvr,
  NID_signKOREA_cp_sign_Gold_Pe,
  NID_signKOREA_cp_sign_Gold_PeSvr,
  NID_signKOREA_cp_sign_Silver_Pe,
  NID_signKOREA_cp_sign_Silver_Co,
  NID_signGATE,
  NID_signGATE_cp,
  NID_signGATE_cp_sign_Class1,
  NID_signGATE_cp_sign_Class2,
  NID_signGATE_cp_sign_Class3,
  NID_signGATE_cp_sign_Class4,
  NID_penta_security,
  NID_penta_algorithm,
  NID_pACA,
  NID_pACA_CBC,
  NID_pbeWithSHA1AndPACA_CBC,
  NID_nEAT_p,
  NID_nEAT_CBC_p,
  NID_pbeWithSHA1AndNEAT_CBC_p,
  NID_id_holdInstruction,
  NID_id_holdInstruction_none,
  NID_id_holdInstruction_callissuer,
  NID_id_holdInstruction_reject,
  NID_dsa,   /* id-dsa */
  NID_dsa_with_sha1,   /* id-dsa-with-sha1 */
  NID_dhpublicnumber,   /* Diffie-Hellman */
  NID_rsaEncryption,
  NID_md2WithRSAEncryption,
  NID_md5WithRSAEncryption,
  NID_sha1WithRSAEncryption,
  NID_id_RSAES_OAEP,   /* id-RSAES-OAEP */
  NID_id_mgf1,   /* id-mgf1 */
  NID_id_pSpecified,   /* id-pSpecified */
  NID_pbeWithMD2AndDES_CBC,
  NID_pbeWithMD5AndDES_CBC,
  NID_pbeWithMD2AndRC2_CBC,
  NID_pbeWithMD5AndRC2_CBC,
  NID_pbeWithSHA1AndDES_CBC,
  NID_pbeWithSHA1AndRC2_CBC,
  NID_id_PBKDF2,
  NID_id_PBES2,
  NID_pkcs_7,
  NID_data,
  NID_signedData,
  NID_envelopedData,
  NID_signedAndEnvelopedData,
  NID_digestedData,
  NID_encryptedData,
  NID_emailAddress,
  NID_contentType,
  NID_messageDigest,
  NID_signingTime,
  NID_countersignature,
  NID_friendlyName,
  NID_localKeyID,
  NID_x509Certificate,
  NID_sdsiCertificate,
  NID_pkcs_12PbeIds,
  NID_pbeWithSHAAnd128BitRC4,
  NID_pbeWithSHAAnd40BitRC4,
  NID_pbeWithSHAAnd3_KeyTripleDES_CBC,
  NID_pbeWithSHAAnd2_KeyTripleDES_CBC,
  NID_pbeWithSHAAnd128BitRC2_CBC,
  NID_pbewithSHAAnd40BitRC2_CBC,
  NID_bagtypes,
  NID_keyBag,
  NID_pkcs8ShroudedKeyBag,
  NID_certBag,
  NID_crlBag,
  NID_secretBag,
  NID_safeContentsBag,
  NID_md2,
  NID_md5,
  NID_hmacWithSHA1,   /* id_hmacWithSHA1 */
  NID_rc2CBC,
  NID_des_EDE3_CBC,   /* des_EDE3_CBC */
  NID_rc5_CBC_PAD,
  NID_pkix,
  NID_mod,   /* id-mod */
  NID_attribute_cert,   /* id-mod-attribute_cert */
  NID_pe,   /* id-pe */
  NID_authorityInfoAccess,   /* id-pe-authorityInfoAccess */
  NID_ac_auditIdentity,   /* id-pe-ac-auditIdentity */
  NID_aaControls,   /* id-pe-aaControls */
  NID_ac_proxying,   /* id-pe-ac-proxying */
  NID_kp,   /* id-kp */
  NID_serverAuth,   /* id-kp-serverAuth */
  NID_clientAuth,   /* id-kp-clientAuth */
  NID_codeSigning,   /* id-kp-codeSigning */
  NID_emailProtection,   /* id-kp-emailProtection */
  NID_timeStamping,   /* id-kp-timeStamping */
  NID_OCSPSigning,   /* id-kp-OCSPSigning */
  NID_aca,   /* id-aca */
  NID_authenticationInfo,   /* id-aca-authenticationInfo */
  NID_accessIdentity,   /* id-aca-accessIdentity */
  NID_chargingIdentity,   /* id-aca-chargingIdentity */
  NID_group,   /* id-aca-group */
  NID_encAttrs,   /* id-aca-encAttrs */
  NID_ad,   /* id-ad */
  NID_ocsp,   /* id-pkix-ocsp */
  NID_ocsp_basic,   /* id-pkix-ocsp-basic */
  NID_ocsp_nonce,   /* id-pkix-ocsp-nonce */
  NID_ocsp_crl,   /* id-pkix-ocsp-crl */
  NID_ocsp_response,   /* id-pkix-ocsp-response */
  NID_ocsp_nocheck,   /* id-pkix-ocsp-nocheck */
  NID_ocsp_archive_cutoff,   /* id-pkix-ocsp-archive-cutoff */
  NID_ocsp_service_locator,   /* id-pkix-ocsp-service-locator */
  NID_desCBC,
  NID_SHA1,   /* id-SHA1 */
  NID_sha1withRSASignature,
  NID_id_at_clearance,
  NID_at,   /* id-at */
  NID_commonName,   /* id-at-commonName */
  NID_serialNumber,   /* id-at-serialNumber */
  NID_countryName,   /* id-at-countryName */
  NID_localityName,   /* id-at-localityName */
  NID_stateOrProvinceName,   /* id-at-stateOrProvinceName */
  NID_organizationName,   /* id-at-organizationName */
  NID_organizationUnitName,   /* id-at-organizationUnitName */
  NID_businessCategory,   /* id-at-businessCategory */
  NID_userPassword,   /* id-at-userPassword */
  NID_userCertificate,   /* id-at-userCertificate */
  NID_cAcertificate,   /* id-at-cAcertificate */
  NID_authorityRevocationList,   /* id-at-authorityRevocationList */
  NID_certificateRevocationList,   /* id-at-certificateRevocationList */
  NID_crossCertificatePair,   /* id-at-crossCertificatePair */
  NID_uniqeIdentifier,   /* id-at-uniqueIdentifier */
  NID_supportedAlgorithms,   /* id-at-attributeCertificate */
  NID_deltaRevocationList,   /* id-at-supportedAlgorithms */
  NID_attributeCertificate,   /* id-at-deltaRevocationList */
  NID_role,   /* id-at-role */
  NID_algorithm,
  NID_encryptionAlgorithm,
  NID_hashAlgorithm,
  NID_signatureAlgorithm,
  NID_matchingRule,   /* id-mr */
  NID_ce,   /* id-ce */
  NID_subjectDirectoryAttributes,   /* id-ce-subjectDirectoryAttributes */
  NID_subjectKeyIdentifier,   /* id-ce-subjectKeyIdentifier */
  NID_keyUsage,   /* id-ce-keyUsage */
  NID_privateKeyUsagePeriod,   /* id-ce-privateKeyUsagePeriod */
  NID_subjectAltName,   /* id-ce-subjectAltName */
  NID_issuerAltName,   /* id-ce-issuerAltName */
  NID_basicConstraints,   /* id-ce-basicConstraints */
  NID_cRLNumber,   /* id-ce-cRLNumber */
  NID_reasonCode,   /* id-ce-reasonCode */
  NID_holdInstructionCode,   /* id-ce-holdInstructionCode */
  NID_invalidityDate,   /* id-ce-invalidityDate */
  NID_deltaCRLIndicator,   /* id-ce-deltaCRLIndicator */
  NID_issuingDistributionPoint,   /* id-ce-issuingDistributionPoint */
  NID_certificateIssuer,   /* id-ce-certificateIssuer */
  NID_nameConstraints,   /* id-ce-nameConstraints */
  NID_cRLDistributionPoints,   /* id-ce-cRLDistributionPoints */
  NID_certificatePolicies,   /* id-ce-certificatePolicies */
  NID_policyMappings,   /* id-ce-policyMappings */
  NID_authorityKeyIdentifier,   /* id-ce-authorityKeyIdentifier */
  NID_policyConstraints,   /* id-ce-policyConstraints */
  NID_extKeyUsage,   /* id-ce-extKeyUsage */
  NID_targetInformation,   /* id-ce-targetInformation */
  NID_has160_old,
  NID_kCDSA_old,
  NID_has160withKCDSA_old,
  NID_sha1withKCDSA_old,
  NID_pACA_old,
  NID_pbeWithSHA1AndPACA_CBC_old,
  NID_pACA_CBC_old,
  NID_nEAT_old,
  NID_pbeWithSHA1AndNEAT_CBC_old,
  NID_nEAT_CBC_old,
  NID_netscape,
  NID_netscape_cert_extension,
  NID_netscape_cert_type,
  NID_netscape_base_url,
  NID_netscape_revocation_url,
  NID_netscape_renewal_url,
  NID_qt,   /* id-qt */
  NID_cps,   /* id-qt-cps */
  NID_unotice,   /* id-qt-unotice */
  NID_caIssuers,   /* id-ad-caIssuers */
  NID_passwordBasedMac,   /* PasswordBasedMac */
  NID_dHBasedMac,   /* DHBasedMac */
  NID_kisa_identifyData,   /* id-kisa-identifyData */
  NID_seedCBCwithSHA1,   /* seedCBCwithSHA1 or pbeWithSHA1AndSEED-CBC */
  NID_desMAC,   /* id-des-MAC */
  NID_it,   /* id-it */
  NID_caProtEncCert,   /* id-it-caProtEncCert */
  NID_signKeyPairTypes,   /* id-it-signKeyPairTypes */
  NID_encKeyPairTypes,   /* id-it-encKeyPairTypes */
  NID_preferredSymmAlg,   /* id-it-preferredSymmAlg */
  NID_caKeyUpdateInfo,   /* id-it-caKeyUpdateInfo */
  NID_currentCRL,   /* id-it-currentCRL */
  NID_unsupportedOIDs,   /* id-it-unsupportedOIDs */
  NID_keyPairParamReq,   /* id-it-keyPairParamReq */
  NID_keyPairParamRep,   /* id-it-keyPairParamRep */
  NID_revPassphrase,   /* id-it-revPassphrase */
  NID_implicitConfirm,   /* id-it-implicitConfirm */
  NID_confirmWaitTime,   /* id-it-confirmWaitTime */
  NID_origPKIMessage,   /* id-it-origPKIMessage */
  NID_suppLangTags,   /* id-it-suppLangTags */
  NID_pkip,   /* id-pkip */
  NID_regCtrl,   /* id-regCtrl */
  NID_regToken,   /* id-regCtrl-regToken */
  NID_authenticator,   /* id-regCtrl-authenticator */
  NID_pkiPublicationInfo,   /* id-regCtrl-pkiPublicationInfo */
  NID_pkiArchiveOptions,   /* id-regCtrl-pkiArchiveOptions */
  NID_oldCertID,   /* id-regCtrl-oldCertID */
  NID_protocolEncrKey,   /* id-regCtrl-protocolEncrKey */
  NID_regInfo,   /* id-regInfo */
  NID_utf8Pairs,   /* id-regInfo-utf8Pairs */
  NID_certReq,   /* id-regInfo-certReq */
  NID_penta_at,   /* penta-at */
  NID_penta_at_cmp,   /* penta-at-cmp */
  NID_penta_at_dir,   /* penta-at-dir */
  NID_penta_at_ac,   /* penta-at-ac */
  NID_penta_acElement,   /* penta-at-ac-acElement */
  NID_penta_userIdentifierList,   /* penta-at-ac-userIdentifierList */
  NID_penta_acElements,   /* penta-at-ac-acElements */
  NID_penta_roleCapabilityList,   /* penta-at-ac-roleCapabilityList */
  NID_penta_role,   /* penta-at-ac-role */
  NID_penta_userTicket,   /* penta-at-ac-userTicket */
  NID_penta_at_oc,   /* penta-at-oc */
  NID_aes,
  NID_aes128ECB,   /* id-aes128-ECB */
  NID_aes128CBC,   /* id-aes128-CBC */
  NID_aes128OFB,   /* id-aes128-OFB */
  NID_aes128CFB,   /* id-aes128-CFB */
  NID_aes192ECB,   /* id-aes192-ECB */
  NID_aes192CBC,   /* id-aes192-CBC */
  NID_aes192OFB,   /* id-aes192-OFB */
  NID_aes192CFB,   /* id-aes192-CFB */
  NID_aes256ECB,   /* id-aes256-ECB */
  NID_aes256CBC,   /* id-aes256-CBC */
  NID_aes256OFB,   /* id-aes256-OFB */
  NID_aes256CFB,   /* id-aes256-CFB */
  NID_blowfishECB,
  NID_blowfishCBC,
  NID_blowfishCFB,
  NID_blowfishOFB,
  NID_cast5CBC,
  NID_ideaECB,   /* IDEA-ECB */
  NID_ideaCBC,   /* IDEA-CBC */
  NID_ideaCFB,   /* IDEA-CFB */
  NID_ideaOFB,   /* IDEA-OFB */
  NID_penta_at_pkc,   /* penta-at-pkc */
  NID_penta_at_pkc_exts,   /* penta-at-pkc-exts */
  NID_pentaAdministrator,   /* penta-at-pkc-exts-pentaAdministrator */
  NID_pentaRevDescription,   /* penta-at-pkc-exts-pentaRevDescription */
  NID_penta_at_pkc_exts_reserved2,   /* penta-at-pkc-exts-reserved2 */
  NID_penta_at_pkc_exts_reserved3,   /* penta-at-pkc-exts-reserved3 */
  NID_penta_at_pkc_exts_reserved4,   /* penta-at-pkc-exts-reserved4 */
  NID_penta_at_pkc_exts_reserved5,   /* penta-at-pkc-exts-reserved5 */
  NID_HMAC_SHA1,
  NID_microsoft,
  NID_msCTL,
  NID_ipsecEndSystem,
  NID_ipsecTunnel,
  NID_ipsecUser,
  NID_penta_at_cmp_keyPolicyId,   /* penta-at-cmp-keyPolicyId */
  NID_penta_at_cmp_keyPolicyReq,   /* penta-at-cmp-keyPolicyReq */
  NID_penta_at_cmp_keyPolicyRes,   /* penta-at-cmp-keyPolicyRes */
  NID_pbeWithSHA1AndSEED_CBC_old2,
  NID_penta_alg_pbeWithSHA1AndSEED_CBC,   /* penta-alg-pbeWithSHA1AndSEED_CBC */
  NID_certificatePolicies_anyPolicy,   /* anyPolicy */
  NID_gpki_alg,   /* gpki-alg */
  NID_nEAT,
  NID_nEAT_ECB,
  NID_nEAT_CBC,
  NID_nEAT_OFB,
  NID_nEAT_CFB,
  NID_nEAT_MAC,
  NID_pbeWithSHA1AndNEAT_CBC,
  NID_pbeWithHAS160AndNEAT_CBC,
  NID_gov,   /* Government */
  NID_gpki_cp,   /* GPKI-CP */
  NID_gpki_class1,   /* GPKI-Class1 */
  NID_gpki_class1_department,   /* GPKI-Class1-Department */
  NID_gpki_class1_computer,   /* GPKI-Class1-Computer */
  NID_gpki_class2,   /* GPKI-Class2 */
  NID_gpki_class2_personal,   /* GPKI-Class2-Personal */
  NID_gpki_kp,   /* GPKI-KP */
  NID_gpki_at,   /* GPKI-Attribute */
  NID_gpki_lca,   /* GPKI-LCA */
  NID_pca_mogaha,   /* PCA-MOGAHA */
  NID_pca_mogaha_cp,   /* PCA-MOGAHA-CP */
  NID_pca_assembly,   /* PCA-Assembly */
  NID_pca_court,   /* PCA-Court */
  NID_pca_electionAdmin,   /* PCA-ElectionAdmin */
  NID_pca_constitutionalCourt,   /* PCA-ConstitutionalCourt */
  NID_seedECBWithHAS160,
  NID_seedCBCWithHAS160,
  NID_seedOFBWithHAS160,
  NID_seedCFBWithHAS160,
  NID_seedECBWithSHA1,
  NID_seedOFBWithSHA1,
  NID_seedCFBWithSHA1,
  NID_rsaWithHAS160,
  NID_ecdsaWithHAS160,
  NID_ecc,
  NID_ncaSign,   /* 한국전산원 */
  NID_crossCert,   /* 한국전자인증 */
  NID_crossCert_cp,   /* 한국전자인증-인증서정책 */
  NID_npki_othername,   /* 확장명칭형식 */
  NID_npki_othername_vid,   /* virtual ID */
  NID_npki_othername_encryptedVID,   /* encrypted virtual ID */
  NID_npki_app,   /* NPKI-application */
  NID_npki_smime,   /* NPKI-SMIME */
  NID_npki_smime_alg,   /* NPKI-smime-알고리즘 */
  NID_npki_smime_cMSSEEDwrap,   /* CMS-Seed-Key-wrapping */
  NID_npki_kbims,   /* NPKI-Biometrics */
  NID_npki_interoperability,   /* NPKI-상호연동 */
  NID_ctl,
  NID_ctl_subjectUsage,   /* subject Usage */
  NID_ctl_electronic_civil_app,   /* CTL-민원서비스 */
  NID_ctl_oc,   /* CTL-ob */
  NID_ctl_oc_pkiCTL,
  NID_ctl_at,   /* CTL-at */
  NID_ctl_at_certificateTrustList,
  NID_penta_customer,   /* 펜타시큐리티 고객 */
  NID_lgcaltex,   /* LG-Caltex */
  NID_lgcaltex_cp,   /* LG-Caltex 인증서정책 */
  NID_hncb,   /* 주택은행 */
  NID_hncb_cp,   /* 주택은행 인증서정책 */
  NID_hncb_ca,   /* 주택은행 인증기관 */
  NID_hncb_alg,   /* 주택은행 알고리즘 */
  NID_hncb_kp,   /* 주택은행 키용도 */
  NID_hncb_at,   /* 주택은행 인증서속성 */
  NID_penta_permissions,   /* penta-at-ac-permissions */
  NID_penta_product,   /* penta-product */
  NID_penta_product_issac,   /* ISSAC */
  NID_penta_product_isign,   /* ISign */
  NID_isign_mechanism,   /* ISign-Mechanisms */
  NID_isign_gssapi_v2,   /* ISign-GSSAPI-v2 */
  NID_isign_x500_dn,   /* ISign-X.500-DN */
  NID_gssapi,   /* GSSAPI */
  NID_gssapi_user_name,   /* GSSAPI_UserName */
  NID_gssapi_machine_uid_name,   /* GSSAPI_MachineUidName */
  NID_gssapi_string_uid_name,   /* GSSAPI_StringUidName */
  NID_gssapi_service_name,   /* GSSAPI_ServiceName */
  NID_internet_security_nametypes,   /* Internet-Security-NameTypes */
  NID_gss_host_based_services,   /* GSS-HostBasedServices */
  NID_gss_anonymous_name,   /* GSS-AnonymousName */
  NID_gss_api_exported_name,   /* GSS-API-ExportedName */
  NID_spkm1,   /* SPKM-1 (rfc2025) */
  NID_spkm2,   /* SPKM-2 (rfc2025) */
  NID_npki,   /* NPKI */
  NID_npki_at,   /* NPKI-Attribute */
  NID_kisa_identifyData200209,   /* KISA-IdentifyData */
  NID_VID,   /* Virtual-ID */
  NID_EncryptedVID,   /* EncryptedVID */
  NID_randomNum,   /* VID-RandomNumber */
  NID_domainComponent,   /* Domain-Component */
  NID_penta_kp,   /* penta-kp */
  NID_penta_kp_auth_only,   /* penta-kp-authOnly */
  NID_inhibitAnyPolicy,   /* id-ce-inhibitAnyPolicy */
  NID_freshestCRL,   /* id-ce-freshestCRL */
  NID_subjectInfoAccess,   /* id-pe-subjectInfoAccess */
  NID_penta_alg_aRIA,   /* ARIA */
  NID_aRIA_CBC,   /* ARIA_CBC */
  NID_pbeWithSHA1AndARIA,   /* PBE_With_SHA1_ARIA */
  NID_SHA256,   /* id-sha256 */
  NID_SHA384,   /* id-sha384 */
  NID_SHA512,   /* id-sha512 */
  NID_sha256WithRSAEncription,
  NID_sha384WithRSAEncription,
  NID_sha512WithRSAEncription,
  NID_fork256,   /* FORK256 */
  NID_kcdsa0WithFORK256,   /* FORK256 해쉬 후 KCDSA 전자서명 */
  NID_kcdsa0WithSHA256,   /* SHA-256 해쉬 후 KCDSA 전자서명 */
  NID_seedECBWithFORK256,   /* FORK256 해쉬로 키 추출 후 SEED ECB로 암호화 */
  NID_seedCBCWithFORK256,   /* FORK256 해쉬로 키 추출 후 SEED CBC로 암호화 */
  NID_seedOFBWithFORK256,   /* FORK256 해쉬로 키 추출 후 SEED OFB로 암호화 */
  NID_seedCFBWithFORK256,   /* FORK256 해쉬로 키 추출 후 SEED CFB로 암호화 */
  NID_seedECBWithSHA256,   /* SHA-265 해쉬로 키 추출 후 SEED ECB 로 암호화 */
  NID_seedCBCWithSHA256,   /* SHA-256 해쉬로 키 추출 후 SEED CBC로 암호화 */
  NID_seedOFBWithSHA256,   /* SHA-256 해쉬로 키 추출 후 SEED OFB 로 암호화 */
  NID_seedCFBWithSHA256,   /* SHA-256 해쉬로 키 추출 후 SEED CFB로 암호화 */
  NID_rsaWithFORK256,   /* FORK256 해쉬 후 RSA 전자서명 */
  NID_kcdsa1WithFORK256,   /* FORK256 해쉬 후 KCDSA1 전자서명 */
  NID_kcdsa1WithSHA256,   /* SHA-256 해쉬 후 KCDSA1 전자서명 */
  NID_ecdsaWithFORK256,   /* FORK256 해쉬 후 ECDSA 전자서명 */
  NID_surName,   /* id-at-surname */
  NID_streetAddress,   /* id-at-streetAddress */
  NID_title,   /* id-at-title */
  NID_givenName,   /* id-at-givenName */
  NID_initials,   /* id-at-initials */
  NID_uniqueIdentifie,   /* id-at-uniqueIdentifie */
  NID_generationQualifier,   /* id-at-generationQualifier */
  NID_dnQualifier,   /* id-at-dnQualifier */
  NID_pseudonym,   /* id-at-pseudonym */
  NID_rfc822MailBox,
  NID_ariaCBC,   /* ARIA128 - CBC모드 */
  NID_pbewithSHA1andARIA_CBC,   /* 패스워드기반 ARIA128 - CBC모드 */
  NID_id_RSASSA_PSS,   /* id-RSASSA-PSS */
  NID_ecdsa,   /* X9.62 ECDSA */
  NID_prime_field,   /* X9.62 prime field */
  NID_binary_field,   /* X9.62 binary field */
  NID_ecdsa_with_SHA1,   /* ECDSA signature with SHA1 */
  NID_ecdsa_with_SHA2,   /* ECDSA signature with SHA2 family */
  NID_ecdsa_with_SHA224,   /* ECDSA signature with SHA224 */
  NID_ecdsa_with_SHA256,   /* ECDSA signature with SHA256 */
  NID_ecdsa_with_SHA384,   /* ECDSA signature with SHA384 */
  NID_ecdsa_with_SHA512,   /* ECDSA signature with SHA512 */
  NID_id_ecPublicKey,   /* Elliptic curve public key */
  NID_secp192r1,   /* secp192r1 */
  NID_secp256r1,   /* secp256r1 */
  NID_sect163k1,   /* sect163k1 */
  NID_sect163r2,   /* sect163r2 */
  NID_sect283k1,   /* sect283k1 */
  NID_sect283r1,   /* sect283r1 */
  NID_sect233k1,   /* sect233k1 */
  NID_sect233r1,   /* sect233r1 */
  NID_secp224r1,   /* secp224r1 */
  NID_secp384r1,   /* secp384r1 */
  NID_secp521r1,   /* secp521r1 */
  NID_sect409k1,   /* sect409k1 */
  NID_sect409r1,   /* sect409r1 */
  NID_sect571k1,   /* sect571k1 */
  NID_sect571r1,   /* sect571r1 */
  NID_eckcdsa,   /* EC-KCDSA */
  NID_eckcdsa_with_HAS160,   /* EC-KCDSA with HAS160 */
  NID_eckcdsa_with_FORK256,   /* EC-KCDSA with FORK256 */
  NID_eckcdsa_with_SHA1,   /* EC-KCDSA with SHA1 */
  NID_eckcdsa_with_SHA224,   /* EC-KCDSA with SHA224 */
  NID_eckcdsa_with_SHA256,   /* EC-KCDSA with SHA256 */
  NID_kcdsa0WithSHA224,   /* SHA224 해쉬 후 KCDSA 전자서명 */
  NID_kcdsa1WithSHA224,   /* SHA224 해쉬 후 KCDSA1 전자서명 */
  NID_id_ecPublicKey_KISA,   /* EC-KCDSA Public Key */
  NID_secp256k1,   /* secp256k1 */
  NID_brainpoolP256r1,   /* Brainpool P256r1 domain parameter set */
  NID_brainpoolP384r1,   /* Brainpool P384r1 domain parameter set */
  NID_SIZE,
  NID_END = NID_SIZE  /* NID 들의 갯수를 표시 */
} NIDs;


/***************************************************************************
 * predefined Object Idenditifers
 */

LIBSPEC_ME
extern Oid Oid_kisa;
LIBSPEC_ME
extern Oid Oid_kisa_algorithm;
LIBSPEC_ME
extern Oid Oid_kCDSA;
LIBSPEC_ME
extern Oid Oid_has160;
LIBSPEC_ME
extern Oid Oid_seedECB;
LIBSPEC_ME
extern Oid Oid_seedCBC;
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndSEED_CBC_old;
LIBSPEC_ME
extern Oid Oid_seedOFB;
LIBSPEC_ME
extern Oid Oid_seedCFB;
LIBSPEC_ME
extern Oid Oid_seedMAC;
LIBSPEC_ME
extern Oid Oid_kcdsaWithHAS160;
LIBSPEC_ME
extern Oid Oid_kcdsaWithSHA1;
LIBSPEC_ME
extern Oid Oid_kCDSA1;
LIBSPEC_ME
extern Oid Oid_kcdsa1WithHAS160;
LIBSPEC_ME
extern Oid Oid_kcdsa1WithSHA1;
LIBSPEC_ME
extern Oid Oid_kisa_npki_cp;
LIBSPEC_ME
extern Oid Oid_npki_cp_sign;
LIBSPEC_ME
extern Oid Oid_kisa_npki_kp;
LIBSPEC_ME
extern Oid Oid_kisa_npki_at;
LIBSPEC_ME
extern Oid Oid_kisa_npki_lca;
LIBSPEC_ME
extern Oid Oid_signKOREA;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp_signPlatinum_Pe;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp_signPlatinum_PeSvr;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp_signPlatinum_Co;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp_signPlatinum_CoSvr;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp_sign_Gold_Pe;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp_sign_Gold_PeSvr;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp_sign_Silver_Pe;
LIBSPEC_ME
extern Oid Oid_signKOREA_cp_sign_Silver_Co;
LIBSPEC_ME
extern Oid Oid_signGATE;
LIBSPEC_ME
extern Oid Oid_signGATE_cp;
LIBSPEC_ME
extern Oid Oid_signGATE_cp_sign_Class1;
LIBSPEC_ME
extern Oid Oid_signGATE_cp_sign_Class2;
LIBSPEC_ME
extern Oid Oid_signGATE_cp_sign_Class3;
LIBSPEC_ME
extern Oid Oid_signGATE_cp_sign_Class4;
LIBSPEC_ME
extern Oid Oid_penta_security;
LIBSPEC_ME
extern Oid Oid_penta_algorithm;
LIBSPEC_ME
extern Oid Oid_pACA;
LIBSPEC_ME
extern Oid Oid_pACA_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndPACA_CBC;
LIBSPEC_ME
extern Oid Oid_nEAT_p;
LIBSPEC_ME
extern Oid Oid_nEAT_CBC_p;
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndNEAT_CBC_p;
LIBSPEC_ME
extern Oid Oid_id_holdInstruction;
LIBSPEC_ME
extern Oid Oid_id_holdInstruction_none;
LIBSPEC_ME
extern Oid Oid_id_holdInstruction_callissuer;
LIBSPEC_ME
extern Oid Oid_id_holdInstruction_reject;
LIBSPEC_ME
extern Oid Oid_dsa;   /* id-dsa */
LIBSPEC_ME
extern Oid Oid_dsa_with_sha1;   /* id-dsa-with-sha1 */
LIBSPEC_ME
extern Oid Oid_dhpublicnumber;   /* Diffie-Hellman */
LIBSPEC_ME
extern Oid Oid_rsaEncryption;
LIBSPEC_ME
extern Oid Oid_md2WithRSAEncryption;
LIBSPEC_ME
extern Oid Oid_md5WithRSAEncryption;
LIBSPEC_ME
extern Oid Oid_sha1WithRSAEncryption;
LIBSPEC_ME
extern Oid Oid_id_RSAES_OAEP;   /* id-RSAES-OAEP */
LIBSPEC_ME
extern Oid Oid_id_mgf1;   /* id-mgf1 */
LIBSPEC_ME
extern Oid Oid_id_pSpecified;   /* id-pSpecified */
LIBSPEC_ME
extern Oid Oid_pbeWithMD2AndDES_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithMD5AndDES_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithMD2AndRC2_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithMD5AndRC2_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndDES_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndRC2_CBC;
LIBSPEC_ME
extern Oid Oid_id_PBKDF2;
LIBSPEC_ME
extern Oid Oid_id_PBES2;
LIBSPEC_ME
extern Oid Oid_pkcs_7;
LIBSPEC_ME
extern Oid Oid_data;
LIBSPEC_ME
extern Oid Oid_signedData;
LIBSPEC_ME
extern Oid Oid_envelopedData;
LIBSPEC_ME
extern Oid Oid_signedAndEnvelopedData;
LIBSPEC_ME
extern Oid Oid_digestedData;
LIBSPEC_ME
extern Oid Oid_encryptedData;
LIBSPEC_ME
extern Oid Oid_emailAddress;
LIBSPEC_ME
extern Oid Oid_contentType;
LIBSPEC_ME
extern Oid Oid_messageDigest;
LIBSPEC_ME
extern Oid Oid_signingTime;
LIBSPEC_ME
extern Oid Oid_countersignature;
LIBSPEC_ME
extern Oid Oid_friendlyName;
LIBSPEC_ME
extern Oid Oid_localKeyID;
LIBSPEC_ME
extern Oid Oid_x509Certificate;
LIBSPEC_ME
extern Oid Oid_sdsiCertificate;
LIBSPEC_ME
extern Oid Oid_pkcs_12PbeIds;
LIBSPEC_ME
extern Oid Oid_pbeWithSHAAnd128BitRC4;
LIBSPEC_ME
extern Oid Oid_pbeWithSHAAnd40BitRC4;
LIBSPEC_ME
extern Oid Oid_pbeWithSHAAnd3_KeyTripleDES_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithSHAAnd2_KeyTripleDES_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithSHAAnd128BitRC2_CBC;
LIBSPEC_ME
extern Oid Oid_pbewithSHAAnd40BitRC2_CBC;
LIBSPEC_ME
extern Oid Oid_bagtypes;
LIBSPEC_ME
extern Oid Oid_keyBag;
LIBSPEC_ME
extern Oid Oid_pkcs8ShroudedKeyBag;
LIBSPEC_ME
extern Oid Oid_certBag;
LIBSPEC_ME
extern Oid Oid_crlBag;
LIBSPEC_ME
extern Oid Oid_secretBag;
LIBSPEC_ME
extern Oid Oid_safeContentsBag;
LIBSPEC_ME
extern Oid Oid_md2;
LIBSPEC_ME
extern Oid Oid_md5;
LIBSPEC_ME
extern Oid Oid_hmacWithSHA1;   /* id_hmacWithSHA1 */
LIBSPEC_ME
extern Oid Oid_rc2CBC;
LIBSPEC_ME
extern Oid Oid_des_EDE3_CBC;   /* des_EDE3_CBC */
LIBSPEC_ME
extern Oid Oid_rc5_CBC_PAD;
LIBSPEC_ME
extern Oid Oid_pkix;
LIBSPEC_ME
extern Oid Oid_mod;   /* id-mod */
LIBSPEC_ME
extern Oid Oid_attribute_cert;   /* id-mod-attribute_cert */
LIBSPEC_ME
extern Oid Oid_pe;   /* id-pe */
LIBSPEC_ME
extern Oid Oid_authorityInfoAccess;   /* id-pe-authorityInfoAccess */
LIBSPEC_ME
extern Oid Oid_ac_auditIdentity;   /* id-pe-ac-auditIdentity */
LIBSPEC_ME
extern Oid Oid_aaControls;   /* id-pe-aaControls */
LIBSPEC_ME
extern Oid Oid_ac_proxying;   /* id-pe-ac-proxying */
LIBSPEC_ME
extern Oid Oid_kp;   /* id-kp */
LIBSPEC_ME
extern Oid Oid_serverAuth;   /* id-kp-serverAuth */
LIBSPEC_ME
extern Oid Oid_clientAuth;   /* id-kp-clientAuth */
LIBSPEC_ME
extern Oid Oid_codeSigning;   /* id-kp-codeSigning */
LIBSPEC_ME
extern Oid Oid_emailProtection;   /* id-kp-emailProtection */
LIBSPEC_ME
extern Oid Oid_timeStamping;   /* id-kp-timeStamping */
LIBSPEC_ME
extern Oid Oid_OCSPSigning;   /* id-kp-OCSPSigning */
LIBSPEC_ME
extern Oid Oid_aca;   /* id-aca */
LIBSPEC_ME
extern Oid Oid_authenticationInfo;   /* id-aca-authenticationInfo */
LIBSPEC_ME
extern Oid Oid_accessIdentity;   /* id-aca-accessIdentity */
LIBSPEC_ME
extern Oid Oid_chargingIdentity;   /* id-aca-chargingIdentity */
LIBSPEC_ME
extern Oid Oid_group;   /* id-aca-group */
LIBSPEC_ME
extern Oid Oid_encAttrs;   /* id-aca-encAttrs */
LIBSPEC_ME
extern Oid Oid_ad;   /* id-ad */
LIBSPEC_ME
extern Oid Oid_ocsp;   /* id-pkix-ocsp */
LIBSPEC_ME
extern Oid Oid_ocsp_basic;   /* id-pkix-ocsp-basic */
LIBSPEC_ME
extern Oid Oid_ocsp_nonce;   /* id-pkix-ocsp-nonce */
LIBSPEC_ME
extern Oid Oid_ocsp_crl;   /* id-pkix-ocsp-crl */
LIBSPEC_ME
extern Oid Oid_ocsp_response;   /* id-pkix-ocsp-response */
LIBSPEC_ME
extern Oid Oid_ocsp_nocheck;   /* id-pkix-ocsp-nocheck */
LIBSPEC_ME
extern Oid Oid_ocsp_archive_cutoff;   /* id-pkix-ocsp-archive-cutoff */
LIBSPEC_ME
extern Oid Oid_ocsp_service_locator;   /* id-pkix-ocsp-service-locator */
LIBSPEC_ME
extern Oid Oid_desCBC;
LIBSPEC_ME
extern Oid Oid_SHA1;   /* id-SHA1 */
LIBSPEC_ME
extern Oid Oid_sha1withRSASignature;
LIBSPEC_ME
extern Oid Oid_id_at_clearance;
LIBSPEC_ME
extern Oid Oid_at;   /* id-at */
LIBSPEC_ME
extern Oid Oid_commonName;   /* id-at-commonName */
LIBSPEC_ME
extern Oid Oid_serialNumber;   /* id-at-serialNumber */
LIBSPEC_ME
extern Oid Oid_countryName;   /* id-at-countryName */
LIBSPEC_ME
extern Oid Oid_localityName;   /* id-at-localityName */
LIBSPEC_ME
extern Oid Oid_stateOrProvinceName;   /* id-at-stateOrProvinceName */
LIBSPEC_ME
extern Oid Oid_organizationName;   /* id-at-organizationName */
LIBSPEC_ME
extern Oid Oid_organizationUnitName;   /* id-at-organizationUnitName */
LIBSPEC_ME
extern Oid Oid_businessCategory;   /* id-at-businessCategory */
LIBSPEC_ME
extern Oid Oid_userPassword;   /* id-at-userPassword */
LIBSPEC_ME
extern Oid Oid_userCertificate;   /* id-at-userCertificate */
LIBSPEC_ME
extern Oid Oid_cAcertificate;   /* id-at-cAcertificate */
LIBSPEC_ME
extern Oid Oid_authorityRevocationList;   /* id-at-authorityRevocationList */
LIBSPEC_ME
extern Oid Oid_certificateRevocationList;   /* id-at-certificateRevocationList */
LIBSPEC_ME
extern Oid Oid_crossCertificatePair;   /* id-at-crossCertificatePair */
LIBSPEC_ME
extern Oid Oid_uniqeIdentifier;   /* id-at-uniqueIdentifier */
LIBSPEC_ME
extern Oid Oid_supportedAlgorithms;   /* id-at-attributeCertificate */
LIBSPEC_ME
extern Oid Oid_deltaRevocationList;   /* id-at-supportedAlgorithms */
LIBSPEC_ME
extern Oid Oid_attributeCertificate;   /* id-at-deltaRevocationList */
LIBSPEC_ME
extern Oid Oid_role;   /* id-at-role */
LIBSPEC_ME
extern Oid Oid_algorithm;
LIBSPEC_ME
extern Oid Oid_encryptionAlgorithm;
LIBSPEC_ME
extern Oid Oid_hashAlgorithm;
LIBSPEC_ME
extern Oid Oid_signatureAlgorithm;
LIBSPEC_ME
extern Oid Oid_matchingRule;   /* id-mr */
LIBSPEC_ME
extern Oid Oid_ce;   /* id-ce */
LIBSPEC_ME
extern Oid Oid_subjectDirectoryAttributes;   /* id-ce-subjectDirectoryAttributes */
LIBSPEC_ME
extern Oid Oid_subjectKeyIdentifier;   /* id-ce-subjectKeyIdentifier */
LIBSPEC_ME
extern Oid Oid_keyUsage;   /* id-ce-keyUsage */
LIBSPEC_ME
extern Oid Oid_privateKeyUsagePeriod;   /* id-ce-privateKeyUsagePeriod */
LIBSPEC_ME
extern Oid Oid_subjectAltName;   /* id-ce-subjectAltName */
LIBSPEC_ME
extern Oid Oid_issuerAltName;   /* id-ce-issuerAltName */
LIBSPEC_ME
extern Oid Oid_basicConstraints;   /* id-ce-basicConstraints */
LIBSPEC_ME
extern Oid Oid_cRLNumber;   /* id-ce-cRLNumber */
LIBSPEC_ME
extern Oid Oid_reasonCode;   /* id-ce-reasonCode */
LIBSPEC_ME
extern Oid Oid_holdInstructionCode;   /* id-ce-holdInstructionCode */
LIBSPEC_ME
extern Oid Oid_invalidityDate;   /* id-ce-invalidityDate */
LIBSPEC_ME
extern Oid Oid_deltaCRLIndicator;   /* id-ce-deltaCRLIndicator */
LIBSPEC_ME
extern Oid Oid_issuingDistributionPoint;   /* id-ce-issuingDistributionPoint */
LIBSPEC_ME
extern Oid Oid_certificateIssuer;   /* id-ce-certificateIssuer */
LIBSPEC_ME
extern Oid Oid_nameConstraints;   /* id-ce-nameConstraints */
LIBSPEC_ME
extern Oid Oid_cRLDistributionPoints;   /* id-ce-cRLDistributionPoints */
LIBSPEC_ME
extern Oid Oid_certificatePolicies;   /* id-ce-certificatePolicies */
LIBSPEC_ME
extern Oid Oid_policyMappings;   /* id-ce-policyMappings */
LIBSPEC_ME
extern Oid Oid_authorityKeyIdentifier;   /* id-ce-authorityKeyIdentifier */
LIBSPEC_ME
extern Oid Oid_policyConstraints;   /* id-ce-policyConstraints */
LIBSPEC_ME
extern Oid Oid_extKeyUsage;   /* id-ce-extKeyUsage */
LIBSPEC_ME
extern Oid Oid_targetInformation;   /* id-ce-targetInformation */
LIBSPEC_ME
extern Oid Oid_has160_old;
LIBSPEC_ME
extern Oid Oid_kCDSA_old;
LIBSPEC_ME
extern Oid Oid_has160withKCDSA_old;
LIBSPEC_ME
extern Oid Oid_sha1withKCDSA_old;
LIBSPEC_ME
extern Oid Oid_pACA_old;
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndPACA_CBC_old;
LIBSPEC_ME
extern Oid Oid_pACA_CBC_old;
LIBSPEC_ME
extern Oid Oid_nEAT_old;
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndNEAT_CBC_old;
LIBSPEC_ME
extern Oid Oid_nEAT_CBC_old;
LIBSPEC_ME
extern Oid Oid_netscape;
LIBSPEC_ME
extern Oid Oid_netscape_cert_extension;
LIBSPEC_ME
extern Oid Oid_netscape_cert_type;
LIBSPEC_ME
extern Oid Oid_netscape_base_url;
LIBSPEC_ME
extern Oid Oid_netscape_revocation_url;
LIBSPEC_ME
extern Oid Oid_netscape_renewal_url;
LIBSPEC_ME
extern Oid Oid_qt;   /* id-qt */
LIBSPEC_ME
extern Oid Oid_cps;   /* id-qt-cps */
LIBSPEC_ME
extern Oid Oid_unotice;   /* id-qt-unotice */
LIBSPEC_ME
extern Oid Oid_caIssuers;   /* id-ad-caIssuers */
LIBSPEC_ME
extern Oid Oid_passwordBasedMac;   /* PasswordBasedMac */
LIBSPEC_ME
extern Oid Oid_dHBasedMac;   /* DHBasedMac */
LIBSPEC_ME
extern Oid Oid_kisa_identifyData;   /* id-kisa-identifyData */
LIBSPEC_ME
extern Oid Oid_seedCBCwithSHA1;   /* seedCBCwithSHA1 or pbeWithSHA1AndSEED-CBC */
LIBSPEC_ME
extern Oid Oid_desMAC;   /* id-des-MAC */
LIBSPEC_ME
extern Oid Oid_it;   /* id-it */
LIBSPEC_ME
extern Oid Oid_caProtEncCert;   /* id-it-caProtEncCert */
LIBSPEC_ME
extern Oid Oid_signKeyPairTypes;   /* id-it-signKeyPairTypes */
LIBSPEC_ME
extern Oid Oid_encKeyPairTypes;   /* id-it-encKeyPairTypes */
LIBSPEC_ME
extern Oid Oid_preferredSymmAlg;   /* id-it-preferredSymmAlg */
LIBSPEC_ME
extern Oid Oid_caKeyUpdateInfo;   /* id-it-caKeyUpdateInfo */
LIBSPEC_ME
extern Oid Oid_currentCRL;   /* id-it-currentCRL */
LIBSPEC_ME
extern Oid Oid_unsupportedOIDs;   /* id-it-unsupportedOIDs */
LIBSPEC_ME
extern Oid Oid_keyPairParamReq;   /* id-it-keyPairParamReq */
LIBSPEC_ME
extern Oid Oid_keyPairParamRep;   /* id-it-keyPairParamRep */
LIBSPEC_ME
extern Oid Oid_revPassphrase;   /* id-it-revPassphrase */
LIBSPEC_ME
extern Oid Oid_implicitConfirm;   /* id-it-implicitConfirm */
LIBSPEC_ME
extern Oid Oid_confirmWaitTime;   /* id-it-confirmWaitTime */
LIBSPEC_ME
extern Oid Oid_origPKIMessage;   /* id-it-origPKIMessage */
LIBSPEC_ME
extern Oid Oid_suppLangTags;   /* id-it-suppLangTags */
LIBSPEC_ME
extern Oid Oid_pkip;   /* id-pkip */
LIBSPEC_ME
extern Oid Oid_regCtrl;   /* id-regCtrl */
LIBSPEC_ME
extern Oid Oid_regToken;   /* id-regCtrl-regToken */
LIBSPEC_ME
extern Oid Oid_authenticator;   /* id-regCtrl-authenticator */
LIBSPEC_ME
extern Oid Oid_pkiPublicationInfo;   /* id-regCtrl-pkiPublicationInfo */
LIBSPEC_ME
extern Oid Oid_pkiArchiveOptions;   /* id-regCtrl-pkiArchiveOptions */
LIBSPEC_ME
extern Oid Oid_oldCertID;   /* id-regCtrl-oldCertID */
LIBSPEC_ME
extern Oid Oid_protocolEncrKey;   /* id-regCtrl-protocolEncrKey */
LIBSPEC_ME
extern Oid Oid_regInfo;   /* id-regInfo */
LIBSPEC_ME
extern Oid Oid_utf8Pairs;   /* id-regInfo-utf8Pairs */
LIBSPEC_ME
extern Oid Oid_certReq;   /* id-regInfo-certReq */
LIBSPEC_ME
extern Oid Oid_penta_at;   /* penta-at */
LIBSPEC_ME
extern Oid Oid_penta_at_cmp;   /* penta-at-cmp */
LIBSPEC_ME
extern Oid Oid_penta_at_dir;   /* penta-at-dir */
LIBSPEC_ME
extern Oid Oid_penta_at_ac;   /* penta-at-ac */
LIBSPEC_ME
extern Oid Oid_penta_acElement;   /* penta-at-ac-acElement */
LIBSPEC_ME
extern Oid Oid_penta_userIdentifierList;   /* penta-at-ac-userIdentifierList */
LIBSPEC_ME
extern Oid Oid_penta_acElements;   /* penta-at-ac-acElements */
LIBSPEC_ME
extern Oid Oid_penta_roleCapabilityList;   /* penta-at-ac-roleCapabilityList */
LIBSPEC_ME
extern Oid Oid_penta_role;   /* penta-at-ac-role */
LIBSPEC_ME
extern Oid Oid_penta_userTicket;   /* penta-at-ac-userTicket */
LIBSPEC_ME
extern Oid Oid_penta_at_oc;   /* penta-at-oc */
LIBSPEC_ME
extern Oid Oid_aes;
LIBSPEC_ME
extern Oid Oid_aes128ECB;   /* id-aes128-ECB */
LIBSPEC_ME
extern Oid Oid_aes128CBC;   /* id-aes128-CBC */
LIBSPEC_ME
extern Oid Oid_aes128OFB;   /* id-aes128-OFB */
LIBSPEC_ME
extern Oid Oid_aes128CFB;   /* id-aes128-CFB */
LIBSPEC_ME
extern Oid Oid_aes192ECB;   /* id-aes192-ECB */
LIBSPEC_ME
extern Oid Oid_aes192CBC;   /* id-aes192-CBC */
LIBSPEC_ME
extern Oid Oid_aes192OFB;   /* id-aes192-OFB */
LIBSPEC_ME
extern Oid Oid_aes192CFB;   /* id-aes192-CFB */
LIBSPEC_ME
extern Oid Oid_aes256ECB;   /* id-aes256-ECB */
LIBSPEC_ME
extern Oid Oid_aes256CBC;   /* id-aes256-CBC */
LIBSPEC_ME
extern Oid Oid_aes256OFB;   /* id-aes256-OFB */
LIBSPEC_ME
extern Oid Oid_aes256CFB;   /* id-aes256-CFB */
LIBSPEC_ME
extern Oid Oid_blowfishECB;
LIBSPEC_ME
extern Oid Oid_blowfishCBC;
LIBSPEC_ME
extern Oid Oid_blowfishCFB;
LIBSPEC_ME
extern Oid Oid_blowfishOFB;
LIBSPEC_ME
extern Oid Oid_cast5CBC;
LIBSPEC_ME
extern Oid Oid_ideaECB;   /* IDEA-ECB */
LIBSPEC_ME
extern Oid Oid_ideaCBC;   /* IDEA-CBC */
LIBSPEC_ME
extern Oid Oid_ideaCFB;   /* IDEA-CFB */
LIBSPEC_ME
extern Oid Oid_ideaOFB;   /* IDEA-OFB */
LIBSPEC_ME
extern Oid Oid_penta_at_pkc;   /* penta-at-pkc */
LIBSPEC_ME
extern Oid Oid_penta_at_pkc_exts;   /* penta-at-pkc-exts */
LIBSPEC_ME
extern Oid Oid_pentaAdministrator;   /* penta-at-pkc-exts-pentaAdministrator */
LIBSPEC_ME
extern Oid Oid_pentaRevDescription;   /* penta-at-pkc-exts-pentaRevDescription */
LIBSPEC_ME
extern Oid Oid_penta_at_pkc_exts_reserved2;   /* penta-at-pkc-exts-reserved2 */
LIBSPEC_ME
extern Oid Oid_penta_at_pkc_exts_reserved3;   /* penta-at-pkc-exts-reserved3 */
LIBSPEC_ME
extern Oid Oid_penta_at_pkc_exts_reserved4;   /* penta-at-pkc-exts-reserved4 */
LIBSPEC_ME
extern Oid Oid_penta_at_pkc_exts_reserved5;   /* penta-at-pkc-exts-reserved5 */
LIBSPEC_ME
extern Oid Oid_HMAC_SHA1;
LIBSPEC_ME
extern Oid Oid_microsoft;
LIBSPEC_ME
extern Oid Oid_msCTL;
LIBSPEC_ME
extern Oid Oid_ipsecEndSystem;
LIBSPEC_ME
extern Oid Oid_ipsecTunnel;
LIBSPEC_ME
extern Oid Oid_ipsecUser;
LIBSPEC_ME
extern Oid Oid_penta_at_cmp_keyPolicyId;   /* penta-at-cmp-keyPolicyId */
LIBSPEC_ME
extern Oid Oid_penta_at_cmp_keyPolicyReq;   /* penta-at-cmp-keyPolicyReq */
LIBSPEC_ME
extern Oid Oid_penta_at_cmp_keyPolicyRes;   /* penta-at-cmp-keyPolicyRes */
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndSEED_CBC_old2;
LIBSPEC_ME
extern Oid Oid_penta_alg_pbeWithSHA1AndSEED_CBC;   /* penta-alg-pbeWithSHA1AndSEED_CBC */
LIBSPEC_ME
extern Oid Oid_certificatePolicies_anyPolicy;   /* anyPolicy */
LIBSPEC_ME
extern Oid Oid_gpki_alg;   /* gpki-alg */
LIBSPEC_ME
extern Oid Oid_nEAT;
LIBSPEC_ME
extern Oid Oid_nEAT_ECB;
LIBSPEC_ME
extern Oid Oid_nEAT_CBC;
LIBSPEC_ME
extern Oid Oid_nEAT_OFB;
LIBSPEC_ME
extern Oid Oid_nEAT_CFB;
LIBSPEC_ME
extern Oid Oid_nEAT_MAC;
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndNEAT_CBC;
LIBSPEC_ME
extern Oid Oid_pbeWithHAS160AndNEAT_CBC;
LIBSPEC_ME
extern Oid Oid_gov;   /* Government */
LIBSPEC_ME
extern Oid Oid_gpki_cp;   /* GPKI-CP */
LIBSPEC_ME
extern Oid Oid_gpki_class1;   /* GPKI-Class1 */
LIBSPEC_ME
extern Oid Oid_gpki_class1_department;   /* GPKI-Class1-Department */
LIBSPEC_ME
extern Oid Oid_gpki_class1_computer;   /* GPKI-Class1-Computer */
LIBSPEC_ME
extern Oid Oid_gpki_class2;   /* GPKI-Class2 */
LIBSPEC_ME
extern Oid Oid_gpki_class2_personal;   /* GPKI-Class2-Personal */
LIBSPEC_ME
extern Oid Oid_gpki_kp;   /* GPKI-KP */
LIBSPEC_ME
extern Oid Oid_gpki_at;   /* GPKI-Attribute */
LIBSPEC_ME
extern Oid Oid_gpki_lca;   /* GPKI-LCA */
LIBSPEC_ME
extern Oid Oid_pca_mogaha;   /* PCA-MOGAHA */
LIBSPEC_ME
extern Oid Oid_pca_mogaha_cp;   /* PCA-MOGAHA-CP */
LIBSPEC_ME
extern Oid Oid_pca_assembly;   /* PCA-Assembly */
LIBSPEC_ME
extern Oid Oid_pca_court;   /* PCA-Court */
LIBSPEC_ME
extern Oid Oid_pca_electionAdmin;   /* PCA-ElectionAdmin */
LIBSPEC_ME
extern Oid Oid_pca_constitutionalCourt;   /* PCA-ConstitutionalCourt */
LIBSPEC_ME
extern Oid Oid_seedECBWithHAS160;
LIBSPEC_ME
extern Oid Oid_seedCBCWithHAS160;
LIBSPEC_ME
extern Oid Oid_seedOFBWithHAS160;
LIBSPEC_ME
extern Oid Oid_seedCFBWithHAS160;
LIBSPEC_ME
extern Oid Oid_seedECBWithSHA1;
LIBSPEC_ME
extern Oid Oid_seedOFBWithSHA1;
LIBSPEC_ME
extern Oid Oid_seedCFBWithSHA1;
LIBSPEC_ME
extern Oid Oid_rsaWithHAS160;
LIBSPEC_ME
extern Oid Oid_ecdsaWithHAS160;
LIBSPEC_ME
extern Oid Oid_ecc;
LIBSPEC_ME
extern Oid Oid_ncaSign;   /* 한국전산원 */
LIBSPEC_ME
extern Oid Oid_crossCert;   /* 한국전자인증 */
LIBSPEC_ME
extern Oid Oid_crossCert_cp;   /* 한국전자인증-인증서정책 */
LIBSPEC_ME
extern Oid Oid_npki_othername;   /* 확장명칭형식 */
LIBSPEC_ME
extern Oid Oid_npki_othername_vid;   /* virtual ID */
LIBSPEC_ME
extern Oid Oid_npki_othername_encryptedVID;   /* encrypted virtual ID */
LIBSPEC_ME
extern Oid Oid_npki_app;   /* NPKI-application */
LIBSPEC_ME
extern Oid Oid_npki_smime;   /* NPKI-SMIME */
LIBSPEC_ME
extern Oid Oid_npki_smime_alg;   /* NPKI-smime-알고리즘 */
LIBSPEC_ME
extern Oid Oid_npki_smime_cMSSEEDwrap;   /* CMS-Seed-Key-wrapping */
LIBSPEC_ME
extern Oid Oid_npki_kbims;   /* NPKI-Biometrics */
LIBSPEC_ME
extern Oid Oid_npki_interoperability;   /* NPKI-상호연동 */
LIBSPEC_ME
extern Oid Oid_ctl;
LIBSPEC_ME
extern Oid Oid_ctl_subjectUsage;   /* subject Usage */
LIBSPEC_ME
extern Oid Oid_ctl_electronic_civil_app;   /* CTL-민원서비스 */
LIBSPEC_ME
extern Oid Oid_ctl_oc;   /* CTL-ob */
LIBSPEC_ME
extern Oid Oid_ctl_oc_pkiCTL;
LIBSPEC_ME
extern Oid Oid_ctl_at;   /* CTL-at */
LIBSPEC_ME
extern Oid Oid_ctl_at_certificateTrustList;
LIBSPEC_ME
extern Oid Oid_penta_customer;   /* 펜타시큐리티 고객 */
LIBSPEC_ME
extern Oid Oid_lgcaltex;   /* LG-Caltex */
LIBSPEC_ME
extern Oid Oid_lgcaltex_cp;   /* LG-Caltex 인증서정책 */
LIBSPEC_ME
extern Oid Oid_hncb;   /* 주택은행 */
LIBSPEC_ME
extern Oid Oid_hncb_cp;   /* 주택은행 인증서정책 */
LIBSPEC_ME
extern Oid Oid_hncb_ca;   /* 주택은행 인증기관 */
LIBSPEC_ME
extern Oid Oid_hncb_alg;   /* 주택은행 알고리즘 */
LIBSPEC_ME
extern Oid Oid_hncb_kp;   /* 주택은행 키용도 */
LIBSPEC_ME
extern Oid Oid_hncb_at;   /* 주택은행 인증서속성 */
LIBSPEC_ME
extern Oid Oid_penta_permissions;   /* penta-at-ac-permissions */
LIBSPEC_ME
extern Oid Oid_penta_product;   /* penta-product */
LIBSPEC_ME
extern Oid Oid_penta_product_issac;   /* ISSAC */
LIBSPEC_ME
extern Oid Oid_penta_product_isign;   /* ISign */
LIBSPEC_ME
extern Oid Oid_isign_mechanism;   /* ISign-Mechanisms */
LIBSPEC_ME
extern Oid Oid_isign_gssapi_v2;   /* ISign-GSSAPI-v2 */
LIBSPEC_ME
extern Oid Oid_isign_x500_dn;   /* ISign-X.500-DN */
LIBSPEC_ME
extern Oid Oid_gssapi;   /* GSSAPI */
LIBSPEC_ME
extern Oid Oid_gssapi_user_name;   /* GSSAPI_UserName */
LIBSPEC_ME
extern Oid Oid_gssapi_machine_uid_name;   /* GSSAPI_MachineUidName */
LIBSPEC_ME
extern Oid Oid_gssapi_string_uid_name;   /* GSSAPI_StringUidName */
LIBSPEC_ME
extern Oid Oid_gssapi_service_name;   /* GSSAPI_ServiceName */
LIBSPEC_ME
extern Oid Oid_internet_security_nametypes;   /* Internet-Security-NameTypes */
LIBSPEC_ME
extern Oid Oid_gss_host_based_services;   /* GSS-HostBasedServices */
LIBSPEC_ME
extern Oid Oid_gss_anonymous_name;   /* GSS-AnonymousName */
LIBSPEC_ME
extern Oid Oid_gss_api_exported_name;   /* GSS-API-ExportedName */
LIBSPEC_ME
extern Oid Oid_spkm1;   /* SPKM-1 (rfc2025) */
LIBSPEC_ME
extern Oid Oid_spkm2;   /* SPKM-2 (rfc2025) */
LIBSPEC_ME
extern Oid Oid_npki;   /* NPKI */
LIBSPEC_ME
extern Oid Oid_npki_at;   /* NPKI-Attribute */
LIBSPEC_ME
extern Oid Oid_kisa_identifyData200209;   /* KISA-IdentifyData */
LIBSPEC_ME
extern Oid Oid_VID;   /* Virtual-ID */
LIBSPEC_ME
extern Oid Oid_EncryptedVID;   /* EncryptedVID */
LIBSPEC_ME
extern Oid Oid_randomNum;   /* VID-RandomNumber */
LIBSPEC_ME
extern Oid Oid_domainComponent;   /* Domain-Component */
LIBSPEC_ME
extern Oid Oid_penta_kp;   /* penta-kp */
LIBSPEC_ME
extern Oid Oid_penta_kp_auth_only;   /* penta-kp-authOnly */
LIBSPEC_ME
extern Oid Oid_inhibitAnyPolicy;   /* id-ce-inhibitAnyPolicy */
LIBSPEC_ME
extern Oid Oid_freshestCRL;   /* id-ce-freshestCRL */
LIBSPEC_ME
extern Oid Oid_subjectInfoAccess;   /* id-pe-subjectInfoAccess */
LIBSPEC_ME
extern Oid Oid_penta_alg_aRIA;   /* ARIA */
LIBSPEC_ME
extern Oid Oid_aRIA_CBC;   /* ARIA_CBC */
LIBSPEC_ME
extern Oid Oid_pbeWithSHA1AndARIA;   /* PBE_With_SHA1_ARIA */
LIBSPEC_ME
extern Oid Oid_SHA256;   /* id-sha256 */
LIBSPEC_ME
extern Oid Oid_SHA384;   /* id-sha384 */
LIBSPEC_ME
extern Oid Oid_SHA512;   /* id-sha512 */
LIBSPEC_ME
extern Oid Oid_sha256WithRSAEncription;
LIBSPEC_ME
extern Oid Oid_sha384WithRSAEncription;
LIBSPEC_ME
extern Oid Oid_sha512WithRSAEncription;
LIBSPEC_ME
extern Oid Oid_fork256;   /* FORK256 */
LIBSPEC_ME
extern Oid Oid_kcdsaWithFORK256;   /* FORK256 해쉬 후 KCDSA 전자서명 */
LIBSPEC_ME
extern Oid Oid_kcdsaWithSHA256;   /* SHA-256 해쉬 후 KCDSA 전자서명 */
LIBSPEC_ME
extern Oid Oid_seedECBWithFORK256;   /* FORK256 해쉬로 키 추출 후 SEED ECB로 암호화 */
LIBSPEC_ME
extern Oid Oid_seedCBCWithFORK256;   /* FORK256 해쉬로 키 추출 후 SEED CBC로 암호화 */
LIBSPEC_ME
extern Oid Oid_seedOFBWithFORK256;   /* FORK256 해쉬로 키 추출 후 SEED OFB로 암호화 */
LIBSPEC_ME
extern Oid Oid_seedCFBWithFORK256;   /* FORK256 해쉬로 키 추출 후 SEED CFB로 암호화 */
LIBSPEC_ME
extern Oid Oid_seedECBWithSHA256;   /* SHA-265 해쉬로 키 추출 후 SEED ECB 로 암호화 */
LIBSPEC_ME
extern Oid Oid_seedCBCWithSHA256;   /* SHA-256 해쉬로 키 추출 후 SEED CBC로 암호화 */
LIBSPEC_ME
extern Oid Oid_seedOFBWithSHA256;   /* SHA-256 해쉬로 키 추출 후 SEED OFB 로 암호화 */
LIBSPEC_ME
extern Oid Oid_seedCFBWithSHA256;   /* SHA-256 해쉬로 키 추출 후 SEED CFB로 암호화 */
LIBSPEC_ME
extern Oid Oid_rsaWithFORK256;   /* FORK256 해쉬 후 RSA 전자서명 */
LIBSPEC_ME
extern Oid Oid_kcdsa1WithFORK256;   /* FORK256 해쉬 후 KCDSA1 전자서명 */
LIBSPEC_ME
extern Oid Oid_kcdsa1WithSHA256;   /* SHA-256 해쉬 후 KCDSA1 전자서명 */
LIBSPEC_ME
extern Oid Oid_ecdsaWithFORK256;   /* FORK256 해쉬 후 ECDSA 전자서명 */
LIBSPEC_ME
extern Oid Oid_surName;   /* id-at-surname */
LIBSPEC_ME
extern Oid Oid_streetAddress;   /* id-at-streetAddress */
LIBSPEC_ME
extern Oid Oid_title;   /* id-at-title */
LIBSPEC_ME
extern Oid Oid_givenName;   /* id-at-givenName */
LIBSPEC_ME
extern Oid Oid_initials;   /* id-at-initials */
LIBSPEC_ME
extern Oid Oid_uniqueIdentifie;   /* id-at-uniqueIdentifie */
LIBSPEC_ME
extern Oid Oid_generationQualifier;   /* id-at-generationQualifier */
LIBSPEC_ME
extern Oid Oid_dnQualifier;   /* id-at-dnQualifier */
LIBSPEC_ME
extern Oid Oid_pseudonym;   /* id-at-pseudonym */
LIBSPEC_ME
extern Oid Oid_rfc822MailBox;
LIBSPEC_ME
extern Oid Oid_ariaCBC;   /* ARIA128 - CBC모드 */
LIBSPEC_ME
extern Oid Oid_pbewithSHA1andARIA_CBC;   /* 패스워드기반 ARIA128 - CBC모드 */
LIBSPEC_ME
extern Oid Oid_id_RSASSA_PSS;   /* id-RSASSA-PSS */
LIBSPEC_ME
extern Oid Oid_ecdsa;   /* X9.62 ECDSA */
LIBSPEC_ME
extern Oid Oid_prime_field;   /* X9.62 prime field */
LIBSPEC_ME
extern Oid Oid_binary_field;   /* X9.62 binary field */
LIBSPEC_ME
extern Oid Oid_ecdsa_with_SHA1;   /* ECDSA signature with SHA1 */
LIBSPEC_ME
extern Oid Oid_ecdsa_with_SHA2;   /* ECDSA signature with SHA2 family */
LIBSPEC_ME
extern Oid Oid_ecdsa_with_SHA224;   /* ECDSA signature with SHA224 */
LIBSPEC_ME
extern Oid Oid_ecdsa_with_SHA256;   /* ECDSA signature with SHA256 */
LIBSPEC_ME
extern Oid Oid_ecdsa_with_SHA384;   /* ECDSA signature with SHA384 */
LIBSPEC_ME
extern Oid Oid_ecdsa_with_SHA512;   /* ECDSA signature with SHA512 */
LIBSPEC_ME
extern Oid Oid_id_ecPublicKey;   /* Elliptic curve public key */
LIBSPEC_ME
extern Oid Oid_secp192r1;   /* secp192r1 */
LIBSPEC_ME
extern Oid Oid_secp256r1;   /* secp256r1 */
LIBSPEC_ME
extern Oid Oid_sect163k1;   /* sect163k1 */
LIBSPEC_ME
extern Oid Oid_sect163r2;   /* sect163r2 */
LIBSPEC_ME
extern Oid Oid_sect283k1;   /* sect283k1 */
LIBSPEC_ME
extern Oid Oid_sect283r1;   /* sect283r1 */
LIBSPEC_ME
extern Oid Oid_sect233k1;   /* sect233k1 */
LIBSPEC_ME
extern Oid Oid_sect233r1;   /* sect233r1 */
LIBSPEC_ME
extern Oid Oid_secp224r1;   /* secp224r1 */
LIBSPEC_ME
extern Oid Oid_secp384r1;   /* secp384r1 */
LIBSPEC_ME
extern Oid Oid_secp521r1;   /* secp521r1 */
LIBSPEC_ME
extern Oid Oid_sect409k1;   /* sect409k1 */
LIBSPEC_ME
extern Oid Oid_sect409r1;   /* sect409r1 */
LIBSPEC_ME
extern Oid Oid_sect571k1;   /* sect571k1 */
LIBSPEC_ME
extern Oid Oid_sect571r1;   /* sect571r1 */
LIBSPEC_ME
extern Oid Oid_eckcdsa;   /* EC-KCDSA */
LIBSPEC_ME
extern Oid Oid_eckcdsa_with_HAS160;   /* EC-KCDSA with HAS160 */
LIBSPEC_ME
extern Oid Oid_eckcdsa_with_FORK256;   /* EC-KCDSA with FORK256 */
LIBSPEC_ME
extern Oid Oid_eckcdsa_with_SHA1;   /* EC-KCDSA with SHA1 */
LIBSPEC_ME
extern Oid Oid_eckcdsa_with_SHA224;   /* EC-KCDSA with SHA224 */
LIBSPEC_ME
extern Oid Oid_eckcdsa_with_SHA256;   /* EC-KCDSA with SHA256 */
LIBSPEC_ME
extern Oid Oid_kcdsaWithSHA224;   /* SHA224 해쉬 후 KCDSA 전자서명 */
LIBSPEC_ME
extern Oid Oid_kcdsa1WithSHA224;   /* SHA224 해쉬 후 KCDSA1 전자서명 */
LIBSPEC_ME
extern Oid Oid_id_ecPublicKey_KISA;   /* EC-KCDSA Public Key */
LIBSPEC_ME
extern Oid Oid_secp256k1;   /* secp256k1 */
LIBSPEC_ME
extern Oid Oid_brainpoolP256r1;   /* Brainpool P256r1 domain parameter set */
LIBSPEC_ME
extern Oid Oid_brainpoolP384r1;   /* Brainpool P384r1 domain parameter set */


#ifdef __cplusplus
}
#endif

#endif /* _oid_h_ */

