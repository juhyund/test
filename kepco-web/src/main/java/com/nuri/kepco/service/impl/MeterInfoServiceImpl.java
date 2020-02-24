package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.model.dao.MeterInfoDAO;
import com.nuri.kepco.service.MeterInfoService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class MeterInfoServiceImpl implements MeterInfoService {

	@Autowired
	MeterInfoDAO meterInfoDAO;

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public JSONObject selectByDeviceSerial(String device_serial) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public JSONArray getMeterList(Map<String, Object> param) throws Exception {
		MeterInfo meterInfo = new MeterInfo();
		ConversionUtil.getModelByMap(meterInfo, param);
		List<MeterInfo> list = this.meterInfoDAO.getMeterList(meterInfo);

		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int getMeterListCnt(Map<String, Object> param) throws Exception {
		MeterInfo meterInfo = new MeterInfo();
		ConversionUtil.getModelByMap(meterInfo, param);

		return this.meterInfoDAO.getMeterListCnt(meterInfo);
	}

	@Override
	public JSONObject getMeterDetailInfo(String meter_serial) throws Exception {
		MeterInfo meterInfo = meterInfoDAO.getMeterDetailInfo(meter_serial);
		return ConversionUtil.getJSONObjectByModel(meterInfo);
	}
}
