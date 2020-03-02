package com.nuri.kepco.util;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.nuri.kepco.model.common.OrderByMap;

public class ConversionUtil {

	public static void getModelByMap(Object o, Map<String, Object> param) throws Exception {
		Class<?> scls = o.getClass().getSuperclass();
		for (Field f : scls.getDeclaredFields()) {
			if(param.containsKey(f.getName())) {
				String name = "set" + f.getName().substring(0, 1).toUpperCase() + f.getName().substring(1);
				Method method = scls.getMethod(name, f.getType());
				method.invoke(o, param.get(f.getName()));
			}
		}
		
		if(param.containsKey("sort") && param.containsKey("dir")) {
			List<OrderByMap> orderByList = new ArrayList<OrderByMap>();
			orderByList.add(new OrderByMap((String)param.get("sort"), (String)param.get("dir")));
			Method method;
			method = scls.getMethod("setOrderByMap", List.class);
			method.invoke(o, orderByList);
		}
		
		
		Class<?> cls = o.getClass();
		for (Field f : cls.getDeclaredFields()) {
			if(param.containsKey(f.getName())) {
				Field field = cls.getDeclaredField(f.getName());
				field.setAccessible(true);
				field.set(o, param.get(f.getName()));	
			}
		}
	}

	public static JSONObject getJSONObjectByModel(Object o) throws Exception {
		JSONObject json = null;
		if(o == null) {
			return new JSONObject();
		}

		Gson gson = new GsonBuilder().serializeNulls().create();
		String str = gson.toJson(o).toString().replaceAll("null", "\"\"");
		JSONParser parser = new JSONParser();
		Object obj = parser.parse(str);
		json = (JSONObject) obj;
		
		return json;
	}
	
	public static JSONArray getJSONArrayByModel(List<?> list) throws Exception  {
		return getJSONArrayByModel(list, 0);
	}
	
	public static JSONArray getJSONArrayByModel(List<?> list, int start) throws Exception  {
		JSONArray jsonarr = new JSONArray();
		int idx = (start + 1);
		for(Object o : list) {
			JSONObject json = getJSONObjectByModel(o);
			json.put("no", idx++);
			jsonarr.add(json);
		}
		
		return jsonarr;
	}
}

