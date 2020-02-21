package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceResource extends CommonObj {

	private String device_id;
	private String resource_path;
	private Integer object_id;
	private Integer object_instance_id;
	private Integer resource_id;
	private Integer resource_instance_id;
	private String resource_val;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;
	
	private String object_nm;
	private int instances;
	private String descr;
}
