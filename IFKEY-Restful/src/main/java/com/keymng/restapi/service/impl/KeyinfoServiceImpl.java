package com.keymng.restapi.service.impl;

import java.util.List;

import javax.persistence.Column;
import javax.persistence.Id;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import com.keymng.restapi.model.Authorize;
import com.keymng.restapi.repository.KeyinfoRepository;
import com.keymng.restapi.service.KeyinfoService;
/**
 * 
 * @author : shinh5
 * @Date   : 2019. 3. 13.
 * @Version: 1.0
 */
@Component
public class KeyinfoServiceImpl implements KeyinfoService {

	@Autowired
	private KeyinfoRepository keyinfoRepository;
	
	private static final Logger logger = LoggerFactory.getLogger(KeyinfoServiceImpl.class);
			
	public int InsertAuthKey(String calling_id, String sys_title, String nas_ip, String nas_port, String fep_key, String nms_key){
		
		Authorize auth=new Authorize();
		long result=0;
		java.text.SimpleDateFormat format=new java.text.SimpleDateFormat("yyyyMMddHHmmss"); 
		String Now_dt=format.format(new java.util.Date());

		/**
		 * 1. Calling_id를  모뎀번호 뒷자리 8자리 형식에 맞게 가공한다.
		 */
		String sid = "";
		char[] CallIdArray = calling_id.toCharArray();
		for(int i = 1; i < calling_id.length(); i=i+3) sid = sid + CallIdArray[i];
		
		logger.info("sid: "+sid);
		if(sid.length() < 8 ) return -1;
		
		/**
		 * 2. System_title을 형식에 맞게 가공한다.
		 */
		sys_title = sys_title.split("@")[0];
		logger.info("sys_title: "+sys_title);
		/**
		 * 3. 최초 인증인지 여부를 확인한다 [0] : 최초인증 [1] : 재인증
		 */
		result = keyinfoRepository.isExistByCallind(sid);
		
		/**
		 * 4. tauthorize 테이블에 저장할 객체의 value를 setting한다. 
		 */
		auth.setCalling_id(sid);
		auth.setSys_title(sys_title);
		auth.setFep_key(fep_key);
		auth.setNms_Key(nms_key);
		auth.setNas_ip(nas_ip);
		auth.setNas_port(nas_port);
		auth.setModify_dt(Now_dt);
		
		/**
		 * 5. 재인증일 경우 기존의 create_dt 정보를 그대로 저장하고 최초인증일경우는 현재 시간으로 저장한다.
		 */
		if( result != 0 ){
			List<Authorize> auth_org = keyinfoRepository.getAuthByCallId(sid);
			auth.setCreate_dt(auth_org.get(0).getCreate_dt());
		} else auth.setCreate_dt(Now_dt); 

		
		try {
			keyinfoRepository.save(auth);
		} catch (Exception e) {
			logger.error("keyinforepository save=",e);
			return -1;
		}
		if(result==0) logger.info("======= Insert Auth Key Information. =======");
		else logger.info("======= Update Auth Key Information. =======");

		return (int) result;
	}

}
