package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceSecLog extends CommonObj {
	
	private String device_id;
	private String reg_dt;
	private String device_serial;
	private String cli_key;
	private String recv_dt;
	private String cmd_cd;
	private String tid;
	private String sec_cd;
}
