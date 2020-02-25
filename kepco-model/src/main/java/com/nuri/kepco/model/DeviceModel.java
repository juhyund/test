package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceModel extends CommonObj {

	private Integer model_seq;
	private String model_nm;
	private Integer vendor_seq;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;

}
