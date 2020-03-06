package com.nuri.kepco.controller;

import javax.servlet.http.HttpServletRequest;

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

@Controller
public class MainController {
	
	Logger logger = LoggerFactory.getLogger(MainController.class);

	@Autowired
	private DeviceInfoService deviceInfoService;

	@RequestMapping(value = "/ajaxCommunication")
	public ResponseEntity<Object> ajaxCommunication(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			JSONObject result = this.deviceInfoService.getCommunication();
			
			json.put("total", result.get("total"));
			json.put("d1", result.get("d1"));
			json.put("d2", result.get("d2"));
			json.put("d3", result.get("d3"));
			json.put("d4", result.get("d4"));

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
}

