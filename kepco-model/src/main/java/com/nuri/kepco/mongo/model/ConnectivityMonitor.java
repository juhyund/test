package com.nuri.kepco.mongo.model;

import java.util.Date;

import lombok.Data;

@Data
public class ConnectivityMonitor {
	
	String deviceId;
	String deviceSerial;
	int rsrp;	// Radio Signal Strength
	int rsrq;	// Link Quality
	String ipAddress;	// 모뎀의 IP 주소 (IPv6)
	int cellId;	// Serving Cell ID
	int smnc; // Serving Mobile Network Code
	int smcc; // Serving Mobile Country Code
	int ssnr; // Signal SNR
	
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
