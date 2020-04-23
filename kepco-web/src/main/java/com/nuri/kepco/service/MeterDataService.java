package com.nuri.kepco.service;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import com.nuri.kepco.model.MeterData;

public interface MeterDataService extends GenericService {
	
	Map<String, String> excelMeterData(Map<String, Object> param) throws Exception;
	
	JSONArray selectDetail(Map<String, Object> param) throws Exception;
}

