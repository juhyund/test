export LD_LIBRARY_PATH=/root/nuri-proxy/ptls/lib

# 개인키 Convert (_KEYCONV_)
/root/nuri-proxy/bin/_KEYCONV_ /root/nuri-proxy/_KEYCONV_/certificate/private.key 

# 인증서 PEM 변환 명령어 (직접 입력)
openssl x509 -in /root/nuri-proxy/_KEYCONV_/NTC501800000A.kepco.com.der -inform DER -out /root/nuri-proxy/_KEYCONV_/NTC501800000A.kepco.com.pem -outform PEM
