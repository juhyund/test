package com.nuri.kepco.fep.process;

import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.stereotype.Service;

import com.google.gson.Gson;
import com.nuri.kepco.fep.datatype.ResultMessage;
import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.DataParser;
import com.nuri.kepco.fep.mddata.MeasurementData;

@Service
public class MDDataProcess implements ApplicationContextAware  {
	
	private ApplicationContext applicationContext;
	
	private static final Logger LOG = LoggerFactory.getLogger(MeasurementData.class);
	
	public void process(String message) {
		
		String parserClassName = "";
		String saverClassName = "";
		
		Gson gson = new Gson();
		
		ResultMessage resultMessage = new ResultMessage();
		resultMessage = gson.fromJson(message, ResultMessage.class);
		String payload = resultMessage.getPayload();		
		String deviceId = resultMessage.getDeviceId();
		Date modemTime = resultMessage.getResultTime(); // 수신시간을 모뎀시간으로 저장한다.
		String method = resultMessage.getMethod();
		MeasurementData md = new MeasurementData();	
		
		try {
			
			LOG.debug("### deviceId : [{}] payload : [{}]", deviceId, payload);
			LOG.debug("### deviceId : [{}] method : [{}]", deviceId, method);
			
			if("DATAPUSH".equals(method)) {			
				
				parserClassName = "kepcoMDDataParser";
				saverClassName = "kepcoMDDataSaver";
				
			} else if ("OBJECTLINK".equals(method)) {
				
				parserClassName = "objectLinkDataParser";
				saverClassName = "objectLinkDataSaver";
			}
			
			DataParser parser = (DataParser)applicationContext.getBean(parserClassName);
			AbstractMDSaver saver = (AbstractMDSaver)applicationContext.getBean(saverClassName);
						
			md.setDeviceId(deviceId);
			md.setModemTime(modemTime);
			md.setMeterDataParser(parser);
			md.decode(payload);
			
			LOG.debug("parser : {}", parser);
			LOG.debug("saver : {}", saver);
			
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