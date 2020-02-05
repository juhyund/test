package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class UserGroup extends CommonObj {

	private String user_seq;
	private String group_user_seq;
	private String reg_dt;
	private String reg_user_id;
	private String reg_user_ip;

}
