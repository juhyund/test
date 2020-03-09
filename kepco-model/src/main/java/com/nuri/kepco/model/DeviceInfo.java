package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceInfo extends CommonObj {

	private String device_id;		
	private String device_serial;
	private String service_id;
	private String branch_id;
	private Integer model_seq;
	private String device_oid;
	private String comm_type;
	private String device_type;
	private String ip;
	private String port;
	private String fw_version;
	private String hw_version;
	private String sw_version1;
	private String sw_version2;
	private String allow_yn;
	private String init_reg_dt;
	private String remark;
	private String reg_id;
	private String reg_dt;
	private String dest_dt;
	private String mobile_no;
	
	private String branch_parent_id;
	private String parent_branch_nm;
	private String branch_nm;
	private String model_nm;
	private String vendor_nm;
	private String code_local_nm;
	private String device_status;
	private String security_mode;
	private String last_comm_dt;
	private String lsdate;
	private String ledate;
	
	private String device_status_nm; // add
	private String device_status_local_nm; // add
	
	
	private long total; // all device
	private long d1; // d1 < 24
	private long d2; // 24 < d2 < 48
	private long d3; // 48 > d3
	private long d4; // not data
	
}

