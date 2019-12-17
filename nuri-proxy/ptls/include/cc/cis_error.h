/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _CIS_ERROR_H_
#define _CIS_ERROR_H_

/** @addtogroup CC
 * @{ */

/** @name Error Codes
 * @{ */
#define INVALID -10

/** @brief ��ȣ��� ���� ���� ���� */
#define ER_INVALID_STATE						-9001
/** @brief ���� ��ȣ����¿��� ����� �˰����� ����� �� */
#define ER_NOT_APPROVED_ALGORITHM				-9002
/** @brief alias */
#define ER_NOT_VERIFIED_ALGORITHM ER_NOT_APPROVED_ALGORITHM
/** @brief ���Ἲ ������ �������� �� */
#define ER_SELFTEST_MODULE_INTEGRITY			-9003
/** @brief N/A */
#define ER_SELFTEST_VERIFIED_ALGORITHM			-9004
/** @brief ��ȣ ���񽺸� ������ �� ���� ������ �� */
#define ER_CIS_NOT_READY						-9005
/** @brief ���Ǻ� �ڰ� ������ �������� �� */
#define ER_CONDITIONAL_SELFTEST					-9006
/** @brief fault-detection test of the RBG �������� �� */
#define ER_FAULT_DETECTION_RBG					-9007

/** @brief ARIA-128 �ڰ� ������ �������� �� */
#define ER_SELFTEST_ARIA_128K					-9102
/** @brief ARIA-192 �ڰ� ������ �������� �� */
#define ER_SELFTEST_ARIA_192K					-9103
/** @brief ARIA-256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_ARIA_256K					-9104
/** @brief SEED �ڰ� ������ �������� �� */
#define ER_SELFTEST_SEED						-9105
/** @brief HIGHT �ڰ� ������ �������� �� */
#define ER_SELFTEST_HIGHT						-9106
/** @brief LEA-128 �ڰ� ������ �������� �� */
#define ER_SELFTEST_LEA128						-9107
/** @brief LEA-192 �ڰ� ������ �������� �� */
#define ER_SELFTEST_LEA192						-9108
/** @brief LEA-256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_LEA256						-9109
/** @brief SHA224 �ڰ� ������ �������� �� */
#define ER_SELFTEST_SHA224						-9123
/** @brief SHA256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_SHA256						-9124
/** @brief SHA384 �ڰ� ������ �������� �� */
#define ER_SELFTEST_SHA384						-9125
/** @brief SHA512 �ڰ� ������ �������� �� */
#define ER_SELFTEST_SHA512						-9126
/** @brief HMAC-SHA224 �ڰ� ������ �������� �� */
#define ER_SELFTEST_HMAC_SHA224					-9143
/** @brief HMAC-SHA256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_HMAC_SHA256					-9144
/** @brief HMAC-SHA384 �ڰ� ������ �������� �� */
#define ER_SELFTEST_HMAC_SHA384					-9145
/** @brief HMAC-SHA512 �ڰ� ������ �������� �� */
#define ER_SELFTEST_HMAC_SHA512					-9146
/** @brief CMAC-ARIA128 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CMAC_ARIA128				-9147
/** @brief CMAC-ARIA192 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CMAC_ARIA192				-9148
/** @brief CMAC-ARIA256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CMAC_ARIA256				-9149
/** @brief CMAC-SEED �ڰ� ������ �������� �� */
#define ER_SELFTEST_CMAC_SEED					-9150
/** @brief GCM-ARIA128 �ڰ� ������ �������� �� */
#define ER_SELFTEST_GMAC_ARIA128				-9151
/** @brief GCM-ARIA192 �ڰ� ������ �������� �� */
#define ER_SELFTEST_GMAC_ARIA192				-9152
/** @brief GCM-ARIA256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_GMAC_ARIA256				-9153
/** @brief GCM-SEED �ڰ� ������ �������� �� */
#define ER_SELFTEST_GMAC_SEED					-9154
/** @brief CCM-ARIA128 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CCM_ARIA128					-9155
/** @brief CCM-ARIA192 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CCM_ARIA192					-9156
/** @brief CCM-ARIA256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CCM_ARIA256					-9157
/** @brief CCM-SEED �ڰ� ������ �������� �� */
#define ER_SELFTEST_CCM_SEED					-9158
/** @brief CMAC-HIGHT �ڰ� ������ �������� �� */
#define ER_SELFTEST_CMAC_HIGHT					-9167
/** @brief CMAC-LEA128 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CMAC_LEA128					-9168
/** @brief CMAC-LEA192 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CMAC_LEA192					-9169
/** @brief CMAC-LEA256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CMAC_LEA256					-9170
/** @brief CCM-LEA128 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CCM_LEA128					-9171
/** @brief CCM-LEA192 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CCM_LEA192					-9172
/** @brief CCM-LEA256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_CCM_LEA256					-9173
/** @brief GCM-LEA128 �ڰ� ������ �������� �� */
#define ER_SELFTEST_GMAC_LEA128					-9174
/** @brief GCM-LEA192 �ڰ� ������ �������� �� */
#define ER_SELFTEST_GMAC_LEA192					-9175
/** @brief GCM-LEA256 �ڰ� ������ �������� �� */
#define ER_SELFTEST_GMAC_LEA256					-9176
/** @brief HASHDRBG �ڰ� ������ �������� �� */
#define ER_SELFTEST_HASHDRBG					-9177
/** @brief HMACDRBG �ڰ� ������ �������� �� */
#define ER_SELFTEST_HMACDRBG					-9178
/** @brief CTRDRBG �ڰ� ������ �������� �� */
#define ER_SELFTEST_CTRDRBG						-9179
/** @brief RSAES �ڰ� ������ �������� �� */
#define ER_SELFTEST_RSAES_OAEP					-9182
/** @brief KCDSA �ڰ� ������ �������� �� */
#define ER_SELFTEST_KCDSA						-9201
/** @brief RSA-PSS �ڰ� ������ �������� �� */
#define ER_SELFTEST_RSASSA_PSS					-9204
/** @brief ECDSA �ڰ� ������ �������� �� */
#define ER_SELFTEST_ECDSA						-9205
/** @brief ECKCDSA �ڰ� ������ �������� �� */
#define ER_SELFTEST_ECKCDSA						-9206
/** @brief DH �ڰ� ������ �������� �� */
#define ER_SELFTEST_DH							-9207
/** @brief ECDH �ڰ� ������ �������� �� */
#define ER_SELFTEST_ECDH						-9208

