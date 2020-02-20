package com.nuri.kepco.service.impl;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.model.dao.MeterValueDAO;
import com.nuri.kepco.service.MeterValueService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class MeterValueServiceImpl implements MeterValueService {

	@Value("${file.download.dir:/files}")
	String fileDownloadDir;
	
	@Autowired
	MeterValueDAO meterValueDAO;

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
	public JSONArray getMeterValue(Map<String, Object> param) throws Exception {
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);
		List<MeterValue> list = this.meterValueDAO.getMeterValue(meterValue);

		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int getMeterValueCount(Map<String, Object> param) throws Exception {
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);

		return this.meterValueDAO.getMeterValueCount(meterValue);
	}

	@Override
	public JSONArray getMeterValueDetail(Map<String, Object> param) throws Exception {
		List<Map<String, Object>> channels = (List<Map<String, Object>>) param.get("channelList");
		MeterValue meterValue = new MeterValue();
		meterValue.setChannelList(channels);
		
		List<MeterValue> list = this.meterValueDAO.selectList(meterValue);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public JSONArray selectMeterInfo(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public JSONArray selectMeterChannel(Map<String, Object> param) throws Exception {
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);
		//meterValueDAO.sel
		List<MeterValue> list = new ArrayList<MeterValue>();
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public Map<String, String> excelMeterValue(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Map<String, String> excelMeterValueDetail(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}
	
	

}
