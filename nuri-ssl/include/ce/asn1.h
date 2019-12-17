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
    @brief  ASN.1 DER encoding/decoding, set/get ���

    ASN.1 type ���� C language�� ǥ���ϴ� ����а� �� type����
    DER ������� encoding/decoding �ϴ� ��ɰ� type���� ������
    set/get �� �� �ִ� ����� �����Ѵ�.

    �����ϴ� ASN.1 type�� ������ ����.

    Basic Type :
    Boolean, Integer, BitString, OctetString, Null, Oid, Enumerate,
    UTF8String, PrintableString, IA5String, UTCTime, GeneralizedTime,
    VisibleString, BMPString

    Constructed Type :
    Sequence, Sequence Of, Set, Set Of

    �⺻������ Encoding/Decoding�� ASN_New�� ASN_EncodeDER�̶��
    �� �Լ��� �����ϰ�, Set/Get�� ASN.1 type���� �Լ��� �����ȴ�.
    */

/** @file asn1.h
    @ingroup ASN
    @brief ASN.1 DER notation ������ type���� ó���ϴ� ���.
 
    ASN.1 �� DER ���·� encoding/decoding �Ǿ�� �ϴ� type�� ó���ϴ�
    ����̴�.  "devide and conquer"�� �⺻ ��Ģ���� ó���ؾ� �� type��
    �⺻ ASN type���� tree ���·� �����ϵ��� �Ͽ� �⺻ type���� 
    encoding/decoding������ ��ü type�� �ڵ������� ó���ϵ��� �Ѵ�.

    �� ����� type ���� ��Ģ�� ���� type�� �����ϴ� �� ������ �� type�� DER
    encoding/decoding�� �ڵ������� �̷��� �ȴ�.
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
    @brief ASN.1 �� encoding/decoding �� ���Ǵ� ����
  
    ASN.1�� encoding �� decoding �� ����ϴ� ���� Ÿ���̴�.
    �Ϲ����� byte stream ���ۿʹ� �޸� alloc ���̰� ���ԵǾ� ���� �ʴٴ�
    ���� �����϶�.  len �� �״�� ����Ÿ�� �������� alloc �����̴�.
    index �� ���� ó���ؾ��� byte ��ġ�� ǥ���ϵ��� �Ǿ� �ִ�.
    index �� ��� ���������� �ٷ�� ���̹Ƿ�, ���Ƿ� ���� �����ؼ���
    �ȵȴ�.

    @sa ASNBuf_Set ASNBuf_Del ASNBuf_Sprint
    */
typedef struct _ASNBuf {
  char *data;    /**< ����Ÿ ���� */
  int   len;     /**< ����Ÿ ������ ���� */
  int   index;   /**< ����Ÿ ���� �� ���� ó���ؾ��� �κ� */
} ASNBuf;

/** @ingroup ASN
    @def ASNBuf_SetP
    @brief ASNBuf ��ü�� �����Ѵ�.

    ���۸� �����ϰ� �ִ� char* ���� ����Ʈ ���� ���̸� �Է°����� �־�
    ASNBuf�� �����Ѵ�. ���������� ������ ���� �����ϴ� ���� �ƴϰ�, �����Ͱ���
    �Ҵ��ϴ� ���̹Ƿ�, �Է��� ���۴� �״�� �����Ǿ�� �Ѵ�.

    @sa ASNBuf ASNBuf_Set ASNBuf_New ASNBuf_Del ASNBuf_Sprint
    */
#define ASNBuf_SetP(buf,d,l) ((buf)->data = (d), (buf)->len = (l), (buf)->index = 0)

/** @ingroup ASN
    @def ASNBuf_Set
    @brief ASNBuf ��ü�� �����Ѵ�.

    ���۸� �����ϰ� �ִ� char* ���� ����Ʈ ���� ���̸� �Է°����� �־�
    ASNBuf�� �����Ѵ�. ASNBuf_SetP�ʹ� �޸� ���������� ������ ���� �����Ѵ�,

    @sa ASNBuf ASNBuf_SetP ASNBuf_New ASNBuf_Del ASNBuf_Sprint
    */
#define ASNBuf_Set(buf,d,l) (memcpy((buf)->data, (d), (l)), (buf)->len = (l), (buf)->index = 0)

/** @ingroup ASN
    @brief ASNBuf ��ü�� �������� �����Ѵ�.
    @param allocSize [in] ASNBuf�� ���� �� �ִ� �������� ����Ʈ ���� ����
    @ret if allocation fails, return NULL, if success, address of ASNBuf

    allocSize ��ŭ�� �����͸� �������� �޸𸮿� �Ҵ��� ����, 
    ASNBuf ��ü�� �����Ͽ� �� �ּҰ��� �����Ѵ�.
    ����� ������ �ݵ�� ASNBuf_Del�� ���Ͽ� �Ҵ�� �޸𸮸� free���Ѿ�
    �Ѵ�.

    @sa ASNBuf ASNBuf_SetP ASNBuf_Set ASNBuf_Del ASNBuf_Sprint
    */
LIBSPEC_ME
ASNBuf* ASNBuf_New(int allocSize);

/** @ingroup ASN
    @def ASNBuf_Del
    @brief �޸𸮿� �Ҵ�Ǿ� �ִ� ASNBuf�� free��Ų��.

    �޸𸮿� �Ҵ�� ASNBuf�� �����Ѵ�. ASN_EncodeDER()�� ���ؼ�,
    ASNBuf�� ���� ���� ������ �������� �Ҵ�ǹǷ�, 
    ���̻� �ʿ� ���� �� ASNBuf�� �ݵ�� free���Ѿ� �Ѵ�.

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
    @brief ������ ������ ������ ���ο� ASNBuf�� �����´�.
    @param filePath ������ ������ ���

    �ű� ASNBuf�� �Ҵ��� �Ŀ� ������ ����� ������ �о
    �̿� �����Ͽ� �����Ѵ�.
    Base64, PEM, DER ���ڵ��� ������ �����Ѵ�.

    return : ���� �ÿ��� �Ҵ�� ASNBuf�� ������, ���нÿ��� NULL.

    @sa ASNBuf ASNBuf_SaveToFile
    */
LIBSPEC_ME
ASNBuf* ASNBuf_NewFromFile(const char *filePath);

/** @ingroup ASN
    @brief ������ ������ ������ ���ο� ASNBuf�� �����´�.
    @param filePath ������ ������ ���

    �ű� ASNBuf�� �Ҵ��� �Ŀ� ������ ��ġ�� ���۸� �о
    �̿� �����Ͽ� �����Ѵ�.
    Base64, PEM, DER ���ڵ��� ���۸� �����Ѵ�.

    return : ���� �ÿ��� �Ҵ�� ASNBuf�� ������, ���нÿ��� NULL.

    @sa ASNBuf ASNBuf_SaveToFile
    */
LIBSPEC_ME
ASNBuf* ASNBuf_NewFromBuffer(const char *buf, unsigned int len);

/** @ingroup ASN
    @brief ������ ASNBuf�� ������ ���Ϸ� �����Ѵ�.
    @param buf      ������ ASNBuf�� �����Ͱ�.
    @param filePath ������ ������ ���
    @retrun  SUCCESS or FAIL

    ASNBuf�� ������ ����� ���Ͽ� �����Ѵ�.

    @sa ASNBuf ASNBuf_NewFromFile
    */
LIBSPEC_ME
ERT ASNBuf_SaveToFile(ASNBuf *buf, const char *filePath);


/** @ingroup ASN
    @brief ASNBuf�� ���̳ʸ����� 16���� ���ڿ� ���·� ����Ѵ�.
    @param out ��°��� ����� ������ �ּҰ�
    @param maxLen out�� ����Ű�� �ִ� ������ �ִ� ����
    @param buf ��½�Ű���� �ϴ� ASNBuf

    ASNBuf�� ���̳ʸ����� 16���� string���·� \i out �� ����Ѵ�.
    String�� ������ null terminator�� �����Ѵ�.
   
    return : SUCCESS, FAIL 

    @sa ASNBuf ASNBuf_Set ASNBuf_Del
    */
LIBSPEC_ME
ERT ASNBuf_Sprint(char *out, int maxLen, const ASNBuf *buf);

/** @ingroup ASN
    @brief �ΰ��� ASNBuf ���� ���Ѵ�.
    @param a ���� ASNBuf 1
    @param b ���� ASNBuf 2

    memcmp() �Լ��� ���������� �� ASNBuf�� ������ ���Ѵ�.
    return : ������ 0, a�� ������ -1, b�� ������ 1

    @sa ASNBuf
    */
