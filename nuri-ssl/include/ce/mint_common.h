/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _MINT_COMMON_H_
#define _MINT_COMMON_H_

/** @defgroup MATH Mathematical Foundation
 * @ingroup CC
 * Mathematical Foundation
 */

/** @defgroup MINT Multi-Precision Integer
 * @ingroup MATH
 * @brief Multi-Precision Integer Arithmetic
 *
 * MINT�� ������ ���� ���� ���μ�, ������ ǥ���ϴ� �⺻ Ÿ���� MINT��
 * �����ϰ� �׿� ���õ� Set/Get ���� �⺻ �Լ���� �����Լ����� ���ǵǾ� �ִ�.
 */

/** @ingroup MINT
    @file mint.h
    @brief MINT Ÿ�԰� ���� �Լ� ����

    ū���� ����� ���� ������ ���� ���� �Լ�
    MINT(Multi Precision Integer) Ÿ��
    MINT ���� �Լ�
*/

#include <memory.h>
#include "cc_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
    @ingroup MINT
    @brief MINT�� �̿��Ͽ� �ٷ� �� �ִ� ū���� ��Ʈ ũ��
    @sa MINT_MAX_LEN, MINT

    MINT�� �̿��Ͽ� �ٷ� �� �ִ� ū���� ��Ʈ ũ���̴�.

    ��, 1024 ��Ʈ�� RSA�� DLP�� �ٷ� ��� 1024 �̻�,
    2048 ��Ʈ�� �ٷ� ��� 2048 �̻�,
    4096 ��Ʈ�� �ٸ� ��� 4096 �̻��� �Ǿ�� �Ѵ�.
*/
#define MINT_MANIPULATED_DATA_BIT_LEN 2048

/**
    @ingroup MINT
    @brief MINT�� data ����� �ִ� ũ��
    @sa MINT_MANIPULATED_DATA_BIT_LEN, BWT_BIT_LEN, MINT

    MINT�� data �������� �ִ� ũ�⸦ �����Ѵ�.
    ������ BWT Ÿ���� ��� ũ���̴�.
    �ٷ�� ū �� ũ���� 2���� ũ�⸦ �ٷ� �� �ֵ��� ���� ���ؾ� �Ѵ�.

    ��, BWT Ÿ���� 32 ��Ʈ Ÿ���̶�� ������ ��, �ִ� 1024 ��Ʈ�� ������ �����ҷ��� 2*1024/32�� ũ�⸦ �����ش�.
*/
#define MINT_MAX_LEN  ((MINT_MANIPULATED_DATA_BIT_LEN/BWT_BIT_LEN)*2+2)


/** 
    @ingroup MINT
    @brief MINT Ÿ���� ũ�� 

    MINTŸ���� ����Ʈ ���� ũ���̴�.
*/
#define MINT_SIZE ((MINT_MAX_LEN+1)*BWT_BYTE_LEN)

/**
    @ingroup MINT
    @brief Window �˰����� �̿��� ��� ���꿡�� ����ϴ� Windows�� ��Ʈ ũ��
    @sa MINT_ExpWin()

    Window �˰����� �̿��� ��� ���꿡�� ����ϴ� Windows�� ��Ʈ ũ���̴�.
*/
#define MINT_WINDOW_BIT_LEN_FOR_EXP 4

/**
    @ingroup MINT
    @brief MINT_WINDOW_BIT_LEN_FOR_EXP�� ������ ǥ��
    @sa MINT_WINDOW_BIT_LEN_FOR_EXP, MINT_ExpWin()

    ���α׷��� MINT_WINDOW_BIT_LEN_FOR_EXP�� �Ź� ���⿡�� �ʹ� ��⿡ MINT_WIN_LEN���� alias �� ���̴�.
*/
#define MINT_WIN_LEN  (MINT_WINDOW_BIT_LEN_FOR_EXP)
    
/** @ingroup MINT
 * @brief Multi-precision (large) integer
 * @note Since this struct uses fixed size array as a data store,
 * it is easy to increase memory footage. <strong>So, be careful.</strong>
 * @see BWT, MINT_MAX_LEN
*/
typedef struct {
  BWT len;                /**< @brief number of used elements in data array */
  BWT data[MINT_MAX_LEN]; /**< @brief actual data array contains
							(msb) data[len-1]....data[0] (lsb). */
} MINT;


