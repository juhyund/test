package com.nuri.kepco.service;

import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public interface DeviceResourceService extends GenericService {
	JSONArray getObjectModelList(Map<String, Object> param) throws Exception;
	
	JSONObject getResourceModelList(Map<String, Object> param) throws Exception;
	
}
