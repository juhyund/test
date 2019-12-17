#ifndef _CHARSET_H
#define _CHARSET_H

/** 
  @file charset.h
  @brief Character Set

  EUC-KR/UTF8/UTF16 사이의 변환 함수
*/

#include "me_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  @param out    [out] BYTE형 출력 데이터 포인터
  @param outLen [out] 변환된 데이터의 바이트 길이
  @param in      [in] BYTE형 입력 데이터 포인터 
  @return CHARSET_ERRORS
  @sa CHARSET_EuckrToUtf16

  UTF16 형식의 입력 in을 EUC-KR형식으로 변환해 out으로 출력한다.
  변환된 바이트 크기는 outLen에 적는다.
*/		
LIBSPEC_ME 
int CHARSET_Utf16ToEuckr
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE형 출력 데이터 포인터
  @param outLen [out] 변환된 데이터의 바이트 길이
  @param in      [in] BYTE형 입력 데이터 포인터 
  @return CHARSET_ERRORS
  @sa CHARSET_Utf16ToEuckr

  EUC-KR 형식의 입력 in을 UTF16 형식으로 변환해 out으로 출력한다.
  변환된 바이트 크기는 outLen에 적는다.
*/		
LIBSPEC_ME 
int CHARSET_EuckrToUtf16
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE형 출력 데이터 포인터
  @param outLen [out] 변환된 데이터의 바이트 길이
  @param in      [in] BYTE형 입력 데이터 포인터 
  @return CHARSET_ERRORS
  @sa CHARSET_Utf8ToUtf16

  UTF8 형식의 입력 in을 UTF16 형식으로 변환해 out으로 출력한다.
  변환된 바이트 크기는 outLen에 적는다.
*/
LIBSPEC_ME 
int CHARSET_Utf8ToUtf16
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE형 출력 데이터 포인터
  @param outLen [out] 변환된 데이터의 바이트 길이
  @param in      [in] BYTE형 입력 데이터 포인터 
  @return CHARSET_ERRORS
  @sa CHARSET_Utf16ToUtf8

  UTF16 형식의 입력 in을 UTF8 형식으로 변환해 out으로 출력한다.
  변환된 바이트 크기는 outLen에 적는다.
*/		
LIBSPEC_ME 
int CHARSET_Utf16ToUtf8
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE형 출력 데이터 포인터
  @param outLen [out] 변환된 데이터의 바이트 길이
  @param in      [in] BYTE형 입력 데이터 포인터 
	@return CHARSET_ERRORS
	@sa CHARSET_EuckrToUtf8

		UTF8형식의 입력 in을 EUC-KR형식으로 변환해 out으로 출력한다.
		변환된 바이트 크기는 outLen에 적는다.
*/
LIBSPEC_ME 
int CHARSET_Utf8ToEuckr
      (BYTE *out, int *outLen, const BYTE *in);

/**
  @param out    [out] BYTE형 출력 데이터 포인터
  @param outLen [out] 변환된 데이터의 바이트 길이
  @param in      [in] BYTE형 입력 데이터 포인터 
  @return CHARSET_ERRORS
  @sa CHARSET_Utf8ToEuckr
		
		EUC-KR형식의 입력 in을 UTF8형식으로 변환해 out으로 출력한다.
		변환된 바이트 크기는 outLen에 적는다.
*/
LIBSPEC_ME 
int CHARSET_EuckrToUtf8
      (BYTE *out, int *outLen, const BYTE *in);


#ifdef __cplusplus
}
#endif

#endif /* _CHARSET_H */
