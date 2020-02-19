package com.nuri.kepco.service.impl;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.dao.UserInfoDAO;
import com.nuri.kepco.service.UserInfoService;
import com.nuri.kepco.model.UserInfo;

@Service
@Transactional
public class UserInfoServiceImpl implements UserInfoService {

	@Autowired
	UserInfoDAO userInfoDAO;


	@Override
	public UserInfo selectOne(UserInfo param) throws Exception {
		return this.userInfoDAO.selectOne(param);
	}

	@Override
	public List<UserInfo> selectList(UserInfo param) throws Exception {
		return this.userInfoDAO.selectList(param);
	}

	@Override
	public int selectCount(UserInfo param) throws Exception {
		return this.userInfoDAO.selectCount(param);
	}

	@Override
	public int insert(UserInfo param) throws Exception {
		return this.userInfoDAO.insert(param);
	}

	@Override
	public int update(UserInfo param) throws Exception {
		return this.userInfoDAO.update(param);
	}

	@Override
	public UserInfo getOneByUserId(String user_id) throws Exception {
		return this.userInfoDAO.getOneByUserId(user_id);
	}

}
