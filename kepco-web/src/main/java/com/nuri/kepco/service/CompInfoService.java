package com.nuri.kepco.service;

import org.json.simple.JSONObject;

public interface CompInfoService extends GenericService {

	JSONObject getCompInfoByUser(int user_seq) throws Exception;
}
