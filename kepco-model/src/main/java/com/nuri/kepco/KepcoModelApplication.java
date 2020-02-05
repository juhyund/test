package com.nuri.kepco;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@ComponentScan({"com.nuri.kepco"})
public class KepcoModelApplication {

	public static void main(String[] args) {
		SpringApplication.run(KepcoModelApplication.class, args);
	}

}
