package com.nuri.kepco.security;

import java.util.ArrayList;
import java.util.List;

import org.json.simple.JSONObject;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.SpringSecurityCoreVersion;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.User;

@SuppressWarnings("serial")
public class SecurityUser extends User {

	private static final long serialVersionUID = SpringSecurityCoreVersion.SERIAL_VERSION_UID;

	private static final String ROLE_PREFIX = "ROLE_";
	public static SimpleGrantedAuthority ROLE_SUPER = new SimpleGrantedAuthority(ROLE_PREFIX + "SUPER");
	public static SimpleGrantedAuthority ROLE_ADMIN = new SimpleGrantedAuthority(ROLE_PREFIX + "ADMIN");
	public static SimpleGrantedAuthority ROLE_USER = new SimpleGrantedAuthority(ROLE_PREFIX + "USER");

	private String user_name;
	private String user_email;
	private JSONObject company;

	public SecurityUser(JSONObject user, JSONObject group, JSONObject company) {

		super((String)user.get("user_id"), (String)user.get("user_pass"), ((int)(long)user.get("user_yn") == 1 ? true : false) 
				, true, true, true, makeGrantedAuthority(group));

		this.user_name = (String)user.get("user_name");
		this.user_email = (String)user.get("user_email");
		
		this.company = company;

	}

	private static List<GrantedAuthority> makeGrantedAuthority(JSONObject group) {
		List<GrantedAuthority> list = new ArrayList<>();
		list.add(new SimpleGrantedAuthority(ROLE_PREFIX + (String)group.get("group_name")));
		return list;
	}
	
	public String getUser_name() {
		return user_name;
	}

	public String getUser_email() {
		return user_email;
	}

	public JSONObject getCompany() {
		return company;
	}

}

