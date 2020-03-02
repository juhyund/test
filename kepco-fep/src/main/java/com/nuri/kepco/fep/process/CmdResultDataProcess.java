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
public class CmdResultDataProcess implements ApplicationContextAware {

	private ApplicationContext applicationContext;

	private static final Logger LOG = LoggerFactory.getLogger(MeasurementData.class);

	/**
	 * process - queue로 부터 수신된 데이터를 처리한다.
	 * 
	 * @param message
	 */
	public void process(String message) {

		Gson gson = new Gson();

		try {

			ResultMessage resultMessage = new ResultMessage();
			resultMessage = gson.fromJson(message, ResultMessage.class);
			
			MeasurementData md = new MeasurementData();
			String deviceId = resultMessage.getDeviceId();
			Date modemTime = resultMessage.getResultTime(); // 수신시간을 모뎀시간으로 저장한다.
			
			md.setDeviceId(deviceId);
			md.setModemTime(modemTime);
			md.setMeterDataParser("com.nuri.kepco.fep.parser.CmdResultDataParser");
			
			// parser
			md.decode(resultMessage);
			
			// saver
			AbstractMDSaver saver = (AbstractMDSaver) applicationContext.getBean("cmdResultDataSaver");
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
