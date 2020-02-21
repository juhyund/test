package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceInfo extends CommonObj {

	private String device_id;		
	private String device_serial;
	private String service_id;
	private String branch_id;
	private String model_seq;
	private String device_oid;
	private String comm_type;
	private String device_type;
	private String ip;
	private String port;
	private String allow_yn;
	private String init_reg_dt;
	private String reg_id;
	private String reg_dt;
	private String dest_dt;
	
	private String branch_nm;
	private String model_nm;
	private String vendor_nm;
	private String code_local_nm;
	private String device_status;
	private String last_comm_dt;
	private String lsdate;
	private String ledate;
	
}