LIBSPEC_ME
int ASNBuf_Compare(const ASNBuf *a, const ASNBuf *b);

/** @ingroup ASN
    @breif ASNBuf�� ���� ��, ù ID, Length ����Ʈ�� ������ ASNBuf�� �����͸� ����
    @param in  [in] ID, Length�� ���ŵ� ASNBuf
    @sa ASNBuf

    */
LIBSPEC_ME
ASNBuf* ASNBuf_PeelOutIdLen(ASNBuf *in);



/******************************************************************************
 * ASN.1 octet field and option field
 */

/* @ingroup ASN
    @typedef ASNOption
    @brief ASN type�� ���¸� �����ϴ� �ɼ�
   
    ASN Option�� ���� 2byte ���� ����Ѵ�. 
    �׷��� Ȥ ������ �𸣴� SIGBUS ������ ���ϱ� ���� 4byte�� ����Ѵ�.
   
    ���� ����Ʈ�� implicit/explicit�� tagging ��ȣ�� 
    class, form ��  ���� ������ ��´�.
    ���� 5bit�� tagging number ���� 3bit�� class�� form�� �����Ѵ�.
    form  = constructed or primitive
    class = universal, applcation, context-specific or private
   
    ���� ����Ʈ�� normal/im/ex tagging��, optional, class_speicific�� ǥ���Ѵ�.
   
    ���� ����Ʈ�� ���� 2bit�� tagging ����� ǥ��.
    ���� 3��° bit�� 1�̸� class�� ��������, 0�̸� �⺻���� ������� ǥ���Ѵ�.
    ���� ����Ʈ�� �ֻ��� bit�� �� type�� optional�� ǥ��.
    ���� ����Ʈ�� �ֻ��� �ٷ� �Ʒ� bit�� �� type�� default ���� ������ ǥ��.
   
    ������ bit���� ������ ���� ���� bit
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
 *  @brief ASN.1 type���� tag �ڵ� ��ȣ ����
 *
 *  ASN.1 type ���� �������ִ� tag �ڵ� ��ȣ���� �����Ѵ�.
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
    @brief   ASN ��ũ������ DEFAULT Ȯ��
  
    Default ���� ������ sequence�� set ���� �� ����� ���� ��
    �̸� ǥ��/ó�����ֱ� ���� ����ü�̴�.
    �� ����� tag �ڵ�� default ���� DER encoding�� ����Ÿ �� ��
    ���̸� ���´�.  ���ڴ��� �� default ���� ���� ����� �߰ߵ���
    ���� ��� �� DER ����Ÿ�� ���ڵ������ν� default ���� setting�Ѵ�.
    ���ڴ��� default ���� ���� ���� ���غ��� ���� ������ ���
    ���ڵ� ���ۿ� �������� �ʴ´�.
  
    default �κ��� ������ �ܰ迡���� ���� ����ϰ� ���� �ʴٰ�
    ���߿� �߰��� �κ��̹Ƿ� ���� ����/������ �ʿ伺�� ���ٰ�
    �����ȴ�.
    */
typedef struct _ASNDefault {
  int       tagCode;    /**< �� ���� TAG code */
  int       dataLen;    /**< default data�� ���� */
  char     *data;       /**< default data�� byte stream */
} ASNDefault;

/**	@ingroup ASN
    @struct ASNDescriptor
    @brief  ASN Ÿ���� ������ ǥ���ϴ� ��ũ����.
  
    Ư�� ASN.1 Ÿ���� ������ ��Ÿ���� ���� ��ũ���� ����ü�̴�.  
    ��� ASN.1 Ÿ���� �� ��ũ������ ������ ����Ͽ� �����ȴ�. 
  
    ���� ��ũ���ʹ� ������ array�� �����ȴ�.
  
    �� : ASN Boolean
    AD_BOOLEAN = {{ASNBool_New, 0}, {NULL, 0}}
  
    ���� ó�� ���� �� Ÿ���� ����� ���� ȣ���ؾ� �ϴ� �Լ���
    �� �ɼ��̴�.
    �� ������ ���ʹ� Ÿ�� ���� �Լ����� ��Ե� �̿��� �� �ִ�
    �����̴�.  Ÿ�� �����Լ����� ������ �޶�����.
    �밳�� construced type������ ���⿡ ���� ��� Ÿ���� ��ũ���Ͱ� ����.
    ���� ���������� ������ ���� ��Ÿ���� {NULL, 0} �̴�.
  
    ����° argument�� Ư���� ��쿡�� ǥ��/����Ѵ�.
    Sequence�� Set �ȿ��� element �ϳ��� default ���� ���� ��
    �̸� ����Ű�� ASN Default�� �����͸� �����Ѵ�.
    */

typedef struct _ASNDescriptor {
  void       *param;       /**< void* �� parameter. �������� ���� ���� */
  ASNOption   option;      /**< �� ASN.1 type�� option */
  ASNDefault *defaultDesc; /**< default ���� ���� �� default descriptor�� ����Ű�� ������ */
} ASNDescriptor[];



/******************************************************************************

                           Class�� ���� ASN Ÿ�Ե�

 *****************************************************************************/



/******************************************************************************
 *  ASN.1 Base clase / type
 */

/**	@ingroup ASN
    @struct ASNClass
    @brief ��� ASN.1 type���� �ֻ��� Ŭ����

    ��� ASN.1 type���� �� type�� ���� �պκп� ���� �־�߸� �Ѵ�.
    ASN.1 type ���� �⺻������ �������� DER ���ڵ��� ������ 
    ����Ÿ �� �Լ����� ���� �ִ�.
    */
typedef struct _ASNClass {
  ASNDescriptor *dsc;      /**< �ڱ� �ڽ��� ��ũ���� */

  int   derLen;            /**< DER ���ڵ��� ��ü ���� */

  char  derHead[8];        /**< DER Header(tag + length) ���� */
  int   derHeadLen;        /**< DER Header�� ���� */
  char *derData;           /**< Header�� ������ DER ���ڵ��� ���� */
  int   derDataLen;        /**< derData �� ���� */

  int  (*encodeDER)();     /**< DER encode function */
  int  (*getDER)();        /**< DER ���۸� ���Ѵ�. */
  int  (*getDERLen)();     /**< DER ������ ���̸� ���Ѵ�. */
  int  (*copy)();          /**< ������ �����Ѵ�. */
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
    @brief ASN* Ÿ������ casting�ϴ� ��ũ��
    
    */
#define ASN(a)  ((ASN*)(a))

/** @ingroup ASN
    @def pASN
    @brief ASN** Ÿ������ casting�ϴ� ��ũ��

    */
#define pASN(a)  ((ASN**)(a))

/** @ingroup ASN
    @def ASN_New(type, data)
    @brief �ű� ASN type object�� �����ϴ� ��ũ��

    ASNDescriptor�� ����Ͽ� �ʿ��� �޸� ������
    �Ҵ��ϰ� ������ �ʱ�ȭ�Ͽ� ���ο� ASN type�� object�� �ϳ� �����Ѵ�.

    ������ ASN.1 �⺻ Ÿ�� ��, boolean�� Integer�� �ش��ϴ� object�� �����ϴ� 
    �ڵ��̴�. ���� ������ primitive Ÿ�Ե鿡 ���� ��������, 
    ������ contstructed Ÿ�������� ���������̴�.

    @code
    Boolean *boolean;
    Integer *integer;

    boolean = ASN_New(Boolean, NULL);
    integer = ASN_New(Integer, NULL);

    ASN_Del(boolean);
    ASN_Del(integer);
    @endcode

    ���� �������� 2��° �Ķ���Ͱ� NULL������ �־����� �Ϳ� �ָ��϶�.
    �� ASN ��⿡���� ������ decoding �������̽��� �������� �ʴ´�.
    Decoding�� �ϱ� ���ؼ��� ���� �������� NULL��ſ� ASNBuf�� �Ѱ� �ָ�,
    ASN_New���� decoding�� ���� ������ object�� �����Ѵ�.
    ������ �� �����̴�. (TestASN �̶�� ASN.1 type�� ���ǵǾ��ٴ� �����Ͽ���)

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
    @brief ASN �ν��Ͻ��� delete�ϴ� ��ũ��

    � ASN type�� �Ҵ�� �� �޸𸮸� �����ϴ� ��ũ���̴�.
    ASN type�� ���� del() �Լ��� �ҷ� �̷��� �۾��� �����Ѵ�.
    ASN_New()�� ���������� ��ģ ��� ASN.1 object���� ��� ��,
    �ݵ��, ASN_Del()������ ���� �Ҵ�� �޸𸮸� free�ϵ��� �Ѵ�.
    */
#define ASN_Del(a)  _START { if(a) ((void (*)(ASN*)) (((ASN*)(a))->del)) \
                      ((ASN*)(a)); (a) = NULL; } _END

