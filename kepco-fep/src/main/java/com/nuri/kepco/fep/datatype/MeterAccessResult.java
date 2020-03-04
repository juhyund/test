package com.nuri.kepco.fep.datatype;

import java.util.Map;

import lombok.Data;

@Data
public class MeterAccessResult {
	 
	String deviceSerial; // deviceSerial
	String OBIS;
	String APDU;
	String resultMsg;
	Map<Integer, String> meterStatus;

}