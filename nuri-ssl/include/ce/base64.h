
#ifndef _BASE64_H_
#define _BASE64_H_

/** @file base64.h
    @brief Base64 인코딩/디코딩 모듈
*/

/**
 * @defgroup BASE64 Base64 Encoding
 * @ingroup ME
 * @{ */

#include "me_define.h"
/** @def BASE64_NUM_IN_LINE
    Base64 encoding bytes number in line
    Base64_EncodeWithNewLine, Base64_EncodeWithAddedNewLine을  사용해
    인코딩 할 경우 한 라인에 출력할 바이트 길이이다.
    4의 배수가 되어야 한다.
*/
/** @def BASE64_NUM_INPUT
    Base64_NUM_IN_LINE을 사용해 계산해 낸 입력 바이트
    길이이다.
*/
#define BASE64_NUM_IN_LINE 64 /* 4의 배수 */
#define BASE64_NUM_INPUT  (BASE64_NUM_IN_LINE/4) * 3

#ifdef __cplusplus
extern "C" {
#endif

/**
  @param encodeData [out] 인코딩된 데이터 값이 할당될 버퍼를 가리키는 포인터
  @param encodeMax   [in] 인코딩 버퍼의 최대 바이트 길이
  @param data        [in] 입력 데이터 포인터
  @param dataLen     [in] 입력 데이터의 바이트 길이
  @return BASE64_ERRORS or SUCCESS
  @sa Base64_EncodeWithNewLine, Base64_EncodeWithAddedNewLine,
  Base64_Decode

  data를 입력 받아서 Base64 인코딩 된 결과를 encodeData로 출력한다.
  라인 구분 없음.
*/
LIBSPEC_ME 
int Base64_Encode
         (char         *encodeData, 
          unsigned int  encodeMax, 
          const BYTE   *data, 
          unsigned int  dataLen);

/**
  @param encodeData [out] 인코딩된 데이터 값이 할당될 버퍼를 가리키는 포인터
  @param encodeMax   [in] 인코딩 버퍼의 최대 바이트 길이
  @param data        [in] 입력 데이터 포인터
  @param dataLen     [in] 입력 데이터의 바이트 길이
  @return BASE64_ERRORS or SUCCESS
  @sa Base64_Encode, Base64_EncodeWithAddedNewLine, Base64_Decode

  data를 입력 받아서 Base64 인코딩 된 결과를 encodeData로 출력한다.
  라인 구분 있음.(인코딩된 결과인 encodeData에  BASE64_NUM_IN_LINE개의
  char마다 '\n'이 추가 되어 있다.)
*/
LIBSPEC_ME 
int Base64_EncodeWithNewLine
         (char         *encodeData, 
          unsigned int  encodeMax, 
          const BYTE   *data, 
          unsigned int  dataLen);


/**
  @param encodeData [out] 인코딩된 데이터 값이 할당될 버퍼를 가리키는 포인터
  @param encodeMax   [in] 인코딩 버퍼의 최대 바이트 길이
  @param data        [in] 입력 데이터 포인터
  @param dataLen     [in] 입력 데이터의 바이트 길이
  @return BASE64_ERRORS or SUCCESS
  @sa Base64_Encode, Base64_EncodeWithNewLine, Base64_Decode

  data를 입력 받아서 Base64 인코딩 된 결과를 encodeData로 출력한다.
  라인 구분 있음.(인코딩된 결과인 encodeData에  BASE64_NUM_IN_LINE개의
  char마다 '\r\n'이 추가 되어 있다.)
*/
LIBSPEC_ME 
int Base64_EncodeWithAddedNewLine
         (char          *encodeData, 
          unsigned int   encodeMax, 
          const BYTE   *data, 
          unsigned int  dataLen);

/**
  @param decodeData [out] 디코딩된 데이터 값이 할당될 버퍼의 데이터 포인터
  @param decodeMax  [in]  디코딩 버퍼의 최대 바이트 길이
  @param decodeLen  [out] 디코딩된 바이트 길이
  @param encodeData [in]  입력 인코딩 데이터를 가리키는 포인터 
  @return BASE64_ERRORS or SUCCESS
  @sa Base64_Encode, Base64_EncodeWithNewLine, Base64_EncodeWithAddedNewLine

  Base64 인코딩 된 encodeData를 입력 받아서 디코딩 된 결과를 decodeData로
  출력한다.  디코딩된 바이트 길이는 decodeLen에 출력된다.

  decodeMax값은 decodeData 버퍼가 가질 수 있는 바이트 단위 길이를 의미한다.
  이 입력값이 만약 디코딩될 결과물의 길이보다 작을 경우, 에러로 처리된다.
  따라서, decodeMax값은 충분한 값을 가져야 하며, 그 길이를 확실히 모를 경우,
  encodeData 길이의 3/4값으로 하면 충분하다. (참고, base64-encoding 한 결과물의
  길이는 반드시 4의 배수가 된다. 즉, encodeData의 스트링길이는 정상적인 인코딩값
  이라면 4의 배수일 것이다.)
*/
LIBSPEC_ME 
int Base64_Decode
         (BYTE         *decodeData, 
          unsigned int  decodeMax, 
          unsigned int *decodeLen, 
          const char   *encodeData);

#ifdef __cplusplus
}
#endif
/** @} */

#endif /* _BASE64_H_ */
 
