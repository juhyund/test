/** @file base_define.h
    @brief 공통 define 

    공통의 값과 데이터형 등을 정의한다.
*/

#ifndef _DEFINE_H_
#define _DEFINE_H_

#ifdef DEBUG
#include <stdio.h>
#endif
#include "sysconfig.h"

#ifndef CIS_VERSION
#define CIS_VERSION 3.3
#define CIS_VERSION_STR "3.3"
#define CIS_CC_NAME_VERSION_STR "CIS-CC v3.3"
#endif

/* BIT Type Definition */

#ifdef BYTE
#undef BYTE
#endif

/** @typedef BYTE
    8비트 정보를 담을 수 있는 데이터형
*/
typedef unsigned char   BYTE;

/** @typedef BT16
    16비트 정보를 담을 수 있는 데이터형
*/
typedef CIS_BT16 BT16;

/** @typedef BT32
    32비트 정보를 담을 수 있는 데이터형
*/
typedef CIS_BT32 BT32;

/** @typedef BT64
    64비트 정보를 담을 수 있는 데이터형
*/
#ifdef CIS_BT64
typedef CIS_BT64 BT64;
#endif

/** @typedef BT128
    128비트 정보를 담을 수 있는 데이터형
*/
#ifdef CIS_BT128
typedef CIS_BT128 BT128;
#endif

#if (CIS_SIZE_PTR == 8)
#define PTR_TO_INT_T BT64
#elif (CIS_SIZE_PTR == 4)
#define PTR_TO_INT_T BT32
#elif (CIS_SIZE_PTR == 2)
#define PTR_TO_INT_T BT16
#else
#error cannot determine pointer size
#endif

#define BYTE_MASK   (0xff)
#define BT16_MASK   (0xffff)
#define BT32_MASK   (0xffffffff)
#define BT64_MASK   (0xffffffffffffffffLL)
#define BT128_MASK  (0xffffffffffffffffffffffffffffffff)


#ifdef WORD_IS_16
#define BASE_WORD_BIT_LEN 16
#endif

#ifdef WORD_IS_32
#define BASE_WORD_BIT_LEN 32
#endif

#ifdef WORD_IS_64
#define BASE_WORD_BIT_LEN 64
#endif

#if !defined(WORD_IS_16) && !defined(WORD_IS_64)
#define BASE_WORD_BIT_LEN 32
#endif


/* Word Type Definition */
/** @typedef BWT
    하드웨어가 처리하는 기본 데이터 블록의 크기; Base Word Type
*/
/** @typedef HWT
    Half of BWT
*/
/** @typedef DWT
    Double BWT
*/
#if (BASE_WORD_BIT_LEN == 16)
typedef BYTE HWT;
typedef BT16 BWT;
typedef BT32 DWT;
#define HWT_MASK  (BYTE_MASK)
#define BWT_MASK  (BT16_MASK)
#define DWT_MASK  (BT32_MASK)
#endif

#if (BASE_WORD_BIT_LEN == 32)
typedef BT16 HWT;
typedef BT32 BWT;
typedef BT64 DWT;
#define HWT_MASK  (BT16_MASK)
#define BWT_MASK  (BT32_MASK)
#define DWT_MASK  (BT64_MASK)
#endif

#if (BASE_WORD_BIT_LEN == 64)
typedef BT32  HWT;
typedef BT64  BWT;
typedef BT128 DWT;
#define HWT_MASK  (BT32_MASK)
#define BWT_MASK  (BT64_MASK)
#define DWT_MASK  (BT128_MASK)
#endif

#define BWT_BIT_LEN  BASE_WORD_BIT_LEN
#define HWT_BIT_LEN  (BWT_BIT_LEN/2)
#define DWT_BIT_LEN  (BWT_BIT_LEN*2)

#define BWT_BYTE_LEN (BWT_BIT_LEN/8)
#define HWT_BYTE_LEN (HWT_BIT_LEN/8)
#define DWT_BYTE_LEN (DWT_BIT_LEN/8)

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif


