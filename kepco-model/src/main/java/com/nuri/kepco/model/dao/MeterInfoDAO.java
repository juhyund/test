package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.MeterInfo;

@Mapper
public interface MeterInfoDAO extends GenericDAO<MeterInfo> {
	
	MeterInfo selectByMeterSerial(String meterSerial) throws Exception;
	
}
