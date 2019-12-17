#ifndef _FPE_NSRI_H_
#define _FPE_NSRI_H_

#include "pe_define.h"

#ifdef __cplusplus
extern "C" {
#endif


BT32 EMat0[256], EMat1[256], EMat2[256], EMat3[256], EOMat03[256], EEMat31[256];
BT32 EFMat0[256], EFMat1[256], EFMat2[256], EFMat3[256], EFMat31[256];

BT32 DOMat00[256], DOMat01[256], DOMat02[256], DOMat03[256];
BT32 DOMat10[256], DOMat11[256], DOMat12[256], DOMat13[256];
BT32 DOMat20[256], DOMat21[256], DOMat22[256], DOMat23[256];
BT32 DOMat30[256], DOMat31[256], DOMat32[256], DOMat33[256];

BT32 DEMat00[256], DEMat01[256], DEMat02[256], DEMat03[256];
BT32 DEMat10[256], DEMat11[256], DEMat12[256], DEMat13[256];
BT32 DEMat20[256], DEMat21[256], DEMat22[256], DEMat23[256];
BT32 DEMat30[256], DEMat31[256], DEMat32[256], DEMat33[256];

BT32 DFMat00[256], DFMat01[256], DFMat02[256], DFMat03[256];
BT32 DFMat10[256], DFMat11[256], DFMat12[256], DFMat13[256];
BT32 DFMat20[256], DFMat21[256], DFMat22[256], DFMat23[256];
BT32 DFMat30[256], DFMat31[256], DFMat32[256], DFMat33[256];

BT32 DTOMat00[256], DTOMat01[256], DTOMat02[256], DTOMat03[256];
BT32 DTOMat10[256], DTOMat11[256], DTOMat12[256], DTOMat13[256];
BT32 DTOMat20[256], DTOMat21[256], DTOMat22[256], DTOMat23[256];
BT32 DTOMat30[256], DTOMat31[256], DTOMat32[256], DTOMat33[256];

BT32 DTEMat00[256], DTEMat01[256], DTEMat02[256], DTEMat03[256];
BT32 DTEMat10[256], DTEMat11[256], DTEMat12[256], DTEMat13[256];
BT32 DTEMat20[256], DTEMat21[256], DTEMat22[256], DTEMat23[256];
BT32 DTEMat30[256], DTEMat31[256], DTEMat32[256], DTEMat33[256];

typedef struct {
	BT32 roundKey[228];
	BT32 tweakKey[220];
	BYTE nr;
	BWT radix;
} ScheduleKey;

LIBSPEC_PE
void Enc_KeySchedule(ScheduleKey *key, const BYTE *keyMat, BWT keyLen, BWT nbBitLen);

LIBSPEC_PE
void Enc_TweakSchedule(ScheduleKey *key, const BYTE *keyMat, BWT keyLen, BWT nbBitLen);

LIBSPEC_PE
void Dec_KeySchedule(ScheduleKey *key, const BYTE *keyMat, BWT keyLen, BWT nbBitLen);

LIBSPEC_PE
void Dec_TweakSchedule(ScheduleKey *key, const BYTE *keyMat, BWT keyLen, BWT nbBitLen);

LIBSPEC_PE
void FPENSRI_EncryptSpeed(BYTE *block, const ScheduleKey *key, const BWT nbBitLen);

LIBSPEC_PE
void FPENSRI_DecryptSpeed(BYTE *block, const ScheduleKey *key, const BWT nbBitLen);

LIBSPEC_PE
void FPENSRI_EncryptWord(BYTE *block, const ScheduleKey *key, const BWT nbBitLen);

LIBSPEC_PE
void FPENSRI_DecryptWord(BYTE *block, const ScheduleKey *key, const BWT nbBitLen);

LIBSPEC_PE
void FPENSRI_Initialize(ScheduleKey *encKey, ScheduleKey *decKey, const BYTE *key, BWT keyLen, const BYTE *tweakKey, BWT tweakKeyLen, BWT nbBitLen);

LIBSPEC_PE
void FPENSRI_CW_Initialize(ScheduleKey *encKey, ScheduleKey *decKey, const BYTE *key, BWT keyLen, const BYTE *tweakKey, BWT tweakKeyLen, BWT radix, BWT xLen);

LIBSPEC_PE
void FPENSRI_CW_Encrypt(BYTE *y, BYTE *x, BWT xLen, const ScheduleKey *key);

LIBSPEC_PE
void FPENSRI_CW_Decrypt(BYTE *y, BYTE *x, BWT xLen, const ScheduleKey *key);

#ifdef __cplusplus
}
#endif

#endif /* _FPE_NSRI_H_ */
