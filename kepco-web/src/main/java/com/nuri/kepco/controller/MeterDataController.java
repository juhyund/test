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

import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.service.MeterValueService;
import com.nuri.kepco.util.FormatUtil;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class MeterDataController {
	
	Logger logger = LoggerFactory.getLogger(MeterDataController.class);

	@Autowired
	private MeterValueService meterValueService;
	
	private String[] commStr = { "meter_id","meter_serial", "device_serial","meter_type","branch_id","itime","mtime"};
	
	@RequestMapping(value = "/ajaxMeterData")
	public ResponseEntity<Object> ajaxMeterData(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "read_dt");
			param.put("dir", "DESC");
			
			int cnt = this.meterValueService.getMeterValueCount(param);
			JSONArray jarr = this.meterValueService.getMeterValue(param);
			
			json.put("totalCount", cnt);
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
			@ModelAttribute(value="detail_meter_id") String meter_id,
			@ModelAttribute(value="billing_dt") String billing_dt,
			//@ModelAttribute(value="obis_code") String obis_code,
			@ModelAttribute(value="sdate") String sdate,
			@ModelAttribute(value="edate") String edate,
			Model model) {

		model.addAttribute("meter_id", meter_id);
		model.addAttribute("billing_dt", billing_dt);
		//model.addAttribute("obis_code", obis_code);
		model.addAttribute("sdate", sdate);
		model.addAttribute("edate", edate);
		
		return "mvm/meterDataDetail";
	
	}

}

