package com.nuri.kepco.service.impl;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.dao.UserGroupDAO;
import com.nuri.kepco.service.UserGroupService;
import com.nuri.kepco.model.GroupInfo;
import com.nuri.kepco.model.UserGroup;

@Service
@Transactional
public class UserGroupServiceImpl implements UserGroupService {

	@Autowired
	UserGroupDAO userGroupDAO;


	@Override
	public UserGroup selectOne(UserGroup param) throws Exception {
		return this.userGroupDAO.selectOne(param);
	}

	@Override
	public List<UserGroup> selectList(UserGroup param) throws Exception {
		return this.userGroupDAO.selectList(param);
	}

	@Override
	public int selectCount(UserGroup param) throws Exception {
		return this.userGroupDAO.selectCount(param);
	}

	@Override
	public int insert(UserGroup param) throws Exception {
		return this.userGroupDAO.insert(param);
	}

	@Override
	public int update(UserGroup param) throws Exception {
		return this.userGroupDAO.update(param);
	}

	@Override
	public GroupInfo getGroupInfoByUserSeq(int user_seq) throws Exception {
		return this.userGroupDAO.getGroupInfoByUserSeq(user_seq);
	}

}
