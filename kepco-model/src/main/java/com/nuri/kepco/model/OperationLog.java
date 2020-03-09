package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class OperationLog extends CommonObj {

	private String device_id;
	private String device_serial;
	private String request_dt;
	private String service_id;
	private String method;
	private Integer object_id;
	private Integer object_instance_id;
	private Integer resource_id;
	private Integer resource_instance_id;
	private String format;
	private String token;
	private String mid;
	private String tid;
	private String payload;
	private String target_meter;
	private Integer result;
	private String result_dt;
	private String _request_dt;
	private String reg_id;
	private String object_nm;
	private String resource_nm;
	private String method_type;
	private String result_status;
	
	private String request_sdate;
	private String request_edate;
	private String result_sdate;
	private String result_edate;
	
	private String m_type;
	private int succ_cnt;
	private int fail_cnt;
	private int wait_cnt;
}