/* Error Code Type Definition */
/** @ingroup CC
 * @brief 특정 function의 수행 결과를 나타냄
 *
 * ERT 타입은 function의 수행 결과를 나타내며 다음의 값들이 가능하다:
 * - SUCCESS
 * - FAIL
 * - INVALID_ARG
 * - ER_ 로 시작하는 enumeration type들
 */
typedef int ERT;

/** @addtogroup CC
 * @{ */
/** 성공 */
#ifndef SUCCESS
#define SUCCESS 0
#endif /* SUCCESS */

/** 실패 */
#ifndef FAIL
#define FAIL -1
#endif /* FAIL */

/** 잘못된 argument가 입력됐을 경우 */
#ifndef INVALID_ARG
#define INVALID_ARG -2
#endif /* INVALID_ARG */

enum _COMMON_ERROR_CODE {
  ER_NULL_PARAM = -3, /**< NULL일 수 없는 parameter가 NULL일 경우 */
  ER_MEMORY_ALLOC_FAIL = -4, /**< 메모리 할당이 실패했을 경우 */
  ER_FILE_WRITING_FAIL = -5, /**< 파일 출력이 실패했을 경우 */
  ER_FILE_READING_FAIL = -6, /**< 파일 입력이 실패했을 경우 */
  ER_NEGATIVE_INTEGER = -7 /**< 음의 정수가 디코딩된 경우 */
}; 

/** @} */

/* Endianness Specification */

/* Intel i386 CPU */
#if defined(__i386) || defined(WIN32) || defined(_WIN32)
#ifndef _LITTLE_ENDIAN_
#define _LITTLE_ENDIAN_
#endif
#endif

/* Intel Itanium CPU */
#if defined(__ia64__) || defined(__ia64)
  #if defined(WIN64) || defined(_WIN64) || defined(WIN32) || defined(_WIN32) || defined(__linux__)
    #ifndef _LITTLE_ENDIAN_
      #define _LITTLE_ENDIAN_
    #endif
  #else
    #ifndef _BIG_ENDIAN_
      #define _BIG_ENDIAN_
    #endif
  #endif
#endif

/* Digital Alpha CPU with OSF */
#if defined(__alpha) && defined(__osf__)
#ifndef _LITTLE_ENDIAN_
#define _LITTLE_ENDIAN_
#endif
#endif

/* HP's HPPA CPU */
#if defined(__hppa)
#ifndef _BIG_ENDIAN_
#define _BIG_ENDIAN_
#endif
#endif

/* Sun Sparc CPU */
#if defined(__sparc)
#ifndef _BIG_ENDIAN_
#define _BIG_ENDIAN_
#endif
#endif

/* Motorola(?) PowerPC CPU */
#if defined(_POWER) || defined(powerpc) || defined(__powerpc__) || defined (__ppc__) || defined (__PPC__) || defined (__powerpc__) || defined (__PPC) || defined (__ppc64)
#ifndef _BIG_ENDIAN_
#define _BIG_ENDIAN_
#endif
#endif

/* ARM CPU */
#if defined(__arm) || defined(__arm__)
#ifndef _LITTLE_ENDIAN_
#define _LITTLE_ENDIAN_
#endif
#endif

/* ARM64 CPU */
#if defined(__aarch64) || defined(__aarch64__)
#ifndef _LITTLE_ENDIAN_
#define _LITTLE_ENDIAN_
#endif
#endif

/* AMD64 CPU */
#if defined(__amd64) || defined(__amd64__)
#ifndef _LITTLE_ENDIAN_
#define _LITTLE_ENDIAN_
#endif
#endif

/* MIPS32 CPU */
#if defined(__mips) || defined(__mips__)
#if defined(__mipsel)
#ifndef _LITTLE_ENDIAN_
#define _LITTLE_ENDIAN_
#endif
#else //mipsel
#ifndef _BIG_ENDIAN_
#define _BIG_ENDIAN_
#endif
#endif //mipsel
#endif

