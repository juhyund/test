#ifndef _ATTCERT_H_
#define _ATTCERT_H_

#include "cert.h"
#include "x509ac.h"

/** @defgroup ATTRIBUTE_CERTIFICATE Attribute Certificate
 * @ingroup CKM
    @brief attribute certificate�� ���õ� Ÿ��, �Լ�

    Sign, Verify �Լ��� ���� �Ǿ� �ְ�,
    Atribute Certificate�� ���� �ֿ� attribute type��� �װ͵���
    �ٷ� �� �ִ� �Լ����� ���ǵǾ� �ִ�. 
*/

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  ER_ATTCERT_ATTRIBUTETYPE_NOT_UNIQUE = ER_ATTCERT,
  ER_ATTCERT_SAME_ATTRIBUTETYPE,
  ER_ATTCERT_NO_ATTRIBUTE
} ATTCERT_ERRORS;

/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef ACContext
    @brief �Ӽ� ���������� ����ϴ� Context Ÿ���� ����

    ACContext�� Ÿ���� OctetString ���� �����Ѵ�. 
    OctetString�� ASN ��⿡ ���ǵǾ� ������,
    octet ������ ���ڿ��� �ǹ��Ѵ�.
    ASN.1 type���� ���ڿ��� �������� ���� ������ ������, ������ ��������
    ������ �ξ� ���� �Ϲ����� OctetString ���� �����Ѵ�.
  */
typedef OctetString  ACContext; 
#define AD_ACContext AD_OctetString

/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef ACRuleIdentifier
    @brief  ACRule�� �����ϴ� Identifier Ÿ���� ����

    ACRuleIdentifier�� Ÿ���� OctetString���� ���ǵǾ� �ִ�.
    OctetString�� ���ؼ��� ACContext�� �����ϱ� �ٶ���.
  */
typedef OctetString ACRuleIdentifier;
#define AD_ACRuleIdentifier AD_OctetString
  
/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef ACRule
    @brief �Ӽ� ���������� ����ϴ� ���� ���� ���� ACRule Ÿ�� ����

    ACRule�� ����ڰ� �̿��ϰ��� �ϴ� ���񽺿� ���� Access Control�� 
    �����̴�.
  */
typedef struct _ACRule {
  ASNSeqClass       klass;
  ACRuleIdentifier *ruleId;
  ACContext        *ruleCtx;
} ACRule;

LIBSPEC_CKM
extern ASNDescriptor AD_ACRule;

typedef struct {
  ASNSeqOfClass   klass;
  int             size;
  ACRule        **member;
} ACRules;

LIBSPEC_CKM
extern ASNDescriptor AD_ACRules;

LIBSPEC_CKM
ERT ACRules_Add(ACRules *rules, void *id, int idLen, void *ctx, int ctxLen);


/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef ServiceIdentifier
    @brief  Service�� �����ϴ� Identifier Ÿ���� ����

    ServiceIdentifier�� Ÿ���� OctetString���� ���ǵǾ� �ִ�.
    OctetString�� ���ؼ��� AAIdentifier�� �����ϱ� �ٶ���.
  */
typedef OctetString ServiceIdentifier;
#define AD_ServiceIdentifier AD_OctetString


/** @ingroup ATTRIBUTE_CERTIFICATE
    @typedef Permission
    @brief   ���񽺿� ���� ��� ���� ���� Permission ���� 
  */
typedef struct _Permission {
  ASNSeqClass        klass;
  ServiceIdentifier *serviceId;
  ACContext         *serviceCtx;
  ACRules           *rules;
} Permission;

LIBSPEC_CKM
extern ASNDescriptor AD_Permission;

typedef struct {
  ASNSeqOfClass   klass;
  int             size;
  Permission    **member;
} SeqOfPermission;

LIBSPEC_CKM
extern ASNDescriptor AD_SeqOfPermission;

typedef struct {
  ASNSeqClass      klass;
  GeneralNames    *policyAuthority;  /* [0] OPTIONAL */
  SeqOfPermission *permissions;  
} Permissions;

LIBSPEC_CKM
extern ASNDescriptor AD_Permissions;

LIBSPEC_CKM
ERT Permissions_Add(Permissions *permissions, 
                    void *id, int idLen, void *ctx, int ctxLen,
                    ACRules *rules);

/*****************************************************************************
 * ATTCERT Setting
 */

LIBSPEC_CKM
ERT Holder_SetByName(Holder *holder, Name *name);

