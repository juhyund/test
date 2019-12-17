#ifndef _ASN1_H_
#define _ASN1_H_

#include <stdlib.h>
#include "base_define.h"
#include "me_define.h" /* base defines */
#include "oid.h"       /* base object identifiers */

#ifdef _WIN32_WCE
#include "wincemodule.h"
#else
#include <time.h>
#endif

/** @defgroup ASN ASN.1 Encoding
 * @ingroup ME
    @brief  ASN.1 DER encoding/decoding, set/get 모듈

    ASN.1 type 들을 C language로 표현하는 방법론과 그 type들을
    DER 방식으로 encoding/decoding 하는 기능과 type들의 값들을
    set/get 할 수 있는 기능을 제공한다.

    지원하는 ASN.1 type은 다음과 같다.

    Basic Type :
    Boolean, Integer, BitString, OctetString, Null, Oid, Enumerate,
    UTF8String, PrintableString, IA5String, UTCTime, GeneralizedTime,
    VisibleString, BMPString

    Constructed Type :
    Sequence, Sequence Of, Set, Set Of

    기본적으로 Encoding/Decoding은 ASN_New와 ASN_EncodeDER이라는
    두 함수가 수행하고, Set/Get은 ASN.1 type별로 함수가 제공된다.
    */

/** @file asn1.h
    @ingroup ASN
    @brief ASN.1 DER notation 따르는 type들을 처리하는 모듈.
 
    ASN.1 의 DER 형태로 encoding/decoding 되어야 하는 type을 처리하는
    모듈이다.  "devide and conquer"를 기본 원칙으로 처리해야 할 type을
    기본 ASN type들의 tree 형태로 구성하도록 하여 기본 type들의 
    encoding/decoding만으로 전체 type을 자동적으로 처리하도록 한다.

    이 모듈의 type 생성 규칙에 따라 type을 정의하는 것 만으로 그 type의 DER
    encoding/decoding이 자동적으로 이루어게 된다.
    */


