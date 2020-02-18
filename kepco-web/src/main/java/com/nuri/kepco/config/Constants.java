package com.nuri.kepco.config;

public class Constants { 
	
	// PAGING
	public static final int LIST_ROWS = 10;
	public static final int FETCH_SIZE = 25;
	public static final int MOBILE_LIST_ROWS = 4;
	public static final int MOBILE_FETCH_SIZE = 10;
	
	public static final int SESSION_KEEP_ALIVE = -1;
	
	
	public static final String BaseDir = "/kepco-web";
	
	public static final String BaseHomeDir = BaseDir + "/webapp"; 

	public static final String LOG_PATH = "/web/project/HaanAPP/LOGS";
	
	public static final String FileAllowExt = "xls|XLS";
	
	public static final String BaseFileUploadDir = BaseHomeDir + "/files";
	
	public static final String FileUploadDir = BaseFileUploadDir + "/upload";
	
	public static final String FileDownloadDir = BaseFileUploadDir + "/download";
	
	public static final String FileTemplateDir = BaseFileUploadDir + "/template";
	
}