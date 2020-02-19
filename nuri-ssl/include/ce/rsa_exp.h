/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _RSA_EXP_H_
#define _RSA_EXP_H_

/** @ingroup RSA
    @brief RSA 서명 생성 함수
    @param S       [out] RSASig의 포인터
    @param M       [in] 서명할 파일의 포인터
    @param MLen    [in] 서명할 파일의 바이트 단위 길이
    @param priKey  [in] RSAPriKey의 포인터  
    @param param   [in] NULL  
    @param hashAlg [in] 사용할 hash 알고리즘의 descriptor
  
    RSA 서명 알고리즘에서는 비공개키 구조체에 시스템 파라미터가 포함되어 있기
    때문에 시스템 파라미터를 따로 입력 받을 필요가 없다.  \e param은 다른 서명
    알고리즘과의 인터페이스 일치를 위해 포함된 인자이고, 내부에서 사용되지
    않는다. NULL값을 입력한다.
    
    \code
    RSA_SSA_S(&S, "This is a test message!", len, &pri, NULL, SHA1);  
    \endcode
    
    @sa RSA_SSA_V_File
*/
ERT RSA_SSA_S_File(       void *S,
                          FILE *M, 
                          BWT   MLen,
                          void *priKey,
                    const void *param,      
                    const void *hashAlg);

/** @ingroup RSA
    @brief RSA 서명 검증 함수
    @param S       [in] RSASig의 포인터
    @param M       [in] 서명 검증할 파일의 포인터
    @param MLen    [in] 서명 검증할 파일의 바이트 단위 길이
    @param priKey  [in] RSAPriKey의 포인터  
    @param param   [in] NULL  
    @param hashAlg [in] 사용할 hash 알고리즘의 descriptor
    @retval ER_RSA_VP1_SIG_OUT_OF_RANGE signature value is out of range
  
    RSA 서명 알고리즘에서는 비공개키 구조체에 시스템 파라미터가 포함되어 있기
    때문에 시스템 파라미터를 따로 입력 받을 필요가 없다. \e param은 다른 서명
    알고리즘과의 인터페이스 일치를 위해 포함된 인자이고, 내부에서 사용되지
    않는다. NULL값을 입력한다.
    
    @sa RSA_SSA_S_File
*/
ERT RSA_SSA_V_File(       void *S,
                          FILE *M,
                          BWT   MLen,
                          void *pubKey,
                    const void *param,      
                    const void *hashAlg);

ERT RSA_SSA_S_Hash(       void *S,
                          const BYTE *hash, 
                          BWT   hashLen,
                          void *priKey,
                    const void *param,      
                    const void *hashAlg);

ERT RSA_SSA_V_Hash(       void *S,
                          const BYTE *hash,
                          BWT   hashLen,
                          void *pubKey,
                    const void *param,      
                    const void *hashAlg);

#endif /* _RSA_EXP_H_ */
