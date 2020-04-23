package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.DevicePowerLog;
import com.nuri.kepco.model.dao.DevicePowerLogDAO;
import com.nuri.kepco.service.DevicePowerLogService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class DevicePowerLogServiceImpl implements DevicePowerLogService {

	@Autowired
	DevicePowerLogDAO devicePowerLogDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);
		devicePowerLog = this.devicePowerLogDAO.selectOne(devicePowerLog);

		return ConversionUtil.getJSONObjectByModel(devicePowerLog);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);
		List<DevicePowerLog> list = this.devicePowerLogDAO.selectList(devicePowerLog);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);

		return this.devicePowerLogDAO.selectCount(devicePowerLog);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);

		return this.devicePowerLogDAO.insert(devicePowerLog);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param, false);

		return this.devicePowerLogDAO.update(devicePowerLog);
	}

}

