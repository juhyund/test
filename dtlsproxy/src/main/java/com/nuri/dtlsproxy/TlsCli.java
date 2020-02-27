package com.nuri.dtlsproxy;
//package com.penta.ptls.sample;

import com.penta.ptls.Constant;
import com.penta.ptls.PtlsClient;
import com.penta.ptls.PtlsException;
import com.penta.ptls.PtlsSocket;
import com.penta.ptls.Util;


/**
 * 샘플은 Visual Studio Code 로 작성하였다.
 * 직접 실행 및 디버깅을 해보려면 아래 파일들을 수정 후 디버그 - 디버깅 시작을 선택한다.
 *  1 .classpath 파일에서 jar 파일의 경로 수정
 *  2 .vscode/launch.json 에서 PATH 경로 수정
 * Visual Studio Code 는 편의를 위해 사용하였으며, 이에 대한 지원은 하지 않는다. (샘플 소스와 관련 없음)
 */

 /**
  * TLS 클라이언트 샘플
  */
public class TlsCli {

    public static boolean USE_DTLS = true;
    public static boolean USE_NONBLOCK = true;

    public static void main(String[] args) throws Exception {
        int ret = 0;

        PtlsClient client = new PtlsClient();

        // 인증서와 개인키, 설정 등을 초기화한다.
        if (USE_DTLS) {
            //ret = client.init(Constant.Transport.DTLS, keyFilePath, pwd, certFilePath, confFilePath);
            ret = client.init(Constant.Transport.DTLS, null, null, null, null);
        } 
        if (ret != 0) {
            System.err.println("client.init() : " + Util.getErrorString(ret));
            return;
        }

        // 아래 설정들은 특정 사이트를 위해 SSL의 기본 기능을 제한시키는 설정이니 모르면 사용하지 않도록 한다.
        // {
        //     // 통신 대상의 호스트명을 비교하지 않음
        //     client.setCompareHostname(false);
        //     // 인증서 체인의 상위 인증서들을 전송하지 않음
        //     client.setSendLeafCertOnly(true);
        //     // 사용할 ciphersuites 를 직접 정의
        //     CipherSuiteElement[] supportedCipherSuiteList = {
        //         CipherSuiteElement.TLS_ECDH_ECDSA_WITH_ARIA_128_GCM_SHA256,
        //     };
        //     client.setCustomCipherSuiteList(supportedCipherSuiteList);
        // }
        

        client.setReadTimeout(0);
        Constant.CipherSuiteElement[] cipershutes = new Constant.CipherSuiteElement[] { Constant.CipherSuiteElement.TLS_PSK_WITH_ARIA_128_GCM_SHA256 };
        client.setCustomCipherSuiteList(cipershutes);
        //byte[] psk = new byte[] { -83, -119, -93, -112, -109, 17, 2, -27, 57, 29, 8, 50, 123, -92, 52, -23 };
        
        
        //56 23 11 65 1f ff 25 2c 80 98 6b a2 35 9a 23 2a 03 67 60 3b c1 d7 83 d4 5a 85 0a 6c 68 d4 b3 a3
        //byte[] pskId = "PSK ID".getBytes("UTF-8");
        //client.setPreSharedKey(psk, pskId);


        {
            byte[] psk = new byte[] {
                (byte) 0xAD, (byte) 0x89, (byte) 0xA3, (byte) 0x90, (byte) 0x93, (byte) 0x11, (byte) 0x02, (byte) 0xE5,
                (byte) 0x39, (byte) 0x1D, (byte) 0x08, (byte) 0x32, (byte) 0x7B, (byte) 0xA4, (byte) 0x34, (byte) 0xE9
            };
            byte[] pskIdentity = "CLI_001".getBytes("UTF-8");
            client.setPreSharedKey(psk, pskIdentity);
        }

        PtlsSocket socket;
        // 서버로 연결을 시도한다.
        try {
            System.out.println("connect to 127.0.0.1:15684 ...");
            socket = client.connect("127.0.0.1", "15684", 8000);
        } catch (PtlsException e) {
            System.err.println("client.connect() : " + e.getMessage());
            client.close();
            return;
        }

        System.out.println("selected ciphersuites : " + socket.getSessionCiphersuite());
        
        if (USE_NONBLOCK) {
            // Non-blocking 방식을 사용할 경우 설정해준다.
            socket.set_block(false);
        }

        // 보낸 메시지를 그대로 돌려받는 에코 클라이언트 (이 샘플에서는 따로 처리하지 않았지만, 실제 보내고 받은 사이즈가 맞는지 확인해야 한다)
        //while (true) {
            System.out.print("input message : ");
            //Scanner scan = new Scanner(System.in);
            //String msg = scan.nextLine();
            //scan.close();
            //if (msg.equals("exit")) {
            //    break;
            //}
            String msg="test1234";
            byte[] writeBytes = msg.getBytes("UTF-8");

            System.out.println("write : " + msg);
            // 세션으로 데이터를 출력한다.
            if (USE_NONBLOCK) {
                // Non-blocking 방식을 사용할 경우 PTLS_ERR_SSL_WANT_WRITE 를 받았다면 다시 시도해야 한다.
                do {
                    ret = socket.write(writeBytes, 0, writeBytes.length);
                } while (ret == Constant.PTLS_ERR_SSL_WANT_WRITE);
            } else {
                ret = socket.write(writeBytes, 0, writeBytes.length);
            }
            if (ret < 0) {
                System.err.println("socket.write() : " + Util.getErrorString(ret));
                //break;
            }

            byte[] readBytes = new byte[1024];
            // 세션에서 데이터를 읽어들인다.
            if (USE_NONBLOCK) {
                // Non-blocking 방식을 사용할 경우 PTLS_ERR_SSL_WANT_READ 를 받았다면 다시 시도해야 한다.
                do {
                    ret = socket.read(readBytes, 0, readBytes.length);
                } while (ret == Constant.PTLS_ERR_SSL_WANT_READ);
            } else {
                ret = socket.read(readBytes, 0, readBytes.length);
            }
            if (ret < 0) {
                System.err.println("socket.read() : " + Util.getErrorString(ret));
                //break;
            }

            String readString = new String(readBytes, 0, ret, "UTF-8");
            System.out.println("read : " + readString);

            if (readString.equals(msg) == false) {
                System.err.println("write and read not matched");
                //break;
            }
        //}
        socket.close();
        client.close();
    }
}
