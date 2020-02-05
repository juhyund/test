package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class UserInfo extends CommonObj {
	
	private String user_seq;
	private String comp_seq;
	private String user_id;
	private String user_name;
	private String user_pass;
	private String reg_dt;
	private String user_yn;
	private String dept_name;
	private String user_phone;
	private String user_email;
	private String reg_user_ip;
}
