package com.keymng.restapi.service;
/**
 * 
 * @author : shinh5
 * @Date   : 2019. 3. 13.
 * @Version: 1.0
 */
public interface KeyinfoService {
	/**
	 * 
	 * 1. 메소드명 : InsertAuthKey
	 * 2. 작성일   : 2019. 3. 13. 오후 3:41:41
	 * 3. 설명     : 수신받은 인증키를 TAuthorize 테이블에 저장한다.
	 */
	public int InsertAuthKey(String calling_id, String sys_title, String nas_ip, String nas_port, String fep_key, String nms_key);
	
	/**
	 * 1. 메소드명 : InsertAuthLog
	 * 2. 작성일   : 2019. 6. 17. 오전 10:35:41
	 * 3. 설명     : 인증 이력을 로그 테이블에 저장한다.
	 */
	public int InsertAuthLog(String calling_id, String sys_title, String nas_ip, String nas_port, String fep_key, String nms_key);
}
