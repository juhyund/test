/** @defgroup ME Message Encoding
 */

/** @file me_define.h
    @brief ME ����� ���� define 

    ME(Message Encoding)��⿡�� ���Ǵ� ������ ����
    �������� ���� �����Ѵ�.
*/

#ifndef _ME_DEFINE_H_
#define _ME_DEFINE_H_

#include "base_define.h"

/* Library Specification */
#if defined(EXPORT_ME) && defined(IMPORT_ME)
  #error "Invalid Library Specification"
#endif


/** @def LIBSPEC
    ���� ��ũ ���̺귯���� ���� ��� �ɺ����� Ư���� ������ �ش�. 
*/

#ifdef LIBSPEC_ME
#undef LIBSPEC_ME
#endif

#if defined(EXPORT_ME)
#define LIBSPEC_ME __declspec(dllexport)
#elif defined(IMPORT_ME)
#define LIBSPEC_ME __declspec(dllimport)
#else
#define LIBSPEC_ME
#endif

#endif /* _ME_DEFINE_H_ */

