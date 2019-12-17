
#ifndef _BASE64_H_
#define _BASE64_H_

/** @file base64.h
    @brief Base64 ���ڵ�/���ڵ� ���
*/

/**
 * @defgroup BASE64 Base64 Encoding
 * @ingroup ME
 * @{ */

#include "me_define.h"
/** @def BASE64_NUM_IN_LINE
    Base64 encoding bytes number in line
    Base64_EncodeWithNewLine, Base64_EncodeWithAddedNewLine��  �����
    ���ڵ� �� ��� �� ���ο� ����� ����Ʈ �����̴�.
    4�� ����� �Ǿ�� �Ѵ�.
*/
/** @def BASE64_NUM_INPUT
    Base64_NUM_IN_LINE�� ����� ����� �� �Է� ����Ʈ
    �����̴�.
*/
#define BASE64_NUM_IN_LINE 64 /* 4�� ��� */
#define BASE64_NUM_INPUT  (BASE64_NUM_IN_LINE/4) * 3

#ifdef __cplusplus
extern "C" {
#endif

/**
  @param encodeData [out] ���ڵ��� ������ ���� �Ҵ�� ���۸� ����Ű�� ������
  @param encodeMax   [in] ���ڵ� ������ �ִ� ����Ʈ ����
  @param data        [in] �Է� ������ ������
  @param dataLen     [in] �Է� �������� ����Ʈ ����
  @return BASE64_ERRORS or SUCCESS
  @sa Base64_EncodeWithNewLine, Base64_EncodeWithAddedNewLine,
  Base64_Decode

  data�� �Է� �޾Ƽ� Base64 ���ڵ� �� ����� encodeData�� ����Ѵ�.
  ���� ���� ����.
*/
LIBSPEC_ME 
int Base64_Encode
         (char         *encodeData, 
          unsigned int  encodeMax, 
          const BYTE   *data, 
          unsigned int  dataLen);

/**
  @param encodeData [out] ���ڵ��� ������ ���� �Ҵ�� ���۸� ����Ű�� ������
  @param encodeMax   [in] ���ڵ� ������ �ִ� ����Ʈ ����
  @param data        [in] �Է� ������ ������
  @param dataLen     [in] �Է� �������� ����Ʈ ����
  @return BASE64_ERRORS or SUCCESS
  @sa Base64_Encode, Base64_EncodeWithAddedNewLine, Base64_Decode

  data�� �Է� �޾Ƽ� Base64 ���ڵ� �� ����� encodeData�� ����Ѵ�.
  ���� ���� ����.(���ڵ��� ����� encodeData��  BASE64_NUM_IN_LINE����
  char���� '\n'�� �߰� �Ǿ� �ִ�.)
*/
LIBSPEC_ME 
int Base64_EncodeWithNewLine
         (char         *encodeData, 
          unsigned int  encodeMax, 
          const BYTE   *data, 
          unsigned int  dataLen);


/**
  @param encodeData [out] ���ڵ��� ������ ���� �Ҵ�� ���۸� ����Ű�� ������
  @param encodeMax   [in] ���ڵ� ������ �ִ� ����Ʈ ����
  @param data        [in] �Է� ������ ������
  @param dataLen     [in] �Է� �������� ����Ʈ ����
  @return BASE64_ERRORS or SUCCESS
  @sa Base64_Encode, Base64_EncodeWithNewLine, Base64_Decode

  data�� �Է� �޾Ƽ� Base64 ���ڵ� �� ����� encodeData�� ����Ѵ�.
  ���� ���� ����.(���ڵ��� ����� encodeData��  BASE64_NUM_IN_LINE����
  char���� '\r\n'�� �߰� �Ǿ� �ִ�.)
*/
LIBSPEC_ME 
int Base64_EncodeWithAddedNewLine
         (char          *encodeData, 
          unsigned int   encodeMax, 
          const BYTE   *data, 
          unsigned int  dataLen);

/**
  @param decodeData [out] ���ڵ��� ������ ���� �Ҵ�� ������ ������ ������
  @param decodeMax  [in]  ���ڵ� ������ �ִ� ����Ʈ ����
  @param decodeLen  [out] ���ڵ��� ����Ʈ ����
  @param encodeData [in]  �Է� ���ڵ� �����͸� ����Ű�� ������ 
  @return BASE64_ERRORS or SUCCESS
  @sa Base64_Encode, Base64_EncodeWithNewLine, Base64_EncodeWithAddedNewLine

  Base64 ���ڵ� �� encodeData�� �Է� �޾Ƽ� ���ڵ� �� ����� decodeData��
  ����Ѵ�.  ���ڵ��� ����Ʈ ���̴� decodeLen�� ��µȴ�.

  decodeMax���� decodeData ���۰� ���� �� �ִ� ����Ʈ ���� ���̸� �ǹ��Ѵ�.
  �� �Է°��� ���� ���ڵ��� ������� ���̺��� ���� ���, ������ ó���ȴ�.
  ����, decodeMax���� ����� ���� ������ �ϸ�, �� ���̸� Ȯ���� �� ���,
  encodeData ������ 3/4������ �ϸ� ����ϴ�. (����, base64-encoding �� �������
  ���̴� �ݵ�� 4�� ����� �ȴ�. ��, encodeData�� ��Ʈ�����̴� �������� ���ڵ���
  �̶�� 4�� ����� ���̴�.)
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
 
