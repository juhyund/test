/** @defgroup PE Preserving Encryption
 * @brief FPE(Format-Preserving Encryption) and OPE(Order-Preserving Encryption)
 */

/** @file pe_define.h
    @brief ���� define 

    SP(Security Protocol)��⿡�� ���Ǵ� ������ ����
    �������� ���� �����Ѵ�.
*/

#ifndef _PE_DEFINE_H_
#define _PE_DEFINE_H_

#include "base_define.h"

/* Library Specification */
#if defined(EXPORT_PE) && defined(IMPORT_PE)
  #error "Invalid Library Specification"
#endif


/** @def LIBSPEC_PE
    ���� ��ũ ���̺귯���� ���� ��� �ɺ����� Ư���� ������ �ش�. 
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
