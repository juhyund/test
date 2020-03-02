package com.nuri.kepco.service;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import com.nuri.kepco.model.DeviceResource;

public interface DeviceResourceService extends GenericService {
	JSONArray getObjectModelList(Map<String, Object> param) throws Exception;
	
	JSONObject getResourceModelList(Map<String, Object> param) throws Exception;
	
	JSONArray getMeterResourceList(Map<String, Object> param) throws Exception;
	
}
