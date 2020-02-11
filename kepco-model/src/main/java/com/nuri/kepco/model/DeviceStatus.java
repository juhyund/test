package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceStatus extends CommonObj {

	private String device_id;
	private String device_status;
	private String last_comm_dt;
	private String last_renw_dt;
	private String device_flag;
}
