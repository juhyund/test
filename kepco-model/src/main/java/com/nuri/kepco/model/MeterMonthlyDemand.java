package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class MeterMonthlyDemand extends CommonObj {
	
	private String meter_id;
	private String read_dt;
	private Double active_pwr_tot;
	private Double active_pwr_time;
	private Double active_pwr_cum;
	private Double active_pwr_rate1;
	private Double active_pwr_time_rate1;
	private Double active_pwr_cum_rate1;
	private Double active_pwr_rate2;
	private Double active_pwr_time_rate2;
	private Double active_pwr_cum_rate2;
	private Double active_pwr_rate3;
	private Double active_pwr_time_rate3;
	private Double active_pwr_cum_rate3;
	private Double active_pwr_rate4;
	private Double active_pwr_time_rate4;
	private Double active_pwr_cum_rate4;
	private Double apparent_pwr_total;
	private Double apparent_pwr_time;
	private Double apparent_pwr_cum;
	private Double apparent_pwr_rate1;
	private Double apparent_pwr_time_rate1;
	private Double apparent_pwr_cum_rate1;
	private Double apparent_pwr_rate2;
	private Double apparent_pwr_time_rate2;
	private Double apparent_pwr_cum_rate2;
	private Double apparent_pwr_rate3;
	private Double apparent_pwr_time_rate3;
	private Double apparent_pwr_cum_rate3;
	private Double apparent_pwr_rate4;
	private Double apparent_pwr_time_rate4;
	private Double apparent_pwr_cum_rate4;
	private Double reg_dt;
	private String update_dt;

}