/** @ingroup MINT */
typedef struct {
  BWT ri;
  MINT RR;
  MINT N;
  MINT Ni;
  BWT Ni_0[2];
} MONT;

/** @ingroup MINT
    @brief MINT�� Ȧ�������� �׽�Ʈ
    @sa MINT_IsEven

    MINT�� Ȧ�������� �׽�Ʈ�Ѵ�. �Ǽ��̸� 1��, �ƴϸ� 0�� �����Ѵ�.
    */
#define MINT_IsOdd(a)  (((a)->len > 0) && ((a)->data[0] & 0x01))

/** @ingroup MINT
    @brief MINT�� ¦�������� �׽�Ʈ
    @sa MINT_IsOdd

    MINT�� ¦�������� �׽�Ʈ�Ѵ�. �Ǽ��̸� 1��, �ƴϸ� 0�� �����Ѵ�.
    */
#define MINT_IsEven(a) (((a)->len == 0) || !(((a)->data[0])&0x01))

/** @ingroup MINT
    @brief MINT�� 1������ �׽�Ʈ�Ѵ�.
    @sa MINT_IsZero MINT_IsNonZero

    MINT�� 1������ �׽�Ʈ�Ѵ�. 1�̸� 1��, �ƴϸ� 0�� �����Ѵ�.
    */
#define MINT_IsOne(a)  (((a)->data[0]==0x01) && ((a)->len==1))

/** @ingroup MINT
    @brief MINT�� 0������ �׽�Ʈ�Ѵ�.
    @sa MINT_IsOne MINT_IsNonZero

    MINT�� 0������ �׽�Ʈ�Ѵ�. 0�̸� 1��, �ƴϸ� 0�� �����Ѵ�.
    */
#define MINT_IsZero(a) (!((a)->len))

/** @ingroup MINT
    @brief MINT�� 0�� �ƴ������� �׽�Ʈ�Ѵ�.
    @sa MINT_IsOne MINT_IsZero

    MINT�� 0������ �׽�Ʈ�Ѵ�. 0�� �ƴϸ� 1��, 0�̸� 0�� �����Ѵ�.
    */
#define MINT_IsNonZero(a) ((a)->len)


/**
    @ingroup MINT
    @brief a�� 0���� ����
    @sa MINT, MINT_Set_Functions

    MINT* �� a�� 0���� �����Ѵ�.
    ��, a->len = 0 �� �ȴ�.
*/
#define MINT_Set0(a)    (((a)->len) = 0)

/** @ingroup MINT
 * @brief Allocate new memory for a MINT structure and set to zero.
 * @return [out] NULL if an error occurred
 * @see MINT
 */
LIBSPEC
MINT* MINT_New(void);

/** @ingroup MINT
 * @brief Free memory held by a MINT structure.
 * @param[in] a MINT to be deleted
 * @return nothing even if there was an error
 * @see MINT
 */
LIBSPEC
void MINT_Del(MINT* a);

/**
    @ingroup MINT
    @brief a�� n���� ����
    @param[out] a MINT* Ÿ������ n ���� �����Ǿ� ��µȴ�.
    @param[in] n BWT Ÿ������ a�� ������ �Է��̴�.
    @sa MINT, MINT_Set_Functions

    MINT* �� a�� n���� �����Ѵ�.
    n�� BWT�� ǥ���� �� �ִ� �ִ밪 ���� �۾ƾ� �Ѵ�.
    ��, a->len = 1; a->data[0] = n; �� �ȴ�.
*/
LIBSPEC
void MINT_SetByInteger(MINT *a, BWT n);

