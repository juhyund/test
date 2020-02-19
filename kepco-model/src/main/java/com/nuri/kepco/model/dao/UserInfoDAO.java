package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.UserInfo;

@Mapper
public interface UserInfoDAO extends GenericDAO<UserInfo> {
	
	public UserInfo getOneByUserId(String user_id) throws Exception;
}
