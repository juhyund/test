package com.nuri.kepco.model.dao;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.DeviceInfo;

@Mapper
public interface DeviceInfoDAO extends GenericDAO<DeviceInfo> {
	
	DeviceInfo selectByDeviceSerial(String device_serial) throws Exception;
	
	List<DeviceInfo> getDeviceList(DeviceInfo deviceInfo) throws Exception;
	
	int getDeviceListCnt(DeviceInfo deviceInfo) throws Exception;
	
	DeviceInfo getDeviceInfo(String deviceId) throws Exception;
	
	DeviceInfo getCommunication() throws Exception;
}

