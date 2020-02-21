package com.nuri.kepco.util;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.nuri.kepco.model.common.OrderByMap;

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
		
		if(param.containsKey("sort") && param.containsKey("dir")) {
			try {
				List<OrderByMap> orderByList = new ArrayList<OrderByMap>();
				orderByList.add(new OrderByMap((String)param.get("sort"), (String)param.get("dir")));
				Method method;
				method = scls.getMethod("setOrderByMap", List.class);
				method.invoke(o, orderByList);
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
		return getJSONArrayByModel(list, 0);
	}
	
	public static JSONArray getJSONArrayByModel(List<?> list, int start) {
		JSONArray jsonarr = new JSONArray();
		int idx = (start + 1);
		try {
			for(Object o : list) {
				JSONObject json = getJSONObjectByModel(o);
				json.put("no", idx++);
				jsonarr.add(json);
			}
		} catch (Exception e) {
			logger.error(e.toString(), e);
		}
		
		return jsonarr;
	}
}
