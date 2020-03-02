package com.keymng.restapi.service.impl;

import java.util.List;

import javax.persistence.Column;
import javax.persistence.Id;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import com.keymng.restapi.model.Authorize;
import com.keymng.restapi.model.AuthorizeLog;
import com.keymng.restapi.repository.AuthlogRepository;
import com.keymng.restapi.service.AuthlogService;
/**
 * 
 * @author : shinh5
 * @Date   : 2019. 3. 13.
 * @Version: 1.0
 */
@Component
public class AuthlogServiceImpl implements AuthlogService {
	
	@Autowired
	private AuthlogRepository authlogRepository;
	
	private static final Logger logger = LoggerFactory.getLogger(AuthlogServiceImpl.class);		


	public int InsertAuthLog(String sys_title,
			String device_id, String log_cd, String receive_dt) {
		
		
		AuthorizeLog authlog = new AuthorizeLog();
		long result=0;
		java.text.SimpleDateFormat format=new java.text.SimpleDateFormat("yyyyMMddHHmmss"); 
		String now_dt=format.format(new java.util.Date());
		
		
		/**
		 * 1. System_title을 형식에 맞게 가공한다.
		 */
		sys_title = sys_title.split("@")[0];
		logger.info("sys_title: "+sys_title);
		
		authlog.setCalling_id(now_dt+sys_title);
		authlog.setDevice_id(device_id);
		authlog.setLog_cd(log_cd);
		authlog.setReceive_dt(receive_dt);
		authlog.setSys_title(sys_title);
		authlog.setWrite_dt(now_dt);		

		try {
			authlogRepository.save(authlog);
		} catch (Exception e) {
			logger.error("authlogresitory save=",e);
			return -1;
		}
		if(result==0) logger.info("======= Insert Auth Key Information. =======");
		else logger.info("======= Update Auth Key Information. =======");

		return (int) result;
	}
}
