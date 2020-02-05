package com.nuri.emi.fep.config;

public class Constants { 
	
	public static boolean LITTLE_ENDIAN = true;
	
	// PAGING
	public static final int LIST_ROWS = 10;
	public static final int FETCH_SIZE = 25;
	public static final int MOBILE_LIST_ROWS = 4;
	public static final int MOBILE_FETCH_SIZE = 10;
	
	public static final int SESSION_KEEP_ALIVE = -1;
	
	
	public static final String BaseDir = "/ewsn-app";
	
	public static final String BaseHomeDir = BaseDir + "/webapp"; 

	public static final String LOG_PATH = "/web/project/HaanAPP/LOGS";
	
	public static final String FileAllowExt = "xls|XLS";
	
	public static final String BaseFileUploadDir = BaseHomeDir + "/files";
	
	public static final String FileUploadDir = BaseFileUploadDir + "/upload";
	
	public static final String FileDownloadDir = BaseFileUploadDir + "/download";
	
	public static final String FileTemplateDir = BaseFileUploadDir + "/template";
	
	public enum WeekDay{
        Sunday("0","일","Sun"),       
        Monday("1","월","Mon"),       
        Tuesday("2","화","Tue"),      
        Wednesday ("3","수","Wed"),   
        Thursday ("4","목","Thu"),   
        Friday ("5","금","Fri"),      
        Saturday ("6","토","Sat");
        
        
        private String code;
        private String kor;
        private String eng;
        
        WeekDay(String code,String kor,String eng) {
            this.code = code;
            this.kor = kor;
            this.eng = eng;
        }
        
        public String getCode() {
            return this.code;
        }
        public String getKorName() {
            return this.kor;
        }
        public String getEngName() {
            return this.eng;
        }
    }
	
}