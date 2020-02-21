package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.dao.DeviceInfoDAO;
import com.nuri.kepco.service.DeviceInfoService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class DeviceInfoServiceImpl implements DeviceInfoService {

	@Autowired
	DeviceInfoDAO deviceInfoDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);
		deviceInfo = this.deviceInfoDAO.selectOne(deviceInfo);

		return ConversionUtil.getJSONObjectByModel(deviceInfo);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);
		List<DeviceInfo> list = this.deviceInfoDAO.selectList(deviceInfo);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);

		return this.deviceInfoDAO.selectCount(deviceInfo);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);

		return this.deviceInfoDAO.insert(deviceInfo);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);

		return this.deviceInfoDAO.update(deviceInfo);
	}

	@Override
	public JSONObject selectByDeviceSerial(String device_serial) throws Exception {
		DeviceInfo deviceInfo = this.deviceInfoDAO.selectByDeviceSerial(device_serial);

		return ConversionUtil.getJSONObjectByModel(deviceInfo);
	}

	@Override
	public JSONArray getDeviceList(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);
		List<DeviceInfo> list = this.deviceInfoDAO.getDeviceList(deviceInfo);

		return ConversionUtil.getJSONArrayByModel(list, deviceInfo.getStart());
	}

	@Override
	public int getDeviceListCnt(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);

		return this.deviceInfoDAO.getDeviceListCnt(deviceInfo);
	}
	
}
