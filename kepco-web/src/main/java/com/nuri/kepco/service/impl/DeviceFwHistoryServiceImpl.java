package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.DeviceFwHistory;
import com.nuri.kepco.model.dao.DeviceFwHistoryDAO;
import com.nuri.kepco.service.DeviceFwHistoryService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class DeviceFwHistoryServiceImpl implements DeviceFwHistoryService {

	@Autowired
	DeviceFwHistoryDAO deviceFwHistoryDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		DeviceFwHistory deviceFwHistory = new DeviceFwHistory();
		ConversionUtil.getModelByMap(deviceFwHistory, param);
		deviceFwHistory = this.deviceFwHistoryDAO.selectOne(deviceFwHistory);

		return ConversionUtil.getJSONObjectByModel(deviceFwHistory);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		DeviceFwHistory deviceFwHistory = new DeviceFwHistory();
		ConversionUtil.getModelByMap(deviceFwHistory, param);
		List<DeviceFwHistory> list = this.deviceFwHistoryDAO.selectList(deviceFwHistory);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		DeviceFwHistory deviceFwHistory = new DeviceFwHistory();
		ConversionUtil.getModelByMap(deviceFwHistory, param);

		return this.deviceFwHistoryDAO.selectCount(deviceFwHistory);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		DeviceFwHistory deviceFwHistory = new DeviceFwHistory();
		ConversionUtil.getModelByMap(deviceFwHistory, param);

		return this.deviceFwHistoryDAO.insert(deviceFwHistory);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		DeviceFwHistory deviceFwHistory = new DeviceFwHistory();
		ConversionUtil.getModelByMap(deviceFwHistory, param);

		return this.deviceFwHistoryDAO.update(deviceFwHistory);
	}

}
