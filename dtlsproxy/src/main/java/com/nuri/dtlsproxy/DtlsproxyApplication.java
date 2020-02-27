package com.nuri.dtlsproxy;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;

@SpringBootApplication
public class DtlsproxyApplication {

	public static void main(String[] args) {
		//SpringApplication.run(DtlsproxyApplication.class, args);
	
		ApplicationContext app = SpringApplication.run(DtlsproxyApplication.class, args);
		DtlsProxyServer server = app.getBean(DtlsProxyServer.class);
		server.start(args);			
		System.out.println("DTLS+PSK PROXY START!!");
	}

}
