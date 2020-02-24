package com.nuri.kepco.service;

import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public interface MeterInfoService extends GenericService {
	
	JSONObject selectByDeviceSerial(String device_serial) throws Exception;
	
	JSONArray getMeterList(Map<String, Object> param) throws Exception;
	
	int getMeterListCnt(Map<String, Object> param) throws Exception;
	
	JSONObject getMeterDetailInfo(String meter_serial) throws Exception;
	
}