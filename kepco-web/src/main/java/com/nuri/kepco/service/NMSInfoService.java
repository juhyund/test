package com.nuri.kepco.service;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import com.nuri.kepco.mongo.model.ConnectivityMonitor;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;

public interface NMSInfoService extends GenericService {
	
	JSONObject selectByDeviceSerial(String device_serial) throws Exception;
	
	JSONArray getNMSList(Map<String, Object> param) throws Exception;
	
	int getNMSListCnt(Map<String, Object> param) throws Exception;
	
	JSONObject getNMSDetail(String meter_serial) throws Exception;

	List<RamUsageMonitor> getRamUsageMonitor(Map<String, Object> param) throws Exception;

	List<CpuUsageMonitor> getCpuUsageMonitor(Map<String, Object> param) throws Exception;

	List<ConnectivityMonitor> getConnectivityMonitor(Map<String, Object> param) throws Exception;
	
}