package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class VendorInfo extends CommonObj {
	
	private int vendor_seq;
	private String vendor_code;
	private String vendor_nm;
	private String remark;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;

}
