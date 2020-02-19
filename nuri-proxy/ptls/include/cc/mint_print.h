#ifndef _MINT_PRINT_H_
#define _MINT_PRINT_H_

#include "mint_common.h"

/** @ingroup MINT
    @file mint_print.h
    @brief MINT�� ���� stdout ����ϴ� �Լ���

    MINT�� ���� stdout ����ϴ� �Լ����̴�.
    stdout���� MINT ���� ����� �ʿ䰡 ���� ��쿡�� ����� �ʿ䰡 ����.
*/

#ifdef __cplusplus
extern "C" {
#endif

/**
    @ingroup MINT
    @brief a�� ���� 16 ������ ����Ʈ�Ѵ�.
    @param[in] str const char* Ÿ������ a ���� Ʈ��Ʈ�ϱ� ���� Ʈ��Ʈ�� ���ڿ��̴�. null-terminated ��Ʈ���̾�� �Ѵ�.
    @param[in] a const MINT* Ÿ������ ����Ʈ�� ���� ���� �Է��̴�.
    @sa MINT, MINT_Print_Functions

    ǥ�� ���(stdout)�� str�� ����ϰ� a�� ���� 16 ���������� ����Ʈ�Ѵ�.
    a ���� msb�� ���� ����Ʈ�ǰ� lsb�� �������� Ʈ��Ʈ�ȴ�.
*/
LIBSPEC
void MINT_PrintInHexString(const char *str, const MINT *a);

/**
    @ingroup MINT
    @brief a�� ���� BWT_BIT_LEN ��Ʈ�� 16 ������ ����Ʈ�Ѵ�.
    @param[in] str const char* Ÿ������ a ���� Ʈ��Ʈ�ϱ� ���� Ʈ��Ʈ�� ���ڿ��̴�. null-terminated ��Ʈ���̾�� �Ѵ�.
    @param[in] a const MINT* Ÿ������ ����Ʈ�� ���� ���� �Է��̴�.
    @sa MINT, MINT_Print_Functions

    ǥ�� ���(stdout)�� str�� ����ϰ� a�� ���� BWT_BIT_LEN ��Ʈ�� 16 ���������� ����Ʈ�Ѵ�.
    BWT_BIT_LEN ��Ʈ ���� ��ĭ�� �ϳ��� ��µȴ�.
    a ���� msb�� ���� ����Ʈ�ǰ� lsb�� �������� Ʈ��Ʈ�ȴ�.
*/
LIBSPEC
void MINT_PrintInHexStringBWT(const char *str, const MINT *a);

/**
    @ingroup MINT
    @brief a�� ���� C ����ü �������� Ʈ��Ʈ�Ѵ�.
    @param[in] str const char* Ÿ������ a ���� Ʈ��Ʈ�ϱ� ���� Ʈ��Ʈ�� ���ڿ��̴�. null-terminated ��Ʈ���̾�� �Ѵ�.
    @param[in] a const MINT* Ÿ������ ����Ʈ�� ���� ���� �Է��̴�.
    @sa MINT, MINT_Print_Functions

    ǥ�� ���(stdout)�� str�� ����ϰ� a�� ����ü ���� ����Ʈ�Ѵ�.
    ��,
    str{{a->len}, {a->data[0], a->data[1], ... , a->data[a->len-1]}}
    ���� ��µȴ�.
*/
LIBSPEC
void MINT_PrintInStructForm(const char *str, const MINT *a);
  
#ifdef __cplusplus
}
#endif

#endif /* _MINT_PRINT_H_ */