#ifdef __cplusplus
extern "C" {
#endif





/******************************************************************************
 * ASN.1 Buffer
 */

typedef enum {
  ASN_SUCCESS = 0,
  ER_WRONG_TAG,
} ASN_ERRORS;

/** @ingroup ASN
    @struct ASNBuf
    @brief ASN.1 의 encoding/decoding 에 사용되는 버퍼
  
    ASN.1의 encoding 및 decoding 시 사용하는 버퍼 타입이다.
    일반적인 byte stream 버퍼와는 달리 alloc 길이가 포함되어 있지 않다는
    점에 유의하라.  len 이 그대로 데이타의 길이이자 alloc 길이이다.
    index 는 현재 처리해야할 byte 위치를 표시하도록 되어 있다.
    index 는 모듈 내부적으로 다루는 값이므로, 임의로 직접 변경해서는
    안된다.

    @sa ASNBuf_Set ASNBuf_Del ASNBuf_Sprint
    */
typedef struct _ASNBuf {
  char *data;    /**< 데이타 버퍼 */
  int   len;     /**< 데이타 버퍼의 길이 */
  int   index;   /**< 데이타 버버 중 현재 처리해야할 부분 */
} ASNBuf;

/** @ingroup ASN
    @def ASNBuf_SetP
    @brief ASNBuf 객체를 설정한다.

    버퍼를 저장하고 있는 char* 값과 바이트 단위 길이를 입력값으로 주어
    ASNBuf를 설정한다. 내부적으로 버퍼의 값을 복사하는 것이 아니고, 포인터값만
    할당하는 것이므로, 입력한 버퍼는 그대로 유지되어야 한다.

    @sa ASNBuf ASNBuf_Set ASNBuf_New ASNBuf_Del ASNBuf_Sprint
    */
#define ASNBuf_SetP(buf,d,l) ((buf)->data = (d), (buf)->len = (l), (buf)->index = 0)

/** @ingroup ASN
    @def ASNBuf_Set
    @brief ASNBuf 객체를 설정한다.

    버퍼를 저장하고 있는 char* 값과 바이트 단위 길이를 입력값으로 주어
    ASNBuf를 설정한다. ASNBuf_SetP와는 달리 내부적으로 버퍼의 값을 복사한다,

    @sa ASNBuf ASNBuf_SetP ASNBuf_New ASNBuf_Del ASNBuf_Sprint
    */
#define ASNBuf_Set(buf,d,l) (memcpy((buf)->data, (d), (l)), (buf)->len = (l), (buf)->index = 0)

/** @ingroup ASN
    @brief ASNBuf 객체를 동적으로 생성한다.
    @param allocSize [in] ASNBuf가 가질 수 있는 데이터의 바이트 단위 길이
    @ret if allocation fails, return NULL, if success, address of ASNBuf

    allocSize 만큼의 데이터를 동적으로 메모리에 할당한 다음, 
    ASNBuf 객체를 생성하여 그 주소값을 리턴한다.
    사용이 끝나면 반드시 ASNBuf_Del을 통하여 할당된 메모리를 free시켜야
    한다.

    @sa ASNBuf ASNBuf_SetP ASNBuf_Set ASNBuf_Del ASNBuf_Sprint
    */
LIBSPEC_ME
ASNBuf* ASNBuf_New(int allocSize);

/** @ingroup ASN
    @def ASNBuf_Del
    @brief 메모리에 할당되어 있는 ASNBuf를 free시킨다.

    메모리에 할당된 ASNBuf를 제거한다. ASN_EncodeDER()을 통해서,
    ASNBuf와 그의 버퍼 영역은 동적으로 할당되므로, 
    더이상 필요 없게 된 ASNBuf는 반드시 free시켜야 한다.

    @sa ASNBuf ASNBuf_SetP ASNBuf_Set ASNBuf_New ASNBuf_Sprint
    */

#ifndef _WIN32
#define ASNBuf_Del(buf) _START {if(buf) free(buf); (buf) = NULL;} _END
#else
#define ASNBuf_Del(buf) _START {if(buf) _ASNBuf_Del(buf); (buf) = NULL;} _END
LIBSPEC_ME
void _ASNBuf_Del(ASNBuf *buf);
#endif

/** @ingroup ASN
    @brief 지정한 파일의 내용을 새로운 ASNBuf로 가져온다.
    @param filePath 가져올 파일의 경로

    신규 ASNBuf를 할당한 후에 지정한 경로의 파일을 읽어서
    이에 저장하여 리턴한다.
    Base64, PEM, DER 인코딩된 파일을 지원한다.

    return : 성공 시에는 할당된 ASNBuf의 포인터, 실패시에는 NULL.

    @sa ASNBuf ASNBuf_SaveToFile
    */
LIBSPEC_ME
ASNBuf* ASNBuf_NewFromFile(const char *filePath);

/** @ingroup ASN
    @brief 지정한 파일의 내용을 새로운 ASNBuf로 가져온다.
    @param filePath 가져올 파일의 경로

    신규 ASNBuf를 할당한 후에 지정한 위치의 버퍼를 읽어서
    이에 저장하여 리턴한다.
    Base64, PEM, DER 인코딩된 버퍼를 지원한다.

    return : 성공 시에는 할당된 ASNBuf의 포인터, 실패시에는 NULL.

    @sa ASNBuf ASNBuf_SaveToFile
    */
LIBSPEC_ME
ASNBuf* ASNBuf_NewFromBuffer(const char *buf, unsigned int len);

/** @ingroup ASN
    @brief 지정한 ASNBuf의 내용을 파일로 저장한다.
    @param buf      저장할 ASNBuf의 포인터값.
    @param filePath 저장할 파일의 경로
    @retrun  SUCCESS or FAIL

    ASNBuf를 지정한 경로의 파일에 저장한다.

    @sa ASNBuf ASNBuf_NewFromFile
    */
LIBSPEC_ME
ERT ASNBuf_SaveToFile(ASNBuf *buf, const char *filePath);


/** @ingroup ASN
    @brief ASNBuf의 바이너리값을 16진수 문자열 형태로 출력한다.
    @param out 출력값이 저장될 버퍼의 주소값
    @param maxLen out이 가리키고 있는 버퍼의 최대 길이
    @param buf 출력시키고자 하는 ASNBuf

    ASNBuf의 바이너리값을 16진수 string형태로 \i out 에 출력한다.
    String의 끝에는 null terminator를 포함한다.
   
    return : SUCCESS, FAIL 

    @sa ASNBuf ASNBuf_Set ASNBuf_Del
    */
LIBSPEC_ME
ERT ASNBuf_Sprint(char *out, int maxLen, const ASNBuf *buf);

/** @ingroup ASN
    @brief 두개의 ASNBuf 값을 비교한다.
    @param a 비교할 ASNBuf 1
    @param b 비교할 ASNBuf 2

    memcmp() 함수와 마찬가지로 두 ASNBuf의 내용을 비교한다.
    return : 같으면 0, a가 작으면 -1, b가 작으면 1

    @sa ASNBuf
    */
LIBSPEC_ME
int ASNBuf_Compare(const ASNBuf *a, const ASNBuf *b);

/** @ingroup ASN
    @breif ASNBuf의 내용 중, 첫 ID, Length 바이트를 제거한 ASNBuf의 포인터를 리턴
    @param in  [in] ID, Length가 제거될 ASNBuf
    @sa ASNBuf

    */
LIBSPEC_ME
ASNBuf* ASNBuf_PeelOutIdLen(ASNBuf *in);



/******************************************************************************
 * ASN.1 octet field and option field
 */

/* @ingroup ASN
    @typedef ASNOption
    @brief ASN type의 형태를 지정하는 옵션
   
    ASN Option은 하위 2byte 만을 사용한다. 
    그러나 혹 있을지 모르는 SIGBUS 에러를 피하기 위해 4byte를 사용한다.
   
    하위 바이트는 implicit/explicit의 tagging 번호와 
    class, form 에  대한 정보를 담는다.
    하위 5bit가 tagging number 상위 3bit가 class와 form을 구분한다.
    form  = constructed or primitive
    class = universal, applcation, context-specific or private
   
    상위 바이트는 normal/im/ex tagging과, optional, class_speicific을 표시한다.
   
    상위 바이트의 하위 2bit가 tagging 사용을 표시.
    다음 3번째 bit가 1이면 class를 지정함을, 0이면 기본값을 사용함을 표시한다.
    상위 바이트의 최상위 bit는 이 type이 optional을 표시.
    상위 바이트의 최상위 바로 아래 bit는 이 type이 default 값을 가짐을 표시.
   
    나머지 bit들은 나중을 위한 예약 bit
    */
typedef unsigned int ASNOption;


/*
  ASN.1 identifier octet field (1'st octet)

    TAG_MASK   : 0001 1111, 0x1F
    FORM_MASK  : 0010 0000, 0x20
    CLASS_MASK : 1100 0000, 0xC0

  ASN.1 Module specific entended field (2'nd octet)

    OPT_FLAG_MASK     : 1000 0000
    DEFAULT_FLAG_MASK : 0100 0000
    CLASS_FLAG_MASK   : 0000 0100
    TAGGING_FLAG_MASK : 0000 0011  
    */

#define TAG_MASK   0x1F   /* tag mask */
#define FORM_MASK  0x20   /* form mask */
#define CLASS_MASK 0xC0   /* class mask */

typedef enum
{
  PRIM = 0,
  CONS = (1 << 5)
} ASN_FORM;

typedef enum
{
  ASN_CLASS = 1 << 10,
  UNIV = 0x0,
  APPL = (1 << 6),
  CNTX = (2 << 6),
  PRIV = (3 << 6)
} ASN_CLASSES;

typedef enum
{
  TAG_NORMAL   = 0,
  TAG_IMPLICIT = (1 << 8),
  TAG_EXPLICIT = (2 << 8),
} ASN_TAGGING;

#define ASN_DEFAULT  0x40000 /* (1<<14) */

#define ASN_OPTIONAL 0x80000 /* (1<<15) */


/** @enum ASN_UNIVERSAL_TAG
 *  @brief ASN.1 type들의 tag 코드 번호 정의
 *
 *  ASN.1 type 들을 구분해주는 tag 코드 번호들을 정의한다.
 */
typedef enum
{
  NO_TAG              =  0, /* in BER, 0 is reserved */

  TAG_BOOLEAN         =  1,
  TAG_INTEGER         =  2,
  TAG_BITSTRING       =  3,
  TAG_OCTETSTRING     =  4,
  TAG_NULL            =  5,
  TAG_OID             =  6,
  TAG_OD              =  7, /* not supported */
  TAG_EXTERNAL        =  8, /* not supported */
  TAG_REAL            =  9, /* not supported */
  TAG_ENUMERATE       = 10,
  TAG_EMBEDDEDPDV     = 11, /* not supported */
  TAG_UTF8STRING      = 12,
  TAG_RELATIVEOID     = 13, /* not supported */

  /* 14, 15 are reseved for future use */

  TAG_SEQ             = 16,
  TAG_SEQOF           = 16,
  TAG_SET             = 17,
  TAG_SETOF           = 17,

  TAG_NUMERICSTRING   = 18, /* not supported */
  TAG_PRINTABLESTRING = 19,
  TAG_TELETEXSTRING   = 20, /* not supported */
  TAG_VIDEOTEXSTRING  = 21, /* not supported */
  TAG_IA5STRING       = 22,
  TAG_UTCTIME         = 23,
  TAG_GENERALIZEDTIME = 24,
  TAG_GRAPHICSTRING   = 25, /* not supported */
  TAG_VISIBLESTRING   = 26,
  TAG_GENERALSTRING   = 27, /* not supported */
  TAG_UNIVERSALSTRING = 28, /* not supported */
  TAG_CHARACTERSTRING = 29, /* not supported */
  TAG_BMPSTRING       = 30,
 
  /* 31, and above are reserved for future use */  

} ASN_UNIVERSAL_TAG;

#define TAG_T61STRING    TAG_TELETEXSTRING
#define TAG_ISO646STRING TAG_VISIBLESTRING





/******************************************************************************
 * Descriptor
 */

/** @ingroup ASN
    @struct ASNDefault
    @brief   ASN 디스크립터의 DEFAULT 확장
  
    Default 값을 가지는 sequence나 set 내의 한 멤버가 있을 때
    이를 표시/처리해주기 위한 구조체이다.
    이 멤버의 tag 코드와 default 값의 DER encoding된 데이타 및 그
    길이를 갖는다.  디코더는 이 default 값을 갖는 멤버가 발견되지
    않을 경우 이 DER 데이타를 디코딩함으로써 default 값을 setting한다.
    인코더는 default 값과 실제 값을 비교해보고 둘이 동일할 경우
    인코딩 버퍼에 복사하지 않는다.
  
    default 부분은 디자인 단계에서는 전혀 고려하고 있지 않다가
    나중에 추가된 부분이므로 이후 수정/개선할 필요성이 높다고
    생각된다.
    */
typedef struct _ASNDefault {
  int       tagCode;    /**< 이 넘의 TAG code */
  int       dataLen;    /**< default data의 길이 */
  char     *data;       /**< default data의 byte stream */
} ASNDefault;

/**	@ingroup ASN
    @struct ASNDescriptor
    @brief  ASN 타입의 구조를 표시하는 디스크립터.
  
    특정 ASN.1 타입의 구조를 나타내기 위한 디스크립터 구조체이다.  
    모든 ASN.1 타입은 이 디스크립터의 정보를 사용하여 생성된다. 
  
    실제 디스크립터는 일종의 array로 구성된다.
  
    예 : ASN Boolean
    AD_BOOLEAN = {{ASNBool_New, 0}, {NULL, 0}}
  
    제일 처음 열은 이 타입을 만들기 위해 호출해야 하는 함수와
    그 옵션이다.
    그 다음열 부터는 타입 생성 함수에서 어떻게든 이용할 수 있는
    내용이다.  타입 생성함수마다 내용이 달라진다.
    대개의 construced type에서는 여기에 내부 멤버 타입의 디스크립터가 들어간다.
    제일 마지막열은 언제나 끝을 나타내는 {NULL, 0} 이다.
  
    세번째 argument는 특수한 경우에만 표시/사용한다.
    Sequence나 Set 안에서 element 하나가 default 값을 가질 때
    이를 가리키는 ASN Default의 포인터를 지정한다.
    */

typedef struct _ASNDescriptor {
  void       *param;       /**< void* 인 parameter. 여러가지 내용 가능 */
  ASNOption   option;      /**< 이 ASN.1 type의 option */
  ASNDefault *defaultDesc; /**< default 값을 가질 때 default descriptor를 가라키는 포인터 */
} ASNDescriptor[];



/******************************************************************************

                           Class를 갖는 ASN 타입들

 *****************************************************************************/



/******************************************************************************
 *  ASN.1 Base clase / type
 */

/**	@ingroup ASN
    @struct ASNClass
    @brief 모든 ASN.1 type들의 최상위 클래스

    모든 ASN.1 type들은 이 type을 제일 앞부분에 갖고 있어야만 한다.
    ASN.1 type 들이 기본적으로 가져야할 DER 인코딩에 관련한 
    데이타 및 함수들을 갖고 있다.
    */
typedef struct _ASNClass {
  ASNDescriptor *dsc;      /**< 자기 자신의 디스크립터 */

  int   derLen;            /**< DER 인코딩된 전체 길이 */

  char  derHead[8];        /**< DER Header(tag + length) 내용 */
  int   derHeadLen;        /**< DER Header의 길이 */
  char *derData;           /**< Header를 제외한 DER 인코딩된 내용 */
  int   derDataLen;        /**< derData 의 길이 */

  int  (*encodeDER)();     /**< DER encode function */
  int  (*getDER)();        /**< DER 버퍼를 구한다. */
  int  (*getDERLen)();     /**< DER 버퍼의 길이를 구한다. */
  int  (*copy)();          /**< 내용을 복사한다. */
  void (*del)();           /**< delete function */

#if 0
  int (*encodeDER)(struct ASNClass*); 
  int (*getDER)(ASNBuf*, struct ASNClass*);
  int (*getDERLen)(struct ASNClass*);
  int (*copy)(struct ASNClass*, struct ASNClass*);
  int (*set)(void *target, ...);
  int (*get)();
  void (*del)(struct ASNClass*);
#endif

} ASNClass;

typedef ASNClass ASN;  /* ASN class have no virtual member */

/**	@ingroup ASN
    @def ASN
    @brief ASN* 타입으로 casting하는 매크로
    
    */
#define ASN(a)  ((ASN*)(a))

/** @ingroup ASN
    @def pASN
    @brief ASN** 타입으로 casting하는 매크로

    */
#define pASN(a)  ((ASN**)(a))

/** @ingroup ASN
    @def ASN_New(type, data)
    @brief 신규 ASN type object를 생성하는 매크로

    ASNDescriptor를 사용하여 필요한 메모리 영역을
    할당하고 내용을 초기화하여 새로운 ASN type의 object를 하나 생성한다.

    다음은 ASN.1 기본 타입 중, boolean과 Integer에 해당하는 object를 생성하는 
    코드이다. 비교적 간단한 primitive 타입들에 대한 것이지만, 
    복잡한 contstructed 타입일지라도 마찬가지이다.

    @code
    Boolean *boolean;
    Integer *integer;

    boolean = ASN_New(Boolean, NULL);
    integer = ASN_New(Integer, NULL);

    ASN_Del(boolean);
    ASN_Del(integer);
    @endcode

    위의 예제에서 2번째 파라미터가 NULL값으로 주어지는 것에 주목하라.
    이 ASN 모듈에서는 별도의 decoding 인터페이스가 존재하지 않는다.
    Decoding을 하기 위해서는 위의 예제에서 NULL대신에 ASNBuf를 넘겨 주면,
    ASN_New에서 decoding된 값을 가지는 object를 생성한다.
    다음은 그 예제이다. (TestASN 이라는 ASN.1 type이 정의되었다는 가정하에서)

    @code
    TestASN *tasn;
    ASNBuf *buf;  // suppose allocated and set

    tasn = ASN_New(TestASN, buf);

    ASN_Del(tasn);
    @endcode

    @sa ASN_Del ASN_EncodeDER
    */
#define ASN_New(type, data) \
        (type*) ( (ASN* (*)(ASNDescriptor, ASNBuf*, ASNOption)) \
                  ((*(ASNDescriptor*)AD_##type)[0].param) ) \
                 (AD_##type, data, 0)

/** @ingroup ASN
    @define ASN_Del(a)
    @brief ASN 인스턴스을 delete하는 매크로

    어떤 ASN type에 할당된 힙 메모리를 해제하는 매크로이다.
    ASN type의 내부 del() 함수를 불러 이러한 작업을 수행한다.
    ASN_New()를 성공적으로 마친 모든 ASN.1 object들은 사용 후,
    반드시, ASN_Del()과정을 거쳐 할당된 메모리를 free하도록 한다.
    */
#define ASN_Del(a)  _START { if(a) ((void (*)(ASN*)) (((ASN*)(a))->del)) \
                      ((ASN*)(a)); (a) = NULL; } _END

/** @ingroup ASN
    @brief ASN.1 DER 인코딩 함수
    @param data 인코딩될 정보가 담겨 있는 ASN Type 포인터

    DER 인코딩 함수이다.
    data의 정보를 읽어 이를 DER 인코딩한 후 그 내용이 저장된
    ASNBuf Type을 리턴한다.

    */
LIBSPEC_ME
ASNBuf* ASN_EncodeDER(const void *asnObj);

/** @ingroup ASN
    @define ASN_Copy(d, s)
    @brief ASN type 복사한다.

    동일한 type의 ASN object 두개가 있을 때,  하나에서 다른 하나로
    내용을 복사하는 매크로이다.
    ASN type의 내부 copy() 함수를 불러 이러한 작업을 수행한다.
    */
#define ASN_Copy(d, s)  (s) ? ( (int (*)(ASN*, ASN*)) ((ASN(s))->copy) ) (ASN(d),ASN(s)) : 0

/** @ingroup ASN
    @brief ASN type 하나와 동일한 ASN type을 새로 생성한다. 
    @param data Duplicate될 ASN type에 대한 포인터

    ASN.1 type과 완전히 동일한 새 type을 생성하는 duplicate 함수 이다.
    data와 같은 type의 ASN type을 생성한 후 원 data의 내용을
    그대로 새롭게 생성된 type에게 복사한다.
    새롭게 생성한 type의 포인터를 리턴한다.
    */
LIBSPEC_ME
ASN* ASN_Dup(const ASN* data);



/*****************************************************************************/
/**	@ingroup ASN
    @struct ASNSeqClass
    @brief ASN.1 SEQUENCE Type Class

    ASN.1 의 SEQUENCE type을 다루기 위한 구조체이다.
    */
typedef struct _ASNSeqClass {
  ASN   klass;    /**< ASN 에서 상속 */
  int   size;     /**< 멤버들의 갯수 */
  ASN **elements; /**< Encode/decode할 구조체 멤버들 */
} ASNSeqClass;

/**	@ingroup ASN
		@struct ASNSeq
		@brief ASN.1 SEQUENCE Type 
    */		
typedef struct _ASNSeq {
  ASNSeqClass klass;
  /* need some virtual members here */
} ASNSeq;

#define ASN_SEQ(a)  ((ASNSeq*)(a))

/** @ingroup ASN
		@brief Sequence Type 생성 및 디코딩 함수
		@param dsc 디스크립터
		@param buf 디코딩 버퍼 포인터
		@param option 옵션

		buf가 NULL일 경우 생성 함수이고, NULL이 아니면 디코딩 함수이다.
    */
LIBSPEC_ME
ASNSeq* ASNSeq_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief Sequence 멤버 중, optional 멤버 할당
    @param member [out] Sequence의 멤버 포인터의 주소값
    @param seq [in] Sequence의 포인터 

    Sequence의 멤버 중, optional 멤버는 ASN_New하여 생성할 시에 메모리에
    할당되지 않는다.(Decoding은 제외) 따라서, optional 멤버를 포함시킬
    경우에는 값을 설정하기 이전, 이 함수를 통하여 메모리를 할당한 다음
    사용하여야 한다.
    */
LIBSPEC_ME
ERT ASNSeq_NewOptional(ASN **opt, const ASNSeq *seq);

LIBSPEC_ME
ERT ASNSeq_NewSetOptional(ASN **opt, const ASNSeq *seq, const ASN *src);

LIBSPEC_ME
ERT ASNSeq_NewSetPOptional(ASN **opt, const ASNSeq *seq, ASN *src);

/** @ingroup ASN
    @brief Sequence 멤버 중, optional 멤버 메모리 해제
    @param member [out] Sequence의 멤버 포인터의 주소값
    @param seq [in] Sequence의 포인터 

    ASNSeq_NewOptional 혹은 Decoding을 통하여 어떠한 Sequence의 Optional
    멤버에 메모리가 할당되었을 경우, optional 멤버를 다시 제거하고자 할때,
    이 함수를 사용한다.
    */
LIBSPEC_ME
ERT ASNSeq_DelOptional(ASN **opt, const ASNSeq *seq);



/*****************************************************************************/
/**	@ingroup ASN
		@struct ASNSetClass
		@brief ASN.1 SET Type class
    */		
typedef struct _ASNSetClass {
  ASN   klass;    /**< ASN에서 상속 */
  int   size;     /**< 구조채 멤버들의 갯수 */
  ASN **elements; /**< Encode/decode할 구조체 멤버들 */
} ASNSetClass;

/**	@ingroup ASN
		@struct ASNSet
		@brief ASN.1 SET Type 
    */		
typedef struct _ASNSet {
  ASNSetClass klass;
  /* need some virtual members here */
} ASNSet;

#define ASN_SET(a)  ((ASNSet*)(a))

/* @ingroup ASN
  	@brief ASN.1 SET 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
    buf가 NULL일 경우 생성 함수이고, NULL이 아니면 디코딩 함수이다.
    */
LIBSPEC_ME
ASNSet* ASNSet_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief SET 멤버 중, optional 멤버 할당
    @param member [out] Set의 멤버 포인터의 주소값
    @param set [in] Set의 포인터 

    Set의 멤버 중, optional 멤버는 ASN_New하여 생성할 시에 메모리에
    할당되지 않는다.(Decoding은 제외) 따라서, optional 멤버를 포함시킬
    경우에는 값을 설정하기 이전, 이 함수를 통하여 메모리를 할당한 다음
    사용하여야 한다.
    */
LIBSPEC_ME
ERT ASNSet_NewOptional(ASN **member, const ASNSet *set);

LIBSPEC_ME
ERT ASNSet_NewSetOptional(ASN **opt, const ASNSet *set, const ASN *src);

LIBSPEC_ME
ERT ASNSet_NewSetPOptional(ASN **opt, const ASNSet *set, ASN *src);

/** @ingroup ASN
    @brief SET 멤버 중, optional 멤버 메모리 해제
    @param member [out] Set의 멤버 포인터의 주소값
    @param set [in] Set의 포인터 

    ASNSet_NewOptional 혹은 Decoding을 통하여 어떠한 Set의 Optional
    멤버에 메모리가 할당되었을 경우, optional 멤버를 다시 제거하고자 할때,
    이 함수를 사용한다.
    */
LIBSPEC_ME
ERT ASNSet_DelOptional(ASN **member, const ASNSet *set);



/*****************************************************************************/
/**	@ingroup ASN
		@struct ASNSeqofClass
		@brief ASN.1 SEQUENCE OF Type class
    */		
typedef struct _ASNSeqOfClass {
  ASN  klass;         /**< ASN 에서 상속 */
  int  alloc;         /**< elements가 담긴 버퍼의 할당 크기 */
  ASN *defaults[8];   /**< elements가 담길 기본 버퍼. 8개. */
} ASNSeqOfClass;
/* 거의 sequence of 에 들어가는 녀석들은 8개를 넘지 않는다.
 * 그러므로 기본 버퍼를 사용하는 것만으로도 대부분은 충분.
 * 8개를 넘어가면 새로 alloc해서 사용한다. */

/**	@ingroup ASN
		@struct ASNSeqOf
		@brief ASN.1 SEQUENCE OF Type
    */		
typedef struct _ASNSeqOf {
  ASNSeqOfClass klass;
  int           size;          /**< 현재 멤버 갯수 */
  ASN         **elements;      /**< Encode/decode할 구조체 멤버들 */
} ASNSeqOf;

#define ASN_SEQOF(a)  ((ASNSeqOf*)(a))

/* @ingroup ASN
  	@brief ASN.1 SEQUENCE OF 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNSeqOf 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNSeqOf 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNSeqOf* ASNSeqOf_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief SEQUENCE OF 타입에 element를 하나 추가한다.
    @param seqof [out] ASNSeqOf의 포인터
    @param asn [in] 추가할 element의 포인터

    ASNSeqOf에 element를 하나 추가한다. 물론, 추가될 asn은 seqof의
    내부 element 타입과 일치해야 할 것이다. 명시적으로 base class 격인
    ASN* 로 type casting 을 하여 사용하기 바란다.

    주의할 점은, Add할 시에 input인 element의 실제 value를 그대로 복사해
    넣는다는 점이다.  입력으로 준 asn element는 Add 한 이후에도 반드시
    ASN_Del()로 메모리에서 지워주어야만 한다.

    @sa ASNSeqOf_AddP
    */
LIBSPEC_ME
ERT ASNSeqOf_Add(ASNSeqOf *seqof, const ASN *asn);

/** @ingroup ASN
    @brief SEQUENCE OF 타입에 element를 하나 추가한다.
    @param seqof [out] ASNSeqOf의 포인터
    @param asn [in] 추가할 element의 포인터

    ASNSeqOf에 element를 하나 추가한다. 물론, 추가될 asn은 seqof의
    내부 element 타입과 일치해야 할 것이다. 명시적으로 base class 격인
    ASN* 로 type casting 을 하여 사용하기 바란다.

    주의할 점은, Add할 시에 input인 element의 포인터값만을 복사하고,
    실제 그 element의 value는 복사하지 않는다. 따라서, ASNSeqOf_AddP를
    사용할 때는, 그에 Add 된 개별 element는 메모리에 그대로 남아 있어야 한다.
    이를 ASN_Del()로 삭제하면 안된다.

    @sa ASNSeqOf_Add
    */
LIBSPEC_ME
ERT ASNSeqOf_AddP(ASNSeqOf *seqof, ASN *asn);

/** @ingroup ASN
    @brief SEQUENCE OF 타입에 element를 하나 제거한다.
    @param seqof [out] ASNSeqOf의 포인터
    @param asn [in] 제거할 element의 index

    ASNSeqOf에 element를 하나 제거한다. ASNSeqOf의 element들은 index를
    통하여 엑세스 된다. element를 하나 제거하려면, 원하는 element의
    index를 찾아서 이 함수를 통하여 제거한다.
    */
LIBSPEC_ME
ERT ASNSeqOf_Remove(ASNSeqOf *seqof, int index);

/** @ingroup ASN
    @brief SEQUENCE OF 타입을 재초기화 한다.
    @param seqof [in/out] ASNSeqOf의 포인터

    ASNSeqOf의 element를 모두 메모리 해제하고, element를 하나도 가지지 않은
    빈 SEQUENCE OF 타입으로 다시 초기화한다. 즉, ASN_Del() 과 ASN_New()를
    다시 한번씩 실행시킨 결과와 동일하다.
    */
LIBSPEC_ME
ERT ASNSeqOf_Reset(ASNSeqOf *seqof);



/*****************************************************************************/
/**	@ingroup ASN
		@struct ASNSetofClass
		@brief ASN.1 SET OF Type class
    */		
typedef struct _ASNSetOfClass {
  ASN  klass;         /**< ASN 에서 상속 */
  int  alloc;         /**< elements가 담긴 버퍼의 할당 크기 */
  ASN *defaults[8];   /**< elements가 담길 기본 버퍼. 8개. */
} ASNSetOfClass;

/* 거의 set of 에 들어가는 녀석들은 8개를 넘지 않는다.
 * 그러므로 기본 버퍼를 사용하는 것만으로도 대부분은 충분.
 * 8개를 넘어가면 새로 alloc해서 사용한다. */

/**	@ingroup ASN
		@struct ASNSetOf
		@brief ASN.1 SET OF Type 
    */		
typedef struct _ASNSetOf {
  ASNSetOfClass klass;
  int           size;          /**< 구조체 멤버의 갯수 */
  ASN         **elements;      /**< Encode/decode할 구조체 멤버들 */
} ASNSetOf;

#define ASN_SETOF(a)  ((ASNSetOf*)(a))

/* @ingroup ASN
  	@brief ASN.1 SET OF 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNSetOf 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNSetOf 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNSetOf* ASNSetOf_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief SET OF 타입에 element를 하나 추가한다.
    @param setof [out] ASNSetOf의 포인터
    @param asn [in] 추가할 element의 포인터

    ASNSetOf에 element를 하나 추가한다. 물론, 추가될 asn은 setof의
    실제 element 타입과 일치해야 할 것이다. 명시적으로 base class 격인
    ASN* 로 type casting 을 하여 사용하기 바란다.

    주의할 점은, Add할 시에 input인 element의 실제 value를 그대로 복사해
    넣는다는 점이다.  입력으로 준 asn element는 Add 한 이후에도 반드시
    ASN_Del()로 메모리에서 지워주어야만 한다.

    @sa ASNSetOf_AddP
    */
LIBSPEC_ME
ERT ASNSetOf_Add(ASNSetOf *setof, const ASN *asn);

/** @ingroup ASN
    @brief SET OF 타입에 element를 하나 추가한다.
    @param setof [out] ASNSetOf의 포인터
    @param asn [in] 추가할 element의 포인터

    ASNSetOf에 element를 하나 추가한다. 물론, 추가될 asn은 setof의
    실제 element 타입과 일치해야 할 것이다. 명시적으로 base class 격인
    ASN* 로 type casting 을 하여 사용하기 바란다.

    주의할 점은, Add할 시에 input인 element의 포인터값만을 복사하고,
    실제 그 element의 value는 복사하지 않는다. 따라서, ASNSetOf_AddP를
    사용하는 한, 그에 Add 된 개별 element는 메모리에 그대로 남아 있어야
    한다. 개별 element에 ASN_Del()을 쓰면 안된다.

    @sa ASNSetOf_Add
    */
LIBSPEC_ME
ERT ASNSetOf_AddP(ASNSetOf *setof, ASN *asn);

/** @ingroup ASN
    @brief SET OF 타입에 element를 하나 제거한다.
    @param setof [out] ASNSetOf의 포인터
    @param asn [in] 제거할 element의 index

    ASNSetOf에 element를 하나 제거한다. ASNSetOf의 element들은 index를
    통하여 엑세스 된다. element를 하나 제거하려면, 원하는 element의
    index를 찾아서 이 함수를 통하여 제거한다.
    */
LIBSPEC_ME
ERT ASNSetOf_Remove(ASNSetOf *setof, int index);

/** @ingroup ASN
    @brief SET OF 타입을 재초기화 한다.
    @param setof [in/out] ASNSetOf의 포인터

    ASNSetOf의 element를 모두 메모리 해제하고, element를 하나도 가지지 않은
    빈 SET OF 타입으로 다시 초기화한다. 즉, ASN_Del() 과 ASN_New()를
    다시 한번씩 실행시킨 결과와 동일하다.
    */
LIBSPEC_ME
ERT ASNSetOf_Reset(ASNSetOf *setof);



/******************************************************************************
 *  ASN.1 Choice 
 */
/**	@ingroup ASN
		@struct ASNChoiceClass
		@brief ASN.1 CHOICE Type class
    */		
typedef struct _ASNChoiceClass {
  ASN      klass;    /**< ASN 에서 계승 */
} ASNChoiceClass;


/**	@ingroup ASN
		@struct ASNChoice
		@brief ASN.1 CHOICE Type 
    */		
typedef struct _ASNChoice {
  ASNChoiceClass klass;
  int            select;  /**< 선택된 ASN의 번호 */
  ASN           *choice;  /**< 선택된 ASN type에 대한 포인터 */
} ASNChoice;

#define ASN_CHOICE(a)  ((ASNChoice*)(a))

/* @ingroup ASN
  	@brief ASN.1 CHOICE 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNChoice 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNChoice 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
*/
LIBSPEC_ME
ASNChoice* ASNChoice_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief CHOICE 타입의 element 선택
    @param choice [out] ASNChoice 타입의 포인터
    @param select [in] element의 select 값, 첫번째가 1번

    ASNChoice 타입의 element를 선택하는 함수이다. 선택한다는 말은 Choice
    대상이 되는 element들 중에서, select가 가리키는 번째의 element를
    생성하고 ASNChoice 타입이 이 element를 가지고 있음을 세팅하는 의미이다.
    따라서, 이 함수를 실행하고 난 다음, 그 element의 값을 세팅하여야
    할 것이다.
    */
LIBSPEC_ME
ERT ASNChoice_Select(ASNChoice* choice, int select);



/******************************************************************************
 
                    Class를 갖지 않는 ASN 타입들
 
 *****************************************************************************/



/*****************************************************************************/
/**	@ingroup ASN
    @struct ASNBool
    @brief ASN.1 Boolean
  
    ASN.1의 Boolean type
    */
typedef struct _ASNBool {
  ASNClass      klass;
  unsigned char  data;  /**< 1이면 true, 0이면 false */
} ASNBool;

#define ASN_BOOL(a)  ((ASNBool*)(a))

/* @ingroup ASN 
    @param dsc Type 디스크립터
    @param data ASNBuf 포인터
  	@param option Type의 옵션
    
    ASN.1의 Boolean type 생성 및 디코딩 함수
  	1. data가 NULL일 경우는 Boolean type을 생성해 리턴한다.
  	2. data가 NULL이 아닐 경우는 디코딩된 Boolean type을 리턴한다.
  	3. option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNBool* ASNBool_New(ASNDescriptor dsc, ASNBuf* data, ASNOption option);

/** @ingroup ASN
    @param target ASNBool type 포인터
    @param in Boolean type에 셋팅할 값
    @ret SUCCESS, FAIL

    ASN.1의 Boolean type Set 함수
    */
LIBSPEC_ME
ERT ASNBool_Set(ASNBool *target, int in);

/** @ingroup ASN
    @param source ASNBool type 포인터
    @ret TRUE 1, FALSE 0
    
    ASN.1의 Boolean type Get 함수
    */
LIBSPEC_ME
int ASNBool_Get(const ASNBool *source);



/*****************************************************************************/
/** @ingroup ASN
    @def ASN_MAX_INT_LEN
    @brief ASNInt의 최대 크기

    ASNInt가 저장할 수 있는 최대 버퍼 크기이다. 즉, 512바이트가 한계이다.
    */
#define ASN_MAX_INT_LEN  512

/** @ingroup ASN
    @struct ASNInt
    @brief  ASN.1 Integer
  
    ASN.1의 Integer type
    */
typedef struct _ASNInt {
  ASNClass klass;
  int       len;                     /**< integer의 byte 수 */
  char      data[ASN_MAX_INT_LEN];  /**< 실제 integer data */
} ASNInt;
/* NOTE : data의 크기가 512byte이므로 512*8=4096 bit 이상의 정수는 표현 못함 */

#define ASN_INT(a)  ((ASNInt*)(a))

/* @ingroup ASN
  	@param dsc Type 디스크립터
    @param data ASNBuf 포인터
  	@param option Type 옵션
    
    ASN.1의 Integer type 생성 및 디코딩 함수
  	1. data가 NULL일 경우는 Integer type을 생성해 리턴한다.
  	2. data가 NULL이 아닐 경우는 디코딩된 Integer type을 리턴한다.
  	3. option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNInt* ASNInt_New(ASNDescriptor dsc, ASNBuf* data, ASNOption option);

/** @ingroup ASN
  	@param in ASNInt 포인터
    @param data 할당할 C int type의 데이터
    @ret SUCCESS, FAIL 

    ASN.1의 Integer type Set 함수.
    int 값으로 부터 ASNInt를 Set한다.
    */
LIBSPEC_ME
ERT ASNInt_SetInt(ASNInt *target, int in);

#define ASNInt_SetByInt(a, b) ASNInt_SetInt(a, b)

/** @ingroup ASN
  	@param data 읽어온 데이터 값이 저장될 C int type을 가리키는 포인터 
    @param in ASNInt 포인터 
    @ret SUCCESS, FAIL 
  
    ASN.1의 Integer type Get 함수
    ASNInt로부터 integer값을 Get한다.  ASNInt는 512바이트까지의 정수를
    저장할 수 있지만 int는 일반적으로 4바이트이므로 만약, ASNInt에 저장된
    값이 4바이트를 초과하면 FAIL을 리턴하게 된다.
    */
LIBSPEC_ME
ERT ASNInt_GetInt(int *out, const ASNInt *source);

#define ASNInt_GetByInt(a, b) ASNInt_GetInt(a, b)

/** @ingroup ASN
    @param target ASNInt 포인터 
  	@param in Integer를 표현하는 문자열을 가리키는 포인터
    @ret 저장에 사용된 바이트 버퍼의 크기, 실패시 FAIL
  
    ASN.1의 Integer type Set 함수.
    "0123456ABCDE"와 같이 사람이 읽을 수 있는 형태의 문자열로 값을 지정한다.
    */
LIBSPEC_ME
int ASNInt_SetStr(ASNInt *target, const char* in);

#define ASNInt_SetByStr(a, b) ASNInt_SetStr(a, b)

/** @ingroup ASN
  	@param out Integer를 표현하는 문자열을 가리키는 포인터
    @param maxLen out 버퍼의 최대 크기
    @param source ASNInt 포인터 
    @ret out에 출력된 스트링의 길이, 실패시 FAIL
  
    ASN.1의 Integer type Get 함수.
    "0123456ABCDE"와 같이 사람이 읽을 수 있는 형태의 문자열로 Integer 값을
    얻는다.
    */
LIBSPEC_ME
int ASNInt_GetStr(char *out, int maxLen, const ASNInt *source);

#define ASNInt_GetByStr(a, b) ASNInt_GetStr(a, b)

/** @ingroup ASN
    @param target ASNInt 포인터 
    @param in 바이너리 값이 저장된 버퍼의 포인터
    @param inLen 바이너리 값의 바이트 단위 길이
    @ret 저장에 사용된 버퍼의 크기, 실패시 FAIL

    ASN.1의 Integer type Set 함수.
    바이너리값을 그대로 ASNInt로 가져온다.
    */
LIBSPEC_ME
int ASNInt_SetBin(ASNInt *target, const char *in, int inLen);

#define ASNInt_SetByBin(a, b, c) ASNInt_SetBin(a, b, c)

/** @ingroup ASN
  	@param out 바이너리값을 저장할 버퍼를 가리키는 포인터
    @param maxLen out 버퍼의 최대 크기
    @param source ASNInt 포인터 
    @ret out에 출력된 바이너리값의 바이트 단위 길이, 실패시 FAIL
    
    ASN.1의 Integer type Get 함수.
    ASNInt로부터 바이너리값을 버퍼로 복사한다.
    */
LIBSPEC_ME
int ASNInt_GetBin(char *out, int maxLen, const ASNInt *source);

#define ASNInt_GetByBin(a, b, c) ASNInt_GetBin(a, b, c)


/*****************************************************************************/
/** @ingroup ASN
 *	@def ASN_MAX_BIT_LEN
 *	@brief ASNBitStr의 최대 바이트 크기.

    ASNBitStr이 저장할 수 있는 최대 버퍼 사이즈이다. 즉, 최대 2048바이트까지
    저장할 수 있다.
 **/
#define ASN_MAX_BIT_LEN  2048

/** @ingroup ASN
 *	@struct ASNBitStr
 *  @brief  ASN.1 BIT STRING Type
 **/

typedef struct _ASNBitStr {
  ASNClass klass;

  int       bitLen;	/**< bits length */
  int       len; /**< byte length(BitString의 byte 크기 + 패딩정보바이트)  */
  char      data[ASN_MAX_BIT_LEN]; /**< 실제 BIT STRING data */ 

} ASNBitStr;

#define ASN_BITSTR(a)  ((ASNBitStr*)(a))

/* 패딩 길이만큼 0으로 padding */
#define PadWithZero(a,b) ((a) = (a) >> (b)); \
        ((a) = (a) << (b));

/* @ingroup ASN
  	@brief ASN.1 BIT STRING 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNBitStr 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNBitStr 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNBitStr* ASNBitStr_New(ASNDescriptor dsc, ASNBuf* data, ASNOption option);

/** @ingroup ASN
    @brief ASN.1 BIS STRING 타입 Set 함수
    @param in 데이터가 Setting될 ASNBitStr Type 포인터 
    @param data 입력 데이터 포인터
    @param bit_len 입력 데이터의 비트 길이
    @ret 처리된 데이터의 비트 길이가 리턴된다. 실패시 FAIL

    패딩 정보가 첫번째 content octet에 기록된다.
    */

LIBSPEC_ME
int ASNBitStr_Set(ASNBitStr *in, const char *data, int bitLen);

/**	@ingroup ASN
    @brief ASN.1 BIT STRING 타입 Get 함수
    @param data [out] 읽어 온 데이터가 할당될 버퍼를 가리키는 포인터
    @param max_bit_len [in] data가 가리키는 버퍼의 최대 비트 길이
    @param in [in] ASNBitStr 타입 포인터 
    @ret data에 출력된 비트 길이, 실패시 FAIL

    읽어 온 데이터의 비트 길이가 리턴된다.
    */
LIBSPEC_ME
int ASNBitStr_Get(char *data, int maxBitLen, const ASNBitStr *in);

/** @ingroup ASN
    @brief ASNBitStr 인스턴스 Set 함수
    @param target 설정 대상인 ASNBitStr의 포인터
    @param asnBuf ASNBuf의 포인터
    @ret 처리된 바이트 길이, 실패시 FAIL

    ASNBuf에 저장되어 있는 바이너리값을 ASNBitStr로 가져온다.
    bit length는 항상 ASNBuf에 저당된 바이트 단위 길이의 8배가 된다.
    */
LIBSPEC_ME
int ASNBitStr_SetASNBuf(ASNBitStr *in, const ASNBuf *asnBuf);

/** @ingroup ASN
    @brief ASNBitStr 인스턴스 Get 함수
    @param source ASNBitStr 포인터

    ASNBitStr에 저장되어 있는 스트링값을 ASNBuf로 설정하여 리턴한다.
    LSB부터 채워진다. 예를 들어 100011001이라는 9bit의 값을 읽어오면,
    data[0] = 0x01, data[1] = 0x19 가 된다.
    리턴된 ASNBuf는 ASNBuf_Del을 사용하여 메모리를 해제하여야 한다.
    */
LIBSPEC_ME
ASNBuf* ASNBitStr_GetASNBuf(const ASNBitStr *in);



/*****************************************************************************/
/** @ingroup ASN
		@struct ASNStr
 		@brief  Base of ASN.1 String Type

    ASNStr은 ASNOctStr, ASNPrintStr, ASNUTF8Str, ASNIA5Str, ASNVisibleStr,
    ASNBMPStr의 base type이다. ASN.1의 string 형태의 basic type들 중에서,
    BitString을 제외하고는 이 모듈에서 구현되는 방식이 동일하므로 ASNStr
    하나만을 정의하고, 이 structure를 나머지 string type의 이름으로 
    rename 하여 (#define을 통해서) 사용하고 있다.

    이 모듈 사용자는 ASNStr을 직접 쓰는 것보다는 어떤 string type인지를
    명시적으로 표현하기 위해서 rename된 원래 string type 이름의 인터페이스를
    사용하기 바란다.
    */
typedef struct _ASNStr {
  ASNClass klass;
  int       len; /**< data byte length */
  char     *data; /**< 실제 OCTET STRING data */
} ASNStr;

LIBSPEC_ME
ASNStr* ASNStr_Safe_New(ASNDescriptor dsc, ASNBuf* buf, ASNOption option);

LIBSPEC_ME
ASNStr* ASNStr_New(ASNDescriptor dsc, ASNBuf* buf, ASNOption option);

/** @ingroup ASN
    @brief ASNStr 인스턴스 Set 함수
    @param target 값을 설정할 ASNStr의 포인터
    @param in 설정할 string를 저장하고 있는 버퍼의 포인터
    @param len string의 바이트 단위 길이
    @ret 설정한 string의 바이트 단위 길이

    String을 저장하고 있는 버퍼와 그 string의 바이트 단위 길이를 입력받아
    ASNStr의 값을 설정한다. 내부적으로는 단지 입력된 길이만을 보고 길이만큼만
    값을 복사한다.

    이 모듈 사용자는 이 인터페이스를 직접 쓰는 것 보다는 어떤 string type인지를
    명시적으로 표현하기 위해서 rename된 원래 string type 이름의 인터페이스를
    사용하기 바란다.
    */
LIBSPEC_ME
int ASNStr_Set(ASNStr *target, const char *in, int len);

/** @ingroup ASN
    @brief ASNStr 인스턴스 Get 함수
    @param out string이 저장될 버퍼의 포인터
    @param maxLen 버퍼에 저장할 수 있는 string의 최대 바이트 단위 길이
    @param source 값을 얻어올 ASNStr의 포인터
    @ret value의 바이트 단위 길이

    ASNStr로 부터 그 값을 버퍼로 읽어온다. maxLen이 저장하고 있는 string의
    길이보다 클 경우에는 string의 값 자체를 복사한 다음, 그 다음 한 바이트는
    0으로 설정한다. maxLen이  저장하고 있는 string의 길이보다 작을 경우는
    -1를 리턴한다. 만약, maxLen과 string의 길이가 정확히 일치하는 경우에는
    string 값 자체만을 복사한다.
    
    이 모듈 사용자는 이 인터페이스를 직접 쓰는 것 보다는 어떤 string type인지를
    명시적으로 표현하기 위해서 rename된 원래 string type 이름의 인터페이스를
    사용하기 바란다.
    */
LIBSPEC_ME
int ASNStr_Get(char *out, int maxLen, const ASNStr *source);

/** @ingroup ASN
    @brief ASNStr 인스턴스 Set 함수
    @param target 설정 대상인 ASNStr의 포인터
    @param asnBuf ASNBuf의 포인터
    @ret 처리된 바이트 길이, 실패시 FAIL

    ASNBuf에 저장되어 있는 바이너리값을 ASNStr로 가져온다.
    */
LIBSPEC_ME
int ASNStr_SetASNBuf(ASNStr *target, const ASNBuf *asnBuf);

/** @ingroup ASN
    @brief ASNStr 인스턴스 Get 함수
    @param source ASNStr 포인터

    ASNStr에 저장되어 있는 스트링값을 ASNBuf로 설정하여 리턴한다.
    리턴된 ASNBuf는 ASNBuf_Del을 사용하여 메모리를 해제하여야 한다.
    */
LIBSPEC_ME
ASNBuf* ASNStr_GetASNBuf(const ASNStr *source);

/** @ingroup ASN
    @param str1 비교하고자 하는 첫번째 스트링
    @param str2 비교하고자 하는 두번째 스트링
    @return str1이 str2보다 크면 양수을, 같으면 0을, 작으면 음수을 출력한다.

    ASNStr에 포함된 두개의 데이터를 비교한다. 내부적으로 memcmp를 사용하여
    비교한다. 서로 길이가 다른 스트링에 대한 비교는 비교 가능한 
    길이(최소 길이)까지의 비교 결과를 우선시 한다.

    이 모듈 사용자는 이 인터페이스를 직접 쓰는 것 보다는 어떤 string type인지를
    명시적으로 표현하기 위해서 rename된 원래 string type 이름의 인터페이스를
    사용하기 바란다.
    */
LIBSPEC_ME
int     ASNStr_Cmp(const ASNStr *str1, const ASNStr *str2);



/*****************************************************************************/
/** @typedef ASNOctStr
    @ingroup ASN

    ASN.1의 string type들의 base type인 ASNStr로 부터 OctetString을
    정의. 즉, ASNOctStr과 ASNStr은 동일하나, 이 모듈 사용할 시에는
    string type들을 명시적으로 구분하기 위하여 ASNOctStr(혹은 OctetString)
    을 사용하기 바란다.

    나머지 PrintableString, UTF8String, IA5String, VisibleString,
    BMPString도 마찬가지이다.

    @sa PrintableString UTF8String IA5String VisibleString BMPString
    */
/** @typedef ASNPrintStr
    @ingroup ASN

    ASN.1의 string type들의 base type인 ASNStr로 부터 PrintableString을
    정의.
    자세한 사항은 OctetString 절을 참조하기 바란다.

    @sa OctetString
    */
/** @typedef ASNUTF8Str
    @ingroup ASN

    ASN.1의 string type들의 base type인 ASNStr로 부터 UTF8String을
    정의.
    자세한 사항은 OctetString 절을 참조하기 바란다.

    @sa OctetString
    */
/** @typedef ASNIA5Str
    @ingroup ASN

    ASN.1의 string type들의 base type인 ASNStr로 부터 IA5String을
    정의.
    자세한 사항은 OctetString 절을 참조하기 바란다.

    @sa OctetString
    */
/** @typedef ASNVisibleStr
    @ingroup ASN

    ASN.1의 string type들의 base type인 ASNStr로 부터 VisibleString을
    정의.
    자세한 사항은 OctetString 절을 참조하기 바란다.

    @sa OctetString
    */
/** @typedef ASNBMPStr
    @ingroup ASN

    ASN.1의 string type들의 base type인 ASNStr로 부터 BMPString을
    정의.
    자세한 사항은 OctetString 절을 참조하기 바란다.

    @sa OctetString
    */
typedef ASNStr ASNOctStr;
typedef ASNStr ASNPrintStr;
typedef ASNStr ASNUTF8Str;
typedef ASNStr ASNIA5Str;
typedef ASNStr ASNVisibleStr;
typedef ASNStr ASNBMPStr;

#define ASN_OCTSTR(a)     ((ASNStr*)(a))
#define ASN_PRINTSTR(a)   ((ASNPrintStr*)(a))
#define ASN_UTF8STR(a)    ((ASNUTF8Str*)(a))
#define ASN_IA5STR(a)     ((ASNIA5Str*)(a))
#define ASN_VISIBLESTR(a) ((ASNVisibleStr*)(a))
#define ASN_BMPSTR(a)     ((ASNBMPStr*)(a))

#ifdef ASN_SAFE
#define ASNOctStr_Safe_New     ASNStr_Safe_New
#endif

#define ASNOctStr_New     ASNStr_New
#define ASNPrintStr_New   ASNStr_New
#define ASNUTF8Str_New    ASNStr_New
#define ASNIA5Str_New     ASNStr_New
#define ASNVisibleStr_New ASNStr_New
#define ASNBMPStr_New     ASNStr_New

/** @ingroup ASN
    @def ASNOctStr_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set을 ASNOctStr을 위한 ASNOctStr_Set으로 rename
    */
/** @ingroup ASN
    @def ASNOctStr_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get을 ASNOctStr을 위한 ASNOctStr_Get으로 rename
    */
/** @ingroup ASN
    @def ASNPrintStr_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set을 ASNPrintStr을 위한 ASNPrintStr_Set으로 rename
    */
/** @ingroup ASN
    @def ASNPrintStr_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get을 ASNPrintStr을 위한 ASNPrintStr_Get으로 rename
    */
/** @ingroup ASN
    @def ASNUTF8Str_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set을 ASNUTF8Str을 위한 ASNUTF8Str_Set으로 rename
    */
/** @ingroup ASN
    @def ASNUTF8Str_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get을 ASNUTF8Str을 위한 ASNUTF8Str_Get으로 rename
    */
/** @ingroup ASN
    @def ASNIA5Str_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set을 ASNIA5Str을 위한 ASNIA5Str_Set으로 rename
    */
/** @ingroup ASN
    @def ASNIA5Str_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get을 ASNIA5Str을 위한 ASNIA5Str_Get으로 rename
    */
/** @ingroup ASN
    @def ASNVisibleStr_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set을 ASNVisibleStr을 위한 ASNVisibleStr_Set으로 rename
    */
/** @ingroup ASN
    @def ASNVisibleStr_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get을 ASNVisibleStr을 위한 ASNVisibleStr_Get으로 rename
    */
/** @ingroup ASN
    @def ASNBMPStr_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set을 ASNBMPStr을 위한 ASNBMPStr_Set으로 rename
    */
/** @ingroup ASN
    @def ASNBMPStr_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get을 ASNBMPStr을 위한 ASNBMPStr_Get으로 rename
    */
#define ASNOctStr_Set(a, b, c)        ASNStr_Set((a), (b), (c))
#define ASNOctStr_Get(a, b, c)        ASNStr_Get((a), (b), (c))
#define ASNOctStr_SetASNBuf(a, b)     ASNStr_SetASNBuf((a), (b))
#define ASNOctStr_GetASNBuf(a)        ASNStr_GetASNBuf((a))
#define ASNOctStr_Cmp(a, b)           ASNStr_Cmp((a), (b))
#define ASNPrintStr_Set(a, b, c)      ASNStr_Set((a), (b), (c))
#define ASNPrintStr_Get(a, b, c)      ASNStr_Get((a), (b), (c))
#define ASNPrintStr_SetASNBuf(a, b)   ASNStr_SetASNBuf((a), (b))
#define ASNPrintStr_GetASNBuf(a)      ASNStr_GetASNBuf((a))
#define ASNPrintStr_Cmp(a, b)         ASNStr_Cmp((a), (b))
#define ASNUTF8Str_Set(a, b, c)       ASNStr_Set((a), (b), (c))
#define ASNUTF8Str_Get(a, b, c)       ASNStr_Get((a), (b), (c))
#define ASNUTF8Str_SetASNBuf(a, b)    ASNStr_SetASNBuf((a), (b))
#define ASNUTF8Str_GetASNBuf(a)       ASNStr_GetASNBuf((a))
#define ASNUTF8Str_Cmp(a, b)          ASNStr_Cmp((a), (b))
#define ASNIA5Str_Set(a, b, c)        ASNStr_Set((a), (b), (c))
#define ASNIA5Str_Get(a, b, c)        ASNStr_Get((a), (b), (c))
#define ASNIA5Str_SetASNBuf(a, b)     ASNStr_SetASNBuf((a), (b))
#define ASNIA5Str_GetASNBuf(a)        ASNStr_GetASNBuf((a))
#define ASNIA5Str_Cmp(a, b)           ASNStr_Cmp((a), (b))
#define ASNVisibleStr_Set(a, b, c)    ASNStr_Set((a), (b), (c))
#define ASNVisibleStr_Get(a, b, c)    ASNStr_Get((a), (b), (c))
#define ASNVisibleStr_SetASNBuf(a, b) ASNStr_SetASNBuf((a), (b))
#define ASNVisibleStr_GetASNBuf(a)    ASNStr_GetASNBuf((a))
#define ASNVisibleStr_Cmp(a, b)       ASNStr_Cmp((a), (b))
#define ASNBMPStr_Set(a, b, c)        ASNStr_Set((a), (b), (c))
#define ASNBMPStr_Get(a, b, c)        ASNStr_Get((a), (b), (c))
#define ASNBMPStr_SetASNBuf(a, b)     ASNStr_SetASNBuf((a), (b))
#define ASNBMPStr_GetASNBuf(a)        ASNStr_GetASNBuf((a))
#define ASNBMPStr_Cmp(a, b)           ASNStr_Cmp((a), (b))



/*****************************************************************************/
/** @ingroup ASN
  	@struct ASNEnum
    @brief ASN.1 Enumerate Type
    */
typedef struct _ASNEnum {
  ASNClass     klass;
  unsigned char value;
} ASNEnum;

#define ASN_ENUM(a)  ((ASNEnum*)(a))

/* @ingroup ASN
  	@brief ASN.1 Enum 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNEnum 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNEnum 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNEnum* ASNEnum_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

#define ASNEnum_Set(enumerate, in) \
        ((ASNEnum*)enumerate)->value = (unsigned char)in;
#define ASNEnum_Get(enumerate) \
        (int)(((ASNEnum*)enumerate)->value)



/*****************************************************************************/
/**	@ingroup ASN
		@struct ASNNull
		@brief ASN.1 NULL Type 
    */		
typedef struct _ASNNull {
  ASNClass    klass;
} ASNNull;

#define ASN_NULL(a)  ((ASNNull*)(a))

/* @ingroup ASN
  	@brief ASN.1 NULL 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNNull 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
    ASNNull 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNNull* ASNNull_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/* ASNNull은 set/get이 필요없다. */



/*****************************************************************************/
#define ASN_MAX_UTC_LEN  24
/**	@ingroup ASN
		@struct ASNUTCTime
		@brief ASN.1 UTCTime Type 
    */		
typedef struct _ASNUTCTime {
  ASNClass   klass;
  struct tm  value;  /**< gmtime */
  char       string[ASN_MAX_UTC_LEN+1];  /**< pritable & der data */
} ASNUTCTime;

typedef ASNUTCTime UTCTime;

#define ASN_UTCTIME(a)  ((ASNUTCTime*)(a))

/* @ingroup ASN
  	@brief ASN.1 UTCTime 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNUTCTime 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNUTCTime 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNUTCTime* ASNUTCTime_New(ASNDescriptor dsc, ASNBuf *data, ASNOption option);

/** @ingroup ASN
    @def ASNUTCTime_Set
    @sa ASNUTCTime_Get
    ASNUTCTime을 설정하는 매크로이다. struct tm 타입을 입력 받아 ASNUTCTime인
    utime을 설정한다.
    */ 
#define ASNUTCTime_Set(utime, in) \
           memcpy(&((ASNUTCTime*)utime)->value, in, sizeof(struct tm))

LIBSPEC_ME
int ASNUTCTime_SetByTimeT(ASNUTCTime* utime, time_t in);

/** @ingroup ASN
    @def ASNUTCTime_Get
    @sa ASNUTCTime_Set
    ASNUTCTime 타입인 utime으로부터 struct tm으로 값을 읽어온다. 
    */ 
#define ASNUTCTime_Get(out, utime)  \
           memcpy(out, &((ASNUTCTime*)utime)->value, sizeof(struct tm))

LIBSPEC_ME
int ASNUTCTime_GetByTimeT(time_t *out, const ASNUTCTime* utime);


/*****************************************************************************/
#define ASN_MAX_GEN_LEN  24
/**	@ingroup ASN
		@struct ASNGenTime
		@brief ASN.1 GeneralizedTime Type
    */		
typedef struct _ASNGenTime {
  ASNClass   klass;
  struct tm  value;  /**< gmtime */
  char       string[ASN_MAX_GEN_LEN+1];  /**< pritable & der data */
} ASNGenTime;

typedef ASNGenTime GeneralizedTime;

#define ASN_GENTIME(a)  ((ASNGenTime*)(a))

/* @ingroup ASN
  	@brief ASN.1 GeneralizedTime 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNGenTime 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNGenTime 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNGenTime* ASNGenTime_New(ASNDescriptor dsc, ASNBuf *data, ASNOption option);

/** @ingroup ASN
    @def ASNGenTime_Set
    @sa ASNGenTime_Get
    ASNGenTime을 설정하는 매크로이다. struct tm 타입을 입력 받아 ASNGenTime인
    utime을 설정한다.
    */ 
#define ASNGenTime_Set(utime, in)\
           memcpy(&((ASNGenTime*)utime)->value, in, sizeof(struct tm))

#define ASNGenTime_SetByTimeT(utime, in) \
    ASNUTCTime_SetByTimeT((ASNUTCTime*) utime, in)

/** @ingroup ASN
    @def ASNGenTime_Get
    @sa ASNGenTime_Set
    ASNGenTime 타입인 utime으로부터 struct tm으로 값을 읽어온다. 
    */ 
#define ASNGenTime_Get(out, utime) \
           memcpy(out, &((ASNGenTime*)utime)->value, sizeof(struct tm))

#define ASNGenTime_GetByTimeT(out, utime) \
    ASNUTCTime_GetByTimeT(out, (ASNUTCTime*) utime)

/** @ingroup ASN
    @param out
    @param in
    @sa LocaltimeToGmtime

    in으로 입력된 local time을 general time으로 변환 후 out으로 출력한다.
    */
LIBSPEC_ME
void GmtimeToLocaltime(struct tm *out, const struct tm *in);

/** @ingroup ASN
    @param out
    @param in

    in으로 입력된 general time을 local time으로 변환 후 out으로 출력한다.
    */
LIBSPEC_ME
void LocaltimeToGmtime(struct tm *out, const struct tm *in);



/*****************************************************************************/
/**	@ingroup ASN
    @struct ASNAny
    @brief ASN.1 ANY type
    */		
typedef struct _ASNAny {
  ASNClass   klass;
  int        len;
  char      *data;
} ASNAny;

#define ASN_ANY(a)  ((ASNAny*)(a))

/* @ingroup ASN
  	@brief ASN.1 ANY 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNAny 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNAny 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
 */
LIBSPEC_ME
ASNAny* ASNAny_New(ASNDescriptor dsc, ASNBuf *data, ASNOption option);

/** @ingroup ASN
    @brief ASN.1 ANY 타입 Set 함수
    @param in 데이터가 Setting될 ASNAny Type 포인터 
    @param inBuf 입력 ASNBuf의 포인터
    @ret 처리된 데이터의 바이트 길이가 리턴된다. 실패시 FAIL

    */
LIBSPEC_ME
int ASNAny_Set(ASNAny *target, const ASNBuf *inBuf);

LIBSPEC_ME
ERT ASNAny_SetASN(ASNAny *target, const ASN *asn);

/**	@ingroup ASN
    @brief ASN.1 ANY 타입 Get 함수
    @param data 읽어 온 데이터가 할당될 버퍼를 가리키는 포인터
    @param max_len data가 가리키는 버퍼의 최대 바이트 길이
    @param in ASNAny 타입 포인터 
    @ret 읽어 온 데이터의 바이트 길이가 리턴된다. 실패시 FAIL

    출력된 ASNBuf는 함수 내부에서 메모리에 할당. ASNBuf_Del을 사용하여
    메모리를 해제하여야 한다.
    */
LIBSPEC_ME
int ASNAny_Get(ASNBuf **outBuf, const ASNAny *source);

#define ASNAny_GetASN(pasn, source, desc) \
        _ASNAny_GetASN((pasn), (source), (AD_##desc))

LIBSPEC_ME
ERT _ASNAny_GetASN(ASN **pasn, const ASNAny *source, ASNDescriptor desc);

/*****************************************************************************/
/**	@ingroup ASN
  @struct ASNOid
  @brief ASN.1 OBJECT IDENTIFIER Type 
    */		
typedef struct _ASNOid {
  ASNClass  klass;
  Oid        oid;
  Nid        nid;
  char       der[64];  /* der buffer */
} ASNOid;

#define ASN_OID(a)  ((ASNOid*)(a))

/* @ingroup ASN
  	@brief ASN.1 OBJECT IDENTIFIER 타입 생성 및 디코딩 함수
  	@param dsc Type 디스크립터
  	@param data 인코딩 정보를 가리키는 ASNBuf 포인터
  	@param option Type 옵션
  
  	data가 NULL일 경우에는 이 함수는 ASNOid 타입을 
  	생성해 그 포인터를 리턴한다. 
  	data가 NULL이 아닐 경우 이 함수는 디코딩 버퍼(data)의 내용이 디코딩된
  	ASNOid 타입을 생성해 리턴한다.
  	option은 인코딩/디코딩 시 같은 값이 입력되어야 한다.
    */
LIBSPEC_ME
ASNOid* ASNOid_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief ASN.1 OBJECT IDENTIFIER 타입 Set 함수
    @param aOid 설정 대상 ASNOid 포인터
    @param oid Oid 포인터

    Oid로 ASNOid를 설정하는 함수이다.
    */
LIBSPEC_ME
ERT ASNOid_Set(ASNOid *aOid, const Oid *oid);

/** @ingroup ASN
    @brief ASN.1 OBJECT IDENTIFIER 타입 Get 매크로

    ASNOid(ansoid)로부터 Oid(out)를 가져온다.
    */
#define ASNOid_Get(out, asnoid) Oid_Copy((out), &(((ASNOid*)(asnoid))->oid))

/** @ingroup ASN
    @brief ASN.1 OBJECT IDENTIFIER 타입 Set 함수
    @param aOid 설정 대상 ASNOid 포인터
    @param nid Nid 

    Nid로 ASNOid를 설정하는 함수이다.
    */
LIBSPEC_ME
ERT ASNOid_SetByNid(ASNOid *aOid, Nid nid);

/** @ingroup ASN
    @brief ASN.1 OBJECT IDENTIFIER 타입 Get 매크로

    ASNOid(ansoid)로부터 Nid를 리턴한다.
    */
#define ASNOid_GetNid(asnoid)  (asnoid->nid)



/******************************************************************************
 * Some types used frequently
 */

/** AlgirithmIdentifier: SEQ 
 *  algorithm은 다음의 값들을 가질 수 있다.
 *    - NID_passwordBasedMac
 *    - NID_sha1WithRSAEncryption:
 *    - NID_sha1withRSASignature:
 *    - NID_dsa_with_sha1:
 *    - NID_kcdsaWithSHA1:
 *    - NID_kcdsa1WithSHA1:
 *    - NID_kcdsaWithHAS160:
 *    - NID_kcdsa1WithHAS160:
 *    - 그외(더 있으면 추가할 것..)
 */
typedef struct _AlgorithmIdentifier {
  ASNSeqClass       klass;
  ASNOid           *algorithm;
  ASNAny           *parameters;
} AlgorithmIdentifier;

/**	@ingroup ASN
    @brief AlgorithmIdentifier 타입의 Set 함수
    @param ai 내용을 지정할 AlgorithmIdentifier 타입의 포인터
    @param oid 지정된 AlgorithmIdentifier 타입이 가질 Oid의 포인터
    @param para  oid에 붙는 parameter의 포인터. NULL을 줄 수 있다.
    @ret SUCCESS, FAIL

    Oid와 그에 따르는 parameter를 지정하여 AlgorithmIdentifier의 값을
    set한다.  parameter에는 NULL을 줄 수 있다.  NULL이 입력될 경우 
    default값인 ASNNull의 인코딩값 "\x05\x00"을 넣게 된다.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_Set(AlgorithmIdentifier *ai, const Oid *oid, const ASNAny *para);

/**	@ingroup ASN
    @brief AlgorithmIdentifier 타입의 Set 함수
    @param ai 내용을 지정할 AlgorithmIdentifier 타입의 포인터
    @param nid 지정된 AlgorithmIdentifier 타입이 가질 Nid
    @param para  oid에 붙는 parameter의 포인터. NULL을 줄 수 있다.
    @ret SUCCESS, FAIL

    Oid 대신 Nid가 입력값인 걸 제외하면 AlgorithmIdentifier_Set과 동일하다.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_SetNid(AlgorithmIdentifier *ai, Nid nid, const ASNAny *para);

/**	@ingroup ASN
    @brief AlgorithmIdentifier 타입의 Set 함수
    @param ai 내용을 지정할 AlgorithmIdentifier 타입의 포인터
    @param nid 지정된 AlgorithmIdentifier 타입이 가질 Nid
    @param para  oid에 붙는 parameter의 포인터. NULL을 줄 수 있다.
    @ret SUCCESS, FAIL

    para 값의 타입이 ASN 인 것을 제외하면 AlgorithmIdentifier_SetNid 과 동일하다.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_SetByNid(AlgorithmIdentifier *ai, Nid nid, const ASN *para);

/**	@ingroup ASN
    @brief AlgorithmIdentifier 타입의 Get 함수
    @param oid 지정된 AlgorithmIdentifier 타입이 갖고 있는 Oid의 포인터
    @param para  oid에 붙는 parameter의 포인터. NULL을 줄 수 있다.
    @param ai 내용을 구할 AlgorithmIdentifier 타입의 포인터
    @ret SUCCESS, FAIL

    AlgorithmIdentifier 타입의 Oid와 그에 따르는 parameter를 값을
    구한다.  parameter에는 NULL을 줄 수 있다.  NULL이 입력될 경우 
    parameter의 값은 구하지 않는다.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_Get(Oid *oid, ASNAny *para, const AlgorithmIdentifier *ai);

/**	@ingroup ASN
    @brief AlgorithmIdentifier 타입의 Get 함수
    @param nid 지정된 AlgorithmIdentifier 타입이 갖고 있는 Nid
    @param para  oid에 붙는 parameter의 포인터. NULL을 줄 수 있다.
    @param ai 내용을 구할 AlgorithmIdentifier 타입의 포인터
    @ret SUCCESS, FAIL

    AlgorithmIdentifier 타입의 Nid와 그에 따르는 parameter를 값을
    구한다.  parameter에는 NULL을 줄 수 있다.  NULL이 입력될 경우 
    parameter의 값은 구하지 않는다.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_GetNid(Nid *nid, ASNAny *para, const AlgorithmIdentifier *ai);



/******************************************************************************
 * Renaming basic ASN.1 primitive types 
 */

/** @def Boolean
    @ingroup ASN
   
    rename ASNBool
    */
/** @def Integer
    @ingroup ASN
   
    rename ASNInt
    */
/** @def BitString
    @ingroup ASN
  
    rename ASNBitStr
    */
/** @def OctetString
    @ingroup ASN
   
    rename ASNOctStr
    */
/** @def PrintableString
    @ingroup ASN
   
    rename ASNPrintStr
    */
/** @def UTF8String
    @ingroup ASN
   
    rename ASNUTF8Str
    */
/** @def IA5String
    @ingroup ASN
   
    rename ASNIA5Str
    */
/** @def VisibleString
    @ingroup ASN
   
    rename ASNVisibleStr
    */
/** @def BMPString
    @ingroup ASN
   
    rename ASNBMPStr
    */
/** @def Enumerate
    @ingroup ASN
   
    rename ASNEnum
    */
/** @def Null
    @ingroup ASN
   
    rename ASNNull
    */
/** @def UTCTime
    @ingroup ASN
   
    rename ASNUTCTime
    */
/** @def GeneralizedTime
    @ingroup ASN
   
    rename ASNGenTime
    */
/** @def Any
    @ingroup ASN
   
    rename ASNAny
    */
#define  Boolean         ASNBool      
#define  Integer         ASNInt       
#define  BitString       ASNBitStr    
#define  OctetString     ASNOctStr    
#define  PrintableString ASNPrintStr  
#define  UTF8String      ASNUTF8Str   
#define  IA5String       ASNIA5Str    
#define  VisibleString   ASNVisibleStr
#define  BMPString       ASNBMPStr    
#define  Enumerate       ASNEnum      
#define  Null            ASNNull      
#define  UTCTime         ASNUTCTime   
#define  GeneralizedTime ASNGenTime   
#define  Any             ASNAny       



/******************************************************************************
 * Descriptor elements for Sequence, SequenceOf, Set, SetOf, and end of AD
 * Descriptor elements of other types must used in ASN.1 module
 * ADE stands for ASN.1 Descriptor Element
 */

#define ADE_Sequence   {(void*)ASNSeq_New,    CONS|UNIV|TAG_SEQ}
#define ADE_SequenceOf {(void*)ASNSeqOf_New,  CONS|UNIV|TAG_SEQOF}
#define ADE_Set        {(void*)ASNSet_New,    CONS|UNIV|TAG_SET}
#define ADE_SetOf      {(void*)ASNSetOf_New,  CONS|UNIV|TAG_SETOF}
#define ADE_Choice     {(void*)ASNChoice_New, NO_TAG}
#define ADE_End        {NULL, 0} 



/******************************************************************************
 * Descriptors for ASN.1 universal types
 * AD stands for ASN.1 Descriptor
 */
#ifdef ASN_SAFE
LIBSPEC_ME extern ASNDescriptor AD_Safe_OctetString;
#endif

LIBSPEC_ME extern ASNDescriptor AD_Boolean;
LIBSPEC_ME extern ASNDescriptor AD_Integer;
LIBSPEC_ME extern ASNDescriptor AD_BitString;
LIBSPEC_ME extern ASNDescriptor AD_OctetString;
LIBSPEC_ME extern ASNDescriptor AD_PrintableString;
LIBSPEC_ME extern ASNDescriptor AD_UTF8String;
LIBSPEC_ME extern ASNDescriptor AD_IA5String;
LIBSPEC_ME extern ASNDescriptor AD_VisibleString;
LIBSPEC_ME extern ASNDescriptor AD_BMPString;
LIBSPEC_ME extern ASNDescriptor AD_Enumerate;
LIBSPEC_ME extern ASNDescriptor AD_Null;
LIBSPEC_ME extern ASNDescriptor AD_UTCTime;
LIBSPEC_ME extern ASNDescriptor AD_GeneralizedTime;
LIBSPEC_ME extern ASNDescriptor AD_Oid;
LIBSPEC_ME extern ASNDescriptor AD_Any;

#ifdef ASN_SAFE
#define AD_Safe_ASNOctStr     AD_Safe_OctetString
#endif

#define AD_ASNBool       AD_Boolean
#define AD_ASNInt        AD_Integer
#define AD_ASNBitStr     AD_BitString
#define AD_ASNOctStr     AD_OctetString
#define AD_ASNPrintStr   AD_PrintableString
#define AD_ASNUTF8Str    AD_UTF8String
#define AD_ASNIA5Str     AD_IA5String
#define AD_ASNVisibleStr AD_VisibleString
#define AD_ASNBMPStr     AD_BMPString
#define AD_ASNEnum       AD_Enumerate
#define AD_ASNNull       AD_Null
#define AD_ASNUTCTime    AD_UTCTime
#define AD_ASNGenTime    AD_GeneralizedTime
#define AD_ASNOid        AD_Oid
#define AD_ASNAny        AD_Any



/******************************************************************************
 * Descriptors of some types used frequently
 */

LIBSPEC_ME extern ASNDescriptor AD_AlgorithmIdentifier;



/******************************************************************************
 * Some defaults 
 */

LIBSPEC_ME extern ASNDefault Default_boolean_false;
LIBSPEC_ME extern ASNDefault Default_boolean_true;
LIBSPEC_ME extern ASNDefault Default_integer_0;
LIBSPEC_ME extern ASNDefault Default_integer_1;
LIBSPEC_ME extern ASNDefault Default_integer_2;
LIBSPEC_ME extern ASNAny Any_null; /* 아직 사용하지 않음. */

/** @ingroup ASN
    @brief ASN 인스턴스을 delete하는 함수
    @param data 해제할 메모리의 포인터

    ASN_Del이 매크로라 펑션 포인터로 쓸수 없어서 내부에서 이를 호출하는
    함수를 추가한다.
    */
LIBSPEC_ME
void ASN_Delete(void *buf);

/** @ingroup ASN
    @brief ASNBuf 인스턴스을 delete하는 함수
    @param data 해제할 메모리의 포인터

    ASNBuf_Del이 매크로라 펑션 포인터로 쓸수 없어서 내부에서 이를 호출하는
    함수를 추가한다.
    */
LIBSPEC_ME
void ASNBuf_Delete(ASNBuf *buf);


#ifdef ASN_SAFE
/** @ingroup ASN
    @brief ASN_Safe_Buf 인스턴스을 delete하는 함수
    @param buf 해제할 메모리의 포인터
    @param allocSize 해제할 메모리 버퍼의 크기

    메모리 스와핑을 방지하기 위해 가상 메모리 주소를 사용할 수 있게 추가된 함수.
    */
LIBSPEC_ME
void ASNBuf_Safe_Del(ASNBuf *buf,int allocSize);

/** @ingroup ASN
    @brief ASN_Safe_buf 인스턴스을 new하는 함수
    @param 생성할 메모리 버퍼의 의 크기
    @ret 생성된 메모리 포인터

    메모리 스와핑을 방지하기 위해 가상 메모리 주소를 사용할 수 있게 추가된 함수.
    */
LIBSPEC_ME
ASNBuf* ASNBuf_Safe_New(int allocSize);

/** @ingroup ASN
    @brief 지정한 파일의 내용을 새로운 ASNBuf로 가져온다.
    @param filePath[in] 가져올 파일의 경로
    @param virSize[out] ASNBuf의 크기
    @ret 성공 시에는 할당된 ASNBuf의 포인터, 실패시에는 NULL.

    신규 ASNBuf를 할당한 후에 지정한 경로의 파일을 읽어서
    이에 저장하여 리턴한다.
    Base64, PEM, DER 인코딩된 파일을 지원한다.
    (메모리 스와핑을 방지하기 위해 가상 메모리 주소를 사용할 수 있게 추가된 함수.)
    */
LIBSPEC_ME
ASNBuf* ASNBuf_Safe_NewFromFile(const char *filePath, int *virSize);

/** @ingroup ASN
    @brief 지정한 버퍼의 내용을 새로운 ASNBuf로 가져온다.
    @param buf 가져올 buf
    @param len buf크기
    @ret 성공 시에는 할당된 ASNBuf의 포인터, 실패시에는 NULL.

    신규 ASNBuf를 할당한 후에 지정한 위치의 버퍼를 읽어서
    이에 저장하여 리턴한다.
    Base64, PEM, DER 인코딩된 버퍼를 지원한다.
    (메모리 스와핑을 방지하기 위해 가상 메모리 주소를 사용할 수 있게 추가된 함수.)
    */
LIBSPEC_ME
ASNBuf* ASNBuf_Safe_NewFromBuffer(const char *buf, unsigned int len);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _ASN1_H_ */