LIBSPEC_CKM
ERT Holder_SetByCertificate(Holder *holder, Certificate *cert);

/*
   RFC3281

   The roleName field MUST be present, and roleName MUST use the
   uniformResourceIdentifier CHOICE of the GeneralName.
*/
LIBSPEC_CKM
ERT Holder_SetByRoleName(Holder *holder, const char *roleName);

/*
   ACs conforming to RFC3281 MUST use the v2Form choice, which MUST
   contain one and only one GeneralName in the issuerName, which MUST
   contain a non-empty distinguished name in the directoryName field.
   This means that all AC issuers MUST have non-empty distinguished
   names.  ACs conforming to this profile MUST omit the
   baseCertificateID and objectDigestInfo fields.

   serialNumber�� NULL�� ��� ���������� ����(issuer, subject�� NULL�̸� ����)

   AC issuers MUST force the serialNumber to be a positive integer.
   This removes a potential ambiguity in mapping between a
   string of octets and an integer value.
   AC users MUST be able to handle serialNumber values longer than 4 octets.  
   Conformant ACs MUST NOT contain serialNumber values longer than 20 octets.

   An AC MUST contain at least one attribute.  That is, the SEQUENCE OF
   Attributes MUST NOT be of zero length.
   ����, attributes�� NULL�̸� �Լ� ���ο��� zero length�� SEQUENCE OF
   Attributes�� attCertInfo�� ����������, 
   �� ���¿��� AC�� ����(ATTCERT_Gen �Լ�)�ϸ� ���� �߻�.
   attributes �ȿ��� ��� �ϳ��� attribute�� ��� �־�� �ϹǷ�,
   �׷��� ��쿡�� AttributeCertificateInfo_AddAttribute�� �̿��Ͽ�
   Attribute �߰��� �Ŀ� AC �����ؾ� �Ѵ�.

   IssuerUniqueIdentifier MUST NOT be used unless it is also used in the AC issuer's
   PKC, in which case it MUST be used.
   Issuer Unique Identifier�� ������� ����.

   An AC that has no extensions conforms to RFC3281.
   Extensions�� ������� ���� ��� NULL �Է�
*/
LIBSPEC_CKM
ERT AttributeCertificateInfo_Set(AttributeCertificateInfo *attCertInfo,
                                 Holder *holder,
                                 Name   *issuer,
                                 CertificateSerialNumber *serialNumber,
                                 struct tm               *notBefore,
                                 struct tm               *notAfter,
                                 SeqOfAttribute          *attributes,
                                 Extensions              *extensions);

/*
   For a given AC, each
   AttributeType OBJECT IDENTIFIER in the sequence MUST be unique.  That
   is, only one instance of each attribute can occur in a single AC, but
   each instance can be multi-valued.

   AttributeCertificateInfo�� attributes�� att�� �߰��ϴ� �Լ��̴�.
   ������ type�� ���� attribute�� �����ؼ��� �ȵǴ� ��Ģ�� �µ���
   attCertInfo�� �� ���ǿ� ���� �ʴ� ��� ER_ATTCERT_ATTRIBUTETYPE_NOT_UNIQUE��
   �����Ѵ�.

   att�� type�� �̹� attCertInfo�� attributes�� �����ϴ� ��� 
   mode�� ���� ���� ������ ���� ó���Ѵ�.

   mode = "r" : �ش� type�� ����ִ� attribute�� vales�� replace�Ѵ�.
                SeqOf�� �ڿ� �߰��Ǵ� ���� �ƴ϶�, �̹� �����ϴ� 
                attribute�� ��ġ�� ���� ������
                ������ attribute values�� �����ϰ��� �ϴ� ��쿡�� ����� ��
                �ִ�.
   mode = "a" : �ش� type�� ����ִ� attribute�� vales�� att�� values�� �߰��Ѵ�.
   mode = �׿�(NULL����) : ER_ATTCERT_SAME_ATTRIBUTETYPE�� ����.
*/
LIBSPEC_CKM
ERT AttributeCertificateInfo_AddAttribute(AttributeCertificateInfo *attCertInfo,
                                          Attribute                *att,
                                          const char               *mode);


/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   �Ӽ� �������� �߱��ڰ� �����Ű�� ����
   @param attCert [out] �Ӽ� ������
   @param attCertInfo [in] ����� �Ӽ� ������ ����
   @param issuerCert [in] ������ �߱����� ������
   @param priInfo [in] ������ �߱����� PrivateSignInfo
   @sa ATTCERT_Verify, PrivateKeyInfo_MakePrivateSignInfo

   �Ӽ� �������� �߱��ڰ� �Ӽ� �������� �����Ѵ�.
