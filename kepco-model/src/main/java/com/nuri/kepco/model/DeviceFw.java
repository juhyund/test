package com.nuri.kepco.model;

import com.nuri.kepco.model.common.CommonObj;

import lombok.Data;

@Data
public class DeviceFw extends CommonObj {
	private int fw_id;
	private String fw_nm;
	private String fw_file_nm;
	private String fw_version;
	private String fw_file_path;
	private String fw_pkg_uri;
	private String fw_biuld_no;
	private String remark;
	private int use_yn;
	private String reg_id;
	private String reg_dt;
	private String update_id;
	private String update_dt;
}
