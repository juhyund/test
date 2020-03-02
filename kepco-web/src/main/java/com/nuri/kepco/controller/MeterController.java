package com.nuri.kepco.controller;

import java.util.HashMap;
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

import com.nuri.kepco.service.DeviceResourceService;
import com.nuri.kepco.service.MeterInfoService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class MeterController {
	
	Logger logger = LoggerFactory.getLogger(MeterController.class);

	private String[] commStr = { "branch_parent_id", "branch_id", "meter_type", "meter_serial", "device_serial", "device_status", "sdate", "edate" };
	
	@Autowired
	private MeterInfoService meterInfoService;
	
	@Autowired
	private DeviceResourceService deviceResourceService;
	

	@RequestMapping(value = "/ajaxMeterInfoList")
	public ResponseEntity<Object> ajaxMeterInfoList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "last_comm_dt");
			param.put("dir", "DESC");
			
			int cnt = this.meterInfoService.getMeterListCnt(param);
			JSONArray jarr = this.meterInfoService.getMeterList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxMeterDetailInfo")
	public ResponseEntity<Object> ajaxMeterDetailInfo(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String meter_serial = request.getParameter("_meter_serial");
			
			JSONObject jarr = this.meterInfoService.getMeterDetailInfo(meter_serial);
			
			json.put("result", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxMeterResourceList")
	public ResponseEntity<Object> ajaxMeterResourceList(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "device_id", "object_id", "object_instance_id" };
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			logger.info("===============ajaxMeterResourceModelList==========================\n param "+param);

			JSONArray jarr = this.deviceResourceService.getMeterResourceList(param);

			json.put("result", jarr);
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
}
