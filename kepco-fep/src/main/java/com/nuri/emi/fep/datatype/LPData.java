package com.nuri.emi.fep.datatype;

import lombok.Data;

@Data
public class LPData implements Comparable<LPData> {
	
	String read_dt;
	String channel;
	Double value;
	
	@Override
	public int compareTo(LPData obj) {
		LPData lpdata = obj;
		return this.read_dt.compareTo(lpdata.read_dt);
	}
}
