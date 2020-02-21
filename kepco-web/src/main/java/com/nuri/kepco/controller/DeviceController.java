package com.nuri.kepco.controller;

import java.util.HashMap;
import java.util.List;
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
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.service.DeviceInfoService;
import com.nuri.kepco.service.DeviceResourceService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class DeviceController {
	
	Logger logger = LoggerFactory.getLogger(DeviceController.class);

	@Autowired
	private DeviceInfoService deviceInfoService;

	@Autowired
	private DeviceResourceService deviceResourceService;
	
	@RequestMapping(value = "/ajaxDeviceInfoList")
	public ResponseEntity<Object> ajaxDeviceInfoList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "branch_nm", "vendor_nm", "device_status", "lsdate", "ledate" };
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "reg_dt");
			param.put("dir", "DESC");
			
			int cnt = this.deviceInfoService.getDeviceListCnt(param);
			JSONArray jarr = this.deviceInfoService.getDeviceList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	
	
	@RequestMapping(value = "/ajaxDeviceObjectModelList")
	public ResponseEntity<Object> ajaxDeviceObjectModelList(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = new HashMap<String, Object>();
			String[] commStr = { "device_id", "vendor_nm", "device_status", "lsdate", "ledate" };
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("device_id", request.getParameter("device_id"));

			JSONArray jarr = this.deviceResourceService.getObjectModelList(param);

			json.put("result", jarr);
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
}
