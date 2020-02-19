#ifndef _CRL_H_
#define _CRL_H_

#include "ckm_pkcrypt.h"
#include "me.h"
#include "x509pkc.h"

/** @defgroup CRL CRL handling
 * @ingroup CKM
    @brief CRL을 다루는 APIs
    
    CRL을 서명 및 서명검증하고 주어진 인증서가 CRL 에
    포함되어 있는지의 여부를 확인하는 등의 CRL을 가지고 어플리케이션이
    해야만 하는 여러 작업을 하는 모듈.
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
    @brief TBSCertList를 설정한다.
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
    @brief TBSCertList에 RevokedCertificate 를 하나 추가한다.
    @param tbsCertList [out] RevokedCertificate을 추가할 TBSCertList의 포인터
    @param revCert     [in]  TBSCertList에 추가할 RevokedCertificate의 포인터

    TBSCertList에 신규 RevokedCertificate를 추가한다.
*/
LIBSPEC_CKM
ERT TBSCertList_AddRevocatedCert(TBSCertList        *tbsCertList,
                                 RevokedCertificate *revCert);

/** @ingroup CRL
    @brief TBSCertList에서 RevokedCertificate를 하나 제거한다.
    @param tbsCertList [out] TBSCertList의 포인터
    @param revCertNum  [in]  제거할 RevokedCertificate 의 인증서 일련번호

    TBSCertList에서 지정된 일련번호를 가진 RevokedCertificate 하나를 제거한다.
*/
LIBSPEC_CKM
ERT TBSCertList_DelRevocatedCert(TBSCertList             *tbsCertList,
                                 CertificateSerialNumber *revCertNum);

/** @ingroup CRL
    @brief 주어진 인증서 일련번호가 TBSCertList에 들어있는지의 여부를 검사한다.
    @param tbsCertList  [in] TBSCertList의 포인터
    @param serialNumber [in] TBSCertList에 포함여부를 확인할 인증서의 일련번호
    @retval RET_CRL_CERT_REVOCATED 인증서 일련번호가 TBSCertList에 포함
    @retval RET_CRL_CERT_NOT_REVOCATED 인증서 일련번호가 TBSCertList에 미포함

    주어진 인증서의 일련번호가 TBSCertList내에 포함 여부를 검사한다.
*/
LIBSPEC_CKM
ERT TBSCertList_CheckRevocated(TBSCertList             *tbsCertList,
                               CertificateSerialNumber *serialNumber);

/** @ingroup CRL
    @brief 주어진 인증서 일련번호가 TBSCertList에 들어있는지의 여부를 검사한다.
    @param tbsCertList  [in] TBSCertList의 포인터
    @param serialNumber [in] TBSCertList에 포함여부를 확인할 인증서의 일련번호
    @param checkTime    [in] 폐지 여부를 체크하고자 하는 시각
    @retval RET_CRL_CERT_REVOCATED 인증서 일련번호가 TBSCertList에 포함
    @retval RET_CRL_CERT_NOT_REVOCATED 인증서 일련번호가 TBSCertList에 미포함
    @retval RET_CRL_CERT_NOT_REVOCATED_AT_TIME 인증서 일련번호가
            TBSCertList에 포함되어 있으나, 폐지 시각은 checkTime 이후임

    주어진 인증서의 일련번호가 TBSCertList내에 포함 여부를 검사한다.
*/
LIBSPEC_CKM
ERT TBSCertList_CheckRevocatedAtTime(TBSCertList             *tbsCertList,
                                     CertificateSerialNumber *serialNumber,
                                     struct tm               *checkTime);

/** @ingroup CRL
    @brief 주어진 인증서가 TBSCertList에 들어있는지의 여부를 검사한다.
    @param tbsCertList  [in] TBSCertList의 포인터
    @param cert         [in] Certificate의 포인터
    @retval RET_CRL_CERT_REVOCATED 인증서가 TBSCertList에 포함
    @retval RET_CRL_CERT_NOT_REVOCATED 인증서가 TBSCertList에 미포함

    주어진 인증서의 일련번호가 TBSCertList내에 포함 여부를 검사한다.
*/
LIBSPEC_CKM
ERT TBSCertList_CheckRevocatedCert(TBSCertList *tbsCertList,
                                   Certificate *cert);

