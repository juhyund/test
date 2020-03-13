package com.nuri.kepco.service;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import com.nuri.kepco.model.MeterBilling;




public interface MeterBillingService extends GenericService {

	Map<String, String> excelMeterBilling(Map<String, Object> param) throws Exception;
	
	JSONArray selectListDetail(Map<String, Object> param) throws Exception;
}

