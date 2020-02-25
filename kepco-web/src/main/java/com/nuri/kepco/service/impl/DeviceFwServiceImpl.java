package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.DeviceFw;
import com.nuri.kepco.model.dao.DeviceFwDAO;
import com.nuri.kepco.service.DeviceFwService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class DeviceFwServiceImpl implements DeviceFwService {

	@Autowired
	DeviceFwDAO deviceFwDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		DeviceFw deviceFw = new DeviceFw();
		ConversionUtil.getModelByMap(deviceFw, param);
		deviceFw = this.deviceFwDAO.selectOne(deviceFw);

		return ConversionUtil.getJSONObjectByModel(deviceFw);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		DeviceFw deviceFw = new DeviceFw();
		ConversionUtil.getModelByMap(deviceFw, param);
		List<DeviceFw> list = this.deviceFwDAO.selectList(deviceFw);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		DeviceFw deviceFw = new DeviceFw();
		ConversionUtil.getModelByMap(deviceFw, param);

		return this.deviceFwDAO.selectCount(deviceFw);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		DeviceFw deviceFw = new DeviceFw();
		ConversionUtil.getModelByMap(deviceFw, param);

		return this.deviceFwDAO.insert(deviceFw);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		DeviceFw deviceFw = new DeviceFw();
		ConversionUtil.getModelByMap(deviceFw, param);

		return this.deviceFwDAO.update(deviceFw);
	}

}
