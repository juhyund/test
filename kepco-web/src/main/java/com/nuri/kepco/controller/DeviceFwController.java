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

import com.nuri.kepco.service.DeviceFwService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class DeviceFwController {
	
	Logger logger = LoggerFactory.getLogger(DeviceFwController.class);

	@Autowired
	private DeviceFwService deviceFwService;
	
	
	@RequestMapping(value = "/ajaxDeviceFWList")
	public ResponseEntity<Object> ajaxDeviceFWList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "fw_nm", "fw_version" };
			Map<String, Object> param = new HashMap<String, Object>();
			ControllerUtil.getCustomParam(request, commStr, param);
			
			int cnt = this.deviceFwService.selectCount(param);
			JSONArray jarr = this.deviceFwService.selectList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxDeviceFWUpload")
	public ResponseEntity<Object> ajaxBranchCombo(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = new HashMap<String, Object>();
			JSONObject branchInfo = new JSONObject();			
			param.put("branch_parent_id", request.getParameter("branch_parent_id"));
			//path - /home/lwm2m/files/firmwares/{버전}/{파일}
			json.put("branch_id", branchInfo);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
}

