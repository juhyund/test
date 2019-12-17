/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _DSA_EXP_H_
#define _DSA_EXP_H_

/** @ingroup DSA
    @brief DSA ���� ���� �Լ� 
    @param S       [out] DSASig�� ������
    @param M       [in] ������ ������ ������
    @param MLen    [in] ������ ������ ����Ʈ ���� ����
    @param priKey  [in] DSAPriKey�� ������  
    @param param   [in] DSAParam�� ������
    @param hashalg [in] ����� hash �˰����� descriptor
    @sa DSA_SSA_V

    DSA ���� ���� �Լ��� ������ �޽����� �޽��� ����, �������� �����Ű, �ý��� �Ķ����, �ؽ� �˰����� �Է����� �޾�
    ������ DSASig�� ����Ѵ�. ���� ���� ���� �� ���� �ڵ带 �����Ѵ�.
*/
ERT DSA_SSA_S_File(       void *S,        
                          FILE *M,       
                          BWT   MLen, 
                    const void *priKey, 
                    const void *param, 
                    const void *hashAlg);

/** @ingroup DSA
    @brief DSA ���� ���� �Լ�
    @param S       [in] DSASig�� ������
    @param M       [in] ���� ������ ������ ������
    @param MLen    [in] ���� ������ ������ ����Ʈ ���� ����
    @param priKey  [in] DSAPriKey�� ������  
    @param param   [in] DSAParam�� ������
    @param hashalg [in] ����� hash �˰����� descriptor
    @retval ER_DSA_VP_SIG_OUT_OF_RANGE signature value is out of range
    @sa DSA_SSA_S
    
    DSA ���� ���� �Լ��� ����, ���� ������ �޽����� �޽��� ����, �������� ����Ű, �ý��� �Ķ����, �ؽ� �˰����� �Է����� �޾�
    ������ �����Ѵ�. ���� ���� ���� �� ���� �ڵ带 �����Ѵ�.
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
