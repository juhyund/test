package com.nuri.kepco.security;

import java.util.ArrayList;
import java.util.List;

import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.SpringSecurityCoreVersion;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.User;

import com.nuri.kepco.model.CompInfo;
import com.nuri.kepco.model.GroupInfo;
import com.nuri.kepco.model.UserInfo;

@SuppressWarnings("serial")
public class SecurityUser extends User {

	private static final long serialVersionUID = SpringSecurityCoreVersion.SERIAL_VERSION_UID;

	private static final String ROLE_PREFIX = "ROLE_";
	public static SimpleGrantedAuthority ROLE_SUPER = new SimpleGrantedAuthority(ROLE_PREFIX + "SUPER");
	public static SimpleGrantedAuthority ROLE_ADMIN = new SimpleGrantedAuthority(ROLE_PREFIX + "ADMIN");
	public static SimpleGrantedAuthority ROLE_USER = new SimpleGrantedAuthority(ROLE_PREFIX + "USER");

	private String user_name;
	private String user_email;
	private CompInfo company;

	public SecurityUser(UserInfo user, GroupInfo group, CompInfo company) {

		super(user.getUser_id(), user.getUser_pass(), (user.getUser_yn() == 1 ? true : false) 
				, true, true, true, makeGrantedAuthority(group));

		this.user_name = user.getUser_name();
		this.user_email = user.getUser_email();
		
		this.company = company;

	}

	private static List<GrantedAuthority> makeGrantedAuthority(GroupInfo group) {
		List<GrantedAuthority> list = new ArrayList<>();
		list.add(new SimpleGrantedAuthority(ROLE_PREFIX + group.getGroup_name()));
		return list;
	}
	
	public String getUser_name() {
		return user_name;
	}

	public String getUser_email() {
		return user_email;
	}

	public CompInfo getCompany() {
		return company;
	}

}
