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
public class MDDataProcess implements ApplicationContextAware {

	private ApplicationContext applicationContext;

	private static final Logger LOG = LoggerFactory.getLogger(MeasurementData.class);

	// method type
	private static final String DATAPUSH = "DATAPUSH";
	private static final String OBJECTLINK = "OBJECTLINK";
	private static final String NOTIFICATION = "NOTIFICATION";

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

			String payload = resultMessage.getPayload();
			String deviceId = resultMessage.getDeviceId();
			Date modemTime = resultMessage.getResultTime(); // 수신시간을 모뎀시간으로 저장한다.
			String method = resultMessage.getMethod();

			MeasurementData md = new MeasurementData();

			LOG.debug("### deviceId : [{}] payload : [{}]", deviceId, payload);
			LOG.debug("### deviceId : [{}] method : [{}] modemTime : [{}] ", deviceId, method, modemTime);

			String parserClassName = getParserClassName(method);
			String saverClassName = getSaverClassName(method);

			if (!"".equals(saverClassName)) {

				AbstractMDSaver saver = (AbstractMDSaver) applicationContext.getBean(saverClassName);

				md.setDeviceId(deviceId);
				md.setModemTime(modemTime);
				md.setMeterDataParser(parserClassName);
				md.decode(payload);

				saver.save(md);
			}

		} catch (Exception e) {
			LOG.error("error", e);
		}
	}

	public String getSaverClassName(String method) {

		String saverClassName = "";

		if (DATAPUSH.equals(method)) {
			saverClassName = "kepcoMDDataSaver";
		} else if (OBJECTLINK.equals(method)) {
			saverClassName = "objectLinkDataSaver";
		} else if (NOTIFICATION.equals(method)) {
			saverClassName = "notifyDataSaver";
		} else {
			saverClassName = "cmdResultDataSaver";	
		}

		return saverClassName;
	}

	public String getParserClassName(String method) {

		String parserClassName = "";

		if (DATAPUSH.equals(method)) {
			parserClassName = "com.nuri.kepco.fep.parser.KepcoMDDataParser";
		} else if (OBJECTLINK.equals(method)) {
			parserClassName = "com.nuri.kepco.fep.parser.ObjectLinkDataParser";
		} else if (NOTIFICATION.equals(method)) {
			parserClassName = "com.nuri.kepco.fep.parser.NotifyDataParser";
		} else {
			parserClassName = "com.nuri.kepco.fep.parser.CmdResultDataParser";
		}

		return parserClassName;
	}

	@Override
	public void setApplicationContext(ApplicationContext applicationContext) throws BeansException {
		this.applicationContext = applicationContext;
	}

}
