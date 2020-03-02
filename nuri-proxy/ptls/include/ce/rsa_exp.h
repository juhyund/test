/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _RSA_EXP_H_
#define _RSA_EXP_H_

/** @ingroup RSA
    @brief RSA ���� ���� �Լ�
    @param S       [out] RSASig�� ������
    @param M       [in] ������ ������ ������
    @param MLen    [in] ������ ������ ����Ʈ ���� ����
    @param priKey  [in] RSAPriKey�� ������  
    @param param   [in] NULL  
    @param hashAlg [in] ����� hash �˰����� descriptor
  
    RSA ���� �˰��򿡼��� �����Ű ����ü�� �ý��� �Ķ���Ͱ� ���ԵǾ� �ֱ�
    ������ �ý��� �Ķ���͸� ���� �Է� ���� �ʿ䰡 ����.  \e param�� �ٸ� ����
    �˰������ �������̽� ��ġ�� ���� ���Ե� �����̰�, ���ο��� ������
    �ʴ´�. NULL���� �Է��Ѵ�.
    
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
    @brief RSA ���� ���� �Լ�
    @param S       [in] RSASig�� ������
    @param M       [in] ���� ������ ������ ������
    @param MLen    [in] ���� ������ ������ ����Ʈ ���� ����
    @param priKey  [in] RSAPriKey�� ������  
    @param param   [in] NULL  
    @param hashAlg [in] ����� hash �˰����� descriptor
    @retval ER_RSA_VP1_SIG_OUT_OF_RANGE signature value is out of range
  
    RSA ���� �˰��򿡼��� �����Ű ����ü�� �ý��� �Ķ���Ͱ� ���ԵǾ� �ֱ�
    ������ �ý��� �Ķ���͸� ���� �Է� ���� �ʿ䰡 ����. \e param�� �ٸ� ����
    �˰������ �������̽� ��ġ�� ���� ���Ե� �����̰�, ���ο��� ������
    �ʴ´�. NULL���� �Է��Ѵ�.
    
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
