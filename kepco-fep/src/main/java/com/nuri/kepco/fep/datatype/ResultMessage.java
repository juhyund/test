package com.nuri.kepco.fep.datatype;

import lombok.Data;

@Data
public class ResultMessage {
	
	String deviceId;
	String tid;
	String method;
	String resource;
	String format;
	String token;
	String mid;
	String payload;
}
