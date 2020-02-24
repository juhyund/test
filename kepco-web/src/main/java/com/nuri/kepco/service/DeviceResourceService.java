package com.nuri.kepco.service;

import java.util.Map;

import org.json.simple.JSONArray;

public interface DeviceResourceService extends GenericService {
	JSONArray getObjectModelList(Map<String, Object> param) throws Exception;
	
	JSONArray getResourceModelList(Map<String, Object> param) throws Exception;
	
}
