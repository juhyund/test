package com.nuri.kepco.controller;

import java.text.SimpleDateFormat;
import java.util.Date;
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
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.mongo.model.ConnectivityMonitor;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;
import com.nuri.kepco.service.NMSInfoService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class NMSController {
	
	Logger logger = LoggerFactory.getLogger(NMSController.class);

	private String[] commStr = {"deviceId", "deviceSerial", "sdate", "edate", "data_per_page", "usageTime"};
	
	@Autowired
	private NMSInfoService nmsInfoService;

	@RequestMapping(value = "/ajaxNMSList")
	public ResponseEntity<Object> ajaxNMSList(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
			int limit = Integer.parseInt(request.getParameter("limit"));
			param.put("row", limit);
			
//			param.put("sort", "usageTime");
//			param.put("dir", "DESC");
			
			long cnt = this.nmsInfoService.getCount(param);
			JSONArray connectivityStatistics =  nmsInfoService.getConnectivityStatistics(param);
			
			/*JSONObject parseResult = new JSONObject();
			for (int i = 0; i < connectivityStatistics.size(); i++) {
				JSONObject tmp = (JSONObject) connectivityStatistics.get(i);
				String usageTime = (String) tmp.get("usageTime");
				String saveTime = (String) tmp.get("saveTime");
				
//				tmp.put("usageTime", usageTime);
//				tmp.put("saveTime", saveTime);
				
				SimpleDateFormat transFormat = new SimpleDateFormat("yyyyMMddHHmmss");

				Date toDate_usageTime = transFormat.parse(usageTime);
				Date toDate_saveTime = transFormat.parse(saveTime);
				
//				tmp.put("usageTime", toDate_usageTime);
//				tmp.put("saveTime", toDate_saveTime);
				
				tmp.put("usageTime", transFormat.parse((String) tmp.get("usageTime")));
				tmp.put("saveTime", transFormat.parse((String) tmp.get("saveTime")));
				
				connectivityStatistics.add(i, tmp);
			}*/
			
			json.put("totalCount", cnt);
			json.put("resultGrid", connectivityStatistics);
			
		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxNMSDetail")
	public ResponseEntity<Object> ajaxNMSDetail(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);
			
//			String deviceSerial = request.getParameter("deviceSerial");
			
			int limit = Integer.parseInt(request.getParameter("limit"));
			String usageTime = request.getParameter("usageTime");
			String sdate = request.getParameter("sdateView");
			String edate = request.getParameter("edateView");
//			param.put("row", limit);
			param.put("usageTime", usageTime);
			param.put("sdate", sdate);
			param.put("edate", edate);
			
//			param.put("deviceSerial", request.getParameter("deviceSerial"));
						
			List<RamUsageMonitor> ramUsageList = this.nmsInfoService.getRamUsageMonitor(param);
			List<CpuUsageMonitor> cpuUsageList = this.nmsInfoService.getCpuUsageMonitor(param);
			List<ConnectivityMonitor> connectivityList = this.nmsInfoService.getConnectivityMonitor(param);
			
			json.put("ramUsageList", ramUsageList);
			json.put("cpuUsageList", cpuUsageList);
			json.put("connectivityList", connectivityList);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
}
