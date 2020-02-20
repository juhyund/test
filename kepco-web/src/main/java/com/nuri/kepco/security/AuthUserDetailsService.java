package com.nuri.kepco.security;

import org.json.simple.JSONObject;
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
				role = userGroupService.getGroupInfoByUserSeq((int)(long)user.get("user_seq"));
				
				// company
				company = userCompService.getCompInfoByUser((int)(long)user.get("user_seq"));			
			} 
			
		} catch (Exception e) {		
			e.printStackTrace();
		}
		
		if(user == null) {
			throw new UsernameNotFoundException(userId);
		}
		
		UserDetails userDetails = null;
		userDetails = new SecurityUser(user, role, company);
		
		return userDetails;
	}

}
