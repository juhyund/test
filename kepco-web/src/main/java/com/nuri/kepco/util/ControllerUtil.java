package com.nuri.kepco.util;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ControllerUtil {

	static Logger logger = LoggerFactory.getLogger(ControllerUtil.class);
	
	static String[] commStr = { "searchfield", "searchquery", "sdate", "edate" };
	static String[] commInt = { "limit", "page"};
	
	public static Map<String, Object> getCommonParam(HttpServletRequest request) {
		Map<String, Object> param = new HashMap<String, Object>();
		
		for(String key : commStr) {
			if(request.getParameterMap().containsKey(key)) {
				param.put(key, request.getParameter(key));	
			}
		}
		
		for(String key : commInt) {
			if(request.getParameterMap().containsKey(key)) {
				param.put(key, Integer.parseInt(request.getParameter(key)));	
			}
		}
		
		return param;
	}
}