*/
LIBSPEC_CKM
ERT ATTCERT_Gen(AttributeCertificate     *attCert,
                AttributeCertificateInfo *attCertInfo,
                PrivateKeyInfo           *issuerPriKeyInfo,
                Parameter                *domainParam,
                AlgDesc                   hashAlg,
                Certificate              *issuerCert);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   �Ӽ� �������� ���� ������ �����Ѵ�.
   @param attCert    [in] �Ӽ� ������ �Է�
   @param issuerCert [in] �߱����� ������
   @param param      [in] DSA�� KCDSA�� ����� ���, �� �˰�����  parameter
   @return ���� ���� �ÿ��� SUCCESS, ���� �ÿ��� FAIL
   @sa ATTCERT_Gen

   �Ӽ� �������� ������ �ùٸ� ������ �����Ѵ�.
   ������ DSA�� KCDSA�� ����ϰ� �߱����� ������ SubjectPublicKeyInfo ������
   �̵� �˰����� �Ķ���Ͱ� ���ԵǾ� ���� ���� ���, �̸� �Է����� �� ��
   �ִ�.  �׷��� ���� ��쿡�� ����° �Է� param�� NULL�� �ָ� �ȴ�.
*/
LIBSPEC_CKM
ERT ATTCERT_VerifySign( AttributeCertificate *attCert,
                        Certificate          *issuerCert,
                        Parameter            *domainParam);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   �Ӽ� �������� ��ȿ�Ⱓ�� �ǹٸ��� Ȯ���Ѵ�.
   @param attCert   [in] �Ӽ� ������ �Է�.
   @param now   [in] ��ȿ�Ⱓ�� Ȯ���� ���� �ð�. NULL�̸� �ý��� �ð� ���.
   @sa ATTCERT_GetValidity

   CERT_VerifyTime�� �����ڵ尡 �����ϴ�.
*/
LIBSPEC_CKM
ERT ATTCERT_VerifyTime( AttributeCertificate *attCert,
                        struct tm            *now);



/*****************************************************************************
 * ATTCERT Getting
 */

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   �Ӽ� �������� �߱� ����ڸ� ���Ѵ�
   @param serial       [out] �Ӽ� �������� �Ϸù�ȣ
   @param issuerName   [out] �߱� ������� �������� �߱��� issuer
   @param holderName   [out] �߱� ������� Name
   @param holderSID    [out] �߱� ������� SID, NULL�� �־� ���� ���� ���� �ִ�.
   @param holderSIDLen [in] holderSID ������ ���� �Է�,
   @param attCert      [in] �Ӽ� ������ �Է�
   @sa ATTCERT_Set

   �Ӽ� ���������� �� �Ӽ� �������� �߱� ����ڰ� ���������� ���Ѵ�.
   �Ӽ� �������� �Ϸù�ȣ, �߱� ������� Name, �߱� ������� issuer �����
   ���Ѵ�.
*/
LIBSPEC_CKM
ERT ATTCERT_GetHolder( CertificateSerialNumber *serial,
                       Name                    *issuerName,
                       Name                    *holderName,
                       char                    *holderSID,
                       int                      holderSIDLen,
                       AttributeCertificate    *attCert);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   ebrief   �Ӽ� �������� �߱��ڸ� ���Ѵ�
   @param issuerName [out] �߱����� Name
   @param attCert    [in] �Ӽ� ������ �Է�
   @sa ATTCERT_Set

   �Ӽ� ���������� �� �Ӽ� �������� �߱����� Name�� ���Ѵ�.
*/
LIBSPEC_CKM
ERT ATTCERT_GetIssuer( Name                 *issuerName,
                       AttributeCertificate *attCert);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   �Ӽ� �������� ��ȿ�Ⱓ�� ���Ѵ�
   @param notBefore [out] ��ȿ�Ⱓ ���� �ð�.  gmtime�̴�.
   @param notAfter [out] ��ȿ�Ⱓ �� ����.  gmtime�̴�.
   @param attCert   [in] �Ӽ� ������ �Է�
   @sa ATTCERT_Set, ATTCERT_VerifyValidity, GmtimeToLocaltime

   �Ӽ� ���������� �� �Ӽ� �������� ��ȿ�Ⱓ�� �������� ������������
   ���Ѵ�.  ���� struct tm�� �� �������� GMT �ð��̹Ƿ� ���� �ð��� ���Ϸ���
   �ݵ�� ����� GmtimeToLocaltime()���� �Լ��� ���� ��ȯ�Ͽ��߸� �Ѵ�.

