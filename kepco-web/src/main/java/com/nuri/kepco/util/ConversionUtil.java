package com.nuri.kepco.util;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class ConversionUtil {

	static Logger logger = LoggerFactory.getLogger(ConversionUtil.class);
	
	public static void getModelByMap(Object o, Map<String, Object> param) {
		Class<?> scls = o.getClass().getSuperclass();
		for (Field f : scls.getDeclaredFields()) {
			try {
				if(param.containsKey(f.getName())) {
					String name = "set" + f.getName().substring(0, 1).toUpperCase() + f.getName().substring(1);
					Method method = scls.getMethod(name, f.getType());
					method.invoke(o, param.get(f.getName()));
				}
			} catch (Exception e) {
				logger.error(e.toString(), e);
			}
		}
		
		Class<?> cls = o.getClass();
		for (Field f : cls.getDeclaredFields()) {
			try {
				if(param.containsKey(f.getName())) {
					Field field = cls.getDeclaredField(f.getName());
					field.setAccessible(true);
					field.set(o, param.get(f.getName()));	
				}
			} catch (Exception e) {
				logger.error(e.toString(), e);
			}
		}
	}

	public static JSONObject getJSONObjectByModel(Object o) {
		JSONObject json = null;
		try {
			Gson gson = new GsonBuilder().serializeNulls().create();
			String str = gson.toJson(o).toString().replaceAll("null", "\"\"");
			JSONParser parser = new JSONParser();
			Object obj = parser.parse(str);
			json = (JSONObject) obj;
			
		} catch (Exception e) {
			logger.error(e.toString(), e);
		}
		
		return json;
	}
	
	public static JSONArray getJSONArrayByModel(List<?> list) {
		JSONArray jsonarr = new JSONArray();
		try {
			for(Object o : list) {
				jsonarr.add(getJSONObjectByModel(o));
			}
		} catch (Exception e) {
			logger.error(e.toString(), e);
		}
		
		return jsonarr;
	}
}