/** @ingroup CRL
    @brief 주어진 인증서가 TBSCertList에 들어있는지의 여부를 검사한다.
    @param tbsCertList  [in] TBSCertList의 포인터
    @param cert         [in] Certificate의 포인터
    @param checkTime    [in] 폐지 여부를 체크하고자 하는 시각
    @retval RET_CRL_CERT_REVOCATED 인증서가 TBSCertList에 포함
    @retval RET_CRL_CERT_NOT_REVOCATED 인증서가 TBSCertList에 미포함
    @retval RET_CRL_CERT_NOT_REVOCATED_AT_TIME 인증서가 TBSCertList에
            포함되어 있으나, 폐지 시각은 checkTime 이후임

    주어진 인증서의 일련번호가 TBSCertList내에 포함 여부를 검사한다.
*/
LIBSPEC_CKM
ERT TBSCertList_CheckRevocatedCertAtTime(TBSCertList *tbsCertList,
                                         Certificate *cert,
                                         struct tm   *checkTime);

/** @ingroup CRL
    @brief 주어진 인증서 일련 번호에 맞는 TBSCertList 내의 RevokedCertificate를
           찾는다.
    @param tbsCertList  [in] TBSCertList의 포인터
    @param serial       [in] 인증서 일련번호의 포인터
    @return 찾은 경우 이의 pointer 값. 없는 경우 NULL 

    주어진 인증서에 대응하는 TBSCertList내의 RevokedCertificate를 찾는다.
    있으면 이의 pointer 값을, 없으면 NULL을 리턴한다. return된 
    RevokedCertificate은 새로 alloc된 값이므로 반드시 ASN_Del()로 지워주어야
    만 한다.
*/
LIBSPEC_CKM
RevokedCertificate* TBSCertList_GetRevokedCert(
                                TBSCertList             *tbsCertList,
                                CertificateSerialNumber *serialNumber);

/** @ingroup CRL
    @brief TBSCertList 내의 RevokedCertificate를 차례대로 갖고 온다.
    @param revCert      [out] 갖고 온 다음 RevokedCertificate의 포인터
    @param tbsCertList  [in] TBSCertList의 포인터
    @param handle       [in] 다음 RevokedCertificate를 찾기 위한 핸들 값.
                             NULL이면 제일 처음 것을 찾는다.
    @return 찾은 경우 다음 검색에 쓸 수 있는 핸들 값. 더 이상 없는 경우 NULL 

    TBSCertList내의 RevokedCertificate들을 차례대로 갖고 온다.
    handel 파라메터를 NULL로 주면 제일 처음 RevokedCertificate를 찾고,
    다음 검색을 위한 handle 값을 리턴한다. 이 리턴된 handle 값을
    입력으로 다시 호출하면 그 다음 RevokedCertificate를 찾는다.
    더 이상 가지고 올 RevokedCertificate이 없으면 NULL을 리턴한다.

*/
LIBSPEC_CKM
void* TBSCertList_GetRevokedCertNext(RevokedCertificate **revCert,
                                     TBSCertList         *tbsCertList,
                                     void                *handle);


/*****************************************************************************
 * CRL manipulating functions
 */

/** @ingroup CRL
    @brief CRL에 주어진 TBSCertList를 입력한다.
    @param crl         [in] CRL의 포인터
    @param tbsCertList  [in] TBSCertList의 포인터
    @return 성공한 경우 SUCCESS

    CRL에 주어진 TBSCertList를 입력한다. 이때 입력된 TBSCertList는
    CRL의 일부로 포함이 되므로 이 함수 호출 후에 ASN_Del()을 해서는
    안된다.
*/
LIBSPEC_CKM
ERT CRL_SetTBSCertListP(CRL *crl, TBSCertList *tbsCertList);


