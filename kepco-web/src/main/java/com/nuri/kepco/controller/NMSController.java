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
			String deviceStatus = request.getParameter("device_status");
			String branch_parent_id = request.getParameter("branch_parent_id");
			String branchId = request.getParameter("branch_id");
			String searchfield = request.getParameter("searchfield");
			String searchquery = request.getParameter("searchquery");
			
			param.put("row", limit);
			if(deviceStatus != null && !("").equals(deviceStatus)) {
				param.put("deviceStatus", deviceStatus);
			}
			if(branch_parent_id != null && !("").equals(branch_parent_id)) {
				param.put("parentBranchId", branch_parent_id);
			}
			if(branchId != null && !("").equals(branchId)) {
				param.put("branchId", branchId);
			}
			
			if(searchfield != null && !("").equals(searchfield)) {
				if(("deviceId").equals(searchfield)) {
					param.put("deviceId", searchquery);
				}else if(("deviceSerial").equals(searchfield)) {
					param.put("deviceSerial", searchquery);
				}
				
			}
			
//			param.put("sort", "usageTime");
//			param.put("dir", "DESC");
			
			long cnt = this.nmsInfoService.getCount(param);
			JSONArray connectivityStatistics =  nmsInfoService.getConnectivityStatistics(param);
			JSONArray jarr = new JSONArray();
			JSONObject tmp = new JSONObject();
			JSONObject parseResult = new JSONObject();
			for (int i = 0; i < connectivityStatistics.size(); i++) {
				tmp = (JSONObject) connectivityStatistics.get(i);
				String usageTime = (String) tmp.get("usageTime");
				String saveTime = (String) tmp.get("saveTime");
				
				SimpleDateFormat beforFormat = new SimpleDateFormat("yyyyMMddHHmmss");
				SimpleDateFormat transFormat = new SimpleDateFormat("yy-MM-dd HH:mm:ss");

				tmp.put("usageTime", transFormat.format(beforFormat.parse(usageTime)));
				tmp.put("saveTime", transFormat.format(beforFormat.parse(saveTime)));
				
				jarr.add(i, tmp);
				
			}
			
			json.put("totalCount", cnt);
			json.put("resultGrid", jarr);
			
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
			
			List<RamUsageMonitor> ramUsageList = this.nmsInfoService.getRamUsageMonitor(param);
			List<CpuUsageMonitor> cpuUsageList = this.nmsInfoService.getCpuUsageMonitor(param);
			List<ConnectivityMonitor> connectivityList = this.nmsInfoService.getConnectivityMonitor(param);
			
			System.out.println("ramUsageList : "+ramUsageList.size());
			System.out.println("cpuUsageList : "+cpuUsageList.size());
			System.out.println("connectivityList : "+connectivityList.size());
			
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