/**
    @ingroup MINT
    @brief a�� hexaString�� ������ ����
    @param[out] a MINT* Ÿ������ hexaString�� ���� �����Ǿ� ��µȴ�.
    @param[in] hexaString const char * Ÿ������ a�� ������ 16������ ǥ���� null-terminated ASCII ��Ʈ�� �Է��̴�.
    @retval SUCCESS ���������� ����Ǿ��� ���� ���� ���̴�.
    @retval FAIL hexaString�� �Է��߿� '0'~'9', 'a'~'f', 'A'~'F'�� �ش����� �ʴ�
    ���ڰ� ���ԵǾ� ������ �߻��ϴ� �����̴�.
    @sa MINT, MINT_Set_Functions, MINT_RefreshLength()

    MINT* �� a�� 16������ ǥ���� null-terminated ASCII ��Ʈ���� hexaString���� �����Ѵ�.
    hexaString[0]�� ����� ASCII ���� msb 4 ��Ʈ�� ǥ���ϴ� ���� �ȴ�.
    hexaString[strlen(hexaString)-1]�� ����� ASCII ���� lsb 4 ��Ʈ�� ǥ���ϴ� ���� �ȴ�.

    a->len�� a->data�� ��ȿ���� ũ�Ⱑ �ƴ� hexaString�� �Է�ũ�⿡ ���� �����ȴ�.
    �׷��Ƿ� �� �Լ��ȿ� MINT_RefreshLength()�� ȿ���� ����. 
*/
LIBSPEC
ERT MINT_SetByHexString(MINT *a, const char *hexaString);

/**
    @ingroup MINT
    @brief a�� byteLen ����Ʈ ���� ��ŭ�� byteArray�� �ִ� ������ ����
    @param[out] a MINT* Ÿ������ byte�� ���� �����Ǿ� ��µȴ�.
    @param[in] byteArray const BYTE* Ÿ������ a�� ������ ���̳ʸ� ��Ʈ�� �Է��̴�.
    @param[in] byteLen BWT Ÿ������ byteArray�� ����� ���� ����Ʈ ���� �Է��̴�.
    @sa MINT, MINT_Set_Functions

    MINT* �� a�� byteLen ����Ʈ ���� ��ŭ�� byteArray�� �ִ� ������ �����Ѵ�.
    �� a = (msb) byteArray[0]||byteArray[1]||...||byteArray[byteLen-1] (lsb) ��
    ������ �����ȴ�.
*/
LIBSPEC
void MINT_SetByByteArray(MINT *a, const BYTE *byteArray, BWT byteLen);

/**
    @ingroup MINT
    @brief a�� b�� ������ �����Ѵ�.
    @sa MINT, MINT_Set_Functions, MINT_Copy()

    a�� b�� ������ �����Ѵ�.
    ��, a = b �� �ȴ�.
    MINT_Copy()�� b�� ��� �����͸� a�� �״�� '����'������,
    MINT_SetByMINT()�� ū�� b�� ���� a�� '����'�Ѵ�.
*/
#define MINT_SetByMINT(a, b) { (a)->len = (b)->len; memcpy((a)->data, (b)->data, ((a)->len)*BWT_BYTE_LEN); }

/**
    @ingroup MINT
    @brief a�� 2^n�� ������ �����Ѵ�.
    @param[out] a MINT* Ÿ���� ����̴�.
    @param[in] n BWT Ÿ���� �Է����� 2^n�� ���� n�� ��Ÿ���� �Է��̴�. n�� MINT_MANIPULATED_DATA_BIT_LEN���� ���� ���̾�� �Ѵ�.
    @sa MINT, MINT_Set_Functions

    a�� 2^n�� ������ �����Ѵ�(a = 2^n).
    ��, 1���Ŀ� n���� 0�� ����(1000...00) ������ ���� �����Ѵ�.
    n�� MINT_MANIPULATED_DATA_BIT_LEN���� ���� ���̾�� �Ѵ�.
*/
LIBSPEC
void MINT_SetBy2ExpN(MINT *a, BWT n);

