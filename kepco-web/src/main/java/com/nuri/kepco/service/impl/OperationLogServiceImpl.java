package com.nuri.kepco.service.impl;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.OperationLog;
import com.nuri.kepco.model.dao.OperationLogDAO;
import com.nuri.kepco.service.OperationLogService;
import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.ExcelRef;
import com.nuri.kepco.util.ExcelUtil;

@Service
@Transactional
public class OperationLogServiceImpl implements OperationLogService {

	@Autowired
	OperationLogDAO operationLogDAO;
	
	@Value("${file.download.dir:/files}")
	String fileDownloadDir;

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
	
	@Override
	public JSONArray getExcuteRate() throws Exception {
		List<OperationLog> list = operationLogDAO.getExcuteRate();
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public Map<String, String> excelOperationLogList(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		OperationLog operationLog = new OperationLog();
		ConversionUtil.getModelByMap(operationLog, param);
		
		String template_filepath = "/template/template_excel.xlsx";
		String filename = "operationLog_List_" + DateUtil.getNowDateTime() + ".xlsx";
		String filepath = fileDownloadDir + "/operationLog_List/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();
		
		List<OperationLog> result = this.operationLogDAO.getOperationLogList(operationLog);
		//리소스 경로 변환
		for (int i = 0; i < result.size(); i++) {
			String resource_sum = null;
			//object_id
			if(result.get(i).getObject_id() != null){
				resource_sum = Integer.toString(result.get(i).getObject_id());
					//object_instance_id	
					if(result.get(i).getObject_instance_id() != null){
						resource_sum += "/" + result.get(i).getObject_instance_id();
					}	
			}
			//resource_id
			if(result.get(i).getResource_id() != null){
				resource_sum += "/" + Integer.toString(result.get(i).getResource_id());
					//resource_instance_id	
					if(result.get(i).getResource_instance_id() != null){
						resource_sum += "/" + result.get(i).getResource_instance_id();
					}	
			} 
			result.get(i).setResource_sum(resource_sum);
		}
		
		ExcelRef excelRef = new ExcelRef();

		excelRef.setTitle("제어이력 다운로드");
		excelRef.setHeaders(new String[] {"모뎀ID", "모뎀번호", "리소스 경로", "오브젝트명", "리소스명","타겟ID", "제어항목", "제어결과", "트랜잭션ID", "전송 일시", "응답 일시", "요청자"});
		excelRef.setCells("device_id,device_serial,resource_sum,object_nm,resource_nm,target_meter,method,result,tid,request_dt,result_dt,reg_id");
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result, excelRef);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
			
		return output;
	}
}
