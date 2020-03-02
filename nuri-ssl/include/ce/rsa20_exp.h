/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _RSA20_EXP_H_
#define _RSA20_EXP_H_

/** @ingroup RSA20
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
ERT RSA20_SSA_S_File(       void *S,
                          FILE *M, 
                          BWT   MLen,
                          void *priKey,
                    const void *param,      
                    const void *hashAlg);
  
/** @ingroup RSA20
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
ERT RSA20_SSA_V_File(       void *S,
                          FILE *M,
                          BWT   MLen,
                          void *pubKey,
                    const void *param,      
                    const void *hashAlg);

ERT RSA20_SSA_S_Hash(       void *S,
                          const BYTE *hash, 
                          BWT   hashLen,
                          void *priKey,
                    const void *param,      
                    const void *hashAlg);
  
ERT RSA20_SSA_V_Hash(       void *S,
                          const BYTE *hash,
                          BWT   hashLen,
                          void *pubKey,
                    const void *param,      
                    const void *hashAlg);
/** @ingroup PKCRYPT
    @brief RSA �� integer�� octet string���� ��ȯ�ϴ� �Լ�
	@deprecated Use RSA or RSA21 algorithm instead
    @sa MINT_WriteInByteArray

    PKCS#1 ver 2.0(RFC2437)�� ����� integer�� octet string����
    ��ȯ�ϴ� �Լ��̴�.  �������� MINT_WriteInByteArray() �Լ���
    ����Ͽ�����, �� �Լ������� ���� byte���� ���� 0�� ��� �̸� �ǹ̾���
    ������ �Ǵ��ϰ� �����ع����� ������ �׻� ���̰� modulus ���̿�
    ���ƾ߸� �ϴ� RSA ���� �������� ���� ������
    �����״�.  �� �Լ��� MINT_WriteInByteArray()�� ���� ���� ������ �ϳ�
    PKCS#1���� ������ ��� �Է��� ���̸� ���� ��ȯ���� �ʰ� �״�� ��������
    Ư���� ������.

    */
   
#endif /* _RSA20_EXP_H_ */
