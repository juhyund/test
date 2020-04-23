package com.nuri.kepco.service;

import java.util.List;
import java.util.Map;

import com.nuri.kepco.model.MeterData;

public interface MeterDataService extends GenericService {
	
	Map<String, String> excelMeterData(Map<String, Object> param) throws Exception;
	
	List<MeterData> selectListDetail(Map<String, Object> param) throws Exception;
}