/* conflict */
/** @brief RSA v2.0�� ���� ���� �ùٸ��� ���� �� */
#define ER_RSA20_VP1_SIG_OUT_OF_RANGE			-1090
/** @brief RSA v2.0�� �޽����� �� �� */
#define ER_RSA20_MESSAGE_TOO_LONG				-1091
/** @brief RSA v2.0�� ��ȣ�� ���̰� �ùٸ��� ���� �� */
#define ER_RSA20_WRONG_CIPHER_LEN				-1092

/** @brief RSA�� ���� ���� �ùٸ��� ���� �� */
#define ER_RSA_VP1_SIG_OUT_OF_RANGE				-1090
/** @brief RSA�� �޽����� �� �� */
#define ER_RSA_MESSAGE_TOO_LONG					-1091
/** @brief RSA�� ��ȣ�� ���̰� �ùٸ��� ���� �� */
#define ER_RSA_WRONG_CIPHER_LEN					-1092
/** @brief RSA�� ���ڵ� ������ �߸��Ǿ��� �� (FIPS 186-3 �������� ���� ����� ���� �ʴ� ���� ���� �ڵ�) */
#define ER_RSA_ENCODING_ERROR					-1093
/** @brief RSA�� ���� ���� ����� ���� ���� ����� ����ġ�� �� */
#define ER_RSA_INCONSISTENT						-1094
/** @brief RSA�� ��ȣȭ ������ �߸��Ǿ��� �� */
#define ER_RSA_DECRYPT_ERROR					-1095  
/** @brief RSA�� ���ڵ� �޽��� ���̰� ª�� �� */
#define ER_RSA_MODULUS_TOO_SHORT				-1096

/** @brief ��� ��ȣ���� ��ȿ���� ���� �е� ������ �� */
#define ER_BCIPHER_INVALID_PAD					-1001
/** @brief ��� ��ȣ���� ��ȿ���� ���� � ����� ��  */
#define ER_BCIPHER_BAD_OP_MODE					-1002
/** @brief ��� ��ȣ���� ��ȿ���� ���� �±� ������ �� */
#define ER_BCIPHER_INVALID_TAG_LENGTH			-1003
/** @brief ��� ��ȣ���� ��ȿ���� ���� ������ ��  */
#define ER_BCIPHER_INVALID_NONCE_LENGTH			-1004
/** @brief ��� ��ȣ���� ��ȿ���� ���Ű ������ ��  */
#define ER_BCIPHER_INVALID_KEY_LENGTH			-1005

/* conflict */
/** @brief DSA�� ���� ���� �ùٸ��� ���� �� */
#define ER_DSA_VP_SIG_OUT_OF_RANGE				-2001
/** @brief ������ ���� ���� �������� ������ ���� �� */
#define ER_MINT_NOT_INVERTIBLE					-2011
/** @brief KCDSA�� ���� ���� �ùٸ��� ���� �� */
#define ER_KCDSA_VP_SIG_OUT_OF_RANGE			-2040
/** @brief KCDSA�� �����߻��⿡�� ����ϴ� SEED�� SEEDŰ�� ���� �� */
#define ER_KCDSARNGHAS160_SEED_EQUAL_TO_SEEDKEY	-2051

/** @brief �����߻��� API�� ��ȿ���� ���� �ؽ��Լ��� �Է��Ͽ��� �� */
#define ER_INVALID_HASH_ALG						-5282
/** @brief �����߻��� API�� ��ȿ���� ���� ��Ͼ�ȣ�� �Է��Ͽ��� �� */
#define ER_INVALID_BLOCKCIPHER_ALG				-5283
/** @brief �����߻��� API�� �����߻��� state�� null�� �Է��Ͽ��� �� */
#define ER_NULL_STATE							-5285
/** @brief �����߻��⿡ 16384��Ʈ���� �� ���� �߻��� �䱸�Ͽ��� �� */
#define ER_REQUEST_TOO_LONG_RANDOM				-5289
/** @brief �����߻��� �ν��Ͻ�ȭ(�ʱ�ȭ)���� �ʾ��� �� */
#define ER_NOT_INSTANTIATION_DRBG				-5290

/** @brief �Լ��� ����� ����� �Ķ������ �޸� ���� ũ�Ⱑ ���� �� */
#define ER_OUT_BUFFER_SIZE_IS_SMALL				-3000

/** @} */

/** @} */

#endif /* _CIS_ERROR_H_ */
