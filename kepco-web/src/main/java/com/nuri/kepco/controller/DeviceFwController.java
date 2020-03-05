package com.nuri.kepco.controller;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.io.FileUtils;
import org.json.simple.JSONArray;
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
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;

import com.nuri.kepco.config.CodeConstants;
import com.nuri.kepco.service.DeviceFwService;
import com.nuri.kepco.service.DeviceFwHistoryService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class DeviceFwController {
	
	Logger logger = LoggerFactory.getLogger(DeviceFwController.class);

	@Autowired
	private DeviceFwService deviceFwService;

	@Autowired
	private DeviceFwHistoryService deviceFwHistoryService;
	
	@Value("${device.fw.path}")
	private String deviceFwPath;
	
	@Value("${device.fw.url}")
	private String deviceFwUrl;
	
	@RequestMapping(value = "/ajaxDeviceFWList")
	public ResponseEntity<Object> ajaxDeviceFWList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "fw_file_nm", "fw_version" };
			Map<String, Object> param = new HashMap<String, Object>();
			ControllerUtil.getCustomParam(request, commStr, param);
			
			int cnt = this.deviceFwService.selectCount(param);
			JSONArray jarr = this.deviceFwService.selectList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxDeviceFWUpload")
	public ResponseEntity<Object> ajaxBranchCombo(HttpServletRequest request
			, @RequestParam("fw_file") MultipartFile multipartFile){

		InputStream fileStream = null;
		File targetFile = null;
		JSONObject json = new JSONObject();
		try {
			String new_name = UUID.randomUUID().toString();

			String[] commStr = { "fw_nm", "fw_version", "fw_file_nm" };
			Map<String, Object> param = new HashMap<String, Object>();
			ControllerUtil.getCustomParam(request, commStr, param);

			File dir = new File(deviceFwPath + "/" + param.get("fw_version"));
			
			if (!dir.exists()) {
				dir.mkdir(); 
			}
			
			targetFile = new File(dir.getPath() + "/" + new_name);
			fileStream = multipartFile.getInputStream();
			FileUtils.copyInputStreamToFile(fileStream, targetFile);
			
			String package_uri = deviceFwUrl + param.get("fw_version") + "/" + new_name;
			
			param.put("fw_file_path", targetFile.getPath());
			param.put("fw_pkg_uri", package_uri);
			param.put("fw_biuld_no", "1.0");
			param.put("use_yn", CodeConstants.USE_YN.Y.getCode());
			param.put("reg_id", ControllerUtil.getLoginUser());
			
			deviceFwService.insert(param);
			
			json.put("result", "success");
		} catch (Exception e) {
			logger.error(e.toString(),e);
			if(targetFile != null) {
				targetFile.delete();
			}
			json.put("result", "error");
		} finally {
			if(fileStream != null) {
				try {
					fileStream.close();
				} catch (IOException e) {
					logger.error(e.toString(),e);
				}
			}
		}
		
		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxFirmwareHistoryList")
	public ResponseEntity<Object> ajaxFirmwareHistoryList(HttpServletRequest request){

		JSONObject json = new JSONObject();
		try {
			String[] commStr = { "device_serial", "fw_issue_status", "fw_file_nm", "fw_version", "usdate", "uedate" };

			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			param.put("sort", "reg_dt");
			param.put("dir", "DESC");
			
			int cnt = this.deviceFwHistoryService.selectCount(param);
			JSONArray jarr = this.deviceFwHistoryService.selectList(param);
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	
	
}

