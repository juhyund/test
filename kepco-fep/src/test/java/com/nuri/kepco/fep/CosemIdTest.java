package com.nuri.kepco.fep;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.aimir.util.DataUtil;
import com.aimir.util.Hex;

@RunWith(SpringRunner.class)
@SpringBootTest
public class CosemIdTest {
	

	@Test
    public void test() {
		
		try {
			
//			String cosem = "50535419013031303230322020203230";
			
			                
			
//			byte[] bcosem = Hex.encode(cosem);
			
			byte[] bcosem = "WZT 160501A  130".getBytes();
			
			byte[] bversion1 = new byte[1];
			byte[] bversion2 = new byte[1];
			
			System.out.println(new String(bcosem));
			
			System.out.println(Hex.decode(new String(bcosem).getBytes()));
			
			System.arraycopy(bcosem, 14, bversion1, 0, bversion1.length);			
			System.arraycopy(bcosem, 15, bversion2, 0, bversion2.length);
			
			String version1 = new String(bversion1);
			String version2 = new String(bversion2);
			String version = version1 + "" + version2;
			
			System.out.println("version : " + Integer.parseInt(version));
			
			if(Integer.parseInt(version) >= 30) {
				System.out.println("보안계기");
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
	
}
