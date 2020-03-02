package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.UserInfo;
import com.nuri.kepco.model.dao.UserInfoDAO;
import com.nuri.kepco.service.UserInfoService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class UserInfoServiceImpl implements UserInfoService {

	@Autowired
	UserInfoDAO userInfoDAO;


	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		UserInfo userInfo = new UserInfo();
		ConversionUtil.getModelByMap(userInfo, param);
		userInfo = this.userInfoDAO.selectOne(userInfo);

		return ConversionUtil.getJSONObjectByModel(userInfo);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		UserInfo userInfo = new UserInfo();
		ConversionUtil.getModelByMap(userInfo, param);
		List<UserInfo> list = this.userInfoDAO.selectList(userInfo);

		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		UserInfo userInfo = new UserInfo();
		ConversionUtil.getModelByMap(userInfo, param);
		return this.userInfoDAO.selectCount(userInfo);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		UserInfo userInfo = new UserInfo();
		ConversionUtil.getModelByMap(userInfo, param);

		return this.userInfoDAO.insert(userInfo);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		UserInfo userInfo = new UserInfo();
		ConversionUtil.getModelByMap(userInfo, param);

		return this.userInfoDAO.update(userInfo);
	}

	@Override
	public JSONObject getOneByUserId(String user_id) throws Exception {
		UserInfo userInfo = this.userInfoDAO.getOneByUserId(user_id);

		return ConversionUtil.getJSONObjectByModel(userInfo);
	}

}
