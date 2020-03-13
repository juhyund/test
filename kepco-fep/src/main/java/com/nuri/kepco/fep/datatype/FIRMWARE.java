package com.nuri.kepco.fep.datatype;

public class FIRMWARE {
	
	public enum FIRMWAREUPDATE {
    	
		FIRMWAREPACKAGE(0, "Firmware package"),
		PACKAGEURI(1, "Package URI"),
		UPDATE(2, "Update"),
		STATE(3, "State"),
		UPDATERESULT(5, "Update Result"),
		PACKAGENAME(6, "Package Name"),
		PACKAGEVERSION(7, "Package Version"),
		PROTOCOL(8, "Firmware Update Protocol Support"),
		METHOD(9, "Firmware Update Delivery Method");
		
        private Integer code;
        private String value;
        
        FIRMWAREUPDATE(Integer code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public Integer getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static FIRMWAREUPDATE getType(Integer code) {
            for (FIRMWAREUPDATE type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
	
	
	public enum FIRMWARECODE {
    	
		FW_UPDATE00(0, "FW000"),
		FW_UPDATE01(1, "FW001"),
		FW_UPDATE02(2, "FW002"),
		FW_UPDATE03(3, "FW003"),
		FW_UPDATE04(4, "FW004"),
		FW_UPDATE05(5, "FW005"),
		FW_UPDATE06(6, "FW006"),
		FW_UPDATE07(7, "FW007"),
		FW_UPDATE08(8, "FW008"),
		FW_UPDATE09(9, "FW009");
		
        private Integer code;
        private String value;
        
        FIRMWARECODE(Integer code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public Integer getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static FIRMWARECODE getType(Integer code) {
            for (FIRMWARECODE type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
}

