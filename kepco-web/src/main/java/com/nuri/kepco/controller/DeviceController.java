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
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.service.DeviceInfoService;
import com.nuri.kepco.service.DeviceResourceService;
import com.nuri.kepco.config.CodeConstants.DEVICE_STAT;
import com.nuri.kepco.service.BranchInfoService;
import com.nuri.kepco.service.DeviceModelService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class DeviceController {
	
	Logger logger = LoggerFactory.getLogger(DeviceController.class);

	@Autowired
	private DeviceInfoService deviceInfoService;

	@Autowired
	private DeviceResourceService deviceResourceService;
	
	@Autowired
	private BranchInfoService branchInfoService;
	
	@Autowired
	private DeviceModelService deviceModelService;
	
	@RequestMapping(value = "/ajaxDeviceInfoList")
	public ResponseEntity<Object> ajaxDeviceInfoList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "branch_parent_id", "branch_id", "model_seq", "device_status", "lsdate", "ledate" };
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
	
	@RequestMapping(value = "/ajaxDeviceModelCombo")
	public ResponseEntity<Object> ajaxDeviceModelCombo(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = new HashMap<String, Object>();
			JSONArray dModel = this.deviceModelService.selectList(param);
			
			JSONObject deviceModel = new JSONObject();
			for(int i = 0 ; i < dModel.size() ; i++){
				JSONObject obj = (JSONObject) dModel.get(i);
				deviceModel.put(obj.get("model_seq"), obj.get("model_nm"));
			}
			
			json.put("model_seq", deviceModel);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}

	
	
	@RequestMapping(value = "/ajaxDeviceInfo")
	public ResponseEntity<Object> ajaxDeviceInfo(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			String deviceId = request.getParameter("device_id");

			JSONObject info = this.deviceInfoService.getDeviceInfo(deviceId);

			json.put("result", info);
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
			String[] commStr = { "vendor_nm", "device_status", "lsdate", "ledate" };
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
	
	@RequestMapping(value = "/ajaxDeviceResourceModelList")
	public ResponseEntity<Object> ajaxDeviceResourceModelList(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = new HashMap<String, Object>();
			String[] commStr = { "device_id", "object_id" };
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("device_id", request.getParameter("device_id"));
			param.put("object_id", request.getParameter("object_id"));

			JSONArray jarr = this.deviceResourceService.getResourceModelList(param);

			json.put("result", jarr);
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
}

