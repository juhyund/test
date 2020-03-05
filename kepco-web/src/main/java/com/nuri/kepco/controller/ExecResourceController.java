package com.nuri.kepco.controller;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.json.simple.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.generator.util.GeneratorId;
import com.nuri.kepco.service.OperationLogService;
import com.nuri.kepco.util.ControllerUtil;
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.HttpClientUtil;

@Controller
public class ExecResourceController {
	
	Logger logger = LoggerFactory.getLogger(ExecResourceController.class);
	
	@Value("${device.cmd.url}")
	private String cmdUrl;
	
	@Autowired
	private OperationLogService operationLogService;
	
	@RequestMapping(value = "/ajaxExecResource")
	public ResponseEntity<Object> ajaxExecResource(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		String tid = null;
		try {
			JSONObject body = new JSONObject();
			String url = request.getParameter("url");
			String method = request.getParameter("method");
			String device_serial = request.getParameter("device_serial");
			String resource = request.getParameter("resource");
			tid = GeneratorId.getInstance().getId(device_serial);
			url = cmdUrl + url + device_serial + resource;
			
			if("Execute".equals(method)) {
				url += "?tid=" + tid;

			} else if("coapping".equals(method)) {
				url += "?timeout=5000";
			} else {
				url += "?format=JSON&tid=" + tid;				
			}
			
			if("Execute".equals(method) || "Write".equals(method)) {
				String value = request.getParameter("newValue");
				body.put("id", "0"); //TODO id는 무엇?
				body.put("value", value);
			}
			
			Map<String, Object> param = new HashMap<String, Object>();
			param.put("request_dt", DateUtil.getNowDateTime());
			param.put("tid", tid);
			param.put("reg_id", ControllerUtil.getLoginUser());
			
			String[] commStr = { "device_id",  "service_id", "resource_instance_id" };
			ControllerUtil.getCustomParam(request, commStr, param);
			
			operationLogService.insert(param);
			
			logger.debug("url: " + url);
			json = HttpClientUtil.send(url, body.toString(), method);
			
		} catch (Exception e) {
			json.put("statusCode", "500");
			json.put("statusMsg", e.toString());
			logger.error(e.toString(), e);
		}

		json.put("tid", tid);
		
		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxCoAPpIng")
	public ResponseEntity<Object> ajaxCoAPpIng(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		String tid = null;
		try {
			String url = request.getParameter("url");
			String method = request.getParameter("method");
			String device_serial = request.getParameter("device_serial");
			int sec = request.getParameter("sec") == "" ? 1 : Integer.parseInt(request.getParameter("sec"));
			tid = GeneratorId.getInstance().getId(device_serial);
			url = cmdUrl + url + device_serial + "?timeout=" + (sec * 1000);
			
			logger.debug("url: " + url);
			
			json = HttpClientUtil.send(url, null, method);
			
		} catch (Exception e) {
			json.put("statusCode", "500");
			json.put("statusMsg", e.toString());
			logger.error(e.toString(), e);
		}

		json.put("tid", tid);
		
		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
}
