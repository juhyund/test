package com.nuri.kepco.service;

import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public interface OperationLogService extends GenericService {
	
	JSONObject selectByDeviceSerial(String device_serial) throws Exception;
	
	JSONArray getOperationLogList(Map<String, Object> param) throws Exception;
	
	int getOperationLogListCnt(Map<String, Object> param) throws Exception;

	JSONObject getOperationLogDetail(Map<String, Object> param) throws Exception;
	
	JSONArray getExcuteRate() throws Exception;

	Map<String, String> excelMeterList(Map<String, Object> param) throws Exception;
	
}