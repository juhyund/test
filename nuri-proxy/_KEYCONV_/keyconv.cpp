#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>

#include "log.h"
#include "ptls.h"
#include "ce/asn1.h"
#include "ce/ckm_pkcrypt.h"
#include "ce/base64.h"

int convert_kepco_privatekey(char *path);

int main(int argc, char* argv[]){

	int ret = 0;

	log_stderr_open(LOG_INFO);

	PCIS_CC_Initialize();
	log_info("argv[1] = %s ", argv[1]);
	if ( ret=convert_kepco_privatekey(argv[1]) < 0 )
	{
		log_error("convert_kepco_privatekey failed.");
	}
	log_info("convert_kepco_privatekey succeed.");
	PCIS_CC_Initialize();

	return 0;
}


int convert_kepco_privatekey(char *path)
{
    FILE *rfd=NULL, *wfd=NULL;
    struct stat file_info;

    int  ret=0;
    char read_buf[128]={0x00,};
    int  read_len=0;
    char pkey_buf[256]={0x00,};
    char *pkey_path=path;

    ASNBuf       *asnbuf = NULL;
    ECPrivateKey *asnKey = NULL;

    if (0!=lstat(pkey_path, &file_info))     // 인증서 파일이 존재여부 확인
    {
        log_error("Private key empty: %s", path);
        return -1;
    }

    rfd = fopen(pkey_path, "rb");
    read_len = fread(read_buf, sizeof(unsigned char), 64, rfd);
    fclose(rfd);
    asnKey = ASN_New(ECPrivateKey, asnbuf);

    ASNInt_SetInt(asnKey->version, 1); //버전 설정

    ASNOctStr_Set(asnKey->privateKey, (const char*)read_buf, read_len);  //개인키값 설정, buf에 한전 제공 32Byte 바이너리 데이터 설정
    ASNSeq_NewOptional(pASN(&(asnKey->parameters)), ASN_SEQ(asnKey));
    ASNChoice_Select(ASN_CHOICE(asnKey->parameters), 1);
    ASNOid_SetByNid(asnKey->parameters->choice.namedCurve, NID_secp256r1);

    asnbuf = ASN_EncodeDER(asnKey);  //개인키를 DER 인코딩하여 ASN Buf에 저장
    if(asnbuf == NULL)
    {
        log_error("ASN_EncodeDER error: %s", path);
        return -1;
    }

    //DER인코딩을 BASE64인코딩으로 변경
    char* enc = NULL;
    enc = (char*)malloc(1024);
    ret = Base64_EncodeWithNewLine(enc, 1024, (BYTE*)asnbuf->data, asnbuf->len);
    if (ret != 0)
    {
        if (enc) free(enc);
        log_error("Base64_EncodeWithNewLine error: %s", path);
        return -1;
    }

    //comment 첨부하여 PEM조합완성
    strcpy(pkey_buf, "-----BEGIN EC PRIVATE KEY-----\n");
    strcat(pkey_buf, enc);
    strcat(pkey_buf, "\n-----END EC PRIVATE KEY-----");
    //printf("\nPEM DATA=\n%s\n", (char *)pkey_buf);
    ASN_Del(asnKey);

    if (enc) free(enc);
    memset(&file_info, 0x00, sizeof(struct stat));

    pkey_path[strlen(pkey_path)-3] = 'p';
    pkey_path[strlen(pkey_path)-2] = 'e';
    pkey_path[strlen(pkey_path)-1] = 'm';
    wfd = fopen(pkey_path, "wb");
    fwrite(pkey_buf, sizeof(unsigned char), strlen(pkey_buf), wfd);
    fclose(wfd);
    return 0;
}
