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

import com.nuri.kepco.model.MeterBilling;
import com.nuri.kepco.model.dao.MeterBillingDAO;
import com.nuri.kepco.service.MeterBillingService;
import com.nuri.kepco.util.ConversionUtil;


@Service
@Transactional
public class MeterBillingServiceImpl implements MeterBillingService {

	@Value("${file.download.dir:/files}")
	String fileDownloadDir;
	
	@Autowired
	MeterBillingDAO meterBillingDAO;


	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		MeterBilling meterBilling = new MeterBilling();
		ConversionUtil.getModelByMap(meterBilling, param);

		return this.meterBillingDAO.selectCount(meterBilling);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		MeterBilling meterBilling = new MeterBilling();
		ConversionUtil.getModelByMap(meterBilling, param);
		List<MeterBilling> list = this.meterBillingDAO.selectList(meterBilling);

		return ConversionUtil.getJSONArrayByModel(list);
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
}