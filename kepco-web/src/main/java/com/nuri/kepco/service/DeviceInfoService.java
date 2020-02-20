package com.nuri.kepco.service;

import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;

public interface DeviceInfoService extends GenericService {
	
	JSONObject selectByDeviceSerial(String device_serial) throws Exception;
	
	JSONArray getDeviceList(Map<String, Object> param) throws Exception;
}
