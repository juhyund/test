package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class MeterInfo extends CommonObj {
	
	private String meter_id;
	private String meter_serial;
	private String device_id;
	private String meter_type;
	private String energy_type_code;
	private String meter_phase;
	private String branch_id;
	private String model_seq;
	private String ip;
	private String port;
	private String prog_id;
	private String prog_version;
	private String latitude;
	private String longtitude;
	private String altitude;
	private String reg_dt;
	private String ins_dt;
	private String dest_dt;
	
	private String cosem_device_name;
	private Double acon;
	private Double rcon;
	private String billing_dt;
	private String itime;
	private String mtime;
	private int lp_period;
	private Double pcon;
	private int net_metering;

}
