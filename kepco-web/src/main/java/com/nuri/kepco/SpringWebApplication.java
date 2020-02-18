package com.nuri.kepco;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@MapperScan(basePackages="com.nuri.kepco.model.dao") // 이 패키지 하위에 존재하는 model들을 bean으로 등록함.
@ComponentScan({"com.nuri.kepco"})
public class SpringWebApplication extends SpringBootServletInitializer {
	
	@Override
	protected SpringApplicationBuilder configure(SpringApplicationBuilder builder) {
		return builder.sources(SpringWebApplication.class);
	}

	public static void main(String[] args) {
		SpringApplication.run(SpringWebApplication.class, args);
		System.out.println("start~~");
	}
}
