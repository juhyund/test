package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.BranchInfo;
import com.nuri.kepco.model.dao.BranchInfoDAO;
import com.nuri.kepco.service.BranchInfoService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class BranchInfoServiceImpl implements BranchInfoService {

	@Autowired
	BranchInfoDAO branchInfoDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		BranchInfo branchInfo = new BranchInfo();
		ConversionUtil.getModelByMap(branchInfo, param);
		branchInfo = this.branchInfoDAO.selectOne(branchInfo);

		return ConversionUtil.getJSONObjectByModel(branchInfo);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		BranchInfo branchInfo = new BranchInfo();
		ConversionUtil.getModelByMap(branchInfo, param);
		List<BranchInfo> list = this.branchInfoDAO.selectList(branchInfo);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		BranchInfo branchInfo = new BranchInfo();
		ConversionUtil.getModelByMap(branchInfo, param);

		return this.branchInfoDAO.selectCount(branchInfo);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		BranchInfo branchInfo = new BranchInfo();
		ConversionUtil.getModelByMap(branchInfo, param);

		return this.branchInfoDAO.insert(branchInfo);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		BranchInfo branchInfo = new BranchInfo();
		ConversionUtil.getModelByMap(branchInfo, param);

		return this.branchInfoDAO.update(branchInfo);
	}

}
