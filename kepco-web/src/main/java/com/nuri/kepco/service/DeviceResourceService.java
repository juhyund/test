package com.nuri.kepco.service;

import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public interface DeviceResourceService extends GenericService {
	JSONObject getResourceModelList(Map<String, Object> param) throws Exception;
	
}
