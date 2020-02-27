package com.nuri.dtlsproxy;

import com.penta.ptls.Constant;
import com.penta.ptls.PeerClientInfo;
import com.penta.ptls.PtlsSocket;
import com.penta.ptls.Util;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;

public class ThreadServer extends Thread {
	public static boolean USE_NONBLOCK = true;
	private PtlsSocket socket;
	private String clientIP;
	private int clientPort;
	private String relayServer;
	private String relayPort;

	public ThreadServer(String relayServer, String relayPort, PtlsSocket paramPtlsSocket) {
		this.socket = paramPtlsSocket;
		PeerClientInfo localPeerClientInfo = paramPtlsSocket.getPeerClientInfo(true);
		this.clientIP = localPeerClientInfo.getClientIp();
		this.clientPort = localPeerClientInfo.getClientPort();
		this.relayServer = relayServer;
		this.relayPort = relayPort;
	}

	private void printMessage(String paramString) {
		System.out.println("[" + this.clientIP + ":" + this.clientPort + "] : " + paramString);
	}

	public void run() {
		int i = 0;
		int ret = 0;
		if (this.socket == null) {
			return;
		} else {
			System.out.println("clientIp: " + clientIP);
			System.out.println("clientPort: " + clientPort);
		}

		byte[] buf = new byte[1024];
		int readSize = 0;
		
		DatagramSocket coapServer = null;
		try {
			coapServer = new DatagramSocket();
		} catch (SocketException e1) {
			// TODO Auto-generated catch block
			System.err.println(e1);
			e1.printStackTrace();
		}
		
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
			String readString = "";
			try {
				readString = new String(buf, 0, readSize, "UTF-8");
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("read : " + readString);

			InetAddress address = null;
			try {
				address = InetAddress.getByName(relayServer);
			} catch (UnknownHostException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			int lesport = Integer.parseInt(relayPort);
			
			coapServer.connect(address, lesport);
			try {
				Thread.sleep(300);
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			if(coapServer.isConnected()) {
				DatagramPacket request = new DatagramPacket(buf, readSize);
				try {
					coapServer.send(request);
				} catch (IOException e) {
					System.err.println(e);
					e.printStackTrace();
				}
			}else {
				System.err.println("write error: " + address + ":"+lesport);
			}

			
			
			
			/*
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
			}*/
			
			
			
			
			System.out.println("write : " + readString);
		}
	}
}
