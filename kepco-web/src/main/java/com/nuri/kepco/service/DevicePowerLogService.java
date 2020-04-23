package com.nuri.kepco.service;

import java.util.Map;

public interface DevicePowerLogService extends GenericService {
	Map<String, String> excelDevicePowerLogList(Map<String, Object> param) throws Exception;
}

