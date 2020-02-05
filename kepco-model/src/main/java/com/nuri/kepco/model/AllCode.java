package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class AllCode extends CommonObj {

	private String code;
	private String code_nm;
	private String code_local_nm;
	private String parent_code;
	private String sort;
	private String use_yn;
	private String remark;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;
	private String add_col1;
	private String add_col2;
	private String add_col3;
	private String add_col4;
	private String add_col5;

}
