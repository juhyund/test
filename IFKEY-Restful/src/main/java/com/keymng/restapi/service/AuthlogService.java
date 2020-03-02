package com.keymng.restapi.service;
/**
 * 
 * @author : shinh5
 * @Date   : 2019. 3. 13.
 * @Version: 1.0
 */
public interface AuthlogService {
	
	/**
	 * 1. 메소드명 : InsertAuthLog
	 * 2. 작성일   : 2019. 6. 17. 오전 10:35:41
	 * 3. 설명     : 인증 이력을 로그 테이블에 저장한다.
	 */
	public int InsertAuthLog(String sys_title,String device_id, String log_cd, String receive_dt);
}
