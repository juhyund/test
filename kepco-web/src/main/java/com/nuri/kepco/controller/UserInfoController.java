package com.nuri.kepco.controller;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

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

import com.nuri.kepco.config.Constants;
import com.nuri.kepco.model.common.OrderByMap;
import com.nuri.kepco.model.common.PagingGridReturnObj;
import com.nuri.kepco.service.UserInfoService;
import com.nuri.kepco.model.UserInfo;
import com.nuri.kepco.util.FormatUtil;

import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

@Controller
public class UserInfoController {
	
	Logger logger = LoggerFactory.getLogger(UserInfoController.class);
/*
	@Autowired
	private UserInfoService userInfoService;

	@RequestMapping(value = "/ajaxUserInfo")
	public ResponseEntity<Object> ajaxUserInfo(
			@ModelAttribute(value="group_user_seq_search") String group_user_seq,
			@ModelAttribute(value="user_name_search") String user_name,
			@ModelAttribute(value="user_id_search") String user_id,
			HttpServletRequest request) {                
		
		
		PagingGridReturnObj result;
		UserInfo param = new UserInfo();
		
		JSONObject json = new JSONObject();
		try {
			param.setPage(param.getPage() == 0 ? 1 : param.getPage());
			param.setLimit(param.getLimit() == 0 ? Constants.FETCH_SIZE : param.getLimit());
			//param.setUser_seq(param.getUser_seq() == 0 ? null : param.getUser_seq());
			param.setUser_name(user_name);
			param.setUser_id(user_id);
			param.setSearchfield("".equals(param.getSearchfield()) ? "user_id" : param.getSearchfield());

			//logger.info("\n\n ### UserInfo : param ### \n"+param+"\n\n");
			
			// sort
			param.getOrderByList().add(new OrderByMap("group_user_seq","asc")); 

			result = this.userInfoService.selectGridList(param);
			
			json.put("totalCount", Integer.toString(result.getTotalcount()));
			json.put("resultGrid", result.getResultgrid());

		} catch (Exception e) {
			e.printStackTrace();
		}

		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "application/json; charset=UTF-8");
		return new ResponseEntity<Object>(json, responseHeaders, HttpStatus.CREATED);
	}

	@RequestMapping(value = "/ajaxCheckId")
	public ResponseEntity<String> ajaxCheckId(
			@ModelAttribute(value="user_id") String user_id,
			HttpServletRequest request) {
		
		//PagingGridReturnObj result;
		
		JSONObject json = new JSONObject();

		try {
			
			UserInfo param = new UserInfo();
			param.setUser_id(user_id);

			int result = this.userInfoService.selectCount(param);
			
			boolean isSuccess = (result == 0)? true: false;
			
			json.put("success", isSuccess);
			json.put("totalCount", result);

		} catch (Exception e) {
			e.printStackTrace();
		}
		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "text/html; charset=UTF-8");
		return new ResponseEntity<String>(json.toString(), responseHeaders, HttpStatus.CREATED);
	}
	
	@RequestMapping(value = "/ajaxSaveUserInfo")	
	public ResponseEntity<Object> ajaxSaveUserInfo(
			@ModelAttribute UserInfo param, 
			@ModelAttribute(value="group_user_seq") String group_user_seq,
			HttpServletRequest request) {

		JSONObject json = new JSONObject();
		
		BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();
		String encodedpw = encoder.encode(param.getUser_pass());
		param.setUser_pass(encodedpw);

		try {
			param.setGroup_user_seq(group_user_seq);

			int result = this.userInfoService.insert(param);
			int result_reg = this.userInfoService.registerGroup(param);
			
			boolean isSuccess = (result > 0 && result_reg > 0 )? true: false;
			
			json.put("success", isSuccess);
		
		} catch (Exception e) {
			logger.error("error : " + e);
		}
		
		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "text/html; charset=UTF-8");
		return new ResponseEntity<Object>(json.toString(), responseHeaders, HttpStatus.CREATED);
}
	
	*//**
	 * ajaxUpdateUserInfo
	 * 
	 * @desc UserInfo update
	 * @param param
	 * @param request
	 * @return
	 *//*
	@RequestMapping(value = "ajaxUpdateUserInfo")
	public ResponseEntity<Object> ajaxUpdateUserInfo(
			@ModelAttribute UserInfo param,
			@ModelAttribute(value="group_user_seq") String group_user_seq,
			HttpServletRequest request) {

		JSONObject json = new JSONObject();
		
		try {
			int result = 0;
			if(param.getUser_pass().equals("")) {
				//비번 안들어올 때
				result = this.userInfoService.update(param);
				
			}else {
				BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();
				String encodedpw = encoder.encode(param.getUser_pass());
				param.setUser_pass(encodedpw);
				result = this.userInfoService.updateWithPassword(param);
			}
			
			boolean isSuccess = (result > 0)? true: false;
			json.put("success", isSuccess);
			
		} catch (Exception e) {
			logger.error("error : " + e);
		}
		
		HttpHeaders responseHeaders = new HttpHeaders();
		responseHeaders.add("Content-Type", "text/html; charset=UTF-8");
		return new ResponseEntity<Object>(json.toString(), responseHeaders, HttpStatus.CREATED);
	}
	*/
}
