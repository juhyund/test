package com.nuri.kepco.fep.process;

import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeansException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.stereotype.Service;

import com.google.gson.Gson;
import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.MeasurementData;
import com.nuri.kepco.mongo.model.LwM2mEventLog;
import com.nuri.kepco.mongo.model.dao.LwM2mEventLogDAO;

@Service
public class LwM2mEventLogProcess implements ApplicationContextAware {

	private ApplicationContext applicationContext;

	private static final Logger LOG = LoggerFactory.getLogger(LwM2mEventLogProcess.class);
	
	@Autowired
	LwM2mEventLogDAO lwm2mEventLogDAO;

	/**
	 * process - queue로 부터 수신된 데이터를 처리한다.
	 * 
	 * @param message
	 */
	public void process(String message) {

		Gson gson = new Gson();

		try {
			
			LwM2mEventLog lwm2mEventLog = new LwM2mEventLog();
			lwm2mEventLog = gson.fromJson(message, LwM2mEventLog.class);
			
			MeasurementData md = new MeasurementData();
			String deviceId = lwm2mEventLog.getEp();
			
			md.setDeviceId(deviceId);
			md.setMeterDataParser("com.nuri.kepco.fep.parser.LwM2mEventDataParser");
			md.setModemTime(lwm2mEventLog.getDate()); // 모뎀으로 부터 수신한 시간
			md.decode(message);
			
			// saver
			AbstractMDSaver saver = (AbstractMDSaver) applicationContext.getBean("lwM2mEventDataSaver");
			saver.save(md);

		} catch (Exception e) {
			LOG.error("error", e);
		}
	}
	
	@Override
	public void setApplicationContext(ApplicationContext applicationContext) throws BeansException {
		this.applicationContext = applicationContext;
	}
}
