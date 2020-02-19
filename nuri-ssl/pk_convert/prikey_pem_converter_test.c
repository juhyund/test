#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "base_define.h"
#include "ce/asn1.h"
#include "cc/cc_define.h"
#include "ce/ckm_pkcrypt.h"
#include "ce/base64.h"

#define MINT_MANIPULATED_DATA_BIT_LEN 2048

#define MINT_MAX_LEN  	((MINT_MANIPULATED_DATA_BIT_LEN/BWT_BIT_LEN)*2+2)
#define MINT_SIZE 		((MINT_MAX_LEN+1)*BWT_BYTE_LEN)

char   *bin2key_buf(const unsigned char *bin, size_t len);
int    key_bufchr2bin(const char key_buf, char *out);
size_t key_bufs2bin(const char *key_buf, unsigned char **out);
int    load_private_key(char *path, char *key_buf);


char *bin2key_buf(const unsigned char *bin, size_t len)
{
	char   *out;
	size_t  i;

	if (bin == NULL || len == 0)
		return NULL;

	out = (char*) malloc(len*2+1);
	for (i=0; i<len; i++) {
		out[i*2]   = "0123456789ABCDEF"[bin[i] >> 4];
		out[i*2+1] = "0123456789ABCDEF"[bin[i] & 0x0F];
	}
	out[len*2] = '\0';

	return out;
}

int key_bufchr2bin(const char key, char *out)
{
	unsigned char key_buf = key & 0xFF;
	if (out == NULL)
		return 0;

	printf("%02X < %02X < %02X\n", '0', key_buf, '9');
	printf("%02X < %02X < %02X\n", 'A', key_buf, 'F');
	printf("%02X < %02X < %02X\n", 'a', key_buf, 'f');

	if (key_buf >= '0' && key_buf <= '9') {
		*out = key_buf - '0';
	} else if (key_buf >= 'A' && key_buf <= 'F') {
		*out = key_buf - 'A' + 10;
	} else if (key_buf >= 'a' && key_buf <= 'f') {
		*out = key_buf - 'a' + 10;
	} else {
		return 0;
	}

	return 1;
}

size_t key_bufs2bin(const char *key_buf, unsigned char **out)
{
	size_t len;
	char   b1;
	char   b2;
	size_t i;

	if (key_buf == NULL || *key_buf == '\0' || out == NULL)
		return 0;

	len = strlen(key_buf);
	if (len % 2 != 0)
		return 0;
	len /= 2;

	*out = (unsigned char *) malloc(len);
	memset(*out, 'A', len);
	for (i=0; i<len; i++) {
		if (!key_bufchr2bin(key_buf[i*2], &b1) || !key_bufchr2bin(key_buf[i*2+1], &b2)) {
			return 0;
		}
		(*out)[i] = (b1 << 4) | b2;
	}
	return len;
}

int load_private_key(char *path, char *key_buf)
{
	FILE *fd=NULL;
	int  key_buf_len=0, i=0;
	struct stat file_info;

	if (0!=lstat(path, &file_info))		// 인증서 파일이 존재여부 확인
	{
		printf("Private key empty\n");
		return 0;
	}

	fd = fopen(path, "rb");
	key_buf_len = fread(key_buf, sizeof(unsigned char), 64, fd);
	fclose(fd);

	return key_buf_len;
}

int main(int argc, char *argv[])
{
	int ret=0;
	int i=0;
	//CIS 초기화
	PCIS_CC_Initialize();

	//BYTE buf[MINT_SIZE];
	BWT len;

	//const char key_buf[128] = "94C705BF5A27D2DEB7D9323D784705736760AF3F9A7213550C41A7D68737392D";
	char key_buf[128]={0x00,};
	int  key_len=32;
	unsigned char *dec;


#if 1
	len = load_private_key(argv[1], key_buf);
	printf("Key length: %d\n", key_len);
	for (i=0; i<key_len; i++)
		printf("%02X", (key_buf[i]&0xFF));
	printf("\n");
#endif

	//len = key_bufs2bin((const char*)key_buf,&dec);
	printf("\n%d", (int)len);

	ASNBuf 		 *asnbuf = NULL;
	ECPrivateKey *asnKey = NULL;

	asnKey = ASN_New(ECPrivateKey, asnbuf);
	
	ASNInt_SetInt(asnKey->version, 1); //버전 설정
	
	//ASNOctStr_Set(asnKey->privateKey, (const char*)dec, len);  //개인키값 설정, buf에 한전 제공 32Byte 바이너리 데이터 설정
	ASNOctStr_Set(asnKey->privateKey, (const char*)key_buf, len);  //개인키값 설정, buf에 한전 제공 32Byte 바이너리 데이터 설정

	ASNSeq_NewOptional(pASN(&(asnKey->parameters)), ASN_SEQ(asnKey));
	ASNChoice_Select(ASN_CHOICE(asnKey->parameters), 1);
	ASNOid_SetByNid(asnKey->parameters->choice.namedCurve, NID_secp256r1);

	asnbuf = ASN_EncodeDER(asnKey);  //개인키를 DER 인코딩하여 ASN Buf에 저장
	if(asnbuf == NULL)
	{
		printf("\nASN_EncodeDER error");
		return -1;
	}

	//DER인코딩을 BASE64인코딩으로 변경
	char* enc = NULL;
	enc = (char*)malloc(1024);
	ret = Base64_EncodeWithNewLine( enc, 1024, (BYTE*)asnbuf->data, asnbuf->len );  
	if( ret != 0 )
	{ 
		if(enc) free(enc);
		printf("\nBase64_EncodeWithNewLine error");
		return -1;    
	}
	printf("\nbase64 : %s", (char *)enc);

	//comment 첨부하여 PEM조합완성
	char keyBuf[2048] = "";
	strcpy(keyBuf, "-----BEGIN EC PRIVATE KEY-----\n");
	strcat(keyBuf, enc);
	strcat(keyBuf, "\n-----END EC PRIVATE KEY-----");
	printf("\nPEM DATA=\n%s", (char *)keyBuf);

	ASN_Del(asnKey);

	return 0;

}
