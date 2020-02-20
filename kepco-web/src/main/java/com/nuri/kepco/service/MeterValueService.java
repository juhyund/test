package com.nuri.kepco.service;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public interface MeterValueService extends GenericService {
	
	JSONArray getMeterValue(Map<String, Object> param) throws Exception;
	
	int getMeterValueCount(Map<String, Object> param) throws Exception;

	JSONArray getMeterValueDetail(Map<String, Object> param) throws Exception;

	JSONArray selectMeterInfo(Map<String, Object> param) throws Exception;

	JSONArray selectMeterChannel(Map<String, Object> param) throws Exception;
	
	public Map<String, String> excelMeterValue(Map<String, Object> param) throws Exception;
	
	public Map<String, String> excelMeterValueDetail(Map<String, Object> param) throws Exception;
}
