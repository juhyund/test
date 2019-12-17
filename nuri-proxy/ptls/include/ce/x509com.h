#ifndef _X509COM_H_
#define _X509COM_H_

#include "ckm_define.h"
#include "asn1.h"

/** @defgroup X509 X.509 Certificate
 * @ingroup CKM
    @brief Certificate에 관련하여 공용으로 사용하는 타입들과 함수

    Certificate, CRL, Attribute Certificate 과 같은 데이타들을
    다룰 때 사용하는 각종 타입과 함수들을 정의한다.
*/

/** @ingroup X509
    @file x509com.h
    @brief X509 모듈 전체에서 공통으로 사용되는 데이터형과 함수 정의

    Certificate, CRL, Attribute Certificate 과 같은 데이타들을
    다루는 X509 모듈에서 공통으로 사용되는 데이터형과 함수들을 정의한다.
    이곳의 정의들은 x509pkc.h와 x509ac.h에서 사용된다.
*/

/** @addtogroup X509
 * @{ */
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  ER_NAME_NOT_SUPPORTED_ATTRIBUTE = ER_X509COM
} X509COM_ERRORS;


/******************************************************************************
 * UniqiueIdentifier
 */
typedef BitString UniqueIdentifier;
#define AD_UniqueIdentifier AD_BitString

#define UniqueIdentifier_Set(in, data, bitLen) ASNBitStr_Set(in, data, bitLen)
#define UniqueIdentifier_Get(data, maxBitLen, in) ASNBitStr_Set(data, maxBitLen, in)


/******************************************************************************
 * Directory String
 */
enum {
  DirectoryString_printableString = 1,
  DirectoryString_utf8String,
  DirectoryString_bmpString
};

typedef struct _DirectoryString {
  ASNChoiceClass klass;
  int            select;
  union {
/*  TeletexString   *teletexString; */
    PrintableString *printableString;
/*  UniversalString *universalString; */
    UTF8String      *utf8String;
    BMPString       *bmpString;
  } choice;
} DirectoryString;

LIBSPEC_CKM
extern ASNDescriptor AD_DirectoryString;

LIBSPEC_CKM
int DirStr_Set(DirectoryString *target, int choice, const char *in, int len);

LIBSPEC_CKM
int DirStr_Get(int *choice, char *out, int maxLen, DirectoryString *source);


/******************************************************************************
 * Name type
 */
typedef ASNOid AttributeType;
#define AD_AttributeType AD_Oid

typedef ASNAny AttributeValue;
#define AD_AttributeValue AD_Any

typedef struct _AttributeTypeAndValue {
  ASNSeqClass     klass;
  AttributeType   *type;
  AttributeValue  *value;
} AttributeTypeAndValue;

LIBSPEC_CKM
extern ASNDescriptor AD_AttributeTypeAndValue;

typedef struct _SeqOfAttributeTypeAndValue {
  ASNSeqOfClass klass;
  int size;
  AttributeTypeAndValue **member;
} SeqOfAttributeTypeAndValue;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfAttributeTypeAndValue;

/** @ingroup X509
  * @brief   주어진 SeqOfAttributeTypeAndValue로부터 주어진 nid에 해당하는 AttributeTypeAndValue값을 리턴한다.
  *
  * @param *attrs [In] SeqOfAttributeTypeAndValue 값
  * @param  nid   [In] 찾으려는 AttributeTypeAndValue의 nid 값
  *
  * @return
  *   - 해당 값을 찾은 경우 해당 값, 찾기에 실패한 경우 NULL
  */
LIBSPEC_CKM
AttributeTypeAndValue *SeqOfAttributeTypeAndValue_GetPByNid(SeqOfAttributeTypeAndValue *attrs, 
                                                            Nid nid);
LIBSPEC_CKM
void* _SeqOfAttributeTypeAndValue_GetByType(SeqOfAttributeTypeAndValue *attr,
                                            ASNDescriptor dsc,
                                            Nid nid);

