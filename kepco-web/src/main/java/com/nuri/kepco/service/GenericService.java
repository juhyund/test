package com.nuri.kepco.service;

import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public interface GenericService {

	int selectCount(Map<String, Object> param) throws Exception;
	
	JSONArray selectList(Map<String, Object> param) throws Exception;
	
	JSONObject selectOne(Map<String, Object> param) throws Exception;

	int insert(Map<String, Object> param) throws Exception;

	int update(Map<String, Object> param) throws Exception;
}