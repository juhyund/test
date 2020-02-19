package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.dao.UserGroupDAO;
import com.nuri.kepco.service.UserGroupService;
import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.model.GroupInfo;
import com.nuri.kepco.model.UserGroup;

@Service
@Transactional
public class UserGroupServiceImpl implements UserGroupService {

	@Autowired
	UserGroupDAO userGroupDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		UserGroup userGroup = new UserGroup();
		ConversionUtil.getModelByMap(userGroup, param);
		userGroup = this.userGroupDAO.selectOne(userGroup);
		
		return ConversionUtil.getJSONObjectByModel(userGroup);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		UserGroup userGroup = new UserGroup();
		ConversionUtil.getModelByMap(userGroup, param);
		List<UserGroup> list = this.userGroupDAO.selectList(userGroup);

		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		UserGroup userGroup = new UserGroup();
		ConversionUtil.getModelByMap(userGroup, param);

		return this.userGroupDAO.selectCount(userGroup);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		UserGroup userGroup = new UserGroup();
		ConversionUtil.getModelByMap(userGroup, param);

		return this.userGroupDAO.insert(userGroup);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		UserGroup userGroup = new UserGroup();
		ConversionUtil.getModelByMap(userGroup, param);

		return this.userGroupDAO.update(userGroup);
	}

	@Override
	public JSONObject getGroupInfoByUserSeq(int user_seq) throws Exception {
		GroupInfo userGroup = this.userGroupDAO.getGroupInfoByUserSeq(user_seq);
		
		return ConversionUtil.getJSONObjectByModel(userGroup);
	}

}
