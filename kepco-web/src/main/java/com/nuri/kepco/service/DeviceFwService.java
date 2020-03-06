package com.nuri.kepco.service;

import org.json.simple.JSONObject;

public interface DeviceFwService extends GenericService {
	
	JSONObject selectOneByPackageUri(String param) throws Exception;
	
}
