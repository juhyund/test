package com.nuri.kepco.controller;

import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.json.JSONArray;
import org.json.simple.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.service.DeviceInfoService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class DeviceController {
	
	Logger logger = LoggerFactory.getLogger(DeviceController.class);

	private String[] commStr = { "branch_nm", "vendor_nm", "device_status" };
	
	@Autowired
	private DeviceInfoService deviceInfoService;

	@RequestMapping(value = "/ajaxDeviceInfoList")
	public ResponseEntity<Object> ajaxDeviceInfoList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for(String key : commStr) {
				if(request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));	
				}
			}
			
			int cnt = this.deviceInfoService.selectCount(param);
			JSONArray jarr = this.deviceInfoService.getDeviceList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr.toString());

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
}
