/** @defgroup SP Security Protocol
 */

/** @file sp_define.h
    @brief 공통 define 

    SP(Security Protocol)모듈에서 사용되는 공통의 값과
    데이터형 등을 정의한다.
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
    동적 링크 라이브러리를 만들 경우 심볼들의 특성을 정의해 준다. 
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