*/
LIBSPEC_CKM
ERT ATTCERT_GetValidity( struct tm            *notBefore,
                         struct tm            *notAfter,
                         AttributeCertificate *attCert);

LIBSPEC_CKM
ASNBuf* ATTCERT_GetSignatureValue(AttributeCertificate *attCert);

/**
   @ingroup ATTRIBUTE_CERTIFICATE
   @brief   �Ӽ� ���������� Oid�� ���� ���ϴ� �Ӽ� type�� ���Ѵ�.
   @param attCert    [in] �Ӽ� ������ �Է�
   @param oid   [in] ���ϰ��� �ϴ� �Ӽ��� Oid
   @param number [in] ���ϰ��� �ϴ� �Ӽ��� index ��ȣ.
   @return  �Ӽ��� DER ���ڵ��� ASNBuf
   @sa ATTCERT_SetAttributes, ATTCERT_AddAttribute

   �Ӽ� ���������� �ʿ�� �ϴ� �Ӽ��� Oid�� ���� ���Ѵ�.  �ϳ��� 
   �Ӽ��� �������� value�� ������ ���� �� �����Ƿ� 
   �Ķ���� number�� ���� ������ �����Ͽ�
   ���� �� �ִ�.  ���ϴ� Oid�� number�� �Ӽ��� ���� ��쿡�� NULL��
   �����Ѵ�.  �Ӽ��� ���ϸ� �̴� DER ���ڵ��� ASNBuf type���� ���ϵȴ�.
   �̴� ASN_New()�� ����Ͽ� ���ϴ� �Ӽ� type���� ��ȯ�Ͽ� ����� �� �ִ�.

   \code
   UserTicket *ut;

   i = 0;
   while((buf = ATTCERT_GetAttributeByOid(attCert, &Oid_UserTicket, i))) {
     if((ut = ASN_New(UserTicket, buf)) == NULL) break; 

     ....

     ASNBuf_Del(buf);
     ASN_Del(ut);
     i++;
   }
   \endcode

   
*/
LIBSPEC_CKM
ASNBuf* ATTCERT_GetAttributeByOid( AttributeCertificate *attCert,
                                   Oid                  *oid,
                                   int                   number);


/*****************************************************************************
 *  Attributes for RAAC and RSAC
 */

typedef enum {
  ATTCERT_TYPE_UNKNOWN = 0,
  ATTCERT_TYPE_RASC,
  ATTCERT_TYPE_RSSC
} ATTCERT_TYPE;
/*
LIBSPEC_CKM
int ATTCERT_GetType();*/

typedef SeqOfAttribute ATTSRoles;
#define AD_ATTSRoles AD_SeqOfAttribute

LIBSPEC_CKM
ERT ATTSRoles_Add(ATTSRoles *atts, const char *roleName);

typedef SeqOfAttribute ATTSRoleSpecs;
#define AD_ATTSRoleSpecs AD_SeqOfAttribute

LIBSPEC_CKM
ERT ATTSRoleSpecs_Add(ATTSRoleSpecs *atts, Permissions *perms);


/*****************************************************************************
 *  ATTCERT PrintCtx
 */

typedef struct {
  char             ruleId[128];
  char             ruleCtx[1024];
} ACRulesPrintCtx;

typedef struct {
  char              serviceId[128];
  char              serviceCtx[1024];
  int               size;
  ACRulesPrintCtx **rules;          /* ACRulesPrintCtx *rules[ruleSize]; */
} PermissionPrintCtx;

typedef struct {
  char                 policyAuthority[256];
  int                  size;
  PermissionPrintCtx **permissions; /* PermissionPrintCtx *permissions[permissionSize] */
} PermissionsPrintCtx;

typedef struct {
  int attCertType;
  
} ATTCERTPrintCtx;

LIBSPEC_CKM
PermissionPrintCtx *PermissionPrintCtx_New(int ruleSize);

LIBSPEC_CKM
void PermissionPrintCtx_Del(PermissionPrintCtx *permission);


LIBSPEC_CKM
PermissionsPrintCtx *PermissionsPrintCtx_New(int permissionSize);

LIBSPEC_CKM
void PermissionsPrintCtx_Del(PermissionsPrintCtx *permissions);


#ifdef __cplusplus
}
#endif
        
#endif /* _ATTCERT_H */

