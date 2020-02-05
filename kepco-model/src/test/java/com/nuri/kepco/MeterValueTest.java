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

@RunWith(SpringRunner.class)
@SpringBootTest
public class MeterValueTest {
	
	@Autowired
	MeterValueDAO meterValueDAO;
	
	@Test
	public void test() {
		
		List<MeterValue> meterValues = new ArrayList<MeterValue>();
		MeterValue meterValue1 = new MeterValue();
		
		meterValue1.setMeter_id("MT0000001");
		meterValue1.setRead_dt("20200205010101");
		meterValue1.setChannel("CH001");
		meterValue1.setMeter_value(0.0);
		meterValue1.setSect_meter_value(0.0);
		
		MeterValue meterValue2 = new MeterValue();
		
		meterValue2.setMeter_id("MT0000001");
		meterValue2.setRead_dt("20200205010101");
		meterValue2.setChannel("CH001");
		meterValue2.setMeter_value(0.0);
		meterValue2.setSect_meter_value(0.0);
		
		meterValues.add(meterValue2);
		
		
		meterValueDAO.insertAll(meterValues);
	}
}
