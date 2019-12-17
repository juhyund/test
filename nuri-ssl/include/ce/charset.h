#ifndef _CHARSET_H
#define _CHARSET_H

/** 
  @file charset.h
  @brief Character Set

  EUC-KR/UTF8/UTF16 ������ ��ȯ �Լ�
*/

#include "me_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  @param out    [out] BYTE�� ��� ������ ������
  @param outLen [out] ��ȯ�� �������� ����Ʈ ����
  @param in      [in] BYTE�� �Է� ������ ������ 
  @return CHARSET_ERRORS
  @sa CHARSET_EuckrToUtf16

  UTF16 ������ �Է� in�� EUC-KR�������� ��ȯ�� out���� ����Ѵ�.
  ��ȯ�� ����Ʈ ũ��� outLen�� ���´�.
*/		
LIBSPEC_ME 
int CHARSET_Utf16ToEuckr
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE�� ��� ������ ������
  @param outLen [out] ��ȯ�� �������� ����Ʈ ����
  @param in      [in] BYTE�� �Է� ������ ������ 
  @return CHARSET_ERRORS
  @sa CHARSET_Utf16ToEuckr

  EUC-KR ������ �Է� in�� UTF16 �������� ��ȯ�� out���� ����Ѵ�.
  ��ȯ�� ����Ʈ ũ��� outLen�� ���´�.
*/		
LIBSPEC_ME 
int CHARSET_EuckrToUtf16
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE�� ��� ������ ������
  @param outLen [out] ��ȯ�� �������� ����Ʈ ����
  @param in      [in] BYTE�� �Է� ������ ������ 
  @return CHARSET_ERRORS
  @sa CHARSET_Utf8ToUtf16

  UTF8 ������ �Է� in�� UTF16 �������� ��ȯ�� out���� ����Ѵ�.
  ��ȯ�� ����Ʈ ũ��� outLen�� ���´�.
*/
LIBSPEC_ME 
int CHARSET_Utf8ToUtf16
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE�� ��� ������ ������
  @param outLen [out] ��ȯ�� �������� ����Ʈ ����
  @param in      [in] BYTE�� �Է� ������ ������ 
  @return CHARSET_ERRORS
  @sa CHARSET_Utf16ToUtf8

  UTF16 ������ �Է� in�� UTF8 �������� ��ȯ�� out���� ����Ѵ�.
  ��ȯ�� ����Ʈ ũ��� outLen�� ���´�.
*/		
LIBSPEC_ME 
int CHARSET_Utf16ToUtf8
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE�� ��� ������ ������
  @param outLen [out] ��ȯ�� �������� ����Ʈ ����
  @param in      [in] BYTE�� �Է� ������ ������ 
	@return CHARSET_ERRORS
	@sa CHARSET_EuckrToUtf8

		UTF8������ �Է� in�� EUC-KR�������� ��ȯ�� out���� ����Ѵ�.
		��ȯ�� ����Ʈ ũ��� outLen�� ���´�.
*/
LIBSPEC_ME 
int CHARSET_Utf8ToEuckr
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE�� ��� ������ ������
  @param outLen [out] ��ȯ�� �������� ����Ʈ ����
  @param in      [in] BYTE�� �Է� ������ ������ 
  @return CHARSET_ERRORS
  @sa CHARSET_Utf8ToEuckr
		
		EUC-KR������ �Է� in�� UTF8�������� ��ȯ�� out���� ����Ѵ�.
		��ȯ�� ����Ʈ ũ��� outLen�� ���´�.
*/
LIBSPEC_ME 
int CHARSET_EuckrToUtf8
      (BYTE *out, int *outLen, const BYTE *in);


#ifdef __cplusplus
}
#endif

#endif /* _CHARSET_H */
