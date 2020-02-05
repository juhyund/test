package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceSecurity extends CommonObj {
	
	private String device_id;
	private String security_mode;
	private String identity;
	private String psk;
	private String x_pub_key;
	private String y_pub_key;
	private String ec_param;
	private String cert;
	private String prik;
	private String issue_date;
	private String cert_issue_dt;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;
}
