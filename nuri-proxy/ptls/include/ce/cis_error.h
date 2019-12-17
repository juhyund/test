/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _CIS_ERROR_H_
#define _CIS_ERROR_H_

/** @addtogroup CC
 * @{ */

/** @name Error Codes
 * @{ */
#define INVALID -10

/** @brief 암호모듈 상태 관련 에러 */
#define ER_INVALID_STATE						-9001
/** @brief 검증 암호운영상태에서 비검증 알고리즘을 사용할 때 */
#define ER_NOT_APPROVED_ALGORITHM				-9002
/** @brief alias */
#define ER_NOT_VERIFIED_ALGORITHM ER_NOT_APPROVED_ALGORITHM
/** @brief 무결성 검증이 실패했을 때 */
#define ER_SELFTEST_MODULE_INTEGRITY			-9003
/** @brief N/A */
#define ER_SELFTEST_VERIFIED_ALGORITHM			-9004
/** @brief 암호 서비스를 제공할 수 없는 상태일 때 */
#define ER_CIS_NOT_READY						-9005
/** @brief 조건부 자가 시험이 실패했을 때 */
#define ER_CONDITIONAL_SELFTEST					-9006
/** @brief fault-detection test of the RBG 실패했을 때 */
#define ER_FAULT_DETECTION_RBG					-9007

/** @brief ARIA-128 자가 시험이 실패했을 때 */
#define ER_SELFTEST_ARIA_128K					-9102
/** @brief ARIA-192 자가 시험이 실패했을 때 */
#define ER_SELFTEST_ARIA_192K					-9103
/** @brief ARIA-256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_ARIA_256K					-9104
/** @brief SEED 자가 시험이 실패했을 때 */
#define ER_SELFTEST_SEED						-9105
/** @brief HIGHT 자가 시험이 실패했을 때 */
#define ER_SELFTEST_HIGHT						-9106
/** @brief LEA-128 자가 시험이 실패했을 때 */
#define ER_SELFTEST_LEA128						-9107
/** @brief LEA-192 자가 시험이 실패했을 때 */
#define ER_SELFTEST_LEA192						-9108
/** @brief LEA-256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_LEA256						-9109
/** @brief SHA224 자가 시험이 실패했을 때 */
#define ER_SELFTEST_SHA224						-9123
/** @brief SHA256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_SHA256						-9124
/** @brief SHA384 자가 시험이 실패했을 때 */
#define ER_SELFTEST_SHA384						-9125
/** @brief SHA512 자가 시험이 실패했을 때 */
#define ER_SELFTEST_SHA512						-9126
/** @brief HMAC-SHA224 자가 시험이 실패했을 때 */
#define ER_SELFTEST_HMAC_SHA224					-9143
/** @brief HMAC-SHA256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_HMAC_SHA256					-9144
/** @brief HMAC-SHA384 자가 시험이 실패했을 때 */
#define ER_SELFTEST_HMAC_SHA384					-9145
/** @brief HMAC-SHA512 자가 시험이 실패했을 때 */
#define ER_SELFTEST_HMAC_SHA512					-9146
/** @brief CMAC-ARIA128 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CMAC_ARIA128				-9147
/** @brief CMAC-ARIA192 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CMAC_ARIA192				-9148
/** @brief CMAC-ARIA256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CMAC_ARIA256				-9149
/** @brief CMAC-SEED 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CMAC_SEED					-9150
/** @brief GCM-ARIA128 자가 시험이 실패했을 때 */
#define ER_SELFTEST_GMAC_ARIA128				-9151
/** @brief GCM-ARIA192 자가 시험이 실패했을 때 */
#define ER_SELFTEST_GMAC_ARIA192				-9152
/** @brief GCM-ARIA256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_GMAC_ARIA256				-9153
/** @brief GCM-SEED 자가 시험이 실패했을 때 */
#define ER_SELFTEST_GMAC_SEED					-9154
/** @brief CCM-ARIA128 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CCM_ARIA128					-9155
/** @brief CCM-ARIA192 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CCM_ARIA192					-9156
/** @brief CCM-ARIA256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CCM_ARIA256					-9157
/** @brief CCM-SEED 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CCM_SEED					-9158
/** @brief CMAC-HIGHT 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CMAC_HIGHT					-9167
/** @brief CMAC-LEA128 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CMAC_LEA128					-9168
/** @brief CMAC-LEA192 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CMAC_LEA192					-9169
/** @brief CMAC-LEA256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CMAC_LEA256					-9170
/** @brief CCM-LEA128 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CCM_LEA128					-9171
/** @brief CCM-LEA192 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CCM_LEA192					-9172
/** @brief CCM-LEA256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CCM_LEA256					-9173
/** @brief GCM-LEA128 자가 시험이 실패했을 때 */
#define ER_SELFTEST_GMAC_LEA128					-9174
/** @brief GCM-LEA192 자가 시험이 실패했을 때 */
#define ER_SELFTEST_GMAC_LEA192					-9175
/** @brief GCM-LEA256 자가 시험이 실패했을 때 */
#define ER_SELFTEST_GMAC_LEA256					-9176
/** @brief HASHDRBG 자가 시험이 실패했을 때 */
#define ER_SELFTEST_HASHDRBG					-9177
/** @brief HMACDRBG 자가 시험이 실패했을 때 */
#define ER_SELFTEST_HMACDRBG					-9178
/** @brief CTRDRBG 자가 시험이 실패했을 때 */
#define ER_SELFTEST_CTRDRBG						-9179
/** @brief RSAES 자가 시험이 실패했을 때 */
#define ER_SELFTEST_RSAES_OAEP					-9182
/** @brief KCDSA 자가 시험이 실패했을 때 */
#define ER_SELFTEST_KCDSA						-9201
/** @brief RSA-PSS 자가 시험이 실패했을 때 */
#define ER_SELFTEST_RSASSA_PSS					-9204
/** @brief ECDSA 자가 시험이 실패했을 때 */
#define ER_SELFTEST_ECDSA						-9205
/** @brief ECKCDSA 자가 시험이 실패했을 때 */
#define ER_SELFTEST_ECKCDSA						-9206
/** @brief DH 자가 시험이 실패했을 때 */
#define ER_SELFTEST_DH							-9207
/** @brief ECDH 자가 시험이 실패했을 때 */
#define ER_SELFTEST_ECDH						-9208

