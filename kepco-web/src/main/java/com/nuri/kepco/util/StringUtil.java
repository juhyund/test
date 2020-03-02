package com.nuri.kepco.util;

import java.io.UnsupportedEncodingException;
import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.log4j.Logger;

public class StringUtil {
	
	static Logger log = Logger.getLogger("StringUtil.class");
	
	public static String E2K(String str) {
		try {
			if (str == null)
				return "";
			else
				return new String(str.getBytes("8859_1"), "KSC5601");
		} catch (UnsupportedEncodingException e) {
			log.debug("[co.kr.kbsjob.common.util.StringUtil.E2K]", e);
			return null;
		}
	}

	public static String K2U(String str) {
		try {
			if (str == null)
				return "";
			else
				return new String(str.getBytes("KSC5601"), "UTF8");
		} catch (UnsupportedEncodingException e) {
			log.debug("[co.kr.kbsjob.common.util.StringUtil.K2U]", e);
			return null;
		}
	}

	public static String U2K(String str) {
		try {
			if (str == null)
				return "";
			else
				return new String(str.getBytes("UTF8"), "KSC5601");
		} catch (UnsupportedEncodingException e) {
			log.debug("[co.kr.kbsjob.common.util.StringUtil.U2K]", e);
			return null;
		}
	}

	public static String U2E(String str) {
		try {
			if (str == null)
				return "";
			else
				return new String(str.getBytes("UTF8"), "8859_1");
		} catch (UnsupportedEncodingException e) {
			log.debug("[co.kr.kbsjob.common.util.StringUtil.U2E]", e);
			return null;
		}
	}

	public static String E2U(String str) {
		try {
			if (str == null)
				return "";
			else
				return new String(str.getBytes("8859_1"), "UTF8");
		} catch (UnsupportedEncodingException e) {
			log.debug("[co.kr.kbsjob.common.util.StringUtil.E2U]", e);
			return null;
		}
	}

	/**
	 * KSC5601 --> 8859_1.
	 * 
	 * @param korean
	 *            String
	 * @return 8859_1로 변환된 String
	 */
	public static String K2E(String korean) {
		String english = null;

		if (korean == null)
			return null;

		english = new String(korean);
		try {
			english = new String(korean.getBytes("KSC5601"), "8859_1");
		} catch (UnsupportedEncodingException e) {
			log.debug("[co.kr.kbsjob.common.util.StringUtil.K2E]", e);
			english = korean;
		}
		return english;
	}
	
	public static String stripHtmlTag(String text) {
		Pattern p = Pattern.compile("\\<(\\/?)(\\w+)*([^<>]*)>");
   		Matcher m = p.matcher(text);
   		text = m.replaceAll("").trim();		 
   		return text;
	}
	
	public static String RPad(String text, int len, String fillStr) {
		String strPad = "";
		
		for(int i = 0; i < len - text.trim().length(); i++) {
			strPad += fillStr;
		}
		return text.trim() + "" + strPad;
	}
	
	public static String LPad(String text, int len, String fillStr) {
		String strPad = "";
		
		for(int i = 0; i < len - text.trim().length(); i++) {
			strPad += fillStr;
		}
		return strPad + "" + text.trim();
	}
	
	public static Date Str2Date(String strDate) {
	
		Date d = null;		
		try {
			
			SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
			d = sdf.parse(strDate, new ParsePosition(0));
			
		} catch(Exception e) {
			log.debug("[co.kr.kbsjob.common.util.StringUtil.Str2Date]", e);
		}
		
		return d;
	}
	
	// 특수문자 제거
	public static String RemoveSpecialChar(String text, String type) {
		String org_txt = text;

	    String match = "\\s{2,}";
		String match1 = "[^\uAC00-\uD7A3xfe0-9a-zA-Z\\s]";	// 모든 특수문자
		String match2 = "[~!@#$%\\^&*\\(\\)_+`\\-=\\{\\}|\\[\\]\\\\:\\\";\\'\\<\\>?./\\s]";
	    
		text = text.replaceAll(match, "");
		
		if (type.equals("2")) {
			text = text.replaceAll(match2, "");
		} else {
			text = text.replaceAll(match1, "");
		}
		
		return text.trim();
	}
}
