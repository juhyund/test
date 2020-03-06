package com.nuri.kepco.mongo.model;

import java.util.Date;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import lombok.Data;

@Data
@Document(collection="CpuUsageMonitor")
public class CpuUsageMonitor {
	
	@Id
	private String id;
	
	private String branchId; // branch id
	private String branchNm; // branch name
	private String deviceId;
	private String deviceSerial;
	private Integer cpuUsage;
	private String deviceStatus; // 단말상태
	private String deviceStatusNm;
	private String usageTime; // usage 수신 시간(통신일자)
	private String saveTime; // 서버 저장 시간
	
	// 조회조건
	private String sdate;
	private String edate;
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