/**
    @ingroup MINT
    @brief a�� ���� 16 ������ ǥ���� ASCII ��Ʈ���� buf�� ����Ѵ�.
    @param[out] buf char* Ÿ������ a�� ���� null-terminated ASCII ��Ʈ���� ��µȴ�.
    @param[in,out] byteLen IN: buf�� �޸� ���� ũ��, OUT: BWT* Ÿ���� buf�� ����� ���̳ʸ��� ����Ʈ ũ�� ����̴�.
    @param[in] a const MINT* Ÿ������ buf�� ����� ���� ���� �Է��̴�.
    @retval FAIL NULL �� �Է� ���� ����
    @retval SUCCESS mint to hex string ��ȯ ����
    @retval ER_OUT_BUFF_ERSIZE_IS_SMALL ��� ������ �޸� ũ�Ⱑ ����� �������� �޸𸮺��� ���� ��
    @sa MINT, MINT_Write_Functions

    a�� 0�� �ƴ� msb�� 4 ��Ʈ�� buf[0]�� ��µǰ�, lsb�� 4 ��Ʈ�� buf[strlen(buf)-1]�� ��µȴ�.

    buf�� a�� ���� 16 ������ ȿ���� null-terminated ASCII ��Ʈ������ ����� �� ���� ��ŭ ����� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
    ��, ((MINT_GetBitLength(a)/4)+1) ����Ʈ �̻��� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
    �Ǵ� ((a->len)*BWT_BYTE_LEN*2)+1 ����Ʈ �̻��� �Ҵ��Ͽ� ����ϰų�,
    a->data�� �ִ� ũ���� ((MINT_MAX_LEN*BWT_BYTE_LEN*2)+1) ����Ʈ �̻��� �Ҵ��Ͽ� ����Ͽ��� �ȴ�.
*/
LIBSPEC
ERT MINT_WriteInHexString_N(char *buf, BWT *bytelen, const MINT *a);

/**
    @ingroup MINT
    @brief a�� ���� 16 ������ ǥ���� ASCII ��Ʈ���� BWT_BIT_LEN ��Ʈ ������ buf�� ����Ѵ�.
    @param[out] buf char* Ÿ������ a�� ���� null-terminated ASCII ��Ʈ���� ��µȴ�.
    @param[in,out] byteLen IN: buf�� �޸� ���� ũ��, OUT: BWT* Ÿ���� buf�� ����� ���̳ʸ��� ����Ʈ ũ�� ����̴�.
    @param[in] a const MINT* Ÿ������ buf�� ����� ���� ���� �Է��̴�.
    @retval FAIL NULL �� �Է� ���� ����
    @retval SUCCESS mint to hex string ��ȯ ����
    @retval ER_OUT_BUFF_ERSIZE_IS_SMALL ��� ������ �޸� ũ�Ⱑ ����� �������� �޸𸮺��� ���� ��
    @sa MINT, MINT_Write_Functions

    a�� msb�� 4 ��Ʈ�� buf[0]�� ��µǰ�, lsb�� 4 ��Ʈ�� buf[strlen(buf)-1]�� ��µȴ�.
    a�� msb�� 0 ���� �̷���� ��쿡�� �տ� 0�� ��µȴ�.
        
    buf�� a�� ���� 16 ������ BWT_BIT_LEN ��Ʈ ������ null-terminated ASCII ��Ʈ������ ����� �� ���� ��ŭ ����� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
    ��, ((MINT_GetBitLength(a)/4)+(MINT_GetBitLength(a)/BWT_BIT_LEN)+1) ����Ʈ �̻��� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
    �Ǵ� (a->len)*((BWT_BYTE_LEN*2)+1)+1 ����Ʈ �̻��� �Ҵ��Ͽ� ����ϰų�,
    a->data�� �ִ� ũ���� ((MINT_MAX_LEN*((BWT_BYTE_LEN*2)+1))+1) ����Ʈ �̻��� �Ҵ��Ͽ� ����Ͽ��� �ȴ�.
*/
LIBSPEC
ERT MINT_WriteInHexStringBWT_N(char *buf, BWT *bytelen, const MINT *a);

/**
    @ingroup MINT
    @brief a�� ���� ���̳ʸ��� byteArray�� ����ϰ� �� ����Ʈ ���̸� byteLen�� ����Ѵ�.
    @param[out] byteArray a ���� BYTE* Ÿ���� ���̳ʸ��� ����Ǵ� ����̴�.
    @param[in,out] byteLen IN: byteArray�� �޸� ���� ũ��, OUT: BWT* Ÿ���� byteArray�� ����� ���̳ʸ��� ����Ʈ ũ�� ����̴�.
    @param[in] a const MINT* Ÿ������ byteArray�� ����� ���� ���� �Է��̴�.
    @sa MINT, MINT_Write_Functions

    a�� ���� ���̳ʸ��� byteArray�� ����ϰ� �� ����Ʈ ���̸� byteLen�� ����Ѵ�.
    ��, (msb) byteArray[0]||byteArray[1]||...||byteArray[byteLen-1] (lsb) = a �� �ȴ�.

    byteArray�� a�� ���� ��µ� �� ���� ��ŭ ����� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
    ��, (MINT_GetBitLength(a)/8) ����Ʈ �̻��� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
    �Ǵ� a->data�� �ִ� ũ���� (MINT_MAX_LEN*BWT_BYTE_LEN) ����Ʈ�� �Ҵ��Ͽ� ����Ͽ��� �ȴ�.
*/
LIBSPEC
void MINT_WriteInByteArray(BYTE *byteArray, BWT *byteLen, const MINT *a);

