package com.nuri.kepco.fep.datatype;

public class ConnectivityMonitorEntry {
	
	public enum CONNECTIVITYMONITOR {
    	
		RSRP(2, "Radio Signal Strength"),
		RSRQ(3, "Link Quality"),
		IPV6(4, "IPv6"),
		CELLID(8, "Cellid"),
		SMNC(9, "Serving Mobile Network Code"), // SKT : 03, 05, KT : 02, 04, 08, LGU+ : 06
		SMCC(10, "Serving Mobile Country Code"), // 대한민국 : 450
		SSNR(11, "Signal SNR");
		
        private Integer code;
        private String value;
        
        CONNECTIVITYMONITOR(Integer code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public Integer getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static CONNECTIVITYMONITOR getType(String code) {
            for (CONNECTIVITYMONITOR type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
}

