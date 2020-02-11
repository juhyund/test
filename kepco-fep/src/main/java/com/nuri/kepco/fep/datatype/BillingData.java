package com.nuri.kepco.fep.datatype;

import lombok.Data;

@Data
public class BillingData {
	
	String read_dt;
	String channel;
	Double value;
}