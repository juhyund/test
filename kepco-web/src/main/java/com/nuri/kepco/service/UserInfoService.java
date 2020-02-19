package com.nuri.kepco.service;

import com.nuri.kepco.model.UserInfo;
import com.nuri.kepco.model.dao.GenericDAO;

public interface UserInfoService extends GenericDAO<UserInfo> {
	
	UserInfo getOneByUserId(String user_id) throws Exception;
}