LIBSPEC_CKM
ERT CRL_GetSignatureValuePK(PKCryptSig *sigVal, CRL *crl);

LIBSPEC_CKM
ASNBuf* CRL_GetSignatureValue(CRL *crl);

#define CRL_GetSignatureAlgNid(a) ((a)->signatureAlgorithm->algorithm->nid)


/** @ingroup CRL
    @brief 주어진 CRL에 전자서명을 행한다.
    @param crl [in/out]서명될 CRL
    @param tbsCertList  [in] TBSCertList의 포인터. NULL을 줄 수 있다.
    @param issuerKey [in] 서명할 CA의 비공개키
    @param priInfo 서명할 CA 비공개키 서명 정보

    주어진 CRL에 CA의 전자 서명을 행한다.
*/
LIBSPEC_CKM
ERT CRL_GenPK(CRL           *crl, 
              TBSCertList   *tbsCRL,
              PKCryptPriKey *issuerKey,
              PKCryptParam  *systemParam,
              AlgDesc        hashAlgorithm,
              const void    *kcdsaPub);

/** @ingroup CRL
    @brief 주어진 CRL에 전자서명을 행한다.
    @param crl [in/out]서명될 CRL
    @param tbsCertList  [in] TBSCertList의 포인터. NULL을 줄 수 있다.
    @param issuerCert [in] 서명할 CA의 인증서
    @param priInfo 서명할 CA 비공개키 서명 정보

    주어진 CRL에 CA의 전자 서명을 행한다.
*/
LIBSPEC_CKM
ERT CRL_Gen(CRL             *crl, 
            TBSCertList     *tbsCRL,
            PrivateKeyInfo  *issuerPriKeyInfo,
            Parameter       *domainParam,
            AlgDesc          hashAlg,
            Certificate     *issuerCert);


/** @ingroup CRL
    @brief 주어진 CRL의 전자서명을 검증한다.
    @param crl 서명을 검증할 CRL
    @param issuerCert CRL을 서명한 CA의 인증서
    @param param 서명 알고리즘이 KCDSA나 DSA일 경우, 인증서에 parameter가
                 들어있지 않을 때, 이 parameter를 직접 준다.

    주어진 CRL의 전자 서명을 검증한다.  서명 알고리즘이 KCDSA나
    DSA인데 인증서 내에 키 파라메터가 들어있지 않다면 같이 파라메터를
    줄 수 있다.
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
    @brief CRL을 파일에서 읽어 온다.
    @param filePath [in] CRL이 저장된 파일 경로
    @ret CRL의 포인터, 실패시 NULL

    DER 인코딩되어 파일로 저장된 CRL을 디코딩하여 메모리로 읽어 온다.
*/
LIBSPEC_CKM                     
CRL* CRL_NewFromFile(const char *filePath);

/** @ingroup CRL
    @brief DER 인코딩되어 메모리에 저장된 CRL을 읽어 온다.
    @param ptr    [in] DER 인코딩된 CRL이 존재하는 메모리 주소
    @param length [in] DER 인코딩된 CRL이 존재하는 메모리의 길이
    @ret CRL의 포인터, 실패시 NULL

    DER 인코딩되어 메모리에 존재하는 CRL을 디코딩하여 읽어 온다.
    네트웍크등을 통해 인코딩된 CRL을 전달받았을 때, 이를 디코딩하는데
    사용한다.
*/
LIBSPEC_CKM                     
CRL* CRL_NewFromMem(const void *ptr, int length);

/** @ingroup CRL
    @brief CRL을 DER 인코딩하여 파일에 저장한다.
    @param crl      [in] CRL의 포인터
    @param filePath [in] CRL이 저장될 파일 경로

    CRL을 DER 인코딩하여 주어진 경로에 파일 형태로 저장한다.
*/
LIBSPEC_CKM
ERT CRL_WriteFile(CRL *crl, const char *filePath);

#ifdef __cplusplus
}
#endif

#endif /* _CRL_H_ */
