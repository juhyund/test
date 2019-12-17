package com.keymng.restapi.controller;

import org.jboss.logging.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import com.keymng.restapi.service.KeyinfoService;

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
		
		logger.info("======= Trying to Saving Auth Key =======");		
		res = keyinfoService.InsertAuthKey(calling_id, sys_title, nas_ip, nas_port, fep_key, nms_key);
		if( res < 0 ){
			logger.error("======= Failed to save auth key =======");
			return "Fail";
		}
		else if (res == 0 ) return "Insert New Auth-key Success [" +calling_id+ "]";
		return "Update Auth-key Success [" +calling_id+ "]";
	}
	
}
