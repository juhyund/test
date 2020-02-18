package com.nuri.kepco.util;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.TimeZone;


public class DateUtil {
	
	public static String getNowDate() {		
		
		Calendar _calendar = Calendar.getInstance();		
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
		
		return dateFormat.format(_calendar.getTime());
	}
	
	public static String getNowDate(String format) {		
		
		if("".equals(format) || format == null) format = "yyyyMMdd";		
		
		Calendar _calendar = Calendar.getInstance();		
		SimpleDateFormat dateFormat = new SimpleDateFormat(format);
		
		return dateFormat.format(_calendar.getTime());
	}
	
	public static String getNowDateTime() {		
		
		Calendar _calendar = Calendar.getInstance();		
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMddHHmmss");
		
		return dateFormat.format(_calendar.getTime());
	}
	
	
	public static String getDateTimeFormat() {		
		
		Calendar _calendar = Calendar.getInstance();		
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		
		return dateFormat.format(_calendar.getTime());
	}
	
	public static Calendar getCalendar(){
		Calendar _calendar = new GregorianCalendar(TimeZone.getTimeZone("GMT+09:00"), Locale.KOREA);
		_calendar.setTime(new Date());		
		return _calendar;
	}
	
	public static String GetYear(){
		
		Calendar _calendar = Calendar.getInstance();
		
		return  FormatUtil.DateForm(String.valueOf(_calendar.get(Calendar.YEAR)), 4);
	}
	
	public static String GetMonth(){
		
		Calendar _calendar = Calendar.getInstance();
		
		return  FormatUtil.DateForm(String.valueOf(_calendar.get(Calendar.MONTH)+1), 2);
	}
	
	public static String GetDay(){
		
		Calendar _calendar = Calendar.getInstance();
		
		return  FormatUtil.DateForm(String.valueOf(_calendar.get(Calendar.DATE)), 2);
	}
	

	public static String GetToday(){
		
		Calendar _calendar = Calendar.getInstance();
		
		return  FormatUtil.DateForm(String.valueOf(_calendar.get(Calendar.YEAR)), 4)+
				FormatUtil.DateForm(String.valueOf(_calendar.get(Calendar.MONTH)+1), 2)+
				FormatUtil.DateForm(String.valueOf(_calendar.get(Calendar.DATE)), 2);
	}  
	
	public static Calendar getCalendar(String strDate){
		Calendar _calendar = new GregorianCalendar(TimeZone.getTimeZone("GMT+09:00"), Locale.KOREA);
		_calendar.setTime(StringUtil.Str2Date(strDate));		
		return _calendar;
	}
	
	public static String getWeekName(String locale) {
		
		Calendar _calendar = Calendar.getInstance();
		String _return = "";
		
		if(locale.equals("KOR")) {
			
			switch(_calendar.get(Calendar.DAY_OF_WEEK)) {
				
				case 1:
					_return = "일";
					break;
					
				case 2:
					_return = "월";
					break;
					
				case 3:
					_return = "화";
					break;
					
				case 4:
					_return = "수";
					break;
					
				case 5:
					_return = "목";
					break;
					
				case 6:
					_return = "금";
					break;
					
				case 7:
					_return = "토";
					break;				
			}			
		} else {
			
			switch(_calendar.get(Calendar.DAY_OF_WEEK)) {			
				case 1:
					_return = "SUN";
					break;
					
				case 2:
					_return = "MON";
					break;
					
				case 3:
					_return = "TUE";
					break;
					
				case 4:
					_return = "WED";
					break;
					
				case 5:
					_return = "THU";
					break;
					
				case 6:
					_return = "FRI";
					break;
					
				case 7:
					_return = "SAT";
					break;				
			}			
		}		
		return _return;
	}
	
	public static String getNextDate(String DATESTR, int days) {		
		
		Calendar _calendar = getCalendar(DATESTR);
		Date d = _calendar.getTime();
		Date _return  = new Date();
		long _return_long = d.getTime() + ((long)1000 * 60 * 60 * 24 * days );
		_return.setTime(_return_long);
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		return sdf.format(_return);
	}
	
	public static String getNextDate(int days) {
		
		Calendar _calendar = getCalendar();		
		Date d = _calendar.getTime();
		Date _return  = new Date();
		long _return_long = d.getTime() + ((long)1000 * 60 * 60 * 24 * days );
		_return.setTime(_return_long);
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		return sdf.format(_return);

	}
	
	public static String getPrevDate(String DATESTR, int days) {		
		
		Calendar _calendar = getCalendar(DATESTR);
		Date d = _calendar.getTime();
		Date _return  = new Date();
		long _return_long = d.getTime() - ((long)1000 * 60 * 60 * 24 * days );
		_return.setTime(_return_long);
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		return sdf.format(_return);
	}
	
	public static String getPrevDate(int days) {
		
		Calendar _calendar = getCalendar();		
		Date d = _calendar.getTime();
		Date _return  = new Date();
		long _return_long = d.getTime() - ((long)1000 * 60 * 60 * 24 * days );
		_return.setTime(_return_long);
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		return sdf.format(_return);
	}
		
	public static String getBetweenDays(String strDate1, String strDate2) {
		
		Calendar _calendar1 = getCalendar(strDate1);		
		Date date1 = _calendar1.getTime();
		
		Calendar _calendar2 = getCalendar(strDate2);		
		Date date2 = _calendar2.getTime();
		
		long _return_long = date2.getTime() - date1.getTime();
		_return_long = (_return_long / ((long)1000 * 60 * 60 * 24));
		
		return String.valueOf(_return_long);
	}
	
	public static String getLastMonth() {
		Calendar _calendar = getCalendar();
		_calendar.roll(Calendar.MONTH, -1);
		Date d = _calendar.getTime();
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMM");
		return sdf.format(d);
	}
	
	public static String getLastDay() {		
		Calendar _calendar = getCalendar();
		_calendar.set(_calendar.get(Calendar.YEAR), _calendar.get(Calendar.MONTH), 1);
		_calendar.add(Calendar.DAY_OF_MONTH, -1);
		return String.valueOf(_calendar.get(Calendar.DAY_OF_MONTH));
	}	
}
