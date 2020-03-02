/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_HMAC_H_
#define _PCIS_HMAC_H_

/** @defgroup MAC Message Authentication Code
 * @ingroup CC
 * @brief Message Authentication Code
 */

/** @file hmac.h
    @ingroup MAC
    @brief HMAC�� ��ϱ� ���� �������̽�

    HMAC �˰����� ����ϱ� ���� �������̽��� �����ϰ� �ִ�.
    HMAC�� ���Ǵ� �ؽ� �˰��� �������� ���μ�, initialize��������
    ����ϰ��� �ϴ� �ؽ� �˰����� �����ؾ� �Ѵ�.
*/

#include "cc_define.h"
#include "hash_op.h"

#ifdef __cplusplus
extern "C" {
#endif

/* for symbol name compatibility */
#define HMAC_Initialize PCIS_HMAC_Initialize
#define HMAC_Finalize PCIS_HMAC_Finalize
#define HMAC_Update PCIS_HMAC_Update

#define HMAC_MAX_KEY_LEN 32 /* temporary max */

/** @addtogroup MAC
 * @{ */

/**
    @brief HMAC�� ��ϱ� ���� ������ ���� ����ü

    HMAC ����� ��� ��, �ʿ��� �������� �����ϱ� ����
    ����ü�̴�. initialize, update �������� �̵� ������
    ���ŵȴ�. ��� ���������� �����ϴ� ����ü�̹Ƿ� ����ڰ�
    �ܺο��� ���Ƿ� �����͸� �ٲپ�� �� �ȴ�.

    @sa PCIS_HMAC_Initialize, PCIS_HMAC_Update, PCIS_HMAC_Finalize
*/
typedef struct {
  HashContext ihCtx; /**< hash of inner padding key */
  HashContext ohCtx; /**< hash of outer padding Key */
} HmacContext;

/**
    @brief HmacContext�� �ʱ�ȭ�Ѵ�.

    HmacContext�� �ʱ�ȭ�Ѵ�. HMAC�� ����ϱ� ���ؼ��� 
    HmacContext�� �����ؾ� �ϸ�, �װ��� �ʱ�ȭ�ϴ� �������̽���
    �� �Լ��̴�. ������ �� ���̴�.
    \code
    HmacContext ctx1, ctx2;
    BYTE key1[] = "\x01\x23\x45\x67";
    BYTE key2[] = "\x01\x23\x45\x67\x01\x23\x45\x67";
    
    PCIS_HMAC_Initialize(&ctx1, key1, 4, SHA1);
    PCIS_HMAC_Initialize(&ctx2, key2, 8, HAS160);
    \endcode
    ���� �ڵ�� SHA1 �ؽ� �˰���� HAS160 �ؽ� �˰����� ����ϱ�
    ���Ͽ� �� ���� HmacContext�� �����ϰ� key1�� key2�� �Բ� 
    �ʱ�ȭ�ϴ� ������ ��Ÿ����. SHA1 �˰���� key1�� Ű�� �ϴ� HMAC��
    HAS160 �˰���� key2�� Ű�� �ϴ� HMAC �� ����ϱ� �����̴�.

    �ؽ� �˰��� descriptor�� �� �˰����� �̸��� �����ϴ�. HASH ��⿡
    ���� ������ ����, �� �ڼ��� ������ ���� �� ���� ���̴�. ���� ��������
    SHA1 �� HAS160 �̶�� �˰����� ������ descriptor�� �Ѱ� �ְ� �ִ�.

    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @sa PCIS_HMAC_Update, PCIS_HMAC_Finalize
*/
LIBSPEC
ERT PCIS_HMAC_Initialize(
		HmacContext *hmCtx, /**< [out] �ʱ�ȭ ����� HmacContext�� ������ */
		const BYTE *key, /**< [in] key to HMAC */
		BWT keyLen, /**< [in] key length in bytes */
		AlgDesc hashAlg /**< [in] ����ϰ��� �ϴ� hash �˰��� descriptor */
		);

/**
    @brief HmacContext�� ������Ʈ�Ѵ�.

    \code
    BYTE hmac[20];
    int hmacLen = sizeof(hmac);
    BYTE key[] = "\x01\x23\x45\x67\x01\x23\x45\x67";
    HmacContext ctx;
    PCIS_HMAC_Initialize(&ctx, key, 8, MD5);
    PCIS_HMAC_Update(&ctx, "abcdefg", strlen("abcdefg");
    PCIS_HMAC_Finalize(hmac, &hmacLen, &ctx);
    \endcode

    ���� ���� MD5 �˰���� key�� "abcdefg"��� �޽����� ���� HMAC����
    ����ϴ� �����̴�.
    ���� �������� �޽����� ���ĺ��̹Ƿ�, ���̸� �ٷ� strlen()�� ����Ͽ�����,
    ���̳ʸ� �������� ����, strlen()�� ����� �� ������ �����ؾ� �Ѵ�.
    (���̳ʸ� 0x00���� �������� ���� �ǹ��ϴ� ���� �ƴϹǷ�.)
    
    @sa PCIS_HMAC_Initialize, PCIS_HMAC_Finalize
*/
LIBSPEC
void PCIS_HMAC_Update( HmacContext *hmCtx, /**< [in,out] ������Ʈ ����� �Ǵ� HmacContext�� ������*/
                    const BYTE  *msg, /**< [in] �޽��� �����͸� �����ϰ� �ִ� ������ ������*/
                    BWT          msgLen /**< [in] msg�� ����Ʈ ���� ���� */
                    );

/**
    @brief ���������� HMAC���� ���Ѵ�.

    �Լ��� �����Ͽ��ٸ�, hmacLen = digestLen���� ��µȴ�.

    �� �Լ��� ��������ν�, ���������� HMAC���� ���� ���� �ִ�. �� ����
    PCIS_HASH_Update�� ���� ���� ���� ���� �ڵ带 �����ϱ� �ٶ���.
    hmCtx �Ķ���Ͱ� const�� ���ǵǾ� �������� �˼� �ֵ���, Finailze����������
    HmacContext�� ������ �������� �ʴ´�. ����, Finalize������ ��ģ 
    HmacContext�� ���� ��� Update �� �� �ִ� ���̴�.  ������ �� ���̴�.

    \code
    BYTE hmac1[16], hmac2[16];
    BWT hmacLen;
    BYTE key[] = "\x01\x23\x45\x67\x01\x23\x45\x67";
    HmacContext ctx;

    PCIS_HMAC_Initialize(&ctx, key, 8, MD5);
    PCIS_HMAC_Update(&ctx, "abcdefg", strlen("abcdefg");
    PCIS_HMAC_Update(&ctx, "hi", strlen("hi");
    hmacLen = sizeof(hmac1);
    PCIS_HMAC_Finalize(hmac1, &hmacLen, &ctx);
    PCIS_HMAC_Update(&ctx, "jklmnopq", strlen("jklmnopq");
    hmacLen = sizeof(hmac2);
    PCIS_HMAC_Finalize(hmac2, &hmacLen, &ctx);
    \endcode

    ���� ������� hmac1�� hmac2��� ��ȿ�� hmac���̴�.
    ��, hmac1�� "abcdefghi"�� hmac���̰�,
    \e hmac2�� "abcdefghijklmnopq"�� hmac���̴�.

    @sa PCIS_HMAC_Initialize, PCIS_HMAC_Update
*/
LIBSPEC
void PCIS_HMAC_Finalize( BYTE         *hmac, /**< [out] ���Ǿ��� HMAC ���� ����� ������ ������*/
                    BWT               *hmacLen, /**< [in,out] IN: hmac�� �޸� ���� ũ��, OUT: hmac�� ���̰� ����� ������ ������ */
                    const HmacContext *hmCtx /**< [in] HmacContext �ν��Ͻ��� ������*/
                    );

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_HMAC_H_ */
