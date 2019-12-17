#ifndef _KCDSA_UDK_H_
#define _KCDSA_UDK_H_

#include <stdio.h>
#include "kcdsa.h"

#ifdef EXPORT_CE
#include "ce_dll.h"
#else
#define LIBSPEC_CE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @brief KCDSA 키 생성 함수
    @param kcdsaPriKey [out] 생성될 private key가 저장될 KCDSAPriKey 구조체
    @param kcdsaPubKey [out] 생성될 public key가 저장될 KCDSAPubKey 구조체
    @param kcdsaParam [in] KCDSAParam 구조체
		@param inputVal   [in] user input value
		@param inputLen   [in] user input value length
    @sa KCDSA_GenParam KCDSA_CheckParam KCDSA_CheckKey

    KCDSAParam 구조체의 p, q, g 값과 user input value를 바탕으로 KCDSA 키쌍을 생성한다.
*/
LIBSPEC_CE
ERT KCDSA_GenKey_UDK(
    void *kcdsaPriKey, void *kcdsaPubKey, const void *kcdsaParam, BYTE *inputVal, BWT inputLen);

#ifdef __cplusplus
}
#endif

#endif
