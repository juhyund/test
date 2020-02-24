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
				String val = request.getParameter(key);
				if(key.indexOf("date") > 0) {
					val = val.replace("/", "");
				}
				param.put(key, val);	
			}
		}
		
		for(String key : commInt) {
			if(validator(request, key)) {
				String val = request.getParameter(key);
				param.put(key, Integer.parseInt(val.trim()));	
			}
		}
		
		return param;
	}
	
	public static void getCustomParam(HttpServletRequest request, String[] commStr, Map<String, Object> param) {
		for(String key : commStr) {
			if(validator(request, key)) {
				String val = request.getParameter(key);
				if(key.indexOf("date") > 0) {
					val = val.replace("/", "");
				}
				param.put(key, val);
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

