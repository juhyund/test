package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class GroupInfo extends CommonObj {

	private String group_user_seq;
	private String group_id;
	private String group_name;
	private String reg_dt;
	private String reg_id;
	private String reg_ip;
	private String group_sort;
	private String group_text;
	private String group_yn;
}