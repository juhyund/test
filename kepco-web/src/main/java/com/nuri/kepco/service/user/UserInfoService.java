package com.nuri.kepco.service.user;

import com.nuri.kepco.model.dao.UserInfoDAO;

import com.nuri.kepco.model.UserInfo;

public interface UserInfoService extends UserInfoDAO {
	
	public UserInfo getOneByUserId(String user_id) throws Exception;
}