/* conflict */
/** @brief RSA v2.0의 서명 값이 올바르지 않을 때 */
#define ER_RSA20_VP1_SIG_OUT_OF_RANGE			-1090
/** @brief RSA v2.0의 메시지가 길 때 */
#define ER_RSA20_MESSAGE_TOO_LONG				-1091
/** @brief RSA v2.0의 암호문 길이가 올바르지 않을 때 */
#define ER_RSA20_WRONG_CIPHER_LEN				-1092

/** @brief RSA의 서명 값이 올바르지 않을 때 */
#define ER_RSA_VP1_SIG_OUT_OF_RANGE				-1090
/** @brief RSA의 메시지가 길 때 */
#define ER_RSA_MESSAGE_TOO_LONG					-1091
/** @brief RSA의 암호문 길이가 올바르지 않을 때 */
#define ER_RSA_WRONG_CIPHER_LEN					-1092
/** @brief RSA의 인코딩 과정이 잘못되었을 때 (FIPS 186-3 개정으로 인해 출력은 되지 않는 내부 에러 코드) */
#define ER_RSA_ENCODING_ERROR					-1093
/** @brief RSA의 서명 검증 결과가 서명 생성 결과와 불일치할 때 */
#define ER_RSA_INCONSISTENT						-1094
/** @brief RSA의 복호화 과정이 잘못되었을 때 */
#define ER_RSA_DECRYPT_ERROR					-1095  
/** @brief RSA의 인코딩 메시지 길이가 짧을 때 */
#define ER_RSA_MODULUS_TOO_SHORT				-1096

/** @brief 블록 암호에서 유효하지 않은 패딩 종류일 때 */
#define ER_BCIPHER_INVALID_PAD					-1001
/** @brief 블록 암호에서 유효하지 않은 운영 모드일 때  */
#define ER_BCIPHER_BAD_OP_MODE					-1002
/** @brief 블록 암호에서 유효하지 않은 태그 길이일 때 */
#define ER_BCIPHER_INVALID_TAG_LENGTH			-1003
/** @brief 블록 암호에서 유효하지 난스 길이일 때  */
#define ER_BCIPHER_INVALID_NONCE_LENGTH			-1004
/** @brief 블록 암호에서 유효하지 비밀키 길이일 때  */
#define ER_BCIPHER_INVALID_KEY_LENGTH			-1005

/* conflict */
/** @brief DSA의 서명 값일 올바르지 않을 때 */
#define ER_DSA_VP_SIG_OUT_OF_RANGE				-2001
/** @brief 다정도 정수 연산 과정에서 역원이 없을 때 */
#define ER_MINT_NOT_INVERTIBLE					-2011
/** @brief KCDSA의 서명 값이 올바르지 않을 때 */
#define ER_KCDSA_VP_SIG_OUT_OF_RANGE			-2040
/** @brief KCDSA용 난수발생기에서 사용하는 SEED와 SEED키와 같을 때 */
#define ER_KCDSARNGHAS160_SEED_EQUAL_TO_SEEDKEY	-2051

/** @brief 난수발생기 API에 유효하지 않은 해시함수를 입력하였을 때 */
#define ER_INVALID_HASH_ALG						-5282
/** @brief 난수발생기 API에 유효하지 않은 블록암호를 입력하였을 때 */
#define ER_INVALID_BLOCKCIPHER_ALG				-5283
/** @brief 난수발생기 API에 난수발생기 state로 null을 입력하였을 때 */
#define ER_NULL_STATE							-5285
/** @brief 난수발생기에 16384비트보다 긴 난수 발생을 요구하였을 때 */
#define ER_REQUEST_TOO_LONG_RANDOM				-5289
/** @brief 난수발생기 인스턴스화(초기화)하지 않았을 때 */
#define ER_NOT_INSTANTIATION_DRBG				-5290

/** @brief 함수의 출력이 저장될 파라미터의 메모리 버퍼 크기가 작을 때 */
#define ER_OUT_BUFFER_SIZE_IS_SMALL				-3000

/** @} */

/** @} */

#endif /* _CIS_ERROR_H_ */
