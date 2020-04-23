package com.nuri.kepco.model.dao;

import java.util.List;
import java.util.Map;
import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.MeterData;

@Mapper
public interface MeterDataDAO extends GenericDAO<MeterData> {

	List<MeterData> selectListDetail(MeterData param) throws Exception;
	
	List<Map<String, Object>> selectMeterInfo(MeterData param);	
	
}

