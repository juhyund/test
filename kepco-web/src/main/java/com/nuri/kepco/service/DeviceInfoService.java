package com.nuri.kepco.service;

import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public interface DeviceInfoService extends GenericService {
	
	JSONObject selectByDeviceSerial(String device_serial) throws Exception;
	
	int getDeviceListCnt(Map<String, Object> param) throws Exception;
	
	JSONArray getDeviceList(Map<String, Object> param) throws Exception;
}
