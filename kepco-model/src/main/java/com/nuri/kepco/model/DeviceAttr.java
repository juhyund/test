package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceAttr extends CommonObj {

	private String attr_policy_seq;
	private String device_id;
	private String object_id;
	private String object_instance_id;
	private String resource_id;
	private String pmin;
	private String pmax;
	private String step;
	private String snot;
	private String hrep;
	private String hmax;
	private String hrst;
	private String ntype;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;

}
