/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _KCDSA_EXP_H_
#define _KCDSA_EXP_H_

ERT KCDSA_SSA_S_Hash(       void *S,
                      const BYTE *hash,
                            BWT   hashLen,
                      const void *priKey,
                      const void *param,
                      const void *hashAlg,
                      const void *pubKey);

ERT KCDSA_SSA_V_Hash( const void *S,
                      const BYTE *hash,
                            BWT   hashLen,
                      const void *pubKey,
                      const void *param,
                      const void *hashAlg);

ERT KCDSA_SSA_S_File(       void *S,
                            FILE *M,
                            BWT   MLen,
                      const void *priKey,
                      const void *param,
                      const void *hashAlg,
                      const void *pubKey);

ERT KCDSA_SSA_V_File( const void *S,
                            FILE *M,
                            BWT   MLen,
                      const void *pubKey,
                      const void *param,
                      const void *hashAlg);

ERT KCDSA_SSA_S0_File(       void *S,
                             FILE *M,
                             BWT   MLen,
                       const void *priKey,
                       const void *param,
                       const void *hashAlg,
                       const BYTE *z);

ERT KCDSA_SSA_V0_File( const void *S,
                             FILE *M,
                             BWT   MLen,
                       const void *pubKey,
                       const void *param,
                       const void *hashAlg,
                       const BYTE *z);

#endif /* _KCDSA_EXP_H_ */
