package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.CompInfo;
import com.nuri.kepco.model.dao.CompInfoDAO;
import com.nuri.kepco.service.CompInfoService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class CompInfoServiceImpl implements CompInfoService {

	@Autowired
	CompInfoDAO compInfoDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		CompInfo compInfo = new CompInfo();
		ConversionUtil.getModelByMap(compInfo, param);
		compInfo = this.compInfoDAO.selectOne(compInfo);

		return ConversionUtil.getJSONObjectByModel(compInfo);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		CompInfo compInfo = new CompInfo();
		ConversionUtil.getModelByMap(compInfo, param);
		List<CompInfo> list = this.compInfoDAO.selectList(compInfo);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		CompInfo compInfo = new CompInfo();
		ConversionUtil.getModelByMap(compInfo, param);

		return this.compInfoDAO.selectCount(compInfo);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		CompInfo compInfo = new CompInfo();
		ConversionUtil.getModelByMap(compInfo, param);

		return this.compInfoDAO.insert(compInfo);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		CompInfo compInfo = new CompInfo();
		ConversionUtil.getModelByMap(compInfo, param);

		return this.compInfoDAO.update(compInfo);
	}

	@Override
	public JSONObject getCompInfoByUser(int user_seq) throws Exception {
		CompInfo compInfo = this.compInfoDAO.getCompInfoByUser(user_seq);

		return ConversionUtil.getJSONObjectByModel(compInfo);
	}

}
