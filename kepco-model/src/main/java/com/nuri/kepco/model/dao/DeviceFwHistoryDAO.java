package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.DeviceFwHistory;

@Mapper
public interface DeviceFwHistoryDAO extends GenericDAO<DeviceFwHistory> {
	
	DeviceFwHistory selectByTid(String tid) throws Exception;
	
}
