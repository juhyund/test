package com.nuri.kepco.controller;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.json.simple.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.generator.util.GeneratorId;
import com.nuri.kepco.util.ControllerUtil;
import com.nuri.kepco.util.HttpClientUtil;

@Controller
public class ExecResourceController {
	
	Logger logger = LoggerFactory.getLogger(ExecResourceController.class);

	private String[] commStr = { "device_id", "resource", "newValue", "observeType" };

	@RequestMapping(value = "/ajaxExecResource")
	public ResponseEntity<Object> ajaxExecResource(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = new HashMap<String, Object>();
			ControllerUtil.getCustomParam(request, commStr, param);
			String url = request.getParameter("url");
			String tid = GeneratorId.getInstance().get((String)param.get("device_id"));
			
			json = HttpClientUtil.post(url, param.toString(), tid);

			//TODO History 필요?

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
}
