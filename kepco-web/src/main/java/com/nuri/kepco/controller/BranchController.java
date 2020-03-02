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
import org.springframework.web.bind.annotation.RequestMapping;

import com.nuri.kepco.service.BranchInfoService;

@Controller
public class BranchController {
	
	Logger logger = LoggerFactory.getLogger(BranchController.class);

	@Autowired
	private BranchInfoService branchInfoService;
	
	
	@RequestMapping(value = "/ajaxParentBranchCombo")
	public ResponseEntity<Object> ajaxDeviceInfoCombo(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = new HashMap<String, Object>();
			JSONArray bInfo = this.branchInfoService.selectParent();
			
			JSONObject branchInfo = new JSONObject();
			for(int i = 0 ; i < bInfo.size() ; i++){
				JSONObject obj = (JSONObject) bInfo.get(i);
				branchInfo.put(obj.get("branch_id"), obj.get("branch_nm"));
			}
			
			json.put("branch_parent_id", branchInfo);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxBranchCombo")
	public ResponseEntity<Object> ajaxBranchCombo(HttpServletRequest request) {                
		
		JSONObject json = new JSONObject();
		try {
			Map<String, Object> param = new HashMap<String, Object>();
			JSONObject branchInfo = new JSONObject();			
			param.put("branch_parent_id", request.getParameter("branch_parent_id"));
			JSONArray bInfo = this.branchInfoService.selectList(param);

			for(int i = 0 ; i < bInfo.size() ; i++){
				JSONObject obj = (JSONObject) bInfo.get(i);
				branchInfo.put(obj.get("branch_id"), obj.get("branch_nm"));
			}

			json.put("branch_id", branchInfo);

		} catch (Exception e) {
			logger.error(e.toString(),e);
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}
	
}

