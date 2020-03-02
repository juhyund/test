package com.nuri.kepco.mongo.model;

import java.util.Date;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import lombok.Data;

@Data
@Document(collection="ConnectivityMonitor")
public class ConnectivityMonitor {
	
	@Id
	private String id;
	
	String branchId; // branch id
	String branchNm; // branch name
	String deviceId;
	String deviceSerial;
	String deviceStatus;
	String deviceStatusNm;
	Integer rsrp;	// Radio Signal Strength
	Integer rsrq;	// Link Quality
	String ipAddress;	// 모뎀의 IP 주소 (IPv6)
	Integer cellId;	// Serving Cell ID
	Integer smnc; // Serving Mobile Network Code
	Integer smcc; // Serving Mobile Country Code
	Integer ssnr; // Signal SNR
	
	String usageTime; // 20200224000000
	String saveTime; // 20200224000000
	
	// 조회조건
	private Date sdate;
	private Date edate;
	private int page;
	private int row;
	
	private long offset;
	
	public void setOffset(long offset) {
		this.offset = offset;
	}
	
	public long getOffset() {
		return (this.page - 1) * this.row;
	}
}
