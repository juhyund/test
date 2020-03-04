package com.nuri.kepco.controller;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.json.simple.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.generator.util.GeneratorId;
import com.nuri.kepco.util.HttpClientUtil;

@Controller
public class ExecResourceController {
	
	Logger logger = LoggerFactory.getLogger(ExecResourceController.class);
	
	@Value("${device.cmd.url}")
	private String cmdUrl;
	
	@RequestMapping(value = "/ajaxExecResource")
	public ResponseEntity<Object> ajaxExecResource(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		String tid = null;
		try {
			Map<String, Object> param = new HashMap<String, Object>();
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
			
			logger.debug("url: " + url);
			json = HttpClientUtil.send(url, param.toString(), method);
			
			//TODO History 필요?

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
