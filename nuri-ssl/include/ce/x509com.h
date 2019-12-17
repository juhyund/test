#ifndef _X509COM_H_
#define _X509COM_H_

#include "ckm_define.h"
#include "asn1.h"

/** @defgroup X509 X.509 Certificate
 * @ingroup CKM
    @brief Certificate�� �����Ͽ� �������� ����ϴ� Ÿ�Ե�� �Լ�

    Certificate, CRL, Attribute Certificate �� ���� ����Ÿ����
    �ٷ� �� ����ϴ� ���� Ÿ�԰� �Լ����� �����Ѵ�.
*/

/** @ingroup X509
    @file x509com.h
    @brief X509 ��� ��ü���� �������� ���Ǵ� ���������� �Լ� ����

    Certificate, CRL, Attribute Certificate �� ���� ����Ÿ����
    �ٷ�� X509 ��⿡�� �������� ���Ǵ� ���������� �Լ����� �����Ѵ�.
    �̰��� ���ǵ��� x509pkc.h�� x509ac.h���� ���ȴ�.
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
  * @brief   �־��� SeqOfAttributeTypeAndValue�κ��� �־��� nid�� �ش��ϴ� AttributeTypeAndValue���� �����Ѵ�.
  *
  * @param *attrs [In] SeqOfAttributeTypeAndValue ��
  * @param  nid   [In] ã������ AttributeTypeAndValue�� nid ��
  *
  * @return
  *   - �ش� ���� ã�� ��� �ش� ��, ã�⿡ ������ ��� NULL
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
    @brief ������ NID�� ���� Attribute type�� �� AttributeTypeAndValue ����� ���ϰ�
           ���� ������ ���ڵ��Ͽ� ���� �ʿ��� type�� ���Ѵ�..
    @param exts     [in]  SeqOfAttributeTypeAndValue ��
    @param type     [in]  Any Type���� �Ǿ� �ִ� AttributeValue�� ���� type
    @param nid      [in]  ���ϰ��� �ϴ� NID

    SeqOfAttributeTypeAndValue�� ����� ������ NID�� ���� AttributeTypeAndValue�� ã�� ��, 
    ���� ������ �־��� type ������ ��ȯ�Ͽ� �����Ѵ�.

    @code
    SeqOfAttributeTypeAndValue *attr;
    OldCertId                  *certId;
    
    ...
    certId = SeqOfAttributeTypeAndValue_GetByType(attr, OldCertId, NID_oldCertId);
    @endcode
    @note SeqOfAttributeAndValue�� ������ type�� �������� �����ϴ� ���, ���� ó�� ������ �����Ѵ�.
*/
#define SeqOfAttributeTypeAndValue_GetByType(attr, type, nid) \
          (type*) _SeqOfAttributeTypeAndValue_GetByType((attr), (AD_##type), (nid))

/** @ingroup X509
 *  @brief ������ Nid�� ���� AttributeTypeAndValue�� SeqOfAttributeTypeAndValue
 *  �� �߰��Ѵ�.
 *  @param *attrs   [out]  ������ �߰��� SeqOfAttributeTypeAndValue
 *  @param  type    [in]   AttributeTypeAndValue�� type
 *  @param *value   [in]   AttributeTypeAndValue�� value
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
    @brief Attribute type�� ���ϴ� attribute value�� �ִ´�.
    @param att [out] ������ �����Ϸ��� Attribute type.
    @param oid [in]  �� attribute value ���� Object Identifier.

    �� Attribute type�� parameter oid�� ǥ�õǴ� ���� ����
    attribute value ���� �ִ´�.
    parameter oid ���� "..."�� �������� ������ ASN type�� ���� �����͵���
    ���� �� �ִ�.  �ݵ�� ���� ������ �Ķ���Ϳ��� NULL�� �־� �Է��� ������
    ǥ���ؾ� �Ѵ�.

    @code
    Attribute_Set(att, &Oid_value, value1, value2, value3, NULL);
    @endcode
 */
LIBSPEC_CKM
int Attribute_Set(Attribute *att, Oid *oid, ...);

/** @ingroup X509
    @brief Attribute type�� ���ϴ� attribute value�� �߰��Ѵ�.
    @param att [out] ������ �߰��Ϸ��� Attribute type.

    �̹� ������ ���� �ִ� ������ Attribute type�� ���ο� attribute value ����
    �ִ´�.  Attribute_Set() �Լ��� ���������� "..."�� �������� ������ ASN
    type�� ���� �����͵��� ���� �� �ִ�.  �ݵ�� ���� ������ �Ķ���Ϳ�
    NULL�� �־� �Է��� ������ ǥ���ؾ� �Ѵ�.

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
    @brief SeqOfAttribute�� �������� value�� ���� �ϳ��� Attribute�� �߰��Ѵ�.
    @param atts [out] ������ �߰��ϰ��� �ϴ� SeqOfAttribute type.
    @param oid [in]  �� attribute value ���� Object Identifier.

    �Լ� ���ο��� Attribute_Set�� ������ ����� �����Ͽ� 
    Attribute�� �ϳ� �����Ͽ� �̸� SeqOfAttribute�� �߰��Ѵ�.
    �߰��ϴ� Attribute type�� parameter oid�� �߰��ȴ�.
    parameter oid ���� "..."�� �������� ������ ASN type�� ���� �����͵���
    ���� �� �ִ�.  �ݵ�� ���� ������ �Ķ���Ϳ��� NULL�� �־� �Է��� ������
    ǥ���ؾ� �Ѵ�.

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
    @brief Name type�� �ʿ��� ������ set�Ѵ�. 
    @param name [out] ������ ������ Name type.
    @param fmt  [in]  ��� ������ �������� ���� format.
 
    Name type�� �ʿ��� ������ �����Ѵ�. printf ���� �Ϲ����� C �Լ�ó��
    format�� �����Ͽ� ���� ������ � ������ �����Ѵ�.
    �Ϲ����� format�� ������ ���� �����̴�.

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

    �ѱ��� �Է��� ���� �տ� "u"�� "b"�� �ٿ��� �� ���ڿ��� UTF8�̳�
    BMP ���·� �����ϵ��� �ؾ��Ѵ�.
  
    ���� Set�� �ƴ϶� Add�� �� ��쿡�� format ���� �տ� '+' Ȥ�� '<'
    �� �ٿ��� ����Ѵٴ�.

    @code
    "+C,CN"  "<CN"
    @endcode

    ���� ������ �� �̻��� �� ���� �̵��� '+'�� ���´�.

    @code
    "C,O,OU,OU,CN+E"
    @endcode

    �����δ� �̷� ������ ����� �� �ִ�.

    @code
    Name_Set(name, "C,uO,uOU,bCN", "KR", "��Ÿ��ť��Ƽ �ý���",
             "��ȣ �����", "�׶� �׻��");
    @endcode
*/

LIBSPEC_CKM
ERT Name_Set(Name *name, const char *fmt, ...);


/** @ingroup X509
    @brief Name type�� ����ִ� ����� �� �� �׸��� ���ڿ��� ���Ѵ�. 
    @param output  [out] ��� ���ڿ��� ����� ����
    @param max_len [in]  output buffer�� �ִ� ����.
    @param oid     [in]  ���� �׸��� oid 
    @param height  [in]  ���Ϸ��� �׸��� ���� ��ġ. ������ ������ C,O,OU,CN
                         ���̴�.
    @param width   [in]  CN�� Email�� ���� ���� ���̿� ���� �׸��� ���� ��,
                         �� �� ���Ϸ��� �׸��� index.
    @return ���� �׸��� � ������ ���ڿ��� �����Ǿ������� ǥ���ϴ� tag ��ȣ.
            0 �̸� �ƹ��͵� ������ ���ߴٴ� ���̴�.
    @retval TAG_UTF8STRING ���ϵ� ���ڿ��� UTF8 ���ڿ�
    @retval TAG_BMPSTRING ���ϵ� ���ڿ��� BMP ���ڿ�
    @retval TAG_PRINTABLE ���ϵ� ���ڿ��� �Ϲ����� printable ���ڿ�
 
    Name type�� ����� �׸���� ���ϴ� ���� �����Ͽ� ���� ��밡����
    �׸��� ���ڿ��� ���ϴ� �Լ��̴ٴ�.

    Name type��
    directory�� ���� �״�� �Ǿ� �����Ƿ� C�� ���� ���� �׸���� CN��
    ���� ���� �׸��� ������� ����Ǿ� �ִ�.  �� ������ �� �Լ�������
    parameter height�� ǥ���Ѵ�. CN�� Email ���� �׸���
    �� ������ ���Ƽ� ���� height�� �����µ� �̶� �� ���� ������
    parameter width�� �Ѵ�. �� width�� height�� �ϳ��� ������Ű�鼭 

    ���� ���� �ڵ�� Name_Sprint()�� ���� �ڵ��̴�. �� ������ ������
    Name_Get() �Լ��� ��� ����ؾ� �ϴ����� ���� ���� �����̴�.

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
    @brief �ΰ��� Name type�� ���Ѵ�.
    @param name1 [in] ���Ϸ��� Name type 1.
    @param name2 [in] ���Ϸ��� Name type 2.
    @return ���� ���� ���� SUCCESS, �ٸ��� FAIL.

    �ΰ��� Name type�� ���� ��, �� ���� ������ ��ġ�ϴ��� ���Ѵ�.
*/
LIBSPEC_CKM
int Name_Compare(Name *name1, Name *name2);


/** @ingroup X509
    @brief Name type�� ��� ������ ���ڿ��� ���.
    @param content [out] ��µ� ���ڿ�
    @param max_len [in]  content buffer�� �ִ� ����
    @param name    [in]  ������ ����� Name type.

    @sa Name_SprintLine
*/
LIBSPEC_CKM
int Name_Sprint(char *content, int max_len, Name *name);

/** @ingroup X509
    @brief Name type�� ��� ������ ���ڿ��� ���.
    @param content [out] ��µ� ���ڿ�
    @param max_len [in]  content buffer�� �ִ� ����
    @param name    [in]  ������ ����� Name type.

    Name type�� �� �ٷ� ','�� �����ڷ� �Ͽ� ����Ѵ�.
    ���� �ý��� ���忡 ����� �� �ֵ��� '/' ���ڴ� '%2F'��
    '%'�� '%%'�� ��ȯ�Ͽ� �ٷ��.

    @sa Name_Sprint
    @return
      - ���� �� : ��µ� ���ڿ��� ����
      - ���� �� : FAIL(-1)
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
    @brief GeneralName type�� ��� ������ ���ڿ��� ���.
    @param content     [out] ��µ� ���ڿ�
    @param content_max [in]  content buffer�� �ִ� ����
    @param gn          [in]  ������ ����� GeneralName type.
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
    @brief GeneralName type�� �ʿ��� ������ �����Ѵ�.
    @param target [out] ������ ������ GneneralName type.
    @param choice [int] ������ �̾��� ������ � Ÿ�������� ǥ��

    Choice ������ �̷���� GeneralName type�� ������ �����Ѵ�.
    �Ķ������ choice�� ���� �Ķ���ͷ� � Ÿ���� ���� �Ǵ�����
    ǥ���Ѵ�.

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
    @brief GeneralNames type�� �� GeneralName Ÿ���� �߰�
    @param target [out] GeneralNames type.
    @param name   [in]  �߰��� GeneralName type.

    GeneralName type�� GeneralNames type�� �� ����� �߰��Ѵ�.
    �߰��� GeneralName type�� GeneralNames type�� ����� �Ǳ� ������
    ���� ASN_Del()�� �Ͽ��� �ʿ䰡 ����.
*/
LIBSPEC_CKM
int GenNames_AddGenName(GeneralNames *target, GeneralName *name);

/** @ingroup X509
    @brief GeneralNames type�� �� Name Ÿ���� �߰�
    @param target [out] GeneralNames type.
    @param name   [in]  �߰��� Name type.

    ���� ���� ���̴� Name type�� GeneralNames type�� �� �����
    �߰��Ѵ�.
    �߰��� Name type�� GeneralNames type�� ����� �Ǳ� ������
    ���� ASN_Del()�� �Ͽ��� �ʿ䰡 ����.

    @sa GenNames_AddGenName
*/
LIBSPEC_CKM
int GenNames_AddByName(GeneralNames *target, Name *name);



/** @ingroup X509
    @brief GeneralNames type�� ��� ������ ���ڿ��� ���.
    @param content     [out] ��µ� ���ڿ�
    @param content_max [in]  content buffer�� �ִ� ����
    @param gns         [in]  ������ ����� GeneralNames type.
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

    Extension(Ext)Ÿ�Կ� ���� ��Ʈ�� ����� ���ؼ� ���� ������ ��.
    ����Ű �������� �Ӽ� �������� ��� ��� �����ϴ�.
 */
typedef struct _ExtPrintCtx {
  char name[128];
  int  critical;
  char value[2048];
} ExtPrintCtx;


/** @ingroup X509
    @brief Extension type�� ������ �����Ѵ�.
    @param ext      [out]  Extension type
    @param oid      [in]  ���� ������ ������ OID
    @param critical [in]  ���� ������ ������ critical ����.  1 �Ǵ� 0 �̴�.
    @param in       [in]  Extension type�� ������ �� ASN type

    Extension type�� ������ �����Ѵ�.  OID�� critical ����, DER ���ڵ��Ǿ�
    �� ASN type�� �Է����� ���´�.

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
    @brief Extension type�� ������ �д´�.
    @param oid      [out] Extension ������ OID
    @param critical [out] Extension ������ critical ����.  1 �Ǵ� 0 �̴�.
    @param ext      [in]  Extension type
    @return DER ���ڵ��Ǿ� �ִ� Extension�� �����̴�. ASN type���� �ٲٱ�
           ���ؼ��� DER ���ڵ��� �ؾ��Ѵ�.

    Extension type�� ������ ���Ѵ�.  OID�� critical ����, DER ���ڵ���
    ASN type�� ����̴�.  ���ϵ� ASNBuf�� ������
    DER ���ڵ��� ���� ���ϴ� ASN type���� ��ȯ�Ͽ��� �Ѵ�.

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
    @brief Extension type�� DER ���ڵ��� ������ �о� �̸� ���ڵ��Ͽ� �����Ѵ�.
    @param critical [out] Extension ������ critical ����.  1 �Ǵ� 0 �̴�.
    @param ext      [in]  Extension type
    @param type     [in]  DER ���ڵ��Ǿ� �ִ� Extension ������ ���� type
    @return Extension�� ������ DER ���ڵ��Ǿ� �Ϲ����� ASN type���� ���ϵȴ�.

    
    Extension type�� ������ ���ϴ� Extension_Get() �Լ��� �������̴�.
    critical ���ο� �Բ� DER ���ڵ��� ASN type�� ������� ���´�.
    Extension_Get()���� �޸� �Ű� ASNBuf type�� �ʿ���� ���ٸ� ���ڵ� ������
    ����.

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

    Extensions(Exts)Ÿ�Կ� ���� ��Ʈ�� ����� ���ؼ� ���� ������ ��.
    ����Ű �������� �Ӽ� �������� ��� ��� �����ϴ�.
 */
typedef struct _ExtsPrintCtx {
  int          size;
  ExtPrintCtx *exts;
} ExtsPrintCtx;

/** @ingroup X509
    @function Extensions_AddP(exts, ext)
    @brief Extensions type�� �� ����� Extension type�� �߰��Ѵ�.
    @param exts [out] Extensions type
    @param ext  [in]  Extension type
    
    Extensions type�� �� ����� Extension type�� �߰��Ѵ�.
    �߰��� Extension type�� ���ؼ��� ������ ASN_Del �۾��� ����
    �ʿ䰡 ����.

    @sa Extensions_Add
*/
#define Extensions_AddP(exts, ext) ASNSeqOf_AddP(ASN_SEQOF(exts), ASN(ext))

/** @ingroup X509
    @brief Extensions type�� �� ����� ���Ӱ� �����Ͽ� �߰��Ѵ�.
    @param exts     [out] Extensions type
    @param oid      [in] ���Ӱ� ������� Extension type�� OID
    @param critical [in] ���Ӱ� �������  Extension type�� critical ����
    @param in       [in] ���Ӱ� ������� Extension type�� ASN type

    Extensions type�� �� ����� ���ο� Extension type�� �߰��Ѵ�.
    Extesions_AddP()�� �޸� Extension type�� �̸� ���� �߰��ϴ�
    ���� �ƴ϶�, �Լ� ���ο��� �ű� Extension type�� ���� ������
    �̰��� �߰��Ѵ�.

    @sa Extensions_AddP
*/
LIBSPEC_CKM
int Extensions_Add(Extensions *exts, Oid *oid, int critical, ASN *in);

LIBSPEC_CKM
int Extensions_AddByNid(Extensions *exts, Nid nid, int critical, ASN *in);

/** @ingroup X509
    @brief ������ OID�� ���� Extensions type�� �� ����� ���Ѵ�.
    @param exts [in] Extensions type
    @param oid  [in] ���ϰ��� �ϴ� OID

    ������ OID�� ���� Extensions type�� �� ����� ���Ѵ�.
    ������ Extension type�� �����ʹ� Extention type ������ �� �����
    �������� �����̹Ƿ� ����� ASN_Del()�� �������� �ȵȴ�.

    @sa Extensions_GetPByOid
*/
LIBSPEC_CKM
Extension* Extensions_GetPByOid(Extensions *exts, Oid *oid);

/** @ingroup X509
    @brief ������ NID�� ���� Extensions type�� �� ����� ���Ѵ�.
    @param exts [in] Extensions type
    @param nid  [in] ���ϰ��� �ϴ� NID

    ������ NID�� ���� Extensions type�� �� ����� ���Ѵ�.
    ������ Extension type�� �����ʹ� Extention type ������ �� �����
    �������� �����̹Ƿ� ����� ASN_Del()�� �������� �ȵȴ�.

    @sa Extensions_GetPByNid
*/
LIBSPEC_CKM
Extension* Extensions_GetPByNid(Extensions *exts, Nid nid);

/** @ingroup X509
    @brief ������ OID�� ���� Extensions type�� �� ����� �����Ѵ�.
    @param exts [in] Extensions type
    @param oid  [in] �����ϰ��� �ϴ� OID

    ������ OID�� ���� Extensions type�� �� ����� �����Ѵ�.
*/
LIBSPEC_CKM
int Extensions_DelByOid(Extensions *exts, Oid *oid);

/** @ingroup X509
    @brief ������ NID�� ���� Extensions type�� �� ����� �����Ѵ�.
    @param exts [in] Extensions type
    @param oid  [in] �����ϰ��� �ϴ� NID

    ������ NID�� ���� Extensions type�� �� ����� �����Ѵ�.
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
    @brief ������ NID�� ���� Extensions type�� �� extension ����� ���ϰ�
           ���� ������ ���ڵ��Ͽ� ���� �ʿ��� type�� ���Ѵ�..
    @param critical [out] ���� Extension type�� critical ����
    @param exts     [in]  Extensions type
    @param type     [in]  DER ���ڵ��Ǿ� �ִ� Extension ������ ���� type
    @param nid      [in]  ���ϰ��� �ϴ� NID

    Extensions type�� ����� �� ������ NID�� ���� extension�� ã�� ��,
    ���� ������ ���ڵ��Ͽ� ���� ������ ���Ѵ�.

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
    @brief CertificateSerialNumber�� ������ �־��� ������ ���� �����Ѵ�.
    @param sn [out] ������ �Ϸù�ȣ�� ����� ������
    @param issuer  [in]  �߱��� DN
    @param subject [in]  �ǹ߱��� DN
    @return ���������� �����Ǹ� SUCCESS�� ���ϵǰ�, �׷��� ������ FAIL

    �߱����� DN�� �ǹ߱����� DN�� �Է����� �޾� ���̰�, ���������� �߱� �ð��� 
    ���� �� ������ ������ �������� 128bit ������ ������
    serial number�� �����Ѵ�.  milli-second ������ �ð��� ����ϹǷ�
    ���� millisecond�� ���� �߱��� DN, ����� DN�� ���� ��������
    �߱����� �ʴ���, ������ serial number�� ������ ���ɼ��� ���� ����.

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
    @brief CertificateSerialNumber_Gen�� ����
    @param sn [out] ������ �Ϸù�ȣ�� ����� ������
    @param issuer  [in]  �߱��� ������ ��� �ִ� ASN Ÿ��
    @param subject [in]  �ǹ߱��� ������ ��� �ִ� ASN Ÿ�� 
    @return ���������� �����Ǹ� SUCCESS�� ���ϵǰ�, �׷��� ������ FAIL

    �߱��ڿ� �ǹ߱����� ������ ���Ե� �ΰ��� �Է� issuer�� subject�� �Բ�
    �߱� �ð��� ������ �������� 128bit ������ ������
    serial number�� �����Ѵ�. ���� ������ CertificateSerialNumber_Gen��
    ���������� TimeInfoForSerialNumber2�� DER ���� �Է����� ����ϴ� ����
    �ٸ���.
    TimeInfoForSerialNumber2�� issuerInfo�� subjectInfo�� �����Ϳ��� 
    �Է� �Ķ���� issuer�� subject�� DER ���ڵ� ���� ���� ����.

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

