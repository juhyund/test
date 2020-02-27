package com.nuri.dtlsproxy;

import com.penta.ptls.Constant;
import com.penta.ptls.PeerClientInfo;
import com.penta.ptls.PtlsException;
import com.penta.ptls.PtlsServer;
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
  * TLS 서버 샘플
  */
public class TlsSrv {

    public static boolean USE_DTLS = true;
    public static boolean USE_NONBLOCK = true;

    public static void main(String[] args) throws Exception {
        int ret = 0;
        String keyFilePath = "resource/127.0.0.1.key.pem";
        String certFilePath = "resource/127.0.0.1.pem";
        String confFilePath = "resource/conf";
        String pwd = null;

        PtlsServer server = new PtlsServer();

        // 인증서와 개인키, 설정 등을 초기화한다.
        if (USE_DTLS) {
            //ret = server.init(Constant.Transport.DTLS, keyFilePath, pwd, certFilePath, confFilePath);
            ret = server.init(Constant.Transport.DTLS, null, null, null, null);
        } else {
            ret = server.init(Constant.Transport.TLS, keyFilePath, pwd, certFilePath, confFilePath);
        }
        if (ret != 0) {
            System.err.println("server_init() : " + Util.getErrorString(ret));
            return;
        }

        // 아래 설정들은 특정 사이트를 위해 SSL의 기본 기능을 제한시키는 설정이니 모르면 사용하지 않도록 한다.
        // {
        //     // 통신 대상의 호스트명을 비교하지 않음
        //     server.setCompareHostname(false);
        //     // 인증서 체인의 상위 인증서들을 전송하지 않음
        //     server.setSendLeafCertOnly(true);
        //     // 사용할 ciphersuites 를 직접 정의
        //     CipherSuiteElement[] supportedCipherSuiteList = {
        //         CipherSuiteElement.TLS_ECDH_ECDSA_WITH_ARIA_128_GCM_SHA256,
        //     };
        //     server.setCustomCipherSuiteList(supportedCipherSuiteList);
        // }

        // 서버를 연결 대기 상태로 설정한다.
        server.setReadTimeout(0);
        Constant.CipherSuiteElement[] cipershutes = new Constant.CipherSuiteElement[] { Constant.CipherSuiteElement.TLS_PSK_WITH_ARIA_128_GCM_SHA256 };
        
        
        
        server.setCustomCipherSuiteList(cipershutes);
        byte[] psk = new byte[] { -83, -119, -93, -112, -109, 17, 2, -27, 57, 29, 8, 50, 123, -92, 52, -23 };
        
        byte[] pskId = "PSK ID".getBytes("UTF-8");
        server.setPreSharedKey(psk, pskId);
        
        
        ret = server.bind("127.0.0.1", "5683");
        if (ret != 0) {
            System.err.println("server.bind() : " + Util.getErrorString(ret));
            return;
        }

        while (true) {
            PtlsSocket socket;
            // 클라이언트의 연결을 기다린다.
            try {
                System.out.println("waiting client connect...");
                socket = server.accept();
            } catch (PtlsException e) {
                System.err.println("server.accept() : " + e.getMessage());
                continue;
            }

            System.out.println("selected ciphersuites : " + socket.getSessionCiphersuite());
            
            if (USE_NONBLOCK) {
                // Non-blocking 방식을 사용할 경우 설정해준다.
                socket.set_block(false);
            }

            if(socket != null) {
                PeerClientInfo localPeerClientInfo = (socket).getPeerClientInfo(true);
                System.out.println("clientIp: " + localPeerClientInfo.getClientIp());
                System.out.println("clientPort: " + localPeerClientInfo.getClientPort());
                System.out.println("encFixedIv: " + byteArrayToHexString(localPeerClientInfo.getEncFixedIv()));
                System.out.println("decFixedIv: " + byteArrayToHexString(localPeerClientInfo.getDecFixedIv()));
                System.out.println("encKey: " + byteArrayToHexString(localPeerClientInfo.getEncKey()));
                System.out.println("decKey: " + byteArrayToHexString(localPeerClientInfo.getDecKey()));
                
                
            }

            
            // 받은 메시지를 그대로 다시 보내주는 에코 서버 샘플 (이 샘플에서는 따로 처리하지 않았지만, 실제 보내고 받은 사이즈가 맞는지 확인해야 한다)

            byte[] buf = new byte[1024];
            int readSize = 0;
            while (true) {
                // 세션에서 데이터를 읽어들인다.
                if (USE_NONBLOCK) {
                    // Non-blocking 방식을 사용할 경우 PTLS_ERR_SSL_WANT_READ 를 받았다면 다시 시도해야 한다.
                    do {
                        ret = socket.read(buf, 0, buf.length);
                    } while (ret == Constant.PTLS_ERR_SSL_WANT_READ);
                } else {
                    ret = socket.read(buf, 0, buf.length);
                }
                if (ret < 0) {
                    System.err.println("socket.read() : " + Util.getErrorString(ret));
                    break;
                }
                readSize = ret;
                String readString = new String(buf, 0, readSize, "UTF-8");
                System.out.println("read : " + readString);

                // exit 를 받으면 바로 세션을 종료하도록 구현되었다.
                if (readString.equals("exit")) {
                    break;
                }

                // 세션으로 데이터를 출력한다.
                if (USE_NONBLOCK) {
                    // Non-blocking 방식을 사용할 경우 PTLS_ERR_SSL_WANT_WRITE 를 받았다면 다시 시도해야 한다.
                    do {
                        ret = socket.write(buf, 0, readSize);
                    } while (ret == Constant.PTLS_ERR_SSL_WANT_WRITE);
                } else {
                    ret = socket.write(buf, 0, readSize);
                }
                if (ret < 0) {
                    System.err.println("socket.write() : " + Util.getErrorString(ret));
                    break;
                }
                System.out.println("write : " + readString);
            }
            socket.close();
        }

        // not reachable
        // server.close();
        // System.out.println("server.close()");
    }
    
    private static String byteArrayToHexString(byte[] paramArrayOfByte)
    {
      StringBuilder localStringBuilder = new StringBuilder();
      for (int i = 0; i < paramArrayOfByte.length; i++)
      {
        String str = Integer.toHexString(0xFF & paramArrayOfByte[i]);
        if (str.length() == 1) {
          localStringBuilder.append('0');
        }
        localStringBuilder.append(str);
      }
      return localStringBuilder.toString();
    }
}
