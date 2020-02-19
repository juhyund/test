#ifndef _HASH_OPERATION_H_
#define _HASH_OPERATION_H_

/** @defgroup HASH Hash Function
 * @ingroup CC
 * @brief Cryptographic Hash Functions
 */

/** @defgroup HASH_ALG Algorithm Descriptors
 * @ingroup HASH
 * @brief HASH Algorithm Descriptors
 */

/** @file hash_op.h
 * @ingroup HASH
 */
    
#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup HASH
 * @{ */

#define HASH_MAX_DIGEST_BIT_SIZE   512
#define HASH_MAX_DIGEST_SIZE        64
#define HASH_MAX_DIGEST_BT32_SIZE   16
#define HASH_MAX_DIGEST_BT64_SIZE   16
#define HASH_MAX_BLOCK_BIT_SIZE   1024
#define HASH_MAX_BLOCK_SIZE        128
#define HASH_MAX_BLOCK_BT32_SIZE    32
#define HASH_MAX_BLOCK_BT64_SIZE    32
#define HASH_MAX_INPUT_BT32_SIZE     4
#define HASH_MAX_INPUT_BT64_SIZE     4

/* for backward compatibility */
#define HASH_Update_PCIS PCIS_HASH_Update
#define HASH_Update_clone PCIS_HASH_Update
#define HASH_Initialize PCIS_HASH_Initialize
#define HASH_Finalize PCIS_HASH_Finalize
#define HASH_Update PCIS_HASH_Update

/**
 * @brief �˰��� �����ڸ� �ǹ��ϴ� ����ü
 *
 * �ؽ� �Լ� �˰����� �����ϴ� ���� ������ ��Ÿ���� ����ü�̸�, HASH
 * ��⿡�� �����Ǵ� API���� ���� �˰���� �����ϱ� ���� ������(descriptor)��
 * ���ȴ�.
 *
 * @sa PCIS_HASH_Initialize
 */
typedef struct {
  BWT    digestLen; /**< ��� ���� ���� */
  void (*initFunc)(); /**< �ʱ�ȭ �Լ� ������ */
  void (*compressFunc)(); /**< ��� ó�� �Լ� ������ */
  void (*padFunc)(); /**< �е� �Լ� ������ */
  void (*dumpFunc)(); /**< 32��Ʈ digest�� 8��Ʈ�� ��ȯ�ϴ� �Լ� ������ */
} HashAlgorithm;

/**
    @brief Hash �˰����� ��ϱ� ���� ������ ���� ����ü

    32bit Hash �˰����� ��ϴ� �� �ʿ��� �پ��� �������� ��� �ִ�.
    ����ü ������� ��� ����������  �����̹Ƿ�, ������� 
    ���� �аų� �������� �ʾƾ� �Ѵ�.

    @sa PCIS_HASH_Initialize, PCIS_HASH_Update, PCIS_HASH_Finalize
*/
typedef struct {
  AlgDesc alg; /**< �˰��� ������ */
  BT32 digest[HASH_MAX_DIGEST_BT32_SIZE]; /**< hash���� �����ϴ� ���� */
  BT32 input [HASH_MAX_BLOCK_BT32_SIZE]; /**< �ϳ��� �޽��� ���� �����ϴ� ���� */
  BT32 count [HASH_MAX_INPUT_BT32_SIZE]; /**< ó���� �޽����� ���̸� �����ϴ� ���� */
} Hash32Context; 

/**
    @brief Hash �˰����� ��ϱ� ���� ������ ���� ����ü

    64bit Hash �˰����� ��ϴ� �� �ʿ��� �پ��� �������� ��� �ִ�.
    ����ü ������� ��� ����������  �����̹Ƿ�, ������� 
    ���� �аų� �������� �ʾƾ� �Ѵ�.

    @sa PCIS_HASH_Initialize, PCIS_HASH_Update, PCIS_HASH_Finalize
*/
typedef struct {
  AlgDesc alg; /**< �˰��� ������ */
  BT64 digest[HASH_MAX_DIGEST_BT64_SIZE]; /**< hash���� �����ϴ� ���� */
  BT64 input [HASH_MAX_BLOCK_BT64_SIZE]; /**< �ϳ��� �޽��� ���� �����ϴ� ���� */
  BT64 count [HASH_MAX_INPUT_BT64_SIZE]; /**< ó���� �޽����� ���̸� �����ϴ� ���� */
} Hash64Context;

/**
    @brief Hash �˰����� ��ϱ� ���� ������ ���� ����ü

	32bit Hash �˰���� 64bit Hash �˰����� ��ϴ� �� �ʿ��� �پ���
	�������� ��� �ִ�. ����ü ������� ��� ����������  �����̹Ƿ�, �������
	���� �аų� �������� �ʾƾ� �Ѵ�.

    @sa PCIS_HASH_Initialize, PCIS_HASH_Update, PCIS_HASH_Finalize
*/
typedef struct {
  AlgDesc alg; /**< �˰��� ������ */
  Hash32Context hash32; /**< 32bit ���� �ؽ� context */
  Hash64Context hash64; /**< 64bit ���� �ؽ� context */
} HashContext;
/**
    @brief HashContext�� �ʱ�ȭ�Ѵ�.

    HashContext�� �ʱ�ȭ�Ѵ�. Hash �˰����� ����ϱ� ���ؼ��� HashContext
    ����ü�� �ν��Ͻ��� �ʿ��ϴ�. \e alg�� ����ϰ��� �ϴ� �˰�����
    descriptor ����ü�� �����Ͱ��̴�. ���� ��� MD5 ��� \e MD5��� descritor��
    global�� ����Ǿ� �ִ�. ������ �� ���̴�.
   
    \code
    BYTE md[20];
    BWT dlen;
    HashContext ctx;
    PCIS_HASH_Initialize(&ctx, MD5);
    PCIS_HASH_Update(&ctx, "abcdefg", strlen("abcdefg");
    dlen = sizeof(md);
    PCIS_HASH_Finalize(md, &dlen, &ctx);
    \endcode
    
    \b MD5 �ܿ��� \b SHA1, \b RIPEMD160, \b HAS160 �˰����� ����� �� �ִ�.
    ��� �˰����� �̸� ��ü�� descriptor�� �ȴ�. ������ SHA1�� HAS160����
    context�� �ʱ�ȭ�ϴ� �����̴�.
   
    \code
    HashContext ctx1, ctx2;
    PCIS_HASH_Initialize(&ctx1, SHA1);
    PCIS_HASH_Initialize(&ctx2, HAS160);
    \endcode
    
    ���� ������ \e ctx1�� SHA1 �˰����� context�̸�, \e ctx2�� HAS160
    �˰����� context�̴�.

    64��Ʈ ���� ��� �ؽ� �˰����� SHA-384, SHA-512�� ��� �����ϴ�.
    
    @retval SUCCESS on success
    @retval FAIL on fail
    @retval ER_NOT_APPROVED_ALGORITHM ������� � ���¿��� �������� ��ȣ�˰��� ȣ�� ��
    @sa PCIS_HASH_Update, PCIS_HASH_Finalize
*/
LIBSPEC
ERT PCIS_HASH_Initialize(
		HashContext *ctx, /**< [out] �ʱ�ȭ�ϰ��� �ϴ� HashContext�� �����Ͱ� */
		AlgDesc hashAlg /**< [in] ����� hash �˰����� descriptor */
		);

/**
    @brief �Է� ���� �޽����κ��� hash���� ������Ʈ�Ѵ�.

	�� ���� 1GB��ŭ�� �޽����� �Է��� �� �ִ�.
    \e msg�� ����Ű�� �ִ� ���ۿ��� �Է� �޽������� �о�ͼ� ���� HashContext��
    hash���� ������Ʈ�Ѵ�. �������� hash���� ��� ���ؼ��� �ݵ��
    \e PCIS_HASH_Finalize�Լ��� ���ؼ� ��µ� ���۰��� ����Ͽ����Ѵ�.

    ���� �޽����� ������ ������ ������Ʈ�ϴ� ���� �����ϴ�. ���� ���,

    \code
    HashContext ctx1, ctx2;
    PCIS_HASH_Initialize(&ctx1, MD5);
    PCIS_HASH_Initialize(&ctx2, MD5);
    
    PCIS_HASH_Update(&ctx1, "abcdefg", strlen("abcdefg");
    
    PCIS_HASH_Update(&ctx2, "ab", strlen("ab");
    PCIS_HASH_Update(&ctx2, "c", strlen("c");
    PCIS_HASH_Update(&ctx2, "defg", strlen("defg");
    \endcode

    ���� \e ctx1, \e ctx2 ������Ʈ ����� �����ϴ�.

    64��Ʈ ���� ��� �ؽ� �˰����� SHA-384, SHA-512�� ��� �����ϴ�.

    2007.07.04
    Netscape �� ������ embed�Ǵ� ��쿡 openssl ���̺귯�� �ɹ��� �浹�ϴ� ���� ���ϱ�
    ���Ͽ� PCIS_HASH_Update �� �̸� ����

    @sa PCIS_HASH_Initialize, PCIS_HASH_Finalize
*/
LIBSPEC
void PCIS_HASH_Update(
		HashContext *ctx, /**< [in,out] update�� HashContext�� �����Ͱ� */
		const BYTE *msg, /**< [in] �Է��� �޽��� ������ ����Ʈ �����Ͱ� */
		BWT msgLen /**< [in] �Է��� �޽��� ������ ����Ʈ ���� ���� */
		);

/**
    @brief �������� hash���� ����� ����, ����� ���ۿ� �����Ѵ�. 
    �Լ� ���� ��, mdLen = 0���� ���
    �Լ� ���� ��, mdLen = digestLen���� ���

    �������� hash���� \e md�� ����Ű�� �ִ� ���ۿ� �����Ѵ�.
    �� �Լ����� padding�� �Ͽ� ���� hash���� ����ϹǷ� �� �Լ��� ������
    ���� \e md���۰����� ��ȿ�� hash���� �ȴ�.

    ���������� HashContext�� ������ ��, ó���� �ϹǷ�, �ԷµǴ� HashContext
    �� ������ ����. ����, �� �� \e PCIS_HASH_Finalize�� ������ HashContext��
    ����Ͽ� \e PCIS_HASH_Update�� ������ �� �ִ�. ���� ���,
   
    \code
    BYTE md1[16], md2[16];
    BWT dlen;
    HashContext ctx;
    PCIS_HASH_Initialize(&ctx, MD5);
    
    PCIS_HASH_Update(&ctx, "abcdefg", strlen("abcdefg");
    PCIS_HASH_Update(&ctx, "hi", strlen("hi");
    dlen = sizeof(md1);
    PCIS_HASH_Finalize(md1, &dlen, &ctx);

    PCIS_HASH_Update(&ctx, "jklmnopq", strlen("jklmnopq");
    dlen = sizeof(md2);
    PCIS_HASH_Finalize(md2, &dlen, &ctx);
    \endcode

    ���� ������� md1�� md2��� ��ȿ�� hash���̴�.
    ��, \e md1�� "abcdefghi"�� hash���̰�,
    \e md2�� "abcdefghijklmnopq"�� hash���̴�.

    64��Ʈ ���� ��� �ؽ� �˰����� SHA-384, SHA-512�� ��� �����ϴ�.

    @sa PCIS_HASH_Initialize, PCIS_HASH_Update
*/
LIBSPEC
void PCIS_HASH_Finalize(
		BYTE *md, /**< [out] �������� ����� ������ ������ ������ */
		BWT *mdLen, /**< [in, out] IN: md�� �޸� ���� ũ��, OUT: ��°��� ����Ʈ ���� ���� */
		const HashContext *ctx /**< [in] HashContext�� �����Ͱ� */
		);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _HASH_OPERATION_H_ */
