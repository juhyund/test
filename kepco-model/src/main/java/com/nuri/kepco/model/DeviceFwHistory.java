package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceFwHistory extends CommonObj {
	private int fw_history_seq;
	private String device_id;
	private int fw_id;
	private String fw_write_dt;
	private String fw_execute_dt;
	private String fw_issue_status;
	private String tid;
	private String reg_id;
	private String reg_dt;

}
