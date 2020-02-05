package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;
import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = false)
@Data
public class ResourceModel extends CommonObj {
	
	private String object_id;
	private String object_nm;
	private String resource_id;
	private String resource_nm;
	private String operation;
	private String instances;
	private String mandatory;
	private String data_type;
	private String range;
	private String unit;
	private String descr;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;	
}
