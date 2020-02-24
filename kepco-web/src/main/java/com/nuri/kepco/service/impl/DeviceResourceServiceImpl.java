package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

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
	public JSONArray getObjectModelList(Map<String, Object> param) throws Exception {
		DeviceResource deviceResource = new DeviceResource();
		ConversionUtil.getModelByMap(deviceResource, param);
		List<DeviceResource> list = this.deviceResourceDAO.getObjectModelList(deviceResource);

		return ConversionUtil.getJSONArrayByModel(list);
	}
}

