package com.nuri.kepco;

import java.util.ArrayList;
import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.model.dao.MeterValueDAO;
import com.nuri.kepco.mongo.model.RamUsageMonitor;
import com.nuri.kepco.mongo.model.dao.RamUsageMonitorDAO;

@RunWith(SpringRunner.class)
@SpringBootTest
public class MeterValueTest {
	
	@Autowired
	MeterValueDAO meterValueDAO;
	
	@Autowired
	RamUsageMonitorDAO ramUsageMonitorDAO;
	
	
	public void test() {
		
		List<MeterValue> meterValues = new ArrayList<MeterValue>();
		MeterValue meterValue1 = new MeterValue();
		
		meterValue1.setMeter_id("MT00000001");
		meterValue1.setRead_dt("20200205010103");
		meterValue1.setChannel("CH001");
		meterValue1.setMeter_value(0.0);
		meterValue1.setSect_meter_value(0.0);
		
		meterValues.add(meterValue1);
		
		MeterValue meterValue2 = new MeterValue();
		
		meterValue2.setMeter_id("MT00000001");
		meterValue2.setRead_dt("20200205010104");
		meterValue2.setChannel("CH001");
		meterValue2.setMeter_value(0.0);
		meterValue2.setSect_meter_value(0.0);
		
		meterValues.add(meterValue2);
		
		System.out.println(meterValues.size());
		
		
		meterValueDAO.insertAll(meterValues);
	}
	
	@Test
	public void RamUsagetest() {
		RamUsageMonitor ramUsage = new RamUsageMonitor();
		ramUsage.setDeviceSerial("LJWOO");
		ramUsage.setDeviceId("GW00000012");
				
		List<RamUsageMonitor> list = null;
		try {
			list = this.ramUsageMonitorDAO.getRamUsageMonitor(ramUsage);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		System.out.println("getRamUsageMonitor  : "+ list.size());
		
		
	}
}
