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

import com.nuri.kepco.model.MeterBilling;
import com.nuri.kepco.service.BranchInfoService;
import com.nuri.kepco.service.MeterBillingService;
import com.nuri.kepco.util.FormatUtil;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class MeterBillingController {
	
	Logger logger = LoggerFactory.getLogger(MeterBillingController.class);

	@Autowired
	private MeterBillingService meterBillingService;
	@Autowired
	private BranchInfoService branchInfoService;
	
	
	@RequestMapping(value = "/ajaxMeterBilling")
	public ResponseEntity<Object> ajaxMeterBilling(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "meter_serial", "device_serial","meter_type","branch_parent_id", "branch_id","billing_dt","itime","mtime"};
			
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "billing_dt");
			param.put("dir", "DESC");
			
			int cnt = this.meterBillingService.selectCount(param);
			JSONArray jarr = this.meterBillingService.selectList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);
			
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxMeterBillingDetail")
	public ResponseEntity<Object> ajaxMeterBillingDetail(HttpServletRequest request) {                
		
		String[] commStr = { "meter_id", "billing_dt"};
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "billing_dt");
			param.put("dir", "DESC");
			
			JSONArray jarr = this.meterBillingService.selectListDetail(param);
			
			json.put("resultGrid", jarr);
			
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	/*
	*//**
	 * ajaxMeterValueDetail
	 * 
	 * @desc 검침정보 상세창의 그리드, 차트데이터
	 * @param param
	 * @param request
	 * @return
	 *//*
	@RequestMapping(value = "/ajaxMeterValueDetail")
	public ResponseEntity<Object> ajaxMeterValueDetail(
			HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for(String key : commStr) {
				if(request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));	
				}
			}

			List<Map<String, Object>> channels = this.meterValueService.selectMeterChannel(param);
			param.put("channelList", channels);
			
			List<Map<String, Object>> meterValueDetail = this.meterValueService.getMeterValueDetail(param);
			json.put("resultGrid", meterValueDetail);

		} catch (Exception e) {
			e.printStackTrace();
		}
		
		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}*/
	
	@RequestMapping(value = "/billingDetail")
	public String meteringDetail(
			@ModelAttribute(value="meter_id") String meter_id,
			@ModelAttribute(value="billing_dt") String billing_dt,
			@ModelAttribute(value="sdate") String sdate,
			@ModelAttribute(value="edate") String edate,
			Model model) {

		model.addAttribute("meter_id", meter_id);
		model.addAttribute("billing_dt", billing_dt);
		model.addAttribute("sdate", sdate);
		model.addAttribute("edate", edate);
		
		return "mvm/billingDetail";
	
	}
}