/**
    @ingroup MINT
    @brief a�� ���� ���̳ʸ��� byteArray�� ����ϰ� �� ����Ʈ ���̸� byteLen�� ����Ѵ�.
    @param[out] byteArray a ���� BYTE* Ÿ���� ���̳ʸ��� LSB���� nByte��ŭ ����Ǵ� ����̴�.
    @param[in] nByte BWT Ÿ���� byteArray�� ������ a�� ���̳ʸ� ����Ʈ ũ��(LSB����) ����̴�.
    @param[in] a const MINT* Ÿ������ byteArray�� ����� ���� ���� �Է��̴�.
    @sa MINT, MINT_Write_Functions

    a�� ���� LSB���� nByte ��ŭ ���̳ʸ��� byteArray�� ����Ѵ�.
    ��, (msb) byteArray[0]||byteArray[1]||...||byteArray[nByte-1] (lsb) = a mod ((2^8)^nByte) �� �ȴ�.

    a�� ���� nByte�̻��� ����� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
    �Ǵ� a->data�� �ִ� ũ���� (MINT_MAX_LEN*BWT_BYTE_LEN) ����Ʈ�� �Ҵ��Ͽ� ����Ͽ��� �ȴ�.
*/
LIBSPEC
void MINT_WriteLSNByteInByteArray(BYTE *byteArray, BWT nByte, const MINT *a);

/** @ingroup MINT
    @brief RSA �� integer�� octet string���� ��ȯ�ϴ� �Լ�
    @retval FAIL NULL �� �Է� ���� ����
    @retval SUCCESS Integer to Octet string ��ȯ ����
    @retval ER_OUT_BUFF_ERSIZE_IS_SMALL ��� ������ �޸� ũ�Ⱑ ����� �������� �޸𸮺��� ���� ��
    @sa MINT_WriteInByteArray

    PKCS#1 ver 2.0(RFC2437)�� ����� integer�� octet string����
    ��ȯ�ϴ� �Լ��̴�.  �������� MINT_WriteInByteArray() �Լ���
    ����Ͽ�����, �� �Լ������� ���� byte���� ���� 0�� ��� �̸� �ǹ̾���
    ������ �Ǵ��ϰ� �����ع����� ������ �׻� ���̰� modulus ���̿�
    ���ƾ߸� �ϴ� RSA ���� �������� ���� ������
    �����״�.  �� �Լ��� MINT_WriteInByteArray()�� ���� ���� ������ �ϳ�
    PKCS#1���� ������ ��� �Է��� ���̸� ���� ��ȯ���� �ʰ� �״�� ��������
    Ư���� ������.
    */
LIBSPEC
ERT MINT_I2OSP(
		BYTE *byteArray, /**< [out] ��ȯ�� octet string */
		BWT *byteLen, /**< [in,out] IN: byteArray�� �޸� ���� ũ��, OUT: ��ȯ�� octet string�� ���� */
		const MINT *a /**< [in] ��ȯ�Ϸ��� integer */
		);

