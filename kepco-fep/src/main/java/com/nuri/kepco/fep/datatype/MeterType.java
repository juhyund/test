package com.nuri.kepco.fep.datatype;

public class MeterType {
	
	public enum TYPE {
    	
    	EnergyMeter("ME002", "Energy Meter"); //전기
    	
        private String code;
        private String value;
        
        TYPE(String code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public String getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static TYPE getType(String code) {
            for (TYPE type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
    
    public enum METERTYPE {
    	
    	EType("MT001", "ET-Type"),
    	GType("MT002", "GT-Type"),
    	AEType("MT003", "AE-Type"),
    	UNKNOWN("MT999", "UNKNOWN");
    	
        private String code;
        private String value;
        
        METERTYPE(String code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public String getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static METERTYPE getType(String code) {
            for (METERTYPE type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
    
    public enum DEVICETYPE {
    	
    	METER("C220040", "METER");
    	
        private String code;
        private String value;
        
        DEVICETYPE(String code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public String getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static DEVICETYPE getType(String code) {
            for (DEVICETYPE type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
    
    public enum DEVICESTATUS {
    	
    	NORMAL("C229100", "NORMAL");
    	
        private String code;
        private String value;
        
        DEVICESTATUS(String code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public String getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static DEVICESTATUS getType(String code) {
            for (DEVICESTATUS type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
}
