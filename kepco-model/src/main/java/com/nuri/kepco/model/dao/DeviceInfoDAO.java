package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.DeviceInfo;

@Mapper
public interface DeviceInfoDAO extends GenericDAO<DeviceInfo> {
	
	DeviceInfo selectByDeviceSerial(String device_serial) throws Exception;
}
