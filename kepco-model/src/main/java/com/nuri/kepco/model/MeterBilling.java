package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class MeterBilling extends CommonObj {
	
	private String meter_id;		
	private String billing_dt;
	private Double active_imp_tot;
	private Double apprent_imp_tot;
	private Double lead_imp_tot;
	private Double lagging_imp_tot;
	private Double pf_imp_tot;
	private Double active_imp_rate1;
	private Double apprent_imp_rate1;
	private Double lead_imp_rate1;
	private Double lagging_imp_rate1;
	private Double pf_imp_rate1;
	private Double active_imp_rate2;
	private Double apprent_imp_rate2;
	private Double lead_imp_rate2;
	private Double lagging_imp_rate2;
	private Double pf_imp_rate2;
	private Double active_imp_rate3;
	private Double apprent_imp_rate3;
	private Double lead_imp_rate3;
	private Double lagging_imp_rate3;
	private Double pf_imp_rate3;
	private Double active_imp_rate4;
	private Double apprent_imp_rate4;
	private Double lead_imp_rate4;
	private Double lagging_imp_rate4;
	private Double pf_imp_rate4;
	private Double active_exp_tot;
	private Double apprent_exp_tot;
	private Double lead_exp_tot;
	private Double lagging_exp_tot;
	private Double pf_exp_tot;
	private Double active_exp_rate1;
	private Double apprent_exp_rate1;
	private Double lead_exp_rate1;
	private Double lagging_exp_rate1;
	private Double pf_exp_rate1;
	private Double active_exp_rate2;
	private Double apprent_exp_rate2;
	private Double lead_exp_rate2;
	private Double lagging_exp_rate2;
	private Double pf_exp_rate2;
	private Double active_exp_rate3;
	private Double apprent_exp_rate3;
	private Double lead_exp_rate3;
	private Double lagging_exp_rate3;
	private Double pf_exp_rate3;
	private Double active_exp_rate4;
	private Double apprent_exp_rate4;
	private Double lead_exp_rate4;
	private Double lagging_exp_rate4;
	private Double pf_exp_rate4;
	private Double reg_dt;
	private Double update_dt;
}
