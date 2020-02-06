package com.nuri.kepco.fep.mddata;

import java.lang.reflect.InvocationTargetException;
import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.parser.KepcoMDDataParser;

@Service
public class MeasurementData implements IMeasurementData {
	
	private static final Logger LOG = LoggerFactory.getLogger(MeasurementData.class);
	
	private String parserClassName = "com.nuri.kepco.fep.parser.KepcoMDDataParser";
	
	private MeterDataParser parser = null;
	private String deviceId;
	private String modemTime;
	
	@Override
	public MeterDataParser getMeterDataParser() {
		return this.parser;
	}
	@Override
	public String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(String deviceId) {
		this.deviceId = deviceId;
	}

	public String getModemTime() {
		return modemTime;
	}

	public void setModemTime(String modemTime) {
		this.modemTime = modemTime;
	}
	
	public void setMeterDataParser() {
		
		Class<?> clazz;
		try {			
			
			clazz = Class.forName(parserClassName);
			this.parser = (MeterDataParser)clazz.getDeclaredConstructor().newInstance();
			
			LOG.debug("parser : {}", this.parser);
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	@Override
	public String getTimeStamp() {
		// TODO Auto-generated method stub
		return null;
	}
	
	public void decode(String data) throws Exception
    {	
		this.parser.parser(data);
    }
	
}
