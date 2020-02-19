package com.nuri.kepco.service;

import org.json.JSONObject;

public interface UserInfoService extends GenericService {
	
	JSONObject getOneByUserId(String user_id) throws Exception;
}
