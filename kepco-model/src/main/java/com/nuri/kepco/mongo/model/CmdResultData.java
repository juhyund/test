package com.nuri.kepco.mongo.model;

import java.util.Date;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import lombok.Data;

@Data
@Document(collection="CmdResultData")
public class CmdResultData {
	
	@Id
	private String id;	
	private String deviceId;
	private String tid;
	private String method;
	private String resource; 
	private String format;
	private String token;
	private String mid;
	private String payload;
	private String resultTime;
	private String saveTime;
	private String requestTime;
	private Boolean result;
	
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