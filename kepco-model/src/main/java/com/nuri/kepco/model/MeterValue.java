package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class MeterValue extends CommonObj {

	private String meter_id;
	private String read_dt;
	private String channel;
	private Double meter_value;
	private Double sect_meter_value;
	private String reg_dt;
	
}
