package com.keymng.restapi;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

/**
 * 
 * @author : shinh5
 * @Date   : 2019. 3. 13.
 * @Version: 1.0
 */
@Configuration
@EnableAutoConfiguration
@ComponentScan
public class RestApiApplication {

	/**
	 * 
	 * 1. 메소드명 : main
	 * 2. 작성일   : 2019. 3. 13. 오후 3:51:58
	 * 3. 설명     : Spring-boot Start
	 */
	public static void main(String[] args) {
		SpringApplication.run(RestApiApplication.class, args);
	}
	
}
