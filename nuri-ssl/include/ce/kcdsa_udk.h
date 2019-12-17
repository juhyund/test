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

/** @brief KCDSA Ű ���� �Լ�
    @param kcdsaPriKey [out] ������ private key�� ����� KCDSAPriKey ����ü
    @param kcdsaPubKey [out] ������ public key�� ����� KCDSAPubKey ����ü
    @param kcdsaParam [in] KCDSAParam ����ü
		@param inputVal   [in] user input value
		@param inputLen   [in] user input value length
    @sa KCDSA_GenParam KCDSA_CheckParam KCDSA_CheckKey

    KCDSAParam ����ü�� p, q, g ���� user input value�� �������� KCDSA Ű���� �����Ѵ�.
*/
LIBSPEC_CE
ERT KCDSA_GenKey_UDK(
    void *kcdsaPriKey, void *kcdsaPubKey, const void *kcdsaParam, BYTE *inputVal, BWT inputLen);

#ifdef __cplusplus
}
#endif

#endif