/** @ingroup ASN
    @brief ASN.1 DER ���ڵ� �Լ�
    @param data ���ڵ��� ������ ��� �ִ� ASN Type ������

    DER ���ڵ� �Լ��̴�.
    data�� ������ �о� �̸� DER ���ڵ��� �� �� ������ �����
    ASNBuf Type�� �����Ѵ�.

    */
LIBSPEC_ME
ASNBuf* ASN_EncodeDER(const void *asnObj);

/** @ingroup ASN
    @define ASN_Copy(d, s)
    @brief ASN type �����Ѵ�.

    ������ type�� ASN object �ΰ��� ���� ��,  �ϳ����� �ٸ� �ϳ���
    ������ �����ϴ� ��ũ���̴�.
    ASN type�� ���� copy() �Լ��� �ҷ� �̷��� �۾��� �����Ѵ�.
    */
#define ASN_Copy(d, s)  (s) ? ( (int (*)(ASN*, ASN*)) ((ASN(s))->copy) ) (ASN(d),ASN(s)) : 0

/** @ingroup ASN
    @brief ASN type �ϳ��� ������ ASN type�� ���� �����Ѵ�. 
    @param data Duplicate�� ASN type�� ���� ������

    ASN.1 type�� ������ ������ �� type�� �����ϴ� duplicate �Լ� �̴�.
    data�� ���� type�� ASN type�� ������ �� �� data�� ������
    �״�� ���Ӱ� ������ type���� �����Ѵ�.
    ���Ӱ� ������ type�� �����͸� �����Ѵ�.
    */
LIBSPEC_ME
ASN* ASN_Dup(const ASN* data);



/*****************************************************************************/
/**	@ingroup ASN
    @struct ASNSeqClass
    @brief ASN.1 SEQUENCE Type Class

    ASN.1 �� SEQUENCE type�� �ٷ�� ���� ����ü�̴�.
    */
