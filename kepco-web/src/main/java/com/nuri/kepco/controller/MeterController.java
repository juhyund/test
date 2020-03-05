package com.nuri.kepco.controller;

import java.util.HashMap;
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

import com.nuri.kepco.service.DeviceResourceService;
import com.nuri.kepco.service.MeterInfoService;
import com.nuri.kepco.service.ObisCodeService;
import com.nuri.kepco.service.ObjectModelService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class MeterController {
	
	Logger logger = LoggerFactory.getLogger(MeterController.class);

	private String[] commStr = { "branch_parent_id", "branch_id", "meter_type", "meter_serial", "device_serial", "device_status", "sdate", "edate" };
	
	@Autowired
	private MeterInfoService meterInfoService;
	
	@Autowired
	private ObjectModelService objectModelService;
	
	@Autowired
	private DeviceResourceService deviceResourceService;
	
	@Autowired
	private ObisCodeService obisCodeService;
	

	@RequestMapping(value = "/ajaxMeterInfoList")
	public ResponseEntity<Object> ajaxMeterInfoList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "last_comm_dt");
			param.put("dir", "DESC");
			
			int cnt = this.meterInfoService.getMeterListCnt(param);
			JSONArray jarr = this.meterInfoService.getMeterList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxMeterDetailInfo")
	public ResponseEntity<Object> ajaxMeterDetailInfo(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String meter_serial = request.getParameter("_meter_serial");
			
			JSONObject jarr = this.meterInfoService.getMeterDetailInfo(meter_serial);
			
			json.put("result", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxMeterObjectModel")
	public ResponseEntity<Object> ajaxMeterObjectModel(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			String[] commStr = { "object_id" };
			ControllerUtil.getCustomParam(request, commStr, param);
			
			JSONObject jarr = this.objectModelService.selectOne(param);

			json.put("result", jarr);
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxMeterResourceList")
	public ResponseEntity<Object> ajaxMeterResourceList(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "device_id", "object_id", "object_instance_id" };
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			JSONArray jarr = this.deviceResourceService.getMeterResourceList(param);

			json.put("result", jarr);
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	
	@RequestMapping(value = "/obisCodePopup")
	public String obisCodePopup(@ModelAttribute(value="meter_type") String meter_type,	Model model) {
		model.addAttribute("meter_type", meter_type);
		return "meter/obisCodePopup";
	}
	@RequestMapping(value = "/obisCodePopup2")
	public String obisCodePopup2(@ModelAttribute(value="meter_type") String meter_type,	Model model) {
		model.addAttribute("meter_type", meter_type);
		return "meter/obisCodePopup2";
	}
	
	//미터 : 동적스케줄 설정 메뉴의 OBIS 팝업
	@RequestMapping(value = "/ajaxSelectObisList")
	public ResponseEntity<Object> ajaxSelectObisList(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "meter_type","obis_code","metering_type_nm" };
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			JSONArray jarr = this.obisCodeService.selectObisList(param);
			
			json.put("result", jarr);
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	//미터 : 동적미터 설정 메뉴의 OBIS 팝업
	@RequestMapping(value = "/ajaxSelectObisList2")
	public ResponseEntity<Object> ajaxSelectObisList2(HttpServletRequest request) {
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "meter_type","obis_code","descr" };
			
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			logger.info("\n-------------ajaxSelectObisList2---\nparam = "+param);
			ControllerUtil.getCustomParam(request, commStr, param);
			JSONArray jarr = this.obisCodeService.selectObisList2(param);
			
			json.put("result", jarr);
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
}
