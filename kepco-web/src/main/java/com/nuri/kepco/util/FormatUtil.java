package com.nuri.kepco.util;

import java.text.DecimalFormat;
import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class FormatUtil {
	
	public static String NumberFormat(String value) {
		
		String result = "";
		
		String pattern = "###,###,###,###,###.#";
		DecimalFormat dformat = new DecimalFormat(pattern);
		
		if(value.equals("-")){
			result = value;
		}else{
			result = dformat.format(Double.parseDouble(value));
		}
		
		return result;
	}
	
	public static String DateForm(String value, int length) {
		
		String result = "";
		String pattern = "";
		
		for(int i=0; i<length; i++){
			pattern += "0";
		}
		
		DecimalFormat dformat = new DecimalFormat(pattern);		
		result = dformat.format(Double.parseDouble(value));
		
		return result;
		
	}
	
	public static String StringCut(String value, int size) {
		
		String result = "";
		if(value==null || value.equals("")){
			return result;
		}else if(value.length()<size){
			return value;
		}else{
			return value.substring(0, size)+"...";
		}	
	}
	
	public static String HideAccip(String ip) {
		
		String result = "";
				
		int start_idx = 0;
		int last_idx = ip.lastIndexOf(".");
		
		int dot_counter = 0;
		
		for(int i=0; i<ip.length(); i++){
			
			if(ip.charAt(i)=='.'){
				dot_counter++;
			}
			
			if(dot_counter==2){
				start_idx = i;
				break;
			}
		}		
		
		result = ip.substring(0, start_idx+1)+"xxx"+ip.substring(last_idx, ip.length());
		
		return result;		
	}
		
	
	public static String returnNotNullString(String str) {
		return str==null?"":str;
	}
	
	public static String DateFormat(String strDate, int format) {
		
		ParsePosition pp = new ParsePosition(0);
		SimpleDateFormat dateFormat = new SimpleDateFormat();
		
		if(strDate.length() == 14){
			dateFormat.applyPattern("yyyyMMddHHmmss");
		}else if(strDate.length() == 8){
			dateFormat.applyPattern("yyyyMMdd");
		}else{
			return null;
		}
		
		Date date = dateFormat.parse(strDate, pp);		
		String strFormat = "";
		
		switch(format){
			case 1 :				
				strFormat = "yyyy-MM-dd HH:mm:ss";
				break;
			case 2 :
				strFormat = "yyyy/MM/dd HH:mm:ss";
				break;
			case 3 :
				strFormat = "yyyy년 MM월 dd일  HH시 mm분 ss초";
				break;
			case 4 :
				strFormat = "yyyy-MM-dd";
				break;
			case 5 :
				strFormat = "yyyy/MM/dd";
				break;
			case 6 :
				strFormat = "yyyy.MM.dd";
				break;	
			case 7 :
				strFormat = "yyyy시 MM분 dd초";
				break;			
		}
		
		SimpleDateFormat dateFormat2 = new SimpleDateFormat(strFormat);		
        return (dateFormat2.format(date)==null)? "" : dateFormat2.format(date); 
	}
	
	public static String DateFormat(String strDate, String strFormat) {
		
		ParsePosition pp = new ParsePosition(0);
		SimpleDateFormat dateFormat = new SimpleDateFormat();
		
		if(strDate.length() == 14){
			dateFormat.applyPattern("yyyyMMddHHmmss");
		}else if(strDate.length() == 8){
			dateFormat.applyPattern("yyyyMMdd");
		}else{
			return null;
		}
		
		Date date = dateFormat.parse(strDate, pp);		
		
		SimpleDateFormat dateFormat2 = new SimpleDateFormat(strFormat);		
        return (dateFormat2.format(date)==null)? "" : dateFormat2.format(date); 
	}
	
	
	/**
	 * 전화번호 형식 변환
	 * @param tel_no
	 * @return
	 */
	public static String formatTelNo(String tel_no) {
		
		if(tel_no != null && !"".equals(tel_no) && tel_no.length() >= 9) {
			return tel_no.replaceAll("(^02.{0}|^01.{1}|[0-9]{3})([0-9]+)([0-9]{4})", "$1-$2-$3");
		} else {
			return "";
		}
	}
	
	/**
	 * 전화번호 형식 변환
	 * @param tel_no
	 * @return
	 */
	public static String formatTelNo2(String tel_no) {
		
		if(tel_no != null && !"".equals(tel_no) && tel_no.length() >= 9) {
			return tel_no.replaceAll("(^02.{0}|^01.{1}|[0-9]{3})([0-9]+)([0-9]{4})", "$1-$2-$3");
		} else {
			return "Err";
		}
	}
}
