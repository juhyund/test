package com.nuri.emi.fep.parser;

public class LPChannel {
	
    public enum CHANNEL {
    	
    	CH1("1", "CH001"), // 순방향 유효전력량(total)
    	CH2("2", "CH002"), // 순방향 지상 무효전력량
    	CH3("3", "CH003"), // 순방향 진상 무효전력량
    	CH4("4", "CH004"), // 순방향 피상 전력량
    	CH5("5", "CH005"), // 역방향 유효전력량(total)
    	CH6("6", "CH006"), // 역방향 지상 무효전력량
    	CH7("7", "CH007"), // 역방향 진상 무효전력량
    	CH8("8", "CH008"); // 역방향 피상 전력량
    	
        private String ch;
        private String code;
        
        CHANNEL(String ch, String code) {
            this.ch = ch;
            this.code = code;           
        }
        
        public String getCh() {
            return this.ch;
        }
        
        public String getCode() {
            return this.code;
        }
        
        public static CHANNEL getChannel(String ch) {
            for (CHANNEL channel : values()) {
                if (channel.getCh().equals(ch)) return channel;
            }
            return null;
        }
    }
}