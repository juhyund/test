package com.nuri.kepco.mongo.model;

import java.util.Date;

import lombok.Data;

@Data
public class CpuUsageMonitor {
	
	String deviceId;
	String deviceSerial;
	int cpuUsage;
	String usageTime; // usage 수신 시간
	String saveTime; // 서버 저장 시간
	
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

