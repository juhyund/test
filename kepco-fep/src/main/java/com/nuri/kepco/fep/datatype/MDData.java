package com.nuri.kepco.fep.datatype;

import java.util.List;

import com.nuri.kepco.model.MeterInfo;

import lombok.Data;

@Data
public class MDData {
	 
	String deviceSerial; // deviceSerial
	String meterTime; // 미터타임
	String modemTime; // 모뎀타임(검침 시 모뎀시간)
	String meterID;
	String meterOid;
	String meterModel; // 미터 모델
	String meterType; // vendor	
	String billingDate;
	
	MeterInfo meterInfo;
	
	List<LPData> lpDatas;
}