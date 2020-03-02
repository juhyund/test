package com.nuri.kepco.controller;

import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.service.MeterInfoService;
import com.nuri.kepco.service.OperationLogService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class OperationLogController {
	
	Logger logger = LoggerFactory.getLogger(OperationLogController.class);

	private String[] commStr = { "device_id", "meter_type", "device_status", "sdate", "edate" };
	
	@Autowired
	private OperationLogService operationLogService;

	@RequestMapping(value = "/ajaxOperationLogList")
	public ResponseEntity<Object> ajaxMeterInfoList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "result_dt");
			param.put("dir", "DESC");
			
			int cnt = this.operationLogService.getOperationLogListCnt(param);
			JSONArray jarr = this.operationLogService.getOperationLogList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxOperationLogDetail")
	public ResponseEntity<Object> ajaxMeterDetailInfo(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String meter_serial = request.getParameter("_meter_serial");
			
//			JSONObject jarr = this.operationLogService.getOperationLogDetail(meter_serial);
			
//			json.put("result", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
}
