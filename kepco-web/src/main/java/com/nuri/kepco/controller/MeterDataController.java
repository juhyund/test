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
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.service.MeterBillingService;
import com.nuri.kepco.service.MeterDataService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class MeterDataController {
	
	Logger logger = LoggerFactory.getLogger(MeterDataController.class);

	@Autowired
	private MeterDataService meterDataService;
	@Autowired
	private MeterBillingService meterBillingService;
	
	private String[] commStr = { "meter_id","meter_serial", "device_serial","meter_type","branch_id","itime","mtime"};
	
	@RequestMapping(value = "/ajaxMeterData")
	public ResponseEntity<Object> ajaxMeterData(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "read_dt");
			param.put("dir", "DESC");
			
			int cnt2 = this.meterBillingService.selectCount(param);
			int cnt = this.meterDataService.selectCount(param);
			JSONArray jarr = this.meterDataService.selectList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxMeterDataDetail")
	public ResponseEntity<Object> ajaxMeterDataDetail(HttpServletRequest request) {                
		
		String[] commStr = { "meter_id", "read_dt","obis_code"};
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "read_dt");
			param.put("dir", "DESC");
			
			JSONArray jarr = this.meterDataService.selectDetail(param);
			
			json.put("resultGrid", jarr);
			
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	
	@RequestMapping(value = "/meterDataDetail")
	public String meterDataDetail(
			@ModelAttribute(value="meter_id") String meter_id,
			@ModelAttribute(value="read_dt") String read_dt,
			@ModelAttribute(value="obis_code") String obis_code,
			Model model) {

		model.addAttribute("meter_id", meter_id);
		model.addAttribute("read_dt", read_dt);
		model.addAttribute("obis_code", obis_code);
		
		return "mvm/meterDataDetail";
	
	}

}

