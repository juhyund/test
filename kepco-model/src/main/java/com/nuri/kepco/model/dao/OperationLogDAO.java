package com.nuri.kepco.model.dao;

import java.util.List;
import java.util.Map;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.OperationLog;

@Mapper
public interface OperationLogDAO extends GenericDAO<OperationLog> {
	
	List<OperationLog> getOperationLogList(OperationLog operationLog) throws Exception;
	
	int getOperationLogListCnt(OperationLog operationLog) throws Exception;

	OperationLog getOperationLogDetail(Map<String, Object> param);
	
	OperationLog selectByTID(String tid) throws Exception;

}
