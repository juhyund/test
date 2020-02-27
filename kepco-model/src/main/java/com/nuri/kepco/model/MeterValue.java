package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;


import lombok.Data;

@Data
public class MeterValue extends CommonObj {

	private String meter_id;
	private String read_dt;
	private String channel;
	private Double meter_value;
	private Double sect_meter_value;
	private String reg_dt;
	private String device_id;
	private String meter_type;
	
	private String mtime;
	private String itime;
	
	private List<Map<String, Object>> channelList = new ArrayList<Map<String, Object>>();
	private String meter_serial;
	
}

