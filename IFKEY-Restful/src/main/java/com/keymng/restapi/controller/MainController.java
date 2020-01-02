package com.keymng.restapi.controller;

import org.jboss.logging.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import org.springframework.web.util.UriComponentsBuilder;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpEntity;
import org.springframework.http.ResponseEntity;
import org.springframework.web.client.RestTemplate;
import org.springframework.http.converter.HttpMessageConverter;
import org.springframework.http.converter.FormHttpMessageConverter;
import org.springframework.http.converter.StringHttpMessageConverter;
import org.springframework.util.MultiValueMap;
import org.springframework.util.LinkedMultiValueMap;

import com.keymng.restapi.service.KeyinfoService;

import org.springframework.http.HttpMethod;
import org.springframework.http.MediaType;
import java.util.ArrayList;
import java.util.Map;
import java.util.List;

/**
 * 
 * @author : shinh5
 * @Date   : 2019. 3. 13.
 * @Version: 1.0
 */
@RestController
@RequestMapping(value="/Authorize")
public class MainController {
    @Autowired
    KeyinfoService keyinfoService;
    		
	@Autowired
    RestTemplate restTemplate;
	
	@Value("${redisurl}") 
	String uri;
    
    private static Logger logger = Logger.getLogger(MainController.class);
    /**
     * 
     * 1. 메소드명 : SampleTest
     * 2. 작성일   : 2019. 3. 13. 오후 3:50:22
     * 3. 설명     : Controller 테스트
     */
	@RequestMapping(value="/Test", method = RequestMethod.GET)
	@ResponseStatus(value = HttpStatus.OK)
	public String SampleTest(){
		return "SampleTest";
	}
	
	/**
	 * 
	 * 1. 메소드명 : SavingAuthKey
	 * 2. 작성일   : 2019. 3. 13. 오후 3:50:40
	 * 3. 설명     : Client의 GET방식 /SavingAuthkey Request를 처리 
	 */
	@RequestMapping(value="/SavingAuthKey", method = RequestMethod.GET)
	@ResponseStatus(value = HttpStatus.OK)
	public String SavingAuthKey(@RequestParam String calling_id, @RequestParam String sys_title,
			@RequestParam String nas_ip, @RequestParam String nas_port, 
			@RequestParam String fep_key, @RequestParam String nms_key){
		
		int res = 0;
		
		logger.info("======= Trying to send Auth Key ro REDIS =======");
		//callSendPSKtoRedisRestAPI(sys_title, fep_key);
		callSendPSKtoRedisRestAPI("yoon", "1234");
		
		logger.info("======= Trying to Saving Auth Key =======");		
		res = keyinfoService.InsertAuthKey(calling_id, sys_title, nas_ip, nas_port, fep_key, nms_key);
		if( res < 0 ){
			logger.error("======= Failed to save auth key =======");
			return "Fail";
		}
		else if (res == 0 ) return "Insert New Auth-key Success [" +calling_id+ "]";
		
		return "Update Auth-key Success [" +calling_id+ "]";
	}
	
	
	public void callSendPSKtoRedisRestAPI(String endPoint, String psk){		
		
		//http://172.16.10.162:18086/security/pskSecurity?ep=yoon&psk=1234
		//String uri = "http://172.16.10.162:18086/security/pskSecurity/";
		// RestTemplate 에 MessageConverter 세팅
        List<HttpMessageConverter<?>> converters = new ArrayList<HttpMessageConverter<?>>();
        converters.add(new FormHttpMessageConverter());
        converters.add(new StringHttpMessageConverter());
 
        HttpHeaders headers = new HttpHeaders();
		headers.setContentType(MediaType.APPLICATION_JSON);
		HttpEntity<String> entity = new HttpEntity<>(headers);

        restTemplate.setMessageConverters(converters);
 
        // parameter 세팅
        //MultiValueMap<String, String> requestParam = new LinkedMultiValueMap<String, String>();
        //requestParam.add("ep", endPoint);
		//requestParam.add("psk", psk);
		
		 // Add query parameter
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(uri)
		.queryParam("ep",endPoint)
		.queryParam("psk", psk);

        // REST API 호출
        //restTemplate.put(redisuri, requestParam);
		ResponseEntity<String> responseEntity 
		= restTemplate.exchange(builder.toUriString(), HttpMethod.PUT, entity, String.class);
        logger.info("REST API["+uri+"] called, Response["+responseEntity.getBody()+"]");
	}	
}
