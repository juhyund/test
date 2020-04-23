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

import com.nuri.kepco.service.DevicePowerLogService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class DevicePowerLogController {
	
	Logger logger = LoggerFactory.getLogger(DevicePowerLogController.class);

	@Autowired
	private DevicePowerLogService devicePowerLogService;

	@RequestMapping(value = "/ajaxDevicePowerLogList")
	public ResponseEntity<Object> ajaxDevicePowerLogList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "branch_parent_id", "branch_id", "device_serial", "power_status", "s_on_date", "e_on_date", "s_off_date", "e_off_date" };
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "reg_dt");
			param.put("dir", "DESC");

			int cnt = this.devicePowerLogService.selectCount(param);
			JSONArray jarr = this.devicePowerLogService.selectList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
}

