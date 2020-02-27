package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class MeterInfo extends CommonObj {
	
	private String meter_id;
	private String meter_serial;
	private String device_id;
	private String meter_type;
	private String comm_type;	
	private String energy_type_code;
	private String meter_phase;
	private String branch_parent_id;
	private String parent_branch_nm;
	private String branch_id;
	private String branch_nm;
	private Integer model_seq;
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
	private String reg_sdate;
	private String reg_edate;
	
	private String cosem_device_name;
	private Double acon;
	private Double rcon;
	private Double pcon;
	private String billing_dt;
	private String itime;
	private String mtime;
	private int lp_period;
	private int net_metering;
	
	private String allow_yn;
	private String device_serial;
	private int vendor_seq;
	private String vendor_nm;
	private String device_status;
	private String last_comm_dt;
	
	private String vendorCd;	
	private String modelCd;
	
	/**
	 * 미터 모델 정보
	 * @param meterSerial
	 */
	public void setMeterModel() {
		
		if(meter_serial != null) {
			this.vendorCd = meter_serial.substring(0, 2);
			this.modelCd = meter_serial.substring(2, 4);
		}
	}

}

