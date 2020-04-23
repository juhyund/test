package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class ObisCode extends CommonObj {

	private int obis_id;
	private String obis_code;
	private String attribute_no;
	private String attribute_nm;
	private String class_id;
	private String class_nm;
	private String datatype;
	private String access_right;
	private String descr;
	private String meter_type;
	
	private String object_id;
	private String object_instance_id;
	private String metering_type_nm;
	private String obis_cnt;
	private String arr_resource_instance_id;
	private String arr_obis_code;
	private String kepco_object;
	private String kepco_obis;
	
}
