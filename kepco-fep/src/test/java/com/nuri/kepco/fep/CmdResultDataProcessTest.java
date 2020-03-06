package com.nuri.kepco.fep;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.fep.process.CmdResultDataProcess;

@RunWith(SpringRunner.class)
@SpringBootTest
public class CmdResultDataProcessTest {
	
	@Autowired
	CmdResultDataProcess process;

	@Test
    public void test() {
		
		String json = "{\"deviceId\":\"NURI-PC\",\"tid\":\"12345\",\"method\":\"READ\",\"resource\":\"3\",\"format\":\"JSON\",\"token\":\"58349BB54BECED1B\",\"mid\":\"37736\",\"payload\":\"{\\\"bn\\\":\\\"/3\\\",\\\"e\\\":[{\\\"n\\\":\\\"0/0\\\",\\\"sv\\\":\\\"LeshanDemoDevice\\\"},{\\\"n\\\":\\\"0/1\\\",\\\"sv\\\":\\\"Model 500\\\"},{\\\"n\\\":\\\"0/2\\\",\\\"sv\\\":\\\"LT-500-000-0001\\\"},{\\\"n\\\":\\\"0/3\\\",\\\"sv\\\":\\\"1.0.0\\\"},{\\\"n\\\":\\\"0/9\\\",\\\"v\\\":53},{\\\"n\\\":\\\"0/10\\\",\\\"v\\\":104101},{\\\"n\\\":\\\"0/11/0\\\",\\\"v\\\":0},{\\\"n\\\":\\\"0/13\\\",\\\"v\\\":1.58289915E9},{\\\"n\\\":\\\"0/14\\\",\\\"sv\\\":\\\"+09\\\"},{\\\"n\\\":\\\"0/15\\\",\\\"sv\\\":\\\"Asia/Seoul\\\"},{\\\"n\\\":\\\"0/16\\\",\\\"sv\\\":\\\"U\\\"},{\\\"n\\\":\\\"0/17\\\",\\\"sv\\\":\\\"demo\\\"},{\\\"n\\\":\\\"0/18\\\",\\\"sv\\\":\\\"1.0.1\\\"},{\\\"n\\\":\\\"0/19\\\",\\\"sv\\\":\\\"1.0.2\\\"},{\\\"n\\\":\\\"0/20\\\",\\\"v\\\":6},{\\\"n\\\":\\\"0/21\\\",\\\"v\\\":131072}]}\",\"result\":true,\"requestTime\":\"20200228231230\",\"resultTime\":\"Feb 28, 2020, 11:12:30 PM\"}";
		
		process.process(json);

		System.out.println("test");		
    }
	
}
