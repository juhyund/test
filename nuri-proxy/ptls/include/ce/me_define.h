/** @defgroup ME Message Encoding
 */

/** @file me_define.h
    @brief ME 모듈의 공통 define 

    ME(Message Encoding)모듈에서 사용되는 공통의 값과
    데이터형 등을 정의한다.
*/

#ifndef _ME_DEFINE_H_
#define _ME_DEFINE_H_

#include "base_define.h"

/* Library Specification */
#if defined(EXPORT_ME) && defined(IMPORT_ME)
  #error "Invalid Library Specification"
#endif


/** @def LIBSPEC
    동적 링크 라이브러리를 만들 경우 심볼들의 특성을 정의해 준다. 
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

