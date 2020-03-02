package com.nuri.kepco.fep.datatype;

import java.util.Date;

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
	Date resultTime;
	String requestTime;
	Boolean result;
}
