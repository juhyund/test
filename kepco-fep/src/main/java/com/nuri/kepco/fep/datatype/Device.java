package com.nuri.kepco.fep.datatype;

public class Device {
	
	public enum DEVICE {
    	
		MANUFACTURER(0, "Manufacturer"),
		MODELNUMBER(1, "Model Number"),
		SERIALNUMBER(2, "Serial Number"),
		FWVERSION(3, "Firmware Version"),
		AVAILABLEPOWERSOURCES(6, "vailable Power Sources"),
		POWERSOURCEVOLTAGE(7, "Power Source Voltage"),
		MEMORYFREE(10, "Memory Free"),
		ERRORCODE(11, "Error Code"),		
		CURRENTTIME(13, "Current Time"),
		TIMEZONE(16, "Timezone"),
		DEVICETYPE(17, "Device Type"),
		HWVERSION(18, "Hardware Version"),
		SWVERSION(19, "Software Version"),
		MEMORYTOTAL(21, "Memory Total");
    	
        private Integer code;
        private String value;
        
        DEVICE(Integer code, String value) {
            this.code = code;
            this.value = value;           
        }
       
        public Integer getCode() {
            return this.code;
        }
        
        public String getValue() {
            return this.value;
        }
        
        public static DEVICE getType(String code) {
            for (DEVICE type : values()) {
                if (type.getCode().equals(code)) return type;
            }
            return null;
        }
    }
}

