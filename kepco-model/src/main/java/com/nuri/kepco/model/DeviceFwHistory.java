package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceFwHistory extends CommonObj {
	
	
	private int fw_history_seq;
	private String device_id;
	private int fw_id;
	private String fw_write_dt;
	private String fw_success_dt;
	private String fw_issue_status;
	private String fw_issue_status_nm;
	private String tid;
	private String result_dt;
	private String reg_id;
	private String reg_dt;

	private String device_serial;
	private String device_fw_version;
	private String fw_version;
	private String fw_nm;
	private String fw_file_nm;
	
	private String usdate;
	private String uedate;
}
