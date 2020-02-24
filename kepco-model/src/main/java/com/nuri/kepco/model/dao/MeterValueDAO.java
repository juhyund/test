package com.nuri.kepco.model.dao;

import java.util.List;
import java.util.Map;
import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.MeterValue;

@Mapper
public interface MeterValueDAO extends GenericDAO<MeterValue> {
	
	int insertAll(List<MeterValue> meterValues);
	
	List<MeterValue> getMeterValue(MeterValue param);
	
	int getMeterValueCount(MeterValue param)throws Exception;
	
	List<MeterValue> getMeterValueDetail(MeterValue param);
	
	List<MeterValue> selectMeterInfo(MeterValue param);
	 
	List<MeterValue> selectMeterChannel(MeterValue param);
	
	MeterValue selectLastValue(MeterValue param);
	
}

