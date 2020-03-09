package com.nuri.kepco.fep;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.fep.process.MDDataProcess;

@RunWith(SpringRunner.class)
@SpringBootTest
public class ObjectLinkParserTest {
	
	@Autowired
	MDDataProcess process;

	@Test
    public void test() {
		
//		String json = "{\"deviceId\":\"LG\",\"method\":\"OBJECTLINK\",\"resource\":\"/5/0\",\"format\":\"JSON\",\"token\":\"B83366C180709BE3\",\"mid\":\"23749\",\"payload\":\"{\\\"bn\\\":\\\"/5/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"1\\\",\\\"sv\\\":\\\"\\\"},{\\\"n\\\":\\\"3\\\",\\\"v\\\":0},{\\\"n\\\":\\\"5\\\",\\\"v\\\":0},{\\\"n\\\":\\\"6\\\",\\\"sv\\\":\\\"\\\"},{\\\"n\\\":\\\"7\\\",\\\"sv\\\":\\\"\\\"},{\\\"n\\\":\\\"8\\\",\\\"v\\\":0},{\\\"n\\\":\\\"9\\\",\\\"v\\\":0}]}\"}";
		
		String json = "{\"deviceId\":\"01220885233\",\"method\":\"OBJECTLINK\",\"resource\":\"/3/0\",\"format\":\"JSON\",\"token\":\"DC5B74A96DE3CD6A\",\"mid\":\"23748\",\"payload\":\"{\\\"bn\\\":\\\"/3/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"0\\\",\\\"sv\\\":\\\"04\\\"},{\\\"n\\\":\\\"1\\\",\\\"sv\\\":\\\"Model 500\\\"},{\\\"n\\\":\\\"2\\\",\\\"sv\\\":\\\"LT-500-000-0001\\\"},{\\\"n\\\":\\\"3\\\",\\\"sv\\\":\\\"1.0.0\\\"},{\\\"n\\\":\\\"9\\\",\\\"v\\\":41},{\\\"n\\\":\\\"10\\\",\\\"v\\\":3223},{\\\"n\\\":\\\"11/0\\\",\\\"v\\\":0},{\\\"n\\\":\\\"13\\\",\\\"v\\\":1.583773696E9},{\\\"n\\\":\\\"14\\\",\\\"sv\\\":\\\"Z\\\"},{\\\"n\\\":\\\"15\\\",\\\"sv\\\":\\\"GMT\\\"},{\\\"n\\\":\\\"16\\\",\\\"sv\\\":\\\"U\\\"},{\\\"n\\\":\\\"17\\\",\\\"sv\\\":\\\"Demo\\\"},{\\\"n\\\":\\\"18\\\",\\\"sv\\\":\\\"1.0.1\\\"},{\\\"n\\\":\\\"19/1\\\",\\\"sv\\\":\\\"1.2.5\\\"},{\\\"n\\\":\\\"19/2\\\",\\\"sv\\\":\\\"0.0.36\\\"},{\\\"n\\\":\\\"20\\\",\\\"v\\\":0},{\\\"n\\\":\\\"21\\\",\\\"v\\\":8192}]}\"}";
		
		
		process.process(json);
    }
	
}
