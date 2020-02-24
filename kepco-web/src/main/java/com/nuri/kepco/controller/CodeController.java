package com.nuri.kepco.controller;

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
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.model.AllCode;
import com.nuri.kepco.service.AllCodeService;
import com.nuri.kepco.util.FormatUtil;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class CodeController {
	
	Logger logger = LoggerFactory.getLogger(MeterValueController.class);

	@Autowired
	private AllCodeService allCodeService;
	
	private String[] commStr = { "code", "code_nm","sort", "parent_code"};
	
	@RequestMapping(value = "/ajaxCodeCombo")
	public ResponseEntity<Object> ajaxCodeCombo(HttpServletRequest request) {                
		
		List<Map<String, Object>> result = null;
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			result = this.allCodeService.selectCombo(param);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}
		JSONObject json = new JSONObject();
		json.put("result", result);

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json.toString(), responseHeaders, HttpStatus.CREATED);
	}
}

