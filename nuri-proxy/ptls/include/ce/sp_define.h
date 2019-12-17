/** @defgroup SP Security Protocol
 */

/** @file sp_define.h
    @brief ���� define 

    SP(Security Protocol)��⿡�� ���Ǵ� ������ ����
    �������� ���� �����Ѵ�.
*/

#ifndef _SP_DEFINE_H_
#define _SP_DEFINE_H_

#include "base_define.h"

/* Error Code Type Definition */
#ifndef ER_QSL
#define ER_QSL (-999)
#endif /* ER_QSL */

/* Library Specification */
#if defined(EXPORT_SP) && defined(IMPORT_SP)
  #error "Invalid Library Specification"
#endif


/** @def LIBSPEC_SP
    ���� ��ũ ���̺귯���� ���� ��� �ɺ����� Ư���� ������ �ش�. 
*/

#ifdef LIBSPEC_SP
#undef LIBSPEC_SP
#endif

#if defined(EXPORT_SP)
#define LIBSPEC_SP __declspec(dllexport)
#elif defined(IMPORT_SP)
#define LIBSPEC_SP __declspec(dllimport)
#else
#define LIBSPEC_SP
#endif

#endif /* _SP_DEFINE_H_ */
