package com.nuri.kepco.model.dao;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.NMSInfo;

@Mapper
public interface NMSInfoDAO extends GenericDAO<NMSInfo> {
	
	NMSInfo selectByMeterSerial(String meterSerial) throws Exception;

	List<NMSInfo> getNMSList(NMSInfo nmsInfo);

	int getNMSListCnt(NMSInfo nmsInfo);

	NMSInfo getNMSDetail(String meterSerial);
	
}

