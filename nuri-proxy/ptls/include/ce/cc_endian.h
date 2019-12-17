/** @file cc_endian.h
    @brief endian에 따른 처리
    
    Endian에 따른 처리 모듈을 정의한다.
*/

#ifndef _ENDIAN_H_
#define _ENDIAN_H_

/* XXX: masking with meaningless 0xffff or 0xffffffff or 0xffffffffffffffffLL
 * is due to the peculiar behavior of arithmetic right shift operation in C.
 * When the operand is a negative integer the left-most bits will be filled
 * with 1's (which is not desirable) instead of 0's (which is desirable). In
 * order to compensate this, we mask it with 0xffff things, which results in
 * implicit integer promotion to unsigned type. Right shift with unsigned
 * integer gives left-most bits filled with 0's.
 */
#define ROTL16(x, n)     (((x) << (n)) | (((x)&0xffff) >> (16-(n))))
#define ROTR16(x, n)     ((((x)&0xffff) >> (n)) | ((x) << (16-(n))))

#define ROTL32(x, n)     (((x) << (n)) | (((x)&0xffffffff) >> (32-(n))))
#define ROTR32(x, n)     ((((x)&0xffffffff) >> (n)) | ((x) << (32-(n))))

#define ROTL64(x, n)     (((x) << (n)) | (((x)&0xffffffffffffffffLL) >> (64-(n))))
#define ROTR64(x, n)     ((((x)&0xffffffffffffffffLL) >> (n)) | ((x) << (64-(n))))

#define ChangeEndianBT16(a) (((a)>>8)|((a)<<8))
#define ChangeEndianBT32(a) ((ROTL32((a), 8)&(BT32)0x00ff00ff)|(ROTL32((a), 24)&(BT32)0xff00ff00))
#if defined(WIN32) || defined(_WIN32_WCE)
#define ChangeEndianBT64(a) ((ROTL64((a), 8)&(BT64)0x000000ff000000ffi64)|\
                             (ROTL64((a), 24)&(BT64)0x0000ff000000ff00i64)|\
                             (ROTL64((a), 40)&(BT64)0x00ff000000ff0000i64)|\
                             (ROTL64((a), 56)&(BT64)0xff000000ff000000i64))
#else
#define ChangeEndianBT64(a) ((ROTL64((a), 8)&(BT64)0x000000ff000000ffLL)|\
                             (ROTL64((a), 24)&(BT64)0x0000ff000000ff00LL)|\
                             (ROTL64((a), 40)&(BT64)0x00ff000000ff0000LL)|\
                             (ROTL64((a), 56)&(BT64)0xff000000ff000000LL))
#endif


#if (BASE_WORD_BIT_LEN == 16)
#define ChangeEndianHWT(a)  (a)
#define ChangeEndianBWT(a)  ChangeEndianBT16(a)
#define ChangeEndianDWT(a)  ChangeEndianBT32(a)
#endif

#if (BASE_WORD_BIT_LEN == 32)
#define ChangeEndianHWT(a)  ChangeEndianBT16(a)
#define ChangeEndianBWT(a)  ChangeEndianBT32(a)
#define ChangeEndianDWT(a)  ChangeEndianBT64(a)
#endif

#if (BASE_WORD_BIT_LEN == 64)
#define ChangeEndianHWT(a)  ChangeEndianBT32(a)
#define ChangeEndianBWT(a)  ChangeEndianBT64(a)
#define ChangeEndianDWT(a)  ChangeEndianBT128(a)
#endif

#endif /* _ENDIAN_H_ */
