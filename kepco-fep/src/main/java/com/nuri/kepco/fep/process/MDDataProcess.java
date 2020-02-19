package com.nuri.kepco.fep.process;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeansException;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.stereotype.Service;

import com.google.gson.Gson;
import com.nuri.kepco.fep.datatype.ResultMessage;
import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.MeasurementData;
import com.nuri.kepco.fep.mddata.MeterDataParser;

@Service
public class MDDataProcess implements ApplicationContextAware  {
	
	private ApplicationContext applicationContext;
	
	@Value("${mddata.saver.class}")
	private String saverClassName;
	
	private static final Logger LOG = LoggerFactory.getLogger(MeasurementData.class);
	
	public void process(String message) {
		
		Gson gson = new Gson();
		
		ResultMessage resultMessage = new ResultMessage();
		resultMessage = gson.fromJson(message, ResultMessage.class);
		String payload = resultMessage.getPayload();
		String deviceId = resultMessage.getDeviceId();
		
		MeasurementData md = new MeasurementData();	
		
		try {
			
			md.setDeviceId(deviceId);
			md.setMeterDataParser();
			md.decode(payload);
			
			AbstractMDSaver saver = (AbstractMDSaver)applicationContext.getBean(saverClassName);
			
			saver.save(md);
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void setApplicationContext(ApplicationContext applicationContext) throws BeansException {
		this.applicationContext = applicationContext;
	}	
}