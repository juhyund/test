#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>     // fopen, fseek, ftell, fread, fclose 함수가 선언된 헤더 파일
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일
#include <string.h>    // memset 함수가 선언된 헤더 파일

char* file_to_buffer(char*);

int main(){
  char *buffer;

  buffer=file_to_buffer("/usr/local/nuri-ssl/certs/000B12000000030DCA.der");
  printf("%s\n", buffer);
}

char* file_to_buffer(char *fdir)
{

    int size;
    int count;
    char *buffer;

    FILE *fp = fopen(fdir, "r");

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    buffer = malloc(size + 1);
    memset(buffer, 0 , size + 1);
    fseek(fp, 0, SEEK_SET);
    count = fread(buffer, size, 1, fp);


 return buffer;
}
