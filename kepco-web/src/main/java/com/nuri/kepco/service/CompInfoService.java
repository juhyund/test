package com.nuri.kepco.service;

import org.json.JSONObject;

public interface CompInfoService extends GenericService {

	JSONObject getCompInfoByUser(int user_seq) throws Exception;
}
