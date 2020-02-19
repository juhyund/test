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
		
		String json = "{\"deviceId\":\"LG\",\"method\":\"OBJECTLINK\",\"resource\":\"/3/0\",\"format\":\"JSON\",\"token\":\"DC76D9E1C6731F6C\",\"mid\":\"23748\",\"payload\":\"{\\\"bn\\\":\\\"/31004\\\",\\\"e\\\":[{\\\"n\\\":\\\"85/2\\\",\\\"sv\\\":\\\"08460002685\\\"},{\\\"n\\\":\\\"85/3\\\",\\\"sv\\\":\\\"\\\"},{\\\"n\\\":\\\"85/4\\\",\\\"sv\\\":\\\"\\\"},{\\\"n\\\":\\\"85/5\\\",\\\"v\\\":1},{\\\"n\\\":\\\"85/6\\\",\\\"v\\\":1},{\\\"n\\\":\\\"85/7\\\",\\\"sv\\\":\\\"15\\\"},{\\\"n\\\":\\\"85/8\\\",\\\"sv\\\":\\\"Tue Feb 18 10:49:10 KST 2020\\\"},{\\\"n\\\":\\\"85/9\\\",\\\"sv\\\":\\\"Tue Feb 18 10:49:10 KST 2020\\\"},{\\\"n\\\":\\\"85/10\\\",\\\"v\\\":15},{\\\"n\\\":\\\"85/11\\\",\\\"v\\\":1},{\\\"n\\\":\\\"85/12\\\",\\\"v\\\":0},{\\\"n\\\":\\\"35/2\\\",\\\"sv\\\":\\\"08380000935\\\"},{\\\"n\\\":\\\"35/3\\\",\\\"sv\\\":\\\"\\\"},{\\\"n\\\":\\\"35/4\\\",\\\"sv\\\":\\\"\\\"},{\\\"n\\\":\\\"35/5\\\",\\\"v\\\":1},{\\\"n\\\":\\\"35/6\\\",\\\"v\\\":1},{\\\"n\\\":\\\"35/7\\\",\\\"sv\\\":\\\"15\\\"},{\\\"n\\\":\\\"35/8\\\",\\\"sv\\\":\\\"Tue Feb 18 10:49:10 KST 2020\\\"},{\\\"n\\\":\\\"35/9\\\",\\\"sv\\\":\\\"Tue Feb 18 10:49:10 KST 2020\\\"},{\\\"n\\\":\\\"35/10\\\",\\\"v\\\":15},{\\\"n\\\":\\\"35/11\\\",\\\"v\\\":1},{\\\"n\\\":\\\"35/12\\\",\\\"v\\\":0}]}\"}";
		
		
		process.process(json);
    }
	
}