/** @ingroup X509
    @function SeqOfAttributeTypeAndValue_GetByType(attr, type, nid)
    @brief 지정한 NID를 갖는 Attribute type의 한 AttributeTypeAndValue 멤버를 구하고
           이의 내용을 디코딩하여 실제 필요한 type을 구한다..
    @param exts     [in]  SeqOfAttributeTypeAndValue 값
    @param type     [in]  Any Type으로 되어 있는 AttributeValue의 실제 type
    @param nid      [in]  구하고자 하는 NID

    SeqOfAttributeTypeAndValue의 멤버중 지정한 NID를 갖는 AttributeTypeAndValue를 찾은 후, 
    이의 내용을 주어진 type 정보로 전환하여 리턴한다.

    @code
    SeqOfAttributeTypeAndValue *attr;
    OldCertId                  *certId;
    
    ...
    certId = SeqOfAttributeTypeAndValue_GetByType(attr, OldCertId, NID_oldCertId);
    @endcode
    @note SeqOfAttributeAndValue에 동일한 type이 복수개가 존재하는 경우, 가장 처음 값만을 리턴한다.
*/
#define SeqOfAttributeTypeAndValue_GetByType(attr, type, nid) \
          (type*) _SeqOfAttributeTypeAndValue_GetByType((attr), (AD_##type), (nid))

/** @ingroup X509
 *  @brief 지정한 Nid를 갖는 AttributeTypeAndValue를 SeqOfAttributeTypeAndValue
 *  에 추가한다.
 *  @param *attrs   [out]  내용을 추가할 SeqOfAttributeTypeAndValue
 *  @param  type    [in]   AttributeTypeAndValue의 type
 *  @param *value   [in]   AttributeTypeAndValue의 value
 *
 *  @return SUCCESS or FAIL
 */
LIBSPEC_CKM
int SeqOfAttributeTypeAndValue_Add(SeqOfAttributeTypeAndValue *attrs,
                                   Nid  type,
                                   ASN *value);

typedef struct _SetOfAttributeValue {
  ASNSetOfClass klass;
  int              size;
  AttributeValue **member;
} SetOfAttributeValue;

LIBSPEC_CKM
extern ASNDescriptor AD_SetOfAttributeValue;

typedef struct _Attribute {
  ASNSeqClass klass;
  AttributeType       *type;
  SetOfAttributeValue *values;
} Attribute;

LIBSPEC_CKM
extern ASNDescriptor AD_Attribute;

/** @ingroup X509
    @brief Attribute type에 원하는 attribute value를 넣는다.
    @param att [out] 내용을 지정하려는 Attribute type.
    @param oid [in]  들어갈 attribute value 들의 Object Identifier.

    한 Attribute type에 parameter oid로 표시되는 여러 개의
    attribute value 들을 넣는다.
    parameter oid 뒤의 "..."의 영역에는 임의의 ASN type의 여러 포인터들이
    들어올 수 있다.  반드시 제일 마지막 파라메터에는 NULL을 넣어 입력의 끝임을
    표시해야 한다.

    @code
    Attribute_Set(att, &Oid_value, value1, value2, value3, NULL);
    @endcode
 */
LIBSPEC_CKM
int Attribute_Set(Attribute *att, Oid *oid, ...);

/** @ingroup X509
    @brief Attribute type에 원하는 attribute value를 추가한다.
    @param att [out] 내용을 추가하려는 Attribute type.

    이미 내용을 갖고 있는 기존의 Attribute type에 새로운 attribute value 들을
    넣는다.  Attribute_Set() 함수와 마찬가지로 "..."의 영역에는 임의의 ASN
    type의 여러 포인터들이 들어올 수 있다.  반드시 제일 마지막 파라메터에
    NULL을 넣어 입력의 끝임을 표시해야 한다.

    @sa Attribute_Set
 */
LIBSPEC_CKM
int Attribute_Add(Attribute *att, ...);

typedef struct _SetOfAttribute {
  ASNSetOfClass klass;
  int              size;
  Attribute      **member;
} SetOfAttribute;

LIBSPEC_CKM
extern ASNDescriptor AD_SetOfAttribute;

typedef struct _SeqOfAttribute {
  ASNSeqOfClass klass;
  int              size;
  Attribute      **member;
} SeqOfAttribute;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfAttribute;

typedef SetOfAttribute Attributes;
#define AD_Attributes AD_SetOfAttribute

/** @ingroup X509
    @brief SeqOfAttribute에 복수개의 value를 갖는 하나의 Attribute를 추가한다.
    @param atts [out] 내용을 추가하고자 하는 SeqOfAttribute type.
    @param oid [in]  들어갈 attribute value 들의 Object Identifier.

    함수 내부에서 Attribute_Set와 동일한 기능을 수행하여 
    Attribute를 하나 생성하여 이를 SeqOfAttribute에 추가한다.
    추가하는 Attribute type에 parameter oid가 추가된다.
    parameter oid 뒤의 "..."의 영역에는 임의의 ASN type의 여러 포인터들이
    들어올 수 있다.  반드시 제일 마지막 파라메터에는 NULL을 넣어 입력의 끝임을
    표시해야 한다.

    @code
    SeqOfAttribute_Add(atts, &Oid_value, value1, value2, value3, NULL);
    @endcode

    @sa Attribute_Set
 */
LIBSPEC_CKM
ERT SeqOfAttribute_Add(SeqOfAttribute *atts, Oid *oid, ...);

LIBSPEC_CKM
ERT SeqOfAttribute_CheckAttTypeUniqueness(SeqOfAttribute *atts);


typedef struct _RelativeDistinguishedName {
  ASNSetOfClass klass;
  int                     size;
  AttributeTypeAndValue **member;
} RelativeDistinguishedName;

LIBSPEC_CKM
extern ASNDescriptor AD_RelativeDistinguishedName;

typedef struct _RDNSequence {
  ASNSeqOfClass klass;
  int                         size;
  RelativeDistinguishedName **member;
} RDNSequence;

LIBSPEC_CKM
extern ASNDescriptor AD_RDNSequence;

enum{
  Name_rdnSequence  = 1
};
typedef struct _Name {
  ASNChoiceClass klass;
  int            select;
  union {
    RDNSequence *rdnSequence;
  } choice;
} Name;

LIBSPEC_CKM
extern ASNDescriptor AD_Name;

/** @ingroup X509
    @brief Name type에 필요한 내용을 set한다. 
    @param name [out] 내용을 지정할 Name type.
    @param fmt  [in]  어떠한 내용이 들어올지에 대한 format.
 
    Name type에 필요한 내용을 지정한다. printf 등의 일반적인 C 함수처럼
    format을 지정하여 들어올 내용이 어떤 것인지 지정한다.
    일반적인 format은 다음과 같은 형태이다.

    @code
    "C,uO,uOU,bCN"
    C  = Contry
    O  = Organization
    OU = Organization Unit
    CN = Common Name
    E  = E-mail
    UID = Serial Number

    u  = UTF8 String
    b  = BMP String
    @endcode

    한글이 입력일 때는 앞에 "u"나 "b"를 붙여서 이 문자열을 UTF8이나
    BMP 형태로 저장하도록 해야한다.
  
    만일 Set이 아니라 Add를 할 경우에는 format 제일 앞에 '+' 혹은 '<'
    를 붙여서 사용한다다.

    @code
    "+C,CN"  "<CN"
    @endcode

    같은 레벨에 둘 이상이 들어갈 때는 이들을 '+'로 묶는다.

    @code
    "C,O,OU,OU,CN+E"
    @endcode

    실제로는 이런 식으로 사용할 수 있다.

    @code
    Name_Set(name, "C,uO,uOU,bCN", "KR", "펜타시큐리티 시스템",
             "암호 기술팀", "그때 그사람");
    @endcode
*/

LIBSPEC_CKM
ERT Name_Set(Name *name, const char *fmt, ...);


/** @ingroup X509
    @brief Name type에 들어있는 내용들 중 한 항목의 문자열을 구한다. 
    @param output  [out] 결과 문자열이 저장될 공관
    @param max_len [in]  output buffer의 최대 길이.
    @param oid     [in]  구한 항목의 oid 
    @param height  [in]  구하려는 항목의 깊이 위치. 깊이의 순서는 C,O,OU,CN
                         순이다.
    @param width   [in]  CN와 Email과 같이 같은 깊이에 여러 항목이 있을 때,
                         그 중 구하려는 항목의 index.
    @return 구한 항목이 어떤 종류의 문자열로 구성되었는지를 표시하는 tag 번호.
            0 이면 아무것도 구하지 못했다는 뜻이다.
    @retval TAG_UTF8STRING 리턴된 문자열이 UTF8 문자열
    @retval TAG_BMPSTRING 리턴된 문자열이 BMP 문자열
    @retval TAG_PRINTABLE 리턴된 문자열이 일반적인 printable 문자열
 
    Name type에 저장된 항목들중 원하는 것을 지정하여 실제 사용가능한
    항목의 문자열을 구하는 함수이다다.

    Name type은
    directory의 구조 그대로 되어 있으므로 C와 같은 상위 항목부터 CN과
    같은 하위 항목이 순서대로 저장되어 있다.  이 순서를 이 함수에서는
    parameter height로 표시한다. CN과 Email 등의 항목은
    그 순위가 같아서 같은 height를 가지는데 이때 이 둘의 구별은
    parameter width로 한다. 즉 width와 height를 하나씩 증가시키면서 

    다음 예제 코드는 Name_Sprint()에 사용된 코드이다. 이 조금은 복잡한
    Name_Get() 함수를 어떻게 사용해야 하는지에 대한 좋은 예제이다.

    @code
    int i, j;
    char line[256];
    Name name;
    Nid  nid;

      for(i=0;;i++) {
        for(j=0;;j++) {

          if((ret = Name_Get(line, 256, &nid, name, i, j)) == 0) break;

          switch(nid) {
          case NID_commonName:
            strcat(content, "CN = ");
            break;
          case NID_emailAddress:
            strcat(content, "     EMAIL = ");
            break;

            ......
          }

          switch(ret) {
              case TAG_UTF8STRING:
                  CHARSET_Utf8ToEuckr(line2, &len, line);
                  sprintf(line3, "%s [UTF8]\n", line2);
                  strcat(content, line3);
                  break;

              case TAG_BMPSTRING:
                  CHARSET_Utf16ToEuckr(line2, &len, line);
                  sprintf(line3, "%s [BMP(UTF16)]\n", line2);
                  strcat(content, line3);
                  break;

              default :
                  sprintf(line3, "%s [Printable]\n", line);
                  strcat(content, line3);
          }
        }
        if(j == 0) break;
      }
     @endcode
*/
LIBSPEC_CKM
ASN_UNIVERSAL_TAG Name_Get(char *output, int max_len, Nid *nid, Name *name, int depth, int width);


/** @ingroup X509
    @brief 두개의 Name type을 비교한다.
    @param name1 [in] 비교하려는 Name type 1.
    @param name2 [in] 비교하려는 Name type 2.
    @return 둘이 같은 때는 SUCCESS, 다르면 FAIL.

    두개의 Name type이 있을 때, 이 둘의 내용이 일치하는지 비교한다.
*/
LIBSPEC_CKM
int Name_Compare(Name *name1, Name *name2);


/** @ingroup X509
    @brief Name type의 모든 내용을 문자열로 출력.
    @param content [out] 출력된 문자열
    @param max_len [in]  content buffer의 최대 길이
    @param name    [in]  내용을 출력할 Name type.

    @sa Name_SprintLine
*/
LIBSPEC_CKM
int Name_Sprint(char *content, int max_len, Name *name);

/** @ingroup X509
    @brief Name type의 모든 내용을 문자열로 출력.
    @param content [out] 출력된 문자열
    @param max_len [in]  content buffer의 최대 길이
    @param name    [in]  내용을 출력할 Name type.

    Name type을 한 줄로 ','를 구분자로 하여 출력한다.
    파일 시스템 저장에 사용할 수 있도록 '/' 문자는 '%2F'로
    '%'는 '%%'로 변환하여 다룬다.

    @sa Name_Sprint
    @return
      - 성공 시 : 출력된 문자열의 길이
      - 실패 시 : FAIL(-1)
*/
LIBSPEC_CKM
int Name_SprintLine(char *content, int max_len, Name *name);

typedef struct _NamePrintCtx {
  int    size;
  struct {
    char type[8];
    char value[64];
  } attr[16];
} NamePrintCtx;

LIBSPEC_CKM
NamePrintCtx *Name_NewPrintCtx(Name *name);

LIBSPEC_CKM
void Name_DelPrintCtx(NamePrintCtx *print);


LIBSPEC_CKM
ERT RelativeDistinguishedName_SetByStr
    (RelativeDistinguishedName *rdn, const char *string);

LIBSPEC_CKM
ERT Name_SetByStr(Name *name, const char *string);


/******************************************************************************
 * General Names
 */
typedef struct _EDIPartyName {
  ASNSeqClass     klass;
  DirectoryString *nameAssigner;
  DirectoryString *partyName;
} EDIPartyName;

LIBSPEC_CKM
extern ASNDescriptor AD_EDIPartyName;

typedef struct _OtherName {
  ASNSeqClass klass;
  ASNOid     *type_id;
  ASNAny     *value;
} OtherName;

LIBSPEC_CKM
extern ASNDescriptor AD_OtherName;

enum {
  GeneralName_otherName = 1,
  GeneralName_rfc822Name,
  GeneralName_dNSName,
  GeneralName_directoryName,
  GeneralName_ediPartyName,
  GeneralName_uniformResourceIdentifier,
  GeneralName_iPAddress,
  GeneralName_registeredID
};

typedef struct _GeneralName {
  ASNChoiceClass klass;
  int            select;
  union {
    OtherName    *otherName;
    IA5String    *rfc822Name;
    IA5String    *dNSName;
  /*ORAddress    *x400Address; - not supported*/
    Name         *directoryName;
    EDIPartyName *ediPartyName;
    IA5String    *uniformResourceIdentifier;
    OctetString  *iPAddress;
    ASNOid       *registeredID;
  } choice;
} GeneralName;

LIBSPEC_CKM
extern ASNDescriptor AD_GeneralName;


/** @ingroup X509
    @brief GeneralName type의 모든 내용을 문자열로 출력.
    @param content     [out] 출력된 문자열
    @param content_max [in]  content buffer의 최대 길이
    @param gn          [in]  내용을 출력할 GeneralName type.
*/
LIBSPEC_CKM
int GeneralName_Sprint(char *content, int content_max, GeneralName *gn);

typedef struct _GeneralNames {
  ASNSeqOfClass klass;
  int            size;
  GeneralName  **member;
} GeneralNames;

LIBSPEC_CKM
extern ASNDescriptor AD_GeneralNames;

/** @ingroup X509
    @brief GeneralName type에 필요한 내용을 지정한다.
    @param target [out] 내용을 지정할 GneneralName type.
    @param choice [int] 다음에 이어질 내용이 어떤 타입인지를 표시

    Choice 구조로 이루어진 GeneralName type의 내용을 설정한다.
    파라메터인 choice가 다음 파라메터로 어떤 타입이 오게 되는지를
    표시한다.

    @code
 parameter '...' will be accessed in following forms according to choice
 
[#] means tag number

[0] otherName
  GenName_Set(target, GeneralName_otherName, Oid *type_id, ASNBuf *value);

[1] rfc822Name
  GenName_Set(target, GeneralName_rfc822Name, char *inData, int inLen);

[2] dNSName
  GenName_Set(target, GeneralName_dNSName, char *inData, int inLen);

[4] directoryName
Name *name = ASN_New(AD_Name, NULL);
  GenName_Set(target, GeneralName_directoryName, name);

[5] ediPartyName
  GenName_Set(target, GeneralName_ediPartyName,
    DirectoryString_printableString, char *nameAssigner, int Len,
    DirectoryString_utf8String, char *partyName, int len);

  GenName_Set(target, GeneralName_ediPartyName, NULL
    DirectoryString_utf8String, char *partyName, int Len)

[6] uniformResourceIdentifier :
  GenName_Set(target, GeneralName_uniformResourceIdentifier, char *inData, int inLen);

[7] iPAddress
  GenName_Set(target, GeneralName_iPAddress, char *inData, int inLen);

[8] registerdID
  GenName_Set(target, GeneralName_registeredID, Oid *oid);

  @endcode
*/
LIBSPEC_CKM
int GenName_Set(GeneralName *target, int choice, ...);

/** @ingroup X509
    @brief GeneralNames type에 새 GeneralName 타입을 추가
    @param target [out] GeneralNames type.
    @param name   [in]  추가될 GeneralName type.

    GeneralName type을 GeneralNames type의 한 멤버로 추가한다.
    추가된 GeneralName type은 GeneralNames type의 멤버가 되기 때문에
    따로 ASN_Del()을 하여줄 필요가 없다.
*/
LIBSPEC_CKM
int GenNames_AddGenName(GeneralNames *target, GeneralName *name);

/** @ingroup X509
    @brief GeneralNames type에 새 Name 타입을 추가
    @param target [out] GeneralNames type.
    @param name   [in]  추가될 Name type.

    가장 자주 쓰이는 Name type을 GeneralNames type의 한 멤버로
    추가한다.
    추가된 Name type은 GeneralNames type의 멤버가 되기 때문에
    따로 ASN_Del()을 하여줄 필요가 없다.

    @sa GenNames_AddGenName
*/
LIBSPEC_CKM
int GenNames_AddByName(GeneralNames *target, Name *name);



/** @ingroup X509
    @brief GeneralNames type의 모든 내용을 문자열로 출력.
    @param content     [out] 출력된 문자열
    @param content_max [in]  content buffer의 최대 길이
    @param gns         [in]  내용을 출력할 GeneralNames type.
*/
LIBSPEC_CKM
int GeneralNames_Sprint(char *content, int content_max, GeneralNames *gns);


/******************************************************************************
 * Extension
 */
typedef struct _Extension {
  ASNSeqClass       klass;
  ASNOid           *extnID;
  ASNBool          *critical;
  ASNOctStr        *extnValue;
} Extension;  

LIBSPEC_CKM
extern ASNDescriptor AD_Extension;

/** @ingroup X509
    @typedef ExtPrintCtx

    Extension(Ext)타입에 대한 스트링 출력을 위해서 만든 데이터 형.
    공개키 인증서와 속성 인증서에 모두 사용 가능하다.
 */
typedef struct _ExtPrintCtx {
  char name[128];
  int  critical;
  char value[2048];
} ExtPrintCtx;


/** @ingroup X509
    @brief Extension type의 내용을 지정한다.
    @param ext      [out]  Extension type
    @param oid      [in]  새로 지정될 내용의 OID
    @param critical [in]  새로 지정될 내용의 critical 여부.  1 또는 0 이다.
    @param in       [in]  Extension type의 내용이 될 ASN type

    Extension type의 내용을 지정한다.  OID와 critical 여부, DER 인코딩되어
    들어갈 ASN type이 입력으로 들어온다.

    @code
    Extension *ext;
    KeyUsage  *ku;
    ....
    Extension_Set(ext, &Oid_keyUsage, 0, ASN(ku));
    @endcode
*/
LIBSPEC_CKM
int Extension_Set(Extension *ext, Oid *oid, int critical, ASN *in);

LIBSPEC_CKM
int Extension_SetByNid(Extension *ext, Nid nid, int critical, ASN *in);

/** @ingroup X509
    @brief Extension type의 내용을 읽는다.
    @param oid      [out] Extension 내용의 OID
    @param critical [out] Extension 내용의 critical 여부.  1 또는 0 이다.
    @param ext      [in]  Extension type
    @return DER 인코딩되어 있는 Extension의 내용이다. ASN type으로 바꾸기
           위해서는 DER 디코딩을 해야한다.

    Extension type의 내용을 구한다.  OID와 critical 여부, DER 인코딩된
    ASN type이 출력이다.  리턴된 ASNBuf의 내용은
    DER 디코딩을 통해 원하는 ASN type으로 변환하여야 한다.

    @code
    Extension *ext;
    KeyUsage  *ku;
    Oid        oid;
    ASNBuf    *buf;
    int        critical
    ....
    buf = Extension_Get(&oid, &critical, ext);
    ku = ASN_New(KeyUsage, buf);
    @endcode

    @sa Extension_GetByType
*/
LIBSPEC_CKM
ASNBuf* Extension_Get(Oid *oid, int *critical, Extension *ext);

LIBSPEC_CKM
void* _Extension_GetByType(int *critical, Extension *ext, ASNDescriptor dsc);

/** @ingroup X509
    @function Extension_GetByType(critical, ext, type)
    @brief Extension type의 DER 인코딩된 내용을 읽어 이를 디코딩하여 리턴한다.
    @param critical [out] Extension 내용의 critical 여부.  1 또는 0 이다.
    @param ext      [in]  Extension type
    @param type     [in]  DER 인코딩되어 있는 Extension 내용의 실제 type
    @return Extension의 내용이 DER 디코딩되어 일반적인 ASN type으로 리턴된다.

    
    Extension type의 내용을 구하는 Extension_Get() 함수의 개선판이다.
    critical 여부와 함께 DER 디코딩된 ASN type이 출력으로 나온다.
    Extension_Get()과는 달리 매개 ASNBuf type이 필요없고 별다른 디코딩 과정이
    없다.

    @code
    Extension *ext;
    KeyUsage  *ku;
    int        critical
    ....
    ku = Extension_GetByType(&critical, ext, KeyUsage);
    @endcode

    @sa Extension_Get
*/
#define Extension_GetByType(critical, ext, type) \
     (type*) _Extension_GetByType((critical), (ext), (AD_##type))


/******************************************************************************
 * Extensions
 */
typedef struct _Extensions {
  ASNSeqOfClass     klass;
  int                size;
  Extension         **member;
} Extensions;

LIBSPEC_CKM
extern ASNDescriptor AD_Extensions;

/** @ingroup X509
    @typedef ExtsPrintCtx

    Extensions(Exts)타입에 대한 스트링 출력을 위해서 만든 데이터 형.
    공개키 인증서와 속성 인증서에 모두 사용 가능하다.
 */
typedef struct _ExtsPrintCtx {
  int          size;
  ExtPrintCtx *exts;
} ExtsPrintCtx;

/** @ingroup X509
    @function Extensions_AddP(exts, ext)
    @brief Extensions type의 한 멤버로 Extension type을 추가한다.
    @param exts [out] Extensions type
    @param ext  [in]  Extension type
    
    Extensions type의 한 멤버로 Extension type을 추가한다.
    추가된 Extension type에 대해서는 별도의 ASN_Del 작업을 해줄
    필요가 없다.

    @sa Extensions_Add
*/
#define Extensions_AddP(exts, ext) ASNSeqOf_AddP(ASN_SEQOF(exts), ASN(ext))

/** @ingroup X509
    @brief Extensions type의 한 멤버를 새롭게 생성하여 추가한다.
    @param exts     [out] Extensions type
    @param oid      [in] 새롭게 만들어질 Extension type의 OID
    @param critical [in] 새롭게 만들어질  Extension type의 critical 여부
    @param in       [in] 새롭게 만들어질 Extension type의 ASN type

    Extensions type의 한 멤버로 새로운 Extension type을 추가한다.
    Extesions_AddP()와 달리 Extension type을 미리 만들어서 추가하는
    것이 아니라, 함수 내부에서 신규 Extension type을 만든 다음에
    이것을 추가한다.

    @sa Extensions_AddP
*/
LIBSPEC_CKM
int Extensions_Add(Extensions *exts, Oid *oid, int critical, ASN *in);

LIBSPEC_CKM
int Extensions_AddByNid(Extensions *exts, Nid nid, int critical, ASN *in);

/** @ingroup X509
    @brief 지정한 OID를 갖는 Extensions type의 한 멤버를 구한다.
    @param exts [in] Extensions type
    @param oid  [in] 구하고자 하는 OID

    지정한 OID를 갖는 Extensions type의 한 멤버를 구한다.
    구해진 Extension type의 포인터는 Extention type 내부의 한 멤버의
    포인터일 따름이므로 절대로 ASN_Del()로 지워서는 안된다.

    @sa Extensions_GetPByOid
*/
LIBSPEC_CKM
Extension* Extensions_GetPByOid(Extensions *exts, Oid *oid);

/** @ingroup X509
    @brief 지정한 NID를 갖는 Extensions type의 한 멤버를 구한다.
    @param exts [in] Extensions type
    @param nid  [in] 구하고자 하는 NID

    지정한 NID를 갖는 Extensions type의 한 멤버를 구한다.
    구해진 Extension type의 포인터는 Extention type 내부의 한 멤버의
    포인터일 따름이므로 절대로 ASN_Del()로 지워서는 안된다.

    @sa Extensions_GetPByNid
*/
LIBSPEC_CKM
Extension* Extensions_GetPByNid(Extensions *exts, Nid nid);

/** @ingroup X509
    @brief 지정한 OID를 갖는 Extensions type의 한 멤버를 제거한다.
    @param exts [in] Extensions type
    @param oid  [in] 제거하고자 하는 OID

    지정한 OID를 갖는 Extensions type의 한 멤버를 제거한다.
*/
LIBSPEC_CKM
int Extensions_DelByOid(Extensions *exts, Oid *oid);

/** @ingroup X509
    @brief 지정한 NID를 갖는 Extensions type의 한 멤버를 제거한다.
    @param exts [in] Extensions type
    @param oid  [in] 제거하고자 하는 NID

    지정한 NID를 갖는 Extensions type의 한 멤버를 제거한다.
*/
LIBSPEC_CKM
int Extensions_DelByNid(Extensions *exts, Nid nid);

LIBSPEC_CKM
void* _Extensions_GetByType(int *critical, 
                            Extensions *exts,
                            ASNDescriptor dsc, 
                            Nid nid);

/** @ingroup X509
    @function Extensions_GetByType(critical, exts, type, nid)
    @brief 지정한 NID를 갖는 Extensions type의 한 extension 멤버를 구하고
           이의 내용을 디코딩하여 실제 필요한 type을 구한다..
    @param critical [out] 구한 Extension type의 critical 여부
    @param exts     [in]  Extensions type
    @param type     [in]  DER 인코딩되어 있는 Extension 내용의 실제 type
    @param nid      [in]  구하고자 하는 NID

    Extensions type의 멤버들 중 지정한 NID를 갖는 extension을 찾은 후,
    이의 내용을 디코딩하여 실제 내용을 구한다.

    @code
    Extensions exts;
    KeyUsage  *ku;
    int        critical;
    ...
    ku = Extensions_GetByType(&critical, exts, KeyUsage, NID_KeyUsage);
    @endcode
    @sa Extension_GetByType
*/
#define Extensions_GetByType(critical, exts, type, nid) \
     (type*) _Extensions_GetByType((critical), (exts), (AD_##type), (nid))


/******************************************************************************
 * Version
 */
typedef ASNInt Version;
#define AD_Version AD_Integer

#define Version_Set(ver, num) ASNInt_SetInt(ver, num)
#define Version_Get(num, ver) ASNInt_GetInt(num, ver)

enum {
  CERT_VER1 = 0,
  CERT_VER2,
  CERT_VER3
};


/******************************************************************************
 * CertificateSerialNumber
 */
typedef ASNInt CertificateSerialNumber;
#define AD_CertificateSerialNumber AD_Integer

#define CertificateSerialNumber_Set(serial, in, len) \
        ASNInt_SetBin(serial, in, len)

#define CertificateSerialNumber_Get(out, mlen, serial) \
        ASNInt_GetBin(out, mlen, serial)

#define CertificateSerialNumber_GetStr(out, mlen, serial) \
        ASNInt_GetStr(out, mlen, serial)


/** @ingroup X509
    @brief CertificateSerialNumber의 내용을 주어진 값들을 토대로 생성한다.
    @param sn [out] 생성된 일련번호가 저장될 데이터
    @param issuer  [in]  발급자 DN
    @param subject [in]  피발급자 DN
    @return 성공적으로 생성되면 SUCCESS가 리턴되고, 그렇지 않으면 FAIL

    발급자의 DN과 피발급자의 DN을 입력으로 받아 들이고, 내부적으로 발급 시간을 
    얻어내어 이 세가지 정보를 기준으로 128bit 길이의 인증서
    serial number를 생성한다.  milli-second 단위의 시간을 사용하므로
    같은 millisecond에 같은 발급자 DN, 사용자 DN을 쓰는 인증서를
    발급하지 않는한, 동일한 serial number가 생성될 가능성은 거의 없다.

    @code
      nowTime := Time in seconds since midnight (00:00:00), January 1, 1970, 
      coordinated universal time (UTC) 
      millitm := Fraction of a second in milliseconds
      TimeInfoForSerialNumber ::= SEQUENCE {
        nowTime     UTCTime;
        millitm     INTEGER;
        issuerName  Name;
        subjectName Name;
      }
      hash := SHA1( DER Encoding of TimeInfoForSerialNumber )
      hashA || hashB := hash
      hash' := hashA ^ hashB
      sn := nowTime(32 bits) || millitm(16 bits) || hash'(80 bits)
    @endcode
*/
LIBSPEC_CKM
int CertificateSerialNumber_Gen(CertificateSerialNumber *sn,
                                Name *issuer, 
                                Name *subject);

/** @ingroup X509
    @brief CertificateSerialNumber_Gen의 변형
    @param sn [out] 생성된 일련번호가 저장될 데이터
    @param issuer  [in]  발급자 정보가 들어 있는 ASN 타입
    @param subject [in]  피발급자 정보가 들어 있는 ASN 타입 
    @return 성공적으로 생성되면 SUCCESS가 리턴되고, 그렇지 않으면 FAIL

    발급자와 피발급자의 정보가 포함된 두가지 입력 issuer와 subject와 함께
    발급 시간을 정보를 기준으로 128bit 길이의 인증서
    serial number를 생성한다. 생성 로직은 CertificateSerialNumber_Gen와
    동일하지만 TimeInfoForSerialNumber2의 DER 값을 입력으로 사용하는 것이
    다르다.
    TimeInfoForSerialNumber2의 issuerInfo와 subjectInfo의 데이터에는 
    입력 파라미터 issuer와 subject의 DER 인코딩 값이 각각 들어간다.

    @code
      nowTime := Time in seconds since midnight (00:00:00), January 1, 1970, 
      coordinated universal time (UTC) 
      millitm := Fraction of a second in milliseconds
      TimeInfoForSerialNumber2 ::= SEQUENCE {
        nowTime     UTCTime;
        millitm     INTEGER;
        issuerInfo  OCTET STRING;
        subjectInfo OCTET STRING;
      }
      hash := SHA1( DER Encoding of TimeInfoForSerialNumber2 )
      hashA || hashB := hash
      hash' := hashA ^ hashB
      sn := nowTime(32 bits) || millitm(16 bits) || hash'(80 bits)
    @endcode
*/
LIBSPEC_CKM
int CertificateSerialNumber_Gen2(CertificateSerialNumber *sn,
                                 ASN                     *issuer, 
                                 ASN                     *subject);


/******************************************************************************
 * SubjectPublicKeyInfo
 */

typedef struct _SubjectPublicKeyInfo {
  ASNSeqClass klass;
  AlgorithmIdentifier *algorithm;
  BitString           *subjectPublicKey;
} SubjectPublicKeyInfo;

LIBSPEC_CKM
extern ASNDescriptor AD_SubjectPublicKeyInfo;




/******************************************************************************
 * Extra Utilities
 */

LIBSPEC_CKM
int TM_Compare(struct tm *a, struct tm *b);

#ifdef __cplusplus
}
#endif
/** @} */
        
#endif /* _X509COM_H_ */

