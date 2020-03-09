package com.nuri.kepco.fep.mddata;

import java.lang.reflect.InvocationTargetException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.datatype.ResultMessage;

@Service
public class MeasurementData implements IMeasurementData {

	private static final Logger LOG = LoggerFactory.getLogger(MeasurementData.class);

	private DataParser parser = null;
	private String deviceId;
	private String modemTime; // 모뎀으로부터 서버가 수신한 시간

	@Override
	public DataParser getMeterDataParser() {
		return this.parser;
	}

	@Override
	public String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(String deviceId) {
		this.deviceId = deviceId;
	}

	@Override
	public String getModemTime() {
		return modemTime;
	}

	public void setModemTime(Date modemTime) {
		if (modemTime != null) {
			SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
			this.modemTime = sdf.format(modemTime);
		}
	}
	
	public void setModemTime(String modemTime) {		
		this.modemTime = modemTime;
	}

	public void setMeterDataParser(String parserClassName) {

		Class<?> clazz;
		try {
			clazz = Class.forName(parserClassName);
			this.parser = (DataParser) clazz.getDeclaredConstructor().newInstance();
		} catch (ClassNotFoundException e) {
			LOG.error("error : ", e);
		} catch (InstantiationException e) {
			LOG.error("error : ", e);
		} catch (IllegalAccessException e) {
			LOG.error("error : ", e);
		} catch (IllegalArgumentException e) {
			LOG.error("error : ", e);
		} catch (InvocationTargetException e) {
			LOG.error("error : ", e);
		} catch (NoSuchMethodException e) {
			LOG.error("error : ", e);
		} catch (SecurityException e) {
			LOG.error("error : ", e);
		}
	}

	public void decode(String data) throws Exception {
		this.parser.parser(data, deviceId, modemTime);
	}
	
	public void decode(ResultMessage resultMessage) throws Exception {
		this.parser.parser(resultMessage, deviceId, modemTime);
	}


}