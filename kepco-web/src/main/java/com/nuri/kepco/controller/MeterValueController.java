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
public class MeterValueController {
	
	Logger logger = LoggerFactory.getLogger(MeterValueController.class);

	@Autowired
	private MeterValueService meterValueService;
	
	private String[] commStr = { "meter_id", "device_id","meter_type"};
	
	@RequestMapping(value = "/ajaxMeterValue")
	public ResponseEntity<Object> ajaxMeterValue(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			logger.info("\n\n ### ajaxMeterValue : param ### \n"+param+"\n\n");
			
			int cnt = this.meterValueService.getMeterValueCount(param);
			JSONArray jarr = this.meterValueService.getMeterValue(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);
			
			logger.info("\n\n ### ajaxMeterValue--> result : jarr ### \n"+jarr+"\n\n");

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	/**
	 * ajaxMeterValueDetail
	 * 
	 * @desc 검침정보 상세창의 그리드, 차트데이터
	 * @param param
	 * @param request
	 * @return
	 */
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

			//logger.info("\n\n ### ajaxMeterValueDetail : param ### \n"+param+"\n\n");

			List<Map<String, Object>> channels = this.meterValueService.selectMeterChannel(param);
			
			param.put("channelList", channels);
			
			logger.info("\n\n ### ajaxMeterValueDetail : param ### \n"+param+"\n\n");
			
			List<Map<String, Object>> meterValueDetail = this.meterValueService.getMeterValueDetail(param);
			
			json.put("resultGrid", meterValueDetail);

		} catch (Exception e) {
			e.printStackTrace();
		}
		
		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	/**
	 * ajaxMeterInfoSummary
	 * 
	 * @desc 
	 * @param meter_id
	 * @param request
	 * @return
	 */
	@RequestMapping(value = "/ajaxMeterInfoSummary")
	public ResponseEntity<Object> ajaxMeterInfoSummary(HttpServletRequest request) {

		JSONObject json = new JSONObject();

		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			logger.info("\n\n ### ajaxMeterInfoSummary : param ### \n"+param+"\n\n");
			List<Map<String, Object>> meterInfo = this.meterValueService.selectMeterInfo(param);
			logger.info("\n\n ### ajaxMeterInfoSummary--> result : jarr ### \n"+meterInfo+"\n\n");
			
			json.put("resultGrid", meterInfo);
			

		} catch (Exception e) {
			e.printStackTrace();
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	
	/**
	 * ajaxChannelList
	 * 
	 * @desc 
	 * @param meter_id
	 * @param request
	 * @return
	 */
	
	@RequestMapping(value = "/ajaxChannelList")
	public ResponseEntity<Object> ajaxChannelList(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			logger.info("\n\n ### ajaxChannelList : param ### \n"+param+"\n\n");
			
			List<Map<String, Object>> channelList = this.meterValueService.selectMeterChannel(param);
			
			json.put("resultGrid", channelList);
			
			logger.info("\n\n ### ajaxChannelList--> result : channelList ### \n"+channelList+"\n\n");


		} catch (Exception e) {
			e.printStackTrace();
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
/*public ResponseEntity<Object> ajaxExceldown(@ModelAttribute MeterValue param, HttpServletRequest request) {
		
		List<Map<String, Object>> result;
		
		JSONObject json = new JSONObject();
		try {
			result = this.meterValueService.selectMeterChannel(param);

			json.put("resultGrid", result);

		} catch (Exception e) {
			e.printStackTrace();
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}

	*//**
	 * ajaxMeterValueInsert
	 * 
	 * @desc device 등록
	 * @param param
	 * @param request
	 * @return
	 *//*
	@RequestMapping(value = "ajaxMeterValueInsert")
	public ResponseEntity<Object> ajaxMeterValueInsert(@ModelAttribute MeterValue param,
			HttpServletRequest request) {

		JSONObject json = new JSONObject();

		try {
			int result = this.meterValueService.insert(param);
			
			boolean isSuccess = (result > 0)? true: false;
			json.put("success", isSuccess);
		
		} catch (Exception e) {
			logger.error("error : " + e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "text/html; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	
	*//**
	 * ajaxMeterValueUpdate
	 * 
	 * @desc device update
	 * @param param
	 * @param request
	 * @return
	 *//*
	@RequestMapping(value = "ajaxMeterValueUpdate")
	public ResponseEntity<Object> ajaxMeterValueUpdate(@ModelAttribute MeterValue param,
			HttpServletRequest request) {

		JSONObject json = new JSONObject();

		try {
			int result = this.meterValueService.update(param);
			
			boolean isSuccess = (result > 0)? true: false;
			json.put("success", isSuccess);
		
		} catch (Exception e) {
			logger.error("error : " + e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "text/html; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}*/
	
	@RequestMapping(value = "/meteringDetail")
	public String meteringDetail(
			@ModelAttribute(value="detail_meter_id") String meter_id,
			@ModelAttribute(value="sdate") String sdate,
			@ModelAttribute(value="edate") String edate,
			Model model) {

		model.addAttribute("meter_id", meter_id);
		model.addAttribute("sdate", sdate);
		model.addAttribute("edate", edate);
		
		return "mvm/meteringDetail";
	
	}
}

