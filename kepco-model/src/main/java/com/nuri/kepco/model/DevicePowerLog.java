package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DevicePowerLog extends CommonObj {

	private String power_log_seq;
	private String device_id;
	private String device_serial;
	private String power_on_time;
	private String power_off_time;
	private String power_status;
	private Integer itime;
	private String reg_dt;

	private String branch_parent_id;
	private String parent_branch_nm;
	private String branch_id;
	private String branch_nm;
	
	private String s_on_date;
	private String e_on_date;
	private String s_off_date;
	private String e_off_date;
	
}