typedef struct _ASNSeqClass {
  ASN   klass;    /**< ASN ���� ��� */
  int   size;     /**< ������� ���� */
  ASN **elements; /**< Encode/decode�� ����ü ����� */
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
		@brief Sequence Type ���� �� ���ڵ� �Լ�
		@param dsc ��ũ����
		@param buf ���ڵ� ���� ������
		@param option �ɼ�

		buf�� NULL�� ��� ���� �Լ��̰�, NULL�� �ƴϸ� ���ڵ� �Լ��̴�.
    */
LIBSPEC_ME
ASNSeq* ASNSeq_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief Sequence ��� ��, optional ��� �Ҵ�
    @param member [out] Sequence�� ��� �������� �ּҰ�
    @param seq [in] Sequence�� ������ 

    Sequence�� ��� ��, optional ����� ASN_New�Ͽ� ������ �ÿ� �޸𸮿�
    �Ҵ���� �ʴ´�.(Decoding�� ����) ����, optional ����� ���Խ�ų
    ��쿡�� ���� �����ϱ� ����, �� �Լ��� ���Ͽ� �޸𸮸� �Ҵ��� ����
    ����Ͽ��� �Ѵ�.
    */
LIBSPEC_ME
ERT ASNSeq_NewOptional(ASN **opt, const ASNSeq *seq);

LIBSPEC_ME
ERT ASNSeq_NewSetOptional(ASN **opt, const ASNSeq *seq, const ASN *src);

LIBSPEC_ME
ERT ASNSeq_NewSetPOptional(ASN **opt, const ASNSeq *seq, ASN *src);

/** @ingroup ASN
    @brief Sequence ��� ��, optional ��� �޸� ����
    @param member [out] Sequence�� ��� �������� �ּҰ�
    @param seq [in] Sequence�� ������ 

    ASNSeq_NewOptional Ȥ�� Decoding�� ���Ͽ� ��� Sequence�� Optional
    ����� �޸𸮰� �Ҵ�Ǿ��� ���, optional ����� �ٽ� �����ϰ��� �Ҷ�,
    �� �Լ��� ����Ѵ�.
    */
LIBSPEC_ME
ERT ASNSeq_DelOptional(ASN **opt, const ASNSeq *seq);



/*****************************************************************************/
/**	@ingroup ASN
		@struct ASNSetClass
		@brief ASN.1 SET Type class
    */		
typedef struct _ASNSetClass {
  ASN   klass;    /**< ASN���� ��� */
  int   size;     /**< ����ä ������� ���� */
  ASN **elements; /**< Encode/decode�� ����ü ����� */
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
  	@brief ASN.1 SET Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
    buf�� NULL�� ��� ���� �Լ��̰�, NULL�� �ƴϸ� ���ڵ� �Լ��̴�.
    */
LIBSPEC_ME
ASNSet* ASNSet_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief SET ��� ��, optional ��� �Ҵ�
    @param member [out] Set�� ��� �������� �ּҰ�
    @param set [in] Set�� ������ 

    Set�� ��� ��, optional ����� ASN_New�Ͽ� ������ �ÿ� �޸𸮿�
    �Ҵ���� �ʴ´�.(Decoding�� ����) ����, optional ����� ���Խ�ų
    ��쿡�� ���� �����ϱ� ����, �� �Լ��� ���Ͽ� �޸𸮸� �Ҵ��� ����
    ����Ͽ��� �Ѵ�.
    */
LIBSPEC_ME
ERT ASNSet_NewOptional(ASN **member, const ASNSet *set);

LIBSPEC_ME
ERT ASNSet_NewSetOptional(ASN **opt, const ASNSet *set, const ASN *src);

LIBSPEC_ME
ERT ASNSet_NewSetPOptional(ASN **opt, const ASNSet *set, ASN *src);

/** @ingroup ASN
    @brief SET ��� ��, optional ��� �޸� ����
    @param member [out] Set�� ��� �������� �ּҰ�
    @param set [in] Set�� ������ 

    ASNSet_NewOptional Ȥ�� Decoding�� ���Ͽ� ��� Set�� Optional
    ����� �޸𸮰� �Ҵ�Ǿ��� ���, optional ����� �ٽ� �����ϰ��� �Ҷ�,
    �� �Լ��� ����Ѵ�.
    */
LIBSPEC_ME
ERT ASNSet_DelOptional(ASN **member, const ASNSet *set);



/*****************************************************************************/
/**	@ingroup ASN
		@struct ASNSeqofClass
		@brief ASN.1 SEQUENCE OF Type class
    */		
typedef struct _ASNSeqOfClass {
  ASN  klass;         /**< ASN ���� ��� */
  int  alloc;         /**< elements�� ��� ������ �Ҵ� ũ�� */
  ASN *defaults[8];   /**< elements�� ��� �⺻ ����. 8��. */
} ASNSeqOfClass;
/* ���� sequence of �� ���� �༮���� 8���� ���� �ʴ´�.
 * �׷��Ƿ� �⺻ ���۸� ����ϴ� �͸����ε� ��κ��� ���.
 * 8���� �Ѿ�� ���� alloc�ؼ� ����Ѵ�. */

/**	@ingroup ASN
		@struct ASNSeqOf
		@brief ASN.1 SEQUENCE OF Type
    */		
typedef struct _ASNSeqOf {
  ASNSeqOfClass klass;
  int           size;          /**< ���� ��� ���� */
  ASN         **elements;      /**< Encode/decode�� ����ü ����� */
} ASNSeqOf;

#define ASN_SEQOF(a)  ((ASNSeqOf*)(a))

/* @ingroup ASN
  	@brief ASN.1 SEQUENCE OF Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNSeqOf Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNSeqOf Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNSeqOf* ASNSeqOf_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief SEQUENCE OF Ÿ�Կ� element�� �ϳ� �߰��Ѵ�.
    @param seqof [out] ASNSeqOf�� ������
    @param asn [in] �߰��� element�� ������

    ASNSeqOf�� element�� �ϳ� �߰��Ѵ�. ����, �߰��� asn�� seqof��
    ���� element Ÿ�԰� ��ġ�ؾ� �� ���̴�. ��������� base class ����
    ASN* �� type casting �� �Ͽ� ����ϱ� �ٶ���.

    ������ ����, Add�� �ÿ� input�� element�� ���� value�� �״�� ������
    �ִ´ٴ� ���̴�.  �Է����� �� asn element�� Add �� ���Ŀ��� �ݵ��
    ASN_Del()�� �޸𸮿��� �����־�߸� �Ѵ�.

    @sa ASNSeqOf_AddP
    */
LIBSPEC_ME
ERT ASNSeqOf_Add(ASNSeqOf *seqof, const ASN *asn);

/** @ingroup ASN
    @brief SEQUENCE OF Ÿ�Կ� element�� �ϳ� �߰��Ѵ�.
    @param seqof [out] ASNSeqOf�� ������
    @param asn [in] �߰��� element�� ������

    ASNSeqOf�� element�� �ϳ� �߰��Ѵ�. ����, �߰��� asn�� seqof��
    ���� element Ÿ�԰� ��ġ�ؾ� �� ���̴�. ��������� base class ����
    ASN* �� type casting �� �Ͽ� ����ϱ� �ٶ���.

    ������ ����, Add�� �ÿ� input�� element�� �����Ͱ����� �����ϰ�,
    ���� �� element�� value�� �������� �ʴ´�. ����, ASNSeqOf_AddP��
    ����� ����, �׿� Add �� ���� element�� �޸𸮿� �״�� ���� �־�� �Ѵ�.
    �̸� ASN_Del()�� �����ϸ� �ȵȴ�.

    @sa ASNSeqOf_Add
    */
LIBSPEC_ME
ERT ASNSeqOf_AddP(ASNSeqOf *seqof, ASN *asn);

/** @ingroup ASN
    @brief SEQUENCE OF Ÿ�Կ� element�� �ϳ� �����Ѵ�.
    @param seqof [out] ASNSeqOf�� ������
    @param asn [in] ������ element�� index

    ASNSeqOf�� element�� �ϳ� �����Ѵ�. ASNSeqOf�� element���� index��
    ���Ͽ� ������ �ȴ�. element�� �ϳ� �����Ϸ���, ���ϴ� element��
    index�� ã�Ƽ� �� �Լ��� ���Ͽ� �����Ѵ�.
    */
LIBSPEC_ME
ERT ASNSeqOf_Remove(ASNSeqOf *seqof, int index);

/** @ingroup ASN
    @brief SEQUENCE OF Ÿ���� ���ʱ�ȭ �Ѵ�.
    @param seqof [in/out] ASNSeqOf�� ������

    ASNSeqOf�� element�� ��� �޸� �����ϰ�, element�� �ϳ��� ������ ����
    �� SEQUENCE OF Ÿ������ �ٽ� �ʱ�ȭ�Ѵ�. ��, ASN_Del() �� ASN_New()��
    �ٽ� �ѹ��� �����Ų ����� �����ϴ�.
    */
LIBSPEC_ME
ERT ASNSeqOf_Reset(ASNSeqOf *seqof);



/*****************************************************************************/
/**	@ingroup ASN
		@struct ASNSetofClass
		@brief ASN.1 SET OF Type class
    */		
typedef struct _ASNSetOfClass {
  ASN  klass;         /**< ASN ���� ��� */
  int  alloc;         /**< elements�� ��� ������ �Ҵ� ũ�� */
  ASN *defaults[8];   /**< elements�� ��� �⺻ ����. 8��. */
} ASNSetOfClass;

/* ���� set of �� ���� �༮���� 8���� ���� �ʴ´�.
 * �׷��Ƿ� �⺻ ���۸� ����ϴ� �͸����ε� ��κ��� ���.
 * 8���� �Ѿ�� ���� alloc�ؼ� ����Ѵ�. */

/**	@ingroup ASN
		@struct ASNSetOf
		@brief ASN.1 SET OF Type 
    */		
typedef struct _ASNSetOf {
  ASNSetOfClass klass;
  int           size;          /**< ����ü ����� ���� */
  ASN         **elements;      /**< Encode/decode�� ����ü ����� */
} ASNSetOf;

#define ASN_SETOF(a)  ((ASNSetOf*)(a))

/* @ingroup ASN
  	@brief ASN.1 SET OF Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNSetOf Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNSetOf Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNSetOf* ASNSetOf_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief SET OF Ÿ�Կ� element�� �ϳ� �߰��Ѵ�.
    @param setof [out] ASNSetOf�� ������
    @param asn [in] �߰��� element�� ������

    ASNSetOf�� element�� �ϳ� �߰��Ѵ�. ����, �߰��� asn�� setof��
    ���� element Ÿ�԰� ��ġ�ؾ� �� ���̴�. ��������� base class ����
    ASN* �� type casting �� �Ͽ� ����ϱ� �ٶ���.

    ������ ����, Add�� �ÿ� input�� element�� ���� value�� �״�� ������
    �ִ´ٴ� ���̴�.  �Է����� �� asn element�� Add �� ���Ŀ��� �ݵ��
    ASN_Del()�� �޸𸮿��� �����־�߸� �Ѵ�.

    @sa ASNSetOf_AddP
    */
LIBSPEC_ME
ERT ASNSetOf_Add(ASNSetOf *setof, const ASN *asn);

/** @ingroup ASN
    @brief SET OF Ÿ�Կ� element�� �ϳ� �߰��Ѵ�.
    @param setof [out] ASNSetOf�� ������
    @param asn [in] �߰��� element�� ������

    ASNSetOf�� element�� �ϳ� �߰��Ѵ�. ����, �߰��� asn�� setof��
    ���� element Ÿ�԰� ��ġ�ؾ� �� ���̴�. ��������� base class ����
    ASN* �� type casting �� �Ͽ� ����ϱ� �ٶ���.

    ������ ����, Add�� �ÿ� input�� element�� �����Ͱ����� �����ϰ�,
    ���� �� element�� value�� �������� �ʴ´�. ����, ASNSetOf_AddP��
    ����ϴ� ��, �׿� Add �� ���� element�� �޸𸮿� �״�� ���� �־��
    �Ѵ�. ���� element�� ASN_Del()�� ���� �ȵȴ�.

    @sa ASNSetOf_Add
    */
LIBSPEC_ME
ERT ASNSetOf_AddP(ASNSetOf *setof, ASN *asn);

/** @ingroup ASN
    @brief SET OF Ÿ�Կ� element�� �ϳ� �����Ѵ�.
    @param setof [out] ASNSetOf�� ������
    @param asn [in] ������ element�� index

    ASNSetOf�� element�� �ϳ� �����Ѵ�. ASNSetOf�� element���� index��
    ���Ͽ� ������ �ȴ�. element�� �ϳ� �����Ϸ���, ���ϴ� element��
    index�� ã�Ƽ� �� �Լ��� ���Ͽ� �����Ѵ�.
    */
LIBSPEC_ME
ERT ASNSetOf_Remove(ASNSetOf *setof, int index);

/** @ingroup ASN
    @brief SET OF Ÿ���� ���ʱ�ȭ �Ѵ�.
    @param setof [in/out] ASNSetOf�� ������

    ASNSetOf�� element�� ��� �޸� �����ϰ�, element�� �ϳ��� ������ ����
    �� SET OF Ÿ������ �ٽ� �ʱ�ȭ�Ѵ�. ��, ASN_Del() �� ASN_New()��
    �ٽ� �ѹ��� �����Ų ����� �����ϴ�.
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
  ASN      klass;    /**< ASN ���� ��� */
} ASNChoiceClass;


/**	@ingroup ASN
		@struct ASNChoice
		@brief ASN.1 CHOICE Type 
    */		
typedef struct _ASNChoice {
  ASNChoiceClass klass;
  int            select;  /**< ���õ� ASN�� ��ȣ */
  ASN           *choice;  /**< ���õ� ASN type�� ���� ������ */
} ASNChoice;

#define ASN_CHOICE(a)  ((ASNChoice*)(a))

/* @ingroup ASN
  	@brief ASN.1 CHOICE Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNChoice Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNChoice Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
*/
LIBSPEC_ME
ASNChoice* ASNChoice_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief CHOICE Ÿ���� element ����
    @param choice [out] ASNChoice Ÿ���� ������
    @param select [in] element�� select ��, ù��°�� 1��

    ASNChoice Ÿ���� element�� �����ϴ� �Լ��̴�. �����Ѵٴ� ���� Choice
    ����� �Ǵ� element�� �߿���, select�� ����Ű�� ��°�� element��
    �����ϰ� ASNChoice Ÿ���� �� element�� ������ ������ �����ϴ� �ǹ��̴�.
    ����, �� �Լ��� �����ϰ� �� ����, �� element�� ���� �����Ͽ���
    �� ���̴�.
    */
LIBSPEC_ME
ERT ASNChoice_Select(ASNChoice* choice, int select);



/******************************************************************************
 
                    Class�� ���� �ʴ� ASN Ÿ�Ե�
 
 *****************************************************************************/



/*****************************************************************************/
/**	@ingroup ASN
    @struct ASNBool
    @brief ASN.1 Boolean
  
    ASN.1�� Boolean type
    */
typedef struct _ASNBool {
  ASNClass      klass;
  unsigned char  data;  /**< 1�̸� true, 0�̸� false */
} ASNBool;

#define ASN_BOOL(a)  ((ASNBool*)(a))

/* @ingroup ASN 
    @param dsc Type ��ũ����
    @param data ASNBuf ������
  	@param option Type�� �ɼ�
    
    ASN.1�� Boolean type ���� �� ���ڵ� �Լ�
  	1. data�� NULL�� ���� Boolean type�� ������ �����Ѵ�.
  	2. data�� NULL�� �ƴ� ���� ���ڵ��� Boolean type�� �����Ѵ�.
  	3. option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNBool* ASNBool_New(ASNDescriptor dsc, ASNBuf* data, ASNOption option);

/** @ingroup ASN
    @param target ASNBool type ������
    @param in Boolean type�� ������ ��
    @ret SUCCESS, FAIL

    ASN.1�� Boolean type Set �Լ�
    */
LIBSPEC_ME
ERT ASNBool_Set(ASNBool *target, int in);

/** @ingroup ASN
    @param source ASNBool type ������
    @ret TRUE 1, FALSE 0
    
    ASN.1�� Boolean type Get �Լ�
    */
LIBSPEC_ME
int ASNBool_Get(const ASNBool *source);



/*****************************************************************************/
/** @ingroup ASN
    @def ASN_MAX_INT_LEN
    @brief ASNInt�� �ִ� ũ��

    ASNInt�� ������ �� �ִ� �ִ� ���� ũ���̴�. ��, 512����Ʈ�� �Ѱ��̴�.
    */
#define ASN_MAX_INT_LEN  512

/** @ingroup ASN
    @struct ASNInt
    @brief  ASN.1 Integer
  
    ASN.1�� Integer type
    */
typedef struct _ASNInt {
  ASNClass klass;
  int       len;                     /**< integer�� byte �� */
  char      data[ASN_MAX_INT_LEN];  /**< ���� integer data */
} ASNInt;
/* NOTE : data�� ũ�Ⱑ 512byte�̹Ƿ� 512*8=4096 bit �̻��� ������ ǥ�� ���� */

#define ASN_INT(a)  ((ASNInt*)(a))

/* @ingroup ASN
  	@param dsc Type ��ũ����
    @param data ASNBuf ������
  	@param option Type �ɼ�
    
    ASN.1�� Integer type ���� �� ���ڵ� �Լ�
  	1. data�� NULL�� ���� Integer type�� ������ �����Ѵ�.
  	2. data�� NULL�� �ƴ� ���� ���ڵ��� Integer type�� �����Ѵ�.
  	3. option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNInt* ASNInt_New(ASNDescriptor dsc, ASNBuf* data, ASNOption option);

/** @ingroup ASN
  	@param in ASNInt ������
    @param data �Ҵ��� C int type�� ������
    @ret SUCCESS, FAIL 

    ASN.1�� Integer type Set �Լ�.
    int ������ ���� ASNInt�� Set�Ѵ�.
    */
LIBSPEC_ME
ERT ASNInt_SetInt(ASNInt *target, int in);

#define ASNInt_SetByInt(a, b) ASNInt_SetInt(a, b)

/** @ingroup ASN
  	@param data �о�� ������ ���� ����� C int type�� ����Ű�� ������ 
    @param in ASNInt ������ 
    @ret SUCCESS, FAIL 
  
    ASN.1�� Integer type Get �Լ�
    ASNInt�κ��� integer���� Get�Ѵ�.  ASNInt�� 512����Ʈ������ ������
    ������ �� ������ int�� �Ϲ������� 4����Ʈ�̹Ƿ� ����, ASNInt�� �����
    ���� 4����Ʈ�� �ʰ��ϸ� FAIL�� �����ϰ� �ȴ�.
    */
LIBSPEC_ME
ERT ASNInt_GetInt(int *out, const ASNInt *source);

#define ASNInt_GetByInt(a, b) ASNInt_GetInt(a, b)

/** @ingroup ASN
    @param target ASNInt ������ 
  	@param in Integer�� ǥ���ϴ� ���ڿ��� ����Ű�� ������
    @ret ���忡 ���� ����Ʈ ������ ũ��, ���н� FAIL
  
    ASN.1�� Integer type Set �Լ�.
    "0123456ABCDE"�� ���� ����� ���� �� �ִ� ������ ���ڿ��� ���� �����Ѵ�.
    */
LIBSPEC_ME
int ASNInt_SetStr(ASNInt *target, const char* in);

#define ASNInt_SetByStr(a, b) ASNInt_SetStr(a, b)

/** @ingroup ASN
  	@param out Integer�� ǥ���ϴ� ���ڿ��� ����Ű�� ������
    @param maxLen out ������ �ִ� ũ��
    @param source ASNInt ������ 
    @ret out�� ��µ� ��Ʈ���� ����, ���н� FAIL
  
    ASN.1�� Integer type Get �Լ�.
    "0123456ABCDE"�� ���� ����� ���� �� �ִ� ������ ���ڿ��� Integer ����
    ��´�.
    */
LIBSPEC_ME
int ASNInt_GetStr(char *out, int maxLen, const ASNInt *source);

#define ASNInt_GetByStr(a, b) ASNInt_GetStr(a, b)

/** @ingroup ASN
    @param target ASNInt ������ 
    @param in ���̳ʸ� ���� ����� ������ ������
    @param inLen ���̳ʸ� ���� ����Ʈ ���� ����
    @ret ���忡 ���� ������ ũ��, ���н� FAIL

    ASN.1�� Integer type Set �Լ�.
    ���̳ʸ����� �״�� ASNInt�� �����´�.
    */
LIBSPEC_ME
int ASNInt_SetBin(ASNInt *target, const char *in, int inLen);

#define ASNInt_SetByBin(a, b, c) ASNInt_SetBin(a, b, c)

/** @ingroup ASN
  	@param out ���̳ʸ����� ������ ���۸� ����Ű�� ������
    @param maxLen out ������ �ִ� ũ��
    @param source ASNInt ������ 
    @ret out�� ��µ� ���̳ʸ����� ����Ʈ ���� ����, ���н� FAIL
    
    ASN.1�� Integer type Get �Լ�.
    ASNInt�κ��� ���̳ʸ����� ���۷� �����Ѵ�.
    */
LIBSPEC_ME
int ASNInt_GetBin(char *out, int maxLen, const ASNInt *source);

#define ASNInt_GetByBin(a, b, c) ASNInt_GetBin(a, b, c)


/*****************************************************************************/
/** @ingroup ASN
 *	@def ASN_MAX_BIT_LEN
 *	@brief ASNBitStr�� �ִ� ����Ʈ ũ��.

    ASNBitStr�� ������ �� �ִ� �ִ� ���� �������̴�. ��, �ִ� 2048����Ʈ����
    ������ �� �ִ�.
 **/
#define ASN_MAX_BIT_LEN  2048

/** @ingroup ASN
 *	@struct ASNBitStr
 *  @brief  ASN.1 BIT STRING Type
 **/

typedef struct _ASNBitStr {
  ASNClass klass;

  int       bitLen;	/**< bits length */
  int       len; /**< byte length(BitString�� byte ũ�� + �е���������Ʈ)  */
  char      data[ASN_MAX_BIT_LEN]; /**< ���� BIT STRING data */ 

} ASNBitStr;

#define ASN_BITSTR(a)  ((ASNBitStr*)(a))

/* �е� ���̸�ŭ 0���� padding */
#define PadWithZero(a,b) ((a) = (a) >> (b)); \
        ((a) = (a) << (b));

/* @ingroup ASN
  	@brief ASN.1 BIT STRING Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNBitStr Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNBitStr Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNBitStr* ASNBitStr_New(ASNDescriptor dsc, ASNBuf* data, ASNOption option);

/** @ingroup ASN
    @brief ASN.1 BIS STRING Ÿ�� Set �Լ�
    @param in �����Ͱ� Setting�� ASNBitStr Type ������ 
    @param data �Է� ������ ������
    @param bit_len �Է� �������� ��Ʈ ����
    @ret ó���� �������� ��Ʈ ���̰� ���ϵȴ�. ���н� FAIL

    �е� ������ ù��° content octet�� ��ϵȴ�.
    */

LIBSPEC_ME
int ASNBitStr_Set(ASNBitStr *in, const char *data, int bitLen);

/**	@ingroup ASN
    @brief ASN.1 BIT STRING Ÿ�� Get �Լ�
    @param data [out] �о� �� �����Ͱ� �Ҵ�� ���۸� ����Ű�� ������
    @param max_bit_len [in] data�� ����Ű�� ������ �ִ� ��Ʈ ����
    @param in [in] ASNBitStr Ÿ�� ������ 
    @ret data�� ��µ� ��Ʈ ����, ���н� FAIL

    �о� �� �������� ��Ʈ ���̰� ���ϵȴ�.
    */
LIBSPEC_ME
int ASNBitStr_Get(char *data, int maxBitLen, const ASNBitStr *in);

/** @ingroup ASN
    @brief ASNBitStr �ν��Ͻ� Set �Լ�
    @param target ���� ����� ASNBitStr�� ������
    @param asnBuf ASNBuf�� ������
    @ret ó���� ����Ʈ ����, ���н� FAIL

    ASNBuf�� ����Ǿ� �ִ� ���̳ʸ����� ASNBitStr�� �����´�.
    bit length�� �׻� ASNBuf�� ����� ����Ʈ ���� ������ 8�谡 �ȴ�.
    */
LIBSPEC_ME
int ASNBitStr_SetASNBuf(ASNBitStr *in, const ASNBuf *asnBuf);

/** @ingroup ASN
    @brief ASNBitStr �ν��Ͻ� Get �Լ�
    @param source ASNBitStr ������

    ASNBitStr�� ����Ǿ� �ִ� ��Ʈ������ ASNBuf�� �����Ͽ� �����Ѵ�.
    LSB���� ä������. ���� ��� 100011001�̶�� 9bit�� ���� �о����,
    data[0] = 0x01, data[1] = 0x19 �� �ȴ�.
    ���ϵ� ASNBuf�� ASNBuf_Del�� ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.
    */
LIBSPEC_ME
ASNBuf* ASNBitStr_GetASNBuf(const ASNBitStr *in);



/*****************************************************************************/
/** @ingroup ASN
		@struct ASNStr
 		@brief  Base of ASN.1 String Type

    ASNStr�� ASNOctStr, ASNPrintStr, ASNUTF8Str, ASNIA5Str, ASNVisibleStr,
    ASNBMPStr�� base type�̴�. ASN.1�� string ������ basic type�� �߿���,
    BitString�� �����ϰ�� �� ��⿡�� �����Ǵ� ����� �����ϹǷ� ASNStr
    �ϳ����� �����ϰ�, �� structure�� ������ string type�� �̸����� 
    rename �Ͽ� (#define�� ���ؼ�) ����ϰ� �ִ�.

    �� ��� ����ڴ� ASNStr�� ���� ���� �ͺ��ٴ� � string type������
    ��������� ǥ���ϱ� ���ؼ� rename�� ���� string type �̸��� �������̽���
    ����ϱ� �ٶ���.
    */
typedef struct _ASNStr {
  ASNClass klass;
  int       len; /**< data byte length */
  char     *data; /**< ���� OCTET STRING data */
} ASNStr;

LIBSPEC_ME
ASNStr* ASNStr_Safe_New(ASNDescriptor dsc, ASNBuf* buf, ASNOption option);

LIBSPEC_ME
ASNStr* ASNStr_New(ASNDescriptor dsc, ASNBuf* buf, ASNOption option);

/** @ingroup ASN
    @brief ASNStr �ν��Ͻ� Set �Լ�
    @param target ���� ������ ASNStr�� ������
    @param in ������ string�� �����ϰ� �ִ� ������ ������
    @param len string�� ����Ʈ ���� ����
    @ret ������ string�� ����Ʈ ���� ����

    String�� �����ϰ� �ִ� ���ۿ� �� string�� ����Ʈ ���� ���̸� �Է¹޾�
    ASNStr�� ���� �����Ѵ�. ���������δ� ���� �Էµ� ���̸��� ���� ���̸�ŭ��
    ���� �����Ѵ�.

    �� ��� ����ڴ� �� �������̽��� ���� ���� �� ���ٴ� � string type������
    ��������� ǥ���ϱ� ���ؼ� rename�� ���� string type �̸��� �������̽���
    ����ϱ� �ٶ���.
    */
LIBSPEC_ME
int ASNStr_Set(ASNStr *target, const char *in, int len);

/** @ingroup ASN
    @brief ASNStr �ν��Ͻ� Get �Լ�
    @param out string�� ����� ������ ������
    @param maxLen ���ۿ� ������ �� �ִ� string�� �ִ� ����Ʈ ���� ����
    @param source ���� ���� ASNStr�� ������
    @ret value�� ����Ʈ ���� ����

    ASNStr�� ���� �� ���� ���۷� �о�´�. maxLen�� �����ϰ� �ִ� string��
    ���̺��� Ŭ ��쿡�� string�� �� ��ü�� ������ ����, �� ���� �� ����Ʈ��
    0���� �����Ѵ�. maxLen��  �����ϰ� �ִ� string�� ���̺��� ���� ����
    -1�� �����Ѵ�. ����, maxLen�� string�� ���̰� ��Ȯ�� ��ġ�ϴ� ��쿡��
    string �� ��ü���� �����Ѵ�.
    
    �� ��� ����ڴ� �� �������̽��� ���� ���� �� ���ٴ� � string type������
    ��������� ǥ���ϱ� ���ؼ� rename�� ���� string type �̸��� �������̽���
    ����ϱ� �ٶ���.
    */
LIBSPEC_ME
int ASNStr_Get(char *out, int maxLen, const ASNStr *source);

/** @ingroup ASN
    @brief ASNStr �ν��Ͻ� Set �Լ�
    @param target ���� ����� ASNStr�� ������
    @param asnBuf ASNBuf�� ������
    @ret ó���� ����Ʈ ����, ���н� FAIL

    ASNBuf�� ����Ǿ� �ִ� ���̳ʸ����� ASNStr�� �����´�.
    */
LIBSPEC_ME
int ASNStr_SetASNBuf(ASNStr *target, const ASNBuf *asnBuf);

/** @ingroup ASN
    @brief ASNStr �ν��Ͻ� Get �Լ�
    @param source ASNStr ������

    ASNStr�� ����Ǿ� �ִ� ��Ʈ������ ASNBuf�� �����Ͽ� �����Ѵ�.
    ���ϵ� ASNBuf�� ASNBuf_Del�� ����Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.
    */
LIBSPEC_ME
ASNBuf* ASNStr_GetASNBuf(const ASNStr *source);

/** @ingroup ASN
    @param str1 ���ϰ��� �ϴ� ù��° ��Ʈ��
    @param str2 ���ϰ��� �ϴ� �ι�° ��Ʈ��
    @return str1�� str2���� ũ�� �����, ������ 0��, ������ ������ ����Ѵ�.

    ASNStr�� ���Ե� �ΰ��� �����͸� ���Ѵ�. ���������� memcmp�� ����Ͽ�
    ���Ѵ�. ���� ���̰� �ٸ� ��Ʈ���� ���� �񱳴� �� ������ 
    ����(�ּ� ����)������ �� ����� �켱�� �Ѵ�.

    �� ��� ����ڴ� �� �������̽��� ���� ���� �� ���ٴ� � string type������
    ��������� ǥ���ϱ� ���ؼ� rename�� ���� string type �̸��� �������̽���
    ����ϱ� �ٶ���.
    */
LIBSPEC_ME
int     ASNStr_Cmp(const ASNStr *str1, const ASNStr *str2);



/*****************************************************************************/
/** @typedef ASNOctStr
    @ingroup ASN

    ASN.1�� string type���� base type�� ASNStr�� ���� OctetString��
    ����. ��, ASNOctStr�� ASNStr�� �����ϳ�, �� ��� ����� �ÿ���
    string type���� ��������� �����ϱ� ���Ͽ� ASNOctStr(Ȥ�� OctetString)
    �� ����ϱ� �ٶ���.

    ������ PrintableString, UTF8String, IA5String, VisibleString,
    BMPString�� ���������̴�.

    @sa PrintableString UTF8String IA5String VisibleString BMPString
    */
/** @typedef ASNPrintStr
    @ingroup ASN

    ASN.1�� string type���� base type�� ASNStr�� ���� PrintableString��
    ����.
    �ڼ��� ������ OctetString ���� �����ϱ� �ٶ���.

    @sa OctetString
    */
/** @typedef ASNUTF8Str
    @ingroup ASN

    ASN.1�� string type���� base type�� ASNStr�� ���� UTF8String��
    ����.
    �ڼ��� ������ OctetString ���� �����ϱ� �ٶ���.

    @sa OctetString
    */
/** @typedef ASNIA5Str
    @ingroup ASN

    ASN.1�� string type���� base type�� ASNStr�� ���� IA5String��
    ����.
    �ڼ��� ������ OctetString ���� �����ϱ� �ٶ���.

    @sa OctetString
    */
/** @typedef ASNVisibleStr
    @ingroup ASN

    ASN.1�� string type���� base type�� ASNStr�� ���� VisibleString��
    ����.
    �ڼ��� ������ OctetString ���� �����ϱ� �ٶ���.

    @sa OctetString
    */
/** @typedef ASNBMPStr
    @ingroup ASN

    ASN.1�� string type���� base type�� ASNStr�� ���� BMPString��
    ����.
    �ڼ��� ������ OctetString ���� �����ϱ� �ٶ���.

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

    ASNStr_Set�� ASNOctStr�� ���� ASNOctStr_Set���� rename
    */
/** @ingroup ASN
    @def ASNOctStr_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get�� ASNOctStr�� ���� ASNOctStr_Get���� rename
    */
/** @ingroup ASN
    @def ASNPrintStr_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set�� ASNPrintStr�� ���� ASNPrintStr_Set���� rename
    */
/** @ingroup ASN
    @def ASNPrintStr_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get�� ASNPrintStr�� ���� ASNPrintStr_Get���� rename
    */
/** @ingroup ASN
    @def ASNUTF8Str_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set�� ASNUTF8Str�� ���� ASNUTF8Str_Set���� rename
    */
/** @ingroup ASN
    @def ASNUTF8Str_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get�� ASNUTF8Str�� ���� ASNUTF8Str_Get���� rename
    */
/** @ingroup ASN
    @def ASNIA5Str_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set�� ASNIA5Str�� ���� ASNIA5Str_Set���� rename
    */
/** @ingroup ASN
    @def ASNIA5Str_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get�� ASNIA5Str�� ���� ASNIA5Str_Get���� rename
    */
/** @ingroup ASN
    @def ASNVisibleStr_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set�� ASNVisibleStr�� ���� ASNVisibleStr_Set���� rename
    */
/** @ingroup ASN
    @def ASNVisibleStr_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get�� ASNVisibleStr�� ���� ASNVisibleStr_Get���� rename
    */
/** @ingroup ASN
    @def ASNBMPStr_Set
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Set�� ASNBMPStr�� ���� ASNBMPStr_Set���� rename
    */
/** @ingroup ASN
    @def ASNBMPStr_Get
    @sa ASNStr_Set ASNStr_Get

    ASNStr_Get�� ASNBMPStr�� ���� ASNBMPStr_Get���� rename
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
  	@brief ASN.1 Enum Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNEnum Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNEnum Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
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
  	@brief ASN.1 NULL Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNNull Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
    ASNNull Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNNull* ASNNull_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/* ASNNull�� set/get�� �ʿ����. */



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
  	@brief ASN.1 UTCTime Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNUTCTime Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNUTCTime Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNUTCTime* ASNUTCTime_New(ASNDescriptor dsc, ASNBuf *data, ASNOption option);

/** @ingroup ASN
    @def ASNUTCTime_Set
    @sa ASNUTCTime_Get
    ASNUTCTime�� �����ϴ� ��ũ���̴�. struct tm Ÿ���� �Է� �޾� ASNUTCTime��
    utime�� �����Ѵ�.
    */ 
#define ASNUTCTime_Set(utime, in) \
           memcpy(&((ASNUTCTime*)utime)->value, in, sizeof(struct tm))

LIBSPEC_ME
int ASNUTCTime_SetByTimeT(ASNUTCTime* utime, time_t in);

/** @ingroup ASN
    @def ASNUTCTime_Get
    @sa ASNUTCTime_Set
    ASNUTCTime Ÿ���� utime���κ��� struct tm���� ���� �о�´�. 
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
  	@brief ASN.1 GeneralizedTime Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNGenTime Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNGenTime Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNGenTime* ASNGenTime_New(ASNDescriptor dsc, ASNBuf *data, ASNOption option);

/** @ingroup ASN
    @def ASNGenTime_Set
    @sa ASNGenTime_Get
    ASNGenTime�� �����ϴ� ��ũ���̴�. struct tm Ÿ���� �Է� �޾� ASNGenTime��
    utime�� �����Ѵ�.
    */ 
#define ASNGenTime_Set(utime, in)\
           memcpy(&((ASNGenTime*)utime)->value, in, sizeof(struct tm))

#define ASNGenTime_SetByTimeT(utime, in) \
    ASNUTCTime_SetByTimeT((ASNUTCTime*) utime, in)

/** @ingroup ASN
    @def ASNGenTime_Get
    @sa ASNGenTime_Set
    ASNGenTime Ÿ���� utime���κ��� struct tm���� ���� �о�´�. 
    */ 
#define ASNGenTime_Get(out, utime) \
           memcpy(out, &((ASNGenTime*)utime)->value, sizeof(struct tm))

#define ASNGenTime_GetByTimeT(out, utime) \
    ASNUTCTime_GetByTimeT(out, (ASNUTCTime*) utime)

/** @ingroup ASN
    @param out
    @param in
    @sa LocaltimeToGmtime

    in���� �Էµ� local time�� general time���� ��ȯ �� out���� ����Ѵ�.
    */
LIBSPEC_ME
void GmtimeToLocaltime(struct tm *out, const struct tm *in);

/** @ingroup ASN
    @param out
    @param in

    in���� �Էµ� general time�� local time���� ��ȯ �� out���� ����Ѵ�.
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
  	@brief ASN.1 ANY Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNAny Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNAny Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
 */
LIBSPEC_ME
ASNAny* ASNAny_New(ASNDescriptor dsc, ASNBuf *data, ASNOption option);

/** @ingroup ASN
    @brief ASN.1 ANY Ÿ�� Set �Լ�
    @param in �����Ͱ� Setting�� ASNAny Type ������ 
    @param inBuf �Է� ASNBuf�� ������
    @ret ó���� �������� ����Ʈ ���̰� ���ϵȴ�. ���н� FAIL

    */
LIBSPEC_ME
int ASNAny_Set(ASNAny *target, const ASNBuf *inBuf);

LIBSPEC_ME
ERT ASNAny_SetASN(ASNAny *target, const ASN *asn);

/**	@ingroup ASN
    @brief ASN.1 ANY Ÿ�� Get �Լ�
    @param data �о� �� �����Ͱ� �Ҵ�� ���۸� ����Ű�� ������
    @param max_len data�� ����Ű�� ������ �ִ� ����Ʈ ����
    @param in ASNAny Ÿ�� ������ 
    @ret �о� �� �������� ����Ʈ ���̰� ���ϵȴ�. ���н� FAIL

    ��µ� ASNBuf�� �Լ� ���ο��� �޸𸮿� �Ҵ�. ASNBuf_Del�� ����Ͽ�
    �޸𸮸� �����Ͽ��� �Ѵ�.
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
  	@brief ASN.1 OBJECT IDENTIFIER Ÿ�� ���� �� ���ڵ� �Լ�
  	@param dsc Type ��ũ����
  	@param data ���ڵ� ������ ����Ű�� ASNBuf ������
  	@param option Type �ɼ�
  
  	data�� NULL�� ��쿡�� �� �Լ��� ASNOid Ÿ���� 
  	������ �� �����͸� �����Ѵ�. 
  	data�� NULL�� �ƴ� ��� �� �Լ��� ���ڵ� ����(data)�� ������ ���ڵ���
  	ASNOid Ÿ���� ������ �����Ѵ�.
  	option�� ���ڵ�/���ڵ� �� ���� ���� �ԷµǾ�� �Ѵ�.
    */
LIBSPEC_ME
ASNOid* ASNOid_New(ASNDescriptor dsc, ASNBuf *buf, ASNOption option);

/** @ingroup ASN
    @brief ASN.1 OBJECT IDENTIFIER Ÿ�� Set �Լ�
    @param aOid ���� ��� ASNOid ������
    @param oid Oid ������

    Oid�� ASNOid�� �����ϴ� �Լ��̴�.
    */
LIBSPEC_ME
ERT ASNOid_Set(ASNOid *aOid, const Oid *oid);

/** @ingroup ASN
    @brief ASN.1 OBJECT IDENTIFIER Ÿ�� Get ��ũ��

    ASNOid(ansoid)�κ��� Oid(out)�� �����´�.
    */
#define ASNOid_Get(out, asnoid) Oid_Copy((out), &(((ASNOid*)(asnoid))->oid))

/** @ingroup ASN
    @brief ASN.1 OBJECT IDENTIFIER Ÿ�� Set �Լ�
    @param aOid ���� ��� ASNOid ������
    @param nid Nid 

    Nid�� ASNOid�� �����ϴ� �Լ��̴�.
    */
LIBSPEC_ME
ERT ASNOid_SetByNid(ASNOid *aOid, Nid nid);

/** @ingroup ASN
    @brief ASN.1 OBJECT IDENTIFIER Ÿ�� Get ��ũ��

    ASNOid(ansoid)�κ��� Nid�� �����Ѵ�.
    */
#define ASNOid_GetNid(asnoid)  (asnoid->nid)



/******************************************************************************
 * Some types used frequently
 */

/** AlgirithmIdentifier: SEQ 
 *  algorithm�� ������ ������ ���� �� �ִ�.
 *    - NID_passwordBasedMac
 *    - NID_sha1WithRSAEncryption:
 *    - NID_sha1withRSASignature:
 *    - NID_dsa_with_sha1:
 *    - NID_kcdsaWithSHA1:
 *    - NID_kcdsa1WithSHA1:
 *    - NID_kcdsaWithHAS160:
 *    - NID_kcdsa1WithHAS160:
 *    - �׿�(�� ������ �߰��� ��..)
 */
typedef struct _AlgorithmIdentifier {
  ASNSeqClass       klass;
  ASNOid           *algorithm;
  ASNAny           *parameters;
} AlgorithmIdentifier;

/**	@ingroup ASN
    @brief AlgorithmIdentifier Ÿ���� Set �Լ�
    @param ai ������ ������ AlgorithmIdentifier Ÿ���� ������
    @param oid ������ AlgorithmIdentifier Ÿ���� ���� Oid�� ������
    @param para  oid�� �ٴ� parameter�� ������. NULL�� �� �� �ִ�.
    @ret SUCCESS, FAIL

    Oid�� �׿� ������ parameter�� �����Ͽ� AlgorithmIdentifier�� ����
    set�Ѵ�.  parameter���� NULL�� �� �� �ִ�.  NULL�� �Էµ� ��� 
    default���� ASNNull�� ���ڵ��� "\x05\x00"�� �ְ� �ȴ�.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_Set(AlgorithmIdentifier *ai, const Oid *oid, const ASNAny *para);

/**	@ingroup ASN
    @brief AlgorithmIdentifier Ÿ���� Set �Լ�
    @param ai ������ ������ AlgorithmIdentifier Ÿ���� ������
    @param nid ������ AlgorithmIdentifier Ÿ���� ���� Nid
    @param para  oid�� �ٴ� parameter�� ������. NULL�� �� �� �ִ�.
    @ret SUCCESS, FAIL

    Oid ��� Nid�� �Է°��� �� �����ϸ� AlgorithmIdentifier_Set�� �����ϴ�.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_SetNid(AlgorithmIdentifier *ai, Nid nid, const ASNAny *para);

/**	@ingroup ASN
    @brief AlgorithmIdentifier Ÿ���� Set �Լ�
    @param ai ������ ������ AlgorithmIdentifier Ÿ���� ������
    @param nid ������ AlgorithmIdentifier Ÿ���� ���� Nid
    @param para  oid�� �ٴ� parameter�� ������. NULL�� �� �� �ִ�.
    @ret SUCCESS, FAIL

    para ���� Ÿ���� ASN �� ���� �����ϸ� AlgorithmIdentifier_SetNid �� �����ϴ�.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_SetByNid(AlgorithmIdentifier *ai, Nid nid, const ASN *para);

/**	@ingroup ASN
    @brief AlgorithmIdentifier Ÿ���� Get �Լ�
    @param oid ������ AlgorithmIdentifier Ÿ���� ���� �ִ� Oid�� ������
    @param para  oid�� �ٴ� parameter�� ������. NULL�� �� �� �ִ�.
    @param ai ������ ���� AlgorithmIdentifier Ÿ���� ������
    @ret SUCCESS, FAIL

    AlgorithmIdentifier Ÿ���� Oid�� �׿� ������ parameter�� ����
    ���Ѵ�.  parameter���� NULL�� �� �� �ִ�.  NULL�� �Էµ� ��� 
    parameter�� ���� ������ �ʴ´�.
    */
LIBSPEC_ME
ERT AlgorithmIdentifier_Get(Oid *oid, ASNAny *para, const AlgorithmIdentifier *ai);

/**	@ingroup ASN
    @brief AlgorithmIdentifier Ÿ���� Get �Լ�
    @param nid ������ AlgorithmIdentifier Ÿ���� ���� �ִ� Nid
    @param para  oid�� �ٴ� parameter�� ������. NULL�� �� �� �ִ�.
    @param ai ������ ���� AlgorithmIdentifier Ÿ���� ������
    @ret SUCCESS, FAIL

    AlgorithmIdentifier Ÿ���� Nid�� �׿� ������ parameter�� ����
    ���Ѵ�.  parameter���� NULL�� �� �� �ִ�.  NULL�� �Էµ� ��� 
    parameter�� ���� ������ �ʴ´�.
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
LIBSPEC_ME extern ASNAny Any_null; /* ���� ������� ����. */

/** @ingroup ASN
    @brief ASN �ν��Ͻ��� delete�ϴ� �Լ�
    @param data ������ �޸��� ������

    ASN_Del�� ��ũ�ζ� ��� �����ͷ� ���� ��� ���ο��� �̸� ȣ���ϴ�
    �Լ��� �߰��Ѵ�.
    */
LIBSPEC_ME
void ASN_Delete(void *buf);

/** @ingroup ASN
    @brief ASNBuf �ν��Ͻ��� delete�ϴ� �Լ�
    @param data ������ �޸��� ������

    ASNBuf_Del�� ��ũ�ζ� ��� �����ͷ� ���� ��� ���ο��� �̸� ȣ���ϴ�
    �Լ��� �߰��Ѵ�.
    */
LIBSPEC_ME
void ASNBuf_Delete(ASNBuf *buf);


#ifdef ASN_SAFE
/** @ingroup ASN
    @brief ASN_Safe_Buf �ν��Ͻ��� delete�ϴ� �Լ�
    @param buf ������ �޸��� ������
    @param allocSize ������ �޸� ������ ũ��

    �޸� �������� �����ϱ� ���� ���� �޸� �ּҸ� ����� �� �ְ� �߰��� �Լ�.
    */
LIBSPEC_ME
void ASNBuf_Safe_Del(ASNBuf *buf,int allocSize);

/** @ingroup ASN
    @brief ASN_Safe_buf �ν��Ͻ��� new�ϴ� �Լ�
    @param ������ �޸� ������ �� ũ��
    @ret ������ �޸� ������

    �޸� �������� �����ϱ� ���� ���� �޸� �ּҸ� ����� �� �ְ� �߰��� �Լ�.
    */
LIBSPEC_ME
ASNBuf* ASNBuf_Safe_New(int allocSize);

/** @ingroup ASN
    @brief ������ ������ ������ ���ο� ASNBuf�� �����´�.
    @param filePath[in] ������ ������ ���
    @param virSize[out] ASNBuf�� ũ��
    @ret ���� �ÿ��� �Ҵ�� ASNBuf�� ������, ���нÿ��� NULL.

    �ű� ASNBuf�� �Ҵ��� �Ŀ� ������ ����� ������ �о
    �̿� �����Ͽ� �����Ѵ�.
    Base64, PEM, DER ���ڵ��� ������ �����Ѵ�.
    (�޸� �������� �����ϱ� ���� ���� �޸� �ּҸ� ����� �� �ְ� �߰��� �Լ�.)
    */
LIBSPEC_ME
ASNBuf* ASNBuf_Safe_NewFromFile(const char *filePath, int *virSize);

/** @ingroup ASN
    @brief ������ ������ ������ ���ο� ASNBuf�� �����´�.
    @param buf ������ buf
    @param len bufũ��
    @ret ���� �ÿ��� �Ҵ�� ASNBuf�� ������, ���нÿ��� NULL.

    �ű� ASNBuf�� �Ҵ��� �Ŀ� ������ ��ġ�� ���۸� �о
    �̿� �����Ͽ� �����Ѵ�.
    Base64, PEM, DER ���ڵ��� ���۸� �����Ѵ�.
    (�޸� �������� �����ϱ� ���� ���� �޸� �ּҸ� ����� �� �ְ� �߰��� �Լ�.)
    */
LIBSPEC_ME
ASNBuf* ASNBuf_Safe_NewFromBuffer(const char *buf, unsigned int len);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _ASN1_H_ */
