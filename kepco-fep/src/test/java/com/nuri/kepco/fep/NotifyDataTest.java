package com.nuri.kepco.fep;

import java.util.Date;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.fep.process.MDDataProcess;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.dao.CpuUsageMonitorDAO;

@RunWith(SpringRunner.class)
@SpringBootTest
public class NotifyDataTest {
	
	@Autowired
	MDDataProcess process;
	

	@Test
    public void test() {
 
		String json = "{\"deviceId\":\"LG-PC02\",\"method\":\"NOTIFICATION\",\"format\":\"JSON\",\"token\":\"806662840758920E\",\"mid\":\"18966\",\"payload\":\"{\\\"bn\\\":\\\"/4/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"2\\\",\\\"v\\\":-94},{\\\"n\\\":\\\"3\\\",\\\"v\\\":-12},{\\\"n\\\":\\\"4\\\",\\\"sv\\\":\\\"122.199.180.120\\\"},{\\\"n\\\":\\\"8\\\",\\\"v\\\":4},{\\\"n\\\":\\\"9\\\",\\\"v\\\":5},{\\\"n\\\":\\\"10\\\",\\\"v\\\":450},{\\\"n\\\":\\\"11\\\",\\\"v\\\":11}]}\"}";

		process.process(json);
    }
	
}
