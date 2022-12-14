package com.nuri.kepco.controller;

import java.util.HashMap;
import java.util.Iterator;
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
import com.nuri.kepco.service.ObjectModelService;
import com.nuri.kepco.service.DeviceResourceService;
import com.nuri.kepco.service.DeviceModelService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class DeviceController {
	
	Logger logger = LoggerFactory.getLogger(DeviceController.class);

	@Autowired
	private DeviceInfoService deviceInfoService;

	@Autowired
	private ObjectModelService objectModelService;
	
	@Autowired
	private DeviceResourceService deviceResourceService;
	
	@Autowired
	private DeviceModelService deviceModelService;
	
	@RequestMapping(value = "/ajaxDeviceInfoList")
	public ResponseEntity<Object> ajaxDeviceInfoList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "branch_parent_id", "branch_id", "model_seq", "device_status", "lsdate", "ledate","fw_version" };
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "reg_dt");
			param.put("dir", "DESC");
			
        	if(param.containsKey("model_seq")) {
        		param.put("model_seq", (Integer.parseInt((String) param.get("model_seq"))));		        		
        	}

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
	
	@RequestMapping(value = "/ajaxObjectModelList")
	public ResponseEntity<Object> ajaxObjectModelList(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			String[] commStr = { "device_id", "instances" };
			ControllerUtil.getCustomParam(request, commStr, param);

			JSONArray jarr = this.objectModelService.selectObjectList(param);

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
			param.put("device_id", request.getParameter("device_id"));
			param.put("object_id", request.getParameter("object_id"));

			JSONObject result = this.deviceResourceService.getResourceModelList(param);

			json.put("result", result);
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxDeviceInfoUpdate")
	public ResponseEntity<Object> ajaxDeviceInfoUpdate(HttpServletRequest request) {
		
		String[] commStr = { "mobile_no", "ip", "port", "hw_version", "fw_version", "sw_version1", "sw_version2", "remark" };
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = new HashMap<String, Object>();
			param.put("device_id", request.getParameter("device_id"));
			
			JSONObject ori = deviceInfoService.selectOne(param);
			Iterator<String> keysItr = ori.keySet().iterator();
		    while(keysItr.hasNext()) {
		        String key = keysItr.next();
		        Object value = ori.get(key);
		        if(value != null && !"".equals(value)) {
		        	if("model_seq".equals(key)) {
		        		param.put(key, ((int)(long) value));		        		
		        	} else {
		        		param.put(key, value);	
		        	}
		        }
		    }
			ControllerUtil.getCustomParam(request, commStr, param);
			deviceInfoService.update(param);

			json.put("result", "SUCCESS!");
		} catch (Exception e) {
			json.put("result", "ERROR!");
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
}

