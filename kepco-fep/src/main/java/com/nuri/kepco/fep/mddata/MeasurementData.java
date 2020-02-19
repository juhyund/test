package com.nuri.kepco.fep.mddata;

import java.text.SimpleDateFormat;
import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.stereotype.Service;

@Service
public class MeasurementData implements IMeasurementData {
	
	private static final Logger LOG = LoggerFactory.getLogger(MeasurementData.class);	
	
	private DataParser parser = null;
	private String deviceId;
	private String modemTime;
		
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
		if(modemTime != null) {
	        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
			this.modemTime = sdf.format(modemTime);
		}
	}
	
	public void setMeterDataParser(DataParser parser) {
		this.parser = parser;
	}
	
	public void decode(String data) throws Exception
    {			
		this.parser.parser(data);
    }

}
