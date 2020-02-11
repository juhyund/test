package com.keymng.restapi.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
/**
 * 
 * @author : shinh5
 * @Date   : 2019. 3. 13.
 * @Version: TAUTHORIZE 테이블의 Entity 객체
 */
@Entity
@Table(name="EMI_AUTH")
public class Authorize {
	
	@Id
	@Column(name="CALLING_ID")
	private String Calling_id;
	
	@Column(name="SYS_TITLE")
	private String Sys_title;
	
	@Column(name="NAS_IP")
	private String Nas_ip;
	
	@Column(name="NAS_PORT")
	private String Nas_port;
	
	@Column(name="FEP_KEY")
	private String Fep_key;
	
	@Column(name="NMS_KEY")
	private String Nms_key;
	
	@Column(name="CREATE_DT")
	private String Create_dt;
	
	@Column(name="MODIFY_DT")
	private String Modify_dt;

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

	public String getNas_ip() {
		return Nas_ip;
	}

	public void setNas_ip(String nas_ip) {
		Nas_ip = nas_ip;
	}

	public String getNas_port() {
		return Nas_port;
	}

	public void setNas_port(String nas_port) {
		Nas_port = nas_port;
	}
	
	public String getFep_key() {
		return Fep_key;
	}

	public void setFep_key(String fep_key) {
		Fep_key = fep_key;
	}

	public String getNms_Key() {
		return Nms_key;
	}

	public void setNms_Key(String nms_Key) {
		Nms_key = nms_Key;
	}

	public String getCreate_dt() {
		return Create_dt;
	}

	public void setCreate_dt(String create_dt) {
		Create_dt = create_dt;
	}

	public String getModify_dt() {
		return Modify_dt;
	}

	public void setModify_dt(String modify_dt) {
		Modify_dt = modify_dt;
	}

	
}
