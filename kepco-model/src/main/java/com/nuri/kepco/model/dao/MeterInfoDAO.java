package com.nuri.kepco.model.dao;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.MeterInfo;

@Mapper
public interface MeterInfoDAO extends GenericDAO<MeterInfo> {
	
	MeterInfo selectByMeterSerial(String meterSerial) throws Exception;

	List<MeterInfo> getMeterList(MeterInfo meterInfo);

	int getMeterListCnt(MeterInfo meterInfo);

	MeterInfo getMeterDetailInfo(String meterSerial);
	
}

