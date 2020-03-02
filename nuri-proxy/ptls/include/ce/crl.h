#ifndef _CRL_H_
#define _CRL_H_

#include "ckm_pkcrypt.h"
#include "me.h"
#include "x509pkc.h"

/** @defgroup CRL CRL handling
 * @ingroup CKM
    @brief CRL�� �ٷ�� APIs
    
    CRL�� ���� �� ��������ϰ� �־��� �������� CRL ��
    ���ԵǾ� �ִ����� ���θ� Ȯ���ϴ� ���� CRL�� ������ ���ø����̼���
    �ؾ߸� �ϴ� ���� �۾��� �ϴ� ���.
*/

#ifdef __cplusplus
extern "C" {
#endif

enum _ER_CRL {
  ER_CRL_PUBKEYALG_MISMATCH = ER_CRL,
  ER_CRL_ISSUER_MISMATCH
};

enum _RET_CRL {
  RET_CRL_CERT_REVOCATED = RET_CRL,
  RET_CRL_CERT_NOT_REVOCATED,
  RET_CRL_CERT_NOT_REVOCATED_AT_TIME
};

/*****************************************************************************
 *  TBSCertList manipulating functions
 */

/** @ingroup CRL
    @brief TBSCertList�� �����Ѵ�.
    @param tbsCertList         [out]
    @param issuer              [in]
    @param thisUpdate          [in]
    @param nextUpdate          [in]
    @param revokedCertificates [in]
    @param extensions          [in]
    */
LIBSPEC_CKM
ERT TBSCertList_Set(TBSCertList         *tbsCertList, 
                    Name                *issuer,
                    struct tm           *thisUpdate,
                    struct tm           *nextUpdate,
                    RevokedCertificates *revokedCertificates,
                    Extensions          *extensions);

/** @ingroup CRL
    @brief TBSCertList�� RevokedCertificate �� �ϳ� �߰��Ѵ�.
    @param tbsCertList [out] RevokedCertificate�� �߰��� TBSCertList�� ������
    @param revCert     [in]  TBSCertList�� �߰��� RevokedCertificate�� ������

    TBSCertList�� �ű� RevokedCertificate�� �߰��Ѵ�.
*/
LIBSPEC_CKM
ERT TBSCertList_AddRevocatedCert(TBSCertList        *tbsCertList,
                                 RevokedCertificate *revCert);

/** @ingroup CRL
    @brief TBSCertList���� RevokedCertificate�� �ϳ� �����Ѵ�.
    @param tbsCertList [out] TBSCertList�� ������
    @param revCertNum  [in]  ������ RevokedCertificate �� ������ �Ϸù�ȣ

    TBSCertList���� ������ �Ϸù�ȣ�� ���� RevokedCertificate �ϳ��� �����Ѵ�.
*/
LIBSPEC_CKM
ERT TBSCertList_DelRevocatedCert(TBSCertList             *tbsCertList,
                                 CertificateSerialNumber *revCertNum);

/** @ingroup CRL
    @brief �־��� ������ �Ϸù�ȣ�� TBSCertList�� ����ִ����� ���θ� �˻��Ѵ�.
    @param tbsCertList  [in] TBSCertList�� ������
    @param serialNumber [in] TBSCertList�� ���Կ��θ� Ȯ���� �������� �Ϸù�ȣ
    @retval RET_CRL_CERT_REVOCATED ������ �Ϸù�ȣ�� TBSCertList�� ����
    @retval RET_CRL_CERT_NOT_REVOCATED ������ �Ϸù�ȣ�� TBSCertList�� ������

    �־��� �������� �Ϸù�ȣ�� TBSCertList���� ���� ���θ� �˻��Ѵ�.
*/
LIBSPEC_CKM
ERT TBSCertList_CheckRevocated(TBSCertList             *tbsCertList,
                               CertificateSerialNumber *serialNumber);

/** @ingroup CRL
    @brief �־��� ������ �Ϸù�ȣ�� TBSCertList�� ����ִ����� ���θ� �˻��Ѵ�.
    @param tbsCertList  [in] TBSCertList�� ������
    @param serialNumber [in] TBSCertList�� ���Կ��θ� Ȯ���� �������� �Ϸù�ȣ
    @param checkTime    [in] ���� ���θ� üũ�ϰ��� �ϴ� �ð�
    @retval RET_CRL_CERT_REVOCATED ������ �Ϸù�ȣ�� TBSCertList�� ����
    @retval RET_CRL_CERT_NOT_REVOCATED ������ �Ϸù�ȣ�� TBSCertList�� ������
    @retval RET_CRL_CERT_NOT_REVOCATED_AT_TIME ������ �Ϸù�ȣ��
            TBSCertList�� ���ԵǾ� ������, ���� �ð��� checkTime ������

    �־��� �������� �Ϸù�ȣ�� TBSCertList���� ���� ���θ� �˻��Ѵ�.
*/
LIBSPEC_CKM
ERT TBSCertList_CheckRevocatedAtTime(TBSCertList             *tbsCertList,
                                     CertificateSerialNumber *serialNumber,
                                     struct tm               *checkTime);

/** @ingroup CRL
    @brief �־��� �������� TBSCertList�� ����ִ����� ���θ� �˻��Ѵ�.
    @param tbsCertList  [in] TBSCertList�� ������
    @param cert         [in] Certificate�� ������
    @retval RET_CRL_CERT_REVOCATED �������� TBSCertList�� ����
    @retval RET_CRL_CERT_NOT_REVOCATED �������� TBSCertList�� ������

    �־��� �������� �Ϸù�ȣ�� TBSCertList���� ���� ���θ� �˻��Ѵ�.
*/
LIBSPEC_CKM
ERT TBSCertList_CheckRevocatedCert(TBSCertList *tbsCertList,
                                   Certificate *cert);

/** @ingroup CRL
    @brief �־��� �������� TBSCertList�� ����ִ����� ���θ� �˻��Ѵ�.
    @param tbsCertList  [in] TBSCertList�� ������
    @param cert         [in] Certificate�� ������
    @param checkTime    [in] ���� ���θ� üũ�ϰ��� �ϴ� �ð�
    @retval RET_CRL_CERT_REVOCATED �������� TBSCertList�� ����
    @retval RET_CRL_CERT_NOT_REVOCATED �������� TBSCertList�� ������
    @retval RET_CRL_CERT_NOT_REVOCATED_AT_TIME �������� TBSCertList��
            ���ԵǾ� ������, ���� �ð��� checkTime ������

    �־��� �������� �Ϸù�ȣ�� TBSCertList���� ���� ���θ� �˻��Ѵ�.
*/
LIBSPEC_CKM
ERT TBSCertList_CheckRevocatedCertAtTime(TBSCertList *tbsCertList,
                                         Certificate *cert,
                                         struct tm   *checkTime);

/** @ingroup CRL
    @brief �־��� ������ �Ϸ� ��ȣ�� �´� TBSCertList ���� RevokedCertificate��
           ã�´�.
    @param tbsCertList  [in] TBSCertList�� ������
    @param serial       [in] ������ �Ϸù�ȣ�� ������
    @return ã�� ��� ���� pointer ��. ���� ��� NULL 

    �־��� �������� �����ϴ� TBSCertList���� RevokedCertificate�� ã�´�.
    ������ ���� pointer ����, ������ NULL�� �����Ѵ�. return�� 
    RevokedCertificate�� ���� alloc�� ���̹Ƿ� �ݵ�� ASN_Del()�� �����־��
    �� �Ѵ�.
*/
LIBSPEC_CKM
RevokedCertificate* TBSCertList_GetRevokedCert(
                                TBSCertList             *tbsCertList,
                                CertificateSerialNumber *serialNumber);

/** @ingroup CRL
    @brief TBSCertList ���� RevokedCertificate�� ���ʴ�� ���� �´�.
    @param revCert      [out] ���� �� ���� RevokedCertificate�� ������
    @param tbsCertList  [in] TBSCertList�� ������
    @param handle       [in] ���� RevokedCertificate�� ã�� ���� �ڵ� ��.
                             NULL�̸� ���� ó�� ���� ã�´�.
    @return ã�� ��� ���� �˻��� �� �� �ִ� �ڵ� ��. �� �̻� ���� ��� NULL 

    TBSCertList���� RevokedCertificate���� ���ʴ�� ���� �´�.
    handel �Ķ���͸� NULL�� �ָ� ���� ó�� RevokedCertificate�� ã��,
    ���� �˻��� ���� handle ���� �����Ѵ�. �� ���ϵ� handle ����
    �Է����� �ٽ� ȣ���ϸ� �� ���� RevokedCertificate�� ã�´�.
    �� �̻� ������ �� RevokedCertificate�� ������ NULL�� �����Ѵ�.

*/
LIBSPEC_CKM
void* TBSCertList_GetRevokedCertNext(RevokedCertificate **revCert,
                                     TBSCertList         *tbsCertList,
                                     void                *handle);


/*****************************************************************************
 * CRL manipulating functions
 */

/** @ingroup CRL
    @brief CRL�� �־��� TBSCertList�� �Է��Ѵ�.
    @param crl         [in] CRL�� ������
    @param tbsCertList  [in] TBSCertList�� ������
    @return ������ ��� SUCCESS

    CRL�� �־��� TBSCertList�� �Է��Ѵ�. �̶� �Էµ� TBSCertList��
    CRL�� �Ϻη� ������ �ǹǷ� �� �Լ� ȣ�� �Ŀ� ASN_Del()�� �ؼ���
    �ȵȴ�.
*/
LIBSPEC_CKM
ERT CRL_SetTBSCertListP(CRL *crl, TBSCertList *tbsCertList);


LIBSPEC_CKM
ERT CRL_GetSignatureValuePK(PKCryptSig *sigVal, CRL *crl);

LIBSPEC_CKM
ASNBuf* CRL_GetSignatureValue(CRL *crl);

#define CRL_GetSignatureAlgNid(a) ((a)->signatureAlgorithm->algorithm->nid)


/** @ingroup CRL
    @brief �־��� CRL�� ���ڼ����� ���Ѵ�.
    @param crl [in/out]����� CRL
    @param tbsCertList  [in] TBSCertList�� ������. NULL�� �� �� �ִ�.
    @param issuerKey [in] ������ CA�� �����Ű
    @param priInfo ������ CA �����Ű ���� ����

    �־��� CRL�� CA�� ���� ������ ���Ѵ�.
*/
LIBSPEC_CKM
ERT CRL_GenPK(CRL           *crl, 
              TBSCertList   *tbsCRL,
              PKCryptPriKey *issuerKey,
              PKCryptParam  *systemParam,
              AlgDesc        hashAlgorithm,
              const void    *kcdsaPub);

/** @ingroup CRL
    @brief �־��� CRL�� ���ڼ����� ���Ѵ�.
    @param crl [in/out]����� CRL
    @param tbsCertList  [in] TBSCertList�� ������. NULL�� �� �� �ִ�.
    @param issuerCert [in] ������ CA�� ������
    @param priInfo ������ CA �����Ű ���� ����

    �־��� CRL�� CA�� ���� ������ ���Ѵ�.
*/
LIBSPEC_CKM
ERT CRL_Gen(CRL             *crl, 
            TBSCertList     *tbsCRL,
            PrivateKeyInfo  *issuerPriKeyInfo,
            Parameter       *domainParam,
            AlgDesc          hashAlg,
            Certificate     *issuerCert);


/** @ingroup CRL
    @brief �־��� CRL�� ���ڼ����� �����Ѵ�.
    @param crl ������ ������ CRL
    @param issuerCert CRL�� ������ CA�� ������
    @param param ���� �˰����� KCDSA�� DSA�� ���, �������� parameter��
                 ������� ���� ��, �� parameter�� ���� �ش�.

    �־��� CRL�� ���� ������ �����Ѵ�.  ���� �˰����� KCDSA��
    DSA�ε� ������ ���� Ű �Ķ���Ͱ� ������� �ʴٸ� ���� �Ķ���͸�
    �� �� �ִ�.
*/
LIBSPEC_CKM
ERT CRL_VerifySignPK(CRL                 *crl,
                     const PKCryptPubKey *pubKey,
                     const PKCryptParam  *param,
                     const void          *kcdsaPubInfo);
  
LIBSPEC_CKM
ERT CRL_VerifySign(CRL         *crl, 
                   Certificate *issuerCert,
                   Parameter   *domainParam);


/** @ingroup CRL
    @brief CRL�� ���Ͽ��� �о� �´�.
    @param filePath [in] CRL�� ����� ���� ���
    @ret CRL�� ������, ���н� NULL

    DER ���ڵ��Ǿ� ���Ϸ� ����� CRL�� ���ڵ��Ͽ� �޸𸮷� �о� �´�.
*/
LIBSPEC_CKM                     
CRL* CRL_NewFromFile(const char *filePath);

/** @ingroup CRL
    @brief DER ���ڵ��Ǿ� �޸𸮿� ����� CRL�� �о� �´�.
    @param ptr    [in] DER ���ڵ��� CRL�� �����ϴ� �޸� �ּ�
    @param length [in] DER ���ڵ��� CRL�� �����ϴ� �޸��� ����
    @ret CRL�� ������, ���н� NULL

    DER ���ڵ��Ǿ� �޸𸮿� �����ϴ� CRL�� ���ڵ��Ͽ� �о� �´�.
    ��Ʈ��ũ���� ���� ���ڵ��� CRL�� ���޹޾��� ��, �̸� ���ڵ��ϴµ�
    ����Ѵ�.
*/
LIBSPEC_CKM                     
CRL* CRL_NewFromMem(const void *ptr, int length);

/** @ingroup CRL
    @brief CRL�� DER ���ڵ��Ͽ� ���Ͽ� �����Ѵ�.
    @param crl      [in] CRL�� ������
    @param filePath [in] CRL�� ����� ���� ���

    CRL�� DER ���ڵ��Ͽ� �־��� ��ο� ���� ���·� �����Ѵ�.
*/
LIBSPEC_CKM
ERT CRL_WriteFile(CRL *crl, const char *filePath);

#ifdef __cplusplus
}
#endif

#endif /* _CRL_H_ */
