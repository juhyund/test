package com.nuri.kepco.service;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import com.nuri.kepco.model.AllCode;
import com.nuri.kepco.service.AllCodeService;

public interface AllCodeService extends GenericService {
	
	List<Map<String, Object>> selectCombo(Map<String, Object> param) throws Exception;
}

