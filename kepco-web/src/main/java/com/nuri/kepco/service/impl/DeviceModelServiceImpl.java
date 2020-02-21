package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.DeviceModel;
import com.nuri.kepco.model.dao.DeviceModelDAO;
import com.nuri.kepco.service.DeviceModelService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class DeviceModelServiceImpl implements DeviceModelService {

	@Autowired
	DeviceModelDAO deviceModelDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		DeviceModel deviceModel = new DeviceModel();
		ConversionUtil.getModelByMap(deviceModel, param);
		deviceModel = this.deviceModelDAO.selectOne(deviceModel);

		return ConversionUtil.getJSONObjectByModel(deviceModel);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		DeviceModel deviceModel = new DeviceModel();
		ConversionUtil.getModelByMap(deviceModel, param);
		List<DeviceModel> list = this.deviceModelDAO.selectList(deviceModel);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		DeviceModel deviceModel = new DeviceModel();
		ConversionUtil.getModelByMap(deviceModel, param);

		return this.deviceModelDAO.selectCount(deviceModel);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		DeviceModel deviceModel = new DeviceModel();
		ConversionUtil.getModelByMap(deviceModel, param);

		return this.deviceModelDAO.insert(deviceModel);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		DeviceModel deviceModel = new DeviceModel();
		ConversionUtil.getModelByMap(deviceModel, param);

		return this.deviceModelDAO.update(deviceModel);
	}

}