/**
    @ingroup MINT
    @brief a�� ���� C ����ü �������� str�� ����Ѵ�.
    @param[out] buf char* Ÿ������ a ���� ����ü �������� ����ϴ� null-terminated ��Ʈ�� ����̴�.
    @param[in,out] byteLen IN: buf�� �޸� ���� ũ��, OUT: BWT* Ÿ���� buf�� ����� ���̳ʸ��� ����Ʈ ũ�� ����̴�.
    @param[in] a const MINT* Ÿ������ str�� ����� ���� ���� �Է��̴�.
    @retval FAIL NULL �� �Է� ���� ����
    @retval SUCCESS mint to hex string ��ȯ ����
    @retval ER_OUT_BUFF_ERSIZE_IS_SMALL ��� ������ �޸� ũ�Ⱑ ����� �������� �޸𸮺��� ���� ��
    @sa MINT, MINT_Write_Functions

    str�� 
    "{{a->len}, {a->data[0], a->data[1], ... , a->data[a->len-1]}}"
    ���� ��µȴ�. (null-terminated string)
    buf�� (11+((a->len)*((BWT_BYTE_LEN*2)+2))) ����Ʈ �̻��� �Ҵ�Ǿ� �־�� �Ѵ�.
    �Ǵ� �ִ� ũ���� (11+(MINT_MAX_LEN*((BWT_BYTE_LEN*2)+2))) ����Ʈ�� �Ҵ��Ͽ� ����Ͽ��� �ȴ�.
*/
LIBSPEC
ERT MINT_WriteInStructForm_N(char *buf, BWT* bytelen, const MINT *a);

/**
    @ingroup MINT
    @brief a�� y�� �����Ѵ�.
    @sa MINT, MINT_Basic_Functions, MINT_SetByMINT()

    a�� MINT struct�� ��� ��� ���� y�� �����Ѵ�.

    MINT_Copy()�� a�� ��� �����͸� y�� �״�� '����'������,
    MINT_SetByMINT()�� ū���� ���� '����'�Ѵ�.
*/  
#define MINT_Copy(y, a) {if ((y) != (a)) memcpy((y), (a), MINT_SIZE);}

/**
    @ingroup MINT
    @brief a�� ���̸� ������ �Ѵ�.
    @sa MINT, MINT_Basic_Functions

    a->len�� ���� a�� ���� ������ ������ �Ѵ�.
    ��, a->data�� msb �������� 0�� ���� ���, 0�� ���� ���� ������ a->len�� ���̸� ���δ�.
*/
#define MINT_RefreshLength(a); { while(((a)->len) && ((a)->data[((a)->len)-1] == 0)) ((a)->len)--; }

/**
    @ingroup MINT
    @brief a�� ��Ʈ ���̸� ����.
    @param[in] a const MINT* Ÿ���� ��Ʈ ���̸� �˰����ϴ� ���� �Է��̴�.
    @return [out] a�� ��Ʈ ���̰� BWT Ÿ������ return �ȴ�.
    @retval FAIL �Լ��� �����Ͽ��� ��
    @sa MINT, MINT_Basic_Functions

    a ���� 2 ������ ǥ���� �� ������ ��Ʈ ���̸� ����Ѵ�.
*/
LIBSPEC
int MINT_GetBitLength(const MINT *a);

/**
    @ingroup MINT
    @brief a�� bit_index ��ġ�� �ִ� ��Ʈ���� �Ǻ��Ѵ�.
    @sa MINT, MINT_Basic_Functions
    
    a->len > (bit_index/BWT_BIT_LEN) ���� �Ѵ�.
    ���� �� ������ �������� ���� ������ ������ ���� ��µȴ�.
    a�� bit_index ��ġ�� �ִ� bit�� 0�̸� 0��, 1�̸� 1�� ��µȴ�.
    bit_index�� 0����(lsb) MINT_GetBitLength(a)-1����(msb) �����ϴ�.
*/
#define MINT_CheckBitByIndex(a, bit_index) ((((a)->data[(bit_index)/BWT_BIT_LEN])>>((bit_index)%BWT_BIT_LEN))&1)

/**
    @ingroup MINT
    @brief a�� b�� ���� ���Ѵ�.
    @param[in] a
    @param[in] b
    @return int Ÿ������ a == b �̸� 0, a > b �̸� 1, a < b �̸� -2 �� return �ȴ�.
    @retval FAIL NULL �� �Է� ���� ����
    @sa MINT, MINT_Basic_Functions

    a�� b�� ���� ���Ѵ�.
    a == b �̸� 0,
    a > b �̸� 1,
    a < b �̸� -2
    �� return �ȴ�.
*/
LIBSPEC
int MINT_Compare(const MINT *a, const MINT *b);

#ifdef __cplusplus
}
#endif

#endif /* _MINT_COMMON_H_ */
