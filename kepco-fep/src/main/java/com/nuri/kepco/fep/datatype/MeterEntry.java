package com.nuri.kepco.fep.datatype;

public class MeterEntry {
	
	public enum METERENTRY {
    	
		METERID(2, "MeterID"),
		COSEMDEVICENAME(3, "Cosem Device Name"),
		STATUS(4, "Status"),
		ACON(5, "ACON"),
		RCON(6, "RCON"),
		MRD(7, "MRD"),
		ITIME(8, "ITime"),
		MTIME(9, "MTime"),
		LPPERIOD(10, "LP_Period"),
		PCON(11, "PCON"),
		NETMETERING(12, "Net Metering");
    	
        private Integer code;
        private String value;
        
        METERENTRY(Integer code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public Integer getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static METERENTRY getType(String code) {
            for (METERENTRY type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
}

