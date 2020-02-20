package com.nuri.kepco.fep;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.fep.process.MDDataProcess;

@RunWith(SpringRunner.class)
@SpringBootTest
public class NotifyDataTest {
	
	@Autowired
	MDDataProcess process;

	@Test
    public void test() {
 
		String json = "{\"deviceId\":\"LG-PC02\",\"method\":\"NOTIFICATION\",\"format\":\"JSON\",\"token\":\"806662840758920E\",\"mid\":\"18966\",\"payload\":\"{\\\"bn\\\":\\\"/26241/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"10\\\",\\\"v\\\":61}]}\"}";
		
		process.process(json);

		System.out.println("test");		
    }
	
}
