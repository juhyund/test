/** @defgroup CKM Certificate and Key Management
 */
/** @file ckm_define.h
    @brief 공통 define 

    CKM(Certificate and Key Management)모듈에서 사용되는 공통의 값과
    데이터형 등을 정의한다.
*/

#ifndef _CKM_DEFINE_H_
#define _CKM_DEFINE_H_

#include "base_define.h"

/* Error Code Type Definition */
#ifndef ER_CMS
#define ER_CMS (-9900)
#endif /* ER_CMS */
#ifndef ER_CERT
#define ER_CERT (-10099)
#endif /* ER_CERT */
#ifndef ER_CERTS
#define ER_CERTS (-10199)
#endif /* ER_CERTS */
#ifndef ER_CRL
#define ER_CRL (-10299)
#endif /* ER_CRL */
#ifndef ER_CKM
#define ER_CKM (-10399)
#endif /* ER_CKM */
#ifndef ER_X509COM
#define ER_X509COM (-10499)
#endif /* ER_X509COM */
#ifndef ER_ATTCERT
#define ER_ATTCERT (-10599)
#endif /* ER_ATTCERT */
#ifndef ER_PKCS
#define ER_PKCS (-10699)
#endif /* ER_PKCS */

#ifndef RET_CRL
#define RET_CRL 10200
#endif

/* Library Specification */
#if defined(EXPORT_CKM) && defined(IMPORT_CKM)
  #error "Invalid Library Specification"
#endif


/** @def LIBSPEC
    동적 링크 라이브러리를 만들 경우 심볼들의 특성을 정의해 준다. 
*/

#ifdef LIBSPEC_CKM
#undef LIBSPEC_CKM
#endif

#if defined(EXPORT_CKM)
#define LIBSPEC_CKM __declspec(dllexport)
#elif defined(IMPORT_CKM)
#define LIBSPEC_CKM __declspec(dllimport)
#else
#define LIBSPEC_CKM
#endif

#endif /* _CKM_DEFINE_H_ */
