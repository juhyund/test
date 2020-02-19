#ifndef _PBKDF_H_
#define _PBKDF_H_

/** @defgroup PBKDF Password-Based Key Derivation Function
 * @ingroup CKM
    @brief PBKDF(Password Based Key Derivation Fucntion) 모듈

    PBKDF(Password Based Key Derivation Function) 구현한 모듈로 주어진
    암호(password)로 부터 일정한 키를 구하는 기능을 한다.
    */

/** @ingroup PBKDF
    @file pbkdf.h
    @brief PBKDF 모듈 인터페이스 정의
   */

#include "ckm_define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PBKDF_MAX_PASSWORD_LEN  128
#define PBKDF_MAX_SALT_LEN      32
#define PBKDF_DEFAULT_SALT      "\x87\x56\x23\x06\x48\x32\x27\x14"
#define PBKDF_DEFAULT_SALT_LEN  8
#define PBKDF_DEFAULT_ITERATION 1353
#define PBKDF_DEFAULT_HASH_ALGORITHM  SHA1


/******************************************************************************
 * PKCS #5
 */

/** @ingroup PBKDF
    @brief PKCS5 의 password-based key derivation fuction - 1
    @param derivedKey [out] 유도된 키가 저장될 버퍼
    @param dkLen [in] 유도될 키의 바이트 길이
    @param passwd [in] password를 담고 있는 null-terminated string
    @param salt [in] salt를 담고 있는 버퍼
    @param saltLen [in] salt의 바이트 단위 길이
    @param iteration [in] 알고리즘 반복 회수, PCS5_DEFAULT_ITERATION 을 쓰기 바람.
    @param hashAlg [in] 이 함수에서 사용할 hash 알고리즘 descriptor

    이 함수는 주어진 password에 기반하여 키를 유도하는 함수이다. 입력으로는
    password 이외에 salt, iteration 값이 주어져야 한다. 결국, 앞의 입력값이
    모두 일치하면 같은 derived key 가 생성되는 것이다.

    dkLen 즉, 유도될 키의 길이는 이 함수에서 사용할 해쉬 알고리즘의 digest
    길이에 제한된다. 예를 들어, SHA1을 사용할 경우, digest 길이는 20바이트이
    므로 dkLen 도 20 이하의 값을 가져야 한다. 만약 그 이상의 길이를 입력하면
    에러를 출력하게 된다.

    @sa PBKDF_PKCS5_2
    */
LIBSPEC_CKM
ERT PBKDF_PKCS5_1( BYTE       *derivedKey, 
                   BWT         dkLen, /* < hLen */
                   const char *passwd,
                   const BYTE *salt,
                   BWT         saltLen,
                   BWT         iteration, 
                   const void *hashAlg);

/** @ingroup PBKDF
    @brief PKCS5 의 password-based key derivation fuction - 2
    @param derivedKey [out] 유도된 키가 저장될 버퍼
    @param dkLen [in] 유도될 키의 바이트 길이
    @param passwd [in] password를 담고 있는 null-terminated string
    @param salt [in] salt를 담고 있는 버퍼
    @param saltLen [in] salt의 바이트 단위 길이
    @param iteration [in] 알고리즘 반복 회수, PCS5_DEFAULT_ITERATION 을 쓰기 바람.
    @param hashAlg [in] 이 함수에서 사용할 hash 알고리즘 descriptor
    
    이 함수는 주어진 password에 기반하여 키를 유도하는 함수이다. 입력으로는
    password 이외에 salt, iteration 값이 주어져야 한다. 결국, 앞의 입력값이
    모두 일치하면 같은 derived key 가 생성되는 것이다.

    내부적으로는 PBKDF_PKCS5_1 함수와는 다른 알고리즘을 가진다. 외부적으로
    다른 점은 유도될 키의 길이가 해쉬 알고리즘의 digest 길이에 제한되지 않
    는다. 이론적으로는 (2^32 - 1) * length of digest 에 제한 받지만, 
    실제로 이러한 키 킬이가 필요한 경우는 없을 것이다.

    @sa PBKDF_PKCS5_1
    */
