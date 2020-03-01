package com.nuri.kepco.service;

import java.util.Map;

import org.json.simple.JSONArray;

public interface ObjectModelService extends GenericService {
	JSONArray selectObjectList(Map<String, Object> param) throws Exception;
}
