package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.OperationLog;
import com.nuri.kepco.model.dao.MeterInfoDAO;
import com.nuri.kepco.model.dao.OperationLogDAO;
import com.nuri.kepco.service.OperationLogService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class OperationLogServiceImpl implements OperationLogService {

	@Autowired
	OperationLogDAO operationLogDAO;

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		OperationLog operationLog = new OperationLog();
		ConversionUtil.getModelByMap(operationLog, param);
		
		return this.operationLogDAO.insert(operationLog);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public JSONObject selectByDeviceSerial(String device_serial) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public JSONArray getOperationLogList(Map<String, Object> param) throws Exception {
		OperationLog operationLog = new OperationLog();
		ConversionUtil.getModelByMap(operationLog, param);
		List<OperationLog> list = this.operationLogDAO.getOperationLogList(operationLog);
		
		return ConversionUtil.getJSONArrayByModel(list,operationLog.getStart());
	}

	@Override
	public int getOperationLogListCnt(Map<String, Object> param) throws Exception {
		OperationLog operationLog = new OperationLog();
		ConversionUtil.getModelByMap(operationLog, param);
		
		return this.operationLogDAO.getOperationLogListCnt(operationLog);
	}

	@Override
	public JSONObject getOperationLogDetail(Map<String, Object> param) throws Exception {
		OperationLog operationLog = operationLogDAO.getOperationLogDetail(param);
		return ConversionUtil.getJSONObjectByModel(operationLog);
	}
}
