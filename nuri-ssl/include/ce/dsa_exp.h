/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _DSA_EXP_H_
#define _DSA_EXP_H_

/** @ingroup DSA
    @brief DSA 서명 생성 함수 
    @param S       [out] DSASig의 포인터
    @param M       [in] 서명할 파일의 포인터
    @param MLen    [in] 서명할 파일의 바이트 단위 길이
    @param priKey  [in] DSAPriKey의 포인터  
    @param param   [in] DSAParam의 포인터
    @param hashalg [in] 사용할 hash 알고리즘의 descriptor
    @sa DSA_SSA_V

    DSA 서명 생성 함수는 서명할 메시지와 메시지 길이, 서명자의 비공개키, 시스템 파라미터, 해쉬 알고리즘을 입력으로 받아
    서명값을 DSASig로 출력한다. 서명 생성 실패 시 에러 코드를 리턴한다.
*/
ERT DSA_SSA_S_File(       void *S,        
                          FILE *M,       
                          BWT   MLen, 
                    const void *priKey, 
                    const void *param, 
                    const void *hashAlg);

/** @ingroup DSA
    @brief DSA 서명 검증 함수
    @param S       [in] DSASig의 포인터
    @param M       [in] 서명 검증할 파일의 포인터
    @param MLen    [in] 서명 검증할 파일의 바이트 단위 길이
    @param priKey  [in] DSAPriKey의 포인터  
    @param param   [in] DSAParam의 포인터
    @param hashalg [in] 사용할 hash 알고리즘의 descriptor
    @retval ER_DSA_VP_SIG_OUT_OF_RANGE signature value is out of range
    @sa DSA_SSA_S
    
    DSA 서명 검증 함수는 서명값, 서명 검증할 메시지와 메시지 길이, 서명자의 공개키, 시스템 파라미터, 해쉬 알고리즘을 입력으로 받아
    서명값을 검증한다. 서명 검증 실패 시 에러 코드를 리턴한다.
*/
ERT DSA_SSA_V_File( const void *S, 
                          FILE *M, 
                          BWT   MLen, 
                    const void *pubKey, 
                    const void *param, 
                    const void *hashAlg);

ERT DSA_SSA_S_Hash(       void *S,        
                    const BYTE *hash,       
                          BWT   hashLen, 
                    const void *priKey, 
                    const void *param, 
                    const void *hashAlg);

ERT DSA_SSA_V_Hash( const void *S, 
                    const BYTE *hash, 
                          BWT   hashLen, 
                    const void *pubKey, 
                    const void *param, 
                    const void *hashAlg);

#endif /* _DSA_EXP_H_ */
