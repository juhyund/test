package com.nuri.kepco.service.impl;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.nuri.kepco.model.DeviceResource;
import com.nuri.kepco.model.dao.DeviceResourceDAO;
import com.nuri.kepco.service.DeviceResourceService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class DeviceResourceServiceImpl implements DeviceResourceService {

	@Autowired
	DeviceResourceDAO deviceResourceDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		DeviceResource deviceResource = new DeviceResource();
		ConversionUtil.getModelByMap(deviceResource, param);
		deviceResource = this.deviceResourceDAO.selectOne(deviceResource);

		return ConversionUtil.getJSONObjectByModel(deviceResource);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		DeviceResource deviceResource = new DeviceResource();
		ConversionUtil.getModelByMap(deviceResource, param);
		List<DeviceResource> list = this.deviceResourceDAO.selectList(deviceResource);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		DeviceResource deviceResource = new DeviceResource();
		ConversionUtil.getModelByMap(deviceResource, param);

		return this.deviceResourceDAO.selectCount(deviceResource);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		DeviceResource deviceResource = new DeviceResource();
		ConversionUtil.getModelByMap(deviceResource, param);

		return this.deviceResourceDAO.insert(deviceResource);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		DeviceResource deviceResource = new DeviceResource();
		ConversionUtil.getModelByMap(deviceResource, param);

		return this.deviceResourceDAO.update(deviceResource);
	}

	@Override
	public JSONObject getResourceModelList(Map<String, Object> param) throws Exception {
		DeviceResource deviceResource = new DeviceResource();
		ConversionUtil.getModelByMap(deviceResource, param);
		List<DeviceResource> list = this.deviceResourceDAO.getResourceModelList(deviceResource);

		Map<String, List<DeviceResource>> map = new LinkedHashMap<String, List<DeviceResource>>();
		for(DeviceResource dr : list) {
			String key = dr.getObject_instance_id();
			if(key == null) {
				key = "0";
				dr.setObject_instance_id("0");
			}
			if(map.containsKey(key)) {
				map.get(key).add(dr);
			} else {
				List<DeviceResource> l = new ArrayList<DeviceResource>();
				l.add(dr);
				map.put(key, l);
			}
		}
		
		JSONObject result = new JSONObject();
		for(String key : map.keySet()) {
			
			
			for(Object o : map.get(key)) {
				Gson gson = new GsonBuilder().serializeNulls().create();
				String str = gson.toJson(o).toString();
				
				JSONParser parser = new JSONParser();
				Object obj = null;
				try {
					obj = parser.parse(str);	
				}catch (Exception e) {
					System.out.println("o: " + o );
					System.out.println(str);
					//e.printStackTrace();
				}
			}
			
			result.put(key, ConversionUtil.getJSONArrayByModel(map.get(key)));
		}

		return result;
	}

	@Override
	public JSONArray getMeterResourceList(Map<String, Object> param) throws Exception {
		DeviceResource deviceResource = new DeviceResource();
		ConversionUtil.getModelByMap(deviceResource, param);
		List<DeviceResource> list = this.deviceResourceDAO.getMeterResourceList(deviceResource);

		return ConversionUtil.getJSONArrayByModel(list);
	}
	
}

