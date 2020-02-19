/** @defgroup PE Preserving Encryption
 * @brief FPE(Format-Preserving Encryption) and OPE(Order-Preserving Encryption)
 */

/** @file pe_define.h
    @brief 공통 define 

    SP(Security Protocol)모듈에서 사용되는 공통의 값과
    데이터형 등을 정의한다.
*/

#ifndef _PE_DEFINE_H_
#define _PE_DEFINE_H_

#include "base_define.h"

/* Library Specification */
#if defined(EXPORT_PE) && defined(IMPORT_PE)
  #error "Invalid Library Specification"
#endif


/** @def LIBSPEC_PE
    동적 링크 라이브러리를 만들 경우 심볼들의 특성을 정의해 준다. 
*/

#ifdef LIBSPEC_PE
#undef LIBSPEC_PE
#endif

#if defined(EXPORT_PE)
#define LIBSPEC_PE __declspec(dllexport)
#elif defined(IMPORT_PE)
#define LIBSPEC_PE __declspec(dllimport)
#else
#define LIBSPEC_PE
#endif

#endif /* _PE_DEFINE_H_ */
