package com.nuri.kepco.controller;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ModelAttribute;

import com.nuri.kepco.config.Constants;
import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.service.MeterValueService;
import com.nuri.kepco.util.ControllerUtil;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import org.springframework.core.io.InputStreamResource;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class FileDownloadController {
	
	Logger logger = LoggerFactory.getLogger(FileDownloadController.class);

	@Autowired
	private MeterValueService meterValueService;

	/*
	 * downloadMeterValue
	 * @desc MeterValue 엑셀다운로드
	 */
	 @GetMapping("/downloadMeterValue")
	   public ResponseEntity<InputStreamResource> downloadMeterValue(HttpServletRequest request) throws IOException {
		
		 String[] commStr = { "meter_id","meter_serial", "device_serial","meter_type","branch_id","itime","mtime"};
		 String file_path = "";

			try {
				
				Map<String, Object> param = ControllerUtil.getCommonParam(request);

		         for(String key : commStr) {
			          if(request.getParameterMap().containsKey(key)) {
			        		  param.put(key, request.getParameter(key));	
			      }
		         }
		         param.put("limit",0);
				
				Map<String, String> output = this.meterValueService.excelMeterValue(param);
				file_path = output.get("filepath") + "/" + output.get("filename");

			} catch (Exception e) {
				logger.error("error : " + e);
			}
			
	      File file = new File(file_path);
	      InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

	      return ResponseEntity.ok()
	            .header(HttpHeaders.CONTENT_DISPOSITION,
	                  "attachment;filename=" + file.getName())
	            .contentType(MediaType.APPLICATION_PDF).contentLength(file.length())
	            .body(resource);
	   }
	 
	 /*
	 * downloadMeterValueDetail
	 * @desc MeterValueDetail 엑셀다운로드
	 
	 @GetMapping("/downloadMeterValueDetail")
	   public ResponseEntity<InputStreamResource> downloadMeterValueDetail(@ModelAttribute MeterValue param) throws IOException {
		
		 String file_path = "";
		 param.setPage(0);
		 param.setLimit(0);

			try {
				
				Map<String, String> channelList = this.meterValueService.selectMeterChannel(param);
				param.setChannelList(channelList);
				
				Map<String, String> output = this.meterValueService.excelMeterValueDetail(param);
				file_path = output.get("filepath") + "/" + output.get("filename");

			} catch (Exception e) {
				logger.error("error : " + e);
			}
			
	      File file = new File(file_path);
	      InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

	      return ResponseEntity.ok()
	            .header(HttpHeaders.CONTENT_DISPOSITION,
	                  "attachment;filename=" + file.getName())
	            .contentType(MediaType.APPLICATION_PDF).contentLength(file.length())
	            .body(resource);
	   }*/

}

