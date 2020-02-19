package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.GroupInfo;
import com.nuri.kepco.model.UserGroup;

@Mapper
public interface UserGroupDAO extends GenericDAO<UserGroup> {
	
	GroupInfo getGroupInfoByUserSeq(int user_seq) throws Exception;
}
