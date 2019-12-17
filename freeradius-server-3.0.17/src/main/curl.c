#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(int argc, char *argv[])
{
  CURL *curl;
  CURLcode res;


  char* url= "http://[2001:2d8:270:10c1:41f5:7dd6:4016:a90e]:9090/Authorize/SavingAuthKey?calling_id=121213131&sys_title=aaaa&fep_key=123123&nms_key=12312323";

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);

    res = curl_easy_perform(curl);
	if (CURLE_OK != res)
	{
		printf(" Error from cURL \n");
	}
	else
	{
		printf(" Success from cURL \n");
	}
	
    curl_easy_cleanup(curl);
  }
  return 0;
}
