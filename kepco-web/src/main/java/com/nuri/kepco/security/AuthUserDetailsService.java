package com.nuri.kepco.security;

import org.json.JSONObject;
import org.json.JSONException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

import com.nuri.kepco.service.CompInfoService;
import com.nuri.kepco.service.UserGroupService;
import com.nuri.kepco.service.UserInfoService;

@Service
public class AuthUserDetailsService implements UserDetailsService {
	
	Logger logger = LoggerFactory.getLogger(AuthUserDetailsService.class);
	
	
	@Autowired
	UserInfoService userInfoService;
	
	@Autowired
	UserGroupService userGroupService;
	
	@Autowired
	CompInfoService userCompService;
	
	@Override
	public UserDetails loadUserByUsername(String userId) throws UsernameNotFoundException {
		
		JSONObject user = null;
		JSONObject role = null;
		JSONObject company = null;
		
		try {
			// 사용자 조회 (userId)
			user = userInfoService.getOneByUserId(userId);
			
			if(user != null) {
				
				// group 
				role = userGroupService.getGroupInfoByUserSeq(user.getInt("user_seq"));
				
				// company
				company = userCompService.getCompInfoByUser(user.getInt("user_seq"));				
			} 
			
		} catch (Exception e) {		
			e.printStackTrace();
		}
		
		if(user == null) {
			throw new UsernameNotFoundException(userId);
		}
		
		UserDetails userDetails = null;
		try {
			userDetails = new SecurityUser(user, role, company);
		} catch (JSONException e) {
			logger.error(e.toString(), e);
		}
		
		return userDetails;
	}

}
