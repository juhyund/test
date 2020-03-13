package com.nuri.kepco.service;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import com.nuri.kepco.model.AllCode;
import com.nuri.kepco.service.ObisCodeService;

public interface ObisCodeService extends GenericService {

	JSONArray selectObisList(Map<String, Object> param) throws Exception;
	
	JSONArray selectObisList2(Map<String, Object> param) throws Exception;
	
}

