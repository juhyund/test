package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceResource extends CommonObj {

	private String device_id;
	private String resource_path;
	private String object_id;
	private String object_instance_id;
	private String resource_id;
	private String resource_instance_id;
	private String resource_val;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;
	
	private String object_nm;
	private String resource_nm;
	private String operation;
	private int instances = -1;
	private int mandatory;
	private String unit;
	private String descr;
}