package com.nuri.kepco.model.dao;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.MeterValue;

@Mapper
public interface MeterValueDAO extends GenericDAO<MeterValue> {
	
	int insertAll(List<MeterValue> meterValues);
	
}
