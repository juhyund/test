package com.nuri.kepco.service;

import org.json.simple.JSONObject;

public interface UserInfoService extends GenericService {
	
	JSONObject getOneByUserId(String user_id) throws Exception;
}
