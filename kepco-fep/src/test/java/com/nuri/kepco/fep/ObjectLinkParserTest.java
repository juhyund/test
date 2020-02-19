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
		
		String json = "{\"deviceId\":\"LG\",\"method\":\"OBJECTLINK\",\"resource\":\"/3/0\",\"format\":\"JSON\",\"token\":\"DC76D9E1C6731F6C\",\"mid\":\"23748\",\"payload\":\"{\\\"bn\\\":\\\"/3/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"0\\\",\\\"sv\\\":\\\"Leshan Demo Device\\\"},{\\\"n\\\":\\\"1\\\",\\\"sv\\\":\\\"Model 500\\\"},{\\\"n\\\":\\\"2\\\",\\\"sv\\\":\\\"LT-500-000-0001\\\"},{\\\"n\\\":\\\"3\\\",\\\"sv\\\":\\\"1.0.0\\\"},{\\\"n\\\":\\\"9\\\",\\\"v\\\":22},{\\\"n\\\":\\\"10\\\",\\\"v\\\":110002},{\\\"n\\\":\\\"11/0\\\",\\\"v\\\":0},{\\\"n\\\":\\\"13\\\",\\\"v\\\":1.582013855E9},{\\\"n\\\":\\\"14\\\",\\\"sv\\\":\\\"+09\\\"},{\\\"n\\\":\\\"15\\\",\\\"sv\\\":\\\"Asia/Seoul\\\"},{\\\"n\\\":\\\"16\\\",\\\"sv\\\":\\\"U\\\"},{\\\"n\\\":\\\"17\\\",\\\"sv\\\":\\\"Demo\\\"},{\\\"n\\\":\\\"18\\\",\\\"sv\\\":\\\"1.0.1\\\"},{\\\"n\\\":\\\"19\\\",\\\"sv\\\":\\\"1.0.2\\\"},{\\\"n\\\":\\\"20\\\",\\\"v\\\":1},{\\\"n\\\":\\\"21\\\",\\\"v\\\":118784}]}\"}";
		
		
		process.process(json);
    }
	
}