/* borrow from 'glib.h' */
#  if defined (__GNUC__) && !defined (__STRICT_ANSI__) && !defined (__cplusplus)
#    define _START    (void)(
#    define _END      )
#  else
#    if (defined (sun) || defined (__sun__))
#      define _START  if (1)
#      define _END    else (void)0
#    else
#      define _START  do
#      define _END    while (0)
#    endif
#  endif


/* assertion code for error handling */
#ifndef DEBUG

#define DEBUG_STR(expr)
#define ER_IF(expr)

#define ER_RET_IF(expr)           if(expr) return FAIL
#define ER_RET_VAL(val)           return (val)
#define ER_RET_VAL_IF(expr, val)  if(expr) return (val)
#define ER_RET_VOID_IF(expr)      if(expr) return
#define ER_RET_NULL_IF(expr)      if(expr) return NULL

#define ER_RETX_IF(expr, line)           if(expr) _START { line; return FAIL; } _END
#define ER_RETX_VAL(val, line)                    _START { line; return (val); } _END
#define ER_RETX_VAL_IF(expr, val, line)  if(expr) _START { line; return (val); } _END
#define ER_RETX_VOID_IF(expr, line)      if(expr) _START { line; return; } _END
#define ER_RETX_NULL_IF(expr, line)      if(expr) _START { line; return NULL; } _END

#else /* DEBUG */

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifdef __GNUC__

#define _ER_PRINT(expr) fprintf(stderr, "ERROR: '%s', file %s, line %d(%s).\n\n", #expr, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define DEBUG_STR(expr) fprintf(stderr, "DEBUG: '%s', file %s, line %d(%s).\n\n", #expr, __FILE__, __LINE__, __PRETTY_FUNCTION__)

#define ER_IF(expr)  if(expr) _ER_PRINT(expr)

#define ER_RET_IF(expr)           if(expr) _START { _ER_PRINT(expr); return FAIL; } _END    

#define ER_RET_VAL(val)    _START {fprintf(stderr, "ERROR: file %s, line %d(%s), '%s' returned.\n\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ , #val); return (val); } _END

#define ER_RET_VAL_IF(expr, val)  if(expr) _START { fprintf(stderr, "ERROR: '%s', file %s, line %d(%s), '%s' returned.\n\n", #expr, __FILE__, __LINE__, __PRETTY_FUNCTION__ , #val); return (val); } _END

#define ER_RET_NULL_IF(expr)      if(expr) _START { _ER_PRINT(expr); return NULL; } _END

#define ER_RET_VOID_IF(expr)      if(expr) _START { _ER_PRINT(expr); return; } _END

#define ER_RETX_IF(expr, line)           if(expr) _START { line; _ER_PRINT(expr); return FAIL; } _END    

#define ER_RETX_VAL(val, line)  _START { line; fprintf(stderr, "ERROR: file %s, line %d(%s), '%s' returned.\n\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ , #val); return (val); } _END

#define ER_RETX_VAL_IF(expr, val, line)  if(expr) _START { line; fprintf(stderr, "ERROR: '%s', file %s, line %d(%s), '%s' returned.\n\n", #expr, __FILE__, __LINE__, __PRETTY_FUNCTION__ , #val); return (val); } _END

#define ER_RETX_NULL_IF(expr, line)      if(expr) _START { line; _ER_PRINT(expr); return NULL; } _END

#define ER_RETX_VOID_IF(expr, line)      if(expr) _START { line; _ER_PRINT(expr); return; } _END

#else /* !__GNUC__ */

#define _ER_PRINT(expr) fprintf(stderr, "ERROR: '%s', file %s, line %d.\n\n", #expr, __FILE__, __LINE__)

#define ER_IF(expr)  if(expr) _ER_PRINT(expr)

