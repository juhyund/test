package com.nuri.kepco;

import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

public class PasswordC {
	public static void main(String[] aaa) {
		BCryptPasswordEncoder bcryptPasswordEncoder = new BCryptPasswordEncoder();
		String returnValue1 = bcryptPasswordEncoder.encode("1234");
		 
		System.out.println("returnValue1 : " + returnValue1);
		 
		System.out.println("============================================================================");
		 
		System.out.println("matches() result : " + bcryptPasswordEncoder.matches("password", returnValue1));
	}
}
