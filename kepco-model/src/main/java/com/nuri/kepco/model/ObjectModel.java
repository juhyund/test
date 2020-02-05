package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;
import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = false)
@Data
public class ObjectModel extends CommonObj {

	private String object_id;
	private String object_nm;
	private String instances;
	private String mandatory;
	private String object_urn;
	private String descr;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;
	
}