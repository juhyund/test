package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class CompInfo extends CommonObj {

	private String comp_seq;
	private String comp_name;
	private String corp_reg_num;
	private String comp_reg_num;
	private String comp_stat;
	private String comp_manage;
	private String comp_type;
	private String comp_sector;
	private String comp_cat;
	private String comp_zcode;
	private String comp_addr1;
	private String comp_addr2;
	private String comp_addr3;
	private String comp_phone;
	private String comp_email;
	private String comp_fax;
	private String comp_id;
	private String reg_ip;
	private String comp_addr4;
}
