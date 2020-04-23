package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;


import lombok.Data;

@Data
public class MeterData extends CommonObj {

	private String meter_id;
	private String read_dt;
	private String obis_code;
	private String mtime;
	private String itime;
	private String payload;

	private String meter_type;
	private String obis_code_descr;
	
}

