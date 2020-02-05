package com.nuri.kepco.fep;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@ComponentScan({"com.nuri.emi"})
public class SpringFepApplication {
	
	public static void main(String[] args) {
		SpringApplication.run(SpringFepApplication.class, args);
		System.out.println("FEP START!!");
	}
}