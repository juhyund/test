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
			if(validator(request, key)) {
				param.put(key, request.getParameter(key));	
			}
		}
		
		for(String key : commInt) {
			if(validator(request, key)) {
				param.put(key, Integer.parseInt(request.getParameter(key)));	
			}
		}
		
		return param;
	}
	
	public static void getCustomParam(HttpServletRequest request, String[] commStr, Map<String, Object> param) {
		for(String key : commStr) {
			if(validator(request, key)) {
				param.put(key, request.getParameter(key).trim());
			}
		}
	}
	
	private static boolean validator(HttpServletRequest request, String key) {
		if(request.getParameterMap().containsKey(key)) {
			if(request.getParameter(key) != null && !"".equals(request.getParameter(key))) {
				return true;
			}
		}
		
		return false;
	}
}
