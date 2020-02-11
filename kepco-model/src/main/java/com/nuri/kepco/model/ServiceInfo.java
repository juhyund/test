package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class ServiceInfo extends CommonObj {
	
	private String service_id;
	private String service_nm;
	private String comp_seq;
	private String descr;
	private String status_cd;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;

}