#define ER_RET_IF(expr)           if(expr) _START { _ER_PRINT(expr); return FAIL; } _END    

#define ER_RET_VAL(val)  _START { fprintf(stderr, "ERROR: file %s, line %d, '%s' returned.\n\n", __FILE__, __LINE__, #val); return (val); } _END

#define ER_RET_VAL_IF(expr, val)  if(expr) _START { fprintf(stderr, "ERROR: '%s', file %s, line %d, '%s' returned.\n\n", #expr, __FILE__, __LINE__, #val); return (val); } _END

#define ER_RET_NULL_IF(expr)      if(expr) _START { _ER_PRINT(expr); return NULL; } _END

#define ER_RET_VOID_IF(expr)      if(expr) _START { _ER_PRINT(expr); return; } _END

#define ER_RETX_IF(expr, line)           if(expr) _START { line; _ER_PRINT(expr); return FAIL; } _END    

#define ER_RETX_VAL(val, line)  _START { line; fprintf(stderr, "ERROR: file %s, line %d, '%s' returned.\n\n", __FILE__, __LINE__, #val); return (val); } _END

#define ER_RETX_VAL_IF(expr, val, line)  if(expr) _START { line; fprintf(stderr, "ERROR: '%s', file %s, line %d, '%s' returned.\n\n", #expr, __FILE__, __LINE__, #val); return (val); } _END

#define ER_RETX_NULL_IF(expr, line)      if(expr) _START { line; _ER_PRINT(expr); return NULL; } _END

#define ER_RETX_VOID_IF(expr, line)      if(expr) _START { line; _ER_PRINT(expr); return; } _END

#endif /* __GNUC__ */

#endif /* DEBUG */



/* to avoid the bug that 32-bit solaris cannot handle file descriptors
 * above 256 */
#if defined(_SOLARIS_SAFE_FILE_OPEN_) && defined(sparc) && !defined(_LP64)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __GNUC__
#warning FILE structure has been changed to avoid Solaris max-open file bug. Most FILE functions except fopen(), fclose(), fread(), fwrite(), fseek(), etc DO NOT OPERATE. Use those FILE functions VERY CAREFULLY
#endif /* __GNUC__ */
  
/* substitute macros */
#define FILE _SAFE_FILE
#define fopen(path, mode)      _safe_fopen(path, mode)
#define fclose(stream)         _safe_fclose(stream)
#define fread(p, sz, n, st)    _safe_fread(p, sz, n, st)
#define fwrite(p, sz, n, st)   _safe_fwrite(p, sz, n, st)
#define fseek(s, o, w)         _safe_fseek(s, o, w)
#define ftell(s)               _safe_ftell(s)
#define rewind(s)              _safe_rewind(s)
#undef  feof
#define feof(s)                _safe_feof(s)
#undef  ferror
#define ferror(s)              _safe_ferror(s)
#define fileno(s)              _safe_fileno(s)
#define fprintf                _safe_fprintf


/* new _safe_file function definitions */

typedef int _SAFE_FILE;

_SAFE_FILE *_safe_fopen  (const char *filename, const char *mode);
int         _safe_fclose (_SAFE_FILE *stream);
size_t      _safe_fread  (void *ptr, size_t size, size_t nitems,
                          _SAFE_FILE *stream);
size_t      _safe_fwrite (const void *ptr, size_t size, size_t nitems,
                          _SAFE_FILE *stream);
int         _safe_fseek  (_SAFE_FILE *stream, long offset, int whence);
long        _safe_ftell  (_SAFE_FILE *stream);
void        _safe_rewind (_SAFE_FILE *stream);
int         _safe_feof   (_SAFE_FILE *stream);
int         _safe_ferror (_SAFE_FILE *stream);
int         _safe_fileno (_SAFE_FILE *stream);
int         _safe_fprintf(void *stream, const char *format, ...);

#endif /* if defined(_SOLARIS_SAFE_FILE_OPEN_) ... */


#endif /* _DEFINE_H_ */

