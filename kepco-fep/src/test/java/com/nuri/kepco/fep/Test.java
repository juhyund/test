package com.nuri.kepco.fep;

import java.text.SimpleDateFormat;
import java.util.Base64;
import java.util.Date;

import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.eclipse.leshan.json.LwM2mJson;
import org.eclipse.leshan.json.LwM2mJsonException;

import com.aimir.util.Hex;

public class Test {
	
	public static void main(String[] args) {
		
//		String mobileInfo = "MjA4ODM3NTYgMw==";
//		//System.out.println(Hex.decode(Base64.getDecoder().decode(mobileInfo)));
//		
//		byte[] mdata = Base64.getDecoder().decode(mobileInfo);
//		
//		byte[] mobileNo = new byte[8];
//		System.arraycopy(mdata, 0, mobileNo, 0, mobileNo.length);
//		
//		System.out.println(new String(mobileNo));
		
		
//		String data = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"50F2AE32530128CF\",\"mid\":\"37752\",\"payload\":\"{\\\"bn\\\":\\\"/31012/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"105\\\",\\\"sv\\\":\\\"+/FGITc\\u003d\\\"},{\\\"n\\\":\\\"106\\\",\\\"sv\\\":\\\"+/EhKjk\\u003d\\\"},{\\\"n\\\":\\\"107/78\\\",\\\"v\\\":0}]}\",\"resultTime\":\"Mar 3, 2020, 5:32:27 PM\"}";
		
		
		// 복전
		long l = (long)1.587633052E9;
		
		SimpleDateFormat format = new  SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");		
		System.out.println("복전ti : " + format.format(new Date(l* 1000)));
		
		
		// 정전
		long l2 = (long)1.587633063E9;				
		System.out.println("정전 : " +format.format(new Date(l2* 1000)));
		
	
		
		
//		String result = "";
//		String frame = "{\"bn\":\"/26243/0/21\",\"e\":[{\"n\":\"\",\"sv\":\"0.68/0.15\"}]}";
//		try {
//			JsonRootObject jsonObject = LwM2mJson.fromJsonLwM2m(frame);			
//			for (JsonArrayEntry e : jsonObject.getResourceList()) {
//				String[] str = e.getStringValue().split("/");
//				System.out.println(str[0]);
//				System.out.println(str[1]);
//				
//			}
//			
//			System.out.println(result);
//			
//			
//		} catch (LwM2mJsonException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
	}
}
