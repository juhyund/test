package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class BranchInfo extends CommonObj {
	
	private String branch_id;
	private String branch_nm;
	private String branch_parent_id;
	private String use_yn;
	private String remark;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;
}
