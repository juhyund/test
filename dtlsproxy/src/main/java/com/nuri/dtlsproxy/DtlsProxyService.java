package com.nuri.dtlsproxy;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import com.nuri.dtlsproxy.util.ProxyUtil;
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
@Service
public class DtlsProxyService {

    public static boolean USE_DTLS = true;
    public static boolean USE_NONBLOCK = true;
    
    
	@Value("${executor.max.pool.size}") 
	String maxPoolSize;

    public static void main(String[] args) throws Exception {
    	
        int ret = 0;
        PtlsServer server = new PtlsServer();

        // 인증서와 개인키, 설정 등을 초기화한다.
        if (USE_DTLS) {
            ret = server.init(Constant.Transport.DTLS, null, null, null, null);
        } 
        if (ret != 0) {
            System.err.println("server_init() : " + Util.getErrorString(ret));
            return;
        }

        System.out.println("WA-SSL version: " + Util.getVersion());
        // 서버를 연결 대기 상태로 설정한다.
        server.setReadTimeout(0);
        Constant.CipherSuiteElement[] cipershutes = new Constant.CipherSuiteElement[] { Constant.CipherSuiteElement.TLS_PSK_WITH_ARIA_128_GCM_SHA256 };     
        
        server.setCustomCipherSuiteList(cipershutes);
        ///byte[] psk = new byte[] { -83, -119, -93, -112, -109, 17, 2, -27, 57, 29, 8, 50, 123, -92, 52, -23 };

        
       // byte[] pskId = "PSK ID".getBytes("UTF-8");
        //server.setPreSharedKey(psk, pskId);
        server.setPsk(new PskManager());
        
        ret = server.bind("127.0.0.1", "5683");
        if (ret != 0) {
            System.err.println("server.bind() : " + Util.getErrorString(ret));
            return;
        }
        
		//_maxThreadWorker = Integer.parseInt(prop.getProperty("recollect.ondemand.maxworker", "10"));
        //ExecutorService executor = Executors.newFixedThreadPool(4);
        
        


        while (true) {
            PtlsSocket socket = null;
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
                System.out.println("encFixedIv: " + ProxyUtil.byteArrayToHexString(localPeerClientInfo.getEncFixedIv()));
                System.out.println("decFixedIv: " + ProxyUtil.byteArrayToHexString(localPeerClientInfo.getDecFixedIv()));
                System.out.println("encKey: " + ProxyUtil.byteArrayToHexString(localPeerClientInfo.getEncKey()));
                System.out.println("decKey: " + ProxyUtil.byteArrayToHexString(localPeerClientInfo.getDecKey()));
               // ThreadServer localThreadServer = new ThreadServer(socket);
                //executor.execute(localThreadServer);
                
                ThreadServer localThreadServer = new ThreadServer("127.0.0.1","15683",socket);
                localThreadServer.start();
                
            }

            System.out.println("testssss"+        server.toString());

        }

        // not reachable
        // server.close();
        // System.out.println("server.close()");
    }

}