LIBSPEC_CKM
ERT PBKDF_PKCS5_2( BYTE       *derivedKey,
                   BWT         dkLen, /* < (2^32-1)*hLen */
                   const char *passwd,
                   const BYTE *salt,
                   BWT         saltLen, 
                   BWT         iteration, 
                   const void *hashAlg);

LIBSPEC_CKM
ERT PBKDF_PKCS5_2_old(BYTE       *derivedKey,
                      BWT         dkLen,
                      const char *passwd,
                      const BYTE *salt,
                      BWT         saltLen, 
                      BWT         iteration, 
                      const void *hashAlg);

/** @ingroup PBKDF
    @brief PKCS5 의 password-based key derivation fuction - 1
    @param derivedKey [out] 유도된 키가 저장될 버퍼
    @param dkLen [in] 유도될 키의 바이트 길이
    @param passwd [in] password를 담고 있는 null-terminated string
    @param salt [in] salt를 담고 있는 버퍼
    @param saltLen [in] salt의 바이트 단위 길이
    @param iteration [in] 알고리즘 반복 회수, PCS5_DEFAULT_ITERATION 을 쓰기 바람.
    @param hashAlg [in] 이 함수에서 사용할 hash 알고리즘 descriptor

    이 함수는 주어진 password에 기반하여 키를 유도하는 함수이다. 입력으로는
    password 이외에 salt, iteration 값이 주어져야 한다. 결국, 앞의 입력값이
    모두 일치하면 같은 derived key 가 생성되는 것이다.

    OpenSSL 의 EVP_BytesToKey 함수를 구현했다.
    유도될 키의 길이 제한이 없다.

    @sa PBKDF_PKCS5_2
    */
LIBSPEC_CKM
ERT PBKDF_PKCS5_OPENSSL( BYTE       *derivedKey, 
                   BWT         dkLen, /* < hLen */
                   BYTE       *derivedIv, 
                   BWT         diLen,
                   const char *passwd,
                   const BYTE *salt,
                   BWT         saltLen,
                   BWT         iteration, 
                   const void *hashAlg);

/******************************************************************************
 * PKCS #12
 */

/** 
    @def PBKDF_PKCS12_ID_ENCKEY 
    @ingroup PBKDF

    PKCS #12 방식의 키 유도 함수의 경우, 같은 password와 
    파라미터(salt와 iteration 수)에 대하여 서로 다른 세가지의
    키를 생성할 수 있다.
    암호화용 키, 초기 벡터, 그리고 무결성 확인용 키가 그것인데,
    데이터 암호화를 위해서 사용할 키를 유도하고 싶은 경우에는
    함수 \e PBKDF_PKCS12의 입력으로 PKCS12_ID_ENCKEY를 준다.

    @sa PBKDF_PKCS12 PBKDF_PKCS12_ID_IV PBKDF_PKCS12_ID_MACKEY
*/
/** 
    @def PBKDF_PKCS12_ID_IV
    @ingroup PBKDF

    PKCS #12 방식의 키 유도 함수에서 암호화 또는 복호화에 사용될
    초기 벡터를 만들어 내기 위해서는 함수 \e PBKDF_PKCS12의 입력으로 
    PKCS12_ID_IV를 준다.

    @sa PBKDF_PKCS12 PBKDF_PKCS12_ID_ENCKEY PBKDF_PKCS12_ID_MACKEY
*/
/** 
    @def PBKDF_PKCS12_ID_MACKEY
    @ingroup PBKDF

    PKCS #12 방식의 키 유도 함수에서 무결성 검증을 위한 MAC용 키를 얻어내기
    위해서는 함수 \e PBKDF_PKCS12의 입력으로 PKCS12_ID_MACKEY를 준다.

    @sa PBKDF_PKCS12 PBKDF_PKCS12_ID_ENCKEY PBKDF_PKCS12_ID_IV
*/
#define PBKDF_PKCS12_ID_ENCKEY  1
#define PBKDF_PKCS12_ID_IV      2
#define PBKDF_PKCS12_ID_MACKEY  3


