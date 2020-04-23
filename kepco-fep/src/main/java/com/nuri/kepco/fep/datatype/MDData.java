package com.nuri.kepco.fep.datatype;

import java.util.List;
import java.util.Map;

import com.nuri.kepco.model.MeterBilling;
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
	String meterType; // 미터 타입
	String billingDay; // 정기검침일(monthly billing date)
	String billingDate; // 정기검침일자 (정기검침데이터 포함)
	
	String vendorCd; // vendor
	String meterPhase;
	
	String cosemDeviceName; //cosem 아이디
	String cosemLogicalDevice; // cosem logica device 번호
	String cosemVersion; // 버전
	Double acon; // 유효전력량 계기정수
	Double rcon; // 무효전력량 계기정수
	Double pcon; // 피상전력량 계기정수
	String itime;
	String mtime;
	Integer lpPeriod;
	Integer netMetering; // 양방향
	Integer avgPowerPeriod; // 평균전압전류주기
		
	MeterInfo meterInfo;
	
	List<LPData> lpDatas;
	
	List<MeterBilling> billingImportData;
	
	List<MeterBilling> billingExportData;
	
	List<MeterBilling> eTypeBillingImportData;
	
	Map<String, Object> dynamicDatas;
}