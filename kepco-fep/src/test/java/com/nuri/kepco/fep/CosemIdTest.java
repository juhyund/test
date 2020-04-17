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
			
			String cosem = "50535419013031303230322020203230";
			
			                
			
			byte[] bcosem = Hex.encode(cosem);
			byte[] blogicalDeviceNo = new byte[1];
			byte[] bversion = new byte[1];
			
			System.out.println(new String(bcosem));
			
			System.out.println(Hex.decode(new String(bcosem).getBytes()));
			
			System.arraycopy(bcosem, 14, blogicalDeviceNo, 0, blogicalDeviceNo.length);
			System.arraycopy(bcosem, 15, bversion, 0, bversion.length);
			
			String logicalDeviceNo = new String(blogicalDeviceNo);
			String version = DataUtil.getBCDtoBytes(bversion);
			
			System.out.println("logicalDeviceNo : " + logicalDeviceNo);
			System.out.println("version : " + Integer.parseInt(version));
			
			if(Integer.parseInt(version) >= 30) {
				System.out.println("ddd");
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
	
}
