package com.nuri.kepco.mongo.model;

import java.util.Date;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import lombok.Data;

@Data
@Document(collection="ConnectivityStatisticsMonitor")
public class ConnectivityStatisticsMonitor {
	
	// 최종 통신 데이터만 가지고 있다.
	// device 별 rowdata는 한개 이다.
	@Id
	private String id;
	
	private String branchId; // branch id
	private String branchNm; // branch name
	private String deviceId;
	private String deviceSerial;
	private String deviceStatus; // 단말상태
	private String deviceStatusNm;
	private Integer rsrp;	// Radio Signal Strength
	private Integer rsrq;	// Link Quality
	private String ipAddress;	// 모뎀의 IP 주소 (IPv6)
	private Integer cellId;	// Serving Cell ID
	private Integer smnc; // Serving Mobile Network Code
	private Integer smcc; // Serving Mobile Country Code
	private Integer ssnr; // Signal SNR
	private Integer cpuUsage; // cpu
	private Integer ramUsage; // ram
	
	private String usageTime; // 20200224000000
	private String saveTime; // 20200224000000
	
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
