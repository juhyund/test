package com.keymng.restapi.bean;

import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.client.RestTemplate;

@Configuration
public class RestTemplateBean {
  
  private RestTemplate restTemplate;
  
  public RestTemplateBean(RestTemplateBuilder builder) {
    this.restTemplate = builder.build();
  }

  @Bean
  public RestTemplate getRestTemplate() {
    return restTemplate;
  }
}