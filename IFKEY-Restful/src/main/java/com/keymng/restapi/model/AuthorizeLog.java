package com.keymng.restapi.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;


/**
 * @author : shinh5
 * @Date   : 2019. 6. 17.
 * @Version: 
 */
@Entity
@Table(name="EMI_AUTHLOG")
public class AuthorizeLog {
	
	
	//4e 54 43 50 18 00 00 01 // 보안 이슈 발생 기기의 시스템 타이틀 (통신시작 기기)
	//30 30 30 00 00 00 00 00  // 통신 대상 기기
	//19 11 19 03 14 53 56 // 발생시간

	//ff // 로그 코드

	@Id
	@Column(name="CALLING_ID")  ///now_dt + systitle
	private String Calling_id;
	
	@Column(name="SYS_TITLE")
	private String Sys_title;
	
	@Column(name="DEVICE_ID")
	private String device_id;
	
	@Column(name="LOG_CD")
	private String log_cd;
	
	@Column(name="RECEIVE_DT")
	private String receive_dt;
	
	@Column(name="WRITE_DT")
	private String write_dt;
	
	public String getCalling_id() {
		return Calling_id;
	}

	public void setCalling_id(String calling_id) {
		Calling_id = calling_id;
	}

	public String getSys_title() {
		return Sys_title;
	}

	public void setSys_title(String sys_title) {
		Sys_title = sys_title;
	}

	public String getDevice_id() {
		return device_id;
	}

	public void setDevice_id(String device_id) {
		this.device_id = device_id;
	}

	public String getLog_cd() {
		return log_cd;
	}

	public void setLog_cd(String log_cd) {
		this.log_cd = log_cd;
	}

	public String getReceive_dt() {
		return receive_dt;
	}

	public void setReceive_dt(String receive_dt) {
		this.receive_dt = receive_dt;
	}

	public String getWrite_dt() {
		return write_dt;
	}

	public void setWrite_dt(String write_dt) {
		this.write_dt = write_dt;
	}

}
