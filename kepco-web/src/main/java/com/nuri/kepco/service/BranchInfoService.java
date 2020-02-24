package com.nuri.kepco.service;

import org.json.simple.JSONArray;

public interface BranchInfoService extends GenericService {
	JSONArray selectParent() throws Exception;
	
}