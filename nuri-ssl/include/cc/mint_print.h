#ifndef _MINT_PRINT_H_
#define _MINT_PRINT_H_

#include "mint_common.h"

/** @ingroup MINT
    @file mint_print.h
    @brief MINT의 값을 stdout 출력하는 함수들

    MINT의 값을 stdout 출력하는 함수들이다.
    stdout으로 MINT 값을 출력할 필요가 없을 경우에는 사용할 필요가 없다.
*/

#ifdef __cplusplus
extern "C" {
#endif

/**
    @ingroup MINT
    @brief a의 값을 16 진수로 프린트한다.
    @param[in] str const char* 타입으로 a 값을 트린트하기 전에 트린트할 문자열이다. null-terminated 스트링이어야 한다.
    @param[in] a const MINT* 타입으로 프린트할 값을 가진 입력이다.
    @sa MINT, MINT_Print_Functions

    표준 출력(stdout)에 str을 출력하고 a의 값을 16 진수값으로 프린트한다.
    a 값의 msb가 먼저 프린트되고 lsb가 마지막에 트린트된다.
*/
LIBSPEC
void MINT_PrintInHexString(const char *str, const MINT *a);

/**
    @ingroup MINT
    @brief a의 값을 BWT_BIT_LEN 비트씩 16 진수로 프린트한다.
    @param[in] str const char* 타입으로 a 값을 트린트하기 전에 트린트할 문자열이다. null-terminated 스트링이어야 한다.
    @param[in] a const MINT* 타입으로 프린트할 값을 가진 입력이다.
    @sa MINT, MINT_Print_Functions

    표준 출력(stdout)에 str을 출력하고 a의 값을 BWT_BIT_LEN 비트씩 16 진수값으로 프린트한다.
    BWT_BIT_LEN 비트 마다 빈칸이 하나씩 출력된다.
    a 값의 msb가 먼저 프린트되고 lsb가 마지막에 트린트된다.
*/
LIBSPEC
void MINT_PrintInHexStringBWT(const char *str, const MINT *a);

/**
    @ingroup MINT
    @brief a의 값을 C 구조체 형식으로 트린트한다.
    @param[in] str const char* 타입으로 a 값을 트린트하기 전에 트린트할 문자열이다. null-terminated 스트링이어야 한다.
    @param[in] a const MINT* 타입으로 프린트할 값을 가진 입력이다.
    @sa MINT, MINT_Print_Functions

    표준 출력(stdout)에 str을 출력하고 a의 구조체 값을 프린트한다.
    즉,
    str{{a->len}, {a->data[0], a->data[1], ... , a->data[a->len-1]}}
    으로 출력된다.
*/
LIBSPEC
void MINT_PrintInStructForm(const char *str, const MINT *a);
  
#ifdef __cplusplus
}
#endif

#endif /* _MINT_PRINT_H_ */