/**
    @ingroup PBKDF
    @brief PKCS #12방식에 따른 키 유도 함수. 일종의 난수 발생기
    @param derivedKey [out] 입력으로 주어진 password, salt, iterations 등을 기초로
           유도된 키 값.
    @param dkLen [in] 구하고자 하는 키의 바이트 길이
    @param pKCS12_ID [in] 유도하고자 하는 키가 어떠한 용도인지를 표시하는 것으로
           \b PBKDF_PKCS12_ID_ENCKEY, \b PBKDF_PKCS12_ID_IV, 
           \b PBKDF_PKCS12_ID_MACKEY을 사용할 수 있다.
           각각은 암복호화를 위한 키, 암복호화 운영에 사용할 초기벡터, 그리고
           무결성을 확인하기 위한 MAC용 키로 사용할 경우에 각각 사용한다.
    @param password [in] 키 유도의 입력이 되는 패스워드. Null-terminated 스트링 형태 
    @param salt [in] 같은 password라고 할 지라도 salt가 다른 경우 다른 키 값이 유도된다.
    @param saltLen [in] 주어진 salt의 바이트 길이
    @param iterations [in] 내부에서 사용하는 키 유도 과정은 일정한 유도 방식의 반복으로
           이루어 지는데, salt와 함께 키 값을 결정하는 파라미터 역할을 한다.
           또한, iterations은 적어도 1000이상의 값을 갖는 것이 바람직하다.

    주어진 derivedKey(비트 길이)를 담을 수 있는 최소한의 바이트 길이 만큼의
    키 값(일종의 난수값)이 derivedKey로 출력된다. 용도에 따라서 pKCS12_ID를 입력해야
    하며, 키 값은 password, salt, iterations에 의해 결정된다.

    @sa PBKDF_PKCS12_UniCode
*/
LIBSPEC_CKM
ERT PBKDF_PKCS12( BYTE       *derivedKey, 
                  BWT         dkLen, 
                  BWT         idByte, 
                  const char *passwd, 
                  const BYTE *salt, 
                  BWT         saltLen,
                  BWT         iterations,
                  const void *hashAlg);

/** 
    @ingroup PBKDF
    @brief PBKDF_PKCS12와 완전히 동일한 기능을 갖는다. 하지만, 입력으로 주어지는
           password가 Uni-Code형태일 경우에 사용한다.
    @param derivedKey [out] 입력으로 주어진 password, salt, iterations 등을 기초로
           유도된 키 값.
    @param dkLen [in] 구하고자 하는 키의 바이트 길이
    @param pKCS12_ID [in] 유도하고자 하는 키가 어떠한 용도인지를 표시하는 것으로
           \b PBKDF_PKCS12_ID_ENCKEY, \b PBKDF_PKCS12_ID_IV,
           \b PBKDF_PKCS12_ID_MACKEY을 사용할 수 있다.
           각각은 암복호화를 위한 키, 암복호화 운영에 사용할 초기벡터, 그리고
           무결성을 확인하기 위한 MAC용 키로 사용할 경우에 각각 사용한다.
    @param password [in] 키 유도의 입력이 되는 패스워드. Unicode 형태
    @param passwordLen [in] password의 바이트단위 길이
    @param salt [in] 같은 password라고 할 지라도 salt가 다른 경우 다른 키 값이 유도된다.
    @param saltLen [in] 주어진 salt의 바이트 길이
    @param iterations [in] 내부에서 사용하는 키 유도 과정은 일정한 유도 방식의 반복으로
           이루어 지는데, salt와 함께 키 값을 결정하는 파라미터 역할을 한다.
           또한, iterations은 적어도 1000이상의 값을 갖는 것이 바람직하다.

    함수의 파라미터는 PBKDF_PKCS12와 한가지를 제외하고 완전히 일치한다.
    password의 경우 Null-terminated 스트링이 아니기 때문에 길이를
    입력해 주는 것이 추가되었다.

    @sa PBKDF_PKCS12
*/
LIBSPEC_CKM
ERT PBKDF_PKCS12_UniCode( BYTE       *derivedKey, 
                          BWT         dkLen, 
                          BWT         idByte,
                          const BYTE *passwd, 
                          BWT         passwdLen,
                          const void *salt, 
                          BWT         saltLen,
                          BWT         iterations,
                          const void *hashAlg);

#ifdef __cplusplus
}
#endif

#endif   /* _PBKDF_H_ */
