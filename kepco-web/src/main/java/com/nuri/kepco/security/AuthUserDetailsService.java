package com.nuri.kepco.security;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

import com.nuri.kepco.model.CompInfo;
import com.nuri.kepco.model.GroupInfo;
import com.nuri.kepco.model.UserInfo;
import com.nuri.kepco.service.user.UserCompService;
import com.nuri.kepco.service.user.UserGroupService;
import com.nuri.kepco.service.user.UserInfoService;

@Service
public class AuthUserDetailsService implements UserDetailsService {
	
	Logger logger = LoggerFactory.getLogger(AuthUserDetailsService.class);
	
	
	@Autowired
	UserInfoService userInfoService;
	
	@Autowired
	UserGroupService userGroupService;
	
	@Autowired
	UserCompService userCompService;
	
	@Override
	public UserDetails loadUserByUsername(String userId) throws UsernameNotFoundException {
		
		UserInfo user = null;
		GroupInfo role = null;
		CompInfo company = null;
		
		try {
			// 사용자 조회 (userId)
			user = userInfoService.getOneByUserId(userId);
			
			if(user != null) {
				
				// group 
				role = userGroupService.getGroupInfoByUserSeq(user.getUser_seq());
				
				// company
				company = userCompService.getCompInfoByUser(user.getUser_seq());				
			} 
			
		} catch (Exception e) {		
			e.printStackTrace();
		}
		
		if(user == null) {
			throw new UsernameNotFoundException(userId);
		}
		
		return new SecurityUser(user, role, company);
	}

}
